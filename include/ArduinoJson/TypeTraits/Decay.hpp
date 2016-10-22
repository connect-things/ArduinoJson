// Copyright Benoit Blanchon 2014-2016
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson
// If you like this project, please add a star!

#pragma once

#include "RemoveConst.hpp"
#include "RemoveReference.hpp"

namespace ArduinoJson {
namespace TypeTraits {

template <typename T>
struct Decay {
  typedef typename RemoveConst<typename RemoveReference<T>::type>::type type;
};

template <typename T>
struct Decay<T[]> {
  typedef typename Decay<T>::type* type;
};

template <typename T, size_t N>
struct Decay<T[N]> {
  typedef typename Decay<T>::type* type;
};
}
}
