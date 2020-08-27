#include "demonstratorwidget.h"
#include "ui_demonstratorwidget.h"
/// <summary>
/// 根据给定的图片数据生成bmp图片
/// </summary>
/// <param name="img"></param>数据数组，一个像素为RGB三个字节
/// <param name="filename"></param>生成图片的名称
/// <param name="w"></param>图片宽度
/// <param name="h"></param>图片高度
void WriteBMP(unsigned	char* img, const char* filename, int w, int h)
{
    int l = (w * 3 + 3) / 4 * 4;
    int bmi[] = { l * h + 54,0,54,40,w,h,1 | 3 * 8 << 16,0,l * h,0,0,100,0 };
    FILE* fp = fopen(filename, "wb");
    fprintf(fp, "BM");
    fwrite(&bmi, 52, 1, fp);
    fwrite(img, 1, l * h, fp);
    fclose(fp);
}
DemonstratorWidget::DemonstratorWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DemonstratorWidget),_cameraFactory(CameraFactoryNS::CameraFactory())
{
    ui->setupUi(this);
    CameraFactoryNS::CameraAttribute    attribute;
    attribute.setCameraAttribute(CameraFactoryNS::CameraType::Camera_Type_Balser_ACA_GigE_Grey, 1920, 1200, "21783245");
    _cameraFactory.creatCamera(attribute);
    _cameraFactory.open();
    _refreshPictureTimer.start(1);
    connect(&_refreshPictureTimer, &QTimer::timeout, this, &DemonstratorWidget::displaySlot);
}

DemonstratorWidget::~DemonstratorWidget()
{
    _cameraFactory.close();
    delete ui;
}
void    DemonstratorWidget::displaySlot()
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
    //WriteBMP(data.data(), "picture.bmp", cameraAttribute.width(), cameraAttribute.height());
    QImage* img = new QImage(cameraAttribute.width(),cameraAttribute.height(),QImage::Format_BGR888);
    std::copy(data.begin(), data.end(), img->bits());
    QImage  temp = img->mirrored(false, true);
    /*QMatrix matrix;
    matrix.rotate(180.0);*/
    //temp.transformed(matrix, Qt::FastTransformation);
    ui->label->setPixmap(QPixmap::fromImage(temp));
    delete  img;
}
