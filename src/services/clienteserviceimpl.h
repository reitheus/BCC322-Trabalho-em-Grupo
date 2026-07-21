#ifndef CLIENTESERVICEIMPL_H
#define CLIENTESERVICEIMPL_H

#include "iclienteservice.h"

#include <vector>

/**
 * @brief Implementação concreta do serviço de clientes.
 *
 * Responsável por cadastrar, listar, localizar e excluir
 * clientes do sistema.
 */
class ClienteServiceImpl : public IClienteService
{
public:
    ClienteServiceImpl() = default;

    ResultadoCadastro cadastrarCliente(
        const Cliente &cliente) override;

    std::vector<Cliente>
    getClientes() const override;

    bool excluirCliente(
        const QString &cpfCnpj) override;

    bool clienteExiste(
        const QString &cpfCnpj) const override;

private:
    std::vector<Cliente> clientes;
};

#endif // CLIENTESERVICEIMPL_H