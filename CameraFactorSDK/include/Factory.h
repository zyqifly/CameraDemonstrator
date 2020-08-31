#pragma once
#include    <iostream>
#include    <map>
//注意：基类不能有纯虚函数，因为要对子类进行注册，纯虚函数New不出来！！！
// 具体工厂类
// Product为抽象产品，ConcreteProduct为具体产品
template<typename Product, typename ConcreteProduct>
class ConcreteCreator
{
public:
    // 生产一个具体产品
    static Product* createProduct()
    {
        return new ConcreteProduct();//将子类指针给基类
    }
};
// 抽象工厂

// Product为抽象产品

template<typename Product>
class Creator
{
    // 单例实现
public:
    static Creator& Instance(std::string type)
    {
        static Creator<Product> instance;
        instance.registerCreator<Product>(type);//先把基类注册
        return instance;
    }
private:
    Creator() {}
    ~Creator() {}
    Creator(Creator&);
    // 对外接口
public:
    typedef Product* (*CreateProductDelegate)(); // 生产产品的函数委托
    typedef std::map<std::string, CreateProductDelegate> MapRegisterCreatorItem;
    // 根据具体产品生成具体工厂
    // 并将其注册进抽象工厂
    // ConcreteProduct为具体产品
    template<typename ConcreteProduct>
    void registerCreator(const std::string& _type)
    {
        //std::cout << "Concrete Product: " + _type + " has be registered!" << std::endl;
        mConcreteCreators[_type] = ConcreteCreator<Product, ConcreteProduct>::createProduct;
    }
    // 删除所有具体工厂
    void unregisterAllCreators()
    {
        mConcreteCreators.clear();
    }
    // 生产类型为_type的产品
    // 失败返回
    Product* createProduct(const std::string& _type)
    {
        MapRegisterCreatorItem::iterator type = mConcreteCreators.find(_type);
        if (type != mConcreteCreators.end())
        {
            CreateProductDelegate create = type->second;
            if (create != 0)
                return create();
        }
        return 0;
    }
private:
    MapRegisterCreatorItem mConcreteCreators; // 保存所有注册过的具体工厂
};