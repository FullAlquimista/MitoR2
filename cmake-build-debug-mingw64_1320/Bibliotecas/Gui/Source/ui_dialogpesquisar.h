/********************************************************************************
** Form generated from reading the UI file 'dialogpesquisar.ui'
**
** Created by: CopperSpice User Interface Compiler, Version 1.8.2
**
** WARNING! Any changes made to this file will be lost when the UI file is recompiled
********************************************************************************/

#ifndef UI_DIALOGPESQUISAR_H
#define UI_DIALOGPESQUISAR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>

class Ui_DialogPesquisar
{
public:
    QVBoxLayout *verticalLayout;
    QTreeView *treeView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *DialogPesquisar)
    {
        if (DialogPesquisar->objectName().isEmpty())
            DialogPesquisar->setObjectName(QString::fromUtf8("DialogPesquisar"));
        DialogPesquisar->resize(580, 496);
        verticalLayout = new QVBoxLayout(DialogPesquisar);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeView = new QTreeView(DialogPesquisar);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout->addWidget(treeView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonOK = new QPushButton(DialogPesquisar);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));

        horizontalLayout->addWidget(pushButtonOK);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DialogPesquisar);

        QMetaObject::connectSlotsByName(DialogPesquisar);
    }  // setupUi

    void retranslateUi(QDialog *DialogPesquisar)
    {
        DialogPesquisar->setProperty("windowTitle", QVariant(QApplication::translate("DialogPesquisar", "Pesquisar...", nullptr)));
        pushButtonOK->setProperty("text", QVariant(QApplication::translate("DialogPesquisar", "OK", nullptr)));
    }  // retranslateUi

};

namespace Ui {
    class DialogPesquisar : public Ui_DialogPesquisar {};
}  // namespace Ui

#endif // UI_DIALOGPESQUISAR_H
