#pragma once

#include "TypeList.h"

class EmptyType {};

template <typename TList, template <class> class Unit>
class GenScatterHierarchy;

template <template <class> class Unit>
class GenScatterHierarchy<TypeList<>, Unit> {};

template <typename AtomicType, template <class> class Unit>
class GenScatterHierarchy : public Unit<AtomicType> {
public:
    using LeftBase = Unit<AtomicType>;
};

template <typename Head, typename... Tail, template <class> class Unit>
class GenScatterHierarchy<TypeList<Head, Tail...>, Unit> :
public GenScatterHierarchy<Head, Unit>,
public GenScatterHierarchy<TypeList<Tail...>, Unit> {
    public:
        using TList = TypeList<Head, Tail...>;
        using LeftBase = GenScatterHierarchy<Head, Unit>;
        using RightBase = GenScatterHierarchy<TypeList<Tail...>, Unit>;
};

template <typename TList, template <class AtomicType, class Base> class Unit, typename Root = EmptyType>
class GenLinearHierarchy;

template <typename T, template <class, class> class Unit, typename Root>
class GenLinearHierarchy<TypeList<T>, Unit, Root> : public Unit<T, Root> {};

template <typename Head, typename Head2, typename... Tail, template <class, class> class Unit, typename Root>
class GenLinearHierarchy<TypeList<Head, Head2, Tail...>, Unit, Root>
: public Unit<Head, GenLinearHierarchy<TypeList<Head2, Tail...>, Unit, Root>> {};
