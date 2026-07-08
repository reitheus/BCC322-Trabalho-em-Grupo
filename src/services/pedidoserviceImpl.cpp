#include "PedidoServiceImpl.h"

namespace
{
constexpr int QUANTIDADE_MINIMA = 1;
}

PedidoServiceImpl::PedidoServiceImpl(IEstoqueService *estoqueService)
{
    this->estoqueService = estoqueService;
}

IPedidoService::ResultadoRegistro
PedidoServiceImpl::registrarPedido(const Pedido &pedido,
                                   int &saldoDisponivel)
{
    IPedidoService::ResultadoRegistro resultado =
        validarPedido(pedido);

    if (resultado != IPedidoService::ResultadoRegistro::Sucesso)
        return resultado;

    saldoDisponivel =
        estoqueService->verificarSaldo(
            pedido.getProduto());

    int comprometido =
        quantidadeComprometida(
            pedido.getProduto());

    saldoDisponivel -= comprometido;

    if (pedido.getQuantidade() > saldoDisponivel)
    {
        return ResultadoRegistro::EstoqueInsuficiente;
    }

    adicionarPedido(pedido);

    return IPedidoService::ResultadoRegistro::Sucesso;
}

int PedidoServiceImpl::consultarSaldo(const QString &produto)
{
    int saldo =
        estoqueService->verificarSaldo(produto);

    saldo -= quantidadeComprometida(produto);

    return saldo;
}

void PedidoServiceImpl::adicionarPedido(const Pedido &pedido)
{
    pedidosPendentes.push_back(pedido);
}

std::vector<Pedido>
PedidoServiceImpl::getPedidosPendentes() const
{
    return pedidosPendentes;;
}

IPedidoService::ResultadoRegistro
PedidoServiceImpl::validarPedido(const Pedido &pedido) const
{
    if (pedido.getCliente().trimmed().isEmpty())
        return ResultadoRegistro::ClienteNaoInformado;

    if (pedido.getProduto().trimmed().isEmpty())
        return ResultadoRegistro::ProdutoNaoInformado;

    if (pedido.getQuantidade() < QUANTIDADE_MINIMA)
        return ResultadoRegistro::QuantidadeInvalida;

    return ResultadoRegistro::Sucesso;
}
IPedidoService::ResultadoRegistro
PedidoServiceImpl::reservarPedidos()
{
    bool houveFalha = false;

    std::vector<Pedido> pedidosNaoReservados;

    for (Pedido &pedido : pedidosPendentes)
    {
        auto resultado =
            estoqueService->reservarEstoque(
                pedido.getProduto(),
                pedido.getQuantidade());

        if (resultado ==
            IEstoqueService::ResultadoReserva::Sucesso)
        {
            pedido.setStatus("Reservado");

            pedidosReservados.push_back(pedido);
        }
        else
        {
            houveFalha = true;

            pedidosNaoReservados.push_back(pedido);
        }
    }

    // Atualiza a lista de pendentes
    pedidosPendentes = pedidosNaoReservados;

    if (houveFalha)
    {
        return IPedidoService::ResultadoRegistro::EstoqueInsuficiente;
    }

    return IPedidoService::ResultadoRegistro::Sucesso;
}
bool PedidoServiceImpl::removerPedido(int indice)
{
    if (indice < 0 || indice >= pedidosPendentes.size())
        return false;

    pedidosPendentes.erase(pedidosPendentes.begin() + indice);

    return true;
}
int PedidoServiceImpl::quantidadeComprometida(
    const QString &produto) const
{
    int total = 0;

    for (const Pedido &pedido : pedidosPendentes)
    {
        if (pedido.getProduto() == produto &&
            pedido.getStatus() == "Pendente")
        {
            total += pedido.getQuantidade();
        }
    }

    return total;
}
std::vector<Pedido>
PedidoServiceImpl::getPedidosReservados() const
{
    return pedidosReservados;
}