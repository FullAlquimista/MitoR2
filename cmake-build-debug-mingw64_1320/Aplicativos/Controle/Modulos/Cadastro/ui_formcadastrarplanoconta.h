/********************************************************************************
** Form generated from reading the UI file 'formcadastrarplanoconta.ui'
**
** Created by: CopperSpice User Interface Compiler, Version 1.8.2
**
** WARNING! Any changes made to this file will be lost when the UI file is recompiled
********************************************************************************/

#ifndef UI_FORMCADASTRARPLANOCONTA_H
#define UI_FORMCADASTRARPLANOCONTA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_FormCadastrarPlanoConta
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QFrame *frameFormulario;
    QVBoxLayout *verticalLayout_7;
    QLabel *labelTituloFormulario;
    QHBoxLayout *horizontalLayoutBotoes;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonAdicionar;
    QPushButton *pushButtonSalvar;
    QPushButton *pushButtonRemover;
    QHBoxLayout *horizontalLayout;
    QFrame *frameInformacoesGerais;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButtonTituloInformacoesGerais;
    QTreeView *treeView;
    QFrame *subFrameInformaoesGerais;
    QGridLayout *gridLayout;

    void setupUi(QWidget *FormCadastrarPlanoConta)
    {
        if (FormCadastrarPlanoConta->objectName().isEmpty())
            FormCadastrarPlanoConta->setObjectName(QString::fromUtf8("FormCadastrarPlanoConta"));
        FormCadastrarPlanoConta->resize(752, 671);
        verticalLayout = new QVBoxLayout(FormCadastrarPlanoConta);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(FormCadastrarPlanoConta);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setProperty("widgetResizable", QVariant(true));
        scrollArea->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setProperty("geometry", QVariant(QRect(0, 0, 732, 651)));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frameFormulario = new QFrame(scrollAreaWidgetContents);
        frameFormulario->setObjectName(QString::fromUtf8("frameFormulario"));
        frameFormulario->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        frameFormulario->setProperty("frameShadow", QVariant(QFrame::Raised));
        frameFormulario->setProperty("styleSheet", QVariant(QString::fromUtf8("QFrame#frameFormulario\n"
"{\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 13px;\n"
"	border-top-right-radius: 13px;\n"
"	border-bottom-left-radius: 15px;\n"
"	border-bottom-right-radius: 15px;\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(170, 255, 255, 125), stop:0.55 rgb(214, 214, 214), stop:0.98 rgb(134, 134, 134), stop:1 rgba(0, 0, 0, 0));\n"
"}\n"
"\n"
"QFrame#frameInformacoesGerais\n"
"{\n"
"	border: 1px solid;\n"
"	border-top-left-radius: 18px;\n"
"	border-top-right-radius: 18px;\n"
"	border-bottom-left-radius: 15px;\n"
"	border-bottom-right-radius: 15px;\n"
"	background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"	border: 1px solid rgba(0, 0, 0, 85);\n"
"	border-radius: 8px;\n"
"	border-right: 2px solid rgba(0, 0, 0, 185);\n"
"	border-bottom: 2px solid rgba(0, 0, 0, 185);\n"
"  background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(35, 84, 156, 125), stop:1 rgba(58, 134, 255, 125));\n"
"  font-si"
                        "ze: 13px;\n"
"	height: 23px;\n"
"	width:65px;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	border: 1px solid rgba(0, 0, 0, 85);\n"
"	border-left: 2px solid rgba(91, 91, 91, 185);\n"
"	border-top: 2px solid rgba(91, 91, 91, 185);\n"
"\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(135, 184, 255, 125), stop:1 rgba(158, 234, 255, 125));\n"
"}\n"
"\n"
"QPushButton#pushButtonAdicionar\n"
"{\n"
"	border-top-left-radius: 8px;\n"
"	\n"
"}\n"
"\n"
"QPushButton#pushButtonSalvar\n"
"{\n"
"	width: 110px;\n"
"}\n"
"\n"
"QPushButton#pushButtonRemover\n"
"{\n"
"	border-top-right-radius: 8px;\n"
"\n"
"	\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(217, 5, 27), stop:1 rgb(253, 183, 186));\n"
"}\n"
"\n"
"\n"
"")));
        verticalLayout_7 = new QVBoxLayout(frameFormulario);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 3);
        labelTituloFormulario = new QLabel(frameFormulario);
        labelTituloFormulario->setObjectName(QString::fromUtf8("labelTituloFormulario"));
        labelTituloFormulario->setProperty("alignment", QVariant(Qt::AlignCenter));
        labelTituloFormulario->setProperty("styleSheet", QVariant(QString::fromUtf8("QLabel\n"
"{\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 10px;\n"
"	border-top-right-radius: 10px;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(59, 82, 131), stop:0.55 rgb(8, 122, 122), 																			stop:0.98 rgba(0, 0, 0, 255), stop:1 rgba(0, 0, 0, 0));\n"
"	padding: 5px 0px;\n"
"	color:rgb(255, 255, 255);\n"
"	max-height: 20px;\n"
"   font-size: 14px;\n"
"}\n"
"\n"
"")));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelTituloFormulario->sizePolicy().hasHeightForWidth());
        labelTituloFormulario->setProperty("sizePolicy", QVariant(sizePolicy));
        QFont font;
        labelTituloFormulario->setProperty("font", QVariant(font));

        verticalLayout_7->addWidget(labelTituloFormulario);

        horizontalLayoutBotoes = new QHBoxLayout();
        horizontalLayoutBotoes->setSpacing(2);
        horizontalLayoutBotoes->setObjectName(QString::fromUtf8("horizontalLayoutBotoes"));
        horizontalLayoutBotoes->setContentsMargins(-1, 6, -1, 6);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayoutBotoes->addItem(horizontalSpacer);

        pushButtonAdicionar = new QPushButton(frameFormulario);
        pushButtonAdicionar->setObjectName(QString::fromUtf8("pushButtonAdicionar"));
        pushButtonAdicionar->setProperty("styleSheet", QVariant(QString::fromUtf8("")));

        horizontalLayoutBotoes->addWidget(pushButtonAdicionar);

        pushButtonSalvar = new QPushButton(frameFormulario);
        pushButtonSalvar->setObjectName(QString::fromUtf8("pushButtonSalvar"));
        pushButtonSalvar->setProperty("styleSheet", QVariant(QString::fromUtf8("")));

        horizontalLayoutBotoes->addWidget(pushButtonSalvar);

        pushButtonRemover = new QPushButton(frameFormulario);
        pushButtonRemover->setObjectName(QString::fromUtf8("pushButtonRemover"));
        pushButtonRemover->setProperty("styleSheet", QVariant(QString::fromUtf8("QPushButton:hover\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(255, 85, 0), stop:1 rgba(255, 255, 255, 255));\n"
"\n"
"}\n"
"")));

        horizontalLayoutBotoes->addWidget(pushButtonRemover);


        verticalLayout_7->addLayout(horizontalLayoutBotoes);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(5, -1, 5, 15);
        frameInformacoesGerais = new QFrame(frameFormulario);
        frameInformacoesGerais->setObjectName(QString::fromUtf8("frameInformacoesGerais"));
        frameInformacoesGerais->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        frameInformacoesGerais->setProperty("frameShadow", QVariant(QFrame::Raised));
        frameInformacoesGerais->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        verticalLayout_4 = new QVBoxLayout(frameInformacoesGerais);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 15);
        pushButtonTituloInformacoesGerais = new QPushButton(frameInformacoesGerais);
        pushButtonTituloInformacoesGerais->setObjectName(QString::fromUtf8("pushButtonTituloInformacoesGerais"));
        pushButtonTituloInformacoesGerais->setProperty("styleSheet", QVariant(QString::fromUtf8("QPushButton\n"
"{\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 17px;\n"
"	border-top-right-radius: 17px;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(98, 98, 98), stop:1 rgb(211, 211, 211));\n"
"	padding: 5px 0px;\n"
"	padding: 5px 0px;\n"
"	max-height: 20px;\n"
"    font-size: 14px;\n"
"	border-bottom-right-radius:0px;\n"
"	border-bottom-left-radius:0px;\n"
"   color:rgb(255, 255, 255);\n"
"\n"
"}")));

        verticalLayout_4->addWidget(pushButtonTituloInformacoesGerais);

        treeView = new QTreeView(frameInformacoesGerais);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout_4->addWidget(treeView);

        subFrameInformaoesGerais = new QFrame(frameInformacoesGerais);
        subFrameInformaoesGerais->setObjectName(QString::fromUtf8("subFrameInformaoesGerais"));
        subFrameInformaoesGerais->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        subFrameInformaoesGerais->setProperty("frameShadow", QVariant(QFrame::Raised));
        gridLayout = new QGridLayout(subFrameInformaoesGerais);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(9, 9, 9, 9);

        verticalLayout_4->addWidget(subFrameInformaoesGerais);


        horizontalLayout->addWidget(frameInformacoesGerais);


        verticalLayout_7->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(frameFormulario);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(FormCadastrarPlanoConta);

        QMetaObject::connectSlotsByName(FormCadastrarPlanoConta);
    }  // setupUi

    void retranslateUi(QWidget *FormCadastrarPlanoConta)
    {
        FormCadastrarPlanoConta->setProperty("windowTitle", QVariant(QApplication::translate("FormCadastrarPlanoConta", "FormCadastrarPlanoConta", nullptr)));
        labelTituloFormulario->setProperty("text", QVariant(QApplication::translate("FormCadastrarPlanoConta", "Formul\303\241rio para cadastrar um plano de conta", nullptr)));
        pushButtonAdicionar->setProperty("text", QVariant(QApplication::translate("FormCadastrarPlanoConta", "Adicionar", nullptr)));
        pushButtonSalvar->setProperty("text", QVariant(QApplication::translate("FormCadastrarPlanoConta", "Salvar altera\303\247\303\265es", nullptr)));
        pushButtonRemover->setProperty("text", QVariant(QApplication::translate("FormCadastrarPlanoConta", "Remover", nullptr)));
        pushButtonTituloInformacoesGerais->setProperty("text", QVariant(QApplication::translate("FormCadastrarPlanoConta", "Informa\303\247\303\265es gerais", nullptr)));
    }  // retranslateUi

};

namespace Ui {
    class FormCadastrarPlanoConta : public Ui_FormCadastrarPlanoConta {};
}  // namespace Ui

#endif // UI_FORMCADASTRARPLANOCONTA_H
