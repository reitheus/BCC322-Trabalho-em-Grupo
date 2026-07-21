#ifndef USUARIOSERVICEIMPL_H
#define USUARIOSERVICEIMPL_H

#include "IUsuarioService.h"

class UsuarioServiceImpl final : public IUsuarioService
{
public:
    UsuarioServiceImpl();
    bool cadastrar(const Usuario &usuario, QString *erro = nullptr) override;
    bool atualizar(const QString &loginOriginal, const Usuario &usuario,
                   QString *erro = nullptr) override;
    bool remover(const QString &login, QString *erro = nullptr) override;
    bool autenticar(const QString &login, const QString &senha,
                    Usuario *usuario = nullptr) const override;
    QList<Usuario> listar() const override;

private:
    int indicePorLogin(const QString &login) const;
    bool validar(const Usuario &usuario, QString *erro) const;
    void carregarDados();
    void salvarDados() const;
    QList<Usuario> m_usuarios;
};

#endif
