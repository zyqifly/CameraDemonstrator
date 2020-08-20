#pragma once
#include	"SDKImport.h"
#include	"CameraDescription.h"
#include	<mutex>
//��������Ĳ���
namespace CameraFactoryNS
{
	/// <summary>
	/// ����Ļ���
	/// </summary>
	class CAMERA_FACTORY_API	CameraBase
	{
	public:
		CameraBase();
		virtual	~CameraBase();
	public:
		/// <summary>
		/// ��������������ʵ��
		/// </summary>
		/// <returns></returns>
		virtual	bool				open() { return false; }
		/// <summary>
		/// �ر�������������ʵ��
		/// </summary>
		/// <returns></returns>
		virtual	bool				close() { return	false; };
		/// <summary>
		/// ��ȡ�������
		/// </summary>
		/// <returns></returns>
		inline	CameraAttribute&	cameraAttribute() { return _cameraAttribute; }
		/// <summary>
		/// ȡ���ͼƬ����
		/// </summary>
		/// <returns></returns>
		inline	ImageData&			imageData() { return	_imageData; }
		/// <summary>
		/// �����������
		/// </summary>
		/// <param name="cameraAttribute"></param>
		void	setCameraAttribute(CameraAttribute cameraAttribute);
		/// <summary>
		/// ��ӡ�������
		/// </summary>
		void	disPlayAttribute();
		/// <summary>
		/// ��ȡ��
		/// </summary>
		/// <returns></returns>
		inline	std::recursive_mutex& getDisplayMutex() { return	_displayMutex; }

	private:
		/// <summary>
		/// ���������
		/// </summary>
		CameraAttribute		_cameraAttribute;
		/// <summary>
		/// �洢���ݼ��ɣ�������ô��ʾ�����_cameraAttribute�еĳ������������ȥ����
		/// </summary>
		ImageData			_imageData;
		/// <summary>
		/// ������ԵĴ�ӡ��
		/// </summary>
		AttributeDisplayer	_attributeDisplayer;
		/// <summary>
		/// ������������дͼ�����ݺ���ʾ���⣬Ŀǰ���Բ��ã�ʹ��DisplayStatus�鿴�Ƿ�Ҫ��ʾ
		/// </summary>
		std::recursive_mutex			_displayMutex;
	};
}