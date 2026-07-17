
#include <QtTest/QtTest>

#include "../../src/views/loginwindow.h"
#include "../../src/views/mainwindow.h"
#include "../../src/views/pedidowindow.h"
#include "../../src/views/reservawindow.h"

#include "../../src/services/estoqueserviceImpl.h"
#include "../../src/services/pedidoserviceImpl.h"

#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QTableWidget>
#include <QMessageBox>
#include <QTimer>
#include <QLabel>

class TestFuncionalInterface : public QObject
{
    Q_OBJECT

private slots:
    void fluxoCompleto_deveFazerLoginAdicionarPedidoEReservar();

private:
    template <typename T>
    T *buscarJanelaAberta()
    {
        for (QWidget *widget : QApplication::topLevelWidgets())
        {
            T *janela = qobject_cast<T *>(widget);

            if (janela != nullptr && janela->isVisible())
                return janela;
        }

        return nullptr;
    }

    QMessageBox *buscarMessageBox()
    {
        for (QWidget *widget : QApplication::topLevelWidgets())
        {
            QMessageBox *msg = qobject_cast<QMessageBox *>(widget);

            if (msg != nullptr)
                return msg;
        }

        return nullptr;
    }

    void fecharProximaMessageBox()
    {
        QTimer::singleShot(100, this, [this]()
        {
            QMessageBox *msg = buscarMessageBox();

            if (msg != nullptr)
                msg->accept();
        });
    }
};

void TestFuncionalInterface::fluxoCompleto_deveFazerLoginAdicionarPedidoEReservar()
{
    EstoqueServiceImpl *estoqueService =
        new EstoqueServiceImpl();

    PedidoServiceImpl *pedidoService =
        new PedidoServiceImpl(estoqueService);

    LoginWindow *loginWindow =
        new LoginWindow(pedidoService);

    loginWindow->show();

    QVERIFY(QTest::qWaitForWindowExposed(loginWindow));

    QLineEdit *txtUsuario =
        loginWindow->findChild<QLineEdit *>("txtUsuario");

    QLineEdit *txtSenha =
        loginWindow->findChild<QLineEdit *>("txtsenha");

    QPushButton *btnEntrar =
        loginWindow->findChild<QPushButton *>("btnEntrar");

    QVERIFY(txtUsuario != nullptr);
    QVERIFY(txtSenha != nullptr);
    QVERIFY(btnEntrar != nullptr);

    QTest::keyClicks(txtUsuario, "admin");
    QTest::keyClicks(txtSenha, "123");

    QTest::mouseClick(btnEntrar, Qt::LeftButton);

    QApplication::processEvents();

    QVERIFY(!loginWindow->isVisible());

    MainWindow *mainWindow =
        buscarJanelaAberta<MainWindow>();

    QVERIFY2(mainWindow != nullptr,
             "MainWindow nao foi aberta apos login correto");

    QPushButton *btnPedido =
        mainWindow->findChild<QPushButton *>("btnPedido");

    QVERIFY(btnPedido != nullptr);

    QTest::mouseClick(btnPedido, Qt::LeftButton);

    QApplication::processEvents();

    QVERIFY(!mainWindow->isVisible());

    PedidoWindow *pedidoWindow =
        buscarJanelaAberta<PedidoWindow>();

    QVERIFY2(pedidoWindow != nullptr,
             "PedidoWindow nao foi aberta apos clicar em Pedidos");

    QLineEdit *txtCliente =
        pedidoWindow->findChild<QLineEdit *>("txtCliente");

    QComboBox *comboProduto =
        pedidoWindow->findChild<QComboBox *>("comboProduto");

    QSpinBox *spinQuantidade =
        pedidoWindow->findChild<QSpinBox *>("spinQuantidade");

    QPushButton *btnVerificar =
        pedidoWindow->findChild<QPushButton *>("btnVerificar");

    QPushButton *btnAdicionar =
        pedidoWindow->findChild<QPushButton *>("btnAdicionar");

    QPushButton *btnReservar =
        pedidoWindow->findChild<QPushButton *>("btnReservar");

    QLabel *lblSaldo =
        pedidoWindow->findChild<QLabel *>("lblSaldo");

    QLabel *lblStatus =
        pedidoWindow->findChild<QLabel *>("lblStatus");

    QTableWidget *tableItens =
        pedidoWindow->findChild<QTableWidget *>("tableItens");

    QVERIFY(txtCliente != nullptr);
    QVERIFY(comboProduto != nullptr);
    QVERIFY(spinQuantidade != nullptr);
    QVERIFY(btnVerificar != nullptr);
    QVERIFY(btnAdicionar != nullptr);
    QVERIFY(btnReservar != nullptr);
    QVERIFY(lblSaldo != nullptr);
    QVERIFY(lblStatus != nullptr);
    QVERIFY(tableItens != nullptr);

    QTest::keyClicks(txtCliente, "Henrique");

    comboProduto->setCurrentText("Capacete");
    spinQuantidade->setValue(5);

    QTest::mouseClick(btnVerificar, Qt::LeftButton);

    QCOMPARE(lblSaldo->text(), QString("20"));
    QCOMPARE(lblStatus->text(), QString::fromUtf8("Disponível"));

    QTest::mouseClick(btnAdicionar, Qt::LeftButton);

    QCOMPARE(lblStatus->text(), QString("Pedido registrado com sucesso."));
    QCOMPARE(lblSaldo->text(), QString("20"));

    QCOMPARE(tableItens->rowCount(), 1);
    QCOMPARE(tableItens->item(0, 0)->text(), QString("Capacete"));
    QCOMPARE(tableItens->item(0, 1)->text(), QString("5"));
    QCOMPARE(tableItens->item(0, 2)->text(), QString("Pendente"));

    fecharProximaMessageBox();

    QTest::mouseClick(btnReservar, Qt::LeftButton);

    QApplication::processEvents();

    QVERIFY(!pedidoWindow->isVisible());

    ReservaWindow *reservaWindow =
        buscarJanelaAberta<ReservaWindow>();

    QVERIFY2(reservaWindow != nullptr,
             "ReservaWindow nao foi aberta apos confirmar reserva");

    QTableWidget *tableReservas =
        reservaWindow->findChild<QTableWidget *>("tableReservas");

    QVERIFY(tableReservas != nullptr);

    QCOMPARE(tableReservas->rowCount(), 1);
    QCOMPARE(tableReservas->item(0, 0)->text(), QString("Henrique"));
    QCOMPARE(tableReservas->item(0, 1)->text(), QString("Capacete"));
    QCOMPARE(tableReservas->item(0, 2)->text(), QString("5"));
    QCOMPARE(tableReservas->item(0, 3)->text(), QString("Reservado"));
}

// ============================================================
// FUNÇÃO EXECUTORA
//
// Será chamada pelo main_funcional.cpp
// ============================================================

int executarTestFuncionalInterface(
    int argc,
    char *argv[]
)
{
    TestFuncionalInterface teste;

    return QTest::qExec(
        &teste,
        argc,
        argv
    );
}

#include "test_funcional_interface.moc"

