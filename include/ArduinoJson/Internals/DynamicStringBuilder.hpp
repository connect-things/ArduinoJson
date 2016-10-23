// Copyright Benoit Blanchon 2014-2016
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson
// If you like this project, please add a star!

#pragma once

#include "../JsonString.hpp"
#include "../Print.hpp"

namespace ArduinoJson {
namespace Internals {

// A Print implementation that allows to write in a String
template <typename TString>
class DynamicStringBuilder : public Print {
 public:
  DynamicStringBuilder(TString &str) : _str(str) {}

  virtual size_t write(uint8_t c) {
    _str.append(c);
    return 1;
  }

 private:
  DynamicStringBuilder &operator=(const DynamicStringBuilder &);

  typename JsonString<TString>::type _str;
};
}
}
