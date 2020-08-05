#include "camerademonstatorwidget.h"
#include "ui_camerademonstatorwidget.h"

CameraDemonstatorWidget::CameraDemonstatorWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CameraDemonstatorWidget)
{
    ui->setupUi(this);
}

CameraDemonstatorWidget::~CameraDemonstatorWidget()
{
    delete ui;
}

