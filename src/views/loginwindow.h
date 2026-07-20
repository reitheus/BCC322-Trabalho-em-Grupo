#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include "IPedidoService.h"
#include "IEstoqueService.h"
#include <QWidget>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(IPedidoService *pedidoService,
                         IEstoqueService *estoqueService,
                         QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_btnEntrar_clicked();
private:
    Ui::LoginWindow *ui;
    IPedidoService *pedidoService;
    IEstoqueService *estoqueService;
};

#endif // LOGINWINDOW_H
