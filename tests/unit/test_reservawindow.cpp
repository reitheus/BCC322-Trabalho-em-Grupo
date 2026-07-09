#include <QtTest/QtTest>

#include "../../src/views/reservawindow.h"
#include "../../src/views/pedidowindow.h"
#include "../../src/services/pedidoserviceImpl.h"
#include "../../src/models/pedido.h"

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QWidget>

#include <vector>


// ============================================================
// FAKE DO SERVIÇO DE PEDIDOS
//
// Permite controlar os pedidos reservados retornados
// para ReservaWindow.
// ============================================================

class FakePedidoService : public IPedidoService
{
public:

    std::vector<Pedido> pedidosPendentes;
    std::vector<Pedido> pedidosReservados;

    bool getPedidosReservadosFoiChamado = false;


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
        return pedidosPendentes;
    }


    std::vector<Pedido>
    getPedidosReservados() const override
    {
        // Como o método da interface é const,
        // usamos const_cast apenas para registrar
        // que a função foi chamada durante o teste.

        const_cast<FakePedidoService *>(this)
            ->getPedidosReservadosFoiChamado = true;

        return pedidosReservados;
    }


    ResultadoRegistro reservarPedidos() override
    {
        return ResultadoRegistro::Sucesso;
    }


    bool removerPedido(
        int indice) override
    {
        Q_UNUSED(indice);

        return false;
    }
};


// ============================================================
// CLASSE DE TESTE
// ============================================================

class TestReservaWindow : public QObject
{
    Q_OBJECT

private slots:

    void init();
    void cleanup();

    // Construção
    void construtor_deveCriarJanela();

    // Componentes
    void tabelaReservas_deveExistir();
    void botaoVoltar_deveExistir();
    void labelMensagem_deveExistir();

    // Conteúdo visual
    void labelMensagem_deveExibirTextoCorreto();
    void botaoVoltar_deveExibirTextoCorreto();

    // Tabela
    void construtor_deveConsultarPedidosReservados();
    void semPedidosReservados_deveCriarTabelaVazia();

    void umPedidoReservado_deveCriarUmaLinha();
    void pedidoReservado_deveExibirCliente();
    void pedidoReservado_deveExibirProduto();
    void pedidoReservado_deveExibirQuantidade();
    void pedidoReservado_deveExibirStatus();

    void variosPedidosReservados_devemCriarVariasLinhas();
    void tabela_deveTerQuatroColunas();
    void tabela_deveExibirCabecalhosCorretos();

    // Transição de janelas
    void clicarVoltar_deveFecharReservaWindow();
    void clicarVoltar_deveAbrirPedidoWindow();

private:

    FakePedidoService *pedidoService;
    ReservaWindow *reservaWindow;

    QTableWidget *tabelaReservas;
    QPushButton *botaoVoltar;
    QLabel *labelMensagem;

    PedidoWindow *buscarPedidoWindow();

    void fecharJanelasAuxiliares();
};


// ============================================================
// INIT
//
// Executado ANTES de cada teste.
//
// Importante:
// ReservaWindow chama atualizarTabela()
// dentro do construtor.
//
// Por isso, para testes que precisam iniciar com pedidos,
// alguns deles criarão uma nova janela manualmente.
// ============================================================

void TestReservaWindow::init()
{
    pedidoService =
        new FakePedidoService();

    reservaWindow =
        new ReservaWindow(
            pedidoService
        );

    tabelaReservas =
        reservaWindow->findChild<QTableWidget *>(
            "tableReservas"
        );

    botaoVoltar =
        reservaWindow->findChild<QPushButton *>(
            "btnVoltar"
        );

    labelMensagem =
        reservaWindow->findChild<QLabel *>(
            "label"
        );
}


// ============================================================
// CLEANUP
//
// ReservaWindow NÃO destrói pedidoService.
//
// Portanto, neste teste devemos deletar:
// 1. reservaWindow
// 2. pedidoService
//
// Porém, PedidoWindow possui um destrutor que atualmente
// executa delete pedidoService.
//
// Por isso, janelas auxiliares precisam ser tratadas
// antes de destruir o serviço.
// ============================================================

