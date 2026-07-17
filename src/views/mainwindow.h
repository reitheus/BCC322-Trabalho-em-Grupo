#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "IPedidoService.h"
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
                        QWidget *parent = nullptr);
    ~MainWindow() override;
private slots:
    void on_btnPedido_clicked();
private:
    Ui::MainWindow *ui;
    IPedidoService *pedidoService;
};
#endif // MAINWINDOW_H
