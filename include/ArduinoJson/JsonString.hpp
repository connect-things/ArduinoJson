// Copyright Benoit Blanchon 2014-2016
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson
// If you like this project, please add a star!

#pragma once

#include "TypeTraits/Decay.hpp"

namespace ArduinoJson {

template <typename TString>
class JsonString {
 public:
  typedef JsonString<typename TypeTraits::Decay<TString>::type> type;
};

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

  static const bool has_c_str = true;
  static const bool should_copy = false;
};

template <>
class JsonString<String> {
  const String& _str;

 public:
  typedef JsonString<String> type;

  JsonString(const String& str) : _str(str) {}

  const char* c_str() const {
    return _str.c_str();
  }

  bool equals(const char* expected) const {
    return _str == expected;
  }

  static const bool has_c_str = true;
  static const bool should_copy = true;
};

template <typename TString>
inline typename JsonString<TString>::type makeJsonString(const TString& str) {
  return typename JsonString<TString>::type(str);
}
}
