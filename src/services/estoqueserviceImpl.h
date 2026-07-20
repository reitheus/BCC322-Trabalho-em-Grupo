#ifndef IESTOQUESERVICEIMPL_H
#define IESTOQUESERVICEIMPL_H

#include <QString>
#include <QVector>

#include "IEstoqueService.h"
#include "Produto.h"

/**
 * @brief Interface responsável pelos serviços de estoque.
 */
class EstoqueServiceImpl : public IEstoqueService
{
public:

    EstoqueServiceImpl();

    int verificarSaldo(const QString &produto) override;
    QList<Produto> listarProdutos() const override;
    ResultadoReserva reservarEstoque(
        const QString &produto,
        int quantidade) override;
    bool adicionarEstoque(const QString &produto,
                          int quantidade) override;
    bool cadastrarProduto(const QString &nome,
                          int quantidade) override;

private:

    void inicializarEstoque();

    Produto *buscarProduto(
        const QString &produto);

    bool quantidadeValida(int quantidade) const;

    QVector<Produto> estoque;
};

#endif