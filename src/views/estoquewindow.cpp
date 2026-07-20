#include "estoquewindow.h"
#include "ui_estoquewindow.h"
#include "cadastroprodutowindow.h"
#include <QMessageBox>
#include <QHeaderView>

EstoqueWindow::EstoqueWindow(
    IEstoqueService *estoqueService,
    QWidget *parent)
    : QDialog(parent),
    ui(new Ui::EstoqueWindow),
    estoqueService(estoqueService)
{
    ui->setupUi(this);
    QList<Produto> produtos = estoqueService->listarProdutos();

    for (const Produto &produto : produtos)
    {
        ui->cbProduto->addItem(produto.getNome());
    }
    ui->tableEstoque->setEditTriggers(
        QAbstractItemView::NoEditTriggers);

    ui->tableEstoque->setSelectionMode(
        QAbstractItemView::NoSelection);
    // A coluna "Produto" ocupa todo o espaço disponível
    ui->tableEstoque->horizontalHeader()->setSectionResizeMode(
        0, QHeaderView::Stretch);

    // A coluna "Quantidade" terá largura fixa
    ui->tableEstoque->horizontalHeader()->setSectionResizeMode(
        2, QHeaderView::Fixed);

    // Define a largura da coluna Quantidade
    ui->tableEstoque->setColumnWidth(1, 80);
    atualizarTabela();
}

EstoqueWindow::~EstoqueWindow()
{
    delete ui;
}

void EstoqueWindow::on_btnAdicionar_clicked()
{
    bool sucesso = estoqueService->adicionarEstoque(
        ui->cbProduto->currentText(),
        ui->sbQuantidade->value());

    if (sucesso)
    {
        QMessageBox::information(this,
                                 "Sucesso",
                                 "Estoque atualizado.");
        atualizarTabela();
        ui->cbProduto->setCurrentIndex(0);
        ui->sbQuantidade->setValue(1);
    }
    else
    {
        QMessageBox::warning(this,
                             "Erro",
                             "Não foi possível atualizar o estoque.");
    }

}
void EstoqueWindow::on_btnVoltar_clicked()
{
    close();
}
void EstoqueWindow::atualizarTabela()
{
    QList<Produto> produtos = estoqueService->listarProdutos();

    ui->tableEstoque->setRowCount(produtos.size());

    for (int i = 0; i < produtos.size(); i++)
    {
        ui->tableEstoque->setItem(
            i,
            0,
            new QTableWidgetItem(produtos[i].getNome()));

        QTableWidgetItem *quantidade =
            new QTableWidgetItem(
                QString::number(produtos[i].getQuantidade()));

        quantidade->setTextAlignment(Qt::AlignCenter);

        ui->tableEstoque->setItem(i, 1, quantidade);
    }
}
void EstoqueWindow::on_btnCadastrarProduto_clicked()
{
    CadastroProdutoWindow janela(estoqueService, this);

    if (janela.exec() == QDialog::Accepted)
    {
        atualizarTabela();

        ui->cbProduto->clear();

        QList<Produto> produtos = estoqueService->listarProdutos();

        for (const Produto &produto : produtos)
        {
            ui->cbProduto->addItem(produto.getNome());
        }
    }
}