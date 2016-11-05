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

  static bool equals(const char* str, const char* expected) {
    return strcmp(str, expected) == 0;
  }

  template <typename Buffer>
  static char* duplicate(const char* str, Buffer* buffer) {
    if (!str) return NULL;
    size_t size = strlen(str) + 1;
    void* dup = buffer->alloc(size);
    if (dup != NULL) memcpy(dup, str, size);
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
  static char* duplicate(const TString& str, Buffer* buffer) {
    if (!str.c_str()) return NULL;  // <- Arduino string can return NULL
    size_t size = str.length() + 1;
    void* dup = buffer->alloc(size);
    if (dup != NULL) memcpy(dup, str.c_str(), size);
    return static_cast<char*>(dup);
  }

  static bool equals(const TString& str, const char* expected) {
    return str == expected;
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
