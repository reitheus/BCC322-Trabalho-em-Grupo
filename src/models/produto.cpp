#include "Produto.h"

Produto::Produto()
{
}

Produto::Produto(QString nome, int quantidade)
{
    this->nome = nome;
    this->quantidade = quantidade;
}

QString Produto::getNome() const
{
    return nome;
}

int Produto::getQuantidade() const
{
    return quantidade;
}

void Produto::setNome(QString nome)
{
    this->nome = nome;
}

void Produto::setQuantidade(int quantidade)
{
    this->quantidade = quantidade;
}