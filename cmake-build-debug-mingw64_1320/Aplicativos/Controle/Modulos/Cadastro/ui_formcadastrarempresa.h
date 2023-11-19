/********************************************************************************
** Form generated from reading the UI file 'formcadastrarempresa.ui'
**
** Created by: CopperSpice User Interface Compiler, Version 1.8.2
**
** WARNING! Any changes made to this file will be lost when the UI file is recompiled
********************************************************************************/

#ifndef UI_FORMCADASTRAREMPRESA_H
#define UI_FORMCADASTRAREMPRESA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_FormCadastrarEmpresa
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollAreaFolha;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QFrame *frameFormulario;
    QVBoxLayout *verticalLayout_5;
    QLabel *labelTituloFormulario;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBoxClassificacao;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBoxFabricante;
    QCheckBox *checkBoxFornecedor;
    QCheckBox *checkBoxCliente;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonPesquisaRapida;
    QPushButton *pushButtonSalvar;
    QPushButton *pushButtonLimpar;
    QPushButton *pushButtonRemover;
    QGroupBox *groupBoxCadastrar;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelCNPJ;
    QLineEdit *lineEditCNPJ;
    QLabel *labelIE;
    QLineEdit *lineEditIE;
    QLabel *labelDataFundacao;
    QDateEdit *dateEditFundacao;
    QHBoxLayout *horizontalLayout;
    QLabel *labelNomeFantasia;
    QLineEdit *lineEditNomeFantasia;
    QLabel *labelRazaoSocial;
    QLineEdit *lineEditRazaoSocial;
    QHBoxLayout *horizontalLayout_13;
    QLabel *labelTipoFornecedor;
    QComboBox *comboBoxTipoFornecedor;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_11;
    QFrame *frameEndereco;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelTituloEndereco;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelEndereco;
    QComboBox *comboBoxEndereco;
    QLabel *labelDataEndereco;
    QDateEdit *dateEditEndereco;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonAdicionarEndereco;
    QPushButton *pushButtonRemoverEndereco;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelLogradouro;
    QLineEdit *lineEditLogradouro;
    QLabel *labelNumero;
    QLineEdit *lineEditNumero;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelComplemento;
    QLineEdit *lineEditComplemento;
    QLabel *labelBairro;
    QLineEdit *lineEditBairro;
    QLabel *labelCEP;
    QLineEdit *lineEditCEP;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labelPais;
    QComboBox *comboBoxPais;
    QLabel *labelEstado;
    QComboBox *comboBoxEstado;
    QLabel *labelCidade;
    QComboBox *comboBoxCidade;
    QHBoxLayout *horizontalLayout_10;
    QFrame *frameContato;
    QVBoxLayout *verticalLayout_7;
    QLabel *labelTituloContato;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_9;
    QLabel *labelContato;
    QComboBox *comboBoxContato;
    QLabel *labelDataContato;
    QDateEdit *dateEditContato;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButtonAdicionarContato;
    QPushButton *pushButtonRemoverContato;
    QHBoxLayout *horizontalLayout_12;
    QLabel *labelEmail;
    QLineEdit *lineEditEmail;
    QLabel *labelTelefone;
    QLineEdit *lineEditTelefone;
    QLabel *labelCargo;
    QLineEdit *lineEditCargo;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *FormCadastrarEmpresa)
    {
        if (FormCadastrarEmpresa->objectName().isEmpty())
            FormCadastrarEmpresa->setObjectName(QString::fromUtf8("FormCadastrarEmpresa"));
        FormCadastrarEmpresa->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(70);
        sizePolicy.setVerticalStretch(100);
        sizePolicy.setHeightForWidth(FormCadastrarEmpresa->sizePolicy().hasHeightForWidth());
        FormCadastrarEmpresa->setProperty("sizePolicy", QVariant(sizePolicy));
        FormCadastrarEmpresa->resize(1006, 824);
        verticalLayout = new QVBoxLayout(FormCadastrarEmpresa);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollAreaFolha = new QScrollArea(FormCadastrarEmpresa);
        scrollAreaFolha->setObjectName(QString::fromUtf8("scrollAreaFolha"));
        scrollAreaFolha->setProperty("widgetResizable", QVariant(true));
        scrollAreaFolha->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setProperty("geometry", QVariant(QRect(0, 0, 986, 804)));
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
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(170, 255, 255, 125), stop:0.55 rgb(214, 214, 214), stop:0.98 rgb(134, 134, 134), stop:1 rgba(0, 0, 0, 0));\n"
"}\n"
"QFrame#frameEndereco\n"
"{\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 18px;\n"
"	border-top-right-radius: 18px;\n"
"	border-bottom-left-radius: 15px;\n"
"	border-bottom-right-radius: 15px;\n"
"}QFrame#frameContato\n"
"{\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 18px;\n"
"	border-top-right-radius: 18px;\n"
"	border-bottom-left-radius: 15px;\n"
"	border-bottom-right-radius: 15px;\n"
"}\n"
"QCheckBox {\n"
"	background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"QLabel {\n"
"Font-size: 12px;\n"
"	background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"QGroupBox {\n"
"	paddi"
                        "ng-top: 12px;\n"
"	border-color: rgb(12, 12, 12);\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 13px;\n"
"	border-top-right-radius: 13px;\n"
"	border-bottom-left-radius: 15px;\n"
"	border-bottom-right-radius: 15px;\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(116, 116, 116, 0), stop:1 rgba(253, 253, 253, 0));\n"
"	font-size: 12px;\n"
"	font-weight: bold;\n"
"}\n"
"QGroupBox::title {\n"
"	margin-left: 12px;\n"
"	margin-top: 3px;\n"
"	margin-bottom: 3px;\n"
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
"  font-size: 13px;\n"
"	height: 23px;\n"
"	width:65px;\n"
"	font-weight: normal;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
""
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
"QPushButton#pushButtonPesquisaRapida{\n"
"width:120px;\n"
"}\n"
"QPushButton#pushButtonRemover  {\n"
"\n"
"\n"
"background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(217, 5, 27), stop:1 rgb(253, 183, 186));\n"
"\n"
"}\n"
"QPushButton#pushButtonRemover:hover {\n"
"    	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(255, 85, 0), stop:1 rgba(255, 255, 255, 255));\n"
"\n"
"   \n"
"}\n"
"\n"
"QPushButton#pushButtonRemover:pressed {\n"
"    background-color: rgba(4, 50, 81, 120);\n"
"}\n"
"\n"
"\n"
"QPushButton#pushButtonRemoverEndereco  {\n"
"\n"
"\n"
"background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:"
                        "0, stop:0 rgb(217, 5, 27), stop:1 rgb(253, 183, 186));\n"
"}\n"
"QPushButton#pushButtonRemoverEndereco:hover {\n"
"   	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(255, 85, 0), stop:1 rgba(255, 255, 255, 255));\n"
"   \n"
"}\n"
"\n"
"QPushButton#pushButtonRemoverEndereco:pressed {\n"
"    background-color: rgba(4, 50, 81, 120);\n"
"}\n"
"\n"
"\n"
"\n"
"QPushButton#pushButtonRemoverContato  {\n"
"\n"
"\n"
"background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(217, 5, 27), stop:1 rgb(253, 183, 186));\n"
"\n"
"\n"
"}\n"
"QPushButton#pushButtonRemoverContato:hover {\n"
"   	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(255, 85, 0), stop:1 rgba(255, 255, 255, 255));\n"
"\n"
"   \n"
"}\n"
"\n"
"QPushButton#pushButtonRemoverContato:pressed {\n"
"    background-color: rgba(4, 50, 81, 120);\n"
"}\n"
"QComboBox\n"
"{ \n"
"background-color:rgb(255, 255, 255);\n"
"\n"
"}\n"
"")));
        verticalLayout_5 = new QVBoxLayout(frameFormulario);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 15);
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

        verticalLayout_5->addWidget(labelTituloFormulario);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(3, 0, 3, -1);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        groupBoxClassificacao = new QGroupBox(frameFormulario);
        groupBoxClassificacao->setObjectName(QString::fromUtf8("groupBoxClassificacao"));
        groupBoxClassificacao->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        horizontalLayout_3 = new QHBoxLayout(groupBoxClassificacao);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        checkBoxFabricante = new QCheckBox(groupBoxClassificacao);
        checkBoxFabricante->setObjectName(QString::fromUtf8("checkBoxFabricante"));
        checkBoxFabricante->setProperty("styleSheet", QVariant(QString::fromUtf8("")));

        horizontalLayout_3->addWidget(checkBoxFabricante);

        checkBoxFornecedor = new QCheckBox(groupBoxClassificacao);
        checkBoxFornecedor->setObjectName(QString::fromUtf8("checkBoxFornecedor"));

        horizontalLayout_3->addWidget(checkBoxFornecedor);

        checkBoxCliente = new QCheckBox(groupBoxClassificacao);
        checkBoxCliente->setObjectName(QString::fromUtf8("checkBoxCliente"));

        horizontalLayout_3->addWidget(checkBoxCliente);


        horizontalLayout_4->addWidget(groupBoxClassificacao);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        pushButtonPesquisaRapida = new QPushButton(frameFormulario);
        pushButtonPesquisaRapida->setObjectName(QString::fromUtf8("pushButtonPesquisaRapida"));
        pushButtonPesquisaRapida->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        pushButtonPesquisaRapida->setProperty("minimumSize", QVariant(QSize(100, 25)));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        pushButtonPesquisaRapida->setProperty("font", QVariant(font1));

        horizontalLayout_4->addWidget(pushButtonPesquisaRapida);

        pushButtonSalvar = new QPushButton(frameFormulario);
        pushButtonSalvar->setObjectName(QString::fromUtf8("pushButtonSalvar"));
        pushButtonSalvar->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        pushButtonSalvar->setProperty("minimumSize", QVariant(QSize(50, 25)));
        pushButtonSalvar->setProperty("font", QVariant(font1));

        horizontalLayout_4->addWidget(pushButtonSalvar);

        pushButtonLimpar = new QPushButton(frameFormulario);
        pushButtonLimpar->setObjectName(QString::fromUtf8("pushButtonLimpar"));
        pushButtonLimpar->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        pushButtonLimpar->setProperty("minimumSize", QVariant(QSize(50, 25)));
        pushButtonLimpar->setProperty("font", QVariant(font1));

        horizontalLayout_4->addWidget(pushButtonLimpar);

        pushButtonRemover = new QPushButton(frameFormulario);
        pushButtonRemover->setObjectName(QString::fromUtf8("pushButtonRemover"));
        pushButtonRemover->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        pushButtonRemover->setProperty("minimumSize", QVariant(QSize(100, 25)));
        pushButtonRemover->setProperty("font", QVariant(font1));

        horizontalLayout_4->addWidget(pushButtonRemover);


        verticalLayout_6->addLayout(horizontalLayout_4);

        groupBoxCadastrar = new QGroupBox(frameFormulario);
        groupBoxCadastrar->setObjectName(QString::fromUtf8("groupBoxCadastrar"));
        groupBoxCadastrar->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBoxCadastrar->sizePolicy().hasHeightForWidth());
        groupBoxCadastrar->setProperty("sizePolicy", QVariant(sizePolicy1));
        gridLayout = new QGridLayout(groupBoxCadastrar);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelCNPJ = new QLabel(groupBoxCadastrar);
        labelCNPJ->setObjectName(QString::fromUtf8("labelCNPJ"));
        labelCNPJ->setProperty("font", QVariant(font));

        horizontalLayout_2->addWidget(labelCNPJ);

        lineEditCNPJ = new QLineEdit(groupBoxCadastrar);
        lineEditCNPJ->setObjectName(QString::fromUtf8("lineEditCNPJ"));

        horizontalLayout_2->addWidget(lineEditCNPJ);

        labelIE = new QLabel(groupBoxCadastrar);
        labelIE->setObjectName(QString::fromUtf8("labelIE"));

        horizontalLayout_2->addWidget(labelIE);

        lineEditIE = new QLineEdit(groupBoxCadastrar);
        lineEditIE->setObjectName(QString::fromUtf8("lineEditIE"));

        horizontalLayout_2->addWidget(lineEditIE);

        labelDataFundacao = new QLabel(groupBoxCadastrar);
        labelDataFundacao->setObjectName(QString::fromUtf8("labelDataFundacao"));

        horizontalLayout_2->addWidget(labelDataFundacao);

        dateEditFundacao = new QDateEdit(groupBoxCadastrar);
        dateEditFundacao->setObjectName(QString::fromUtf8("dateEditFundacao"));

        horizontalLayout_2->addWidget(dateEditFundacao);


        gridLayout->addLayout(horizontalLayout_2, 1, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelNomeFantasia = new QLabel(groupBoxCadastrar);
        labelNomeFantasia->setObjectName(QString::fromUtf8("labelNomeFantasia"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelNomeFantasia->sizePolicy().hasHeightForWidth());
        labelNomeFantasia->setProperty("sizePolicy", QVariant(sizePolicy2));
        labelNomeFantasia->setProperty("font", QVariant(font));

        horizontalLayout->addWidget(labelNomeFantasia);

        lineEditNomeFantasia = new QLineEdit(groupBoxCadastrar);
        lineEditNomeFantasia->setObjectName(QString::fromUtf8("lineEditNomeFantasia"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineEditNomeFantasia->sizePolicy().hasHeightForWidth());
        lineEditNomeFantasia->setProperty("sizePolicy", QVariant(sizePolicy3));

        horizontalLayout->addWidget(lineEditNomeFantasia);

        labelRazaoSocial = new QLabel(groupBoxCadastrar);
        labelRazaoSocial->setObjectName(QString::fromUtf8("labelRazaoSocial"));
        sizePolicy2.setHeightForWidth(labelRazaoSocial->sizePolicy().hasHeightForWidth());
        labelRazaoSocial->setProperty("sizePolicy", QVariant(sizePolicy2));
        labelRazaoSocial->setProperty("font", QVariant(font));

        horizontalLayout->addWidget(labelRazaoSocial);

        lineEditRazaoSocial = new QLineEdit(groupBoxCadastrar);
        lineEditRazaoSocial->setObjectName(QString::fromUtf8("lineEditRazaoSocial"));
        sizePolicy1.setHeightForWidth(lineEditRazaoSocial->sizePolicy().hasHeightForWidth());
        lineEditRazaoSocial->setProperty("sizePolicy", QVariant(sizePolicy1));

        horizontalLayout->addWidget(lineEditRazaoSocial);


        gridLayout->addLayout(horizontalLayout, 0, 3, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(-1, 0, -1, -1);
        labelTipoFornecedor = new QLabel(groupBoxCadastrar);
        labelTipoFornecedor->setObjectName(QString::fromUtf8("labelTipoFornecedor"));

        horizontalLayout_13->addWidget(labelTipoFornecedor);

        comboBoxTipoFornecedor = new QComboBox(groupBoxCadastrar);
        comboBoxTipoFornecedor->setObjectName(QString::fromUtf8("comboBoxTipoFornecedor"));
        sizePolicy1.setHeightForWidth(comboBoxTipoFornecedor->sizePolicy().hasHeightForWidth());
        comboBoxTipoFornecedor->setProperty("sizePolicy", QVariant(sizePolicy1));

        horizontalLayout_13->addWidget(comboBoxTipoFornecedor);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_13, 2, 3, 1, 1);


        verticalLayout_6->addWidget(groupBoxCadastrar);


        verticalLayout_5->addLayout(verticalLayout_6);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(6, 6, 6, -1);
        frameEndereco = new QFrame(frameFormulario);
        frameEndereco->setObjectName(QString::fromUtf8("frameEndereco"));
        frameEndereco->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        frameEndereco->setProperty("frameShadow", QVariant(QFrame::Raised));
        frameEndereco->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        verticalLayout_4 = new QVBoxLayout(frameEndereco);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 15);
        labelTituloEndereco = new QLabel(frameEndereco);
        labelTituloEndereco->setObjectName(QString::fromUtf8("labelTituloEndereco"));
        labelTituloEndereco->setProperty("alignment", QVariant(Qt::AlignCenter));
        labelTituloEndereco->setProperty("styleSheet", QVariant(QString::fromUtf8("QLabel#labelTituloEndereco {\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 17px;\n"
"	border-top-right-radius: 17px;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(155, 159, 74), stop:1 rgb(211, 211, 211));\n"
"	padding: 5px 0px;\n"
"	padding: 5px 0px;\n"
"	max-height: 25px;\n"
"    font-size: 14px;\n"
"}")));
        labelTituloEndereco->setProperty("font", QVariant(font));

        verticalLayout_4->addWidget(labelTituloEndereco);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(3, 0, 3, -1);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 0, -1, -1);
        labelEndereco = new QLabel(frameEndereco);
        labelEndereco->setObjectName(QString::fromUtf8("labelEndereco"));
        sizePolicy2.setHeightForWidth(labelEndereco->sizePolicy().hasHeightForWidth());
        labelEndereco->setProperty("sizePolicy", QVariant(sizePolicy2));

        horizontalLayout_5->addWidget(labelEndereco);

        comboBoxEndereco = new QComboBox(frameEndereco);
        comboBoxEndereco->setObjectName(QString::fromUtf8("comboBoxEndereco"));
        sizePolicy1.setHeightForWidth(comboBoxEndereco->sizePolicy().hasHeightForWidth());
        comboBoxEndereco->setProperty("sizePolicy", QVariant(sizePolicy1));

        horizontalLayout_5->addWidget(comboBoxEndereco);

        labelDataEndereco = new QLabel(frameEndereco);
        labelDataEndereco->setObjectName(QString::fromUtf8("labelDataEndereco"));
        sizePolicy2.setHeightForWidth(labelDataEndereco->sizePolicy().hasHeightForWidth());
        labelDataEndereco->setProperty("sizePolicy", QVariant(sizePolicy2));

        horizontalLayout_5->addWidget(labelDataEndereco);

        dateEditEndereco = new QDateEdit(frameEndereco);
        dateEditEndereco->setObjectName(QString::fromUtf8("dateEditEndereco"));

        horizontalLayout_5->addWidget(dateEditEndereco);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        pushButtonAdicionarEndereco = new QPushButton(frameEndereco);
        pushButtonAdicionarEndereco->setObjectName(QString::fromUtf8("pushButtonAdicionarEndereco"));
        pushButtonAdicionarEndereco->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        sizePolicy3.setHeightForWidth(pushButtonAdicionarEndereco->sizePolicy().hasHeightForWidth());
        pushButtonAdicionarEndereco->setProperty("sizePolicy", QVariant(sizePolicy3));
        pushButtonAdicionarEndereco->setProperty("minimumSize", QVariant(QSize(65, 25)));
        pushButtonAdicionarEndereco->setProperty("maximumSize", QVariant(QSize(300, 16777215)));
        pushButtonAdicionarEndereco->setProperty("font", QVariant(font1));

        horizontalLayout_5->addWidget(pushButtonAdicionarEndereco);

        pushButtonRemoverEndereco = new QPushButton(frameEndereco);
        pushButtonRemoverEndereco->setObjectName(QString::fromUtf8("pushButtonRemoverEndereco"));
        pushButtonRemoverEndereco->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        pushButtonRemoverEndereco->setProperty("minimumSize", QVariant(QSize(60, 25)));
        pushButtonRemoverEndereco->setProperty("maximumSize", QVariant(QSize(300, 16777215)));
        pushButtonRemoverEndereco->setProperty("font", QVariant(font1));

        horizontalLayout_5->addWidget(pushButtonRemoverEndereco);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, 6, -1, -1);
        labelLogradouro = new QLabel(frameEndereco);
        labelLogradouro->setObjectName(QString::fromUtf8("labelLogradouro"));

        horizontalLayout_6->addWidget(labelLogradouro);

        lineEditLogradouro = new QLineEdit(frameEndereco);
        lineEditLogradouro->setObjectName(QString::fromUtf8("lineEditLogradouro"));

        horizontalLayout_6->addWidget(lineEditLogradouro);

        labelNumero = new QLabel(frameEndereco);
        labelNumero->setObjectName(QString::fromUtf8("labelNumero"));
        sizePolicy2.setHeightForWidth(labelNumero->sizePolicy().hasHeightForWidth());
        labelNumero->setProperty("sizePolicy", QVariant(sizePolicy2));

        horizontalLayout_6->addWidget(labelNumero);

        lineEditNumero = new QLineEdit(frameEndereco);
        lineEditNumero->setObjectName(QString::fromUtf8("lineEditNumero"));
        sizePolicy3.setHeightForWidth(lineEditNumero->sizePolicy().hasHeightForWidth());
        lineEditNumero->setProperty("sizePolicy", QVariant(sizePolicy3));

        horizontalLayout_6->addWidget(lineEditNumero);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(-1, 6, -1, -1);
        labelComplemento = new QLabel(frameEndereco);
        labelComplemento->setObjectName(QString::fromUtf8("labelComplemento"));
        sizePolicy2.setHeightForWidth(labelComplemento->sizePolicy().hasHeightForWidth());
        labelComplemento->setProperty("sizePolicy", QVariant(sizePolicy2));

        horizontalLayout_7->addWidget(labelComplemento);

        lineEditComplemento = new QLineEdit(frameEndereco);
        lineEditComplemento->setObjectName(QString::fromUtf8("lineEditComplemento"));

        horizontalLayout_7->addWidget(lineEditComplemento);

        labelBairro = new QLabel(frameEndereco);
        labelBairro->setObjectName(QString::fromUtf8("labelBairro"));

        horizontalLayout_7->addWidget(labelBairro);

        lineEditBairro = new QLineEdit(frameEndereco);
        lineEditBairro->setObjectName(QString::fromUtf8("lineEditBairro"));

        horizontalLayout_7->addWidget(lineEditBairro);

        labelCEP = new QLabel(frameEndereco);
        labelCEP->setObjectName(QString::fromUtf8("labelCEP"));

        horizontalLayout_7->addWidget(labelCEP);

        lineEditCEP = new QLineEdit(frameEndereco);
        lineEditCEP->setObjectName(QString::fromUtf8("lineEditCEP"));
        sizePolicy3.setHeightForWidth(lineEditCEP->sizePolicy().hasHeightForWidth());
        lineEditCEP->setProperty("sizePolicy", QVariant(sizePolicy3));

        horizontalLayout_7->addWidget(lineEditCEP);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(-1, 6, -1, -1);
        labelPais = new QLabel(frameEndereco);
        labelPais->setObjectName(QString::fromUtf8("labelPais"));

        horizontalLayout_8->addWidget(labelPais);

        comboBoxPais = new QComboBox(frameEndereco);
        comboBoxPais->setObjectName(QString::fromUtf8("comboBoxPais"));
        sizePolicy3.setHeightForWidth(comboBoxPais->sizePolicy().hasHeightForWidth());
        comboBoxPais->setProperty("sizePolicy", QVariant(sizePolicy3));
        QFont font2;
        font2.setPointSize(10);
        comboBoxPais->setProperty("font", QVariant(font2));

        horizontalLayout_8->addWidget(comboBoxPais);

        labelEstado = new QLabel(frameEndereco);
        labelEstado->setObjectName(QString::fromUtf8("labelEstado"));
        sizePolicy2.setHeightForWidth(labelEstado->sizePolicy().hasHeightForWidth());
        labelEstado->setProperty("sizePolicy", QVariant(sizePolicy2));

        horizontalLayout_8->addWidget(labelEstado);

        comboBoxEstado = new QComboBox(frameEndereco);
        comboBoxEstado->setObjectName(QString::fromUtf8("comboBoxEstado"));
        sizePolicy3.setHeightForWidth(comboBoxEstado->sizePolicy().hasHeightForWidth());
        comboBoxEstado->setProperty("sizePolicy", QVariant(sizePolicy3));
        comboBoxEstado->setProperty("font", QVariant(font2));

        horizontalLayout_8->addWidget(comboBoxEstado);

        labelCidade = new QLabel(frameEndereco);
        labelCidade->setObjectName(QString::fromUtf8("labelCidade"));
        sizePolicy2.setHeightForWidth(labelCidade->sizePolicy().hasHeightForWidth());
        labelCidade->setProperty("sizePolicy", QVariant(sizePolicy2));

        horizontalLayout_8->addWidget(labelCidade);

        comboBoxCidade = new QComboBox(frameEndereco);
        comboBoxCidade->setObjectName(QString::fromUtf8("comboBoxCidade"));
        sizePolicy1.setHeightForWidth(comboBoxCidade->sizePolicy().hasHeightForWidth());
        comboBoxCidade->setProperty("sizePolicy", QVariant(sizePolicy1));
        comboBoxCidade->setProperty("font", QVariant(font2));

        horizontalLayout_8->addWidget(comboBoxCidade);


        verticalLayout_3->addLayout(horizontalLayout_8);


        verticalLayout_4->addLayout(verticalLayout_3);


        horizontalLayout_11->addWidget(frameEndereco);


        verticalLayout_5->addLayout(horizontalLayout_11);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(6, 6, 6, -1);
        frameContato = new QFrame(frameFormulario);
        frameContato->setObjectName(QString::fromUtf8("frameContato"));
        frameContato->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        frameContato->setProperty("frameShadow", QVariant(QFrame::Raised));
        frameContato->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        verticalLayout_7 = new QVBoxLayout(frameContato);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 15);
        labelTituloContato = new QLabel(frameContato);
        labelTituloContato->setObjectName(QString::fromUtf8("labelTituloContato"));
        labelTituloContato->setProperty("alignment", QVariant(Qt::AlignCenter));
        labelTituloContato->setProperty("styleSheet", QVariant(QString::fromUtf8("QLabel#labelTituloContato {\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 17px;\n"
"	border-top-right-radius: 17px;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(98, 98, 98), stop:1 rgb(211, 211, 211));\n"
"	padding: 5px 0px;\n"
"	padding: 5px 0px;\n"
"	max-height: 25px;\n"
"    font-size: 14px;\n"
"}")));
        labelTituloContato->setProperty("font", QVariant(font));

        verticalLayout_7->addWidget(labelTituloContato);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(3, 0, 3, -1);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(-1, 0, -1, -1);
        labelContato = new QLabel(frameContato);
        labelContato->setObjectName(QString::fromUtf8("labelContato"));

        horizontalLayout_9->addWidget(labelContato);

        comboBoxContato = new QComboBox(frameContato);
        comboBoxContato->setObjectName(QString::fromUtf8("comboBoxContato"));
        sizePolicy1.setHeightForWidth(comboBoxContato->sizePolicy().hasHeightForWidth());
        comboBoxContato->setProperty("sizePolicy", QVariant(sizePolicy1));

        horizontalLayout_9->addWidget(comboBoxContato);

        labelDataContato = new QLabel(frameContato);
        labelDataContato->setObjectName(QString::fromUtf8("labelDataContato"));

        horizontalLayout_9->addWidget(labelDataContato);

        dateEditContato = new QDateEdit(frameContato);
        dateEditContato->setObjectName(QString::fromUtf8("dateEditContato"));

        horizontalLayout_9->addWidget(dateEditContato);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);

        pushButtonAdicionarContato = new QPushButton(frameContato);
        pushButtonAdicionarContato->setObjectName(QString::fromUtf8("pushButtonAdicionarContato"));
        pushButtonAdicionarContato->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        pushButtonAdicionarContato->setProperty("minimumSize", QVariant(QSize(65, 25)));
        pushButtonAdicionarContato->setProperty("font", QVariant(font1));

        horizontalLayout_9->addWidget(pushButtonAdicionarContato);

        pushButtonRemoverContato = new QPushButton(frameContato);
        pushButtonRemoverContato->setObjectName(QString::fromUtf8("pushButtonRemoverContato"));
        pushButtonRemoverContato->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        pushButtonRemoverContato->setProperty("minimumSize", QVariant(QSize(60, 25)));
        pushButtonRemoverContato->setProperty("font", QVariant(font1));

        horizontalLayout_9->addWidget(pushButtonRemoverContato);


        verticalLayout_8->addLayout(horizontalLayout_9);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(-1, 0, -1, -1);
        labelEmail = new QLabel(frameContato);
        labelEmail->setObjectName(QString::fromUtf8("labelEmail"));

        horizontalLayout_12->addWidget(labelEmail);

        lineEditEmail = new QLineEdit(frameContato);
        lineEditEmail->setObjectName(QString::fromUtf8("lineEditEmail"));
        sizePolicy1.setHeightForWidth(lineEditEmail->sizePolicy().hasHeightForWidth());
        lineEditEmail->setProperty("sizePolicy", QVariant(sizePolicy1));

        horizontalLayout_12->addWidget(lineEditEmail);

        labelTelefone = new QLabel(frameContato);
        labelTelefone->setObjectName(QString::fromUtf8("labelTelefone"));

        horizontalLayout_12->addWidget(labelTelefone);

        lineEditTelefone = new QLineEdit(frameContato);
        lineEditTelefone->setObjectName(QString::fromUtf8("lineEditTelefone"));
        sizePolicy3.setHeightForWidth(lineEditTelefone->sizePolicy().hasHeightForWidth());
        lineEditTelefone->setProperty("sizePolicy", QVariant(sizePolicy3));

        horizontalLayout_12->addWidget(lineEditTelefone);

        labelCargo = new QLabel(frameContato);
        labelCargo->setObjectName(QString::fromUtf8("labelCargo"));

        horizontalLayout_12->addWidget(labelCargo);

        lineEditCargo = new QLineEdit(frameContato);
        lineEditCargo->setObjectName(QString::fromUtf8("lineEditCargo"));

        horizontalLayout_12->addWidget(lineEditCargo);


        verticalLayout_8->addLayout(horizontalLayout_12);


        verticalLayout_7->addLayout(verticalLayout_8);


        horizontalLayout_10->addWidget(frameContato);


        verticalLayout_5->addLayout(horizontalLayout_10);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);


        verticalLayout_2->addWidget(frameFormulario);

        scrollAreaFolha->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollAreaFolha);

        QWidget::setTabOrder(scrollAreaFolha, checkBoxFabricante);
        QWidget::setTabOrder(checkBoxFabricante, checkBoxFornecedor);
        QWidget::setTabOrder(checkBoxFornecedor, checkBoxCliente);
        QWidget::setTabOrder(checkBoxCliente, lineEditNomeFantasia);
        QWidget::setTabOrder(lineEditNomeFantasia, lineEditRazaoSocial);
        QWidget::setTabOrder(lineEditRazaoSocial, lineEditCNPJ);
        QWidget::setTabOrder(lineEditCNPJ, lineEditIE);
        QWidget::setTabOrder(lineEditIE, dateEditFundacao);
        QWidget::setTabOrder(dateEditFundacao, comboBoxEndereco);
        QWidget::setTabOrder(comboBoxEndereco, dateEditEndereco);
        QWidget::setTabOrder(dateEditEndereco, lineEditLogradouro);
        QWidget::setTabOrder(lineEditLogradouro, lineEditNumero);
        QWidget::setTabOrder(lineEditNumero, lineEditComplemento);
        QWidget::setTabOrder(lineEditComplemento, lineEditBairro);
        QWidget::setTabOrder(lineEditBairro, lineEditCEP);
        QWidget::setTabOrder(lineEditCEP, comboBoxPais);
        QWidget::setTabOrder(comboBoxPais, comboBoxEstado);
        QWidget::setTabOrder(comboBoxEstado, comboBoxCidade);
        QWidget::setTabOrder(comboBoxCidade, pushButtonAdicionarEndereco);
        QWidget::setTabOrder(pushButtonAdicionarEndereco, pushButtonRemoverEndereco);
        QWidget::setTabOrder(pushButtonRemoverEndereco, comboBoxContato);
        QWidget::setTabOrder(comboBoxContato, dateEditContato);
        QWidget::setTabOrder(dateEditContato, lineEditEmail);
        QWidget::setTabOrder(lineEditEmail, lineEditTelefone);
        QWidget::setTabOrder(lineEditTelefone, lineEditCargo);
        QWidget::setTabOrder(lineEditCargo, pushButtonAdicionarContato);
        QWidget::setTabOrder(pushButtonAdicionarContato, pushButtonRemoverContato);
        QWidget::setTabOrder(pushButtonRemoverContato, pushButtonPesquisaRapida);
        QWidget::setTabOrder(pushButtonPesquisaRapida, pushButtonSalvar);
        QWidget::setTabOrder(pushButtonSalvar, pushButtonLimpar);
        QWidget::setTabOrder(pushButtonLimpar, pushButtonRemover);

        retranslateUi(FormCadastrarEmpresa);

        QMetaObject::connectSlotsByName(FormCadastrarEmpresa);
    }  // setupUi

    void retranslateUi(QDialog *FormCadastrarEmpresa)
    {
        FormCadastrarEmpresa->setProperty("windowTitle", QVariant(QApplication::translate("FormCadastrarEmpresa", "Dialog", nullptr)));
        labelTituloFormulario->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Formul\303\241rio cadastro de uma empresa", nullptr)));
        groupBoxClassificacao->setProperty("title", QVariant(QApplication::translate("FormCadastrarEmpresa", "Classifica\303\247\303\243o:", nullptr)));
        checkBoxFabricante->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Fabricante", nullptr)));
        checkBoxFornecedor->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Fornecedor", nullptr)));
        checkBoxCliente->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Cliente", nullptr)));
        pushButtonPesquisaRapida->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Pesquisa R\303\241pida", nullptr)));
        pushButtonSalvar->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Salvar", nullptr)));
        pushButtonLimpar->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Limpar", nullptr)));
        pushButtonRemover->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Remover", nullptr)));
        groupBoxCadastrar->setProperty("title", QVariant(QApplication::translate("FormCadastrarEmpresa", "Cadastrar uma empresa:", nullptr)));
        labelCNPJ->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "CNPJ:", nullptr)));
        labelIE->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "IE:", nullptr)));
        labelDataFundacao->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Data de funda\303\247\303\243o:", nullptr)));
        labelNomeFantasia->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Nome fantasia:", nullptr)));
        labelRazaoSocial->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Raz\303\243o Social:", nullptr)));
        labelTipoFornecedor->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Tipo do fornecedor:", nullptr)));
        labelTituloEndereco->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Endere\303\247o", nullptr)));
        labelEndereco->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Identifica\303\247\303\243o:", nullptr)));
        labelDataEndereco->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Data inclus\303\243o:", nullptr)));
        pushButtonAdicionarEndereco->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Adicionar", nullptr)));
        pushButtonRemoverEndereco->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Remover", nullptr)));
        labelLogradouro->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Logradouro:", nullptr)));
        labelNumero->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "N\303\272mero:", nullptr)));
        labelComplemento->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Complemento:", nullptr)));
        labelBairro->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Bairro:", nullptr)));
        labelCEP->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "CEP:", nullptr)));
        labelPais->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Pa\303\255s:", nullptr)));
        labelEstado->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Estado:", nullptr)));
        labelCidade->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Cidade:", nullptr)));
        labelTituloContato->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Contato", nullptr)));
        labelContato->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Identifica\303\247\303\243o:", nullptr)));
        labelDataContato->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Data inclus\303\243o:", nullptr)));
        pushButtonAdicionarContato->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Adicionar", nullptr)));
        pushButtonRemoverContato->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Remover", nullptr)));
        labelEmail->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "E-mail:", nullptr)));
        labelTelefone->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Telefone:", nullptr)));
        labelCargo->setProperty("text", QVariant(QApplication::translate("FormCadastrarEmpresa", "Cargo:", nullptr)));
    }  // retranslateUi

};

namespace Ui {
    class FormCadastrarEmpresa : public Ui_FormCadastrarEmpresa {};
}  // namespace Ui

#endif // UI_FORMCADASTRAREMPRESA_H
