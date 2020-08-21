#include "widget.h"

Widget::Widget(QWidget *parent)
	: QWidget(parent), _cameraFactory(CameraFactoryNS::CameraFactory())
{
	ui.setupUi(this);
	connect(ui.pushButton, &QPushButton::clicked, this,&Widget::openCamera);
}

Widget::~Widget()
{
	_cameraFactory.close();
}
void	Widget::openCamera()
{
	CameraFactoryNS::CameraAttribute    attribute;
	attribute.setCameraAttribute(CameraFactoryNS::CameraType::Camera_Type_Balser_ACA_GigE_Grey, 1920, 1200, "21783245");
	_cameraFactory.creatCamera(attribute);
	_cameraFactory.open();
	_refreshPictureTimer.start(1);
	connect(&_refreshPictureTimer, &QTimer::timeout, this, &Widget::displaySlot);
}
void    Widget::displaySlot()
{
	if (!_cameraFactory.camera()->cameraAttribute().displayStatus())
	{
		return;
	}
	_cameraFactory.camera()->cameraAttribute().setDisplayStatus(false);
	//[1]取出数据
	auto& data = _cameraFactory.camera()->imageData().Data();
	auto& cameraAttribute = _cameraFactory.camera()->cameraAttribute();
	int dataMinNum = cameraAttribute.height() * cameraAttribute.width() * cameraAttribute.getPixelByteNum();
	if (data.size() < dataMinNum)
	{
		return;
	}
	QImage* img = new QImage(cameraAttribute.width(), cameraAttribute.height(), QImage::Format_RGB888);
	std::copy(data.begin(), data.end(), img->bits());
	ui.label->setPixmap(QPixmap::fromImage(*img));
	delete  img;
}