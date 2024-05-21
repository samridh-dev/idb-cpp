#ifndef IDBCPP_HPP
#define IDBCPP_HPP

#include <string>
#include <vector>

namespace idb {

class interface {

  public:
  
    interface(const std::string& _url, 
              const std::string& _org,
              const std::string& _bucket,
              const std::string& _token);

    template <typename T>

    bool send(const std::string& name, const std::string& tag,
              const std::vector<std::pair<std::string, T>>& keyval);

    inline bool send(const std::string& data);

  private:

    const std::string url;
    const std::string org;
    const std::string bucket;
    const std::string token;

};

} // namespace idb
#include "idb.ipp"

#endif
