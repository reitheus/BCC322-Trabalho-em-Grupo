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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *lblTitulo;
    QLabel *lblBemVindo;
    QPushButton *btnPedido;
    QPushButton *btnSair;

    void setupUi(QMainWindow *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName("mainWindow");
        mainWindow->resize(655, 350);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(20);
        sizePolicy.setVerticalStretch(15);
        sizePolicy.setHeightForWidth(mainWindow->sizePolicy().hasHeightForWidth());
        mainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(mainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        lblTitulo = new QLabel(centralwidget);
        lblTitulo->setObjectName("lblTitulo");
        QFont font;
        font.setPointSize(19);
        font.setBold(true);
        lblTitulo->setFont(font);
        lblTitulo->setTextFormat(Qt::TextFormat::PlainText);
        lblTitulo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(lblTitulo);

        lblBemVindo = new QLabel(centralwidget);
        lblBemVindo->setObjectName("lblBemVindo");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(50);
        sizePolicy1.setHeightForWidth(lblBemVindo->sizePolicy().hasHeightForWidth());
        lblBemVindo->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        lblBemVindo->setFont(font1);
        lblBemVindo->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        lblBemVindo->setTextFormat(Qt::TextFormat::PlainText);
        lblBemVindo->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout->addWidget(lblBemVindo);

        btnPedido = new QPushButton(centralwidget);
        btnPedido->setObjectName("btnPedido");
        QFont font2;
        font2.setPointSize(12);
        btnPedido->setFont(font2);
        btnPedido->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(btnPedido);

        btnSair = new QPushButton(centralwidget);
        btnSair->setObjectName("btnSair");
        btnSair->setFont(font2);

        verticalLayout->addWidget(btnSair);


        verticalLayout_2->addLayout(verticalLayout);

        mainWindow->setCentralWidget(centralwidget);

        retranslateUi(mainWindow);

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainWindow)
    {
        mainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "EpiStock", nullptr));
        lblTitulo->setText(QCoreApplication::translate("MainWindow", "EpiStock", nullptr));
        lblBemVindo->setText(QCoreApplication::translate("MainWindow", "Ol\303\241, Bem Vindo!", nullptr));
        btnPedido->setText(QCoreApplication::translate("MainWindow", "Pedidos de Venda", nullptr));
        btnSair->setText(QCoreApplication::translate("MainWindow", "Sair", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
