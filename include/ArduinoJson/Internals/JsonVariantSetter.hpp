// Copyright Benoit Blanchon 2014-2016
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson
// If you like this project, please add a star!

#pragma once

#include "../JsonBuffer.hpp"
#include "../JsonVariant.hpp"
#include "../TypeTraits/EnableIf.hpp"
#include "JsonString.hpp"

namespace ArduinoJson {
namespace Internals {

template <typename T, typename Enable = void>
struct JsonVariantSetter {
  static bool set(JsonBuffer*, JsonVariant& destination, const T& value) {
    destination = value;
    return true;
  }
};

template <typename T>
struct JsonVariantSetter<T, typename TypeTraits::EnableIf<GetJsonString<
                                T>::type::should_duplicate>::type> {
  static bool set(JsonBuffer* buffer, JsonVariant& destination,
                  const T& value) {
    const char* copy = buffer->strdup(value);
    if (!copy) return false;
    destination = copy;
    return true;
  }
};
}
}
