#include "usuariodialog.h"

#include <QComboBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>

UsuarioDialog::UsuarioDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Dados do funcionário");
    auto *layout = new QVBoxLayout(this);
    auto *formulario = new QFormLayout;
    m_nome = new QLineEdit(this);
    m_login = new QLineEdit(this);
    m_email = new QLineEdit(this);
    m_senha = new QLineEdit(this);
    m_senha->setEchoMode(QLineEdit::Password);
    m_perfil = new QComboBox(this);
    m_perfil->addItems({"Administrador", "Logístico", "Vendas", "Faturamento", "Gestor", "Operador"});
    formulario->addRow("Nome completo:", m_nome);
    formulario->addRow("Login:", m_login);
    formulario->addRow("E-mail:", m_email);
    formulario->addRow("Senha:", m_senha);
    formulario->addRow("Perfil:", m_perfil);
    layout->addLayout(formulario);
    auto *botoes = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel, this);
    connect(botoes, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(botoes, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(botoes);
}

void UsuarioDialog::setUsuario(const Usuario &usuario)
{
    m_nome->setText(usuario.nome());
    m_login->setText(usuario.login());
    m_email->setText(usuario.email());
    m_senha->setText(usuario.senha());
    m_perfil->setCurrentText(usuario.perfil());
}

Usuario UsuarioDialog::usuario() const
{
    return Usuario(m_nome->text().trimmed(), m_login->text().trimmed(),
                   m_senha->text(), m_email->text().trimmed(), m_perfil->currentText());
}
