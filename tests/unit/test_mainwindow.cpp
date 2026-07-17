
#include <QtTest/QtTest>

#include "../../src/views/mainwindow.h"
#include "../../src/views/pedidowindow.h"
#include "../../src/services/pedidoserviceImpl.h"
#include "../../src/models/pedido.h"

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

#include <vector>


// ============================================================
// FAKE DO SERVIÇO DE PEDIDOS
//
// MainWindow depende de IPedidoService.
// Criamos um Fake para testar MainWindow isoladamente.
// ============================================================

class FakePedidoService : public IPedidoService
{
public:

    ResultadoRegistro registrarPedido(
        const Pedido &pedido,
        int &saldoDisponivel) override
    {
        Q_UNUSED(pedido);

        saldoDisponivel = 0;

        return ResultadoRegistro::Sucesso;
    }

    int consultarSaldo(
        const QString &produto) override
    {
        Q_UNUSED(produto);

        return 0;
    }

    std::vector<Pedido>
    getPedidosPendentes() const override
    {
        return {};
    }

    std::vector<Pedido>
    getPedidosReservados() const override
    {
        return {};
    }

    ResultadoRegistro reservarPedidos() override
    {
        return ResultadoRegistro::Sucesso;
    }

    bool removerPedido(int indice) override
    {
        Q_UNUSED(indice);

        return false;
    }
};


// ============================================================
// CLASSE DE TESTE
// ============================================================

class TestMainWindow : public QObject
{
    Q_OBJECT

private slots:

    // Executados automaticamente pelo Qt Test
    void init();
    void cleanup();

    // Testes da construção da janela
    void construtor_deveCriarMainWindow();
    void construtor_deveDefinirTituloDaJanela();

    // Testes dos componentes da interface
    void labelTitulo_deveExistir();
    void labelTitulo_deveExibirTextoCorreto();

    void labelBemVindo_deveExistir();
    void labelBemVindo_deveExibirTextoCorreto();

    void botaoPedido_deveExistir();
    void botaoPedido_deveExibirTextoCorreto();

    void botaoSair_deveExistir();
    void botaoSair_deveExibirTextoCorreto();

    // Testes de GUI e transição de janelas
    void clicarBotaoPedido_deveEsconderMainWindow();
    void clicarBotaoPedido_deveAbrirPedidoWindow();

private:

    FakePedidoService *pedidoService;
    MainWindow *mainWindow;

    QLabel *labelTitulo;
    QLabel *labelBemVindo;

    QPushButton *botaoPedido;
    QPushButton *botaoSair;

    PedidoWindow *buscarPedidoWindow();

    void fecharJanelasAuxiliares();
};


// ============================================================
// INIT
//
// Executado ANTES de cada teste.
// Cada teste começa com objetos novos.
// ============================================================

void TestMainWindow::init()
{
    pedidoService =
        new FakePedidoService();

    mainWindow =
        new MainWindow(pedidoService);

    labelTitulo =
        mainWindow->findChild<QLabel *>(
            "lblTitulo"
        );

    labelBemVindo =
        mainWindow->findChild<QLabel *>(
            "lblBemVindo"
        );

    botaoPedido =
        mainWindow->findChild<QPushButton *>(
            "btnPedido"
        );

    botaoSair =
        mainWindow->findChild<QPushButton *>(
            "btnSair"
        );
}


// ============================================================
// CLEANUP
//
// Executado DEPOIS de cada teste.
// ============================================================

void TestMainWindow::cleanup()
{
    fecharJanelasAuxiliares();

    delete mainWindow;
    mainWindow = nullptr;

    delete pedidoService;
    pedidoService = nullptr;
}


// ============================================================
// FUNÇÃO AUXILIAR
//
// Procura uma PedidoWindow entre as janelas abertas.
// ============================================================

PedidoWindow *
TestMainWindow::buscarPedidoWindow()
{
    const QWidgetList widgets =
        QApplication::topLevelWidgets();

    for (QWidget *widget : widgets)
    {
        PedidoWindow *pedidoWindow =
            qobject_cast<PedidoWindow *>(widget);

        if (pedidoWindow != nullptr)
        {
            return pedidoWindow;
        }
    }

    return nullptr;
}


// ============================================================
// FUNÇÃO AUXILIAR
//
// Fecha janelas criadas durante os testes.
// Principalmente PedidoWindow.
// ============================================================

void TestMainWindow::fecharJanelasAuxiliares()
{
    const QWidgetList widgets =
        QApplication::topLevelWidgets();

    for (QWidget *widget : widgets)
    {
        if (widget != mainWindow)
        {
            widget->close();
            widget->deleteLater();
        }
    }

    QApplication::processEvents();
}


// ============================================================
// TESTE 1
//
// Verifica se MainWindow foi criada.
// ============================================================

void TestMainWindow::
construtor_deveCriarMainWindow()
{
    QVERIFY(
        mainWindow != nullptr
    );
}


// ============================================================
// TESTE 2
//
// Verifica o título definido no arquivo mainwindow.ui.
// ============================================================

