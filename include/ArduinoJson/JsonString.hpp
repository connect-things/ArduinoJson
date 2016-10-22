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
  const TString& _str;

 public:
  JsonString(const TString& str) : _str(str) {}

  const char* c_str() const {
    return _str.c_str();
  }

  bool equals(const char* expected) const {
    return _str == expected;
  }

  static const bool has_c_str = true;
};

template <>
class JsonString<char*> {
  const char* _str;

 public:
  JsonString(const char* str) : _str(str) {}

  const char* c_str() const {
    return _str;
  }

  bool equals(const char* expected) const {
    return !strcmp(_str, expected);
  }

  static const bool has_c_str = true;
};

template <typename TString>
JsonString<typename TypeTraits::Decay<TString>::type> makeJsonString(
    const TString& str) {
  return JsonString<typename TypeTraits::Decay<TString>::type>(str);
}
}
