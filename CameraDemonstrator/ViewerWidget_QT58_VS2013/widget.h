#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include    <QTimer>
#include    "CameraFactory.h"
using namespace CameraFactoryNS;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public  slots:
    void    displaySlot();

private:
    Ui::Widget *ui;
    CameraFactory  _cameraFactory;
    QTimer  _refreshPictureTimer;

};

#endif // WIDGET_H
