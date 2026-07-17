
#include <QtTest/QtTest>

#include "../../src/services/pedidoserviceImpl.h"
#include "../../src/services/estoqueserviceImpl.h"
#include "../../src/models/pedido.h"

#include <QMap>

// ============================================================
// FAKE DO SERVIÇO DE ESTOQUE
// ============================================================

class FakeEstoqueService : public IEstoqueService
{
public:
    QMap<QString, int> saldos;

    int verificarSaldo(const QString &produto) override
    {
        return saldos.value(produto, 0);
    }

    ResultadoReserva reservarEstoque(
        const QString &produto,
        int quantidade) override
    {
        if (!saldos.contains(produto))
        {
            return ResultadoReserva::ProdutoNaoEncontrado;
        }

        if (quantidade <= 0)
        {
            return ResultadoReserva::QuantidadeInvalida;
        }

        if (quantidade > saldos[produto])
        {
            return ResultadoReserva::EstoqueInsuficiente;
        }

        saldos[produto] -= quantidade;

        return ResultadoReserva::Sucesso;
    }
};


// ============================================================
// CLASSE DE TESTE
// ============================================================

class TestPedidoServiceImpl : public QObject
{
    Q_OBJECT

private slots:

    void registrarPedido_deveRetornarSucesso();
    void registrarPedido_deveAdicionarPedidoAListaDePendentes();

    void registrarPedido_deveRetornarClienteNaoInformado();
    void registrarPedido_deveRetornarClienteNaoInformadoParaEspacos();

    void registrarPedido_deveRetornarProdutoNaoInformado();
    void registrarPedido_deveRetornarProdutoNaoInformadoParaEspacos();

    void registrarPedido_deveRetornarQuantidadeInvalidaParaZero();
    void registrarPedido_deveRetornarQuantidadeInvalidaParaNegativo();

    void registrarPedido_deveRetornarEstoqueInsuficiente();

    void consultarSaldo_deveRetornarSaldoDoEstoque();
    void consultarSaldo_deveDescontarQuantidadeComprometida();

    void registrarDoisPedidos_deveDescontarPedidosPendentesDoSaldo();

    void removerPedido_deveRemoverPedidoValido();
    void removerPedido_deveRetornarFalseParaIndiceNegativo();
    void removerPedido_deveRetornarFalseParaIndiceInexistente();

    void reservarPedidos_deveMoverPedidoParaReservados();
    void reservarPedidos_deveAlterarStatusParaReservado();
    void reservarPedidos_deveDiminuirSaldoDoEstoque();

    void reservarPedidos_comFalha_deveManterPedidoPendente();
    void reservarPedidos_comFalha_deveRetornarEstoqueInsuficiente();

    void reservarPedidosSemPendentes_deveRetornarSucesso();
};


// ============================================================
// TESTE 1
// Pedido válido deve ser registrado com sucesso
// ============================================================

void TestPedidoServiceImpl::
registrarPedido_deveRetornarSucesso()
{
    FakeEstoqueService estoque;
    estoque.saldos["Capacete"] = 20;

    PedidoServiceImpl service(&estoque);

    Pedido pedido(
        "Henrique",
        "Capacete",
        5
    );

    int saldoDisponivel = 0;

    auto resultado =
        service.registrarPedido(
            pedido,
            saldoDisponivel
        );

    QCOMPARE(
        resultado,
        IPedidoService::ResultadoRegistro::Sucesso
    );

    QCOMPARE(saldoDisponivel, 20);
}


// ============================================================
// TESTE 2
// Pedido válido deve entrar na lista de pendentes
// ============================================================

void TestPedidoServiceImpl::
registrarPedido_deveAdicionarPedidoAListaDePendentes()
{
    FakeEstoqueService estoque;
    estoque.saldos["Capacete"] = 20;

    PedidoServiceImpl service(&estoque);

    Pedido pedido(
        "Henrique",
        "Capacete",
        5
    );

    int saldoDisponivel = 0;

    service.registrarPedido(
        pedido,
        saldoDisponivel
    );

    std::vector<Pedido> pendentes =
        service.getPedidosPendentes();

    QCOMPARE(
        static_cast<int>(pendentes.size()),
        1
    );

    QCOMPARE(
        pendentes[0].getCliente(),
        QString("Henrique")
    );

    QCOMPARE(
        pendentes[0].getProduto(),
        QString("Capacete")
    );

    QCOMPARE(
        pendentes[0].getQuantidade(),
        5
    );
}


// ============================================================
// TESTE 3
// Cliente vazio
// ============================================================

