#ifndef IMPORTACAOXMLWINDOW_H
#define IMPORTACAOXMLWINDOW_H

#include "IEstoqueService.h"
#include <QDialog>
#include <QSet>

class QCheckBox;
class QLabel;
class QTableWidget;

struct ItemNotaCompra
{
    QString codigo;
    QString descricao;
    int quantidade = 0;
};

class ImportacaoXmlWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ImportacaoXmlWindow(IEstoqueService *estoqueService, QWidget *parent = nullptr);
    bool carregarXml(const QString &arquivo, QString *erro = nullptr);

private slots:
    void selecionarXml();
    void confirmarConferencia();

private:
    bool lerNota(const QString &arquivo, QString *erro);
    bool validarItens(QString *erro) const;
    void exibirItens();

    IEstoqueService *m_estoqueService;
    QTableWidget *m_tabela;
    QCheckBox *m_conferencia;
    QLabel *m_status;
    QString m_chaveNota;
    QList<ItemNotaCompra> m_itens;
    QSet<QString> m_notasImportadas;
};

#endif
