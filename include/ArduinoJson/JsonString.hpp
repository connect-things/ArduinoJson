// Copyright Benoit Blanchon 2014-2016
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson
// If you like this project, please add a star!

#pragma once

#include "String.hpp"

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

  static const bool has_append = false;
  static const bool should_copy = false;
};

template <size_t N>
class JsonString<char[N]> : public JsonString<char*> {};

template <>
class JsonString<const char*> : public JsonString<char*> {};

template <>
class JsonString<String> {
 protected:
  const String* _str;

 public:
  typedef JsonString<String> type;

  JsonString(const String& str) : _str(&str) {}

  const char* c_str() const {
    return _str->c_str();
  }

  bool equals(const char* expected) const {
    return strcmp(_str->c_str(), expected) == 0;
  }

  void append(char c) {
    *const_cast<String*>(_str) += static_cast<char>(c);
  }

  static const bool has_append = true;
  static const bool should_copy = true;
};

template <typename TString>
inline typename JsonString<TString>::type makeJsonString(const TString& str) {
  return typename JsonString<TString>::type(str);
}
}