void TestPedidoServiceImpl::
registrarPedido_deveRetornarClienteNaoInformado()
{
    FakeEstoqueService estoque;
    estoque.saldos["Capacete"] = 20;

    PedidoServiceImpl service(&estoque);

    Pedido pedido(
        "",
        "Capacete",
        5
    );

    int saldoDisponivel = 0;

    auto resultado =
        service.registrarPedido(
            pedido,
            saldoDisponivel
        );

    QCOMPARE(
        resultado,
        IPedidoService::ResultadoRegistro::ClienteNaoInformado
    );

    QCOMPARE(
        static_cast<int>(
            service.getPedidosPendentes().size()
        ),
        0
    );
}


// ============================================================
// TESTE 4
// Cliente contendo somente espaços
// ============================================================

void TestPedidoServiceImpl::
registrarPedido_deveRetornarClienteNaoInformadoParaEspacos()
{
    FakeEstoqueService estoque;
    estoque.saldos["Capacete"] = 20;

    PedidoServiceImpl service(&estoque);

    Pedido pedido(
        "   ",
        "Capacete",
        5
    );

    int saldoDisponivel = 0;

    auto resultado =
        service.registrarPedido(
            pedido,
            saldoDisponivel
        );

    QCOMPARE(
        resultado,
        IPedidoService::ResultadoRegistro::ClienteNaoInformado
    );
}


// ============================================================
// TESTE 5
// Produto vazio
// ============================================================

void TestPedidoServiceImpl::
registrarPedido_deveRetornarProdutoNaoInformado()
{
    FakeEstoqueService estoque;

    PedidoServiceImpl service(&estoque);

    Pedido pedido(
        "Henrique",
        "",
        5
    );

    int saldoDisponivel = 0;

    auto resultado =
        service.registrarPedido(
            pedido,
            saldoDisponivel
        );

    QCOMPARE(
        resultado,
        IPedidoService::ResultadoRegistro::ProdutoNaoInformado
    );
}


// ============================================================
// TESTE 6
// Produto contendo somente espaços
// ============================================================

void TestPedidoServiceImpl::
registrarPedido_deveRetornarProdutoNaoInformadoParaEspacos()
{
    FakeEstoqueService estoque;

    PedidoServiceImpl service(&estoque);

    Pedido pedido(
        "Henrique",
        "   ",
        5
    );

    int saldoDisponivel = 0;

    auto resultado =
        service.registrarPedido(
            pedido,
            saldoDisponivel
        );

    QCOMPARE(
        resultado,
        IPedidoService::ResultadoRegistro::ProdutoNaoInformado
    );
}


// ============================================================
// TESTE 7
// Quantidade zero
// ============================================================

void TestPedidoServiceImpl::
registrarPedido_deveRetornarQuantidadeInvalidaParaZero()
{
    FakeEstoqueService estoque;
    estoque.saldos["Capacete"] = 20;

    PedidoServiceImpl service(&estoque);

    Pedido pedido(
        "Henrique",
        "Capacete",
        0
    );

    int saldoDisponivel = 0;

    auto resultado =
        service.registrarPedido(
            pedido,
            saldoDisponivel
        );

    QCOMPARE(
        resultado,
        IPedidoService::ResultadoRegistro::QuantidadeInvalida
    );
}


// ============================================================
// TESTE 8
// Quantidade negativa
// ============================================================

void TestPedidoServiceImpl::
registrarPedido_deveRetornarQuantidadeInvalidaParaNegativo()
{
    FakeEstoqueService estoque;
    estoque.saldos["Capacete"] = 20;

    PedidoServiceImpl service(&estoque);

    Pedido pedido(
        "Henrique",
        "Capacete",
        -5
    );

    int saldoDisponivel = 0;

    auto resultado =
        service.registrarPedido(
            pedido,
            saldoDisponivel
        );

    QCOMPARE(
        resultado,
        IPedidoService::ResultadoRegistro::QuantidadeInvalida
    );
}


// ============================================================
// TESTE 9
// Quantidade maior que o estoque
// ============================================================

void TestPedidoServiceImpl::
registrarPedido_deveRetornarEstoqueInsuficiente()
{
    FakeEstoqueService estoque;
    estoque.saldos["Capacete"] = 20;

    PedidoServiceImpl service(&estoque);

    Pedido pedido(
        "Henrique",
        "Capacete",
        25
    );

    int saldoDisponivel = 0;

    auto resultado =
        service.registrarPedido(
            pedido,
            saldoDisponivel
        );

    QCOMPARE(
        resultado,
        IPedidoService::ResultadoRegistro::EstoqueInsuficiente
    );

    QCOMPARE(saldoDisponivel, 20);

    QCOMPARE(
        static_cast<int>(
            service.getPedidosPendentes().size()
        ),
        0
    );
}


