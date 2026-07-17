
#include <QtTest/QtTest>

#include "../../src/views/loginwindow.h"
#include "../../src/views/mainwindow.h"
#include "../../src/services/pedidoserviceImpl.h"

#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QApplication>
#include <QTimer>
#include <QWidget>


// ============================================================
// FAKE DO SERVIÇO DE PEDIDOS
// ============================================================

class FakePedidoService : public IPedidoService
{
public:

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
        return {};
    }

    std::vector<Pedido>
    getPedidosReservados() const override
    {
        return {};
    }

    ResultadoRegistro
    reservarPedidos() override
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

class TestLoginWindow : public QObject
{
    Q_OBJECT

private slots:

    void init();
    void cleanup();

    void construtor_deveCriarJanela();

    void camposDeLogin_devemExistir();
    void botaoEntrar_deveExistir();

    void usuario_deveReceberTextoDigitado();
    void senha_deveReceberTextoDigitado();

    void loginCorreto_deveFecharLoginWindow();
    void loginCorreto_deveAbrirMainWindow();

    void loginIncorreto_deveExibirMensagemDeErro();
    void loginIncorreto_deveManterLoginWindowAberta();

    void loginComUsuarioVazio_deveExibirErro();
    void loginComSenhaVazia_deveExibirErro();

private:

    FakePedidoService *pedidoService;
    LoginWindow *loginWindow;

    QLineEdit *campoUsuario;
    QLineEdit *campoSenha;
    QPushButton *botaoEntrar;

    QString mensagemEsperada;

    QMessageBox *buscarMessageBox();
    MainWindow *buscarMainWindow();

    void fecharJanelasAuxiliares();
};


// ============================================================
// INIT
//
// Executado ANTES de cada teste
// ============================================================

void TestLoginWindow::init()
{
    pedidoService =
        new FakePedidoService();

    loginWindow =
        new LoginWindow(pedidoService);

    campoUsuario =
        loginWindow->findChild<QLineEdit *>(
            "txtUsuario"
        );

    campoSenha =
        loginWindow->findChild<QLineEdit *>(
            "txtsenha"
        );

    botaoEntrar =
        loginWindow->findChild<QPushButton *>(
            "btnEntrar"
        );

    mensagemEsperada =
        "Usuário ou senha inválidos!";
}


// ============================================================
// CLEANUP
//
// Executado DEPOIS de cada teste
// ============================================================

void TestLoginWindow::cleanup()
{
    fecharJanelasAuxiliares();

    delete loginWindow;
    loginWindow = nullptr;

    delete pedidoService;
    pedidoService = nullptr;
}


// ============================================================
// FUNÇÃO AUXILIAR
//
// Procura uma QMessageBox aberta
// ============================================================

QMessageBox *
TestLoginWindow::buscarMessageBox()
{
    const QWidgetList widgets =
        QApplication::topLevelWidgets();

    for (QWidget *widget : widgets)
    {
        QMessageBox *messageBox =
            qobject_cast<QMessageBox *>(widget);

        if (messageBox != nullptr)
        {
            return messageBox;
        }
    }

    return nullptr;
}


// ============================================================
// FUNÇÃO AUXILIAR
//
// Procura uma MainWindow aberta
// ============================================================

MainWindow *
TestLoginWindow::buscarMainWindow()
{
    const QWidgetList widgets =
        QApplication::topLevelWidgets();

    for (QWidget *widget : widgets)
    {
        MainWindow *mainWindow =
            qobject_cast<MainWindow *>(widget);

        if (mainWindow != nullptr)
        {
            return mainWindow;
        }
    }

    return nullptr;
}


// ============================================================
// FUNÇÃO AUXILIAR
//
// Fecha janelas criadas durante os testes
// ============================================================

void TestLoginWindow::fecharJanelasAuxiliares()
{
    const QWidgetList widgets =
        QApplication::topLevelWidgets();

    for (QWidget *widget : widgets)
    {
        if (widget != loginWindow)
        {
            widget->close();
            widget->deleteLater();
        }
    }

    QApplication::processEvents();
}


