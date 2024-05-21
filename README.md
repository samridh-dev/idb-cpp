# InfluxDB C++ (idbcpp)

This is a write only library to an Influxdb server implemented in c++.

## Installation
Currently only source installation is possible.
This run script will be sufficient to generate a working executable. Edit as
you see fit.

NOTE: to configure the project, refer to the /cmake/config.cmake file.

```bash
REPO_NAME="periodic-async"
git clone https://github.com/samridh-dev/periodic-async.git $REPO_NAME
pushd $REPO_NAME
git submodule update --init --recursive
mkdir -p bin/ dat/
mkdir -p cmake/build/
pushd cmake/build
cmake ../.. -Wdev
make -j $(nproc)
popd
```

## Usage

```cpp
int main(int argc, char* argv[]) {
    
  std::string url = "";     // url to server
  std::string org = "";     // organization name
  std::string bucket = "";  // bucket name
  std::string token = "";   // authorization token
  std::string name = "";    // name of database
  std::string tag = "";     // metadata

  // example data to send to server 
  const std::vector<std::pair<std::string, double>> keyval_pairs = [] {
    std::vector<std::pair<std::string, double>> pairs;
    for (int i = 0; i <= 1000; ++i) {
      pairs.emplace_back("value", i);
    }
    return pairs;
  }();
    
 
  // create influxdb interface object
  idb::interface iface(url, org, bucket, token);

  // check if connection to influxdb server is possible 
  if (!iface.check_server()) {
    return -1;
  }

  for (const auto& keyval : keyval_pairs) {
    
    // convert to vector of pairs (supports more than one field insertion)
    std::vector<std::pair<std::string, double>> keyval_vector = {keyval};

    // send data to influxdb server. break if write fails.
    if (!iface.send(name, tag, keyval_vector)) break;

    // sleep for some reason
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}
```
