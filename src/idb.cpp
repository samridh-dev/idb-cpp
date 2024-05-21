#include <idb.hpp>
idb::interface::interface(const std::string& _url, 
                          const std::string& _org,
                          const std::string& _bucket,
                          const std::string& _token) 
  : url(_url), org(_org), bucket(_bucket), token(_token) {}
