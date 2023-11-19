/********************************************************************************
** Form generated from reading the UI file 'dialogpesquisararvore.ui'
**
** Created by: CopperSpice User Interface Compiler, Version 1.8.2
**
** WARNING! Any changes made to this file will be lost when the UI file is recompiled
********************************************************************************/

#ifndef UI_DIALOGPESQUISARARVORE_H
#define UI_DIALOGPESQUISARARVORE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_DialogPesquisarCT
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *framePesquisa;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pushButtonTituloPesquisa;
    QFrame *subFrameDiretivas;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonOk;
    QTreeView *treeView;

    void setupUi(QWidget *DialogPesquisarCT)
    {
        if (DialogPesquisarCT->objectName().isEmpty())
            DialogPesquisarCT->setObjectName(QString::fromUtf8("DialogPesquisarCT"));
        DialogPesquisarCT->resize(838, 576);
        verticalLayout = new QVBoxLayout(DialogPesquisarCT);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        framePesquisa = new QFrame(DialogPesquisarCT);
        framePesquisa->setObjectName(QString::fromUtf8("framePesquisa"));
        framePesquisa->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        framePesquisa->setProperty("frameShadow", QVariant(QFrame::Raised));
        framePesquisa->setProperty("styleSheet", QVariant(QString::fromUtf8("QFrame#framePesquisa\n"
"{\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 18px;\n"
"	border-top-right-radius: 18px;\n"
"	border-bottom-left-radius: 15px;\n"
"	border-bottom-right-radius: 15px;\n"
"}")));
        verticalLayout_5 = new QVBoxLayout(framePesquisa);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 15);
        pushButtonTituloPesquisa = new QPushButton(framePesquisa);
        pushButtonTituloPesquisa->setObjectName(QString::fromUtf8("pushButtonTituloPesquisa"));
        pushButtonTituloPesquisa->setProperty("styleSheet", QVariant(QString::fromUtf8("QPushButton#pushButtonTituloPesquisa{\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 15px;\n"
"	border-top-right-radius: 15px;\n"
"	background-color: #c0c4ff;\n"
"	padding: 5px 0px;\n"
"	max-height: 25px;\n"
"   font-size: 14px;\n"
"}")));

        verticalLayout_5->addWidget(pushButtonTituloPesquisa);

        subFrameDiretivas = new QFrame(framePesquisa);
        subFrameDiretivas->setObjectName(QString::fromUtf8("subFrameDiretivas"));
        subFrameDiretivas->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        subFrameDiretivas->setProperty("frameShadow", QVariant(QFrame::Raised));
        gridLayout_2 = new QGridLayout(subFrameDiretivas);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(9, 9, 9, 9);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 6, -1, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonOk = new QPushButton(subFrameDiretivas);
        pushButtonOk->setObjectName(QString::fromUtf8("pushButtonOk"));

        horizontalLayout->addWidget(pushButtonOk);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        treeView = new QTreeView(subFrameDiretivas);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        gridLayout_2->addWidget(treeView, 0, 0, 1, 1);


        verticalLayout_5->addWidget(subFrameDiretivas);


        verticalLayout->addWidget(framePesquisa);


        retranslateUi(DialogPesquisarCT);

        QMetaObject::connectSlotsByName(DialogPesquisarCT);
    }  // setupUi

    void retranslateUi(QWidget *DialogPesquisarCT)
    {
        DialogPesquisarCT->setProperty("windowTitle", QVariant(QApplication::translate("DialogPesquisarCT", "DialogPesquisarCT", nullptr)));
        pushButtonTituloPesquisa->setProperty("text", QVariant(QApplication::translate("DialogPesquisarCT", "Pesuisa", nullptr)));
        pushButtonOk->setProperty("text", QVariant(QApplication::translate("DialogPesquisarCT", "OK", nullptr)));
    }  // retranslateUi

};

namespace Ui {
    class DialogPesquisarCT : public Ui_DialogPesquisarCT {};
}  // namespace Ui

#endif // UI_DIALOGPESQUISARARVORE_H
