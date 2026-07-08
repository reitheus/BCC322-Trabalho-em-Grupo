#ifndef IESTOQUESERVICE_H
#define IESTOQUESERVICE_H

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

    virtual ResultadoReserva reservarEstoque(
        const QString &produto,
        int quantidade) = 0;

    virtual ~IEstoqueService() = default;
};

#endif