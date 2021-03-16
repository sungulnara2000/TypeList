#include "typelist.hpp"

void test_erase() {
    static_assert(std::is_same<NullType, Erase<NullType, char>::Result>::value);

    static_assert(std::is_same<EmptyList, Erase<TypeList<>, char>::Result>::value);

    static_assert(std::is_same<EmptyList, Erase<TypeList<char>, char>::Result>::value);

    static_assert(std::is_same<TypeList<char>, Erase<TypeList<char, char>, char>::Result>::value);

    static_assert(std::is_same<TypeList<int>, Erase<TypeList<int, char>, char>::Result>::value);

    static_assert(std::is_same<TypeList<bool>, Erase<Erase<TypeList<bool, int, char>, char>::Result, int>::Result>::value);
}