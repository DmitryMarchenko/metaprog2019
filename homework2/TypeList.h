#pragma once

template <class T, class U>
class Conversion {
    typedef char Small;
    class Big { char dummy[2]; };
    static Small Test(U);
    static Big Test(...);
    static T MakeT();
public:
    enum { exists = sizeof(Test(MakeT())) == sizeof(Small) };
    enum { sameType = false };
};

template <class T>
class Conversion<T, T> {
public:
    enum { exists = 1, sameType = 1 };
};

#define SUPERSUBCLASS(T, U) \
    (Conversion<const U*, const T*>::exists && \
    !Conversion<const T*, const void*>::sameType)

template <typename T>
struct Type2Type {
    using type = T;
};

class NullType {};

template <typename... Ts>
struct TypeList {};

namespace TL {

    template <typename TList, size_t ind> struct TypeAt;

    template <typename Head, typename... Tail>
    struct TypeAt<TypeList<Head, Tail...>, 0> {
        using result = Head;
    };

    template <typename Head, typename... Tail, size_t i>
    struct TypeAt<TypeList<Head, Tail...>, i> {
        using result = typename TypeAt<TypeList<Tail...>, i - 1>::result;
    };

    template <typename TList, typename T> struct TypeExists;

    template <typename T>
    struct TypeExists<TypeList<>, T> {
        static constexpr bool result = false;
    };

    template <typename T, typename... Tail>
    struct TypeExists<TypeList<T, Tail...>, T> {
        static constexpr bool result = true;
    };

    template <typename Head, typename... Tail, typename T>
    struct TypeExists<TypeList<Head, Tail...>, T> {
        static constexpr bool result = TypeExists<TypeList<Tail...>, T>::result;
    };

    template <typename TList, typename T> struct ListWithType;

    template <typename T>
    struct ListWithType<TypeList<>, T> {
        using result = NullType;
    };

    template <typename Head, typename... Tail, typename T>
    struct ListWithType<TypeList<Head, Tail...>, T> {
        using result = typename std::conditional<
                TypeExists<Head, T>::result,
                Head,
                typename ListWithType<TypeList<Tail...>, T>::result
        >::type;
    };

    template <typename TList, typename T> struct Append;

    template <typename... Ts, typename T>
    struct Append<TypeList<Ts...>, T> {
        using result = TypeList<Ts..., T>;
    };

    template <typename TList> struct Reverse;

    template <typename Head, typename... Tail>
    struct Reverse<TypeList<Head, Tail...>> {
        using ReversedTail = typename Reverse<TypeList<Tail...>>::result;
        using result = typename Append<ReversedTail, Head>::result;
    };

    template <>
    struct Reverse<TypeList<>> {
        using result = TypeList<>;
    };

    template <typename TList> struct GetTail;

    template <typename Head, typename... Tail>
    struct GetTail<TypeList<Head, Tail...> > {
        using result = TypeList<Tail...>;
    };

    template <typename... TLists> struct GetSupers;

    template <typename Head, typename... Tail, typename TList, typename... OthersTLists>
    struct GetSupers<TypeList<Head, Tail...>, TList, OthersTLists...> {
        using OthersRes = typename GetSupers<TList, OthersTLists...>::result;
        using OthersResHead = typename TypeAt<OthersRes, 0>::result;
        using result = typename std::conditional<
                SUPERSUBCLASS(Head, OthersResHead),
                TypeList<Head, Tail...>,
                OthersRes
        >::type;
    };

    template <typename TList>
    struct GetSupers<TList> {
        using result = TList;
    };
}