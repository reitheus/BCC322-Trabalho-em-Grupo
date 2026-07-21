#include "loginwindow.h"
#include "ui_loginwindow.h"


#include "mainwindow.h"
#include "usuariodialog.h"
#include <QMessageBox>

LoginWindow::LoginWindow(IPedidoService *pedidoService,
                         IEstoqueService *estoqueService,
                         IUsuarioService *usuarioService,
                         QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
    , pedidoService(pedidoService)
    , estoqueService(estoqueService)
    , usuarioService(usuarioService)
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

    Usuario usuarioAutenticado;
    if (usuarioService->autenticar(usuario, senha, &usuarioAutenticado))
    {
        MainWindow *menu = new MainWindow(
            pedidoService,
            estoqueService,
            usuarioService,
            usuarioAutenticado);
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

void LoginWindow::on_btnCadastro_clicked()
{
    UsuarioDialog dialog(this);
    if (dialog.exec() != QDialog::Accepted)
        return;
    QString erro;
    if (!usuarioService->cadastrar(dialog.usuario(), &erro)) {
        QMessageBox::warning(this, "Cadastro não realizado", erro);
        return;
    }
    QMessageBox::information(this, "Cadastro concluído", "Usuário cadastrado com sucesso.");
}
