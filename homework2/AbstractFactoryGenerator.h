#include "HierarchyGenerators.h"

template <typename T>
class AbstractFactoryUnit {
public:
    virtual T* DoCreate(Type2Type<T>) = 0;
    virtual ~AbstractFactoryUnit() = default;
};

template <typename TList, template <class> class Unit = AbstractFactoryUnit>
class AbstractFactory : public GenScatterHierarchy<TList, Unit> {
public:
    using ProductList = TList;

    template <typename T>
    T* Get() {
        Unit<T>& unit = *this;
        return unit.DoCreate(Type2Type<T>());
    }
};

template <class ConcreteProduct, class Base>
class ConcreteFactoryUnit : public Base {
    using BaseProductList = typename Base::ProductList;
protected:
    using ProductList = typename TL::GetTail<BaseProductList>::result;
public:
    using AbstractProduct = typename TL::TypeAt<BaseProductList, 0>::result;
    ConcreteProduct* DoCreate(Type2Type<AbstractProduct>) {
        return new ConcreteProduct;
    }
};

template <typename AbstractFact, template <class, class> class Creator = ConcreteFactoryUnit,
        typename TList = typename AbstractFact::ProductList>
class ConcreteFactory : public GenLinearHierarchy<typename TL::Reverse<TList>::result, Creator, AbstractFact> {
public:
    using ProductList = typename AbstractFact::ProductList;
    using ConcreteProductList = TList;
};

template <size_t N, size_t M, typename... TLists>
class GetAbstractFactory {
    using BaseTypes = typename TL::GetSupers<TLists...>::result;
public:
    using Factory = AbstractFactory<BaseTypes>;

    template <typename T>
    class GetConcreteFactory {
        using CorrespondingList = typename TL::ListWithType<TypeList<TLists...>, T>::result;
    public:
        using result = ConcreteFactory<Factory, ConcreteFactoryUnit, CorrespondingList>;
    };
};