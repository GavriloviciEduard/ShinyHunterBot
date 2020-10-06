/********************************************************************************
** Form generated from reading UI file 'windowcontainer.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWCONTAINER_H
#define UI_WINDOWCONTAINER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowContainer
{
public:

    void setupUi(QWidget *WindowContainer)
    {
        if (WindowContainer->objectName().isEmpty())
            WindowContainer->setObjectName(QString::fromUtf8("WindowContainer"));
        WindowContainer->resize(681, 384);

        retranslateUi(WindowContainer);

        QMetaObject::connectSlotsByName(WindowContainer);
    } // setupUi

    void retranslateUi(QWidget *WindowContainer)
    {
        WindowContainer->setWindowTitle(QCoreApplication::translate("WindowContainer", "WindowContainer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowContainer: public Ui_WindowContainer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWCONTAINER_H
