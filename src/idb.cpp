#include <idb.hpp>
#include <curl/curl.h>

idb::interface::interface(const std::string& _url, 
                          const std::string& _org,
                          const std::string& _bucket,
                          const std::string& _token) 
  : url(_url), org(_org), bucket(_bucket), token(_token) {}

bool idb::interface::check_server() const {

  CURL* handle = curl_easy_init();
  if (!handle) {

    std::cerr << "\033[31mError: \033[0m"
              << "Failed to initialize curl" 
              << std::endl;

    return false;
  }

  curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
  curl_easy_setopt(handle, CURLOPT_NOBODY, 1L);

  CURLcode res = curl_easy_perform(handle);
  if (res != CURLE_OK) {

    std::cerr << "\033[31mError: \033[0m" 
              << "Unable to reach InfluxDB server at " 
              << url 
              << " (" << curl_easy_strerror(res) << ")" 
              << std::endl;

    curl_easy_cleanup(handle);
    return false;
  }
  
  long http_code = 0;
  curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &http_code);
  if (http_code < 200 || http_code >= 300) {

    std::cerr << "\033[31mError: \033[0m" 
              << "Influxdb server at " << url
              << " responded with HTTP code " << http_code 
              << std::endl;

    curl_easy_cleanup(handle);
    return false;
  }

  curl_easy_cleanup(handle);
  return true;

}