void TestMainWindow::
construtor_deveDefinirTituloDaJanela()
{
    QCOMPARE(
        mainWindow->windowTitle(),
        QString("EpiStock")
    );
}


// ============================================================
// TESTE 3
//
// Verifica se lblTitulo existe.
// ============================================================

void TestMainWindow::
labelTitulo_deveExistir()
{
    QVERIFY2(
        labelTitulo != nullptr,
        "Label lblTitulo nao foi encontrada"
    );
}


// ============================================================
// TESTE 4
//
// Verifica o texto da lblTitulo.
// ============================================================

void TestMainWindow::
labelTitulo_deveExibirTextoCorreto()
{
    QVERIFY(
        labelTitulo != nullptr
    );

    QCOMPARE(
        labelTitulo->text(),
        QString("EpiStock")
    );
}


// ============================================================
// TESTE 5
//
// Verifica se lblBemVindo existe.
// ============================================================

void TestMainWindow::
labelBemVindo_deveExistir()
{
    QVERIFY2(
        labelBemVindo != nullptr,
        "Label lblBemVindo nao foi encontrada"
    );
}


// ============================================================
// TESTE 6
//
// Verifica o texto da mensagem de boas-vindas.
// ============================================================

void TestMainWindow::
labelBemVindo_deveExibirTextoCorreto()
{
    QVERIFY(
        labelBemVindo != nullptr
    );

    QCOMPARE(
        labelBemVindo->text(),
        QString::fromUtf8("Olá, Bem Vindo!")
    );
}


// ============================================================
// TESTE 7
//
// Verifica se btnPedido existe.
// ============================================================

void TestMainWindow::
botaoPedido_deveExistir()
{
    QVERIFY2(
        botaoPedido != nullptr,
        "Botao btnPedido nao foi encontrado"
    );
}


// ============================================================
// TESTE 8
//
// Verifica o texto do botão de pedidos.
// ============================================================

void TestMainWindow::
botaoPedido_deveExibirTextoCorreto()
{
    QVERIFY(
        botaoPedido != nullptr
    );

    QCOMPARE(
        botaoPedido->text(),
        QString("Pedidos de Venda")
    );
}


// ============================================================
// TESTE 9
//
// Verifica se btnSair existe.
// ============================================================

void TestMainWindow::
botaoSair_deveExistir()
{
    QVERIFY2(
        botaoSair != nullptr,
        "Botao btnSair nao foi encontrado"
    );
}


// ============================================================
// TESTE 10
//
// Verifica o texto do botão sair.
// ============================================================

void TestMainWindow::
botaoSair_deveExibirTextoCorreto()
{
    QVERIFY(
        botaoSair != nullptr
    );

    QCOMPARE(
        botaoSair->text(),
        QString("Sair")
    );
}


// ============================================================
// TESTE 11
//
// Ao clicar em btnPedido:
//
// MainWindow::on_btnPedido_clicked()
//
// deve executar:
//
// this->hide();
//
// Portanto, MainWindow deve ficar invisível.
// ============================================================

void TestMainWindow::
clicarBotaoPedido_deveEsconderMainWindow()
{
    QVERIFY(
        botaoPedido != nullptr
    );

    mainWindow->show();

    QVERIFY(
        QTest::qWaitForWindowExposed(
            mainWindow
        )
    );

    QVERIFY(
        mainWindow->isVisible()
    );

    QTest::mouseClick(
        botaoPedido,
        Qt::LeftButton
    );

    QApplication::processEvents();

    QVERIFY(
        !mainWindow->isVisible()
    );
}


// ============================================================
// TESTE 12
//
// Ao clicar em btnPedido:
//
// PedidoWindow *pedido =
//     new PedidoWindow(pedidoService);
//
// pedido->show();
//
// Portanto, uma PedidoWindow deve ser criada e exibida.
// ============================================================

void TestMainWindow::
clicarBotaoPedido_deveAbrirPedidoWindow()
{
    QVERIFY(
        botaoPedido != nullptr
    );

    mainWindow->show();

    QVERIFY(
        QTest::qWaitForWindowExposed(
            mainWindow
        )
    );

    // Antes do clique não deve existir
    // nenhuma PedidoWindow.
    PedidoWindow *antesDoClique =
        buscarPedidoWindow();

    QVERIFY(
        antesDoClique == nullptr
    );

    // Simula clique real do usuário.
    QTest::mouseClick(
        botaoPedido,
        Qt::LeftButton
    );

    QApplication::processEvents();

    // Procura a janela criada.
    PedidoWindow *pedidoWindow =
        buscarPedidoWindow();

    QVERIFY2(
        pedidoWindow != nullptr,
        "PedidoWindow nao foi criada apos clicar em btnPedido"
    );

    QVERIFY(
        pedidoWindow->isVisible()
    );
}

int executarTestMainWindow(
    int argc,
    char *argv[]
)
{
    TestMainWindow teste;

    return QTest::qExec(
        &teste,
        argc,
        argv
    );
}

#include "test_mainwindow.moc"

