#ifndef IDBCPP_HPP
#define IDBCPP_HPP

#include <string>
#include <vector>

namespace idb {
/**
 * @class interface
 * @brief Class to interact with an InfluxDB database.
 */
class interface {

  public:
  
  /**
   * @brief Constructs an interface object.
   * @param _url The URL of the InfluxDB server.
   * @param _org The InfluxDB organization.
   * @param _bucket The bucket to send data to.
   * @param _token The token for write access.
   */
  interface(const std::string& _url, 
            const std::string& _org,
            const std::string& _bucket,
            const std::string& _token);
  
  /**
   * @brief Checks if Influxdb server is ready to recieve data
   */ 
  bool check_server() const;

  /**
   * @brief Sends data to the InfluxDB database.
   * @tparam T The type of the field values.
   * @param name The name of the database.
   * @param tag The metadata tag.
   * @param keyval A vector of pairs of field names and values.
   * @return True if the data was sent successfully, false otherwise.
   */
  template <typename T>
  bool send(const std::string& name, const std::string& tag,
        const std::vector<std::pair<std::string, T>>& keyval);

  /**
   * @brief Sends raw string data to the InfluxDB database.
   * @param data The raw data string.
   * @return True if the data was sent successfully, false otherwise.
   */
  inline bool send(const std::string& data);

  private:

    const std::string url;    /**< URL of the InfluxDB server */
    const std::string org;    /**< InfluxDB organization */
    const std::string bucket; /**< Bucket to send data to */
    const std::string token;  /**< Token for write access */

};

} // namespace idb
#include "idb.ipp"
#endif
