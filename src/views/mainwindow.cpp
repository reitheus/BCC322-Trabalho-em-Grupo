#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "estoquewindow.h"
#include "pedidowindow.h"
#include "funcionarioswindow.h"
#include "importacaoxmlwindow.h"
#include "clienteswindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QApplication>


MainWindow::MainWindow(
    IPedidoService *pedidoService,
    IEstoqueService *estoqueService,
    IUsuarioService *usuarioService,
    IClienteService *clienteService,
    const Usuario &usuarioAutenticado,
    QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pedidoService(pedidoService)
    , estoqueService(estoqueService)
    , usuarioService(usuarioService)
    , clienteService(clienteService)
    , usuarioAutenticado(usuarioAutenticado)
{
    ui->setupUi(this);

    ui->lblBemVindo->setText(
        "Olá, " + usuarioAutenticado.nome() + "!");

    const bool administrador =
        usuarioAutenticado.perfil() == "Administrador";

    ui->btnGerenciarFuncionarios->setVisible(
        administrador);

    ui->btnImportarXml->setVisible(
        administrador ||
        usuarioAutenticado.perfil() == "Logístico");

    // Caso você queira restringir a tela de clientes
    // apenas para administradores, use:
    //
    // ui->btnClientes->setVisible(administrador);
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
    EstoqueWindow janela(
        estoqueService,
        this);

    janela.exec();
}


void MainWindow::on_btnGerenciarFuncionarios_clicked()
{
    FuncionariosWindow janela(
        usuarioService,
        this);

    janela.exec();
}


void MainWindow::on_btnImportarXml_clicked()
{
    ImportacaoXmlWindow janela(
        estoqueService,
        this);

    janela.exec();
}


// void MainWindow::on_btnClientes_clicked()
// {
//     ClientesWindow *janelaClientes =
//         new ClientesWindow(
//             clienteService);

//     janelaClientes->show();

//     this->hide();
// }










void MainWindow::on_btnSairw_clicked()
{
    QApplication::quit();
}









// void MainWindow::on_btnClientes_clicked()
// {
//     ClientesWindow *janelaClientes =
//         new ClientesWindow(
//             clienteService,
//             this);

//     janelaClientes->setWindowFlag(
//         Qt::Window,
//         true);

//     janelaClientes->show();

//     this->hide();
// }


void MainWindow::on_btnClientes_clicked()
{
    ClientesWindow *janelaClientes =
        new ClientesWindow(
            clienteService,
            this);

    janelaClientes->setWindowFlag(
        Qt::Window,
        true);

    janelaClientes->show();

    this->hide();
}
