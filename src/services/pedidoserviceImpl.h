#ifndef PEDIDOSERVICEIMPL_H
#define PEDIDOSERVICEIMPL_H

#include "IPedidoService.h"
#include "IEstoqueService.h"

#include <vector>

/**
 * @brief Implementação concreta do serviço de gerenciamento de pedidos.
 *
 * Responsável por validar, registrar e consultar pedidos.
 * Todas as regras de negócio relacionadas aos pedidos devem
 * estar concentradas nesta classe.
 */
class PedidoServiceImpl : public IPedidoService
{
public:

    explicit PedidoServiceImpl(
        IEstoqueService *estoqueService);

    IPedidoService::ResultadoRegistro
    registrarPedido(
        const Pedido &pedido,
        int &saldoDisponivel) override;

    int consultarSaldo(
        const QString &produto) override;

    std::vector<Pedido> getPedidosPendentes() const override;

    std::vector<Pedido>
    getPedidosReservados() const override;

    IPedidoService::ResultadoRegistro
    reservarPedidos() override;

    bool removerPedido(
        int indice) override;
private:

    IPedidoService::ResultadoRegistro
    validarPedido(const Pedido &pedido) const;

    void adicionarPedido(const Pedido &pedido);

    int quantidadeComprometida(
        const QString &produto) const;
private:

    std::vector<Pedido> pedidosPendentes;

    std::vector<Pedido> pedidosReservados;

    IEstoqueService *estoqueService;
};

#endif // PEDIDOSERVICEIMPL_H