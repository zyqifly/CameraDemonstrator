#ifndef DEMONSTRATORWIDGET_H
#define DEMONSTRATORWIDGET_H

#include <QWidget>
#include <qtimer.h>
#include    "CameraFactory.h"
QT_BEGIN_NAMESPACE
namespace Ui { class DemonstratorWidget; }
QT_END_NAMESPACE

class DemonstratorWidget : public QWidget
{
    Q_OBJECT

public:
    DemonstratorWidget(QWidget *parent = nullptr);
    ~DemonstratorWidget();
public  slots:
    void    displaySlot();

private:
    Ui::DemonstratorWidget *ui;
    CameraFactoryNS::CameraFactory  _cameraFactory;
    QTimer  _refreshPictureTimer;
};
#endif // DEMONSTRATORWIDGET_H
