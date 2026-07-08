#include "loginwindow.h"
#include "ui_loginwindow.h"

#include "mainwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(IPedidoService *pedidoService,
                         QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
    , pedidoService(pedidoService)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
void LoginWindow::on_btnEntrar_clicked()
{
    QString usuario = ui->txtUsuario->text();
    QString senha = ui->txtsenha->text();

    if (usuario == "admin" && senha == "123")
    {
        MainWindow *menu = new MainWindow(pedidoService);
        menu->show();

        this->close();
    }
    else
    {
        QMessageBox::warning(this,
                             "Erro",
                             "Usuário ou senha inválidos!");
    }
}