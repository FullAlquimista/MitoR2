/********************************************************************************
** Form generated from reading the UI file 'formcadastrarmateriais.ui'
**
** Created by: CopperSpice User Interface Compiler, Version 1.8.2
**
** WARNING! Any changes made to this file will be lost when the UI file is recompiled
********************************************************************************/

#ifndef UI_FORMCADASTRARMATERIAIS_H
#define UI_FORMCADASTRARMATERIAIS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
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
#include <QtGui/QSpinBox>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_FormCadastrarMateriais
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
    QPushButton *pushButtonNovoFormulario;
    QPushButton *pushButtonPesquisarFormulario;
    QPushButton *pushButtonSalvarFormulario;
    QPushButton *pushButtonLimparFormulario;
    QPushButton *pushButtonRemoverFormulario;
    QFrame *frameInformacoesGerais;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButtonTituloInformacoesGerais;
    QFrame *subFrameInformaoesGerais;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelClassificacao;
    QFrame *frameBoxId;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *lineEditIdClassificacao;
    QFrame *frameBtUpDown;
    QVBoxLayout *verticalLayout_8;
    QPushButton *pushButtonCUp;
    QPushButton *pushButtonCDown;
    QLineEdit *lineEditDescricaoClassificacao;
    QPushButton *pushButtonSelecionarClassificacao;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *labelIdMaterial;
    QSpinBox *spinBoxIdMaterial;
    QLabel *labelDescricaoMaterial;
    QLineEdit *lineEditDescricaoMaterial;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelUnidadeEstoque;
    QComboBox *comboBoxUnidadeEstoque;
    QLabel *labelUnidadeComercial;
    QComboBox *comboBoxUnidadeComercial;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelPlanoConta;
    QFrame *frameBoxId_2;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *lineEditIdPlanoConta;
    QFrame *frameBtUpDown_2;
    QVBoxLayout *verticalLayout_9;
    QPushButton *pushButtonPUp;
    QPushButton *pushButtonPDown;
    QLineEdit *lineEditDescricaoPlanoConta;
    QPushButton *pushButtonSelecionarPlanoConta;
    QSpacerItem *horizontalSpacer_3;
    QFrame *frameInformacoesMaterialFracionado;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pushButtonTituloInformacoesFracionado;
    QFrame *subFrameInformacoesMaterialFracionado;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButtonAdicionarRegistro;
    QPushButton *pushButtonGravarRegistro;
    QPushButton *pushButtonExcluirRegistro;
    QSpacerItem *horizontalSpacer_6;
    QTableView *tableView;

    void setupUi(QWidget *FormCadastrarMateriais)
    {
        if (FormCadastrarMateriais->objectName().isEmpty())
            FormCadastrarMateriais->setObjectName(QString::fromUtf8("FormCadastrarMateriais"));
        FormCadastrarMateriais->resize(787, 613);
        verticalLayout = new QVBoxLayout(FormCadastrarMateriais);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(FormCadastrarMateriais);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setProperty("widgetResizable", QVariant(true));
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setProperty("geometry", QVariant(QRect(0, 0, 767, 593)));
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
"\n"
"QLabel#labelTituloFormulario {\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 10px;\n"
"	border-top-right-radius: 10px;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(59, 82, 131), stop:0.55 rgb(8, 122, 122), stop:0.98 rgba(0, 0, 0, 255), stop:1 rgba(0, 0, 0, 0));\n"
"	padding: 5px 0px;\n"
"	color: rgb(255, 255, 255);\n"
"	max-height: 25px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QPushButton#pushButtonTituloInformacoesGerais {\n"
"	border: 1px solid #00000000;\n"
"	border-top-left-radius: 15px;\n"
"	border-top-right-radius: 15px;\n"
"	background"
                        "-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(155, 159, 74), stop:1 rgb(211, 211, 211));\n"
"	padding: 5px 0px;\n"
"	max-height: 25px;\n"
"   font-size: 14px;\n"
"}\n"
"\n"
"QPushButton#pushButtonTituloInformacoesFracionado {\n"
"	border: 1px solid rgba(0, 0, 0, 50);\n"
"	border-top-left-radius: 15px;\n"
"	border-top-right-radius: 15px;\n"
"	border-right: 2px solid rgba(0, 0, 0, 185);\n"
"	border-bottom: 2px solid rgba(0, 0, 0, 185);\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(98, 98, 98), stop:1 rgb(211, 211, 211));\n"
"	padding: 5px 0px;\n"
"	max-height: 25px;\n"
"   font-size: 14px;\n"
"}")));
        verticalLayout_7 = new QVBoxLayout(frameFormulario);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 15);
        labelTituloFormulario = new QLabel(frameFormulario);
        labelTituloFormulario->setObjectName(QString::fromUtf8("labelTituloFormulario"));
        labelTituloFormulario->setProperty("alignment", QVariant(Qt::AlignCenter));
        labelTituloFormulario->setProperty("styleSheet", QVariant(QString::fromUtf8("")));
        QFont font;
        labelTituloFormulario->setProperty("font", QVariant(font));

        verticalLayout_7->addWidget(labelTituloFormulario);

        horizontalLayoutBotoes = new QHBoxLayout();
        horizontalLayoutBotoes->setSpacing(2);
        horizontalLayoutBotoes->setObjectName(QString::fromUtf8("horizontalLayoutBotoes"));
        horizontalLayoutBotoes->setContentsMargins(-1, 6, -1, 6);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayoutBotoes->addItem(horizontalSpacer);

        pushButtonNovoFormulario = new QPushButton(frameFormulario);
        pushButtonNovoFormulario->setObjectName(QString::fromUtf8("pushButtonNovoFormulario"));
        pushButtonNovoFormulario->setProperty("styleSheet", QVariant(QString::fromUtf8("QPushButton\n"
"{\n"
"	border: 1px solid rgba(0, 0, 0, 85);\n"
"	border-radius: 8px;\n"
"	border-right: 2px solid rgba(0, 0, 0, 185);\n"
"	border-bottom: 2px solid rgba(0, 0, 0, 185);\n"
"  background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(35, 84, 156, 125), stop:1 rgba(58, 134, 255, 125));\n"
"  font-size: 13px;\n"
"	height: 23px;\n"
"\n"
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
"}")));
        pushButtonNovoFormulario->setProperty("minimumSize", QVariant(QSize(75, 23)));

        horizontalLayoutBotoes->addWidget(pushButtonNovoFormulario);

        pushButtonPesquisarFormulario = new QPushButton(frameFormulario);
        pushButtonPesquisarFormulario->setObjectName(QString::fromUtf8("pushButtonPesquisarFormulario"));
        pushButtonPesquisarFormulario->setProperty("styleSheet", QVariant(QString::fromUtf8("QPushButton\n"
"{\n"
"	border: 1px solid rgba(0, 0, 0, 85);\n"
"	border-radius: 8px;\n"
"	border-right: 2px solid rgba(0, 0, 0, 185);\n"
"	border-bottom: 2px solid rgba(0, 0, 0, 185);\n"
"  background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(35, 84, 156, 125), stop:1 rgba(58, 134, 255, 125));\n"
"  font-size: 13px;\n"
"	height: 23px;\n"
"  width: 85px;\n"
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
"}")));

        horizontalLayoutBotoes->addWidget(pushButtonPesquisarFormulario);

        pushButtonSalvarFormulario = new QPushButton(frameFormulario);
        pushButtonSalvarFormulario->setObjectName(QString::fromUtf8("pushButtonSalvarFormulario"));
        pushButtonSalvarFormulario->setProperty("styleSheet", QVariant(QString::fromUtf8("QPushButton\n"
"{\n"
"	border: 1px solid rgba(0, 0, 0, 85);\n"
"	border-radius: 8px;\n"
"	border-right: 2px solid rgba(0, 0, 0, 185);\n"
"	border-bottom: 2px solid rgba(0, 0, 0, 185);\n"
"  background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(35, 84, 156, 125), stop:1 rgba(58, 134, 255, 125));\n"
"  font-size: 13px;\n"
"	height: 23px;\n"
"  width: 65px;\n"
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
"}")));

        horizontalLayoutBotoes->addWidget(pushButtonSalvarFormulario);

        pushButtonLimparFormulario = new QPushButton(frameFormulario);
        pushButtonLimparFormulario->setObjectName(QString::fromUtf8("pushButtonLimparFormulario"));
        pushButtonLimparFormulario->setProperty("styleSheet", QVariant(QString::fromUtf8("QPushButton\n"
"{\n"
"	border: 1px solid rgba(0, 0, 0, 85);\n"
"	border-radius: 8px;\n"
"	border-right: 2px solid rgba(0, 0, 0, 185);\n"
"	border-bottom: 2px solid rgba(0, 0, 0, 185);\n"
"  background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(35, 84, 156, 125), stop:1 rgba(58, 134, 255, 125));\n"
"  font-size: 13px;\n"
"	height: 23px;\n"
"  width: 65px;\n"
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
"}")));

        horizontalLayoutBotoes->addWidget(pushButtonLimparFormulario);

        pushButtonRemoverFormulario = new QPushButton(frameFormulario);
        pushButtonRemoverFormulario->setObjectName(QString::fromUtf8("pushButtonRemoverFormulario"));
        pushButtonRemoverFormulario->setProperty("styleSheet", QVariant(QString::fromUtf8("QPushButton\n"
"{\n"
"	border: 1px solid rgba(0, 0, 0, 85);\n"
"	border-radius: 8px;\n"
"	border-right: 2px solid rgba(0, 0, 0, 185);\n"
"	border-bottom: 2px solid rgba(0, 0, 0, 185);\n"
" background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(217, 5, 27), stop:1 rgb(253, 183, 186));\n"
"  font-size: 13px;\n"
"	height: 23px;\n"
"  width: 65px;\n"
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
"		background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(255, 85, 0), stop:1 rgba(255, 255, 255, 255));\n"
"}\n"
"\n"
"")));

        horizontalLayoutBotoes->addWidget(pushButtonRemoverFormulario);


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
        pushButtonTituloInformacoesGerais->setProperty("styleSheet", QVariant(QString::fromUtf8("")));

        verticalLayout_4->addWidget(pushButtonTituloInformacoesGerais);

        subFrameInformaoesGerais = new QFrame(frameInformacoesGerais);
        subFrameInformaoesGerais->setObjectName(QString::fromUtf8("subFrameInformaoesGerais"));
        subFrameInformaoesGerais->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        subFrameInformaoesGerais->setProperty("frameShadow", QVariant(QFrame::Raised));
        gridLayout = new QGridLayout(subFrameInformaoesGerais);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(9, 9, 9, 9);
        groupBox = new QGroupBox(subFrameInformaoesGerais);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setProperty("minimumSize", QVariant(QSize(500, 0)));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 0);
        labelClassificacao = new QLabel(groupBox);
        labelClassificacao->setObjectName(QString::fromUtf8("labelClassificacao"));

        horizontalLayout_3->addWidget(labelClassificacao);

        frameBoxId = new QFrame(groupBox);
        frameBoxId->setObjectName(QString::fromUtf8("frameBoxId"));
        frameBoxId->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        frameBoxId->setProperty("frameShadow", QVariant(QFrame::Raised));
        frameBoxId->setProperty("minimumSize", QVariant(QSize(0, 0)));
        frameBoxId->setProperty("maximumSize", QVariant(QSize(70, 16777215)));
        horizontalLayout_7 = new QHBoxLayout(frameBoxId);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        lineEditIdClassificacao = new QLineEdit(frameBoxId);
        lineEditIdClassificacao->setObjectName(QString::fromUtf8("lineEditIdClassificacao"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEditIdClassificacao->sizePolicy().hasHeightForWidth());
        lineEditIdClassificacao->setProperty("sizePolicy", QVariant(sizePolicy));

        horizontalLayout_7->addWidget(lineEditIdClassificacao);

        frameBtUpDown = new QFrame(frameBoxId);
        frameBtUpDown->setObjectName(QString::fromUtf8("frameBtUpDown"));
        frameBtUpDown->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        frameBtUpDown->setProperty("frameShadow", QVariant(QFrame::Raised));
        frameBtUpDown->setProperty("styleSheet", QVariant(QString::fromUtf8("QFrame\n"
"{\n"
"	margin: 0px;\n"
"	padding: 0px;\n"
"}\n"
"QPushButton\n"
"{\n"
"	\n"
"	margin: 0px;\n"
"	padding: 0px;\n"
"}")));
        verticalLayout_8 = new QVBoxLayout(frameBtUpDown);
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        pushButtonCUp = new QPushButton(frameBtUpDown);
        pushButtonCUp->setObjectName(QString::fromUtf8("pushButtonCUp"));
        pushButtonCUp->setProperty("styleSheet", QVariant(QString::fromUtf8("QPushButton\n"
"{\n"
"file-icon: url(file.png);\n"
"}")));

        verticalLayout_8->addWidget(pushButtonCUp);

        pushButtonCDown = new QPushButton(frameBtUpDown);
        pushButtonCDown->setObjectName(QString::fromUtf8("pushButtonCDown"));

        verticalLayout_8->addWidget(pushButtonCDown);


        horizontalLayout_7->addWidget(frameBtUpDown);


        horizontalLayout_3->addWidget(frameBoxId);

        lineEditDescricaoClassificacao = new QLineEdit(groupBox);
        lineEditDescricaoClassificacao->setObjectName(QString::fromUtf8("lineEditDescricaoClassificacao"));
        lineEditDescricaoClassificacao->setProperty("readOnly", QVariant(true));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEditDescricaoClassificacao->sizePolicy().hasHeightForWidth());
        lineEditDescricaoClassificacao->setProperty("sizePolicy", QVariant(sizePolicy1));

        horizontalLayout_3->addWidget(lineEditDescricaoClassificacao);

        pushButtonSelecionarClassificacao = new QPushButton(groupBox);
        pushButtonSelecionarClassificacao->setObjectName(QString::fromUtf8("pushButtonSelecionarClassificacao"));
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("user-trash")));
        pushButtonSelecionarClassificacao->setProperty("icon", QVariant(icon));
        pushButtonSelecionarClassificacao->setProperty("minimumSize", QVariant(QSize(10, 0)));
        pushButtonSelecionarClassificacao->setProperty("maximumSize", QVariant(QSize(30, 16777215)));

        horizontalLayout_3->addWidget(pushButtonSelecionarClassificacao);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 0);
        labelIdMaterial = new QLabel(groupBox);
        labelIdMaterial->setObjectName(QString::fromUtf8("labelIdMaterial"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelIdMaterial->sizePolicy().hasHeightForWidth());
        labelIdMaterial->setProperty("sizePolicy", QVariant(sizePolicy2));

        horizontalLayout->addWidget(labelIdMaterial);

        spinBoxIdMaterial = new QSpinBox(groupBox);
        spinBoxIdMaterial->setObjectName(QString::fromUtf8("spinBoxIdMaterial"));
        spinBoxIdMaterial->setProperty("readOnly", QVariant(false));

        horizontalLayout->addWidget(spinBoxIdMaterial);

        labelDescricaoMaterial = new QLabel(groupBox);
        labelDescricaoMaterial->setObjectName(QString::fromUtf8("labelDescricaoMaterial"));

        horizontalLayout->addWidget(labelDescricaoMaterial);

        lineEditDescricaoMaterial = new QLineEdit(groupBox);
        lineEditDescricaoMaterial->setObjectName(QString::fromUtf8("lineEditDescricaoMaterial"));

        horizontalLayout->addWidget(lineEditDescricaoMaterial);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 0);
        labelUnidadeEstoque = new QLabel(groupBox);
        labelUnidadeEstoque->setObjectName(QString::fromUtf8("labelUnidadeEstoque"));
        sizePolicy2.setHeightForWidth(labelUnidadeEstoque->sizePolicy().hasHeightForWidth());
        labelUnidadeEstoque->setProperty("sizePolicy", QVariant(sizePolicy2));

        horizontalLayout_2->addWidget(labelUnidadeEstoque);

        comboBoxUnidadeEstoque = new QComboBox(groupBox);
        comboBoxUnidadeEstoque->setObjectName(QString::fromUtf8("comboBoxUnidadeEstoque"));
        sizePolicy.setHeightForWidth(comboBoxUnidadeEstoque->sizePolicy().hasHeightForWidth());
        comboBoxUnidadeEstoque->setProperty("sizePolicy", QVariant(sizePolicy));
        comboBoxUnidadeEstoque->setProperty("minimumSize", QVariant(QSize(50, 0)));

        horizontalLayout_2->addWidget(comboBoxUnidadeEstoque);

        labelUnidadeComercial = new QLabel(groupBox);
        labelUnidadeComercial->setObjectName(QString::fromUtf8("labelUnidadeComercial"));
        sizePolicy2.setHeightForWidth(labelUnidadeComercial->sizePolicy().hasHeightForWidth());
        labelUnidadeComercial->setProperty("sizePolicy", QVariant(sizePolicy2));

        horizontalLayout_2->addWidget(labelUnidadeComercial);

        comboBoxUnidadeComercial = new QComboBox(groupBox);
        comboBoxUnidadeComercial->setObjectName(QString::fromUtf8("comboBoxUnidadeComercial"));
        sizePolicy.setHeightForWidth(comboBoxUnidadeComercial->sizePolicy().hasHeightForWidth());
        comboBoxUnidadeComercial->setProperty("sizePolicy", QVariant(sizePolicy));
        comboBoxUnidadeComercial->setProperty("minimumSize", QVariant(QSize(50, 0)));

        horizontalLayout_2->addWidget(comboBoxUnidadeComercial);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, -1, -1, 0);
        labelPlanoConta = new QLabel(groupBox);
        labelPlanoConta->setObjectName(QString::fromUtf8("labelPlanoConta"));

        horizontalLayout_4->addWidget(labelPlanoConta);

        frameBoxId_2 = new QFrame(groupBox);
        frameBoxId_2->setObjectName(QString::fromUtf8("frameBoxId_2"));
        frameBoxId_2->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        frameBoxId_2->setProperty("frameShadow", QVariant(QFrame::Raised));
        frameBoxId_2->setProperty("minimumSize", QVariant(QSize(0, 0)));
        frameBoxId_2->setProperty("maximumSize", QVariant(QSize(70, 16777215)));
        horizontalLayout_8 = new QHBoxLayout(frameBoxId_2);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        lineEditIdPlanoConta = new QLineEdit(frameBoxId_2);
        lineEditIdPlanoConta->setObjectName(QString::fromUtf8("lineEditIdPlanoConta"));
        sizePolicy.setHeightForWidth(lineEditIdPlanoConta->sizePolicy().hasHeightForWidth());
        lineEditIdPlanoConta->setProperty("sizePolicy", QVariant(sizePolicy));

        horizontalLayout_8->addWidget(lineEditIdPlanoConta);

        frameBtUpDown_2 = new QFrame(frameBoxId_2);
        frameBtUpDown_2->setObjectName(QString::fromUtf8("frameBtUpDown_2"));
        frameBtUpDown_2->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        frameBtUpDown_2->setProperty("frameShadow", QVariant(QFrame::Raised));
        frameBtUpDown_2->setProperty("styleSheet", QVariant(QString::fromUtf8("QFrame\n"
"{\n"
"	margin: 0px;\n"
"	padding: 0px;\n"
"}\n"
"QPushButton\n"
"{\n"
"	\n"
"	margin: 0px;\n"
"	padding: 0px;\n"
"}")));
        verticalLayout_9 = new QVBoxLayout(frameBtUpDown_2);
        verticalLayout_9->setSpacing(0);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        pushButtonPUp = new QPushButton(frameBtUpDown_2);
        pushButtonPUp->setObjectName(QString::fromUtf8("pushButtonPUp"));
        pushButtonPUp->setProperty("styleSheet", QVariant(QString::fromUtf8("QPushButton\n"
"{\n"
"file-icon: url(file.png);\n"
"}")));

        verticalLayout_9->addWidget(pushButtonPUp);

        pushButtonPDown = new QPushButton(frameBtUpDown_2);
        pushButtonPDown->setObjectName(QString::fromUtf8("pushButtonPDown"));

        verticalLayout_9->addWidget(pushButtonPDown);


        horizontalLayout_8->addWidget(frameBtUpDown_2);


        horizontalLayout_4->addWidget(frameBoxId_2);

        lineEditDescricaoPlanoConta = new QLineEdit(groupBox);
        lineEditDescricaoPlanoConta->setObjectName(QString::fromUtf8("lineEditDescricaoPlanoConta"));
        lineEditDescricaoPlanoConta->setProperty("readOnly", QVariant(true));

        horizontalLayout_4->addWidget(lineEditDescricaoPlanoConta);

        pushButtonSelecionarPlanoConta = new QPushButton(groupBox);
        pushButtonSelecionarPlanoConta->setObjectName(QString::fromUtf8("pushButtonSelecionarPlanoConta"));
        pushButtonSelecionarPlanoConta->setProperty("maximumSize", QVariant(QSize(30, 16777215)));

        horizontalLayout_4->addWidget(pushButtonSelecionarPlanoConta);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_4);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        verticalLayout_4->addWidget(subFrameInformaoesGerais);


        verticalLayout_7->addWidget(frameInformacoesGerais);

        frameInformacoesMaterialFracionado = new QFrame(frameFormulario);
        frameInformacoesMaterialFracionado->setObjectName(QString::fromUtf8("frameInformacoesMaterialFracionado"));
        frameInformacoesMaterialFracionado->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        frameInformacoesMaterialFracionado->setProperty("frameShadow", QVariant(QFrame::Raised));
        frameInformacoesMaterialFracionado->setProperty("styleSheet", QVariant(QString::fromUtf8("QFrame#frameInformacoesMaterialFracionado\n"
"{\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 18px;\n"
"	border-top-right-radius: 18px;\n"
"	border-bottom-left-radius: 15px;\n"
"	border-bottom-right-radius: 15px;\n"
"}")));
        verticalLayout_5 = new QVBoxLayout(frameInformacoesMaterialFracionado);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 15);
        pushButtonTituloInformacoesFracionado = new QPushButton(frameInformacoesMaterialFracionado);
        pushButtonTituloInformacoesFracionado->setObjectName(QString::fromUtf8("pushButtonTituloInformacoesFracionado"));
        pushButtonTituloInformacoesFracionado->setProperty("styleSheet", QVariant(QString::fromUtf8("")));

        verticalLayout_5->addWidget(pushButtonTituloInformacoesFracionado);

        subFrameInformacoesMaterialFracionado = new QFrame(frameInformacoesMaterialFracionado);
        subFrameInformacoesMaterialFracionado->setObjectName(QString::fromUtf8("subFrameInformacoesMaterialFracionado"));
        subFrameInformacoesMaterialFracionado->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        subFrameInformacoesMaterialFracionado->setProperty("frameShadow", QVariant(QFrame::Raised));
        gridLayout_2 = new QGridLayout(subFrameInformacoesMaterialFracionado);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(9, 9, 9, 9);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 6, -1, -1);
        pushButtonAdicionarRegistro = new QPushButton(subFrameInformacoesMaterialFracionado);
        pushButtonAdicionarRegistro->setObjectName(QString::fromUtf8("pushButtonAdicionarRegistro"));
        pushButtonAdicionarRegistro->setProperty("styleSheet", QVariant(QString::fromUtf8("QPushButton\n"
"{\n"
"	border: 1px solid rgba(0, 0, 0, 85);\n"
"	border-radius: 8px;\n"
"	border-right: 2px solid rgba(0, 0, 0, 185);\n"
"	border-bottom: 2px solid rgba(0, 0, 0, 185);\n"
"  background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(35, 84, 156, 125), stop:1 rgba(58, 134, 255, 125));\n"
"  font-size: 13px;\n"
"	height: 23px;\n"
"  width: 65px;\n"
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
"}")));

        horizontalLayout_5->addWidget(pushButtonAdicionarRegistro);

        pushButtonGravarRegistro = new QPushButton(subFrameInformacoesMaterialFracionado);
        pushButtonGravarRegistro->setObjectName(QString::fromUtf8("pushButtonGravarRegistro"));
        pushButtonGravarRegistro->setProperty("styleSheet", QVariant(QString::fromUtf8("QPushButton\n"
"{\n"
"	border: 1px solid rgba(0, 0, 0, 85);\n"
"	border-radius: 8px;\n"
"	border-right: 2px solid rgba(0, 0, 0, 185);\n"
"	border-bottom: 2px solid rgba(0, 0, 0, 185);\n"
"  background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(35, 84, 156, 125), stop:1 rgba(58, 134, 255, 125));\n"
"  font-size: 13px;\n"
"	height: 23px;\n"
"  width: 65px;\n"
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
"}")));

        horizontalLayout_5->addWidget(pushButtonGravarRegistro);

        pushButtonExcluirRegistro = new QPushButton(subFrameInformacoesMaterialFracionado);
        pushButtonExcluirRegistro->setObjectName(QString::fromUtf8("pushButtonExcluirRegistro"));
        pushButtonExcluirRegistro->setProperty("styleSheet", QVariant(QString::fromUtf8("QPushButton\n"
"{\n"
"	border: 1px solid rgba(0, 0, 0, 85);\n"
"	border-radius: 8px;\n"
"	border-right: 2px solid rgba(0, 0, 0, 185);\n"
"	border-bottom: 2px solid rgba(0, 0, 0, 185);\n"
" background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(217, 5, 27), stop:1 rgb(253, 183, 186));\n"
"  font-size: 13px;\n"
"	height: 23px;\n"
"  width: 65px;\n"
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
"		background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(255, 85, 0), stop:1 rgba(255, 255, 255, 255));\n"
"}")));

        horizontalLayout_5->addWidget(pushButtonExcluirRegistro);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        gridLayout_2->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        tableView = new QTableView(subFrameInformacoesMaterialFracionado);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout_2->addWidget(tableView, 1, 0, 1, 1);


        verticalLayout_5->addWidget(subFrameInformacoesMaterialFracionado);


        verticalLayout_7->addWidget(frameInformacoesMaterialFracionado);


        verticalLayout_2->addWidget(frameFormulario);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(FormCadastrarMateriais);

        QMetaObject::connectSlotsByName(FormCadastrarMateriais);
    }  // setupUi

    void retranslateUi(QWidget *FormCadastrarMateriais)
    {
        FormCadastrarMateriais->setProperty("windowTitle", QVariant(QApplication::translate("FormCadastrarMateriais", "FormCadastrarMateriais", nullptr)));
        labelTituloFormulario->setProperty("text", QVariant(QApplication::translate("FormCadastrarMateriais", "Formul\303\241rio para cadastrar materiais", nullptr)));
        pushButtonNovoFormulario->setProperty("text", QVariant(QApplication::translate("FormCadastrarMateriais", "Novo", nullptr)));
        pushButtonPesquisarFormulario->setProperty("text", QVariant(QApplication::translate("FormCadastrarMateriais", "Pesquisar", nullptr)));
        pushButtonSalvarFormulario->setProperty("text", QVariant(QApplication::translate("FormCadastrarMateriais", "Salvar", nullptr)));
        pushButtonLimparFormulario->setProperty("text", QVariant(QApplication::translate("FormCadastrarMateriais", "Limpar", nullptr)));
        pushButtonRemoverFormulario->setProperty("text", QVariant(QApplication::translate("FormCadastrarMateriais", "Remover", nullptr)));
        pushButtonTituloInformacoesGerais->setProperty("text", QVariant(QApplication::translate("FormCadastrarMateriais", "Informa\303\247\303\265es gerais", nullptr)));
        groupBox->setProperty("title", QVariant(QString()));
        labelClassificacao->setProperty("text", QVariant(QApplication::translate("FormCadastrarMateriais", "Classifica\303\247\303\243o:", nullptr)));
        pushButtonCUp->setProperty("text", QVariant(QString()));
        pushButtonCDown->setProperty("text", QVariant(QString()));
        pushButtonSelecionarClassificacao->setProperty("text", QVariant(QString()));
        labelIdMaterial->setProperty("text", QVariant(QApplication::translate("FormCadastrarMateriais", "ID:", nullptr)));
        labelDescricaoMaterial->setProperty("text", QVariant(QApplication::translate("FormCadastrarMateriais", "Descri\303\247\303\243o:", nullptr)));
        labelUnidadeEstoque->setProperty("text", QVariant(QApplication::translate("FormCadastrarMateriais", "Unidade de estoque:", nullptr)));
        labelUnidadeComercial->setProperty("text", QVariant(QApplication::translate("FormCadastrarMateriais", "Unidade comercial:", nullptr)));
        labelPlanoConta->setProperty("text", QVariant(QApplication::translate("FormCadastrarMateriais", "Plano de conta:", nullptr)));
        pushButtonPUp->setProperty("text", QVariant(QString()));
        pushButtonPDown->setProperty("text", QVariant(QString()));
        pushButtonSelecionarPlanoConta->setProperty("text", QVariant(QString()));
        pushButtonTituloInformacoesFracionado->setProperty("text", QVariant(QApplication::translate("FormCadastrarMateriais", "Informa\303\247\303\265es do material fracionado", nullptr)));
        pushButtonAdicionarRegistro->setProperty("text", QVariant(QApplication::translate("FormCadastrarMateriais", "Adicionar", nullptr)));
        pushButtonGravarRegistro->setProperty("text", QVariant(QApplication::translate("FormCadastrarMateriais", "Gravar", nullptr)));
        pushButtonExcluirRegistro->setProperty("text", QVariant(QApplication::translate("FormCadastrarMateriais", "Excluir", nullptr)));
    }  // retranslateUi

};

namespace Ui {
    class FormCadastrarMateriais : public Ui_FormCadastrarMateriais {};
}  // namespace Ui

#endif // UI_FORMCADASTRARMATERIAIS_H
