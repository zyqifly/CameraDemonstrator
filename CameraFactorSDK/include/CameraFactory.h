// CameraFactory.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>
#include "SDKImport.h"
#include "CameraBase.h"
namespace CameraFactoryNS
{
	//相机工厂类，可以产生一个特定类型的相机，暂时不支持在本类中创建多个相机
	class CAMERA_FACTORY_API	CameraFactory
	{
	public:
		CameraFactory();
		~CameraFactory();
		/// <summary>
		/// 根据相机的描述信息创建一个相机
		/// </summary>
		/// <param name="attribute"></param>相机描述信息，有调用都提供
		/// <returns></returns>
		bool	creatCamera(CameraAttribute attribute);
		/*打开相机*/
		bool	open();
		/*关闭相机*/
		bool	close();
		/*销毁相机*/
		bool	destoryCamera();
		/*取出相机，供使用者使用，比如用相机里面的图片数据进行显示*/
		CameraBase* camera() { return	m_Camera; }
	private:
		CameraBase* m_Camera;
	};
	//可以使用此类创建一个指定型号的相机，而不使用上面的类
	CameraBase* createCameraByType(CameraType type);
	
}
// TODO: 在此处引用程序需要的其他标头。
