/********************************************************************************
** Form generated from reading UI file 'estoquewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ESTOQUEWINDOW_H
#define UI_ESTOQUEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EstoqueWindow
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label;
    QSpacerItem *horizontalSpacer_10;
    QTableWidget *tableEstoque;
    QHBoxLayout *horizontalLayout;
    QLabel *lblProduto;
    QSpacerItem *horizontalSpacer_5;
    QComboBox *cbProduto;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_6;
    QSpinBox *sbQuantidade;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *btnAdicionar;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *btnCadastrarProduto;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *btnVoltar;

    void setupUi(QWidget *EstoqueWindow)
    {
        if (EstoqueWindow->objectName().isEmpty())
            EstoqueWindow->setObjectName("EstoqueWindow");
        EstoqueWindow->resize(794, 415);
        gridLayout = new QGridLayout(EstoqueWindow);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_11);

        label = new QLabel(EstoqueWindow);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        label->setFont(font);
        label->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_5->addWidget(label);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);


        gridLayout->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        tableEstoque = new QTableWidget(EstoqueWindow);
        if (tableEstoque->columnCount() < 2)
            tableEstoque->setColumnCount(2);
        QFont font1;
        font1.setPointSize(12);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font1);
        tableEstoque->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QFont font2;
        font2.setPointSize(9);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font2);
        tableEstoque->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableEstoque->setObjectName("tableEstoque");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableEstoque->sizePolicy().hasHeightForWidth());
        tableEstoque->setSizePolicy(sizePolicy1);
        tableEstoque->setAutoScrollMargin(16);
        tableEstoque->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
        tableEstoque->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectItems);
        tableEstoque->setTextElideMode(Qt::TextElideMode::ElideLeft);
        tableEstoque->setUpdateThreshold(200);
        tableEstoque->horizontalHeader()->setCascadingSectionResizes(false);
        tableEstoque->horizontalHeader()->setMinimumSectionSize(75);
        tableEstoque->horizontalHeader()->setDefaultSectionSize(123);
        tableEstoque->verticalHeader()->setMinimumSectionSize(35);
        tableEstoque->verticalHeader()->setDefaultSectionSize(45);

        gridLayout->addWidget(tableEstoque, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        lblProduto = new QLabel(EstoqueWindow);
        lblProduto->setObjectName("lblProduto");
        lblProduto->setFont(font1);

        horizontalLayout->addWidget(lblProduto);

        horizontalSpacer_5 = new QSpacerItem(85, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        cbProduto = new QComboBox(EstoqueWindow);
        cbProduto->setObjectName("cbProduto");
        cbProduto->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(cbProduto);

        horizontalSpacer = new QSpacerItem(540, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(EstoqueWindow);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFont(font1);

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_6 = new QSpacerItem(55, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        sbQuantidade = new QSpinBox(EstoqueWindow);
        sbQuantidade->setObjectName("sbQuantidade");
        sbQuantidade->setMaximumSize(QSize(100, 16777215));
        sbQuantidade->setMinimum(1);
        sbQuantidade->setMaximum(999);

        horizontalLayout_2->addWidget(sbQuantidade);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        horizontalLayout_2->addLayout(horizontalLayout_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        btnAdicionar = new QPushButton(EstoqueWindow);
        btnAdicionar->setObjectName("btnAdicionar");
        sizePolicy.setHeightForWidth(btnAdicionar->sizePolicy().hasHeightForWidth());
        btnAdicionar->setSizePolicy(sizePolicy);
        btnAdicionar->setMaximumSize(QSize(200, 16777215));
        btnAdicionar->setFont(font1);

        horizontalLayout_4->addWidget(btnAdicionar);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        btnCadastrarProduto = new QPushButton(EstoqueWindow);
        btnCadastrarProduto->setObjectName("btnCadastrarProduto");
        sizePolicy.setHeightForWidth(btnCadastrarProduto->sizePolicy().hasHeightForWidth());
        btnCadastrarProduto->setSizePolicy(sizePolicy);
        btnCadastrarProduto->setMaximumSize(QSize(200, 16777215));
        btnCadastrarProduto->setFont(font1);

        horizontalLayout_4->addWidget(btnCadastrarProduto);

        horizontalSpacer_9 = new QSpacerItem(100, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);

        btnVoltar = new QPushButton(EstoqueWindow);
        btnVoltar->setObjectName("btnVoltar");
        sizePolicy.setHeightForWidth(btnVoltar->sizePolicy().hasHeightForWidth());
        btnVoltar->setSizePolicy(sizePolicy);
        btnVoltar->setMaximumSize(QSize(200, 16777215));
        btnVoltar->setFont(font1);

        horizontalLayout_4->addWidget(btnVoltar);


        gridLayout->addLayout(horizontalLayout_4, 4, 0, 1, 1);


        retranslateUi(EstoqueWindow);

        QMetaObject::connectSlotsByName(EstoqueWindow);
    } // setupUi

    void retranslateUi(QWidget *EstoqueWindow)
    {
        EstoqueWindow->setWindowTitle(QCoreApplication::translate("EstoqueWindow", "Form", nullptr));
        label->setText(QCoreApplication::translate("EstoqueWindow", "Gerenciar Estoque", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableEstoque->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EstoqueWindow", "Produto", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableEstoque->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EstoqueWindow", "Quantidade", nullptr));
        lblProduto->setText(QCoreApplication::translate("EstoqueWindow", "Produto:", nullptr));
        label_2->setText(QCoreApplication::translate("EstoqueWindow", "Quantidade:", nullptr));
        btnAdicionar->setText(QCoreApplication::translate("EstoqueWindow", "Adicionar Item", nullptr));
        btnCadastrarProduto->setText(QCoreApplication::translate("EstoqueWindow", "Cadastrar Produto", nullptr));
        btnVoltar->setText(QCoreApplication::translate("EstoqueWindow", "Voltar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EstoqueWindow: public Ui_EstoqueWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ESTOQUEWINDOW_H
