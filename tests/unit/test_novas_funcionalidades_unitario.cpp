#include <QtTest>
#include <QSettings>
#include <QTemporaryDir>

#include "UsuarioServiceImpl.h"
#include "EstoqueServiceImpl.h"

class TestNovasFuncionalidadesUnitario : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void init();
    void usuario_deveCadastrarAtualizarRemoverEAutenticar();
    void usuario_devePersistirAposNovaInstancia();
    void estoque_devePersistirEntradaEReserva();

private:
    QTemporaryDir m_diretorio;
};

void TestNovasFuncionalidadesUnitario::initTestCase()
{
    QVERIFY(m_diretorio.isValid());
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, m_diretorio.path());
    QCoreApplication::setOrganizationName("EpiStockTestes");
    QCoreApplication::setApplicationName("NovasFuncionalidades");
}

void TestNovasFuncionalidadesUnitario::init()
{
    QSettings configuracao;
    configuracao.clear();
    configuracao.sync();
}

void TestNovasFuncionalidadesUnitario::usuario_deveCadastrarAtualizarRemoverEAutenticar()
{
    UsuarioServiceImpl servico;
    QString erro;
    const Usuario novo("Ana Silva", "ana", "senha", "ana@epistock.com", "Logístico");

    QVERIFY(servico.cadastrar(novo, &erro));
    Usuario autenticado;
    QVERIFY(servico.autenticar("ana", "senha", &autenticado));
    QCOMPARE(autenticado.nome(), QString("Ana Silva"));

    const Usuario atualizado("Ana Souza", "ana.souza", "novaSenha", "ana.souza@epistock.com", "Gestor");
    QVERIFY(servico.atualizar("ana", atualizado, &erro));
    QVERIFY(!servico.autenticar("ana", "senha"));
    QVERIFY(servico.autenticar("ana.souza", "novaSenha", &autenticado));
    QCOMPARE(autenticado.perfil(), QString("Gestor"));

    QVERIFY(servico.remover("ana.souza", &erro));
    QVERIFY(!servico.autenticar("ana.souza", "novaSenha"));
}

void TestNovasFuncionalidadesUnitario::usuario_devePersistirAposNovaInstancia()
{
    {
        UsuarioServiceImpl servico;
        QVERIFY(servico.cadastrar(Usuario("Carlos Lima", "carlos", "1234",
                                           "carlos@epistock.com", "Vendas")));
    }
    UsuarioServiceImpl servicoReaberto;
    Usuario usuario;
    QVERIFY(servicoReaberto.autenticar("carlos", "1234", &usuario));
    QCOMPARE(usuario.email(), QString("carlos@epistock.com"));
}

void TestNovasFuncionalidadesUnitario::estoque_devePersistirEntradaEReserva()
{
    {
        EstoqueServiceImpl estoque;
        QCOMPARE(estoque.verificarSaldo("Capacete"), 20);
        QVERIFY(estoque.adicionarEstoque("Capacete", 7));
        QCOMPARE(estoque.reservarEstoque("Capacete", 3), IEstoqueService::ResultadoReserva::Sucesso);
    }
    EstoqueServiceImpl estoqueReaberto;
    QCOMPARE(estoqueReaberto.verificarSaldo("Capacete"), 24);
}

QTEST_MAIN(TestNovasFuncionalidadesUnitario)
#include "test_novas_funcionalidades_unitario.moc"
