#include "UsuarioServiceImpl.h"

#include <QSettings>

UsuarioServiceImpl::UsuarioServiceImpl()
{
    carregarDados();
    if (m_usuarios.isEmpty()) {
        m_usuarios.append(Usuario("Administrador do Sistema", "admin", "123",
                                  "admin@epistock.local", "Administrador"));
        salvarDados();
    }
}

void UsuarioServiceImpl::carregarDados()
{
    QSettings configuracao;
    const int total = configuracao.beginReadArray("usuarios");
    for (int i = 0; i < total; ++i) {
        configuracao.setArrayIndex(i);
        Usuario usuario(configuracao.value("nome").toString(),
                        configuracao.value("login").toString(),
                        configuracao.value("senha").toString(),
                        configuracao.value("email").toString(),
                        configuracao.value("perfil").toString());
        usuario.setAtivo(configuracao.value("ativo", true).toBool());
        m_usuarios.append(usuario);
    }
    configuracao.endArray();
}

void UsuarioServiceImpl::salvarDados() const
{
    QSettings configuracao;
    configuracao.remove("usuarios");
    configuracao.beginWriteArray("usuarios");
    for (int i = 0; i < m_usuarios.size(); ++i) {
        const Usuario &usuario = m_usuarios.at(i);
        configuracao.setArrayIndex(i);
        configuracao.setValue("nome", usuario.nome());
        configuracao.setValue("login", usuario.login());
        configuracao.setValue("senha", usuario.senha());
        configuracao.setValue("email", usuario.email());
        configuracao.setValue("perfil", usuario.perfil());
        configuracao.setValue("ativo", usuario.ativo());
    }
    configuracao.endArray();
    configuracao.sync();
}

int UsuarioServiceImpl::indicePorLogin(const QString &login) const
{
    for (int i = 0; i < m_usuarios.size(); ++i) {
        if (m_usuarios.at(i).login().compare(login.trimmed(), Qt::CaseInsensitive) == 0)
            return i;
    }
    return -1;
}

bool UsuarioServiceImpl::validar(const Usuario &usuario, QString *erro) const
{
    if (usuario.nome().trimmed().isEmpty() || usuario.login().trimmed().isEmpty()
        || usuario.senha().isEmpty() || usuario.email().trimmed().isEmpty()
        || usuario.perfil().trimmed().isEmpty()) {
        if (erro) *erro = "Preencha todos os campos obrigatórios.";
        return false;
    }
    if (!usuario.email().contains('@')) {
        if (erro) *erro = "Informe um e-mail válido.";
        return false;
    }
    return true;
}

bool UsuarioServiceImpl::cadastrar(const Usuario &usuario, QString *erro)
{
    if (!validar(usuario, erro)) return false;
    if (indicePorLogin(usuario.login()) >= 0) {
        if (erro) *erro = "Já existe um funcionário com este login.";
        return false;
    }
    m_usuarios.append(usuario);
    salvarDados();
    return true;
}

bool UsuarioServiceImpl::atualizar(const QString &loginOriginal, const Usuario &usuario,
                                   QString *erro)
{
    if (!validar(usuario, erro)) return false;
    const int indice = indicePorLogin(loginOriginal);
    if (indice < 0) { if (erro) *erro = "Funcionário não encontrado."; return false; }
    const int outro = indicePorLogin(usuario.login());
    if (outro >= 0 && outro != indice) {
        if (erro) *erro = "Já existe um funcionário com este login.";
        return false;
    }
    m_usuarios[indice] = usuario;
    salvarDados();
    return true;
}

bool UsuarioServiceImpl::remover(const QString &login, QString *erro)
{
    const int indice = indicePorLogin(login);
    if (indice < 0) { if (erro) *erro = "Funcionário não encontrado."; return false; }
    if (m_usuarios.at(indice).perfil() == "Administrador") {
        if (erro) *erro = "O administrador padrão não pode ser removido.";
        return false;
    }
    m_usuarios.removeAt(indice);
    salvarDados();
    return true;
}

bool UsuarioServiceImpl::autenticar(const QString &login, const QString &senha,
                                    Usuario *usuario) const
{
    const int indice = indicePorLogin(login);
    if (indice < 0) return false;
    const Usuario encontrado = m_usuarios.at(indice);
    if (!encontrado.ativo() || encontrado.senha() != senha) return false;
    if (usuario) *usuario = encontrado;
    return true;
}

QList<Usuario> UsuarioServiceImpl::listar() const { return m_usuarios; }
