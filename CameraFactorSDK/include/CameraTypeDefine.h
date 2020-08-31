#pragma once
namespace CameraFactoryNS
{
	/*
	����������ҡ�ϵ�С��������ӿڡ���ɫ���ͽ�����һЩenum class
	���ݲ�ͬ�ĳ��ҡ�ϵ�С��������ӿڡ���ɫ����������������͵�enum class CameraType
	*/
	typedef	unsigned int	CameraEnumTypeDefine;
	enum class CAMERA_FACTORY_API CameraProductor :CameraEnumTypeDefine
	{
		Default = 0x00,
		Hikvision = 0x01,
		Fotric = 0x02,
		Balser = 0x03,
		Do3Think = 0x04,
		DaHeng = 0x04, 
		Check = 0xff
		//TODO:third,���ӳ��ҵ�Enum

	};
	enum class CAMERA_FACTORY_API CameraSeries :CameraEnumTypeDefine
	{
		Default = 0x00 << 8,
		IRVision = 0x01 << 8,
		XF = 0x02 << 8,
		ACA = 0x03 << 8,
		M2s = 0x04 << 8,
		MER = 0x05,
		Check = 0xff << 8
		//TODO:fourth,���ӳ������ϵ�е�Enum
	};
	enum class CAMERA_FACTORY_API CameraInterface :CameraEnumTypeDefine
	{
		Default = 0x00 << 16,
		USB2 = 0x01 << 16,
		USB3 = 0x02 << 16,
		GigE = 0x03 << 16,
		_10GigE = 0x04 << 16,
		Check = 0xff
	};
	enum class CAMERA_FACTORY_API CameraColour :CameraEnumTypeDefine
	{
		Default = 0x00 << 24,
		Grey = 0x01 << 24,
		RGB = 0x02 << 24,
		Infrare = 0x03 << 24,
		Check = 0xff
	};
	/// <summary>
	/// ����һ��32λ����������ͺ�,4�ֽ�
	/// </summary>
	enum class CAMERA_FACTORY_API CameraType :CameraEnumTypeDefine
	{
		Camera_Type_Default = 0x0000,
		Camera_Type_Hikvision_XF_GigE_Infrare = (int)CameraProductor::Hikvision | (int)CameraSeries::XF | (int)CameraInterface::GigE | (int)CameraColour::Infrare,
		Camera_Type_Fotric_IRVision_GigE_Infrera = (int)CameraProductor::Fotric | (int)CameraSeries::IRVision | (int)CameraInterface::GigE | (int)CameraColour::Infrare,
		Camera_Type_Balser_ACA_GigE_Grey = (int)CameraProductor::Balser | (int)CameraSeries::ACA | (int)CameraInterface::GigE | (int)CameraColour::Grey,
		Camera_Type_Do3Think_M2s_USB2_Grey = (int)CameraProductor::Do3Think|(int)CameraSeries::M2s|(int)CameraInterface::USB2|(int)CameraColour::Grey,
		Camera_Type_DaHeng_MER_USB2_RGB =(int)CameraProductor::DaHeng|(int)CameraSeries::MER|(int)CameraInterface::USB2|(int)CameraColour::RGB
		//TODO:fifth,���������Enum
	};
}