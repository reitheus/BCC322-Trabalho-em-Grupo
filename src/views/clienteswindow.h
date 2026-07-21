#ifndef CLIENTESWINDOW_H
#define CLIENTESWINDOW_H

#include <QWidget>

#include "iclienteservice.h"

namespace Ui {
class ClientesWindow;
}

class ClientesWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientesWindow(IClienteService *clienteService, QWidget *parent = nullptr);

    ~ClientesWindow();

private slots:
    void on_btnCadastrar_clicked();
    void on_btnExcluir_clicked();
    void on_btnVoltar_clicked();

private:
    void atualizarTabela();
    void limparCampos();

    Ui::ClientesWindow *ui;
    IClienteService *clienteService;
};

#endif // CLIENTESWINDOW_H