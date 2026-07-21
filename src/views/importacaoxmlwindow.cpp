#include "importacaoxmlwindow.h"

#include <QCheckBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QXmlStreamReader>
#include <QtMath>

ImportacaoXmlWindow::ImportacaoXmlWindow(IEstoqueService *estoqueService, QWidget *parent)
    : QDialog(parent), m_estoqueService(estoqueService)
{
    setWindowTitle("Importar NF-e de compra (XML)");
    resize(700, 420);
    auto *layout = new QVBoxLayout(this);
    auto *selecionar = new QPushButton("Selecionar XML da NF-e", this);
    m_status = new QLabel("Nenhuma nota selecionada.", this);
    m_tabela = new QTableWidget(this);
    m_tabela->setColumnCount(3);
    m_tabela->setHorizontalHeaderLabels({"Código", "Produto", "Quantidade"});
    m_tabela->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tabela->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_conferencia = new QCheckBox("Confirmo que a entrega física foi conferida sem divergências.", this);
    auto *confirmar = new QPushButton("Lançar itens no estoque", this);
    layout->addWidget(selecionar); layout->addWidget(m_status); layout->addWidget(m_tabela);
    layout->addWidget(m_conferencia); layout->addWidget(confirmar);
    connect(selecionar, &QPushButton::clicked, this, &ImportacaoXmlWindow::selecionarXml);
    connect(confirmar, &QPushButton::clicked, this, &ImportacaoXmlWindow::confirmarConferencia);
}

void ImportacaoXmlWindow::selecionarXml()
{
    const QString arquivo = QFileDialog::getOpenFileName(this, "Selecionar NF-e", QString(), "XML (*.xml);;Todos os arquivos (*)");
    if (arquivo.isEmpty()) return;
    QString erro;
    if (!carregarXml(arquivo, &erro))
        QMessageBox::warning(this, "XML inválido", erro);
}

bool ImportacaoXmlWindow::carregarXml(const QString &arquivo, QString *erro)
{
    QString erroLocal;
    if (!lerNota(arquivo, &erroLocal)) {
        m_itens.clear(); exibirItens(); m_status->setText("Falha na importação: " + erroLocal);
        if (erro) *erro = erroLocal;
        return false;
    }
    m_conferencia->setChecked(false);
    m_status->setText(QString("NF-e carregada: %1 item(ns). Aguarde a conferência física.").arg(m_itens.size()));
    exibirItens();
    return true;
}

bool ImportacaoXmlWindow::lerNota(const QString &arquivo, QString *erro)
{
    QFile xmlFile(arquivo);
    if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) { *erro = "Não foi possível abrir o arquivo."; return false; }
    QXmlStreamReader xml(&xmlFile);
    QList<ItemNotaCompra> itens;
    QString chave;
    ItemNotaCompra item;
    bool emProduto = false;
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
            const QString tag = xml.name().toString();
            if (tag == "infNFe") chave = xml.attributes().value("Id").toString();
            if (tag == "prod") { item = ItemNotaCompra(); emProduto = true; }
            else if (emProduto && tag == "cProd") item.codigo = xml.readElementText().trimmed();
            else if (emProduto && tag == "xProd") item.descricao = xml.readElementText().trimmed();
            else if (emProduto && tag == "qCom") {
                bool ok = false;
                const double qtd = xml.readElementText().replace(',', '.').toDouble(&ok);
                if (!ok || qtd <= 0 || qtd != qRound(qtd)) { *erro = "A quantidade da NF-e deve ser um inteiro positivo."; return false; }
                item.quantidade = qRound(qtd);
            }
        } else if (xml.isEndElement() && xml.name() == QStringLiteral("prod")) {
            emProduto = false;
            if (item.descricao.isEmpty() || item.quantidade <= 0) { *erro = "Há um produto sem descrição ou quantidade válida."; return false; }
            itens.append(item);
        }
    }
    if (xml.hasError()) { *erro = "XML malformado: " + xml.errorString(); return false; }
    if (itens.isEmpty()) { *erro = "O XML não contém produtos de NF-e."; return false; }
    m_chaveNota = chave.isEmpty() ? QFileInfo(arquivo).absoluteFilePath() : chave;
    if (m_notasImportadas.contains(m_chaveNota)) { *erro = "Esta NF-e já foi lançada no estoque."; return false; }
    m_itens = itens;
    return true;
}

bool ImportacaoXmlWindow::validarItens(QString *erro) const
{
    for (const ItemNotaCompra &item : m_itens) {
        if (m_estoqueService->verificarSaldo(item.descricao) < 0) {
            *erro = "Produto não localizado no cadastro: " + item.descricao; return false;
        }
        bool encontrado = false;
        for (const Produto &produto : m_estoqueService->listarProdutos())
            if (produto.getNome().compare(item.descricao, Qt::CaseInsensitive) == 0) { encontrado = true; break; }
        if (!encontrado) { *erro = "Produto não localizado no cadastro: " + item.descricao; return false; }
    }
    return true;
}

void ImportacaoXmlWindow::exibirItens()
{
    m_tabela->setRowCount(m_itens.size());
    for (int i = 0; i < m_itens.size(); ++i) {
        const ItemNotaCompra &item = m_itens.at(i);
        m_tabela->setItem(i, 0, new QTableWidgetItem(item.codigo));
        m_tabela->setItem(i, 1, new QTableWidgetItem(item.descricao));
        m_tabela->setItem(i, 2, new QTableWidgetItem(QString::number(item.quantidade)));
    }
}

void ImportacaoXmlWindow::confirmarConferencia()
{
    if (m_itens.isEmpty()) { QMessageBox::information(this, "Importação", "Selecione uma NF-e antes de confirmar."); return; }
    if (!m_conferencia->isChecked()) { QMessageBox::warning(this, "Conferência pendente", "Confirme a conferência física sem divergências para lançar o estoque."); return; }
    QString erro;
    if (!validarItens(&erro)) { QMessageBox::warning(this, "Nota não lançada", erro); return; }
    for (const ItemNotaCompra &item : m_itens) {
        if (!m_estoqueService->adicionarEstoque(item.descricao, item.quantidade)) {
            QMessageBox::critical(this, "Erro", "Não foi possível lançar todos os itens da nota."); return;
        }
    }
    m_notasImportadas.insert(m_chaveNota);
    m_status->setText("Entrada lançada no estoque com sucesso.");
    QMessageBox::information(this, "Entrada concluída", "Produtos adicionados ao estoque após a conferência física.");
    m_itens.clear(); exibirItens(); m_conferencia->setChecked(false);
}
