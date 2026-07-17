#include <QtTest/QtTest>
#include "../../src/models/usuario.h"

class TestUsuario : public QObject
{
    Q_OBJECT

private slots:
    void construtor_deveCriarUsuario();
};

void TestUsuario::construtor_deveCriarUsuario()
{
    usuario u;

    QVERIFY(true);
}

int executarTestUsuario(
    int argc,
    char *argv[]
)
{
    TestUsuario teste;

    return QTest::qExec(
        &teste,
        argc,
        argv
    );
}


#include "test_usuario.moc"