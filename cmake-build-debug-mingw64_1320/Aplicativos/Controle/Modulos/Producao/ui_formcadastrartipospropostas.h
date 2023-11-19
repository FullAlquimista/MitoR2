/********************************************************************************
** Form generated from reading the UI file 'formcadastrartipospropostas.ui'
**
** Created by: CopperSpice User Interface Compiler, Version 1.8.2
**
** WARNING! Any changes made to this file will be lost when the UI file is recompiled
********************************************************************************/

#ifndef UI_FORMCADASTRARTIPOSPROPOSTAS_H
#define UI_FORMCADASTRARTIPOSPROPOSTAS_H

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
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_FormCadastrarTiposPropostas
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
    QFrame *frameInformacoesGerais;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButtonTituloInformacoesGerais;
    QFrame *subFrameInformaoesGerais;
    QGridLayout *gridLayout;
    QTableView *tableView;

    void setupUi(QWidget *FormCadastrarTiposPropostas)
    {
        if (FormCadastrarTiposPropostas->objectName().isEmpty())
            FormCadastrarTiposPropostas->setObjectName(QString::fromUtf8("FormCadastrarTiposPropostas"));
        FormCadastrarTiposPropostas->resize(754, 447);
        verticalLayout = new QVBoxLayout(FormCadastrarTiposPropostas);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(FormCadastrarTiposPropostas);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setProperty("widgetResizable", QVariant(true));
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setProperty("geometry", QVariant(QRect(0, 0, 734, 427)));
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
"}\n"
"\n"
"QPushButton\n"
"{\n"
"	border: 1px solid rgba(0, 0, 0, 85);\n"
"	border-radius: 8px;\n"
"	border-right: 2px solid rgba(0, 0, 0, 185);\n"
"	border-bottom: 2px solid rgba(0, 0, 0, 185);\n"
"  background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(35, 84, 156, 125), stop:1 rgba(58, 134, 255, 125));\n"
"  font-size: 13px;\n"
"	height: 23px;\n"
"	width:65px\n"
"}\n"
"\n"
"QPushButton#pushButtonSalvar\n"
"{\n"
"	width:110px;\n"
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
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(135, 184, 255, 125), stop:1 rgba(158"
                        ", 234, 255, 125));\n"
"}\n"
"\n"
"\n"
"\n"
"QPushButton#pushButtonRemover  {\n"
"\n"
"\n"
"background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(217, 5, 27), stop:1 rgb(253, 183, 186));\n"
"\n"
"}\n"
"QPushButton#pushButtonRemover:hover {\n"
"    	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(255, 85, 0), stop:1 rgba(255, 255, 255, 255));   \n"
"}")));
        verticalLayout_7 = new QVBoxLayout(frameFormulario);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 15);
        labelTituloFormulario = new QLabel(frameFormulario);
        labelTituloFormulario->setObjectName(QString::fromUtf8("labelTituloFormulario"));
        labelTituloFormulario->setProperty("alignment", QVariant(Qt::AlignCenter));
        labelTituloFormulario->setProperty("styleSheet", QVariant(QString::fromUtf8("QLabel#labelTituloFormulario {\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 10px;\n"
"	border-top-right-radius: 10px;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(59, 82, 131), stop:0.55 rgb(8, 122, 122), stop:0.98 rgba(0, 0, 0, 255), stop:1 rgba(0, 0, 0, 0));\n"
"	padding: 5px 0px;\n"
"	color: rgb(255, 255, 255);\n"
"	max-height: 25px;\n"
"    font-size: 14px;\n"
"}")));
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

        horizontalLayoutBotoes->addWidget(pushButtonAdicionar);

        pushButtonSalvar = new QPushButton(frameFormulario);
        pushButtonSalvar->setObjectName(QString::fromUtf8("pushButtonSalvar"));

        horizontalLayoutBotoes->addWidget(pushButtonSalvar);

        pushButtonRemover = new QPushButton(frameFormulario);
        pushButtonRemover->setObjectName(QString::fromUtf8("pushButtonRemover"));

        horizontalLayoutBotoes->addWidget(pushButtonRemover);


        verticalLayout_7->addLayout(horizontalLayoutBotoes);

        frameInformacoesGerais = new QFrame(frameFormulario);
        frameInformacoesGerais->setObjectName(QString::fromUtf8("frameInformacoesGerais"));
        frameInformacoesGerais->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        frameInformacoesGerais->setProperty("frameShadow", QVariant(QFrame::Raised));
        frameInformacoesGerais->setProperty("styleSheet", QVariant(QString::fromUtf8("QFrame#frameInformacoesGerais\n"
"{\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 18px;\n"
"	border-top-right-radius: 18px;\n"
"	border-bottom-left-radius: 15px;\n"
"	border-bottom-right-radius: 15px;\n"
"}")));
        verticalLayout_4 = new QVBoxLayout(frameInformacoesGerais);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 15);
        pushButtonTituloInformacoesGerais = new QPushButton(frameInformacoesGerais);
        pushButtonTituloInformacoesGerais->setObjectName(QString::fromUtf8("pushButtonTituloInformacoesGerais"));
        pushButtonTituloInformacoesGerais->setProperty("styleSheet", QVariant(QString::fromUtf8("QPushButton#pushButtonTituloInformacoesGerais {\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 15px;\n"
"	border-top-right-radius: 15px;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(98, 98, 98), stop:1 rgb(211, 211, 211));\n"
"	padding: 5px 0px;\n"
"	height: 22px;\n"
"   font-size: 14px;\n"
"border-bottom-left-radius: 0px;\n"
"	border-bottom-right-radius: 0px;\n"
"}")));

        verticalLayout_4->addWidget(pushButtonTituloInformacoesGerais);

        subFrameInformaoesGerais = new QFrame(frameInformacoesGerais);
        subFrameInformaoesGerais->setObjectName(QString::fromUtf8("subFrameInformaoesGerais"));
        subFrameInformaoesGerais->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        subFrameInformaoesGerais->setProperty("frameShadow", QVariant(QFrame::Raised));
        gridLayout = new QGridLayout(subFrameInformaoesGerais);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(9, 9, 9, 9);
        tableView = new QTableView(subFrameInformaoesGerais);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout->addWidget(tableView, 0, 0, 1, 1);


        verticalLayout_4->addWidget(subFrameInformaoesGerais);


        verticalLayout_7->addWidget(frameInformacoesGerais);


        verticalLayout_2->addWidget(frameFormulario);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(FormCadastrarTiposPropostas);

        QMetaObject::connectSlotsByName(FormCadastrarTiposPropostas);
    }  // setupUi

    void retranslateUi(QWidget *FormCadastrarTiposPropostas)
    {
        FormCadastrarTiposPropostas->setProperty("windowTitle", QVariant(QApplication::translate("FormCadastrarTiposPropostas", "FormCadastrarTiposMateriais", nullptr)));
        labelTituloFormulario->setProperty("text", QVariant(QApplication::translate("FormCadastrarTiposPropostas", "Formul\303\241rio para cadastrar tipos de propostas de or\303\247amento", nullptr)));
        pushButtonAdicionar->setProperty("text", QVariant(QApplication::translate("FormCadastrarTiposPropostas", "Adicionar", nullptr)));
        pushButtonSalvar->setProperty("text", QVariant(QApplication::translate("FormCadastrarTiposPropostas", "Salvar altera\303\247\303\265es", nullptr)));
        pushButtonRemover->setProperty("text", QVariant(QApplication::translate("FormCadastrarTiposPropostas", "Remover", nullptr)));
        pushButtonTituloInformacoesGerais->setProperty("text", QVariant(QApplication::translate("FormCadastrarTiposPropostas", "Informa\303\247\303\265es gerais", nullptr)));
    }  // retranslateUi

};

namespace Ui {
    class FormCadastrarTiposPropostas : public Ui_FormCadastrarTiposPropostas {};
}  // namespace Ui

#endif // UI_FORMCADASTRARTIPOSPROPOSTAS_H
