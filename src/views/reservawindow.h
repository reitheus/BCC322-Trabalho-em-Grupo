#ifndef RESERVAWINDOW_H
#define RESERVAWINDOW_H

#include "IPedidoService.h"
#include "IEstoqueService.h"

#include <QWidget>

class PedidoWindow;

namespace Ui {
class ReservaWindow;
}

class ReservaWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ReservaWindow(IPedidoService *pedidoService,
                           IEstoqueService *estoqueService,
                           PedidoWindow *pedidoWindow,
                           QWidget *parent = nullptr);

    ~ReservaWindow();

private slots:
    void on_btnVoltar_clicked();

private:
    void atualizarTabela();

    Ui::ReservaWindow *ui;

    IPedidoService *pedidoService;
    IEstoqueService *estoqueService;
    PedidoWindow *pedidoWindow;
};

#endif