// ============================================================
// TESTE 1
// Verifica se LoginWindow pode ser criada
// ============================================================

void TestLoginWindow::
construtor_deveCriarJanela()
{
    QVERIFY(loginWindow != nullptr);
}


// ============================================================
// TESTE 2
// Verifica existência dos campos
// ============================================================

void TestLoginWindow::
camposDeLogin_devemExistir()
{
    QVERIFY2(
        campoUsuario != nullptr,
        "Campo txtUsuario nao foi encontrado"
    );

    QVERIFY2(
        campoSenha != nullptr,
        "Campo txtsenha nao foi encontrado"
    );
}


// ============================================================
// TESTE 3
// Verifica existência do botão
// ============================================================

void TestLoginWindow::
botaoEntrar_deveExistir()
{
    QVERIFY2(
        botaoEntrar != nullptr,
        "Botao btnEntrar nao foi encontrado"
    );
}


// ============================================================
// TESTE 4
// Simula digitação no campo usuário
// ============================================================

void TestLoginWindow::
usuario_deveReceberTextoDigitado()
{
    QVERIFY(campoUsuario != nullptr);

    loginWindow->show();

    QVERIFY(
        QTest::qWaitForWindowExposed(
            loginWindow
        )
    );

    QTest::keyClicks(
        campoUsuario,
        "admin"
    );

    QCOMPARE(
        campoUsuario->text(),
        QString("admin")
    );
}


// ============================================================
// TESTE 5
// Simula digitação no campo senha
// ============================================================

void TestLoginWindow::
senha_deveReceberTextoDigitado()
{
    QVERIFY(campoSenha != nullptr);

    loginWindow->show();

    QVERIFY(
        QTest::qWaitForWindowExposed(
            loginWindow
        )
    );

    QTest::keyClicks(
        campoSenha,
        "123"
    );

    QCOMPARE(
        campoSenha->text(),
        QString("123")
    );
}


// ============================================================
// TESTE 6
// Login correto deve fechar LoginWindow
// ============================================================

void TestLoginWindow::
loginCorreto_deveFecharLoginWindow()
{
    QVERIFY(campoUsuario != nullptr);
    QVERIFY(campoSenha != nullptr);
    QVERIFY(botaoEntrar != nullptr);

    loginWindow->show();

    QVERIFY(
        QTest::qWaitForWindowExposed(
            loginWindow
        )
    );

    QTest::keyClicks(
        campoUsuario,
        "admin"
    );

    QTest::keyClicks(
        campoSenha,
        "123"
    );

    QTest::mouseClick(
        botaoEntrar,
        Qt::LeftButton
    );

    QApplication::processEvents();

    QVERIFY(
        !loginWindow->isVisible()
    );
}


// ============================================================
// TESTE 7
// Login correto deve abrir MainWindow
// ============================================================

void TestLoginWindow::
loginCorreto_deveAbrirMainWindow()
{
    QVERIFY(campoUsuario != nullptr);
    QVERIFY(campoSenha != nullptr);
    QVERIFY(botaoEntrar != nullptr);

    loginWindow->show();

    QVERIFY(
        QTest::qWaitForWindowExposed(
            loginWindow
        )
    );

    QTest::keyClicks(
        campoUsuario,
        "admin"
    );

    QTest::keyClicks(
        campoSenha,
        "123"
    );

    QTest::mouseClick(
        botaoEntrar,
        Qt::LeftButton
    );

    QApplication::processEvents();

    MainWindow *mainWindow =
        buscarMainWindow();

    QVERIFY2(
        mainWindow != nullptr,
        "MainWindow nao foi aberta apos login correto"
    );

    QVERIFY(
        mainWindow->isVisible()
    );
}


// ============================================================
// TESTE 8
// Login incorreto deve mostrar QMessageBox
// ============================================================

