// Copyright Benoit Blanchon 2014-2016
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson
// If you like this project, please add a star!

#pragma once

#include "../Configuration.hpp"

#if ARDUINOJSON_ENABLE_ARDUINO_STRING
#include <WString.h>
#endif

#if ARDUINOJSON_ENABLE_STD_STRING
#include <string>
#endif

namespace ArduinoJson {
namespace Internals {

// A meta-function returning the JsonString type to be used for a TString
template <typename TString>
struct GetJsonString {};

class CharPtrJsonString {
  const char* _str;

 public:
  CharPtrJsonString(const char* str) : _str(str) {}

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
  static const bool should_duplicate = false;
};

template <>
struct GetJsonString<const char*> {
  typedef CharPtrJsonString type;
};

template <>
struct GetJsonString<char*> {
  typedef CharPtrJsonString type;
};

template <typename TString>
class StlJsonString {
 protected:
  const TString* _str;

 public:
  StlJsonString(const TString& str) : _str(&str) {}

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

  static void append(TString& str, char c) {
    str += c;
  }

  static const bool has_append = true;
  static const bool should_duplicate = true;
};

#if ARDUINOJSON_ENABLE_ARDUINO_STRING
template <>
struct GetJsonString<String> {
  typedef StlJsonString<String> type;
};
template <>
struct GetJsonString<StringSumHelper> {
  typedef StlJsonString<StringSumHelper> type;
};
#endif

#if ARDUINOJSON_ENABLE_STD_STRING
template <>
struct GetJsonString<std::string> {
  typedef StlJsonString<std::string> type;
};
#endif

template <typename TString>
inline typename GetJsonString<TString>::type makeJsonString(
    const TString& str) {
  return typename GetJsonString<TString>::type(str);
}
}
}
