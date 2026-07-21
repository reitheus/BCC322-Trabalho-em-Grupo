#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "IPedidoService.h"
#include "IEstoqueService.h"
#include "IUsuarioService.h"
#include "IClienteService.h"

#include <QWidget>


namespace Ui {
class LoginWindow;
}


class LoginWindow : public QWidget
{
    Q_OBJECT

public:

    explicit LoginWindow(
        IPedidoService *pedidoService,
        IEstoqueService *estoqueService,
        IUsuarioService *usuarioService,
        IClienteService *clienteService,
        QWidget *parent = nullptr);

    ~LoginWindow();


private slots:

    void on_btnEntrar_clicked();

    void on_btnCadastro_clicked();


private:

    Ui::LoginWindow *ui;

    IPedidoService *pedidoService;

    IEstoqueService *estoqueService;

    IUsuarioService *usuarioService;

    IClienteService *clienteService;
};


#endif // LOGINWINDOW_H