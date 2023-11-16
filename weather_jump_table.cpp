#include <array>
#include <cstdio>
#include <immintrin.h>
#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>

static inline __attribute__((always_inline)) void freezing(unsigned &val) {
  val |= 1;
}

static inline __attribute__((always_inline)) void dirty(unsigned &val) {
  val |= 2;
}

static inline __attribute__((always_inline)) void dry(unsigned &val) {
  val |= 4;
}

static inline __attribute__((always_inline)) void windy(unsigned &val) {
  val |= 8;
}

static inline __attribute__((always_inline)) void sunny(unsigned &val) {
  val |= 16;
}

static inline __attribute__((always_inline)) void dupa_1(unsigned &val) {
  val |= 32;
}

static inline __attribute__((always_inline)) void dupa_2(unsigned &val) {
  val |= 64;
}

static inline __attribute__((always_inline)) void dupa_3(unsigned &val) {
  val |= 128;
}

static inline __attribute__((always_inline)) void dupa_4(unsigned &val) {
  val |= 256;
}

static inline __attribute__((always_inline)) void dupa_5(unsigned &val) {
  val |= 512;
}

static inline __attribute__((always_inline)) void dupa_6(unsigned &val) {
  val |= 1024;
}

static inline __attribute__((always_inline)) void dupa_7(unsigned &val) {
  val |= 2048;
}

static inline __attribute__((always_inline)) void dupa_8(unsigned &val) {
  val |= 4096;
}

using fnptr = void (*)(unsigned &);
constexpr static fnptr functs[]{freezing, dirty,  dry,    windy,  sunny,
                                dupa_1,   dupa_2, dupa_3, dupa_4, dupa_5,
                                dupa_6,   dupa_7, dupa_8};

template <size_t NUM>
constexpr static __attribute__((always_inline)) void
get_weather_in_russia(unsigned &s) {
  functs[NUM](s);
}

template <size_t Value> static constexpr size_t lowest_bit_index() {
  if (Value == 0)
    return 0;

  if (Value & 1)
    return 1;

  constexpr auto ShiftedValue = Value >> 1;
  return 1 + lowest_bit_index<ShiftedValue>();
}

template <size_t NUM>
constexpr static __attribute__((always_inline)) void
weather(unsigned &s) noexcept {
  if (NUM) {
    constexpr auto idx = lowest_bit_index<NUM>() - 1;
    constexpr auto mask = NUM & (NUM - 1);
    weather<mask>(s);
    get_weather_in_russia<idx>(s);
  }
}

template <size_t... Seq>
constexpr auto generate_array_helper(std::index_sequence<Seq...>)
    -> std::array<void (*)(unsigned &), sizeof...(Seq)> {
  return {{weather<Seq>...}};
}

template <size_t N> constexpr auto generate_array() {
  return generate_array_helper(std::make_index_sequence<N>{});
}
template <class T, size_t N>
static constexpr size_t array_size(const T (&)[N]) noexcept {
  return N;
}
static constexpr auto fn_arr = generate_array<(1u << array_size(functs))>();

int main() {
  size_t bitmask = 0;
  std::cin >> bitmask;

  unsigned s = 0;
  fn_arr[bitmask](s);
  std::cout << s;
}
