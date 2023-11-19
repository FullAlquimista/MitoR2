/********************************************************************************
** Form generated from reading the UI file 'dialogsessao.ui'
**
** Created by: CopperSpice User Interface Compiler, Version 1.8.2
**
** WARNING! Any changes made to this file will be lost when the UI file is recompiled
********************************************************************************/

#ifndef UI_DIALOGSESSAO_H
#define UI_DIALOGSESSAO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

class Ui_DialogSessao
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_Usuario;
    QLineEdit *lineEditUsuario;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_Senha;
    QLineEdit *lineEditSenha;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_Acessar;
    QPushButton *pushButton_Cancelar;

    void setupUi(QDialog *DialogSessao)
    {
        if (DialogSessao->objectName().isEmpty())
            DialogSessao->setObjectName(QString::fromUtf8("DialogSessao"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogSessao->sizePolicy().hasHeightForWidth());
        DialogSessao->setProperty("sizePolicy", QVariant(sizePolicy));
        DialogSessao->resize(400, 150);
        verticalLayout_2 = new QVBoxLayout(DialogSessao);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_Usuario = new QLabel(DialogSessao);
        label_Usuario->setObjectName(QString::fromUtf8("label_Usuario"));

        horizontalLayout_2->addWidget(label_Usuario);

        lineEditUsuario = new QLineEdit(DialogSessao);
        lineEditUsuario->setObjectName(QString::fromUtf8("lineEditUsuario"));

        horizontalLayout_2->addWidget(lineEditUsuario);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_Senha = new QLabel(DialogSessao);
        label_Senha->setObjectName(QString::fromUtf8("label_Senha"));

        horizontalLayout_3->addWidget(label_Senha);

        lineEditSenha = new QLineEdit(DialogSessao);
        lineEditSenha->setObjectName(QString::fromUtf8("lineEditSenha"));
        lineEditSenha->setProperty("echoMode", QVariant(QLineEdit::PasswordEchoOnEdit));

        horizontalLayout_3->addWidget(lineEditSenha);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_Acessar = new QPushButton(DialogSessao);
        pushButton_Acessar->setObjectName(QString::fromUtf8("pushButton_Acessar"));

        horizontalLayout->addWidget(pushButton_Acessar);

        pushButton_Cancelar = new QPushButton(DialogSessao);
        pushButton_Cancelar->setObjectName(QString::fromUtf8("pushButton_Cancelar"));

        horizontalLayout->addWidget(pushButton_Cancelar);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(DialogSessao);

        QMetaObject::connectSlotsByName(DialogSessao);
    }  // setupUi

    void retranslateUi(QDialog *DialogSessao)
    {
        DialogSessao->setProperty("windowTitle", QVariant(QApplication::translate("DialogSessao", "Acessar sistema...", nullptr)));
        label_Usuario->setProperty("text", QVariant(QApplication::translate("DialogSessao", "Usu\303\241rio:", nullptr)));
        label_Senha->setProperty("text", QVariant(QApplication::translate("DialogSessao", "Senha:", nullptr)));
        pushButton_Acessar->setProperty("text", QVariant(QApplication::translate("DialogSessao", "Acessar", nullptr)));
        pushButton_Cancelar->setProperty("text", QVariant(QApplication::translate("DialogSessao", "Cancelar", nullptr)));
    }  // retranslateUi

};

namespace Ui {
    class DialogSessao : public Ui_DialogSessao {};
}  // namespace Ui

#endif // UI_DIALOGSESSAO_H
