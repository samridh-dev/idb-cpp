#include <sstream>
#include <chrono>
#include <iostream>

template <typename T>
bool idb::interface::send(
  const std::string& name, const std::string& tag,
  const std::vector<std::pair<std::string, T>>& keyval
) {

  std::ostringstream oss;
  oss << name << "," 
      << tag << " "; 

  for (size_t i = 0; i < keyval.size(); ++i) {

    const auto& key = keyval[i].first;
    const auto& val = keyval[i].second;

    if (i != 0) oss << ",";
    oss << key << "=" << val;

  }

  using namespace std::chrono;
  auto now = system_clock::now();
  auto timestamp = duration_cast<milliseconds>(now.time_since_epoch());
  oss << " " << timestamp.count();

  return send(oss.str());

}

#include <curl/curl.h>
inline bool idb::interface::send(const std::string& data) {

  std::ostringstream url;
  url << (*this).url << "/api/v2/write" 
      << "?org="        << (*this).org 
      << "&bucket="     << (*this).bucket
      << "&precision="  << "ms";

  std::ostringstream auth;
  auth << "Authorization: Token " << (*this).token;
  struct curl_slist* headers = nullptr;
  headers = curl_slist_append(headers, auth.str().c_str());

  CURL* handle = curl_easy_init();
  if (!handle) {
    return false;
  }
  
  curl_easy_setopt(handle, CURLOPT_URL, url.str().c_str());
  curl_easy_setopt(handle, CURLOPT_POST, 1L);
  curl_easy_setopt(handle, CURLOPT_POSTFIELDS, data.c_str());
  curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);

  CURLcode res = curl_easy_perform(handle);
  if (res != CURLE_OK) {

    std::cerr << "\n\033[31mError: \033[0m"
              << "curl request failed: " 
              << curl_easy_strerror(res) 
              << std::endl;

    curl_slist_free_all(headers);
    curl_easy_cleanup(handle);
    return false;
  }

  long http_code = 0;
  curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &http_code);
  if (http_code != 204) {

    std::cerr << "\n\033[31mError: \033[0m"
              << "write to InfluxDB server failed" 
              << " (code:" << http_code << ")"
              << std::endl;

    curl_slist_free_all(headers);
    curl_easy_cleanup(handle);
    return false;
  }

  
  curl_slist_free_all(headers);
  curl_easy_cleanup(handle);
  return true;

}
