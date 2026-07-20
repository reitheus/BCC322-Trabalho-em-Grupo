/********************************************************************************
** Form generated from reading UI file 'pedidowindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PEDIDOWINDOW_H
#define UI_PEDIDOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PedidoWindow
{
public:
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QLabel *Cliente;
    QLineEdit *txtCliente;
    QLabel *txtproduto_2;
    QComboBox *comboProduto;
    QLabel *txtquantidade_2;
    QSpinBox *spinQuantidade;
    QLabel *lblTitulo;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnVerificar;
    QPushButton *btnAdicionar;
    QHBoxLayout *horizontalLayout_2;
    QLabel *status;
    QLabel *lblStatus;
    QHBoxLayout *horizontalLayout_3;
    QLabel *saldo;
    QLabel *lblSaldo;
    QTableWidget *tableItens;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnRemover;
    QPushButton *btnReservar;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnVoltar;

    void setupUi(QWidget *PedidoWindow)
    {
        if (PedidoWindow->objectName().isEmpty())
            PedidoWindow->setObjectName("PedidoWindow");
        PedidoWindow->resize(541, 429);
        gridLayout = new QGridLayout(PedidoWindow);
        gridLayout->setObjectName("gridLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        Cliente = new QLabel(PedidoWindow);
        Cliente->setObjectName("Cliente");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, Cliente);

        txtCliente = new QLineEdit(PedidoWindow);
        txtCliente->setObjectName("txtCliente");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, txtCliente);

        txtproduto_2 = new QLabel(PedidoWindow);
        txtproduto_2->setObjectName("txtproduto_2");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, txtproduto_2);

        comboProduto = new QComboBox(PedidoWindow);
        comboProduto->setObjectName("comboProduto");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, comboProduto);

        txtquantidade_2 = new QLabel(PedidoWindow);
        txtquantidade_2->setObjectName("txtquantidade_2");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, txtquantidade_2);

        spinQuantidade = new QSpinBox(PedidoWindow);
        spinQuantidade->setObjectName("spinQuantidade");
        spinQuantidade->setMinimum(1);
        spinQuantidade->setMaximum(999);

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, spinQuantidade);

        lblTitulo = new QLabel(PedidoWindow);
        lblTitulo->setObjectName("lblTitulo");
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        lblTitulo->setFont(font);
        lblTitulo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lblTitulo);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnVerificar = new QPushButton(PedidoWindow);
        btnVerificar->setObjectName("btnVerificar");
        btnVerificar->setMaximumSize(QSize(150, 16777215));
        QFont font1;
        font1.setPointSize(13);
        btnVerificar->setFont(font1);

        horizontalLayout->addWidget(btnVerificar);

        btnAdicionar = new QPushButton(PedidoWindow);
        btnAdicionar->setObjectName("btnAdicionar");
        btnAdicionar->setMaximumSize(QSize(150, 16777215));
        btnAdicionar->setFont(font1);

        horizontalLayout->addWidget(btnAdicionar);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        status = new QLabel(PedidoWindow);
        status->setObjectName("status");

        horizontalLayout_2->addWidget(status);

        lblStatus = new QLabel(PedidoWindow);
        lblStatus->setObjectName("lblStatus");

        horizontalLayout_2->addWidget(lblStatus);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        saldo = new QLabel(PedidoWindow);
        saldo->setObjectName("saldo");

        horizontalLayout_3->addWidget(saldo);

        lblSaldo = new QLabel(PedidoWindow);
        lblSaldo->setObjectName("lblSaldo");

        horizontalLayout_3->addWidget(lblSaldo);


        gridLayout->addLayout(horizontalLayout_3, 3, 0, 1, 1);

        tableItens = new QTableWidget(PedidoWindow);
        if (tableItens->columnCount() < 3)
            tableItens->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableItens->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableItens->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableItens->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableItens->setObjectName("tableItens");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableItens->sizePolicy().hasHeightForWidth());
        tableItens->setSizePolicy(sizePolicy);
        tableItens->setTabletTracking(false);
        tableItens->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        tableItens->setAcceptDrops(false);
        tableItens->setFrameShadow(QFrame::Shadow::Sunken);
        tableItens->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        tableItens->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        tableItens->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustIgnored);
        tableItens->setDragEnabled(false);
        tableItens->setDragDropMode(QAbstractItemView::DragDropMode::NoDragDrop);
        tableItens->setDefaultDropAction(Qt::DropAction::IgnoreAction);
        tableItens->setAlternatingRowColors(false);
        tableItens->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
        tableItens->setIconSize(QSize(10, 10));
        tableItens->setShowGrid(true);
        tableItens->setSortingEnabled(false);
        tableItens->setRowCount(0);
        tableItens->setColumnCount(3);
        tableItens->setSupportedDragActions(Qt::DropAction::CopyAction|Qt::DropAction::MoveAction);
        tableItens->horizontalHeader()->setCascadingSectionResizes(false);
        tableItens->horizontalHeader()->setDefaultSectionSize(173);
        tableItens->verticalHeader()->setDefaultSectionSize(32);
        tableItens->verticalHeader()->setProperty("showSortIndicator", QVariant(false));

        gridLayout->addWidget(tableItens, 4, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        btnRemover = new QPushButton(PedidoWindow);
        btnRemover->setObjectName("btnRemover");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(20);
        sizePolicy1.setVerticalStretch(20);
        sizePolicy1.setHeightForWidth(btnRemover->sizePolicy().hasHeightForWidth());
        btnRemover->setSizePolicy(sizePolicy1);
        btnRemover->setMaximumSize(QSize(150, 16777215));
        QFont font2;
        font2.setPointSize(12);
        btnRemover->setFont(font2);

        horizontalLayout_4->addWidget(btnRemover);

        btnReservar = new QPushButton(PedidoWindow);
        btnReservar->setObjectName("btnReservar");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnReservar->sizePolicy().hasHeightForWidth());
        btnReservar->setSizePolicy(sizePolicy2);
        btnReservar->setMaximumSize(QSize(167, 16777215));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Segoe UI")});
        font3.setPointSize(12);
        font3.setWeight(QFont::Medium);
        font3.setKerning(true);
        font3.setHintingPreference(QFont::PreferDefaultHinting);
        btnReservar->setFont(font3);
        btnReservar->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        btnReservar->setAutoFillBackground(false);
        btnReservar->setAutoRepeatDelay(300);
        btnReservar->setAutoDefault(false);

        horizontalLayout_4->addWidget(btnReservar);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        btnVoltar = new QPushButton(PedidoWindow);
        btnVoltar->setObjectName("btnVoltar");
        sizePolicy2.setHeightForWidth(btnVoltar->sizePolicy().hasHeightForWidth());
        btnVoltar->setSizePolicy(sizePolicy2);
        btnVoltar->setMaximumSize(QSize(167, 16777215));
        btnVoltar->setFont(font3);
        btnVoltar->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        btnVoltar->setAutoFillBackground(false);
        btnVoltar->setAutoRepeatDelay(300);
        btnVoltar->setAutoDefault(false);

        horizontalLayout_4->addWidget(btnVoltar);


        gridLayout->addLayout(horizontalLayout_4, 5, 0, 1, 1);


        retranslateUi(PedidoWindow);

        btnReservar->setDefault(false);
        btnVoltar->setDefault(false);


        QMetaObject::connectSlotsByName(PedidoWindow);
    } // setupUi

    void retranslateUi(QWidget *PedidoWindow)
    {
        PedidoWindow->setWindowTitle(QCoreApplication::translate("PedidoWindow", "Form", nullptr));
        Cliente->setText(QCoreApplication::translate("PedidoWindow", "Cliente", nullptr));
        txtproduto_2->setText(QCoreApplication::translate("PedidoWindow", "Produto", nullptr));
        txtquantidade_2->setText(QCoreApplication::translate("PedidoWindow", "Quantidade", nullptr));
        lblTitulo->setText(QCoreApplication::translate("PedidoWindow", "Registrar Pedido", nullptr));
        btnVerificar->setText(QCoreApplication::translate("PedidoWindow", "Verificar Saldo", nullptr));
        btnAdicionar->setText(QCoreApplication::translate("PedidoWindow", "Adicionar Item", nullptr));
        status->setText(QCoreApplication::translate("PedidoWindow", "Status", nullptr));
        lblStatus->setText(QCoreApplication::translate("PedidoWindow", "-----", nullptr));
        saldo->setText(QCoreApplication::translate("PedidoWindow", "Saldo", nullptr));
        lblSaldo->setText(QCoreApplication::translate("PedidoWindow", "-----", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableItens->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PedidoWindow", "Produto", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableItens->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PedidoWindow", "Quantidade", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableItens->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PedidoWindow", "Situa\303\247\303\243o", nullptr));
        btnRemover->setText(QCoreApplication::translate("PedidoWindow", "Remover Item", nullptr));
        btnReservar->setText(QCoreApplication::translate("PedidoWindow", "Confirmar Reserva", nullptr));
        btnVoltar->setText(QCoreApplication::translate("PedidoWindow", "Voltar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PedidoWindow: public Ui_PedidoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PEDIDOWINDOW_H
