#include <QtTest/QtTest>
#include "../../src/models/produto.h"

class TestProduto : public QObject
{
    Q_OBJECT

private slots:
    void construtorPadrao_deveCriarProduto();
    void construtorComParametros_deveDefinirNomeEQuantidade();
    void setNome_deveAlterarNome();
    void setQuantidade_deveAlterarQuantidade();
};

void TestProduto::construtorPadrao_deveCriarProduto()
{
    Produto produto;

    QVERIFY(true);
}

void TestProduto::construtorComParametros_deveDefinirNomeEQuantidade()
{
    Produto produto("Racao", 10);

    QCOMPARE(produto.getNome(), QString("Racao"));
    QCOMPARE(produto.getQuantidade(), 10);
}

void TestProduto::setNome_deveAlterarNome()
{
    Produto produto;

    produto.setNome("Milho");

    QCOMPARE(produto.getNome(), QString("Milho"));
}

void TestProduto::setQuantidade_deveAlterarQuantidade()
{
    Produto produto;

    produto.setQuantidade(25);

    QCOMPARE(produto.getQuantidade(), 25);
}

int executarTestProduto(
    int argc,
    char *argv[]
)
{
    TestProduto teste;

    return QTest::qExec(
        &teste,
        argc,
        argv
    );
}

#include "test_produto.moc"
