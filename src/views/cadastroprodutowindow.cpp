#include "cadastroprodutowindow.h"
#include "ui_cadastroprodutowindow.h"
#include <QMessageBox>
CadastroProdutoWindow::CadastroProdutoWindow(
    IEstoqueService *estoqueService,
    QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CadastroProdutoWindow)
    , estoqueService(estoqueService)
{
    ui->setupUi(this);
}
CadastroProdutoWindow::~CadastroProdutoWindow()
{
    delete ui;
}
void CadastroProdutoWindow::on_btnCancelar_clicked()
{
    reject();
}
void CadastroProdutoWindow::on_btnCadastrar_clicked()
{
    bool sucesso = estoqueService->cadastrarProduto(
        ui->txtNome->text(),
        ui->sbQuantidade->value());

    if (sucesso)
    {
        QMessageBox::information(
            this,
            "Sucesso",
            "Produto cadastrado com sucesso.");

        accept();
    }
    else
    {
        QMessageBox::warning(
            this,
            "Erro",
            "Não foi possível cadastrar o produto.");
    }
}