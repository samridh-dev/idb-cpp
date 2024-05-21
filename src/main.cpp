#include <iostream>
#include <vector>
#include <string>
#include <getopt.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <idb.hpp>

static void print_help() {
  std::cout << "Usage: idb[options]\n"
        << "Options:\n"
        << "  -u, --url     <url>           URL of the InfluxDB server\n"
        << "  -o, --org     <organization>  InfluxDB organization\n"
        << "  -b, --bucket  <bucket>        Bucket to send data to\n"
        << "  -t, --token   <token>         Token for write access\n"
        << "  -n, --name    <name>          Name of the database\n"
        << "  -g, --tag     <tag>           Metadata tag\n"
        << "  -h, --help                    Display this help message"
        << std::endl;
}

int main(int argc, char* argv[]) {

  const std::vector<std::pair<std::string, double>> keyval_pairs = [] {
    std::vector<std::pair<std::string, double>> pairs;
    for (int i = 0; i <= 1000; ++i) {
      pairs.emplace_back("value", i);
    }
    return pairs;
  }();

  std::string url = "";
  std::string org = "";
  std::string bucket = "";
  std::string token = "";
  std::string name = "";
  std::string tag = "";

  int option;
  static struct option long_options[] = {
    {"url", required_argument, nullptr, 'u'},
    {"org", required_argument, nullptr, 'o'},
    {"bucket", required_argument, nullptr, 'b'},
    {"token", required_argument, nullptr, 't'},
    {"name", required_argument, nullptr, 'n'},
    {"tag", required_argument, nullptr, 'g'},
    {"help", no_argument, nullptr, 'h'},
    {nullptr, 0, nullptr, 0}
  };

  while ((option = getopt_long(argc, argv, "u:o:b:t:n:g:h",
                               long_options, nullptr)) != -1) {
    switch (option) {
      case 'u':
        url = optarg;
        break;
      case 'o':
        org = optarg;
        break;
      case 'b':
        bucket = optarg;
        break;
      case 't':
        token = optarg;
        break;
      case 'n':
        name = optarg;
        break;
      case 'g':
        tag = optarg;
        break;
      case 'h':
        print_help();
        return 0;
      case '?':
        print_help();
        return 1;
      default:
        std::abort();
    }
  }

  if (url.empty()    || org.empty()   || 
      bucket.empty() || token.empty() ||
      name.empty()   || tag.empty())  {
    std::cerr << "Error: All options must be specified.\n";
    print_help();
    return 1;
  }

  idb::interface iface(url, org, bucket, token);
  if (!iface.check_server()) {
    return 1;
  }

  for (const auto& keyval : keyval_pairs) {
    std::vector<std::pair<std::string, double>> keyval_vector = {keyval};

    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    const auto ret = iface.send(name, tag, keyval_vector);
    auto end = high_resolution_clock::now();
    auto elapsed = duration_cast<milliseconds>(end - start);

    std::cout << "\r" << std::string(100, ' ') << std::flush;
    std::cout << "\rInfluxdb server write time: " 
              << elapsed.count() << "ms"
              << std::flush;


    if (!ret) break;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}
