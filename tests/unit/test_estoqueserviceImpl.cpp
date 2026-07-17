#include <QtTest/QtTest>

#include "../../src/services/estoqueserviceImpl.h"

class TestEstoqueServiceImpl : public QObject
{
    Q_OBJECT

private slots:
    void verificarSaldo_deveRetornarSaldoInicialDosProdutos_data();
    void verificarSaldo_deveRetornarSaldoInicialDosProdutos();

    void verificarSaldo_deveRetornarZeroParaProdutoInexistente();

    void reservarEstoque_deveRetornarSucesso();
    void reservarEstoque_deveDiminuirSaldo();

    void reservarEstoque_deveRetornarQuantidadeInvalidaParaZero();
    void reservarEstoque_deveRetornarQuantidadeInvalidaParaNegativo();

    void reservarEstoque_deveRetornarProdutoNaoEncontrado();

    void reservarEstoque_deveRetornarEstoqueInsuficiente();
    void reservarEstoqueInsuficiente_naoDeveAlterarSaldo();

    void reservarEstoque_devePermitirReservarTodoOSaldo();
};

using ResultadoReserva = IEstoqueService::ResultadoReserva;


// ============================================================
// TESTE 1
// Verifica os saldos iniciais usando testes orientados por dados
// ============================================================

void TestEstoqueServiceImpl::
verificarSaldo_deveRetornarSaldoInicialDosProdutos_data()
{
    QTest::addColumn<QString>("nomeProduto");
    QTest::addColumn<int>("saldoEsperado");

    QTest::newRow("capacete")
        << QString("Capacete")
        << 20;

    QTest::newRow("luva")
        << QString("Luva")
        << 15;

    QTest::newRow("botina")
        << QString("Botina")
        << 10;

    QTest::newRow("oculos de protecao")
        << QString::fromUtf8("Óculos de Proteção")
        << 25;

    QTest::newRow("mascara pff2")
        << QString::fromUtf8("Máscara PFF2")
        << 50;
}


void TestEstoqueServiceImpl::
verificarSaldo_deveRetornarSaldoInicialDosProdutos()
{
    QFETCH(QString, nomeProduto);
    QFETCH(int, saldoEsperado);

    EstoqueServiceImpl estoqueService;

    int saldoObtido =
        estoqueService.verificarSaldo(nomeProduto);

    QCOMPARE(saldoObtido, saldoEsperado);
}


// ============================================================
// TESTE 2
// Produto inexistente deve retornar saldo zero
// ============================================================

void TestEstoqueServiceImpl::
verificarSaldo_deveRetornarZeroParaProdutoInexistente()
{
    EstoqueServiceImpl estoqueService;

    int saldo =
        estoqueService.verificarSaldo("Produto Inexistente");

    QCOMPARE(saldo, 0);
}


// ============================================================
// TESTE 3
// Reserva válida deve retornar Sucesso
// ============================================================

void TestEstoqueServiceImpl::
reservarEstoque_deveRetornarSucesso()
{
    EstoqueServiceImpl estoqueService;

    ResultadoReserva resultado =
        estoqueService.reservarEstoque(
            "Capacete",
            5
        );

    QCOMPARE(
        resultado,
        ResultadoReserva::Sucesso
    );
}


// ============================================================
// TESTE 4
// Reserva válida deve diminuir o saldo
// ============================================================

void TestEstoqueServiceImpl::
reservarEstoque_deveDiminuirSaldo()
{
    EstoqueServiceImpl estoqueService;

    QCOMPARE(
        estoqueService.verificarSaldo("Capacete"),
        20
    );

    ResultadoReserva resultado =
        estoqueService.reservarEstoque(
            "Capacete",
            5
        );

    QCOMPARE(
        resultado,
        ResultadoReserva::Sucesso
    );

    QCOMPARE(
        estoqueService.verificarSaldo("Capacete"),
        15
    );
}


// ============================================================
// TESTE 5
// Quantidade zero deve ser inválida
// ============================================================

void TestEstoqueServiceImpl::
reservarEstoque_deveRetornarQuantidadeInvalidaParaZero()
{
    EstoqueServiceImpl estoqueService;

    ResultadoReserva resultado =
        estoqueService.reservarEstoque(
            "Capacete",
            0
        );

    QCOMPARE(
        resultado,
        ResultadoReserva::QuantidadeInvalida
    );
}


// ============================================================
// TESTE 6
// Quantidade negativa deve ser inválida
// ============================================================

void TestEstoqueServiceImpl::
reservarEstoque_deveRetornarQuantidadeInvalidaParaNegativo()
{
    EstoqueServiceImpl estoqueService;

    ResultadoReserva resultado =
        estoqueService.reservarEstoque(
            "Capacete",
            -5
        );

    QCOMPARE(
        resultado,
        ResultadoReserva::QuantidadeInvalida
    );
}


// ============================================================
// TESTE 7
// Produto inexistente
// ============================================================

void TestEstoqueServiceImpl::
reservarEstoque_deveRetornarProdutoNaoEncontrado()
{
    EstoqueServiceImpl estoqueService;

    ResultadoReserva resultado =
        estoqueService.reservarEstoque(
            "Produto Inexistente",
            5
        );

    QCOMPARE(
        resultado,
        ResultadoReserva::ProdutoNaoEncontrado
    );
}


// ============================================================
// TESTE 8
// Quantidade maior que o saldo disponível
// ============================================================

void TestEstoqueServiceImpl::
reservarEstoque_deveRetornarEstoqueInsuficiente()
{
    EstoqueServiceImpl estoqueService;

    ResultadoReserva resultado =
        estoqueService.reservarEstoque(
            "Botina",
            11
        );

    QCOMPARE(
        resultado,
        ResultadoReserva::EstoqueInsuficiente
    );
}


// ============================================================
// TESTE 9
// Reserva recusada não deve alterar o saldo
// ============================================================

void TestEstoqueServiceImpl::
reservarEstoqueInsuficiente_naoDeveAlterarSaldo()
{
    EstoqueServiceImpl estoqueService;

    QCOMPARE(
        estoqueService.verificarSaldo("Botina"),
        10
    );

    ResultadoReserva resultado =
        estoqueService.reservarEstoque(
            "Botina",
            11
        );

    QCOMPARE(
        resultado,
        ResultadoReserva::EstoqueInsuficiente
    );

    QCOMPARE(
        estoqueService.verificarSaldo("Botina"),
        10
    );
}


// ============================================================
// TESTE 10
// Deve permitir reservar exatamente todo o saldo
// ============================================================

void TestEstoqueServiceImpl::
reservarEstoque_devePermitirReservarTodoOSaldo()
{
    EstoqueServiceImpl estoqueService;

    QCOMPARE(
        estoqueService.verificarSaldo("Luva"),
        15
    );

    ResultadoReserva resultado =
        estoqueService.reservarEstoque(
            "Luva",
            15
        );

    QCOMPARE(
        resultado,
        ResultadoReserva::Sucesso
    );

    QCOMPARE(
        estoqueService.verificarSaldo("Luva"),
        0
    );
}


int executarTestEstoqueServiceImpl(
    int argc,
    char *argv[]
)
{
    TestEstoqueServiceImpl teste;

    return QTest::qExec(
        &teste,
        argc,
        argv
    );
}

#include "test_estoqueserviceimpl.moc"

