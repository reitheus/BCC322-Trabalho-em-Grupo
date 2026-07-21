#ifndef CLIENTE_H
#define CLIENTE_H

#include <QString>

/**
 * @brief Representa um cliente cadastrado no sistema.
 *
 * A classe armazena as informações básicas necessárias
 * para identificação e gerenciamento de um cliente.
 */
class Cliente
{
public:
    Cliente() = default;

    Cliente(QString nome,
            QString cpfCnpj,
            QString email,
            QString telefone);

    QString nome() const;
    QString cpfCnpj() const;
    QString email() const;
    QString telefone() const;

    void setNome(const QString &valor);
    void setCpfCnpj(const QString &valor);
    void setEmail(const QString &valor);
    void setTelefone(const QString &valor);

private:
    QString m_nome;
    QString m_cpfCnpj;
    QString m_email;
    QString m_telefone;
};

#endif // CLIENTE_H