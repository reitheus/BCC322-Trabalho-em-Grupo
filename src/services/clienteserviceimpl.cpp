#include "clienteserviceimpl.h"

IClienteService::ResultadoCadastro
ClienteServiceImpl::cadastrarCliente(
    const Cliente &cliente)
{
    if (cliente.nome().trimmed().isEmpty())
    {
        return ResultadoCadastro::NomeNaoInformado;
    }

    if (cliente.cpfCnpj().trimmed().isEmpty())
    {
        return ResultadoCadastro::DocumentoNaoInformado;
    }

    if (clienteExiste(cliente.cpfCnpj()))
    {
        return ResultadoCadastro::ClienteJaExiste;
    }

    clientes.push_back(cliente);

    return ResultadoCadastro::Sucesso;
}


std::vector<Cliente>
ClienteServiceImpl::getClientes() const
{
    return clientes;
}


bool ClienteServiceImpl::excluirCliente(
    const QString &cpfCnpj)
{
    for (auto it = clientes.begin();
         it != clientes.end();
         ++it)
    {
        if (it->cpfCnpj() == cpfCnpj)
        {
            clientes.erase(it);

            return true;
        }
    }

    return false;
}


bool ClienteServiceImpl::clienteExiste(
    const QString &cpfCnpj) const
{
    for (const Cliente &cliente : clientes)
    {
        if (cliente.cpfCnpj() == cpfCnpj)
        {
            return true;
        }
    }

    return false;
}