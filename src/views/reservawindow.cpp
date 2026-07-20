#include "reservawindow.h"
#include "ui_reservawindow.h"
#include "pedidowindow.h"

#include <QTableWidgetItem>

ReservaWindow::ReservaWindow(IPedidoService *pedidoService,
                             IEstoqueService *estoqueService,
                             PedidoWindow *pedidoWindow,
                             QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReservaWindow)
    , pedidoService(pedidoService)
    , estoqueService(estoqueService)
    , pedidoWindow(pedidoWindow)
{
    ui->setupUi(this);

    atualizarTabela();
}

ReservaWindow::~ReservaWindow()
{
    delete ui;
}

void ReservaWindow::atualizarTabela()
{
    ui->tableReservas->setRowCount(0);

    std::vector<Pedido> pedidos =
        pedidoService->getPedidosReservados();

    for (const Pedido &pedido : pedidos)
    {
        int linha = ui->tableReservas->rowCount();

        ui->tableReservas->insertRow(linha);

        ui->tableReservas->setItem(
            linha,
            0,
            new QTableWidgetItem(
                pedido.getCliente()));

        ui->tableReservas->setItem(
            linha,
            1,
            new QTableWidgetItem(
                pedido.getProduto()));

        ui->tableReservas->setItem(
            linha,
            2,
            new QTableWidgetItem(
                QString::number(
                    pedido.getQuantidade())));

        ui->tableReservas->setItem(
            linha,
            3,
            new QTableWidgetItem(
                pedido.getStatus()));
    }
}

void ReservaWindow::on_btnVoltar_clicked()
{
    if (pedidoWindow)
    {
        pedidoWindow->show();
    }

    deleteLater();
}