/********************************************************************************
** Form generated from reading UI file 'demonstratorwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEMONSTRATORWIDGET_H
#define UI_DEMONSTRATORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DemonstratorWidget
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;

    void setupUi(QWidget *DemonstratorWidget)
    {
        if (DemonstratorWidget->objectName().isEmpty())
            DemonstratorWidget->setObjectName(QString::fromUtf8("DemonstratorWidget"));
        DemonstratorWidget->resize(800, 600);
        verticalLayout = new QVBoxLayout(DemonstratorWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(DemonstratorWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 780, 580));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(DemonstratorWidget);

        QMetaObject::connectSlotsByName(DemonstratorWidget);
    } // setupUi

    void retranslateUi(QWidget *DemonstratorWidget)
    {
        DemonstratorWidget->setWindowTitle(QCoreApplication::translate("DemonstratorWidget", "DemonstratorWidget", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DemonstratorWidget: public Ui_DemonstratorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMONSTRATORWIDGET_H
