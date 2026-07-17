
#include <QApplication>
#include <QDebug>

// ============================================================
// DECLARAÇÕES DAS FUNÇÕES EXECUTORAS
//
// Essas funções estarão implementadas nos respectivos
// arquivos de testes funcionais.
// ============================================================

int executarTestFuncionalFluxoPedido(
    int argc,
    char *argv[]
);

int executarTestFuncionalInterface(
    int argc,
    char *argv[]
);


// ============================================================
// MAIN PRINCIPAL DOS TESTES FUNCIONAIS
// ============================================================

int main(int argc, char *argv[])
{
    // Usamos QApplication porque um dos testes
    // trabalha com interface gráfica.
    QApplication app(argc, argv);

    int totalFalhas = 0;


    qDebug()
        << "\n========================================";

    qDebug()
        << "INICIANDO TESTES FUNCIONAIS";

    qDebug()
        << "========================================\n";


    // ========================================================
    // TESTE FUNCIONAL 1
    //
    // Fluxo dos serviços:
    //
    // EstoqueServiceImpl
    //        ↓
    // PedidoServiceImpl
    //        ↓
    // Registrar pedido
    //        ↓
    // Consultar saldo
    //        ↓
    // Reservar pedido
    // ========================================================

    qDebug()
        << "\n[1/2] Testando fluxo funcional de pedidos...\n";

    int falhasFluxoPedido =
        executarTestFuncionalFluxoPedido(
            argc,
            argv
        );

    totalFalhas +=
        falhasFluxoPedido;


    // ========================================================
    // RESULTADO PARCIAL
    // ========================================================

    if (falhasFluxoPedido == 0)
    {
        qDebug()
            << "Fluxo funcional de pedidos: OK";
    }
    else
    {
        qDebug()
            << "Fluxo funcional de pedidos: FALHOU";

        qDebug()
            << "Falhas:"
            << falhasFluxoPedido;
    }


    // ========================================================
    // TESTE FUNCIONAL 2
    //
    // Fluxo completo da interface:
    //
    // LoginWindow
    //      ↓
    // MainWindow
    //      ↓
    // PedidoWindow
    //      ↓
    // ReservaWindow
    // ========================================================

    qDebug()
        << "\n[2/2] Testando fluxo funcional da interface...\n";

    int falhasInterface =
        executarTestFuncionalInterface(
            argc,
            argv
        );

    totalFalhas +=
        falhasInterface;


    // ========================================================
    // RESULTADO PARCIAL
    // ========================================================

    if (falhasInterface == 0)
    {
        qDebug()
            << "Fluxo funcional da interface: OK";
    }
    else
    {
        qDebug()
            << "Fluxo funcional da interface: FALHOU";

        qDebug()
            << "Falhas:"
            << falhasInterface;
    }


    // ========================================================
    // RESULTADO FINAL
    // ========================================================

    qDebug()
        << "\n========================================";

    qDebug()
        << "RESULTADO FINAL DOS TESTES FUNCIONAIS";

    qDebug()
        << "========================================";


    if (totalFalhas == 0)
    {
        qDebug()
            << "TODOS OS TESTES FUNCIONAIS PASSARAM!";
    }
    else
    {
        qDebug()
            << "TOTAL DE FALHAS:"
            << totalFalhas;
    }


    qDebug()
        << "========================================\n";


    return totalFalhas;
}

