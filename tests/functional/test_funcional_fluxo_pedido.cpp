
#include <QtTest/QtTest>

#include "../../src/services/estoqueserviceImpl.h"
#include "../../src/services/pedidoserviceImpl.h"
#include "../../src/models/pedido.h"

class TestFuncionalFluxoPedido : public QObject
{
    Q_OBJECT

private slots:
    void fluxoPedidoValido_deveRegistrarEReservar();
    void fluxoPedido_deveDescontarSaldoComprometido();
    void fluxoPedidoComEstoqueInsuficiente_deveSerRecusado();
    void fluxoRemoverPedido_deveLiberarSaldo();
};

void TestFuncionalFluxoPedido::fluxoPedidoValido_deveRegistrarEReservar()
{
    EstoqueServiceImpl estoqueService;
    PedidoServiceImpl pedidoService(&estoqueService);

    Pedido pedido("Henrique", "Capacete", 5);

    int saldoDisponivel = 0;

    auto resultadoRegistro =
        pedidoService.registrarPedido(pedido, saldoDisponivel);

    QCOMPARE(resultadoRegistro,
             IPedidoService::ResultadoRegistro::Sucesso);

    QCOMPARE(saldoDisponivel, 20);

    QCOMPARE(pedidoService.consultarSaldo("Capacete"), 15);

    auto resultadoReserva =
        pedidoService.reservarPedidos();

    QCOMPARE(resultadoReserva,
             IPedidoService::ResultadoRegistro::Sucesso);

    QCOMPARE(static_cast<int>(pedidoService.getPedidosPendentes().size()), 0);
    QCOMPARE(static_cast<int>(pedidoService.getPedidosReservados().size()), 1);

    QCOMPARE(pedidoService.getPedidosReservados()[0].getStatus(),
             QString("Reservado"));

    QCOMPARE(estoqueService.verificarSaldo("Capacete"), 15);
}

void TestFuncionalFluxoPedido::fluxoPedido_deveDescontarSaldoComprometido()
{
    EstoqueServiceImpl estoqueService;
    PedidoServiceImpl pedidoService(&estoqueService);

    Pedido pedido1("Henrique", "Capacete", 5);
    Pedido pedido2("Joao", "Capacete", 10);

    int saldo1 = 0;
    int saldo2 = 0;

    auto resultado1 =
        pedidoService.registrarPedido(pedido1, saldo1);

    auto resultado2 =
        pedidoService.registrarPedido(pedido2, saldo2);

    QCOMPARE(resultado1,
             IPedidoService::ResultadoRegistro::Sucesso);

    QCOMPARE(resultado2,
             IPedidoService::ResultadoRegistro::Sucesso);

    QCOMPARE(saldo1, 20);
    QCOMPARE(saldo2, 15);

    QCOMPARE(pedidoService.consultarSaldo("Capacete"), 5);
}

void TestFuncionalFluxoPedido::fluxoPedidoComEstoqueInsuficiente_deveSerRecusado()
{
    EstoqueServiceImpl estoqueService;
    PedidoServiceImpl pedidoService(&estoqueService);

    Pedido pedido("Henrique", "Botina", 11);

    int saldoDisponivel = 0;

    auto resultado =
        pedidoService.registrarPedido(pedido, saldoDisponivel);

    QCOMPARE(resultado,
             IPedidoService::ResultadoRegistro::EstoqueInsuficiente);

    QCOMPARE(saldoDisponivel, 10);

    QCOMPARE(static_cast<int>(pedidoService.getPedidosPendentes().size()), 0);
    QCOMPARE(estoqueService.verificarSaldo("Botina"), 10);
}

void TestFuncionalFluxoPedido::fluxoRemoverPedido_deveLiberarSaldo()
{
    EstoqueServiceImpl estoqueService;
    PedidoServiceImpl pedidoService(&estoqueService);

    Pedido pedido("Henrique", "Luva", 5);

    int saldoDisponivel = 0;

    auto resultado =
        pedidoService.registrarPedido(pedido, saldoDisponivel);

    QCOMPARE(resultado,
             IPedidoService::ResultadoRegistro::Sucesso);

    QCOMPARE(pedidoService.consultarSaldo("Luva"), 10);

    bool removeu =
        pedidoService.removerPedido(0);

    QVERIFY(removeu);

    QCOMPARE(pedidoService.consultarSaldo("Luva"), 15);
    QCOMPARE(static_cast<int>(pedidoService.getPedidosPendentes().size()), 0);
}


// ============================================================
// FUNÇÃO EXECUTORA
//
// Será chamada pelo main_funcional.cpp
// ============================================================

int executarTestFuncionalFluxoPedido(
    int argc,
    char *argv[]
)
{
    TestFuncionalFluxoPedido teste;

    return QTest::qExec(
        &teste,
        argc,
        argv
    );
}

#include "test_funcional_fluxo_pedido.moc"

