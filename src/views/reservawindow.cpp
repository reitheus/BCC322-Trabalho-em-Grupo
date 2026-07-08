#include "reservawindow.h"
#include "ui_reservawindow.h"
#include "pedidowindow.h"

#include <QTableWidgetItem>

ReservaWindow::ReservaWindow(IPedidoService *pedidoService,
                             QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReservaWindow)
    , pedidoService(pedidoService)
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
    PedidoWindow *janela =
        new PedidoWindow(pedidoService);

    janela->show();

    close();
}