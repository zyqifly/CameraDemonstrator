#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>
#include <qtimer.h>
#include "ui_widget.h"
#include "CameraFactory.h"

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = 0);
	~Widget();
public  slots:
	void    displaySlot();
	void	openCamera();

private:
	Ui::WidgetClass ui;
	CameraFactoryNS::CameraFactory  _cameraFactory;
	QTimer  _refreshPictureTimer;
};

#endif // WIDGET_H
