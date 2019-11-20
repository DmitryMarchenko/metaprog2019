#include <iostream>
#include "TypeList.h"
#include "AbstractFactoryGenerator.h"
#include "AbstractProduct.h"

int main() {

    using MyFactoryHierarchy = GetAbstractFactory<
            3, 5,
            TypeList<Chair, Table, Sofa>,
            TypeList<WoodenChair, WoodenTable, WoodenSofa>,
            TypeList<MetalChair, MetalTable, MetalSofa>,
            TypeList<MetalRichChair, MetalRichTable, MetalRichSofa>,
            TypeList<MetalPoorChair, MetalPoorTable, MetalPoorSofa>
    >;
    MyFactoryHierarchy::Factory* MyFactory = new MyFactoryHierarchy::GetConcreteFactory<MetalRichChair>::result;

    std::cout << std::endl << "Sofa generating:" << std::endl << std::endl;
    auto* sofa = MyFactory->Get<Sofa>();

    std::cout << std::endl << "Table generating:" << std::endl << std::endl;
    auto* table = MyFactory->Get<Table>();

    std::cout << std::endl << "Chair generating:" << std::endl << std::endl;
    auto* chair = MyFactory->Get<Chair>();

    return 0;
}