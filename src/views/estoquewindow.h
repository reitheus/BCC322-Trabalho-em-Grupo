#ifndef ESTOQUEWINDOW_H
#define ESTOQUEWINDOW_H

#include <QDialog>
#include "IEstoqueService.h"

namespace Ui {
class EstoqueWindow;
}

class EstoqueWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EstoqueWindow(IEstoqueService *estoqueService,
                           QWidget *parent = nullptr);
    ~EstoqueWindow();

private slots:
    void on_btnAdicionar_clicked();
    void on_btnVoltar_clicked();
    void on_btnCadastrarProduto_clicked();
private:
    Ui::EstoqueWindow *ui;
    IEstoqueService *estoqueService;
    void atualizarTabela();
};

#endif // ESTOQUEWINDOW_H