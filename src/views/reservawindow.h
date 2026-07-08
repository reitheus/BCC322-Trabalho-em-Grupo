#ifndef RESERVAWINDOW_H
#define RESERVAWINDOW_H
#include "IPedidoService.h"

#include <QWidget>
namespace Ui
{
class ReservaWindow;
}

class ReservaWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ReservaWindow(IPedidoService *pedidoService,
                           QWidget *parent = nullptr);

    ~ReservaWindow();

private slots:
    void on_btnVoltar_clicked();

private:
    void atualizarTabela();

    Ui::ReservaWindow *ui;

    IPedidoService *pedidoService;
};

#endif // RESERVAWINDOW_H
