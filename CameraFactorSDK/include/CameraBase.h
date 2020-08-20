#pragma once
#include	"SDKImport.h"
#include	"CameraDescription.h"
#include	<mutex>
//定义相机的操作
namespace CameraFactoryNS
{
	/// <summary>
	/// 相机的基类
	/// </summary>
	class CAMERA_FACTORY_API	CameraBase
	{
	public:
		CameraBase();
		virtual	~CameraBase();
	public:
		/// <summary>
		/// 打开相机，子类必需实现
		/// </summary>
		/// <returns></returns>
		virtual	bool				open() { return false; }
		/// <summary>
		/// 关闭相机，子类必需实现
		/// </summary>
		/// <returns></returns>
		virtual	bool				close() { return	false; };
		/// <summary>
		/// 提取相机属性
		/// </summary>
		/// <returns></returns>
		inline	CameraAttribute&	cameraAttribute() { return _cameraAttribute; }
		/// <summary>
		/// 取相机图片数据
		/// </summary>
		/// <returns></returns>
		inline	ImageData&			imageData() { return	_imageData; }
		/// <summary>
		/// 设置相机属性
		/// </summary>
		/// <param name="cameraAttribute"></param>
		void	setCameraAttribute(CameraAttribute cameraAttribute);
		/// <summary>
		/// 打印相机属性
		/// </summary>
		void	disPlayAttribute();
		/// <summary>
		/// 提取锁
		/// </summary>
		/// <returns></returns>
		inline	std::recursive_mutex& getDisplayMutex() { return	_displayMutex; }

	private:
		/// <summary>
		/// 相机的描述
		/// </summary>
		CameraAttribute		_cameraAttribute;
		/// <summary>
		/// 存储数据即可，数据怎么显示，结合_cameraAttribute中的长宽和数据类型去解析
		/// </summary>
		ImageData			_imageData;
		/// <summary>
		/// 相机属性的打印机
		/// </summary>
		AttributeDisplayer	_attributeDisplayer;
		/// <summary>
		/// 这个锁，管理读写图像数据和显示互斥，目前可以不用，使用DisplayStatus查看是否要显示
		/// </summary>
		std::recursive_mutex			_displayMutex;
	};
}