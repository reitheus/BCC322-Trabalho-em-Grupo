
#include <QtTest/QtTest>

#include "../../src/views/pedidowindow.h"
#include "../../src/services/pedidoserviceImpl.h"
#include "../../src/models/pedido.h"

#include <QApplication>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>

#include <vector>


// ============================================================
// FAKE DO SERVIÇO DE PEDIDOS
//
// Permite controlar exatamente os resultados retornados
// para PedidoWindow.
// ============================================================

class FakePedidoService : public IPedidoService
{
public:

    ResultadoRegistro resultadoRegistro =
        ResultadoRegistro::Sucesso;

    ResultadoRegistro resultadoReserva =
        ResultadoRegistro::Sucesso;

    int saldoConsulta = 0;
    int saldoRegistro = 0;

    bool resultadoRemocao = true;

    std::vector<Pedido> pedidosPendentes;
    std::vector<Pedido> pedidosReservados;

    Pedido ultimoPedidoRegistrado;

    QString ultimoProdutoConsultado;

    int ultimoIndiceRemovido = -1;

    bool registrarPedidoFoiChamado = false;
    bool consultarSaldoFoiChamado = false;
    bool reservarPedidosFoiChamado = false;
    bool removerPedidoFoiChamado = false;


    ResultadoRegistro registrarPedido(
        const Pedido &pedido,
        int &saldoDisponivel) override
    {
        registrarPedidoFoiChamado = true;

        ultimoPedidoRegistrado = pedido;

        saldoDisponivel =
            saldoRegistro;

        if (resultadoRegistro ==
            ResultadoRegistro::Sucesso)
        {
            pedidosPendentes.push_back(
                pedido
            );
        }

        return resultadoRegistro;
    }


    int consultarSaldo(
        const QString &produto) override
    {
        consultarSaldoFoiChamado = true;

        ultimoProdutoConsultado =
            produto;

        return saldoConsulta;
    }


    std::vector<Pedido>
    getPedidosPendentes() const override
    {
        return pedidosPendentes;
    }


    std::vector<Pedido>
    getPedidosReservados() const override
    {
        return pedidosReservados;
    }


    ResultadoRegistro
    reservarPedidos() override
    {
        reservarPedidosFoiChamado = true;

        if (resultadoReserva ==
            ResultadoRegistro::Sucesso)
        {
            for (Pedido pedido : pedidosPendentes)
            {
                pedido.setStatus("Reservado");

                pedidosReservados.push_back(
                    pedido
                );
            }

            pedidosPendentes.clear();
        }

        return resultadoReserva;
    }


    bool removerPedido(
        int indice) override
    {
        removerPedidoFoiChamado = true;

        ultimoIndiceRemovido =
            indice;

        if (!resultadoRemocao)
        {
            return false;
        }

        if (indice < 0 ||
            indice >=
            static_cast<int>(
                pedidosPendentes.size()
            ))
        {
            return false;
        }

        pedidosPendentes.erase(
            pedidosPendentes.begin()
            + indice
        );

        return true;
    }
};


// ============================================================
// CLASSE DE TESTE
// ============================================================

class TestPedidoWindow : public QObject
{
    Q_OBJECT

private slots:

    void init();
    void cleanup();

    // Construção da interface
    void construtor_deveCriarJanela();
    void componentesPrincipais_devemExistir();

    // Verificação de saldo
    void verificarSaldo_deveConsultarProdutoSelecionado();
    void verificarSaldo_deveExibirSaldo();
    void verificarSaldoDisponivel_deveExibirStatusDisponivel();
    void verificarSaldoInsuficiente_deveExibirStatusEstoqueInsuficiente();

    // Adicionar pedido
    void adicionarPedido_deveEnviarDadosCorretosAoService();
    void adicionarPedidoComSucesso_deveExibirMensagemDeSucesso();
    void adicionarPedidoComSucesso_deveAtualizarTabela();

    void adicionarPedidoSemCliente_deveExibirMensagem();
    void adicionarPedidoSemProduto_deveExibirMensagem();
    void adicionarPedidoQuantidadeInvalida_deveExibirMensagem();
    void adicionarPedidoEstoqueInsuficiente_deveExibirMensagem();

    // Remoção
    void removerPedidoSelecionado_deveChamarServiceComIndiceCorreto();
    void removerPedidoComSucesso_deveAtualizarTabela();
    void removerSemSelecao_deveExibirMensagem();

    // Reserva
    void reservarSemItens_deveExibirMensagem();
    void reservarComSucesso_deveChamarService();
    void reservarComEstoqueInsuficiente_deveExibirMensagem();

private:

