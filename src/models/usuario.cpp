#include "usuario.h"

Usuario::Usuario(QString nome, QString login, QString senha, QString email,
                 QString perfil)
    : m_nome(nome), m_login(login), m_senha(senha), m_email(email), m_perfil(perfil)
{
}

QString Usuario::nome() const { return m_nome; }
QString Usuario::login() const { return m_login; }
QString Usuario::senha() const { return m_senha; }
QString Usuario::email() const { return m_email; }
QString Usuario::perfil() const { return m_perfil; }
bool Usuario::ativo() const { return m_ativo; }
void Usuario::setNome(const QString &valor) { m_nome = valor; }
void Usuario::setLogin(const QString &valor) { m_login = valor; }
void Usuario::setSenha(const QString &valor) { m_senha = valor; }
void Usuario::setEmail(const QString &valor) { m_email = valor; }
void Usuario::setPerfil(const QString &valor) { m_perfil = valor; }
void Usuario::setAtivo(bool valor) { m_ativo = valor; }
