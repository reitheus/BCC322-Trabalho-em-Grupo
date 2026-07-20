/********************************************************************************
** Form generated from reading UI file 'cadastroprodutowindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CADASTROPRODUTOWINDOW_H
#define UI_CADASTROPRODUTOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CadastroProdutoWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *lblnome;
    QLineEdit *txtNome;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *sbQuantidade;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnCancelar;
    QPushButton *btnCadastrar;

    void setupUi(QWidget *CadastroProdutoWindow)
    {
        if (CadastroProdutoWindow->objectName().isEmpty())
            CadastroProdutoWindow->setObjectName("CadastroProdutoWindow");
        CadastroProdutoWindow->resize(400, 300);
        gridLayout = new QGridLayout(CadastroProdutoWindow);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(CadastroProdutoWindow);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(200);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(16777215, 100));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        lblnome = new QLabel(CadastroProdutoWindow);
        lblnome->setObjectName("lblnome");

        horizontalLayout->addWidget(lblnome);

        txtNome = new QLineEdit(CadastroProdutoWindow);
        txtNome->setObjectName("txtNome");

        horizontalLayout->addWidget(txtNome);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(CadastroProdutoWindow);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        sbQuantidade = new QSpinBox(CadastroProdutoWindow);
        sbQuantidade->setObjectName("sbQuantidade");
        sbQuantidade->setMinimum(1);
        sbQuantidade->setMaximum(999);

        horizontalLayout_2->addWidget(sbQuantidade);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        btnCancelar = new QPushButton(CadastroProdutoWindow);
        btnCancelar->setObjectName("btnCancelar");

        horizontalLayout_3->addWidget(btnCancelar);

        btnCadastrar = new QPushButton(CadastroProdutoWindow);
        btnCadastrar->setObjectName("btnCadastrar");

        horizontalLayout_3->addWidget(btnCadastrar);


        gridLayout->addLayout(horizontalLayout_3, 3, 0, 1, 1);


        retranslateUi(CadastroProdutoWindow);

        QMetaObject::connectSlotsByName(CadastroProdutoWindow);
    } // setupUi

    void retranslateUi(QWidget *CadastroProdutoWindow)
    {
        CadastroProdutoWindow->setWindowTitle(QCoreApplication::translate("CadastroProdutoWindow", "Form", nullptr));
        label->setText(QCoreApplication::translate("CadastroProdutoWindow", "     CADASTRAR PRODUTO", nullptr));
        lblnome->setText(QCoreApplication::translate("CadastroProdutoWindow", "Nome:", nullptr));
        label_2->setText(QCoreApplication::translate("CadastroProdutoWindow", "Quantidade:", nullptr));
        btnCancelar->setText(QCoreApplication::translate("CadastroProdutoWindow", "Cancelar", nullptr));
        btnCadastrar->setText(QCoreApplication::translate("CadastroProdutoWindow", "Cadastrar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CadastroProdutoWindow: public Ui_CadastroProdutoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CADASTROPRODUTOWINDOW_H
