#ifndef USUARIO_H
#define USUARIO_H

#include <QString>

class Usuario
{
public:
    Usuario() = default;
    Usuario(QString nome, QString login, QString senha, QString email,
            QString perfil = "Operador");

    QString nome() const;
    QString login() const;
    QString senha() const;
    QString email() const;
    QString perfil() const;
    bool ativo() const;

    void setNome(const QString &valor);
    void setLogin(const QString &valor);
    void setSenha(const QString &valor);
    void setEmail(const QString &valor);
    void setPerfil(const QString &valor);
    void setAtivo(bool valor);

private:
    QString m_nome;
    QString m_login;
    QString m_senha;
    QString m_email;
    QString m_perfil;
    bool m_ativo = true;
};

#endif // USUARIO_H
