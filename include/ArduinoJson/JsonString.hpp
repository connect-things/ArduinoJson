// Copyright Benoit Blanchon 2014-2016
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson
// If you like this project, please add a star!

#pragma once

#include "Configuration.hpp"

#if ARDUINOJSON_ENABLE_ARDUINO_STRING
#include <WString.h>
#endif

#if ARDUINOJSON_ENABLE_STD_STRING
#include <string>
#endif

namespace ArduinoJson {

template <typename TString>
class JsonString {
 public:
  // default value, even for types that are not strings
  // this simplifies SFINAE
  static const bool should_copy = false;
};

template <typename TString>
class JsonString<const TString> : public JsonString<TString> {};

template <typename TString>
class JsonString<TString&> : public JsonString<TString> {};

template <>
class JsonString<char*> {
  const char* _str;

 public:
  typedef JsonString<char*> type;

  JsonString(const char* str) : _str(str) {}

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
  static const bool should_copy = false;
};

template <size_t N>
class JsonString<char[N]> : public JsonString<char*> {};

template <>
class JsonString<const char*> : public JsonString<char*> {};

template <typename TString>
class StandardJsonString {
 protected:
  const TString* _str;

 public:
  typedef JsonString<TString> type;

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
  static const bool should_copy = true;
};

#if ARDUINOJSON_ENABLE_ARDUINO_STRING
template <>
class JsonString<String> : public StandardJsonString<String> {
 public:
  JsonString(const String& str) : StandardJsonString(str) {}
};
#endif

#if ARDUINOJSON_ENABLE_STD_STRING
template <>
class JsonString<std::string> : public StandardJsonString<std::string> {
 public:
  JsonString(const std::string& str) : StandardJsonString(str) {}
};
#endif

template <typename TString>
inline typename JsonString<TString>::type makeJsonString(const TString& str) {
  return typename JsonString<TString>::type(str);
}
}
