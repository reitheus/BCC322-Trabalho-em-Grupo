#include "pedidowindow.h"
#include "ui_pedidowindow.h"
#include "pedidoserviceImpl.h"
#include "Pedido.h"
#include "reservawindow.h"
#include <QMessageBox>
#include <QHeaderView>

PedidoWindow::PedidoWindow(IPedidoService *pedidoService,
                           QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PedidoWindow)
    , pedidoService(pedidoService)
{
    ui->setupUi(this);

    ui->tableItens->horizontalHeader()->setStretchLastSection(true);
    ui->tableItens->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
PedidoWindow::~PedidoWindow()
{
    delete pedidoService;
    delete ui;
}
void PedidoWindow::on_btnVerificar_clicked()
{
    int saldo =
        pedidoService->consultarSaldo(
            ui->comboProduto->currentText());

    ui->lblSaldo->setText(QString::number(saldo));

    if (saldo >= ui->spinQuantidade->value())
    {
        ui->lblStatus->setText("Disponível");
    }
    else
    {
        ui->lblStatus->setText("Estoque insuficiente");
    }
}
void PedidoWindow::on_btnAdicionar_clicked()
{
    Pedido pedido(
        ui->txtCliente->text(),
        ui->comboProduto->currentText(),
        ui->spinQuantidade->value()
        );

    int saldo;

    IPedidoService::ResultadoRegistro resultado =
        pedidoService->registrarPedido(pedido, saldo);

    switch (resultado)
    {
    case IPedidoService::ResultadoRegistro::Sucesso:
        ui->lblStatus->setText("Pedido registrado com sucesso.");
        atualizarTabela();
        break;

    case IPedidoService::ResultadoRegistro::ClienteNaoInformado:
        ui->lblStatus->setText("Informe o cliente.");
        break;

    case IPedidoService::ResultadoRegistro::ProdutoNaoInformado:
        ui->lblStatus->setText("Informe o produto.");
        break;

    case IPedidoService::ResultadoRegistro::QuantidadeInvalida:
        ui->lblStatus->setText("Quantidade inválida.");
        break;

    case IPedidoService::ResultadoRegistro::EstoqueInsuficiente:
        ui->lblStatus->setText("Estoque insuficiente.");
        break;
    }

    ui->lblSaldo->setText(QString::number(saldo));
}
void PedidoWindow::on_btnReservar_clicked()
{
    if(ui->tableItens->rowCount() == 0)
    {
        QMessageBox::warning(this,
                             "Aviso",
                             "Nenhum item foi adicionado ao pedido.");

        return;
    }
    IPedidoService::ResultadoRegistro resultado =
        pedidoService->reservarPedidos();
    switch (resultado)
    {
    case IPedidoService::ResultadoRegistro::Sucesso:

        QMessageBox::information(
            this,
            "Reserva",
            "Pedidos reservados com sucesso.");

        atualizarTabela();

        break;

    case IPedidoService::ResultadoRegistro::EstoqueInsuficiente:

        QMessageBox::warning(
            this,
            "Reserva",
            "Não foi possível reservar todos os itens.");

        break;

    default:

        QMessageBox::warning(
            this,
            "Reserva",
            "Ocorreu um erro ao reservar.");

        break;
    }

    if(resultado == IPedidoService::ResultadoRegistro::Sucesso)
    {
        ReservaWindow *janela =
            new ReservaWindow(pedidoService);

        janela->show();

        close();
    }
}
void PedidoWindow::atualizarTabela()
{
    ui->tableItens->setRowCount(0);

    std::vector<Pedido> pedidos = pedidoService->getPedidosPendentes();

    for (const Pedido &pedido : pedidos)
    {
        int linha = ui->tableItens->rowCount();

        ui->tableItens->insertRow(linha);

        ui->tableItens->setItem(
            linha,
            0,
            new QTableWidgetItem(pedido.getProduto()));

        ui->tableItens->setItem(
            linha,
            1,
            new QTableWidgetItem(
                QString::number(pedido.getQuantidade())));

        ui->tableItens->setItem(
            linha,
            2,
            new QTableWidgetItem(pedido.getStatus()));
    }
}
void PedidoWindow::on_btnRemover_clicked()
{
    int linha = ui->tableItens->currentRow();

    if (linha < 0)
    {
        QMessageBox::warning(
            this,
            "Aviso",
            "Selecione um pedido.");

        return;
    }

    if (pedidoService->removerPedido(linha))
    {
        atualizarTabela();
    }
}