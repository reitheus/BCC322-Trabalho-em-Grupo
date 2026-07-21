#ifndef IUSUARIOSERVICE_H
#define IUSUARIOSERVICE_H

#include "usuario.h"
#include <QList>

class IUsuarioService
{
public:
    virtual ~IUsuarioService() = default;
    virtual bool cadastrar(const Usuario &usuario, QString *erro = nullptr) = 0;
    virtual bool atualizar(const QString &loginOriginal, const Usuario &usuario,
                           QString *erro = nullptr) = 0;
    virtual bool remover(const QString &login, QString *erro = nullptr) = 0;
    virtual bool autenticar(const QString &login, const QString &senha,
                            Usuario *usuario = nullptr) const = 0;
    virtual QList<Usuario> listar() const = 0;
};

#endif
