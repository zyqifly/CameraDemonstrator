#pragma once
#include    <iostream>
#include    <map>
//ע�⣺���಻���д��麯������ΪҪ���������ע�ᣬ���麯��New������������
// ���幤����
// ProductΪ�����Ʒ��ConcreteProductΪ�����Ʒ
template<typename Product, typename ConcreteProduct>
class ConcreteCreator
{
public:
    // ����һ�������Ʒ
    static Product* createProduct()
    {
        return new ConcreteProduct();//������ָ�������
    }
};
// ���󹤳�

// ProductΪ�����Ʒ

template<typename Product>
class Creator
{
    // ����ʵ��
public:
    static Creator& Instance(std::string type)
    {
        static Creator<Product> instance;
        instance.registerCreator<Product>(type);//�Ȱѻ���ע��
        return instance;
    }
private:
    Creator() {}
    ~Creator() {}
    Creator(Creator&);
    // ����ӿ�
public:
    typedef Product* (*CreateProductDelegate)(); // ������Ʒ�ĺ���ί��
    typedef std::map<std::string, CreateProductDelegate> MapRegisterCreatorItem;
    // ���ݾ����Ʒ���ɾ��幤��
    // ������ע������󹤳�
    // ConcreteProductΪ�����Ʒ
    template<typename ConcreteProduct>
    void registerCreator(const std::string& _type)
    {
        //std::cout << "Concrete Product: " + _type + " has be registered!" << std::endl;
        mConcreteCreators[_type] = ConcreteCreator<Product, ConcreteProduct>::createProduct;
    }
    // ɾ�����о��幤��
    void unregisterAllCreators()
    {
        mConcreteCreators.clear();
    }
    // ��������Ϊ_type�Ĳ�Ʒ
    // ʧ�ܷ���
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
    MapRegisterCreatorItem mConcreteCreators; // ��������ע����ľ��幤��
};