#ifndef IDBCPP_HPP
#define IDBCPP_HPP

#include <string>

namespace idb {

class interface {

  public:
  
    interface(const std::string& _url, 
              const std::string& _org,
              const std::string& _bucket,
              const std::string& _token);
  
    template <typename T>
    bool write(const std::string& name, const std::string& tag,
               const std::string& key, const T& val);

  private:

    const std::string url;
    const std::string org;
    const std::string bucket;
    const std::string token;

    bool send_data(const std::string& data);

};

} // namespace idb

#endif
