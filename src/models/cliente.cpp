#include "cliente.h"

Cliente::Cliente(QString nome,
                 QString cpfCnpj,
                 QString email,
                 QString telefone)
    : m_nome(nome)
    , m_cpfCnpj(cpfCnpj)
    , m_email(email)
    , m_telefone(telefone)
{
}

QString Cliente::nome() const
{
    return m_nome;
}

QString Cliente::cpfCnpj() const
{
    return m_cpfCnpj;
}

QString Cliente::email() const
{
    return m_email;
}

QString Cliente::telefone() const
{
    return m_telefone;
}

void Cliente::setNome(const QString &valor)
{
    m_nome = valor;
}

void Cliente::setCpfCnpj(const QString &valor)
{
    m_cpfCnpj = valor;
}

void Cliente::setEmail(const QString &valor)
{
    m_email = valor;
}

void Cliente::setTelefone(const QString &valor)
{
    m_telefone = valor;
}