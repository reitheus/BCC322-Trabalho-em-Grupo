#ifndef PRODUTO_H
#define PRODUTO_H

#include <QString>

/**
 * @brief Representa um produto do estoque.
 */
class Produto
{
public:
    Produto();

    Produto(QString nome, int quantidade);

    QString getNome() const;
    int getQuantidade() const;

    void setNome(QString nome);
    void setQuantidade(int quantidade);

private:
    QString nome;
    int quantidade;
};

#endif