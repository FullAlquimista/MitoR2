/********************************************************************************
** Form generated from reading the UI file 'formgerenciarusuarios.ui'
**
** Created by: CopperSpice User Interface Compiler, Version 1.8.2
**
** WARNING! Any changes made to this file will be lost when the UI file is recompiled
********************************************************************************/

#ifndef UI_FORMGERENCIARUSUARIOS_H
#define UI_FORMGERENCIARUSUARIOS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_FormGerenciarUsuarios
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frameFormulario;
    QVBoxLayout *verticalLayout_7;
    QLabel *labelTituloFormulario;
    QHBoxLayout *horizontalLayoutBotoes;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonLimpar;
    QPushButton *pushButtonNovo;
    QPushButton *pushButtonSalvar;
    QPushButton *pushButtonPesquisar;
    QPushButton *pushButtonRemover;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QFrame *frameInformacoesGerais;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButtonTituloInformacoesGerais;
    QFrame *subFrameInformaoesGerais;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelSenha;
    QLineEdit *lineEditSenha;
    QLabel *labelConfirmarSenha;
    QLineEdit *lineEditConfirmarSenha;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayoutUsuario;
    QLabel *labelUsuario;
    QLineEdit *lineEditUsuario;
    QLabel *labelPrevilegio;
    QComboBox *comboBoxPrevilegio;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frameDiretivas;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pushButtonTituloDiretivas;
    QFrame *subFrameDiretivas;
    QGridLayout *gridLayout_2;
    QTreeView *treeViewDiretivas;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButtonAtualizar;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QWidget *FormGerenciarUsuarios)
    {
        if (FormGerenciarUsuarios->objectName().isEmpty())
            FormGerenciarUsuarios->setObjectName(QString::fromUtf8("FormGerenciarUsuarios"));
        FormGerenciarUsuarios->resize(775, 745);
        verticalLayout = new QVBoxLayout(FormGerenciarUsuarios);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frameFormulario = new QFrame(FormGerenciarUsuarios);
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
"	background-color: #c6c600;\n"
"	padding: 5px 0px;\n"
"	color: #000000;\n"
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

        pushButtonLimpar = new QPushButton(frameFormulario);
        pushButtonLimpar->setObjectName(QString::fromUtf8("pushButtonLimpar"));

        horizontalLayoutBotoes->addWidget(pushButtonLimpar);

        pushButtonNovo = new QPushButton(frameFormulario);
        pushButtonNovo->setObjectName(QString::fromUtf8("pushButtonNovo"));

        horizontalLayoutBotoes->addWidget(pushButtonNovo);

        pushButtonSalvar = new QPushButton(frameFormulario);
        pushButtonSalvar->setObjectName(QString::fromUtf8("pushButtonSalvar"));

        horizontalLayoutBotoes->addWidget(pushButtonSalvar);

        pushButtonPesquisar = new QPushButton(frameFormulario);
        pushButtonPesquisar->setObjectName(QString::fromUtf8("pushButtonPesquisar"));

        horizontalLayoutBotoes->addWidget(pushButtonPesquisar);

        pushButtonRemover = new QPushButton(frameFormulario);
        pushButtonRemover->setObjectName(QString::fromUtf8("pushButtonRemover"));

        horizontalLayoutBotoes->addWidget(pushButtonRemover);


        verticalLayout_7->addLayout(horizontalLayoutBotoes);

        scrollArea = new QScrollArea(frameFormulario);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setProperty("widgetResizable", QVariant(true));
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setProperty("geometry", QVariant(QRect(0, 0, 745, 607)));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frameInformacoesGerais = new QFrame(scrollAreaWidgetContents);
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
        horizontalLayout->setContentsMargins(-1, 6, -1, -1);
        labelSenha = new QLabel(subFrameInformaoesGerais);
        labelSenha->setObjectName(QString::fromUtf8("labelSenha"));
        labelSenha->setProperty("alignment", QVariant(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter));
        labelSenha->setProperty("minimumSize", QVariant(QSize(45, 0)));

        horizontalLayout->addWidget(labelSenha);

        lineEditSenha = new QLineEdit(subFrameInformaoesGerais);
        lineEditSenha->setObjectName(QString::fromUtf8("lineEditSenha"));
        lineEditSenha->setProperty("echoMode", QVariant(QLineEdit::Password));
        lineEditSenha->setProperty("maximumSize", QVariant(QSize(240, 16777215)));

        horizontalLayout->addWidget(lineEditSenha);

        labelConfirmarSenha = new QLabel(subFrameInformaoesGerais);
        labelConfirmarSenha->setObjectName(QString::fromUtf8("labelConfirmarSenha"));

        horizontalLayout->addWidget(labelConfirmarSenha);

        lineEditConfirmarSenha = new QLineEdit(subFrameInformaoesGerais);
        lineEditConfirmarSenha->setObjectName(QString::fromUtf8("lineEditConfirmarSenha"));
        lineEditConfirmarSenha->setProperty("echoMode", QVariant(QLineEdit::Password));
        lineEditConfirmarSenha->setProperty("maximumSize", QVariant(QSize(240, 16777215)));

        horizontalLayout->addWidget(lineEditConfirmarSenha);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayoutUsuario = new QHBoxLayout();
        horizontalLayoutUsuario->setObjectName(QString::fromUtf8("horizontalLayoutUsuario"));
        horizontalLayoutUsuario->setContentsMargins(-1, 6, -1, -1);
        labelUsuario = new QLabel(subFrameInformaoesGerais);
        labelUsuario->setObjectName(QString::fromUtf8("labelUsuario"));
        labelUsuario->setProperty("alignment", QVariant(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter));
        labelUsuario->setProperty("minimumSize", QVariant(QSize(45, 0)));

        horizontalLayoutUsuario->addWidget(labelUsuario);

        lineEditUsuario = new QLineEdit(subFrameInformaoesGerais);
        lineEditUsuario->setObjectName(QString::fromUtf8("lineEditUsuario"));
        lineEditUsuario->setProperty("maximumSize", QVariant(QSize(240, 16777215)));

        horizontalLayoutUsuario->addWidget(lineEditUsuario);

        labelPrevilegio = new QLabel(subFrameInformaoesGerais);
        labelPrevilegio->setObjectName(QString::fromUtf8("labelPrevilegio"));

        horizontalLayoutUsuario->addWidget(labelPrevilegio);

        comboBoxPrevilegio = new QComboBox(subFrameInformaoesGerais);
        comboBoxPrevilegio->setObjectName(QString::fromUtf8("comboBoxPrevilegio"));

        horizontalLayoutUsuario->addWidget(comboBoxPrevilegio);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayoutUsuario->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayoutUsuario, 0, 0, 1, 1);


        verticalLayout_4->addWidget(subFrameInformaoesGerais);


        verticalLayout_2->addWidget(frameInformacoesGerais);

        frameDiretivas = new QFrame(scrollAreaWidgetContents);
        frameDiretivas->setObjectName(QString::fromUtf8("frameDiretivas"));
        frameDiretivas->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        frameDiretivas->setProperty("frameShadow", QVariant(QFrame::Raised));
        frameDiretivas->setProperty("styleSheet", QVariant(QString::fromUtf8("QFrame#frameDiretivas\n"
"{\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 18px;\n"
"	border-top-right-radius: 18px;\n"
"	border-bottom-left-radius: 15px;\n"
"	border-bottom-right-radius: 15px;\n"
"}")));
        verticalLayout_5 = new QVBoxLayout(frameDiretivas);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 15);
        pushButtonTituloDiretivas = new QPushButton(frameDiretivas);
        pushButtonTituloDiretivas->setObjectName(QString::fromUtf8("pushButtonTituloDiretivas"));
        pushButtonTituloDiretivas->setProperty("styleSheet", QVariant(QString::fromUtf8("QPushButton#pushButtonTituloDiretivas {\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 15px;\n"
"	border-top-right-radius: 15px;\n"
"	background-color: #859901;\n"
"	padding: 5px 0px;\n"
"	max-height: 25px;\n"
"   font-size: 14px;\n"
"}")));

        verticalLayout_5->addWidget(pushButtonTituloDiretivas);

        subFrameDiretivas = new QFrame(frameDiretivas);
        subFrameDiretivas->setObjectName(QString::fromUtf8("subFrameDiretivas"));
        subFrameDiretivas->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        subFrameDiretivas->setProperty("frameShadow", QVariant(QFrame::Raised));
        gridLayout_2 = new QGridLayout(subFrameDiretivas);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(9, 9, 9, 9);
        treeViewDiretivas = new QTreeView(subFrameDiretivas);
        treeViewDiretivas->setObjectName(QString::fromUtf8("treeViewDiretivas"));

        gridLayout_2->addWidget(treeViewDiretivas, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 6, -1, 6);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        pushButtonAtualizar = new QPushButton(subFrameDiretivas);
        pushButtonAtualizar->setObjectName(QString::fromUtf8("pushButtonAtualizar"));

        horizontalLayout_2->addWidget(pushButtonAtualizar);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);


        verticalLayout_5->addWidget(subFrameDiretivas);


        verticalLayout_2->addWidget(frameDiretivas);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_7->addWidget(scrollArea);


        verticalLayout->addWidget(frameFormulario);


        retranslateUi(FormGerenciarUsuarios);

        QMetaObject::connectSlotsByName(FormGerenciarUsuarios);
    }  // setupUi

    void retranslateUi(QWidget *FormGerenciarUsuarios)
    {
        FormGerenciarUsuarios->setProperty("windowTitle", QVariant(QApplication::translate("FormGerenciarUsuarios", "FormGerenciarUsuarios", nullptr)));
        labelTituloFormulario->setProperty("text", QVariant(QApplication::translate("FormGerenciarUsuarios", "Formul\303\241rio para gerenciar um usu\303\241rio", nullptr)));
        pushButtonLimpar->setProperty("text", QVariant(QApplication::translate("FormGerenciarUsuarios", "Limpar", nullptr)));
        pushButtonNovo->setProperty("text", QVariant(QApplication::translate("FormGerenciarUsuarios", "Novo", nullptr)));
        pushButtonSalvar->setProperty("text", QVariant(QApplication::translate("FormGerenciarUsuarios", "Salvar", nullptr)));
        pushButtonPesquisar->setProperty("text", QVariant(QApplication::translate("FormGerenciarUsuarios", "Pesquisar", nullptr)));
        pushButtonRemover->setProperty("text", QVariant(QApplication::translate("FormGerenciarUsuarios", "Remover", nullptr)));
        pushButtonTituloInformacoesGerais->setProperty("text", QVariant(QApplication::translate("FormGerenciarUsuarios", "Informa\303\247\303\265es gerais", nullptr)));
        labelSenha->setProperty("text", QVariant(QApplication::translate("FormGerenciarUsuarios", "Senha:", nullptr)));
        labelConfirmarSenha->setProperty("text", QVariant(QApplication::translate("FormGerenciarUsuarios", "Confirmar Senha:", nullptr)));
        labelUsuario->setProperty("text", QVariant(QApplication::translate("FormGerenciarUsuarios", "Usu\303\241rio:", nullptr)));
        labelPrevilegio->setProperty("text", QVariant(QApplication::translate("FormGerenciarUsuarios", "Previl\303\251gio:", nullptr)));
        comboBoxPrevilegio->clear();
        comboBoxPrevilegio->insertItems(0, QStringList()
         << QApplication::translate("FormGerenciarUsuarios", "Nenhum", nullptr)
         << QApplication::translate("FormGerenciarUsuarios", "Usu\303\241rio", nullptr)
         << QApplication::translate("FormGerenciarUsuarios", "Administrador", nullptr)
        );
        pushButtonTituloDiretivas->setProperty("text", QVariant(QApplication::translate("FormGerenciarUsuarios", "Diretivas", nullptr)));
        pushButtonAtualizar->setProperty("text", QVariant(QApplication::translate("FormGerenciarUsuarios", "Atualizar URIs de dispositivos dos m\303\263dulos carregados atualmente", nullptr)));
    }  // retranslateUi

};

namespace Ui {
    class FormGerenciarUsuarios : public Ui_FormGerenciarUsuarios {};
}  // namespace Ui

#endif // UI_FORMGERENCIARUSUARIOS_H
