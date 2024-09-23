// Defines objects that represents HTTP request and response
// and some utility functions to manipulate HTTP data

#ifndef HTTP_MESSAGE_H_
#define HTTP_MESSAGE_H_

#include <map>
#include <string>
#include <utility>

#include "uri.h"

namespace simple_http_server {

// HTTP methods defined in the following document:
// https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods
enum class HttpMethod {
  GET,
  HEAD,
  POST,
  PUT,
  DELETE,
  CONNECT,
  OPTIONS,
  TRACE,
  PATCH
};

// Here we only support HTTP/1.1
enum class HttpVersion {
  HTTP_0_9 = 9,
  HTTP_1_0 = 10,
  HTTP_1_1 = 11,
  HTTP_2_0 = 20
};

// HTTP response status codes as listed in:
// https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
// Note that not all of them are present in this enum class
enum class HttpStatusCode {
  Continue = 100,
  SwitchingProtocols = 101,
  EarlyHints = 103,
  Ok = 200,
  Created = 201,
  Accepted = 202,
  NonAuthoritativeInformation = 203,
  NoContent = 204,
  ResetContent = 205,
  PartialContent = 206,
  MultipleChoices = 300,
  MovedPermanently = 301,
  Found = 302,
  NotModified = 304,
  BadRequest = 400,
  Unauthorized = 401,
  Forbidden = 403,
  NotFound = 404,
  MethodNotAllowed = 405,
  RequestTimeout = 408,
  ImATeapot = 418,
  InternalServerError = 500,
  NotImplemented = 501,
  BadGateway = 502,
  ServiceUnvailable = 503,
  GatewayTimeout = 504,
  HttpVersionNotSupported = 505
};

// Utility functions to convert between string or integer to enum classes
std::string to_string(HttpMethod method);
std::string to_string(HttpVersion version);
std::string to_string(HttpStatusCode status_code);
HttpMethod string_to_method(const std::string& method_string);
HttpVersion string_to_version(const std::string& version_string);

/// Defines the common interface of an HTTP request and HTTP response.
/// Each message will have an HTTP version, collection of header fields,
/// and message content. The collection of headers and content can be empty.
class HttpMessageInterface {
 public:
  HttpMessageInterface() : version_(HttpVersion::HTTP_1_1) {}
  virtual ~HttpMessageInterface() = default;


  /// @brief Set a header field of the message
  /// @param key Key of the header field
  /// @param value Value of the header field
  void SetHeader(const std::string& key, const std::string& value) {
    headers_[key] = std::move(value);
  }

  /// @brief Remove a header field
  /// @param key Key of the header field to remove
  void RemoveHeader(const std::string& key) { headers_.erase(key); }

  /// @brief Clear all headers
  void ClearHeader() { headers_.clear(); }

  /// @brief Set the content of the message
  /// @param content Content to set
  void SetContent(const std::string& content) {
    content_ = std::move(content);
    SetContentLength();
  }

  /// @brief Clear the content of the message
  /// @param content
  void ClearContent(const std::string& content) {
    content_.clear();
    SetContentLength();
  }

  /// @brief Get the HTTP version of the message
  /// @return HTTP version of the message
  HttpVersion version() const { return version_; }

  /// @brief Get the value of a header field
  /// @param key Key of the header field to get
  /// @return Value of the header field
  std::string header(const std::string& key) const {
    if (headers_.count(key) > 0) return headers_.at(key);
    return std::string();
  }

  /// @brief Get all headers
  /// @return Collection of header fields
  std::map<std::string, std::string> headers() const { return headers_; }

  /// @brief Get the content of the message
  /// @return Content of the message as a string
  std::string content() const { return content_; }

  /// @brief Get the length of the content
  /// @return Length of the content as a size_t
  size_t content_length() const { return content_.length(); }

 protected:
  /// @brief Version of the http message
  HttpVersion version_;

  /// @brief Collection of header fields
  std::map<std::string, std::string> headers_;

  /// @brief Content of the message
  std::string content_;

  /// @brief Set the content length header field
  void SetContentLength() {
    SetHeader("Content-Length", std::to_string(content_.length()));
  }
};

/// An HttpRequest object represents a single HTTP request
/// It has a HTTP method and URI so that the server can identify
/// the corresponding resource and action
class HttpRequest : public HttpMessageInterface {
 public:
  HttpRequest() : method_(HttpMethod::GET) {}
  ~HttpRequest() = default;

  /// @brief Set the HTTP method of the HTTP request
  /// @param method HTTP method to set
  void SetMethod(HttpMethod method) { method_ = method; }

  /// @brief Set the URI of the HTTP request
  /// @param uri URI to set
  void SetUri(const Uri& uri) { uri_ = std::move(uri); }

  /// @brief Method of the HTTP request
  /// @return HTTP method of the request
  HttpMethod method() const { return method_; }

  /// @brief URI of the HTTP request
  /// @return URI of the request
  Uri uri() const { return uri_; }

  /// @brief Convert an HTTP request object to a string
  /// @param request HTTP request object to convert
  /// @return String representation of the HTTP request
  friend std::string to_string(const HttpRequest& request);

  /// @brief Convert a string to an HTTP request object
  /// @param request_string String to convert
  /// @return HTTP request object
  friend HttpRequest string_to_request(const std::string& request_string);

 private:
  HttpMethod method_;
  Uri uri_;
};

/// An HTTPResponse object represents a single HTTP response
/// The HTTP server sends an HTTP response to a client that include
/// an HTTP status code, headers, and (optional) content
class HttpResponse : public HttpMessageInterface {
 public:
  /// @brief Construct a new HttpResponse object with a default status code (200 OK)
  HttpResponse() : status_code_(HttpStatusCode::Ok) {}

  /// @brief Construct a new HttpResponse object with a status code
  /// @param status_code Status code of the HTTP response
  HttpResponse(HttpStatusCode status_code) : status_code_(status_code) {}
  ~HttpResponse() = default;

  /// @brief Set the status code of the HTTP response
  /// @param status_code Status code to set
  void SetStatusCode(HttpStatusCode status_code) { status_code_ = status_code; }

  /// @brief Get the status code of the HTTP response
  /// @return Status code of the HTTP response
  HttpStatusCode status_code() const { return status_code_; }

  /// @brief Convert an HTTP response object to a string
  /// @param request HTTP response object to convert
  /// @param send_content
  /// @return String representation of the HTTP response
  friend std::string to_string(const HttpResponse& request, bool send_content);

  /// @brief Convert a string to an HTTP response object
  /// @param response_string String to convert
  /// @return HTTP response object
  friend HttpResponse string_to_response(const std::string& response_string);

 private:
  HttpStatusCode status_code_;
};

// Utility functions to convert HTTP message objects to string and vice versa
std::string to_string(const HttpRequest& request);
std::string to_string(const HttpResponse& response, bool send_content = true);
HttpRequest string_to_request(const std::string& request_string);
HttpResponse string_to_response(const std::string& response_string);

}  // namespace simple_http_server

#endif  // HTTP_MESSAGE_H_
