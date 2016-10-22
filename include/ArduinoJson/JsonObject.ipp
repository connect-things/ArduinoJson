// Copyright Benoit Blanchon 2014-2016
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson
// If you like this project, please add a star!

#pragma once

#include "JsonArray.hpp"
#include "JsonObject.hpp"
#include "JsonObjectSubscript.hpp"

namespace ArduinoJson {

template <>
inline const JsonObject &JsonVariant::defaultValue<const JsonObject &>() {
  return JsonObject::invalid();
}

template <>
inline const JsonObject &JsonVariant::defaultValue<const JsonObject>() {
  return JsonObject::invalid();
}

template <>
inline JsonObject &JsonVariant::defaultValue<JsonObject &>() {
  return JsonObject::invalid();
}

template <>
inline JsonObject &JsonVariant::defaultValue<JsonObject>() {
  return JsonObject::invalid();
}

inline JsonObject &JsonVariant::asObject() const {
  if (_type == Internals::JSON_OBJECT) return *_content.asObject;
  return JsonObject::invalid();
}

template <typename TString>
inline JsonObject &JsonObject::createNestedObject(const TString &key) {
  if (!_buffer) return JsonObject::invalid();
  JsonObject &array = _buffer->createObject();
  setNodeAt(makeJsonString(key), array);
  return array;
}

inline JsonObject &JsonArray::createNestedObject() {
  if (!_buffer) return JsonObject::invalid();
  JsonObject &object = _buffer->createObject();
  add(object);
  return object;
}
}
