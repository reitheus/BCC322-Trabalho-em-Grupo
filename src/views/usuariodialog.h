#ifndef USUARIODIALOG_H
#define USUARIODIALOG_H

#include "usuario.h"
#include <QDialog>

class QComboBox;
class QLineEdit;

class UsuarioDialog : public QDialog
{
    Q_OBJECT
public:
    explicit UsuarioDialog(QWidget *parent = nullptr);
    void setUsuario(const Usuario &usuario);
    Usuario usuario() const;

private:
    QLineEdit *m_nome;
    QLineEdit *m_login;
    QLineEdit *m_email;
    QLineEdit *m_senha;
    QComboBox *m_perfil;
};

#endif
