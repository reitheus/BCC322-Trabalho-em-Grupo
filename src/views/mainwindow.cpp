#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "estoquewindow.h"
#include <QDebug>
#include "pedidowindow.h"
#include <QMessageBox>

MainWindow::MainWindow(IPedidoService *pedidoService,
                       IEstoqueService *estoqueService,
                       QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pedidoService(pedidoService)
    , estoqueService(estoqueService)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destruída";
    delete ui;
}
void MainWindow::on_btnPedido_clicked()
{
    PedidoWindow *pedido =
        new PedidoWindow(
            pedidoService,
            estoqueService,
            this);

    pedido->show();
    hide();
}
void MainWindow::on_btnGerenciarEstoque_clicked()
{
    EstoqueWindow janela(estoqueService, this);
    janela.exec();
}