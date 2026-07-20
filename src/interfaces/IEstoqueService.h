#ifndef IESTOQUESERVICE_H
#define IESTOQUESERVICE_H
#include <QList>
#include "produto.h"
#include <QString>

/**
 * @brief Interface responsável pelos serviços de estoque.
 */
class IEstoqueService
{
public:

    enum class ResultadoReserva
    {
        Sucesso,
        ProdutoNaoEncontrado,
        QuantidadeInvalida,
        EstoqueInsuficiente
    };

    virtual int verificarSaldo(const QString &produto) = 0;
    virtual QList<Produto> listarProdutos() const = 0;
    virtual ResultadoReserva reservarEstoque(
        const QString &produto,
        int quantidade) = 0;
    virtual bool adicionarEstoque(const QString &produto,
                                  int quantidade) = 0;

    virtual ~IEstoqueService() = default;
    virtual bool cadastrarProduto(const QString &nome,
                                  int quantidade) = 0;
};

#endif