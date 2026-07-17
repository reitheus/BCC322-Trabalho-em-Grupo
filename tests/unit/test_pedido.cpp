#include <QtTest/QtTest>
#include "../../src/models/pedido.h"

class TestPedido : public QObject
{
    Q_OBJECT

private slots:
    void construtorPadrao_deveCriarPedido();
    void construtorComParametros_deveDefinirDados();
    void construtorComParametros_deveDefinirStatusPendente();
    void setCliente_deveAlterarCliente();
    void setProduto_deveAlterarProduto();
    void setQuantidade_deveAlterarQuantidade();
    void setStatus_deveAlterarStatus();
};

void TestPedido::construtorPadrao_deveCriarPedido()
{
    Pedido pedido;

    QVERIFY(true);
}

void TestPedido::construtorComParametros_deveDefinirDados()
{
    Pedido pedido("Henrique", "Racao", 5);

    QCOMPARE(pedido.getCliente(), QString("Henrique"));
    QCOMPARE(pedido.getProduto(), QString("Racao"));
    QCOMPARE(pedido.getQuantidade(), 5);
}

void TestPedido::construtorComParametros_deveDefinirStatusPendente()
{
    Pedido pedido("Henrique", "Racao", 5);

    QCOMPARE(pedido.getStatus(), QString("Pendente"));
}

void TestPedido::setCliente_deveAlterarCliente()
{
    Pedido pedido;

    pedido.setCliente("Joao");

    QCOMPARE(pedido.getCliente(), QString("Joao"));
}

void TestPedido::setProduto_deveAlterarProduto()
{
    Pedido pedido;

    pedido.setProduto("Milho");

    QCOMPARE(pedido.getProduto(), QString("Milho"));
}

void TestPedido::setQuantidade_deveAlterarQuantidade()
{
    Pedido pedido;

    pedido.setQuantidade(10);

    QCOMPARE(pedido.getQuantidade(), 10);
}

void TestPedido::setStatus_deveAlterarStatus()
{
    Pedido pedido;

    pedido.setStatus("Finalizado");

    QCOMPARE(pedido.getStatus(), QString("Finalizado"));
}

int executarTestPedido(
    int argc,
    char *argv[]
)
{
    TestPedido teste;

    return QTest::qExec(
        &teste,
        argc,
        argv
    );
}

#include "test_pedido.moc"