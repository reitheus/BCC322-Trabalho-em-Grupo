#ifndef ICLIENTESERVICE_H
#define ICLIENTESERVICE_H

#include <QString>
#include <vector>

#include "../models/cliente.h"

/**
 * @brief Interface responsável pelos serviços de clientes.
 *
 * Define o contrato para cadastro, consulta e exclusão
 * de clientes no sistema.
 */
class IClienteService
{
public:

    /**
     * @brief Possíveis resultados de uma operação de cadastro.
     */
    enum class ResultadoCadastro
    {
        Sucesso,
        NomeNaoInformado,
        DocumentoNaoInformado,
        ClienteJaExiste
    };

    /**
     * @brief Cadastra um novo cliente.
     *
     * @param cliente Cliente que será cadastrado.
     *
     * @return Resultado da operação.
     */
    virtual ResultadoCadastro cadastrarCliente(
        const Cliente &cliente) = 0;

    /**
     * @brief Retorna todos os clientes cadastrados.
     *
     * @return Vetor contendo os clientes cadastrados.
     */
    virtual std::vector<Cliente>
    getClientes() const = 0;

    /**
     * @brief Exclui um cliente cadastrado.
     *
     * @param cpfCnpj CPF ou CNPJ utilizado para identificar
     * o cliente.
     *
     * @return true se o cliente foi removido;
     * false caso o cliente não tenha sido encontrado.
     */
    virtual bool excluirCliente(
        const QString &cpfCnpj) = 0;

    /**
     * @brief Verifica se um cliente já está cadastrado.
     *
     * @param cpfCnpj CPF ou CNPJ do cliente.
     *
     * @return true se o cliente existir;
     * false caso contrário.
     */
    virtual bool clienteExiste(
        const QString &cpfCnpj) const = 0;

    /**
     * @brief Destrutor virtual da interface.
     */
    virtual ~IClienteService() = default;
};

#endif // ICLIENTESERVICE_H