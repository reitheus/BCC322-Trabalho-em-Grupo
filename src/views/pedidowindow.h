#ifndef PEDIDOWINDOW_H
#define PEDIDOWINDOW_H
#include "IPedidoService.h"
#include "IEstoqueService.h"
#include <QWidget>
class MainWindow;
class ReservaWindow;

namespace Ui {
class PedidoWindow;
}

class PedidoWindow : public QWidget
{
    Q_OBJECT

public:
    PedidoWindow(IPedidoService *pedidoService,
                 IEstoqueService *estoqueService,
                 MainWindow *mainWindow,
                 QWidget *parent = nullptr);
    ~PedidoWindow();
    void atualizarTabela();
private slots:
    void on_btnVerificar_clicked();
    void on_btnAdicionar_clicked();
    void on_btnReservar_clicked();
    void on_btnRemover_clicked();
    void on_btnVoltar_clicked();

private:
    Ui::PedidoWindow *ui;
    IPedidoService *pedidoService;
    IEstoqueService *estoqueService;
    MainWindow *mainWindow;


};

#endif // PEDIDOWINDOW_H