// ============================================================
// TESTE 10
// Consulta simples de saldo
// ============================================================

void TestPedidoServiceImpl::
consultarSaldo_deveRetornarSaldoDoEstoque()
{
    FakeEstoqueService estoque;
    estoque.saldos["Capacete"] = 20;

    PedidoServiceImpl service(&estoque);

    int saldo =
        service.consultarSaldo("Capacete");

    QCOMPARE(saldo, 20);
}


// ============================================================
// TESTE 11
// Pedido pendente compromete parte do saldo
// ============================================================

void TestPedidoServiceImpl::
consultarSaldo_deveDescontarQuantidadeComprometida()
{
    FakeEstoqueService estoque;
    estoque.saldos["Capacete"] = 20;

    PedidoServiceImpl service(&estoque);

    Pedido pedido(
        "Henrique",
        "Capacete",
        5
    );

    int saldoDisponivel = 0;

    auto resultado =
        service.registrarPedido(
            pedido,
            saldoDisponivel
        );

    QCOMPARE(
        resultado,
        IPedidoService::ResultadoRegistro::Sucesso
    );

    int saldo =
        service.consultarSaldo("Capacete");

    QCOMPARE(saldo, 15);
}


// ============================================================
// TESTE 12
// Dois pedidos pendentes devem comprometer o saldo
// ============================================================

void TestPedidoServiceImpl::
registrarDoisPedidos_deveDescontarPedidosPendentesDoSaldo()
{
    FakeEstoqueService estoque;
    estoque.saldos["Capacete"] = 20;

    PedidoServiceImpl service(&estoque);

    Pedido pedido1(
        "Henrique",
        "Capacete",
        5
    );

    Pedido pedido2(
        "Joao",
        "Capacete",
        7
    );

    int saldo1 = 0;
    int saldo2 = 0;

    auto resultado1 =
        service.registrarPedido(
            pedido1,
            saldo1
        );

    auto resultado2 =
        service.registrarPedido(
            pedido2,
            saldo2
        );

    QCOMPARE(
        resultado1,
        IPedidoService::ResultadoRegistro::Sucesso
    );

    QCOMPARE(
        resultado2,
        IPedidoService::ResultadoRegistro::Sucesso
    );

    QCOMPARE(saldo1, 20);

    // Antes do segundo pedido,
    // 5 unidades já estão comprometidas
    QCOMPARE(saldo2, 15);

    QCOMPARE(
        service.consultarSaldo("Capacete"),
        8
    );
}


// ============================================================
// TESTE 13
// Remover pedido válido
// ============================================================

void TestPedidoServiceImpl::
removerPedido_deveRemoverPedidoValido()
{
    FakeEstoqueService estoque;
    estoque.saldos["Capacete"] = 20;

    PedidoServiceImpl service(&estoque);

    Pedido pedido(
        "Henrique",
        "Capacete",
        5
    );

    int saldoDisponivel = 0;

    service.registrarPedido(
        pedido,
        saldoDisponivel
    );

    QCOMPARE(
        static_cast<int>(
            service.getPedidosPendentes().size()
        ),
        1
    );

    bool removeu =
        service.removerPedido(0);

    QVERIFY(removeu);

    QCOMPARE(
        static_cast<int>(
            service.getPedidosPendentes().size()
        ),
        0
    );
}


// ============================================================
// TESTE 14
// Índice negativo
// ============================================================

void TestPedidoServiceImpl::
removerPedido_deveRetornarFalseParaIndiceNegativo()
{
    FakeEstoqueService estoque;

    PedidoServiceImpl service(&estoque);

    bool removeu =
        service.removerPedido(-1);

    QVERIFY(!removeu);
}


// ============================================================
// TESTE 15
// Índice inexistente
// ============================================================

void TestPedidoServiceImpl::
removerPedido_deveRetornarFalseParaIndiceInexistente()
{
    FakeEstoqueService estoque;

    PedidoServiceImpl service(&estoque);

    bool removeu =
        service.removerPedido(10);

    QVERIFY(!removeu);
}


// ============================================================
// TESTE 16
// Reserva deve mover pedido para reservados
// ============================================================

void TestPedidoServiceImpl::
reservarPedidos_deveMoverPedidoParaReservados()
{
    FakeEstoqueService estoque;
    estoque.saldos["Capacete"] = 20;

    PedidoServiceImpl service(&estoque);

    Pedido pedido(
        "Henrique",
        "Capacete",
        5
    );

    int saldoDisponivel = 0;

    service.registrarPedido(
        pedido,
        saldoDisponivel
    );

    auto resultado =
        service.reservarPedidos();

    QCOMPARE(
        resultado,
        IPedidoService::ResultadoRegistro::Sucesso
    );

    QCOMPARE(
        static_cast<int>(
            service.getPedidosPendentes().size()
        ),
        0
    );

    QCOMPARE(
        static_cast<int>(
            service.getPedidosReservados().size()
        ),
        1
    );
}


