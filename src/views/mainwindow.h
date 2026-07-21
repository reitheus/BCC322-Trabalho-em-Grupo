#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "IPedidoService.h"
#include "IEstoqueService.h"
#include "IUsuarioService.h"
#include "usuario.h"
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
                        IUsuarioService *usuarioService,
                        const Usuario &usuarioAutenticado,
                        QWidget *parent = nullptr);
    ~MainWindow() override;
private slots:
    void on_btnPedido_clicked();
    void on_btnGerenciarEstoque_clicked();
    void on_btnGerenciarFuncionarios_clicked();
    void on_btnImportarXml_clicked();
    void on_btnSairw_clicked();
private:
    Ui::MainWindow *ui;
    IPedidoService *pedidoService;
    IEstoqueService *estoqueService;
    IUsuarioService *usuarioService;
    Usuario usuarioAutenticado;
};
#endif // MAINWINDOW_H
