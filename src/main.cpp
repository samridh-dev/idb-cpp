#include <iostream>

#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <chrono>
#include <thread>

#include <getopt.h>
#include <cstdlib>

#include <idb.hpp>
int main(int argc, char* argv[]) {

  std::cout << "hello world!" << std::endl;

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
    {nullptr, 0, nullptr, 0}
  };

  while ((option = getopt_long(argc, argv, "u:o:b:t:n:g:", 
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
      case '?':
        break;
      default:
        std::abort();
    }
  }

  class idb::interface iface(url, org, bucket, token);

  for (const auto& keyval : keyval_pairs) {
    std::vector<std::pair<std::string, double>> keyval_vector = {keyval};

    const auto ret = iface.send(name, tag, keyval_vector);
    if (ret) std::cout << " (success)" << std::endl;
    else std::cout << " (failure)" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}