// ============================================================
// TESTE 17
// Status deve mudar para "Reservado"
// ============================================================

void TestPedidoServiceImpl::
reservarPedidos_deveAlterarStatusParaReservado()
{
    FakeEstoqueService estoque;
    estoque.saldos["Capacete"] = 20;

    PedidoServiceImpl service(&estoque);

    Pedido pedido(
        "Henrique",
        "Capacete",
        5
    );

    int saldoDisponivel = 0;

    service.registrarPedido(
        pedido,
        saldoDisponivel
    );

    service.reservarPedidos();

    std::vector<Pedido> reservados =
        service.getPedidosReservados();

    QCOMPARE(
        static_cast<int>(reservados.size()),
        1
    );

    QCOMPARE(
        reservados[0].getStatus(),
        QString("Reservado")
    );
}


// ============================================================
// TESTE 18
// Reserva deve realmente reduzir o estoque fake
// ============================================================

void TestPedidoServiceImpl::
reservarPedidos_deveDiminuirSaldoDoEstoque()
{
    FakeEstoqueService estoque;
    estoque.saldos["Capacete"] = 20;

    PedidoServiceImpl service(&estoque);

    Pedido pedido(
        "Henrique",
        "Capacete",
        5
    );

    int saldoDisponivel = 0;

    service.registrarPedido(
        pedido,
        saldoDisponivel
    );

    service.reservarPedidos();

    QCOMPARE(
        estoque.verificarSaldo("Capacete"),
        15
    );
}


// ============================================================
// TESTE 19
// Se a reserva falhar, pedido continua pendente
// ============================================================

void TestPedidoServiceImpl::
reservarPedidos_comFalha_deveManterPedidoPendente()
{
    FakeEstoqueService estoque;
    estoque.saldos["Capacete"] = 20;

    PedidoServiceImpl service(&estoque);

    Pedido pedido(
        "Henrique",
        "Capacete",
        5
    );

    int saldoDisponivel = 0;

    auto registro =
        service.registrarPedido(
            pedido,
            saldoDisponivel
        );

    QCOMPARE(
        registro,
        IPedidoService::ResultadoRegistro::Sucesso
    );

    // Simula alteração externa no estoque
    estoque.saldos["Capacete"] = 2;

    auto resultadoReserva =
        service.reservarPedidos();

    QCOMPARE(
        resultadoReserva,
        IPedidoService::ResultadoRegistro::EstoqueInsuficiente
    );

    QCOMPARE(
        static_cast<int>(
            service.getPedidosPendentes().size()
        ),
        1
    );

    QCOMPARE(
        static_cast<int>(
            service.getPedidosReservados().size()
        ),
        0
    );
}


// ============================================================
// TESTE 20
// Falha na reserva deve retornar EstoqueInsuficiente
// ============================================================

void TestPedidoServiceImpl::
reservarPedidos_comFalha_deveRetornarEstoqueInsuficiente()
{
    FakeEstoqueService estoque;
    estoque.saldos["Capacete"] = 20;

    PedidoServiceImpl service(&estoque);

    Pedido pedido(
        "Henrique",
        "Capacete",
        5
    );

    int saldoDisponivel = 0;

    service.registrarPedido(
        pedido,
        saldoDisponivel
    );

    // Estoque muda antes da reserva
    estoque.saldos["Capacete"] = 2;

    auto resultado =
        service.reservarPedidos();

    QCOMPARE(
        resultado,
        IPedidoService::ResultadoRegistro::EstoqueInsuficiente
    );
}


// ============================================================
// TESTE 21
// Sem pedidos pendentes, reservarPedidos retorna sucesso
// ============================================================

void TestPedidoServiceImpl::
reservarPedidosSemPendentes_deveRetornarSucesso()
{
    FakeEstoqueService estoque;

    PedidoServiceImpl service(&estoque);

    auto resultado =
        service.reservarPedidos();

    QCOMPARE(
        resultado,
        IPedidoService::ResultadoRegistro::Sucesso
    );

    QCOMPARE(
        static_cast<int>(
            service.getPedidosPendentes().size()
        ),
        0
    );

    QCOMPARE(
        static_cast<int>(
            service.getPedidosReservados().size()
        ),
        0
    );
}


int executarTestPedidoServiceImpl(
    int argc,
    char *argv[]
)
{
    TestPedidoServiceImpl teste;

    return QTest::qExec(
        &teste,
        argc,
        argv
    );
}

#include "test_pedidoserviceimpl.moc"

