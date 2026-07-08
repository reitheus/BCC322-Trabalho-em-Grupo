#ifndef IPEDIDOSERVICE_H
#define IPEDIDOSERVICE_H

#include <vector>

#include "Pedido.h"

/**
 * @brief Interface responsável pelos serviços de pedidos.
 */
class IPedidoService
{
public:

    /**
     * @brief Resultado da tentativa de registrar um pedido.
     */
    enum class ResultadoRegistro
    {
        Sucesso,
        ClienteNaoInformado,
        ProdutoNaoInformado,
        QuantidadeInvalida,
        EstoqueInsuficiente
    };

    /**
     * @brief Registra um novo pedido.
     *
     * @param pedido Pedido a ser registrado.
     * @param saldoDisponivel Saldo disponível para o produto.
     * @return Resultado da operação.
     */
    virtual ResultadoRegistro registrarPedido(
        const Pedido &pedido,
        int &saldoDisponivel) = 0;

    /**
     * @brief Remove um pedido pendente.
     *
     * @param indice Índice do pedido.
     * @return true caso o pedido tenha sido removido.
     */
    virtual bool removerPedido(int indice) = 0;

    /**
     * @brief Consulta o saldo disponível de um produto.
     *
     * @param produto Nome do produto.
     * @return Quantidade disponível em estoque.
     */
    virtual int consultarSaldo(
        const QString &produto) = 0;

    /**
     * @brief Retorna todos os pedidos pendentes.
     */
    virtual std::vector<Pedido>
    getPedidosPendentes() const = 0;

    /**
     * @brief Retorna todos os pedidos reservados.
     */
    virtual std::vector<Pedido>
    getPedidosReservados() const = 0;

    /**
     * @brief Reserva todos os pedidos pendentes.
     *
     * Os pedidos reservados deixam a lista de pendentes
     * e passam para a lista de pedidos reservados.
     *
     * @return Resultado da operação.
     */
    virtual ResultadoRegistro
    reservarPedidos() = 0;

    virtual ~IPedidoService() = default;
};

#endif // IPEDIDOSERVICE_H