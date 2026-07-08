#ifndef PEDIDOWINDOW_H
#define PEDIDOWINDOW_H
#include "IPedidoService.h"
#include <QWidget>

namespace Ui {
class PedidoWindow;
}

class PedidoWindow : public QWidget
{
    Q_OBJECT

public:
    PedidoWindow(IPedidoService *pedidoService,
                 QWidget *parent = nullptr);
    ~PedidoWindow();
private slots:
    void on_btnVerificar_clicked();
    void on_btnAdicionar_clicked();
    void on_btnReservar_clicked();
    void on_btnRemover_clicked();
private:
    Ui::PedidoWindow *ui;
    IPedidoService *pedidoService;
    void atualizarTabela();

};

#endif // PEDIDOWINDOW_H
