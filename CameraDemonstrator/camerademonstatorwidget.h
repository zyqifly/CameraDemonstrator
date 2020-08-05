#ifndef CAMERADEMONSTATORWIDGET_H
#define CAMERADEMONSTATORWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class CameraDemonstatorWidget; }
QT_END_NAMESPACE

class CameraDemonstatorWidget : public QWidget
{
    Q_OBJECT

public:
    CameraDemonstatorWidget(QWidget *parent = nullptr);
    ~CameraDemonstatorWidget();

private:
    Ui::CameraDemonstatorWidget *ui;
};
#endif // CAMERADEMONSTATORWIDGET_H
