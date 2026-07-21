
#include "EstoqueServiceImpl.h"
#include <QSettings>
using ResultadoReserva = IEstoqueService::ResultadoReserva;



EstoqueServiceImpl::EstoqueServiceImpl()
{
    carregarDados();
    if (estoque.isEmpty()) {
        inicializarEstoque();
        salvarDados();
    }
}

void EstoqueServiceImpl::carregarDados()
{
    QSettings configuracao;
    const int total = configuracao.beginReadArray("estoque");
    for (int i = 0; i < total; ++i) {
        configuracao.setArrayIndex(i);
        const QString nome = configuracao.value("nome").toString();
        const int quantidade = configuracao.value("quantidade").toInt();
        if (!nome.trimmed().isEmpty() && quantidade >= 0)
            estoque.append(Produto(nome, quantidade));
    }
    configuracao.endArray();
}

void EstoqueServiceImpl::salvarDados() const
{
    QSettings configuracao;
    configuracao.remove("estoque");
    configuracao.beginWriteArray("estoque");
    for (int i = 0; i < estoque.size(); ++i) {
        configuracao.setArrayIndex(i);
        configuracao.setValue("nome", estoque.at(i).getNome());
        configuracao.setValue("quantidade", estoque.at(i).getQuantidade());
    }
    configuracao.endArray();
    configuracao.sync();
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
    salvarDados();

    return ResultadoReserva::Sucesso;
}
bool EstoqueServiceImpl::adicionarEstoque(
    const QString &produto,
    int quantidade)
{
    if (!quantidadeValida(quantidade))
        return false;

    Produto *p = buscarProduto(produto);

    if (p == nullptr)
        return false;

    p->setQuantidade(
        p->getQuantidade() + quantidade);
    salvarDados();

    return true;
}
QList<Produto> EstoqueServiceImpl::listarProdutos() const
{
    return estoque;
}
bool EstoqueServiceImpl::cadastrarProduto(const QString &nome,
                                          int quantidade)
{
    if (nome.trimmed().isEmpty())
        return false;

    if (!quantidadeValida(quantidade))
        return false;

    if (buscarProduto(nome) != nullptr)
        return false;

    estoque.append(Produto(nome, quantidade));
    salvarDados();

    return true;
}
