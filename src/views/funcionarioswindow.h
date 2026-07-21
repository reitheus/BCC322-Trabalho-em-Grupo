#ifndef FUNCIONARIOSWINDOW_H
#define FUNCIONARIOSWINDOW_H

#include "IUsuarioService.h"
#include <QDialog>

class QTableWidget;
class QLineEdit;

class FuncionariosWindow : public QDialog
{
    Q_OBJECT
public:
    explicit FuncionariosWindow(IUsuarioService *usuarioService, QWidget *parent = nullptr);

private slots:
    void cadastrar();
    void editar();
    void remover();
    void atualizarTabela();

private:
    IUsuarioService *m_usuarioService;
    QTableWidget *m_tabela;
    QLineEdit *m_busca;
};

#endif
