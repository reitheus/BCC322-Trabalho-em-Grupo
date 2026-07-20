/********************************************************************************
** Form generated from reading UI file 'reservawindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESERVAWINDOW_H
#define UI_RESERVAWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReservaWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableWidget *tableReservas;
    QPushButton *btnVoltar;

    void setupUi(QWidget *ReservaWindow)
    {
        if (ReservaWindow->objectName().isEmpty())
            ReservaWindow->setObjectName("ReservaWindow");
        ReservaWindow->resize(464, 305);
        ReservaWindow->setMinimumSize(QSize(100, 0));
        verticalLayout = new QVBoxLayout(ReservaWindow);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(ReservaWindow);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        tableReservas = new QTableWidget(ReservaWindow);
        if (tableReservas->columnCount() < 4)
            tableReservas->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableReservas->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableReservas->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableReservas->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableReservas->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableReservas->setObjectName("tableReservas");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableReservas->sizePolicy().hasHeightForWidth());
        tableReservas->setSizePolicy(sizePolicy);
        tableReservas->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        tableReservas->setColumnCount(4);
        tableReservas->horizontalHeader()->setDefaultSectionSize(110);

        verticalLayout->addWidget(tableReservas);

        btnVoltar = new QPushButton(ReservaWindow);
        btnVoltar->setObjectName("btnVoltar");
        btnVoltar->setMaximumSize(QSize(100, 16777215));

        verticalLayout->addWidget(btnVoltar);


        retranslateUi(ReservaWindow);

        QMetaObject::connectSlotsByName(ReservaWindow);
    } // setupUi

    void retranslateUi(QWidget *ReservaWindow)
    {
        ReservaWindow->setWindowTitle(QCoreApplication::translate("ReservaWindow", "Form", nullptr));
        label->setText(QCoreApplication::translate("ReservaWindow", "Estoque reservado com sucesso!", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableReservas->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ReservaWindow", "Cliente", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableReservas->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ReservaWindow", "Produto", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableReservas->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ReservaWindow", "Quantidade", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableReservas->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ReservaWindow", "Situa\303\247\303\243o", nullptr));
        btnVoltar->setText(QCoreApplication::translate("ReservaWindow", "Voltar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReservaWindow: public Ui_ReservaWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESERVAWINDOW_H
