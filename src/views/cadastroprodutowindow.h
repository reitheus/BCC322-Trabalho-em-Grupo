#ifndef CADASTROPRODUTOWINDOW_H
#define CADASTROPRODUTOWINDOW_H
#include <QDialog>
#include "IEstoqueService.h"
#include <QWidget>

namespace Ui {
class CadastroProdutoWindow;
}

class CadastroProdutoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CadastroProdutoWindow(IEstoqueService *estoqueService,
                                   QWidget *parent = nullptr);
    ~CadastroProdutoWindow();

private slots:
    void on_btnCadastrar_clicked();
    void on_btnCancelar_clicked();

private:
    Ui::CadastroProdutoWindow *ui;
    IEstoqueService *estoqueService;
};

#endif // CADASTROPRODUTOWINDOW_H
