// Copyright Benoit Blanchon 2014-2016
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson
// If you like this project, please add a star!

#pragma once

#include "Configuration.hpp"
#include "StoragePolicy.hpp"

#if ARDUINOJSON_ENABLE_ARDUINO_STRING
#include <WString.h>
#endif

#if ARDUINOJSON_ENABLE_STD_STRING
#include <string>
#endif

namespace ArduinoJson {

// A meta-function returning the JsonString type to be used for a TString
template <typename TString>
struct GetJsonString {};

template <typename TString>
struct GetJsonString<const TString> : GetJsonString<TString> {};

template <typename TString>
struct GetJsonString<TString&> : GetJsonString<TString> {};

class StaticJsonString {
  const char* _str;

 public:
  StaticJsonString(const char* str) : _str(str) {}

  const char* c_str() const {
    return _str;
  }

  bool equals(const char* expected) const {
    return strcmp(_str, expected) == 0;
  }

  template <typename Buffer>
  char* duplicate(Buffer* buffer) const {
    if (!_str) return NULL;
    size_t size = strlen(_str) + 1;
    void* dup = buffer->alloc(size);
    if (dup != NULL) memcpy(dup, _str, size);
    return static_cast<char*>(dup);
  }

  static const bool has_append = false;
};

template <size_t N>
struct GetJsonString<char[N]> {
  typedef StaticJsonString type;
};

template <>
struct GetJsonString<const char*> {
  typedef StaticJsonString type;
};

template <>
struct GetJsonString<char*> {
  typedef StaticJsonString type;
};

template <typename TString>
class StandardJsonString {
 protected:
  const TString* _str;

 public:
  StandardJsonString(const TString& str) : _str(&str) {}

  const char* c_str() const {
    return _str->c_str();
  }

  template <typename Buffer>
  char* duplicate(Buffer* buffer) const {
    if (!_str->c_str()) return NULL;
    size_t size = _str->length() + 1;
    void* dup = buffer->alloc(size);
    if (dup != NULL) memcpy(dup, _str->c_str(), size);
    return static_cast<char*>(dup);
  }

  bool equals(const char* expected) const {
    return strcmp(_str->c_str(), expected) == 0;
  }

  void append(char c) {
    *const_cast<TString*>(_str) += static_cast<char>(c);
  }

  static const bool has_append = true;

  typedef StoragePolicy::Clone storage_policy;
};

#if ARDUINOJSON_ENABLE_ARDUINO_STRING
template <>
struct GetJsonString<String> {
  typedef StandardJsonString<String> type;
};
template <>
struct GetStoragePolicy<String> {
  typedef StoragePolicy::Clone type;
};
#endif

#if ARDUINOJSON_ENABLE_STD_STRING
template <>
struct GetJsonString<std::string> {
  typedef StandardJsonString<std::string> type;
};
template <>
struct GetStoragePolicy<std::string> {
  typedef StoragePolicy::Clone type;
};
#endif

template <typename TString>
inline typename GetJsonString<TString>::type makeJsonString(
    const TString& str) {
  return typename GetJsonString<TString>::type(str);
}
}