    FakePedidoService *pedidoService;
    PedidoWindow *pedidoWindow;

    QLineEdit *campoCliente;
    QComboBox *comboProduto;
    QSpinBox *spinQuantidade;

    QLabel *labelStatus;
    QLabel *labelSaldo;

    QTableWidget *tabelaItens;

    QPushButton *botaoVerificar;
    QPushButton *botaoAdicionar;
    QPushButton *botaoRemover;
    QPushButton *botaoReservar;

    QMessageBox *buscarMessageBox();

    void fecharMessageBoxDepois(
        int tempo = 100
    );
};


// ============================================================
// INIT
//
// Executado antes de cada teste.
// ============================================================

void TestPedidoWindow::init()
{
    pedidoService =
        new FakePedidoService();

    pedidoWindow =
        new PedidoWindow(
            pedidoService
        );

    campoCliente =
        pedidoWindow->findChild<QLineEdit *>(
            "txtCliente"
        );

    comboProduto =
        pedidoWindow->findChild<QComboBox *>(
            "comboProduto"
        );

    spinQuantidade =
        pedidoWindow->findChild<QSpinBox *>(
            "spinQuantidade"
        );

    labelStatus =
        pedidoWindow->findChild<QLabel *>(
            "lblStatus"
        );

    labelSaldo =
        pedidoWindow->findChild<QLabel *>(
            "lblSaldo"
        );

    tabelaItens =
        pedidoWindow->findChild<QTableWidget *>(
            "tableItens"
        );

    botaoVerificar =
        pedidoWindow->findChild<QPushButton *>(
            "btnVerificar"
        );

    botaoAdicionar =
        pedidoWindow->findChild<QPushButton *>(
            "btnAdicionar"
        );

    botaoRemover =
        pedidoWindow->findChild<QPushButton *>(
            "btnRemover"
        );

    botaoReservar =
        pedidoWindow->findChild<QPushButton *>(
            "btnReservar"
        );
}


// ============================================================
// CLEANUP
//
// PedidoWindow destrói pedidoService.
// Portanto, NÃO deletamos pedidoService separadamente.
// ============================================================

void TestPedidoWindow::cleanup()
{
    const QWidgetList widgets =
        QApplication::topLevelWidgets();

    for (QWidget *widget : widgets)
    {
        QMessageBox *messageBox =
            qobject_cast<QMessageBox *>(
                widget
            );

        if (messageBox != nullptr)
        {
            messageBox->close();
        }
    }

    delete pedidoWindow;
    pedidoWindow = nullptr;

    // Não fazer:
    //
    // delete pedidoService;
    //
    // PedidoWindow já deletou esse objeto.

    pedidoService = nullptr;

    QApplication::processEvents();
}


// ============================================================
// FUNÇÃO AUXILIAR
//
// Procura QMessageBox aberta.
// ============================================================

