/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblTitulo;
    QLabel *lblBemVindo;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *btnPedido;
    QSpacerItem *verticalSpacer;
    QPushButton *btnGerenciarEstoque;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btnSairw;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(760, 540);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(20);
        sizePolicy.setVerticalStretch(15);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        lblTitulo = new QLabel(centralwidget);
        lblTitulo->setObjectName("lblTitulo");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(50);
        sizePolicy1.setHeightForWidth(lblTitulo->sizePolicy().hasHeightForWidth());
        lblTitulo->setSizePolicy(sizePolicy1);
        lblTitulo->setMaximumSize(QSize(16777215, 100));
        QFont font;
        font.setPointSize(19);
        font.setBold(true);
        lblTitulo->setFont(font);
        lblTitulo->setTextFormat(Qt::TextFormat::PlainText);
        lblTitulo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(lblTitulo);

        lblBemVindo = new QLabel(centralwidget);
        lblBemVindo->setObjectName("lblBemVindo");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(100);
        sizePolicy2.setHeightForWidth(lblBemVindo->sizePolicy().hasHeightForWidth());
        lblBemVindo->setSizePolicy(sizePolicy2);
        lblBemVindo->setMaximumSize(QSize(16777215, 200));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        lblBemVindo->setFont(font1);
        lblBemVindo->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        lblBemVindo->setTextFormat(Qt::TextFormat::PlainText);
        lblBemVindo->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_2->addWidget(lblBemVindo);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        btnPedido = new QPushButton(centralwidget);
        btnPedido->setObjectName("btnPedido");
        QFont font2;
        font2.setPointSize(12);
        btnPedido->setFont(font2);
        btnPedido->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(btnPedido);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        btnGerenciarEstoque = new QPushButton(centralwidget);
        btnGerenciarEstoque->setObjectName("btnGerenciarEstoque");
        btnGerenciarEstoque->setFont(font2);
        btnGerenciarEstoque->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(btnGerenciarEstoque);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        btnSairw = new QPushButton(centralwidget);
        btnSairw->setObjectName("btnSairw");
        btnSairw->setFont(font2);

        verticalLayout->addWidget(btnSairw);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "EpiStock", nullptr));
        lblTitulo->setText(QCoreApplication::translate("MainWindow", "EpiStock", nullptr));
        lblBemVindo->setText(QCoreApplication::translate("MainWindow", "Ol\303\241, Bem Vindo!", nullptr));
        btnPedido->setText(QCoreApplication::translate("MainWindow", "Realizar Pedido", nullptr));
        btnGerenciarEstoque->setText(QCoreApplication::translate("MainWindow", "Gerenciar Estoque", nullptr));
        btnSairw->setText(QCoreApplication::translate("MainWindow", "Sair", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
