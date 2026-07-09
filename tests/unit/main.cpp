#include <QApplication>
#include <QDebug>

int executarTestUsuario(int argc, char *argv[]);
int executarTestProduto(int argc, char *argv[]);
int executarTestPedido(int argc, char *argv[]);
int executarTestEstoqueServiceImpl(int argc, char *argv[]);
int executarTestPedidoServiceImpl(int argc, char *argv[]);
int executarTestLoginWindow(int argc, char *argv[]);
int executarTestMainWindow(int argc, char *argv[]);
int executarTestPedidoWindow(int argc, char *argv[]);
int executarTestReservaWindow(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int totalFalhas = 0;

    qDebug() << "\n====================================";
    qDebug() << "INICIANDO TESTES UNITARIOS";
    qDebug() << "====================================\n";

    totalFalhas += executarTestUsuario(argc, argv);
    totalFalhas += executarTestProduto(argc, argv);
    totalFalhas += executarTestPedido(argc, argv);
    totalFalhas += executarTestEstoqueServiceImpl(argc, argv);
    totalFalhas += executarTestPedidoServiceImpl(argc, argv);
    totalFalhas += executarTestLoginWindow(argc, argv);
    totalFalhas += executarTestMainWindow(argc, argv);
    totalFalhas += executarTestPedidoWindow(argc, argv);
    totalFalhas += executarTestReservaWindow(argc, argv);

    qDebug() << "\n====================================";
    qDebug() << "RESULTADO FINAL";
    qDebug() << "====================================";

    if (totalFalhas == 0)
        qDebug() << "TODOS OS TESTES UNITARIOS PASSARAM!";
    else
        qDebug() << "TOTAL DE FALHAS:" << totalFalhas;

    qDebug() << "====================================\n";

    return totalFalhas;
}