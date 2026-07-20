#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "IPedidoService.h"
#include "IEstoqueService.h"
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(IPedidoService *pedidoService,
                        IEstoqueService *estoqueService,
                        QWidget *parent = nullptr);
    ~MainWindow() override;
private slots:
    void on_btnPedido_clicked();
    void on_btnGerenciarEstoque_clicked();
private:
    Ui::MainWindow *ui;
    IPedidoService *pedidoService;
    IEstoqueService *estoqueService;
};
#endif // MAINWINDOW_H
