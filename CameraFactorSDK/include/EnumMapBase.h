#pragma once
#include	<iostream>
#include	<map>
#include	<SDKImport.h>
/*
【1】本模板以Key的类型和Value的类型产生一个map
【2】将key和value使用insertPair()插入map,eg:（key,"key"）
【3】可以根据key值打印出value，value必须能cout
【4】也可以根据key值等到value，函数：ValueType	getValue(KeyType _key)
*/
namespace CameraFactoryNS
{
	template	<class KeyType, class ValueType>
	class CAMERA_FACTORY_API	EnumMapBase
	{
		std::map<KeyType, ValueType> _data;
	public:
		EnumMapBase();
		~EnumMapBase();
		void	insertPair(KeyType _key, ValueType _value);
		void	print(KeyType _key, std::string _message);
		ValueType	getValue(KeyType _key);
	};
	template	<class KeyType, class ValueType>
	EnumMapBase<KeyType, ValueType>::EnumMapBase() :_data(std::map<KeyType, ValueType>())
	{

	}
	template	<class KeyType, class ValueType>
	EnumMapBase<KeyType, ValueType>::~EnumMapBase()
	{

	}
	template	<class KeyType, class ValueType>
	void	EnumMapBase<KeyType, ValueType> ::insertPair(KeyType _key, ValueType _value)
	{
		_data.insert(std::make_pair(_key, _value));
	}
	template	<class KeyType, class ValueType>
	void	EnumMapBase<KeyType, ValueType> ::print(KeyType _key, std::string _message)
	{
		auto _elem = _data.find(_key);
		if (_elem != _data.end())
		{
			std::cout << _message + ":" + _elem->second << std::endl;
		}
		else
		{
			std::cout << _message + ":" + "UNKNOWN" << std::endl;
		}
	}
	template	<class KeyType, class ValueType>
	ValueType	EnumMapBase<KeyType, ValueType> ::getValue(KeyType _key)
	{
		auto	_elem = _data.find(_key);
		if (_elem != _data.end())
		{
			return	_elem->second;
		}
		return	"UNKNOWN";
	}
}