void TestLoginWindow::
loginIncorreto_deveExibirMensagemDeErro()
{
    QVERIFY(campoUsuario != nullptr);
    QVERIFY(campoSenha != nullptr);
    QVERIFY(botaoEntrar != nullptr);

    loginWindow->show();

    QVERIFY(
        QTest::qWaitForWindowExposed(
            loginWindow
        )
    );

    QTest::keyClicks(
        campoUsuario,
        "usuarioErrado"
    );

    QTest::keyClicks(
        campoSenha,
        "senhaErrada"
    );

    // QMessageBox::warning() é modal.
    // O timer fecha a mensagem depois de verificá-la.
    QTimer::singleShot(
        100,
        this,
        [this]()
        {
            QMessageBox *messageBox =
                buscarMessageBox();

            QVERIFY2(
                messageBox != nullptr,
                "QMessageBox de erro nao foi encontrada"
            );

            QCOMPARE(
                messageBox->windowTitle(),
                QString("Erro")
            );

            QCOMPARE(
                messageBox->text(),
                mensagemEsperada
            );

            messageBox->accept();
        }
    );

    QTest::mouseClick(
        botaoEntrar,
        Qt::LeftButton
    );
}


// ============================================================
// TESTE 9
// Login incorreto deve manter janela aberta
// ============================================================

void TestLoginWindow::
loginIncorreto_deveManterLoginWindowAberta()
{
    QVERIFY(campoUsuario != nullptr);
    QVERIFY(campoSenha != nullptr);
    QVERIFY(botaoEntrar != nullptr);

    loginWindow->show();

    QVERIFY(
        QTest::qWaitForWindowExposed(
            loginWindow
        )
    );

    QTest::keyClicks(
        campoUsuario,
        "errado"
    );

    QTest::keyClicks(
        campoSenha,
        "999"
    );

    QTimer::singleShot(
        100,
        this,
        [this]()
        {
            QMessageBox *messageBox =
                buscarMessageBox();

            if (messageBox != nullptr)
            {
                messageBox->accept();
            }
        }
    );

    QTest::mouseClick(
        botaoEntrar,
        Qt::LeftButton
    );

    QApplication::processEvents();

    QVERIFY(
        loginWindow->isVisible()
    );
}


// ============================================================
// TESTE 10
// Usuário vazio deve gerar erro
// ============================================================

void TestLoginWindow::
loginComUsuarioVazio_deveExibirErro()
{
    QVERIFY(campoUsuario != nullptr);
    QVERIFY(campoSenha != nullptr);
    QVERIFY(botaoEntrar != nullptr);

    loginWindow->show();

    QVERIFY(
        QTest::qWaitForWindowExposed(
            loginWindow
        )
    );

    QTest::keyClicks(
        campoSenha,
        "123"
    );

    QTimer::singleShot(
        100,
        this,
        [this]()
        {
            QMessageBox *messageBox =
                buscarMessageBox();

            QVERIFY2(
                messageBox != nullptr,
                "Mensagem de erro nao foi exibida"
            );

            QCOMPARE(
                messageBox->text(),
                mensagemEsperada
            );

            messageBox->accept();
        }
    );

    QTest::mouseClick(
        botaoEntrar,
        Qt::LeftButton
    );
}


// ============================================================
// TESTE 11
// Senha vazia deve gerar erro
// ============================================================

void TestLoginWindow::
loginComSenhaVazia_deveExibirErro()
{
    QVERIFY(campoUsuario != nullptr);
    QVERIFY(campoSenha != nullptr);
    QVERIFY(botaoEntrar != nullptr);

    loginWindow->show();

    QVERIFY(
        QTest::qWaitForWindowExposed(
            loginWindow
        )
    );

    QTest::keyClicks(
        campoUsuario,
        "admin"
    );

    QTimer::singleShot(
        100,
        this,
        [this]()
        {
            QMessageBox *messageBox =
                buscarMessageBox();

            QVERIFY2(
                messageBox != nullptr,
                "Mensagem de erro nao foi exibida"
            );

            QCOMPARE(
                messageBox->text(),
                mensagemEsperada
            );

            messageBox->accept();
        }
    );

    QTest::mouseClick(
        botaoEntrar,
        Qt::LeftButton
    );
}

int executarTestLoginWindow(
    int argc,
    char *argv[]
)
{
    TestLoginWindow teste;

    return QTest::qExec(
        &teste,
        argc,
        argv
    );
}

#include "test_loginwindow.moc"
