#include <idb.hpp>
#include <sstream>

idb::interface::interface(const std::string& _url, 
                          const std::string& _org,
                          const std::string& _bucket,
                          const std::string& _token) 
  : url(_url), org(_org), bucket(_bucket), token(_token) {}


template <typename T>
bool idb::interface::write(const std::string& name, const std::string& tag,
                           const std::string& key, const T& val) {
  
  (void) name;
  (void) tag;
  (void) key;
  (void) val;

  return true;

}

#include <curl/curl.h>
bool idb::interface::send_data(const std::string& data) {

  (void)data;

  CURL* handle = curl_easy_init();
  if (!handle) {
    return false;
  }

  {

    std::ostringstream oss;
    oss << (*this).url << "/api/v2/write" 
        << "?org=" << (*this).org 
        << "&bucket=" << (*this).bucket
        << "&precision=" << "s";

    curl_easy_setopt(handle, CURLOPT_URL, oss.str().c_str());

  }
  
  return true;

}