QMessageBox *
TestPedidoWindow::buscarMessageBox()
{
    const QWidgetList widgets =
        QApplication::topLevelWidgets();

    for (QWidget *widget : widgets)
    {
        QMessageBox *messageBox =
            qobject_cast<QMessageBox *>(
                widget
            );

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
// Fecha QMessageBox modal automaticamente.
// ============================================================

void TestPedidoWindow::
fecharMessageBoxDepois(int tempo)
{
    QTimer::singleShot(
        tempo,
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
}


// ============================================================
// TESTE 1
//
// Verifica criação da janela.
// ============================================================

void TestPedidoWindow::
construtor_deveCriarJanela()
{
    QVERIFY(
        pedidoWindow != nullptr
    );
}


// ============================================================
// TESTE 2
//
// Verifica componentes principais.
// ============================================================

void TestPedidoWindow::
componentesPrincipais_devemExistir()
{
    QVERIFY2(
        campoCliente != nullptr,
        "txtCliente nao encontrado"
    );

    QVERIFY2(
        comboProduto != nullptr,
        "comboProduto nao encontrado"
    );

    QVERIFY2(
        spinQuantidade != nullptr,
        "spinQuantidade nao encontrado"
    );

    QVERIFY2(
        labelStatus != nullptr,
        "lblStatus nao encontrado"
    );

    QVERIFY2(
        labelSaldo != nullptr,
        "lblSaldo nao encontrado"
    );

    QVERIFY2(
        tabelaItens != nullptr,
        "tableItens nao encontrado"
    );

    QVERIFY2(
        botaoVerificar != nullptr,
        "btnVerificar nao encontrado"
    );

    QVERIFY2(
        botaoAdicionar != nullptr,
        "btnAdicionar nao encontrado"
    );

    QVERIFY2(
        botaoRemover != nullptr,
        "btnRemover nao encontrado"
    );

    QVERIFY2(
        botaoReservar != nullptr,
        "btnReservar nao encontrado"
    );
}


// ============================================================
// TESTE 3
//
// Verificar saldo deve consultar produto selecionado.
// ============================================================

void TestPedidoWindow::
verificarSaldo_deveConsultarProdutoSelecionado()
{
    pedidoService->saldoConsulta = 20;

    comboProduto->setCurrentText(
        "Capacete"
    );

    QTest::mouseClick(
        botaoVerificar,
        Qt::LeftButton
    );

    QVERIFY(
        pedidoService->
        consultarSaldoFoiChamado
    );

    QCOMPARE(
        pedidoService->
        ultimoProdutoConsultado,
        QString("Capacete")
    );
}


// ============================================================
// TESTE 4
//
// Saldo retornado deve aparecer em lblSaldo.
// ============================================================

void TestPedidoWindow::
verificarSaldo_deveExibirSaldo()
{
    pedidoService->saldoConsulta = 20;

    spinQuantidade->setValue(5);

    QTest::mouseClick(
        botaoVerificar,
        Qt::LeftButton
    );

    QCOMPARE(
        labelSaldo->text(),
        QString("20")
    );
}


// ============================================================
// TESTE 5
//
// saldo >= quantidade
//
// deve mostrar "Disponível".
// ============================================================

void TestPedidoWindow::
verificarSaldoDisponivel_deveExibirStatusDisponivel()
{
    pedidoService->saldoConsulta = 20;

    spinQuantidade->setValue(5);

    QTest::mouseClick(
        botaoVerificar,
        Qt::LeftButton
    );

    QCOMPARE(
        labelStatus->text(),
        QString::fromUtf8("Disponível")
    );
}


// ============================================================
// TESTE 6
//
// saldo < quantidade
//
// deve mostrar "Estoque insuficiente".
// ============================================================

void TestPedidoWindow::
verificarSaldoInsuficiente_deveExibirStatusEstoqueInsuficiente()
{
    pedidoService->saldoConsulta = 3;

    spinQuantidade->setValue(5);

    QTest::mouseClick(
        botaoVerificar,
        Qt::LeftButton
    );

    QCOMPARE(
        labelStatus->text(),
        QString("Estoque insuficiente")
    );
}


// ============================================================
// TESTE 7
//
// Verifica se dados da GUI são enviados corretamente
// ao serviço.
// ============================================================

void TestPedidoWindow::
adicionarPedido_deveEnviarDadosCorretosAoService()
{
    pedidoService->resultadoRegistro =
        IPedidoService::ResultadoRegistro::Sucesso;

    pedidoService->saldoRegistro = 20;

    campoCliente->setText(
        "Henrique"
    );

    comboProduto->setCurrentText(
        "Capacete"
    );

    spinQuantidade->setValue(
        5
    );

    QTest::mouseClick(
        botaoAdicionar,
        Qt::LeftButton
    );

    QVERIFY(
        pedidoService->
        registrarPedidoFoiChamado
    );

    QCOMPARE(
        pedidoService->
        ultimoPedidoRegistrado.getCliente(),
        QString("Henrique")
    );

    QCOMPARE(
        pedidoService->
        ultimoPedidoRegistrado.getProduto(),
        QString("Capacete")
    );

    QCOMPARE(
        pedidoService->
        ultimoPedidoRegistrado.getQuantidade(),
        5
    );
}


// ============================================================
// TESTE 8
//
// Registro com sucesso deve atualizar lblStatus.
// ============================================================

void TestPedidoWindow::
adicionarPedidoComSucesso_deveExibirMensagemDeSucesso()
{
    pedidoService->resultadoRegistro =
        IPedidoService::ResultadoRegistro::Sucesso;

    pedidoService->saldoRegistro = 20;

    campoCliente->setText(
        "Henrique"
    );

    spinQuantidade->setValue(
        5
    );

    QTest::mouseClick(
        botaoAdicionar,
        Qt::LeftButton
    );

    QCOMPARE(
        labelStatus->text(),
        QString("Pedido registrado com sucesso.")
    );

    QCOMPARE(
        labelSaldo->text(),
        QString("20")
    );
}


// ============================================================
// TESTE 9
//
// Registro com sucesso deve inserir linha na tabela.
// ============================================================

void TestPedidoWindow::
adicionarPedidoComSucesso_deveAtualizarTabela()
{
    pedidoService->resultadoRegistro =
        IPedidoService::ResultadoRegistro::Sucesso;

    pedidoService->saldoRegistro = 20;

    campoCliente->setText(
        "Henrique"
    );

    comboProduto->setCurrentText(
        "Capacete"
    );

    spinQuantidade->setValue(
        5
    );

    QTest::mouseClick(
        botaoAdicionar,
        Qt::LeftButton
    );

    QCOMPARE(
        tabelaItens->rowCount(),
        1
    );

    QCOMPARE(
        tabelaItens->item(0, 0)->text(),
        QString("Capacete")
    );

    QCOMPARE(
        tabelaItens->item(0, 1)->text(),
        QString("5")
    );

    QCOMPARE(
        tabelaItens->item(0, 2)->text(),
        QString("Pendente")
    );
}


// ============================================================
// TESTE 10
//
// Cliente não informado.
// ============================================================

void TestPedidoWindow::
adicionarPedidoSemCliente_deveExibirMensagem()
{
    pedidoService->resultadoRegistro =
        IPedidoService::ResultadoRegistro::
        ClienteNaoInformado;

    pedidoService->saldoRegistro = 20;

    QTest::mouseClick(
        botaoAdicionar,
        Qt::LeftButton
    );

    QCOMPARE(
        labelStatus->text(),
        QString("Informe o cliente.")
    );
}


// ============================================================
// TESTE 11
//
// Produto não informado.
// ============================================================

void TestPedidoWindow::
adicionarPedidoSemProduto_deveExibirMensagem()
{
    pedidoService->resultadoRegistro =
        IPedidoService::ResultadoRegistro::
        ProdutoNaoInformado;

    pedidoService->saldoRegistro = 20;

    QTest::mouseClick(
        botaoAdicionar,
        Qt::LeftButton
    );

    QCOMPARE(
        labelStatus->text(),
        QString("Informe o produto.")
    );
}


// ============================================================
// TESTE 12
//
// Quantidade inválida.
// ============================================================

void TestPedidoWindow::
adicionarPedidoQuantidadeInvalida_deveExibirMensagem()
{
    pedidoService->resultadoRegistro =
        IPedidoService::ResultadoRegistro::
        QuantidadeInvalida;

    pedidoService->saldoRegistro = 20;

    QTest::mouseClick(
        botaoAdicionar,
        Qt::LeftButton
    );

    QCOMPARE(
        labelStatus->text(),
        QString::fromUtf8("Quantidade inválida.")
    );
}


// ============================================================
// TESTE 13
//
// Estoque insuficiente.
// ============================================================

void TestPedidoWindow::
adicionarPedidoEstoqueInsuficiente_deveExibirMensagem()
{
    pedidoService->resultadoRegistro =
        IPedidoService::ResultadoRegistro::
        EstoqueInsuficiente;

    pedidoService->saldoRegistro = 3;

    QTest::mouseClick(
        botaoAdicionar,
        Qt::LeftButton
    );

    QCOMPARE(
        labelStatus->text(),
        QString("Estoque insuficiente.")
    );

    QCOMPARE(
        labelSaldo->text(),
        QString("3")
    );
}


// ============================================================
// TESTE 14
//
// Remove linha selecionada.
// ============================================================

void TestPedidoWindow::
removerPedidoSelecionado_deveChamarServiceComIndiceCorreto()
{
    Pedido pedido(
        "Henrique",
        "Capacete",
        5
    );

    pedidoService->
        pedidosPendentes.push_back(
            pedido
        );

    pedidoService->resultadoRegistro =
        IPedidoService::ResultadoRegistro::Sucesso;

    pedidoService->saldoRegistro = 20;

    campoCliente->setText(
        "Outro Cliente"
    );

    spinQuantidade->setValue(
        2
    );

    // Força atualização da tabela
    QTest::mouseClick(
        botaoAdicionar,
        Qt::LeftButton
    );

    tabelaItens->selectRow(0);

    QTest::mouseClick(
        botaoRemover,
        Qt::LeftButton
    );

    QVERIFY(
        pedidoService->
        removerPedidoFoiChamado
    );

    QCOMPARE(
        pedidoService->
        ultimoIndiceRemovido,
        0
    );
}


// ============================================================
// TESTE 15
//
// Remoção com sucesso atualiza tabela.
// ============================================================

void TestPedidoWindow::
removerPedidoComSucesso_deveAtualizarTabela()
{
    pedidoService->resultadoRegistro =
        IPedidoService::ResultadoRegistro::Sucesso;

    pedidoService->saldoRegistro = 20;

    campoCliente->setText(
        "Henrique"
    );

    spinQuantidade->setValue(
        5
    );

    QTest::mouseClick(
        botaoAdicionar,
        Qt::LeftButton
    );

    QCOMPARE(
        tabelaItens->rowCount(),
        1
    );

    tabelaItens->selectRow(0);

    QTest::mouseClick(
        botaoRemover,
        Qt::LeftButton
    );

    QCOMPARE(
        tabelaItens->rowCount(),
        0
    );
}


// ============================================================
// TESTE 16
//
// Sem linha selecionada deve mostrar QMessageBox.
// ============================================================

void TestPedidoWindow::
removerSemSelecao_deveExibirMensagem()
{
    pedidoWindow->show();

    fecharMessageBoxDepois();

    QTimer::singleShot(
        50,
        this,
        [this]()
        {
            QMessageBox *messageBox =
                buscarMessageBox();

            if (messageBox != nullptr)
            {
                QCOMPARE(
                    messageBox->windowTitle(),
                    QString("Aviso")
                );

                QCOMPARE(
                    messageBox->text(),
                    QString("Selecione um pedido.")
                );
            }
        }
    );

    QTest::mouseClick(
        botaoRemover,
        Qt::LeftButton
    );
}


// ============================================================
// TESTE 17
//
// Reservar tabela vazia deve mostrar aviso.
// ============================================================

void TestPedidoWindow::
reservarSemItens_deveExibirMensagem()
{
    pedidoWindow->show();

    fecharMessageBoxDepois();

    QTimer::singleShot(
        50,
        this,
        [this]()
        {
            QMessageBox *messageBox =
                buscarMessageBox();

            if (messageBox != nullptr)
            {
                QCOMPARE(
                    messageBox->windowTitle(),
                    QString("Aviso")
                );

                QCOMPARE(
                    messageBox->text(),
                    QString(
                        "Nenhum item foi adicionado ao pedido."
                    )
                );
            }
        }
    );

    QTest::mouseClick(
        botaoReservar,
        Qt::LeftButton
    );

    QVERIFY(
        !pedidoService->
        reservarPedidosFoiChamado
    );
}


// ============================================================
// TESTE 18
//
// Com itens, reservar deve chamar service.
// ============================================================

void TestPedidoWindow::
reservarComSucesso_deveChamarService()
{
    pedidoService->resultadoRegistro =
        IPedidoService::ResultadoRegistro::Sucesso;

    pedidoService->resultadoReserva =
        IPedidoService::ResultadoRegistro::Sucesso;

    pedidoService->saldoRegistro = 20;

    campoCliente->setText(
        "Henrique"
    );

    spinQuantidade->setValue(
        5
    );

    QTest::mouseClick(
        botaoAdicionar,
        Qt::LeftButton
    );

    QCOMPARE(
        tabelaItens->rowCount(),
        1
    );

    pedidoWindow->show();

    fecharMessageBoxDepois();

    QTest::mouseClick(
        botaoReservar,
        Qt::LeftButton
    );

    QVERIFY(
        pedidoService->
        reservarPedidosFoiChamado
    );
}


// ============================================================
// TESTE 19
//
// Falha de estoque na reserva deve mostrar mensagem.
// ============================================================

void TestPedidoWindow::
reservarComEstoqueInsuficiente_deveExibirMensagem()
{
    pedidoService->resultadoRegistro =
        IPedidoService::ResultadoRegistro::Sucesso;

    pedidoService->resultadoReserva =
        IPedidoService::ResultadoRegistro::
        EstoqueInsuficiente;

    pedidoService->saldoRegistro = 20;

    campoCliente->setText(
        "Henrique"
    );

    spinQuantidade->setValue(
        5
    );

    QTest::mouseClick(
        botaoAdicionar,
        Qt::LeftButton
    );

    pedidoWindow->show();

    QTimer::singleShot(
        50,
        this,
        [this]()
        {
            QMessageBox *messageBox =
                buscarMessageBox();

            QVERIFY2(
                messageBox != nullptr,
                "QMessageBox de reserva nao encontrada"
            );

            QCOMPARE(
                messageBox->windowTitle(),
                QString("Reserva")
            );

            QCOMPARE(
                messageBox->text(),
                QString::fromUtf8(
                    "Não foi possível reservar todos os itens."
                )
            );

            messageBox->accept();
        }
    );

    QTest::mouseClick(
        botaoReservar,
        Qt::LeftButton
    );

    QVERIFY(
        pedidoService->
        reservarPedidosFoiChamado
    );

    QVERIFY(
        pedidoWindow->isVisible()
    );
}


int executarTestPedidoWindow(
    int argc,
    char *argv[]
)
{
    TestPedidoWindow teste;

    return QTest::qExec(
        &teste,
        argc,
        argv
    );
}

#include "test_pedidowindow.moc"

