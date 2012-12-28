/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Fri 28. Dec 10:50:09 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *Fly_Button;
    QLabel *bestVal;
    QPushButton *Clear_Button;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(714, 644);
        Fly_Button = new QPushButton(Widget);
        Fly_Button->setObjectName(QString::fromUtf8("Fly_Button"));
        Fly_Button->setGeometry(QRect(0, 10, 75, 23));
        bestVal = new QLabel(Widget);
        bestVal->setObjectName(QString::fromUtf8("bestVal"));
        bestVal->setGeometry(QRect(100, 10, 271, 16));
        Clear_Button = new QPushButton(Widget);
        Clear_Button->setObjectName(QString::fromUtf8("Clear_Button"));
        Clear_Button->setGeometry(QRect(0, 40, 75, 23));

        retranslateUi(Widget);
        QObject::connect(Fly_Button, SIGNAL(clicked()), Widget, SLOT(flySwarm()));
        QObject::connect(Clear_Button, SIGNAL(clicked()), Widget, SLOT(clearAxes()));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        Fly_Button->setText(QApplication::translate("Widget", "Fly", 0, QApplication::UnicodeUTF8));
        bestVal->setText(QApplication::translate("Widget", "Prepare to SWARM!", 0, QApplication::UnicodeUTF8));
        Clear_Button->setText(QApplication::translate("Widget", "Clear", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
