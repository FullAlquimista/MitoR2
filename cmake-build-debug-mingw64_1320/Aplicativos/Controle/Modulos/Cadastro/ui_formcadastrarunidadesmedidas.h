/********************************************************************************
** Form generated from reading the UI file 'formcadastrarunidadesmedidas.ui'
**
** Created by: CopperSpice User Interface Compiler, Version 1.8.2
**
** WARNING! Any changes made to this file will be lost when the UI file is recompiled
********************************************************************************/

#ifndef UI_FORMCADASTRARUNIDADESMEDIDAS_H
#define UI_FORMCADASTRARUNIDADESMEDIDAS_H

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

class Ui_FormCadastrarUnidadesMedidas
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QFrame *frameFormulario;
    QVBoxLayout *verticalLayout_7;
    QLabel *labelTituloFormulario;
    QFrame *frameInformacoesGerais;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButtonTituloInformacoesGerais;
    QFrame *subFrameInformaoesGerais;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonAdicionarConversao;
    QPushButton *pushButtonGravarConversao;
    QPushButton *pushButtonExcluirConversao;
    QSpacerItem *horizontalSpacer_2;
    QTableView *tableView;
    QTableView *tableViewConversao;
    QLabel *labelConversao;
    QLabel *labelUnidadesMedidas;
    QHBoxLayout *horizontalLayoutBotoes;
    QPushButton *pushButtonAdicionar;
    QPushButton *pushButtonGravar;
    QPushButton *pushButtonExcluir;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *FormCadastrarUnidadesMedidas)
    {
        if (FormCadastrarUnidadesMedidas->objectName().isEmpty())
            FormCadastrarUnidadesMedidas->setObjectName(QString::fromUtf8("FormCadastrarUnidadesMedidas"));
        FormCadastrarUnidadesMedidas->resize(767, 590);
        verticalLayout = new QVBoxLayout(FormCadastrarUnidadesMedidas);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(FormCadastrarUnidadesMedidas);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setProperty("widgetResizable", QVariant(true));
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setProperty("geometry", QVariant(QRect(0, 0, 747, 570)));
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
"QPushButton#pushButtonExcluir\n"
""
                        "{\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(217, 5, 27), stop:1 rgb(253, 183, 186));\n"
"}\n"
"\n"
"QPushButton#pushButtonExcluir:hover\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(255, 85, 0), stop:1 rgba(255, 255, 255, 255));\n"
"}\n"
"\n"
"QPushButton#pushButtonExcluirConversao\n"
"{\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(217, 5, 27), stop:1 rgb(253, 183, 186));\n"
"}\n"
"\n"
"QPushButton#pushButtonExcluirConversao:hover\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(255, 85, 0), stop:1 rgba(255, 255, 255, 255));\n"
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
"	background-color: #55ffff;\n"
"	padding: 5px 0px;\n"
"	color: #000000;\n"
"	max-height: 25px;\n"
"    font-size: 14px;\n"
"}")));
        QFont font;
        labelTituloFormulario->setProperty("font", QVariant(font));

        verticalLayout_7->addWidget(labelTituloFormulario);

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
"	background-color: #859901;\n"
"	padding: 5px 0px;\n"
"	max-height: 25px;\n"
"   font-size: 14px;\n"
"}")));

        verticalLayout_4->addWidget(pushButtonTituloInformacoesGerais);

        subFrameInformaoesGerais = new QFrame(frameInformacoesGerais);
        subFrameInformaoesGerais->setObjectName(QString::fromUtf8("subFrameInformaoesGerais"));
        subFrameInformaoesGerais->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        subFrameInformaoesGerais->setProperty("frameShadow", QVariant(QFrame::Raised));
        gridLayout = new QGridLayout(subFrameInformaoesGerais);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(9, 9, 9, 9);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 6, -1, 6);
        pushButtonAdicionarConversao = new QPushButton(subFrameInformaoesGerais);
        pushButtonAdicionarConversao->setObjectName(QString::fromUtf8("pushButtonAdicionarConversao"));

        horizontalLayout->addWidget(pushButtonAdicionarConversao);

        pushButtonGravarConversao = new QPushButton(subFrameInformaoesGerais);
        pushButtonGravarConversao->setObjectName(QString::fromUtf8("pushButtonGravarConversao"));

        horizontalLayout->addWidget(pushButtonGravarConversao);

        pushButtonExcluirConversao = new QPushButton(subFrameInformaoesGerais);
        pushButtonExcluirConversao->setObjectName(QString::fromUtf8("pushButtonExcluirConversao"));

        horizontalLayout->addWidget(pushButtonExcluirConversao);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 6, 0, 1, 1);

        tableView = new QTableView(subFrameInformaoesGerais);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setProperty("styleSheet", QVariant(QString::fromUtf8("")));

        gridLayout->addWidget(tableView, 3, 0, 1, 1);

        tableViewConversao = new QTableView(subFrameInformaoesGerais);
        tableViewConversao->setObjectName(QString::fromUtf8("tableViewConversao"));

        gridLayout->addWidget(tableViewConversao, 7, 0, 1, 1);

        labelConversao = new QLabel(subFrameInformaoesGerais);
        labelConversao->setObjectName(QString::fromUtf8("labelConversao"));

        gridLayout->addWidget(labelConversao, 5, 0, 1, 1);

        labelUnidadesMedidas = new QLabel(subFrameInformaoesGerais);
        labelUnidadesMedidas->setObjectName(QString::fromUtf8("labelUnidadesMedidas"));

        gridLayout->addWidget(labelUnidadesMedidas, 1, 0, 1, 1);

        horizontalLayoutBotoes = new QHBoxLayout();
        horizontalLayoutBotoes->setSpacing(2);
        horizontalLayoutBotoes->setObjectName(QString::fromUtf8("horizontalLayoutBotoes"));
        horizontalLayoutBotoes->setContentsMargins(-1, 6, -1, 6);
        pushButtonAdicionar = new QPushButton(subFrameInformaoesGerais);
        pushButtonAdicionar->setObjectName(QString::fromUtf8("pushButtonAdicionar"));
        pushButtonAdicionar->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        pushButtonAdicionar->setProperty("minimumSize", QVariant(QSize(78, 25)));

        horizontalLayoutBotoes->addWidget(pushButtonAdicionar);

        pushButtonGravar = new QPushButton(subFrameInformaoesGerais);
        pushButtonGravar->setObjectName(QString::fromUtf8("pushButtonGravar"));
        pushButtonGravar->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        pushButtonGravar->setProperty("minimumSize", QVariant(QSize(78, 25)));

        horizontalLayoutBotoes->addWidget(pushButtonGravar);

        pushButtonExcluir = new QPushButton(subFrameInformaoesGerais);
        pushButtonExcluir->setObjectName(QString::fromUtf8("pushButtonExcluir"));
        pushButtonExcluir->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        pushButtonExcluir->setProperty("minimumSize", QVariant(QSize(80, 25)));

        horizontalLayoutBotoes->addWidget(pushButtonExcluir);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayoutBotoes->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayoutBotoes, 2, 0, 1, 1);


        verticalLayout_4->addWidget(subFrameInformaoesGerais);


        verticalLayout_7->addWidget(frameInformacoesGerais);


        verticalLayout_2->addWidget(frameFormulario);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(FormCadastrarUnidadesMedidas);

        QMetaObject::connectSlotsByName(FormCadastrarUnidadesMedidas);
    }  // setupUi

    void retranslateUi(QWidget *FormCadastrarUnidadesMedidas)
    {
        FormCadastrarUnidadesMedidas->setProperty("windowTitle", QVariant(QApplication::translate("FormCadastrarUnidadesMedidas", "FormCadastrarUnidadesMedidas", nullptr)));
        labelTituloFormulario->setProperty("text", QVariant(QApplication::translate("FormCadastrarUnidadesMedidas", "Formul\303\241rio para cadastrar unidades de medidas no sistema", nullptr)));
        pushButtonTituloInformacoesGerais->setProperty("text", QVariant(QApplication::translate("FormCadastrarUnidadesMedidas", "Informa\303\247\303\265es gerais", nullptr)));
        pushButtonAdicionarConversao->setProperty("text", QVariant(QApplication::translate("FormCadastrarUnidadesMedidas", "Adicionar", nullptr)));
        pushButtonGravarConversao->setProperty("text", QVariant(QApplication::translate("FormCadastrarUnidadesMedidas", "Gravar", nullptr)));
        pushButtonExcluirConversao->setProperty("text", QVariant(QApplication::translate("FormCadastrarUnidadesMedidas", "Excluir", nullptr)));
        labelConversao->setProperty("text", QVariant(QApplication::translate("FormCadastrarUnidadesMedidas", "Convers\303\243o entre as medidas:", nullptr)));
        labelUnidadesMedidas->setProperty("text", QVariant(QApplication::translate("FormCadastrarUnidadesMedidas", "Unidades de medidas:", nullptr)));
        pushButtonAdicionar->setProperty("text", QVariant(QApplication::translate("FormCadastrarUnidadesMedidas", "Adicionar", nullptr)));
        pushButtonGravar->setProperty("text", QVariant(QApplication::translate("FormCadastrarUnidadesMedidas", "Gravar", nullptr)));
        pushButtonExcluir->setProperty("text", QVariant(QApplication::translate("FormCadastrarUnidadesMedidas", "Excluir", nullptr)));
    }  // retranslateUi

};

namespace Ui {
    class FormCadastrarUnidadesMedidas : public Ui_FormCadastrarUnidadesMedidas {};
}  // namespace Ui

#endif // UI_FORMCADASTRARUNIDADESMEDIDAS_H
