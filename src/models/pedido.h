#ifndef PEDIDO_H
#define PEDIDO_H

#include <QString>

/**
 * @brief Representa um pedido de venda.
 */
class Pedido
{
public:
    Pedido();

    Pedido(QString cliente,
           QString produto,
           int quantidade);
    QString getCliente() const;
    QString getProduto() const;
    int getQuantidade() const;
    QString getStatus() const;

    void setCliente(QString cliente);
    void setProduto(QString produto);
    void setQuantidade(int quantidade);
    void setStatus(QString status);

private:
    QString cliente;
    QString produto;
    int quantidade;
    QString status;
};

#endif