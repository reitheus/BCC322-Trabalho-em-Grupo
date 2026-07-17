#include "Pedido.h"

Pedido::Pedido()
{
}

Pedido::Pedido(QString cliente,
               QString produto,
               int quantidade)
{
    this->cliente = cliente;
    this->produto = produto;
    this->quantidade = quantidade;

    this->status = "Pendente";
}
QString Pedido::getCliente() const
{
    return cliente;
}

QString Pedido::getProduto() const
{
    return produto;
}

int Pedido::getQuantidade() const
{
    return quantidade;
}

QString Pedido::getStatus() const
{
    return status;
}

void Pedido::setCliente(QString cliente)
{
    this->cliente = cliente;
}

void Pedido::setProduto(QString produto)
{
    this->produto = produto;
}

void Pedido::setQuantidade(int quantidade)
{
    this->quantidade = quantidade;
}

void Pedido::setStatus(QString status)
{
    this->status = status;
}