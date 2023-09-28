// Type your code here, or load an example.
#include <cstdio>
#include <stdint.h>
#include <immintrin.h>
#include <array>
#include <iostream>
#include <vector>
#include <string>

static inline void freezing(std::string& s)
{
    s.append("freezing ");
}

static inline void dirty(std::string& s)
{
        s.append("dirty ");

}

static inline void dry(std::string& s)
{
    s.append("dry ");
}

static inline void windy(std::string& s)
{
    s.append("windy ");
}
using fnptr = void(*)(std::string&);
constexpr static std::array<fnptr, 4> functs {freezing, dirty, dry, windy};

template <size_t NUM>
constexpr static void get_weather_in_russia(std::string &s)
{
    functs[NUM](s);
}

template <size_t Value>
static constexpr size_t lowest_bit_index()
{   
    if (Value == 0)
        return 0;

    if(Value & 1)
        return 1;

    constexpr auto ShiftedValue = Value >> 1;
    return 1 + lowest_bit_index<ShiftedValue>();
}

template <size_t NUM>
constexpr static void weather( std::string & s)
{
    if(NUM)
    {
        constexpr auto idx = lowest_bit_index<NUM>() -1;
        constexpr auto mask = NUM & (NUM-1);
        weather<mask>(s);
        get_weather_in_russia<idx>(s);
    }
}


template <size_t... Seq>
constexpr auto generate_array_helper(std::index_sequence<Seq...>)-> std::array<void(*)(std::string&), sizeof...(Seq)>
{
    return {{weather<Seq>...}};
}

template <size_t N> constexpr auto generate_array()
{
    return generate_array_helper(std::make_index_sequence<N>{});
}

static constexpr std::array<void(*)(std::string&), 16> fn_arr = generate_array<16>();

int main()
{   
    size_t bitmask = 0;
    std::cin >> bitmask;

    std::string s;
    fn_arr[bitmask](s);
    std::cout << s;

}