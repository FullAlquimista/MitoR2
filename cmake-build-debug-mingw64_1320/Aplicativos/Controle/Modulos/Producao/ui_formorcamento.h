/********************************************************************************
** Form generated from reading the UI file 'formorcamento.ui'
**
** Created by: CopperSpice User Interface Compiler, Version 1.8.2
**
** WARNING! Any changes made to this file will be lost when the UI file is recompiled
********************************************************************************/

#ifndef UI_FORMORCAMENTO_H
#define UI_FORMORCAMENTO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
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
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_FormOrcamento
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frameFormulario;
    QVBoxLayout *verticalLayout_7;
    QLabel *labelTituloFormulario;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonPesquisaRapida;
    QPushButton *pushButtonNovo;
    QPushButton *pushButtonSalvar;
    QPushButton *pushButtonLimpar;
    QPushButton *pushButtonRemover;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_6;
    QFrame *frameInformacoesGerais;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButtonTituloInformacoesPrincipais;
    QFrame *subFrameInformaoesGerais;
    QGridLayout *gridLayout;
    QGroupBox *groupBoxInformacoesGerais;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_1;
    QLabel *labelFabricante;
    QLineEdit *lineEditFabricante;
    QPushButton *pushButtonPesquisarFabricante;
    QLabel *labelIDFabricante;
    QSpinBox *spinBoxIDFabricante;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelCliente;
    QLineEdit *lineEditCliente;
    QPushButton *pushButtonPesquisarCliente;
    QLabel *labelIDCliente;
    QSpinBox *spinBoxIDCliente;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelTitulo;
    QLineEdit *lineEditTitulo;
    QLabel *labelDataOrcamento;
    QDateEdit *dateEditOrcamento;
    QGroupBox *groupBoxAnexos;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButtonAdicionarAnexo;
    QPushButton *pushButtonBaixarAnexo;
    QPushButton *pushButtonDeletarAnexo;
    QSpacerItem *horizontalSpacer_9;
    QTableView *tableViewAnexos;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *groupBoxImagem;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelImagemProduto;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButtonCarregarImagemProduto;
    QSpacerItem *horizontalSpacer_4;
    QFrame *framePropostas;
    QVBoxLayout *verticalLayout_8;
    QPushButton *pushButtonTituloPropostas;
    QFrame *subFramePropostas;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelIdentificacaoProposta;
    QComboBox *comboBoxIdentificacaoProposta;
    QPushButton *pushButtonAdicionar;
    QPushButton *pushButtonSalvarProposta;
    QPushButton *pushButtonRemoverProposta;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_9;
    QLabel *labelTipoProposta;
    QComboBox *comboBoxTipoProposta;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelNumeroOrcamento;
    QLineEdit *lineEditNumeroOrcamento;
    QLabel *labelDataProposta;
    QDateEdit *dateEditDataProposta;
    QLabel *labelProducaoHoraria;
    QSpinBox *spinBoxProducaoHoraria;
    QLabel *labelPPM;
    QSpacerItem *horizontalSpacer_5;
    QLabel *labelDescricao;
    QTextEdit *textEditDescricao;
    QHBoxLayout *horizontalLayout_11;
    QLabel *labelItens;
    QPushButton *pushButtonAdicionarItem;
    QPushButton *pushButtonRemoverItem;
    QSpacerItem *horizontalSpacer_10;
    QTableView *tableViewItens;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labelValorTotal;
    QDoubleSpinBox *doubleSpinBoxValorTotal;
    QLabel *labelPrazoEntrega;
    QSpinBox *spinBoxPrazoEntrega;
    QLabel *labelDiasUteis;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBoxAprovacaoProposta;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelNumeroPedido;
    QLineEdit *lineEditNumeroPedido;
    QLabel *labelDataAprovacao;
    QDateEdit *dateEditDataAprovacao;
    QPushButton *pushButtonAprovarProposta;
    QPushButton *pushButtonCancelarAprovacao;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_1;

    void setupUi(QDialog *FormOrcamento)
    {
        if (FormOrcamento->objectName().isEmpty())
            FormOrcamento->setObjectName(QString::fromUtf8("FormOrcamento"));
        FormOrcamento->resize(923, 966);
        verticalLayout = new QVBoxLayout(FormOrcamento);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frameFormulario = new QFrame(FormOrcamento);
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

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 6, -1, 6);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonPesquisaRapida = new QPushButton(frameFormulario);
        pushButtonPesquisaRapida->setObjectName(QString::fromUtf8("pushButtonPesquisaRapida"));

        horizontalLayout->addWidget(pushButtonPesquisaRapida);

        pushButtonNovo = new QPushButton(frameFormulario);
        pushButtonNovo->setObjectName(QString::fromUtf8("pushButtonNovo"));

        horizontalLayout->addWidget(pushButtonNovo);

        pushButtonSalvar = new QPushButton(frameFormulario);
        pushButtonSalvar->setObjectName(QString::fromUtf8("pushButtonSalvar"));

        horizontalLayout->addWidget(pushButtonSalvar);

        pushButtonLimpar = new QPushButton(frameFormulario);
        pushButtonLimpar->setObjectName(QString::fromUtf8("pushButtonLimpar"));

        horizontalLayout->addWidget(pushButtonLimpar);

        pushButtonRemover = new QPushButton(frameFormulario);
        pushButtonRemover->setObjectName(QString::fromUtf8("pushButtonRemover"));

        horizontalLayout->addWidget(pushButtonRemover);


        verticalLayout_7->addLayout(horizontalLayout);

        scrollArea = new QScrollArea(frameFormulario);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setProperty("widgetResizable", QVariant(true));
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setProperty("geometry", QVariant(QRect(0, 0, 901, 853)));
        verticalLayout_6 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
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
        pushButtonTituloInformacoesPrincipais = new QPushButton(frameInformacoesGerais);
        pushButtonTituloInformacoesPrincipais->setObjectName(QString::fromUtf8("pushButtonTituloInformacoesPrincipais"));
        pushButtonTituloInformacoesPrincipais->setProperty("styleSheet", QVariant(QString::fromUtf8("QPushButton#pushButtonTituloInformacoesPrincipais {\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 15px;\n"
"	border-top-right-radius: 15px;\n"
"	background-color: #859901;\n"
"	padding: 5px 0px;\n"
"	max-height: 25px;\n"
"   font-size: 14px;\n"
"}")));

        verticalLayout_4->addWidget(pushButtonTituloInformacoesPrincipais);

        subFrameInformaoesGerais = new QFrame(frameInformacoesGerais);
        subFrameInformaoesGerais->setObjectName(QString::fromUtf8("subFrameInformaoesGerais"));
        subFrameInformaoesGerais->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        subFrameInformaoesGerais->setProperty("frameShadow", QVariant(QFrame::Raised));
        gridLayout = new QGridLayout(subFrameInformaoesGerais);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);
        groupBoxInformacoesGerais = new QGroupBox(subFrameInformaoesGerais);
        groupBoxInformacoesGerais->setObjectName(QString::fromUtf8("groupBoxInformacoesGerais"));
        verticalLayout_5 = new QVBoxLayout(groupBoxInformacoesGerais);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(3, 3, 3, 3);
        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
        labelFabricante = new QLabel(groupBoxInformacoesGerais);
        labelFabricante->setObjectName(QString::fromUtf8("labelFabricante"));
        labelFabricante->setProperty("alignment", QVariant(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter));
        labelFabricante->setProperty("minimumSize", QVariant(QSize(0, 0)));

        horizontalLayout_1->addWidget(labelFabricante);

        lineEditFabricante = new QLineEdit(groupBoxInformacoesGerais);
        lineEditFabricante->setObjectName(QString::fromUtf8("lineEditFabricante"));

        horizontalLayout_1->addWidget(lineEditFabricante);

        pushButtonPesquisarFabricante = new QPushButton(groupBoxInformacoesGerais);
        pushButtonPesquisarFabricante->setObjectName(QString::fromUtf8("pushButtonPesquisarFabricante"));
        pushButtonPesquisarFabricante->setProperty("maximumSize", QVariant(QSize(25, 16777215)));

        horizontalLayout_1->addWidget(pushButtonPesquisarFabricante);

        labelIDFabricante = new QLabel(groupBoxInformacoesGerais);
        labelIDFabricante->setObjectName(QString::fromUtf8("labelIDFabricante"));

        horizontalLayout_1->addWidget(labelIDFabricante);

        spinBoxIDFabricante = new QSpinBox(groupBoxInformacoesGerais);
        spinBoxIDFabricante->setObjectName(QString::fromUtf8("spinBoxIDFabricante"));
        spinBoxIDFabricante->setProperty("readOnly", QVariant(true));

        horizontalLayout_1->addWidget(spinBoxIDFabricante);


        verticalLayout_5->addLayout(horizontalLayout_1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelCliente = new QLabel(groupBoxInformacoesGerais);
        labelCliente->setObjectName(QString::fromUtf8("labelCliente"));
        labelCliente->setProperty("alignment", QVariant(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter));
        labelCliente->setProperty("minimumSize", QVariant(QSize(55, 0)));

        horizontalLayout_2->addWidget(labelCliente);

        lineEditCliente = new QLineEdit(groupBoxInformacoesGerais);
        lineEditCliente->setObjectName(QString::fromUtf8("lineEditCliente"));

        horizontalLayout_2->addWidget(lineEditCliente);

        pushButtonPesquisarCliente = new QPushButton(groupBoxInformacoesGerais);
        pushButtonPesquisarCliente->setObjectName(QString::fromUtf8("pushButtonPesquisarCliente"));
        pushButtonPesquisarCliente->setProperty("maximumSize", QVariant(QSize(25, 16777215)));

        horizontalLayout_2->addWidget(pushButtonPesquisarCliente);

        labelIDCliente = new QLabel(groupBoxInformacoesGerais);
        labelIDCliente->setObjectName(QString::fromUtf8("labelIDCliente"));

        horizontalLayout_2->addWidget(labelIDCliente);

        spinBoxIDCliente = new QSpinBox(groupBoxInformacoesGerais);
        spinBoxIDCliente->setObjectName(QString::fromUtf8("spinBoxIDCliente"));
        spinBoxIDCliente->setProperty("readOnly", QVariant(true));

        horizontalLayout_2->addWidget(spinBoxIDCliente);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelTitulo = new QLabel(groupBoxInformacoesGerais);
        labelTitulo->setObjectName(QString::fromUtf8("labelTitulo"));
        labelTitulo->setProperty("alignment", QVariant(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter));
        labelTitulo->setProperty("minimumSize", QVariant(QSize(55, 0)));
        labelTitulo->setProperty("layoutDirection", QVariant(Qt::RightToLeft));

        horizontalLayout_3->addWidget(labelTitulo);

        lineEditTitulo = new QLineEdit(groupBoxInformacoesGerais);
        lineEditTitulo->setObjectName(QString::fromUtf8("lineEditTitulo"));

        horizontalLayout_3->addWidget(lineEditTitulo);

        labelDataOrcamento = new QLabel(groupBoxInformacoesGerais);
        labelDataOrcamento->setObjectName(QString::fromUtf8("labelDataOrcamento"));

        horizontalLayout_3->addWidget(labelDataOrcamento);

        dateEditOrcamento = new QDateEdit(groupBoxInformacoesGerais);
        dateEditOrcamento->setObjectName(QString::fromUtf8("dateEditOrcamento"));

        horizontalLayout_3->addWidget(dateEditOrcamento);


        verticalLayout_5->addLayout(horizontalLayout_3);

        groupBoxAnexos = new QGroupBox(groupBoxInformacoesGerais);
        groupBoxAnexos->setObjectName(QString::fromUtf8("groupBoxAnexos"));
        verticalLayout_10 = new QVBoxLayout(groupBoxAnexos);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(-1, -1, -1, 6);
        pushButtonAdicionarAnexo = new QPushButton(groupBoxAnexos);
        pushButtonAdicionarAnexo->setObjectName(QString::fromUtf8("pushButtonAdicionarAnexo"));

        horizontalLayout_10->addWidget(pushButtonAdicionarAnexo);

        pushButtonBaixarAnexo = new QPushButton(groupBoxAnexos);
        pushButtonBaixarAnexo->setObjectName(QString::fromUtf8("pushButtonBaixarAnexo"));

        horizontalLayout_10->addWidget(pushButtonBaixarAnexo);

        pushButtonDeletarAnexo = new QPushButton(groupBoxAnexos);
        pushButtonDeletarAnexo->setObjectName(QString::fromUtf8("pushButtonDeletarAnexo"));

        horizontalLayout_10->addWidget(pushButtonDeletarAnexo);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_9);


        verticalLayout_10->addLayout(horizontalLayout_10);

        tableViewAnexos = new QTableView(groupBoxAnexos);
        tableViewAnexos->setObjectName(QString::fromUtf8("tableViewAnexos"));

        verticalLayout_10->addWidget(tableViewAnexos);


        verticalLayout_5->addWidget(groupBoxAnexos);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);

        groupBoxAnexos->raise();

        gridLayout->addWidget(groupBoxInformacoesGerais, 0, 0, 1, 1);

        groupBoxImagem = new QGroupBox(subFrameInformaoesGerais);
        groupBoxImagem->setObjectName(QString::fromUtf8("groupBoxImagem"));
        groupBoxImagem->setProperty("maximumSize", QVariant(QSize(190, 16777215)));
        verticalLayout_3 = new QVBoxLayout(groupBoxImagem);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(3, 3, 3, 3);
        labelImagemProduto = new QLabel(groupBoxImagem);
        labelImagemProduto->setObjectName(QString::fromUtf8("labelImagemProduto"));
        labelImagemProduto->setProperty("scaledContents", QVariant(false));
        labelImagemProduto->setProperty("pixmap", QVariant(true));
        labelImagemProduto->setProperty("alignment", QVariant(Qt::AlignCenter));
        labelImagemProduto->setProperty("frameShape", QVariant(QFrame::Box));
        labelImagemProduto->setProperty("frameShadow", QVariant(QFrame::Sunken));
        labelImagemProduto->setProperty("minimumSize", QVariant(QSize(180, 180)));
        labelImagemProduto->setProperty("maximumSize", QVariant(QSize(180, 180)));

        verticalLayout_3->addWidget(labelImagemProduto);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, 6, -1, 6);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        pushButtonCarregarImagemProduto = new QPushButton(groupBoxImagem);
        pushButtonCarregarImagemProduto->setObjectName(QString::fromUtf8("pushButtonCarregarImagemProduto"));

        horizontalLayout_6->addWidget(pushButtonCarregarImagemProduto);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_6);


        gridLayout->addWidget(groupBoxImagem, 0, 1, 1, 1);


        verticalLayout_4->addWidget(subFrameInformaoesGerais);


        verticalLayout_6->addWidget(frameInformacoesGerais);

        framePropostas = new QFrame(scrollAreaWidgetContents);
        framePropostas->setObjectName(QString::fromUtf8("framePropostas"));
        framePropostas->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        framePropostas->setProperty("frameShadow", QVariant(QFrame::Raised));
        framePropostas->setProperty("styleSheet", QVariant(QString::fromUtf8("QFrame#framePropostas\n"
"{\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 18px;\n"
"	border-top-right-radius: 18px;\n"
"	border-bottom-left-radius: 15px;\n"
"	border-bottom-right-radius: 15px;\n"
"}")));
        verticalLayout_8 = new QVBoxLayout(framePropostas);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 15);
        pushButtonTituloPropostas = new QPushButton(framePropostas);
        pushButtonTituloPropostas->setObjectName(QString::fromUtf8("pushButtonTituloPropostas"));
        pushButtonTituloPropostas->setProperty("styleSheet", QVariant(QString::fromUtf8("QPushButton#pushButtonTituloPropostas {\n"
"	border: 1px solid #FF17365D;\n"
"	border-top-left-radius: 15px;\n"
"	border-top-right-radius: 15px;\n"
"	background-color: rgba(182, 182, 91, 120);\n"
"	padding: 5px 0px;\n"
"	max-height: 25px;\n"
"    font-size: 14px;\n"
"}")));

        verticalLayout_8->addWidget(pushButtonTituloPropostas);

        subFramePropostas = new QFrame(framePropostas);
        subFramePropostas->setObjectName(QString::fromUtf8("subFramePropostas"));
        subFramePropostas->setProperty("frameShape", QVariant(QFrame::StyledPanel));
        subFramePropostas->setProperty("frameShadow", QVariant(QFrame::Raised));
        verticalLayout_2 = new QVBoxLayout(subFramePropostas);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(-1, 6, -1, -1);
        labelIdentificacaoProposta = new QLabel(subFramePropostas);
        labelIdentificacaoProposta->setObjectName(QString::fromUtf8("labelIdentificacaoProposta"));
        labelIdentificacaoProposta->setProperty("alignment", QVariant(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelIdentificacaoProposta->sizePolicy().hasHeightForWidth());
        labelIdentificacaoProposta->setProperty("sizePolicy", QVariant(sizePolicy));
        labelIdentificacaoProposta->setProperty("minimumSize", QVariant(QSize(0, 0)));

        horizontalLayout_7->addWidget(labelIdentificacaoProposta);

        comboBoxIdentificacaoProposta = new QComboBox(subFramePropostas);
        comboBoxIdentificacaoProposta->setObjectName(QString::fromUtf8("comboBoxIdentificacaoProposta"));
        comboBoxIdentificacaoProposta->setProperty("minimumSize", QVariant(QSize(150, 0)));

        horizontalLayout_7->addWidget(comboBoxIdentificacaoProposta);

        pushButtonAdicionar = new QPushButton(subFramePropostas);
        pushButtonAdicionar->setObjectName(QString::fromUtf8("pushButtonAdicionar"));

        horizontalLayout_7->addWidget(pushButtonAdicionar);

        pushButtonSalvarProposta = new QPushButton(subFramePropostas);
        pushButtonSalvarProposta->setObjectName(QString::fromUtf8("pushButtonSalvarProposta"));

        horizontalLayout_7->addWidget(pushButtonSalvarProposta);

        pushButtonRemoverProposta = new QPushButton(subFramePropostas);
        pushButtonRemoverProposta->setObjectName(QString::fromUtf8("pushButtonRemoverProposta"));

        horizontalLayout_7->addWidget(pushButtonRemoverProposta);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(-1, 6, -1, 6);
        labelTipoProposta = new QLabel(subFramePropostas);
        labelTipoProposta->setObjectName(QString::fromUtf8("labelTipoProposta"));
        labelTipoProposta->setProperty("alignment", QVariant(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter));
        labelTipoProposta->setProperty("minimumSize", QVariant(QSize(100, 0)));

        horizontalLayout_9->addWidget(labelTipoProposta);

        comboBoxTipoProposta = new QComboBox(subFramePropostas);
        comboBoxTipoProposta->setObjectName(QString::fromUtf8("comboBoxTipoProposta"));
        comboBoxTipoProposta->setProperty("minimumSize", QVariant(QSize(200, 0)));

        horizontalLayout_9->addWidget(comboBoxTipoProposta);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_8);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 6, -1, -1);
        labelNumeroOrcamento = new QLabel(subFramePropostas);
        labelNumeroOrcamento->setObjectName(QString::fromUtf8("labelNumeroOrcamento"));

        horizontalLayout_4->addWidget(labelNumeroOrcamento);

        lineEditNumeroOrcamento = new QLineEdit(subFramePropostas);
        lineEditNumeroOrcamento->setObjectName(QString::fromUtf8("lineEditNumeroOrcamento"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEditNumeroOrcamento->sizePolicy().hasHeightForWidth());
        lineEditNumeroOrcamento->setProperty("sizePolicy", QVariant(sizePolicy1));

        horizontalLayout_4->addWidget(lineEditNumeroOrcamento);

        labelDataProposta = new QLabel(subFramePropostas);
        labelDataProposta->setObjectName(QString::fromUtf8("labelDataProposta"));

        horizontalLayout_4->addWidget(labelDataProposta);

        dateEditDataProposta = new QDateEdit(subFramePropostas);
        dateEditDataProposta->setObjectName(QString::fromUtf8("dateEditDataProposta"));

        horizontalLayout_4->addWidget(dateEditDataProposta);

        labelProducaoHoraria = new QLabel(subFramePropostas);
        labelProducaoHoraria->setObjectName(QString::fromUtf8("labelProducaoHoraria"));

        horizontalLayout_4->addWidget(labelProducaoHoraria);

        spinBoxProducaoHoraria = new QSpinBox(subFramePropostas);
        spinBoxProducaoHoraria->setObjectName(QString::fromUtf8("spinBoxProducaoHoraria"));
        spinBoxProducaoHoraria->setProperty("maximum", QVariant(999999));

        horizontalLayout_4->addWidget(spinBoxProducaoHoraria);

        labelPPM = new QLabel(subFramePropostas);
        labelPPM->setObjectName(QString::fromUtf8("labelPPM"));

        horizontalLayout_4->addWidget(labelPPM);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_4);

        labelDescricao = new QLabel(subFramePropostas);
        labelDescricao->setObjectName(QString::fromUtf8("labelDescricao"));

        verticalLayout_2->addWidget(labelDescricao);

        textEditDescricao = new QTextEdit(subFramePropostas);
        textEditDescricao->setObjectName(QString::fromUtf8("textEditDescricao"));
        textEditDescricao->setProperty("maximumSize", QVariant(QSize(16777215, 100)));

        verticalLayout_2->addWidget(textEditDescricao);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(2);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(-1, 3, -1, 0);
        labelItens = new QLabel(subFramePropostas);
        labelItens->setObjectName(QString::fromUtf8("labelItens"));

        horizontalLayout_11->addWidget(labelItens);

        pushButtonAdicionarItem = new QPushButton(subFramePropostas);
        pushButtonAdicionarItem->setObjectName(QString::fromUtf8("pushButtonAdicionarItem"));
        pushButtonAdicionarItem->setProperty("maximumSize", QVariant(QSize(37, 30)));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setUnderline(false);
        font1.setWeight(75);
        font1.setStrikeOut(false);
        font1.setKerning(true);
        pushButtonAdicionarItem->setProperty("font", QVariant(font1));

        horizontalLayout_11->addWidget(pushButtonAdicionarItem);

        pushButtonRemoverItem = new QPushButton(subFramePropostas);
        pushButtonRemoverItem->setObjectName(QString::fromUtf8("pushButtonRemoverItem"));
        pushButtonRemoverItem->setProperty("maximumSize", QVariant(QSize(37, 30)));
        QFont font2;
        font2.setPointSize(15);
        font2.setBold(true);
        font2.setWeight(75);
        pushButtonRemoverItem->setProperty("font", QVariant(font2));

        horizontalLayout_11->addWidget(pushButtonRemoverItem);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_10);


        verticalLayout_2->addLayout(horizontalLayout_11);

        tableViewItens = new QTableView(subFramePropostas);
        tableViewItens->setObjectName(QString::fromUtf8("tableViewItens"));
        tableViewItens->setProperty("minimumSize", QVariant(QSize(0, 100)));

        verticalLayout_2->addWidget(tableViewItens);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(-1, 6, -1, -1);
        labelValorTotal = new QLabel(subFramePropostas);
        labelValorTotal->setObjectName(QString::fromUtf8("labelValorTotal"));

        horizontalLayout_8->addWidget(labelValorTotal);

        doubleSpinBoxValorTotal = new QDoubleSpinBox(subFramePropostas);
        doubleSpinBoxValorTotal->setObjectName(QString::fromUtf8("doubleSpinBoxValorTotal"));
        doubleSpinBoxValorTotal->setProperty("maximum", QVariant(1e+08));
        doubleSpinBoxValorTotal->setProperty("decimals", QVariant(4));

        horizontalLayout_8->addWidget(doubleSpinBoxValorTotal);

        labelPrazoEntrega = new QLabel(subFramePropostas);
        labelPrazoEntrega->setObjectName(QString::fromUtf8("labelPrazoEntrega"));

        horizontalLayout_8->addWidget(labelPrazoEntrega);

        spinBoxPrazoEntrega = new QSpinBox(subFramePropostas);
        spinBoxPrazoEntrega->setObjectName(QString::fromUtf8("spinBoxPrazoEntrega"));
        spinBoxPrazoEntrega->setProperty("minimum", QVariant(1));
        spinBoxPrazoEntrega->setProperty("maximum", QVariant(720));

        horizontalLayout_8->addWidget(spinBoxPrazoEntrega);

        labelDiasUteis = new QLabel(subFramePropostas);
        labelDiasUteis->setObjectName(QString::fromUtf8("labelDiasUteis"));

        horizontalLayout_8->addWidget(labelDiasUteis);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_8);

        groupBoxAprovacaoProposta = new QGroupBox(subFramePropostas);
        groupBoxAprovacaoProposta->setObjectName(QString::fromUtf8("groupBoxAprovacaoProposta"));
        verticalLayout_9 = new QVBoxLayout(groupBoxAprovacaoProposta);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 6, -1, -1);
        labelNumeroPedido = new QLabel(groupBoxAprovacaoProposta);
        labelNumeroPedido->setObjectName(QString::fromUtf8("labelNumeroPedido"));

        horizontalLayout_5->addWidget(labelNumeroPedido);

        lineEditNumeroPedido = new QLineEdit(groupBoxAprovacaoProposta);
        lineEditNumeroPedido->setObjectName(QString::fromUtf8("lineEditNumeroPedido"));
        lineEditNumeroPedido->setProperty("maximumSize", QVariant(QSize(290, 16777215)));

        horizontalLayout_5->addWidget(lineEditNumeroPedido);

        labelDataAprovacao = new QLabel(groupBoxAprovacaoProposta);
        labelDataAprovacao->setObjectName(QString::fromUtf8("labelDataAprovacao"));

        horizontalLayout_5->addWidget(labelDataAprovacao);

        dateEditDataAprovacao = new QDateEdit(groupBoxAprovacaoProposta);
        dateEditDataAprovacao->setObjectName(QString::fromUtf8("dateEditDataAprovacao"));

        horizontalLayout_5->addWidget(dateEditDataAprovacao);

        pushButtonAprovarProposta = new QPushButton(groupBoxAprovacaoProposta);
        pushButtonAprovarProposta->setObjectName(QString::fromUtf8("pushButtonAprovarProposta"));

        horizontalLayout_5->addWidget(pushButtonAprovarProposta);

        pushButtonCancelarAprovacao = new QPushButton(groupBoxAprovacaoProposta);
        pushButtonCancelarAprovacao->setObjectName(QString::fromUtf8("pushButtonCancelarAprovacao"));

        horizontalLayout_5->addWidget(pushButtonCancelarAprovacao);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);


        verticalLayout_9->addLayout(horizontalLayout_5);


        verticalLayout_2->addWidget(groupBoxAprovacaoProposta);


        verticalLayout_8->addWidget(subFramePropostas);


        verticalLayout_6->addWidget(framePropostas);

        verticalSpacer_1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_7->addWidget(scrollArea);


        verticalLayout->addWidget(frameFormulario);

        QWidget::setTabOrder(lineEditFabricante, pushButtonPesquisarFabricante);
        QWidget::setTabOrder(pushButtonPesquisarFabricante, lineEditCliente);
        QWidget::setTabOrder(lineEditCliente, pushButtonPesquisarCliente);
        QWidget::setTabOrder(pushButtonPesquisarCliente, lineEditTitulo);
        QWidget::setTabOrder(lineEditTitulo, dateEditOrcamento);
        QWidget::setTabOrder(dateEditOrcamento, pushButtonCarregarImagemProduto);
        QWidget::setTabOrder(pushButtonCarregarImagemProduto, spinBoxIDFabricante);
        QWidget::setTabOrder(spinBoxIDFabricante, spinBoxIDCliente);

        retranslateUi(FormOrcamento);

        QMetaObject::connectSlotsByName(FormOrcamento);
    }  // setupUi

    void retranslateUi(QDialog *FormOrcamento)
    {
        FormOrcamento->setProperty("windowTitle", QVariant(QApplication::translate("FormOrcamento", "Or\303\247amento", nullptr)));
        labelTituloFormulario->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Formul\303\241rio de um or\303\247amento", nullptr)));
        pushButtonPesquisaRapida->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Pesquisa R\303\241pida", nullptr)));
        pushButtonNovo->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Novo", nullptr)));
        pushButtonSalvar->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Salvar", nullptr)));
        pushButtonLimpar->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Limpar", nullptr)));
        pushButtonRemover->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Remover", nullptr)));
        pushButtonTituloInformacoesPrincipais->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Informa\303\247\303\265es principais", nullptr)));
        groupBoxInformacoesGerais->setProperty("title", QVariant(QString()));
        labelFabricante->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Fabricante:", nullptr)));
        pushButtonPesquisarFabricante->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "...", nullptr)));
        labelIDFabricante->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "ID:", nullptr)));
        labelCliente->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Cliente:", nullptr)));
        pushButtonPesquisarCliente->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "...", nullptr)));
        labelIDCliente->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "ID:", nullptr)));
        labelTitulo->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "T\303\255tulo:", nullptr)));
        labelDataOrcamento->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Data:", nullptr)));
        groupBoxAnexos->setProperty("title", QVariant(QApplication::translate("FormOrcamento", "Anexos:", nullptr)));
        pushButtonAdicionarAnexo->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Adicionar", nullptr)));
        pushButtonBaixarAnexo->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Baixar", nullptr)));
        pushButtonDeletarAnexo->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Deletar", nullptr)));
        groupBoxImagem->setProperty("title", QVariant(QApplication::translate("FormOrcamento", "Imagem do produto:", nullptr)));
        labelImagemProduto->setProperty("text", QVariant(QString()));
        pushButtonCarregarImagemProduto->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Trocar Imagem", nullptr)));
        pushButtonTituloPropostas->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Propostas", nullptr)));
        labelIdentificacaoProposta->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Identifica\303\247\303\243o:", nullptr)));
        pushButtonAdicionar->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Adicionar", nullptr)));
        pushButtonSalvarProposta->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Salvar", nullptr)));
        pushButtonRemoverProposta->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Remover", nullptr)));
        labelTipoProposta->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Tipo do or\303\247amento:", nullptr)));
        labelNumeroOrcamento->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "N\303\272mero do or\303\247amento:", nullptr)));
        labelDataProposta->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Data", nullptr)));
        labelProducaoHoraria->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Produ\303\247\303\243o horaria:", nullptr)));
        labelPPM->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "pe\303\247as.", nullptr)));
        labelDescricao->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Descri\303\247\303\243o:", nullptr)));
        labelItens->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Itens:", nullptr)));
        pushButtonAdicionarItem->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "+", nullptr)));
        pushButtonRemoverItem->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "-", nullptr)));
        labelValorTotal->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Valor total:", nullptr)));
        doubleSpinBoxValorTotal->setProperty("prefix", QVariant(QString()));
        labelPrazoEntrega->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Prazo de entrega:", nullptr)));
        labelDiasUteis->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "dias \303\272teis.", nullptr)));
        groupBoxAprovacaoProposta->setProperty("title", QVariant(QApplication::translate("FormOrcamento", "Aprova\303\247\303\243o da proposta:", nullptr)));
        labelNumeroPedido->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Numero do pedido:", nullptr)));
        labelDataAprovacao->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Data aprova\303\247\303\243o:", nullptr)));
        pushButtonAprovarProposta->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Aprovar proposta", nullptr)));
        pushButtonCancelarAprovacao->setProperty("text", QVariant(QApplication::translate("FormOrcamento", "Cancelar aprova\303\247\303\243o", nullptr)));
    }  // retranslateUi

};

namespace Ui {
    class FormOrcamento : public Ui_FormOrcamento {};
}  // namespace Ui

#endif // UI_FORMORCAMENTO_H
