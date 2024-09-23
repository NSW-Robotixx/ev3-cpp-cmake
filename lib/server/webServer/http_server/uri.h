// Define object that can be used to represent a Unique Resource Identifier
// which is useful for parsing and request handling

#ifndef URI_H_
#define URI_H_

#include <algorithm>
#include <cctype>
#include <string>
#include <utility>
#include <cstdint>

namespace simple_http_server {

/// A Uri object will contain a valid scheme (for example: HTTP), host,
/// port, and the actual URI path
class Uri {
 public:
  Uri() = default;
  
  /// @brief Construct a URI object with a path
  /// @param path Path of the URI
  explicit Uri(const std::string& path) : path_(path) { SetPathToLowercase(); }
  
  ~Uri() = default;

  /// @brief Check if one URI is less than another
  /// @param other Other URI compared to
  /// @return True if the URI is less than the other, false otherwise
  inline bool operator<(const Uri& other) const { return path_ < other.path_; }

  /// @brief Check if two URIs are equal
  /// @param other Other URI compared to
  /// @return True if the URIs are equal, false otherwise
  inline bool operator==(const Uri& other) const {
    return path_ == other.path_;
  }

  /// @brief Set the path of the URI
  /// @param path Path to set
  void SetPath(const std::string& path) {
    path_ = std::move(path);
    SetPathToLowercase();
  }

  /// @brief Get the scheme of the URI
  /// @return Scheme of the URI
  std::string scheme() const { return scheme_; }

  /// @brief Get the host of the URI
  /// @return The host of the URI
  std::string host() const { return host_; }

  /// @brief Get the port of the URI
  /// @return Port of the URI
  uint16_t port() const { return port_; }

  /// @brief Get the path of the URI
  /// @return Path of the URI
  std::string path() const { return path_; }

 private:
  // Only the path is supported for now
  std::string path_;
  std::string scheme_;
  std::string host_;
  uint16_t port_;

  void SetPathToLowercase() {
    std::transform(path_.begin(), path_.end(), path_.begin(),
                   [](char c) { return tolower(c); });
  }
};

}  // namespace simple_http_server

#endif  // URI_H_
