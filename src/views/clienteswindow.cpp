#include "clienteswindow.h"
#include "ui_clienteswindow.h"

#include <QMessageBox>
#include <QTableWidgetItem>

ClientesWindow::ClientesWindow(IClienteService *clienteService, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientesWindow)
    , clienteService(clienteService)
{
    ui->setupUi(this);

    atualizarTabela();
}

ClientesWindow::~ClientesWindow()
{
    delete ui;
}

void ClientesWindow::on_btnCadastrar_clicked()
{
    Cliente cliente(ui->txtNome->text(),
                    ui->txtCpfCnpj->text(),
                    ui->txtEmail->text(),
                    ui->txtTelefone->text());

    IClienteService::ResultadoCadastro resultado = clienteService->cadastrarCliente(cliente);

    switch (resultado) {
    case IClienteService::ResultadoCadastro::Sucesso:
        QMessageBox::information(this, "Cliente", "Cliente cadastrado com sucesso.");

        atualizarTabela();
        limparCampos();
        break;

    case IClienteService::ResultadoCadastro::NomeNaoInformado:
        QMessageBox::warning(this, "Cliente", "Informe o nome do cliente.");
        break;

    case IClienteService::ResultadoCadastro::DocumentoNaoInformado:
        QMessageBox::warning(this, "Cliente", "Informe o CPF ou CNPJ do cliente.");
        break;

    case IClienteService::ResultadoCadastro::ClienteJaExiste:
        QMessageBox::warning(this, "Cliente", "Já existe um cliente cadastrado com esse CPF/CNPJ.");
        break;
    }
}

void ClientesWindow::on_btnExcluir_clicked()
{
    int linha = ui->tableClientes->currentRow();

    if (linha < 0) {
        QMessageBox::warning(this, "Cliente", "Selecione um cliente para excluir.");

        return;
    }

    QTableWidgetItem *itemCpfCnpj = ui->tableClientes->item(linha, 1);

    if (itemCpfCnpj == nullptr) {
        return;
    }

    QString cpfCnpj = itemCpfCnpj->text();

    QMessageBox::StandardButton resposta
        = QMessageBox::question(this,
                                "Excluir cliente",
                                "Deseja realmente excluir o cliente selecionado?",
                                QMessageBox::Yes | QMessageBox::No);

    if (resposta != QMessageBox::Yes) {
        return;
    }

    if (clienteService->excluirCliente(cpfCnpj)) {
        QMessageBox::information(this, "Cliente", "Cliente excluído com sucesso.");

        atualizarTabela();
    } else {
        QMessageBox::warning(this, "Cliente", "Não foi possível excluir o cliente.");
    }
}

void ClientesWindow::atualizarTabela()
{
    ui->tableClientes->setRowCount(0);

    std::vector<Cliente> clientes = clienteService->getClientes();

    for (const Cliente &cliente : clientes) {
        int linha = ui->tableClientes->rowCount();

        ui->tableClientes->insertRow(linha);

        ui->tableClientes->setItem(linha, 0, new QTableWidgetItem(cliente.nome()));

        ui->tableClientes->setItem(linha, 1, new QTableWidgetItem(cliente.cpfCnpj()));

        ui->tableClientes->setItem(linha, 2, new QTableWidgetItem(cliente.email()));

        ui->tableClientes->setItem(linha, 3, new QTableWidgetItem(cliente.telefone()));
    }
}

void ClientesWindow::limparCampos()
{
    ui->txtNome->clear();
    ui->txtCpfCnpj->clear();
    ui->txtEmail->clear();
    ui->txtTelefone->clear();

    ui->txtNome->setFocus();
}


//void ClientesWindow::on_btnVoltar_clicked()
//{
//    if (parentWidget() != nullptr)
//    {
//        parentWidget()->show();
//   }
 //   close();
//}

void ClientesWindow::on_btnVoltar_clicked()
{
    QWidget *janelaAnterior =
        parentWidget();

    if (janelaAnterior != nullptr)
    {
        janelaAnterior->show();
    }

    close();
}

