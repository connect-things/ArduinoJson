// Copyright Benoit Blanchon 2014-2016
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson
// If you like this project, please add a star!

#pragma once

namespace ArduinoJson {

// Tags defining the way a value is stored
namespace StoragePolicy {
struct Default {};
struct Clone {};
}

// A meta-function that returns the StoragePolicy for a given type
template <typename T>
struct GetStoragePolicy {
  typedef StoragePolicy::Default type;
};

// An helper to call GetStoragePolicy<T> concisely
template <typename T>
typename GetStoragePolicy<T>::type getStoragePolicy(const T&) {
  return typename GetStoragePolicy<T>::type();
}
}
