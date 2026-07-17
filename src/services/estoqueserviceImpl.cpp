
#include "EstoqueServiceImpl.h"
using ResultadoReserva = IEstoqueService::ResultadoReserva;



EstoqueServiceImpl::EstoqueServiceImpl()
{
    inicializarEstoque();
}
void EstoqueServiceImpl::inicializarEstoque()
{
    estoque.append(Produto("Capacete",20));
    estoque.append(Produto("Luva",15));
    estoque.append(Produto("Botina",10));
    estoque.append(Produto("Óculos de Proteção",25));
    estoque.append(Produto("Máscara PFF2",50));
}
Produto *EstoqueServiceImpl::buscarProduto(
    const QString &nome)
{
    for (Produto &produto : estoque)
    {
        if (produto.getNome() == nome)
            return &produto;
    }

    return nullptr;
}
bool EstoqueServiceImpl::quantidadeValida(
    int quantidade) const
{
    return quantidade > 0;
}

int EstoqueServiceImpl::verificarSaldo(const QString &produto)
{
    Produto *p = buscarProduto(produto);

    if (p == nullptr)
        return 0;

    return p->getQuantidade();
}
IEstoqueService::ResultadoReserva
EstoqueServiceImpl::reservarEstoque(
    const QString &produto,
    int quantidade)
{
    if (!quantidadeValida(quantidade))
        return ResultadoReserva::QuantidadeInvalida;

    Produto *p = buscarProduto(produto);

    if (p == nullptr)
        return ResultadoReserva::ProdutoNaoEncontrado;

    if (p->getQuantidade() < quantidade)
        return ResultadoReserva::EstoqueInsuficiente;

    p->setQuantidade(
        p->getQuantidade() - quantidade);

    return ResultadoReserva::Sucesso;
}