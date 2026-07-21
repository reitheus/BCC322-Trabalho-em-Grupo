#include "funcionarioswindow.h"
#include "usuariodialog.h"

#include <QHeaderView>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <algorithm>

FuncionariosWindow::FuncionariosWindow(IUsuarioService *usuarioService, QWidget *parent)
    : QDialog(parent), m_usuarioService(usuarioService)
{
    setWindowTitle("Gerenciamento de funcionários");
    resize(720, 380);
    auto *layout = new QVBoxLayout(this);
    m_busca = new QLineEdit(this);
    m_busca->setPlaceholderText("Buscar por nome, login, e-mail ou perfil...");
    layout->addWidget(m_busca);
    m_tabela = new QTableWidget(this);
    m_tabela->setColumnCount(4);
    m_tabela->setHorizontalHeaderLabels({"Nome", "Login", "E-mail", "Perfil"});
    m_tabela->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tabela->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tabela->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tabela->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(m_tabela);
    auto *botoes = new QHBoxLayout;
    auto *novo = new QPushButton("Cadastrar", this);
    auto *alterar = new QPushButton("Editar", this);
    auto *excluir = new QPushButton("Remover", this);
    auto *fechar = new QPushButton("Fechar", this);
    botoes->addWidget(novo); botoes->addWidget(alterar); botoes->addWidget(excluir);
    botoes->addStretch(); botoes->addWidget(fechar);
    layout->addLayout(botoes);
    connect(novo, &QPushButton::clicked, this, &FuncionariosWindow::cadastrar);
    connect(alterar, &QPushButton::clicked, this, &FuncionariosWindow::editar);
    connect(excluir, &QPushButton::clicked, this, &FuncionariosWindow::remover);
    connect(fechar, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_busca, &QLineEdit::textChanged, this, &FuncionariosWindow::atualizarTabela);
    atualizarTabela();
}

void FuncionariosWindow::atualizarTabela()
{
    const QList<Usuario> usuarios = m_usuarioService->listar();
    m_tabela->setRowCount(0);
    const QString filtro = m_busca->text().trimmed();
    int linha = 0;
    for (const Usuario &u : usuarios) {
        const QString dados = u.nome() + ' ' + u.login() + ' ' + u.email() + ' ' + u.perfil();
        if (!filtro.isEmpty() && !dados.contains(filtro, Qt::CaseInsensitive))
            continue;
        m_tabela->insertRow(linha);
        m_tabela->setItem(linha, 0, new QTableWidgetItem(u.nome()));
        m_tabela->setItem(linha, 1, new QTableWidgetItem(u.login()));
        m_tabela->setItem(linha, 2, new QTableWidgetItem(u.email()));
        m_tabela->setItem(linha, 3, new QTableWidgetItem(u.perfil()));
        ++linha;
    }
}

void FuncionariosWindow::cadastrar()
{
    UsuarioDialog dialog(this);
    if (dialog.exec() != QDialog::Accepted) return;
    QString erro;
    if (!m_usuarioService->cadastrar(dialog.usuario(), &erro)) {
        QMessageBox::warning(this, "Cadastro não realizado", erro); return;
    }
    atualizarTabela();
}

void FuncionariosWindow::editar()
{
    const int linha = m_tabela->currentRow();
    if (linha < 0) { QMessageBox::information(this, "Seleção", "Selecione um funcionário."); return; }
    const QString login = m_tabela->item(linha, 1)->text();
    const auto usuarios = m_usuarioService->listar();
    const auto it = std::find_if(usuarios.cbegin(), usuarios.cend(), [&login](const Usuario &u) { return u.login() == login; });
    if (it == usuarios.cend()) return;
    UsuarioDialog dialog(this); dialog.setUsuario(*it);
    if (dialog.exec() != QDialog::Accepted) return;
    QString erro;
    if (!m_usuarioService->atualizar(login, dialog.usuario(), &erro)) {
        QMessageBox::warning(this, "Alteração não realizada", erro); return;
    }
    atualizarTabela();
}

void FuncionariosWindow::remover()
{
    const int linha = m_tabela->currentRow();
    if (linha < 0) { QMessageBox::information(this, "Seleção", "Selecione um funcionário."); return; }
    const QString login = m_tabela->item(linha, 1)->text();
    if (QMessageBox::question(this, "Confirmar remoção", "Remover o funcionário selecionado?") != QMessageBox::Yes) return;
    QString erro;
    if (!m_usuarioService->remover(login, &erro)) QMessageBox::warning(this, "Remoção não realizada", erro);
    atualizarTabela();
}
