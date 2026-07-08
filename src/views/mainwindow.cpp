#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "pedidowindow.h"
#include <QMessageBox>

MainWindow::MainWindow(IPedidoService *pedidoService,
                       QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pedidoService(pedidoService)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_btnPedido_clicked()
{
    PedidoWindow *pedido =
        new PedidoWindow(pedidoService);

    pedido->show();

    this->hide();
}
