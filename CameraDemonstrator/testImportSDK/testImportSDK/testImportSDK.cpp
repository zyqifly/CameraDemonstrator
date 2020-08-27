// testImportSDK.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "CameraFactory.h"
using namespace CameraFactoryNS;
#include	"windows.h"
#include	<mutex>
#include <thread>
using namespace CameraFactoryNS;
/// <summary>
/// ���ݸ�����ͼƬ��������bmpͼƬ
/// </summary>
/// <param name="img"></param>�������飬һ������ΪRGB�����ֽ�
/// <param name="filename"></param>����ͼƬ������
/// <param name="w"></param>ͼƬ���
/// <param name="h"></param>ͼƬ�߶�
void WriteBMP(unsigned	char* img, const char* filename, int w, int h)
{
	int l = (w * 3 + 3) / 4 * 4;
	int bmi[] = { l * h + 54, 0, 54, 40, w, h, 1 | 3 * 8 << 16, 0, l * h, 0, 0, 100, 0 };
	FILE* fp /*= fopen_s(filename, "wb")*/;
	fopen_s(&fp, filename, "w");
	fprintf(fp, "BM");
	fwrite(&bmi, 52, 1, fp);
	fwrite(img, 1, l * h, fp);
	fclose(fp);
}
/// <summary>
/// ��ʾ������������е�ͼƬ��ʾ������̨
/// </summary>
/// <param name="m_Camera"></param>
void	disPlay(CameraBase*	m_Camera)
{
	if (m_Camera == nullptr)
	{
		return;
	}
	if (!m_Camera->cameraAttribute().displayStatus())
	{
		return;
	}
	m_Camera->cameraAttribute().setDisplayStatus(false);//�����־λ��Ҫ��Ȼһ��ͼƬ��ͣ��ˢ�¡�
	std::recursive_mutex& mutex = m_Camera->getDisplayMutex();
	std::lock_guard<std::recursive_mutex> lg(mutex);
	//std::cout << "display tid:" << GetCurrentThreadId() <<"  pid:"<< GetCurrentProcessId() << std::endl;
	//[1]ȡ������
	ImageVector& data = m_Camera->imageData().Data();
	int dataMinNum = m_Camera->cameraAttribute().width() * m_Camera->cameraAttribute().height() * m_Camera->cameraAttribute().getPixelByteNum();
	if (data.size() < dataMinNum)
	{
		return;
	}
	HWND hwnd;
	HDC hdc;
	//��ȡconsole���豸�����ľ��
	hwnd = GetConsoleWindow();
	hdc = GetDC(hwnd);
	WriteBMP(data.data(), "picture.bmp", m_Camera->cameraAttribute().width(), m_Camera->cameraAttribute().height());
	HBITMAP hBitmap;
	hBitmap = (HBITMAP)LoadImage(NULL, L"picture.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	HDC cmdmem = CreateCompatibleDC(hdc);
	SelectObject(cmdmem, hBitmap);
	BitBlt(hdc, 0, 0, m_Camera->cameraAttribute().width(), m_Camera->cameraAttribute().height(), cmdmem, 0, 0, SRCCOPY);
}
void	displayInThread(void* camera)
{
	if (camera == nullptr)
	{
		return;
	}
	CameraBase* pCam = (CameraBase*)camera;
	while (pCam->cameraAttribute().isOpen())
	{
		disPlay(pCam);
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	CameraFactory	factory;
	CameraAttribute	attribute;
	//attribute.setCameraAttribute(CameraType::Camera_Type_Fotric_IRVision_GigE_Infrera, 640, 480, "192.168.1.115");
	attribute.setCameraAttribute(CameraType::Camera_Type_Balser_ACA_GigE_Grey, 1920, 1200, "21783245");
	factory.creatCamera(attribute);
	factory.open();
	//system("cls");
	std::thread	t(displayInThread, factory.camera());
	getchar();
	factory.close();
	t.join();
	return 0;
}