void TestReservaWindow::cleanup()
{
    fecharJanelasAuxiliares();

    delete reservaWindow;
    reservaWindow = nullptr;

    delete pedidoService;
    pedidoService = nullptr;

    QApplication::processEvents();
}


// ============================================================
// FUNÇÃO AUXILIAR
//
// Procura uma PedidoWindow aberta.
// ============================================================

PedidoWindow *
TestReservaWindow::buscarPedidoWindow()
{
    const QWidgetList widgets =
        QApplication::topLevelWidgets();

    for (QWidget *widget : widgets)
    {
        PedidoWindow *pedidoWindow =
            qobject_cast<PedidoWindow *>(
                widget
            );

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
// Fecha janelas auxiliares.
//
// Atenção:
// PedidoWindow atualmente destrói pedidoService.
// Para evitar double delete nos testes de transição,
// não deletamos imediatamente a PedidoWindow aqui.
// ============================================================

void TestReservaWindow::fecharJanelasAuxiliares()
{
    const QWidgetList widgets =
        QApplication::topLevelWidgets();

    for (QWidget *widget : widgets)
    {
        if (widget != reservaWindow)
        {
            widget->close();
        }
    }

    QApplication::processEvents();
}


// ============================================================
// TESTE 1
//
// Verifica se ReservaWindow foi criada.
// ============================================================

void TestReservaWindow::
construtor_deveCriarJanela()
{
    QVERIFY(
        reservaWindow != nullptr
    );
}


// ============================================================
// TESTE 2
//
// Verifica se tableReservas existe.
// ============================================================

void TestReservaWindow::
tabelaReservas_deveExistir()
{
    QVERIFY2(
        tabelaReservas != nullptr,
        "tableReservas nao foi encontrada"
    );
}


// ============================================================
// TESTE 3
//
// Verifica se btnVoltar existe.
// ============================================================

void TestReservaWindow::
botaoVoltar_deveExistir()
{
    QVERIFY2(
        botaoVoltar != nullptr,
        "btnVoltar nao foi encontrado"
    );
}


// ============================================================
// TESTE 4
//
// Verifica se label existe.
// ============================================================

void TestReservaWindow::
labelMensagem_deveExistir()
{
    QVERIFY2(
        labelMensagem != nullptr,
        "Label de mensagem nao foi encontrada"
    );
}


// ============================================================
// TESTE 5
//
// Verifica mensagem definida no .ui.
// ============================================================

void TestReservaWindow::
labelMensagem_deveExibirTextoCorreto()
{
    QVERIFY(
        labelMensagem != nullptr
    );

    QCOMPARE(
        labelMensagem->text(),
        QString(
            "Estoque reservado com sucesso!"
        )
    );
}


// ============================================================
// TESTE 6
//
// Verifica texto do botão.
// ============================================================

void TestReservaWindow::
botaoVoltar_deveExibirTextoCorreto()
{
    QVERIFY(
        botaoVoltar != nullptr
    );

    QCOMPARE(
        botaoVoltar->text(),
        QString("Voltar")
    );
}


// ============================================================
// TESTE 7
//
// O construtor chama:
//
// atualizarTabela();
//
// E atualizarTabela chama:
//
// pedidoService->getPedidosReservados();
//
// ============================================================

void TestReservaWindow::
construtor_deveConsultarPedidosReservados()
{
    QVERIFY(
        pedidoService->
        getPedidosReservadosFoiChamado
    );
}


// ============================================================
// TESTE 8
//
// Sem reservas, tabela deve ficar vazia.
// ============================================================

void TestReservaWindow::
semPedidosReservados_deveCriarTabelaVazia()
{
    QVERIFY(
        tabelaReservas != nullptr
    );

    QCOMPARE(
        tabelaReservas->rowCount(),
        0
    );
}


// ============================================================
// TESTE 9
//
// Um pedido reservado deve criar uma linha.
//
// Como atualizarTabela() roda no construtor,
// recriamos a janela após configurar o Fake.
// ============================================================

void TestReservaWindow::
umPedidoReservado_deveCriarUmaLinha()
{
    delete reservaWindow;

    Pedido pedido(
        "Henrique",
        "Capacete",
        5
    );

    pedido.setStatus(
        "Reservado"
    );

    pedidoService->
        pedidosReservados.push_back(
            pedido
        );

    reservaWindow =
        new ReservaWindow(
            pedidoService
        );

    tabelaReservas =
        reservaWindow->findChild<QTableWidget *>(
            "tableReservas"
        );

    QCOMPARE(
        tabelaReservas->rowCount(),
        1
    );
}


// ============================================================
// TESTE 10
//
// Verifica coluna Cliente.
// ============================================================

void TestReservaWindow::
pedidoReservado_deveExibirCliente()
{
    delete reservaWindow;

    Pedido pedido(
        "Henrique",
        "Capacete",
        5
    );

    pedido.setStatus(
        "Reservado"
    );

    pedidoService->
        pedidosReservados.push_back(
            pedido
        );

    reservaWindow =
        new ReservaWindow(
            pedidoService
        );

    tabelaReservas =
        reservaWindow->findChild<QTableWidget *>(
            "tableReservas"
        );

    QVERIFY(
        tabelaReservas->item(0, 0)
        != nullptr
    );

    QCOMPARE(
        tabelaReservas->item(0, 0)->text(),
        QString("Henrique")
    );
}


// ============================================================
// TESTE 11
//
// Verifica coluna Produto.
// ============================================================

void TestReservaWindow::
pedidoReservado_deveExibirProduto()
{
    delete reservaWindow;

    Pedido pedido(
        "Henrique",
        "Capacete",
        5
    );

    pedido.setStatus(
        "Reservado"
    );

    pedidoService->
        pedidosReservados.push_back(
            pedido
        );

    reservaWindow =
        new ReservaWindow(
            pedidoService
        );

    tabelaReservas =
        reservaWindow->findChild<QTableWidget *>(
            "tableReservas"
        );

    QVERIFY(
        tabelaReservas->item(0, 1)
        != nullptr
    );

    QCOMPARE(
        tabelaReservas->item(0, 1)->text(),
        QString("Capacete")
    );
}


// ============================================================
// TESTE 12
//
// Verifica coluna Quantidade.
// ============================================================

void TestReservaWindow::
pedidoReservado_deveExibirQuantidade()
{
    delete reservaWindow;

    Pedido pedido(
        "Henrique",
        "Capacete",
        5
    );

    pedido.setStatus(
        "Reservado"
    );

    pedidoService->
        pedidosReservados.push_back(
            pedido
        );

    reservaWindow =
        new ReservaWindow(
            pedidoService
        );

    tabelaReservas =
        reservaWindow->findChild<QTableWidget *>(
            "tableReservas"
        );

    QVERIFY(
        tabelaReservas->item(0, 2)
        != nullptr
    );

    QCOMPARE(
        tabelaReservas->item(0, 2)->text(),
        QString("5")
    );
}


// ============================================================
// TESTE 13
//
// Verifica coluna Status.
// ============================================================

void TestReservaWindow::
pedidoReservado_deveExibirStatus()
{
    delete reservaWindow;

    Pedido pedido(
        "Henrique",
        "Capacete",
        5
    );

    pedido.setStatus(
        "Reservado"
    );

    pedidoService->
        pedidosReservados.push_back(
            pedido
        );

    reservaWindow =
        new ReservaWindow(
            pedidoService
        );

    tabelaReservas =
        reservaWindow->findChild<QTableWidget *>(
            "tableReservas"
        );

    QVERIFY(
        tabelaReservas->item(0, 3)
        != nullptr
    );

    QCOMPARE(
        tabelaReservas->item(0, 3)->text(),
        QString("Reservado")
    );
}


// ============================================================
// TESTE 14
//
// Vários pedidos devem criar várias linhas.
// ============================================================

void TestReservaWindow::
variosPedidosReservados_devemCriarVariasLinhas()
{
    delete reservaWindow;

    Pedido pedido1(
        "Henrique",
        "Capacete",
        5
    );

    pedido1.setStatus(
        "Reservado"
    );


    Pedido pedido2(
        "Joao",
        "Luva",
        3
    );

    pedido2.setStatus(
        "Reservado"
    );


    Pedido pedido3(
        "Maria",
        "Botina",
        2
    );

    pedido3.setStatus(
        "Reservado"
    );


    pedidoService->
        pedidosReservados.push_back(
            pedido1
        );

    pedidoService->
        pedidosReservados.push_back(
            pedido2
        );

    pedidoService->
        pedidosReservados.push_back(
            pedido3
        );


    reservaWindow =
        new ReservaWindow(
            pedidoService
        );

    tabelaReservas =
        reservaWindow->findChild<QTableWidget *>(
            "tableReservas"
        );

    QCOMPARE(
        tabelaReservas->rowCount(),
        3
    );


    QCOMPARE(
        tabelaReservas->item(0, 0)->text(),
        QString("Henrique")
    );

    QCOMPARE(
        tabelaReservas->item(1, 0)->text(),
        QString("Joao")
    );

    QCOMPARE(
        tabelaReservas->item(2, 0)->text(),
        QString("Maria")
    );
}


// ============================================================
// TESTE 15
//
// Tabela deve possuir quatro colunas.
// ============================================================

void TestReservaWindow::
tabela_deveTerQuatroColunas()
{
    QCOMPARE(
        tabelaReservas->columnCount(),
        4
    );
}


// ============================================================
// TESTE 16
//
// Verifica cabeçalhos definidos no .ui.
// ============================================================

void TestReservaWindow::
tabela_deveExibirCabecalhosCorretos()
{
    QCOMPARE(
        tabelaReservas->
            horizontalHeaderItem(0)->text(),
        QString("Cliente")
    );

    QCOMPARE(
        tabelaReservas->
            horizontalHeaderItem(1)->text(),
        QString("Produto")
    );

    QCOMPARE(
        tabelaReservas->
            horizontalHeaderItem(2)->text(),
        QString("Quantidade")
    );

    QCOMPARE(
        tabelaReservas->
            horizontalHeaderItem(3)->text(),
        QString::fromUtf8("Situação")
    );
}


// ============================================================
// TESTE 17
//
// Ao clicar Voltar:
//
// close();
//
// deve fechar ReservaWindow.
// ============================================================

void TestReservaWindow::
clicarVoltar_deveFecharReservaWindow()
{
    QVERIFY(
        botaoVoltar != nullptr
    );

    reservaWindow->show();

    QVERIFY(
        QTest::qWaitForWindowExposed(
            reservaWindow
        )
    );

    QVERIFY(
        reservaWindow->isVisible()
    );

    QTest::mouseClick(
        botaoVoltar,
        Qt::LeftButton
    );

    QApplication::processEvents();

    QVERIFY(
        !reservaWindow->isVisible()
    );

    // IMPORTANTE:
    // O clique cria PedidoWindow.
    // PedidoWindow passa a compartilhar pedidoService.
    //
    // Para evitar problemas no cleanup deste teste,
    // localizamos a janela criada e apenas a fechamos.

    PedidoWindow *pedidoWindow =
        buscarPedidoWindow();

    if (pedidoWindow != nullptr)
    {
        pedidoWindow->close();
    }
}


// ============================================================
// TESTE 18
//
// Ao clicar Voltar:
//
// PedidoWindow *janela =
//     new PedidoWindow(pedidoService);
//
// janela->show();
//
// Portanto, PedidoWindow deve aparecer.
// ============================================================

void TestReservaWindow::
clicarVoltar_deveAbrirPedidoWindow()
{
    QVERIFY(
        botaoVoltar != nullptr
    );

    reservaWindow->show();

    QVERIFY(
        QTest::qWaitForWindowExposed(
            reservaWindow
        )
    );

    PedidoWindow *antes =
        buscarPedidoWindow();

    QVERIFY(
        antes == nullptr
    );

    QTest::mouseClick(
        botaoVoltar,
        Qt::LeftButton
    );

    QApplication::processEvents();

    PedidoWindow *pedidoWindow =
        buscarPedidoWindow();

    QVERIFY2(
        pedidoWindow != nullptr,
        "PedidoWindow nao foi criada"
    );

    QVERIFY(
        pedidoWindow->isVisible()
    );

    pedidoWindow->close();
}


int executarTestReservaWindow(
    int argc,
    char *argv[]
)
{
    TestReservaWindow teste;

    return QTest::qExec(
        &teste,
        argc,
        argv
    );
}

#include "test_reservawindow.moc"

