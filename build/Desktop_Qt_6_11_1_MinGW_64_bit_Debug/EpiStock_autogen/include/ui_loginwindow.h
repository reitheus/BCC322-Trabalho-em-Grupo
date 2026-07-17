/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *lblTitulo;
    QLabel *lblUsuario;
    QLineEdit *txtUsuario;
    QLabel *lblSenha;
    QLineEdit *txtsenha;
    QPushButton *btnEntrar;

    void setupUi(QWidget *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName("login");
        login->resize(320, 220);
        login->setMinimumSize(QSize(320, 220));
        login->setMaximumSize(QSize(320, 220));
#if QT_CONFIG(accessibility)
        login->setAccessibleDescription(QString::fromUtf8(""));
#endif // QT_CONFIG(accessibility)
        layoutWidget = new QWidget(login);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(80, 10, 154, 174));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lblTitulo = new QLabel(layoutWidget);
        lblTitulo->setObjectName("lblTitulo");
        lblTitulo->setMaximumSize(QSize(196, 16777215));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        lblTitulo->setFont(font);
        lblTitulo->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        lblTitulo->setAutoFillBackground(false);
        lblTitulo->setTextFormat(Qt::TextFormat::AutoText);
        lblTitulo->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lblTitulo->setWordWrap(true);

        verticalLayout->addWidget(lblTitulo);

        lblUsuario = new QLabel(layoutWidget);
        lblUsuario->setObjectName("lblUsuario");

        verticalLayout->addWidget(lblUsuario);

        txtUsuario = new QLineEdit(layoutWidget);
        txtUsuario->setObjectName("txtUsuario");

        verticalLayout->addWidget(txtUsuario);

        lblSenha = new QLabel(layoutWidget);
        lblSenha->setObjectName("lblSenha");

        verticalLayout->addWidget(lblSenha);

        txtsenha = new QLineEdit(layoutWidget);
        txtsenha->setObjectName("txtsenha");
        txtsenha->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout->addWidget(txtsenha);

        btnEntrar = new QPushButton(layoutWidget);
        btnEntrar->setObjectName("btnEntrar");

        verticalLayout->addWidget(btnEntrar);

#if QT_CONFIG(shortcut)
#endif // QT_CONFIG(shortcut)

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QWidget *login)
    {
        login->setWindowTitle(QCoreApplication::translate("LoginWindow", "Login - EpiStock", nullptr));
#if QT_CONFIG(tooltip)
        lblTitulo->setToolTip(QCoreApplication::translate("LoginWindow", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        lblTitulo->setText(QCoreApplication::translate("LoginWindow", " EpiStock       ", nullptr));
        lblUsuario->setText(QCoreApplication::translate("LoginWindow", "Usu\303\241rio:", nullptr));
        lblSenha->setText(QCoreApplication::translate("LoginWindow", "Senha:  ", nullptr));
        btnEntrar->setText(QCoreApplication::translate("LoginWindow", "Entrar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
