#include <iostream>

//-----------------------------------------------------------------//

class NullType {
};

template<typename T=NullType, typename ... U>
struct TypeList {
    using head = T;
    using tail = TypeList<U ...>;
};

//-----------------------------------------------------------------//

template<class TList, class T>
struct Append {
};

template<typename ...Args>
struct Append<TypeList<Args...>, NullType> {
    using Result = TypeList<Args...>;
};

template<typename ...Args>
struct Append<TypeList<Args...>, TypeList<>> {
    using Result = TypeList<Args...>;
};

template<typename T, typename ...Args>
struct Append<TypeList<Args...>, T> {
    using Result = TypeList<Args..., T>;
};

template<typename ...Args1, typename ...Args2>
struct Append<TypeList<Args1...>, TypeList<Args2...>> {
    using Result = TypeList<Args1..., Args2...>;
};

//-----------------------------------------------------------------//

template<class TList, class T>
struct Erase {
};

template<class T>
struct Erase<NullType, T> {
    using Result = NullType;
};

template<typename T>
struct Erase<TypeList<>, T> {
    using Result = TypeList<>;
};

template<typename T, typename ...Args>
struct Erase<TypeList<Args...>, T> {
    using Head = typename TypeList<Args...>::head;
    using Tail = typename TypeList<Args...>::tail;
    using Removed = typename Erase<Tail, T>::Result;
    using Result = typename std::conditional<
            std::is_same<Head, T>::value,
            Tail,
            typename Append<TypeList<Head>, Removed>::Result
    >::type;
};

//-----------------------------------------------------------------//

template<typename TypeList>
struct Length {
    enum {
        value = Length<typename TypeList::tail>::value + 1
    };
};

template<>
struct Length<NullType> {
    enum {
        value = 0
    };
};

template<>
struct Length<TypeList<>> {
    enum {
        value = 0
    };
};

//-----------------------------------------------------------------//

using EmptyList = TypeList<>;
