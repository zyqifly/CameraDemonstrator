#pragma once
#include	"SDKImport.h"
#include	"CameraTypeDefine.h"
#include	"EnumMapBase.h"
#include	<vector>
#include	<string>
#include	<map>
namespace  CameraFactoryNS
{
	/// <summary>
	/// 存储相机的描述信息
	/// </summary>
	class CAMERA_FACTORY_API CameraAttribute
	{
		int				_width;
		int				_height;
		bool			_openStatus;
		bool			_displayStatus;
		std::string		_SN;
		CameraType		_cameraType;
		int				_PixelByteNum;
		CameraProductor	_cameraProductor;
		CameraSeries	_cameraSerise;
		CameraInterface	_cameraInterface;
		CameraColour	_cameraColour;
	public:
		/// <summary>
		/// 两个构造函数，如果使用默认构造函数，则一定要执行setCameraAttribute
		/// </summary>
		/// <returns></returns>
		CameraAttribute();
		CameraAttribute(CameraType	type, int width, int height, std::string	sn);
		~CameraAttribute();
		bool	setCameraAttribute(CameraType	type, int width, int height,std::string	sn);
		bool	setWidth(int w);
		bool	setHeight(int h);
		inline	std::string		SN() { return	_SN; }
		inline	int				width() { return _width; }
		inline	int				height() { return _height; }
		inline	CameraType		getType() { return _cameraType; }
		inline	CameraProductor	getProductor() { return	_cameraProductor; }
		inline	CameraSeries	getSeries() { return _cameraSerise; }
		inline	CameraInterface	getInterface() { return _cameraInterface; }
		inline	CameraColour	getColour() { return _cameraColour; }
		inline	int				getPixelByteNum() { return _PixelByteNum; }
		inline	bool			isOpen() { return _openStatus; }
		inline	void			setOpenStatus(bool status) { _openStatus = status; }
		inline	bool			displayStatus() { return _displayStatus; }
		inline	void			setDisplayStatus(bool status) { _displayStatus = status; }
		
	private:

	};
	typedef	std::vector<unsigned char> ImageVector;
	/// <summary>
	/// 存储图片信息，以byte存储，显示时再按照图片尺寸、相互位数去解析，一般都给转成RGB三字节数据
	/// </summary>
	class CAMERA_FACTORY_API ImageData
	{
		ImageVector _data;
		ImageVector	_data_RGB;
	public:
		ImageVector& Data() { return _data; }
		ImageVector& Data_RGB(){ return	_data_RGB; }
		ImageData();
		~ImageData();
		bool	importData_Raw8(char* src, int	width, int height);
		bool	Raw8ToRGB();
	private:
	};
	/// <summary>
	/// 相机描述信息的打印机
	/// </summary>
	typedef	EnumMapBase<CameraProductor, std::string>		CameraProductorMap;
	typedef	EnumMapBase<CameraSeries, std::string>			CameraSeriesMap;
	typedef	EnumMapBase<CameraInterface, std::string>		CameraInterfaceMap;
	typedef	EnumMapBase<CameraColour, std::string>			CameraColourMap;
	typedef	EnumMapBase<CameraType, std::string>			CameraTypeMap;
	class CAMERA_FACTORY_API	AttributeDisplayer
	{
		CameraProductorMap		_CameraProductorMap;
		CameraSeriesMap			_CameraSeriesMap;
		CameraInterfaceMap		_CameraInterfaceMap;
		CameraColourMap			_CameraColourMap;
		CameraTypeMap			_CameraTypeMap;
	public:
		AttributeDisplayer();
		~AttributeDisplayer();
		void	print(CameraAttribute attribute);
	};

	
}