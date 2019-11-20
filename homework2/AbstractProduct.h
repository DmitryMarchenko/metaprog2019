class AbstractProduct {
public:
    AbstractProduct() { std::cout << "AbstractProduct" << std::endl; }
};


class Chair : public AbstractProduct {
public:
    Chair() { std::cout << "Chair" << std::endl; }
};

class Table : public AbstractProduct {
public:
    Table() { std::cout << "Table" << std::endl; }
};

class Sofa : public AbstractProduct {
public:
    Sofa() { std::cout << "Sofa" << std::endl; }
};


class WoodenChair : public Chair {
public:
    WoodenChair() { std::cout << "WoodenChair" << std::endl; }
};

class WoodenTable : public Table {
public:
    WoodenTable() { std::cout << "WoodenTable" << std::endl; }
};

class WoodenSofa : public Sofa {
public:
    WoodenSofa() { std::cout << "WoodenSofa" << std::endl; }
};


class MetalChair : public Chair {
public:
    MetalChair() { std::cout << "MetalChair" << std::endl; }
};

class MetalTable : public Table {
public:
    MetalTable() { std::cout << "MetalTable" << std::endl; }
};

class MetalSofa : public Sofa {
public:
    MetalSofa() { std::cout << "MetalSofa" << std::endl; }
};


class MetalRichChair : public MetalChair {
public:
    MetalRichChair() { std::cout << "MetalRichChair" << std::endl; }
};

class MetalRichTable : public MetalTable {
public:
    MetalRichTable() { std::cout << "MetalRichTable" << std::endl; }
};

class MetalRichSofa : public MetalSofa {
public:
    MetalRichSofa() { std::cout << "MetalRichSofa" << std::endl; }
};


class MetalPoorChair : public MetalChair {
public:
    MetalPoorChair() { std::cout << "MetalPoorChair" << std::endl; }
};

class MetalPoorTable : public MetalTable {
public:
    MetalPoorTable() { std::cout << "MetalPoorTable" << std::endl; }
};

class MetalPoorSofa : public MetalSofa {
public:
    MetalPoorSofa() { std::cout << "MetalPoorSofa" << std::endl; }
};