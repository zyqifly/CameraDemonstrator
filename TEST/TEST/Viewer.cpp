#include	"Viewer.h"
using namespace CameraFactoryNS;
int	main()
{
	CameraFactory	factory;
	CameraAttribute	attribute;
	attribute.setCameraAttribute(CameraType::Camera_Type_Fotric_IRVision_GigE_Infrera, 640, 480, "192.168.1.115");
	factory.creatCamera(attribute);
	factory.open();
	system("cls");
	while (true)
	{
		disPlay(factory.camera());
	}
	factory.close();


	return	0;
}