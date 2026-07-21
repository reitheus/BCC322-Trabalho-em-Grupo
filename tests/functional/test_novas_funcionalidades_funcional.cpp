#include <QtTest>
#include <QCheckBox>
#include <QMessageBox>
#include <QSettings>
#include <QTableWidget>
#include <QTemporaryDir>
#include <QTemporaryFile>
#include <QTimer>

#include "importacaoxmlwindow.h"
#include "EstoqueServiceImpl.h"

class TestNovasFuncionalidadesFuncional : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void init();
    void fluxoImportacao_deveExigirConferenciaELancarEstoque();

private:
    QTemporaryDir m_diretorio;
};

void TestNovasFuncionalidadesFuncional::initTestCase()
{
    QVERIFY(m_diretorio.isValid());
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, m_diretorio.path());
    QCoreApplication::setOrganizationName("EpiStockTestes");
    QCoreApplication::setApplicationName("ImportacaoXml");
}

void TestNovasFuncionalidadesFuncional::init()
{
    QSettings configuracao;
    configuracao.clear();
    configuracao.sync();
}

void TestNovasFuncionalidadesFuncional::fluxoImportacao_deveExigirConferenciaELancarEstoque()
{
    QTemporaryFile xml;
    QVERIFY(xml.open());
    const QByteArray conteudo = R"(<NFe><infNFe Id="NFe123"><det nItem="1"><prod><cProd>001</cProd><xProd>Capacete</xProd><qCom>4</qCom></prod></det></infNFe></NFe>)";
    QCOMPARE(xml.write(conteudo), conteudo.size());
    xml.flush();

    EstoqueServiceImpl estoque;
    ImportacaoXmlWindow janela(&estoque);
    QString erro;
    QVERIFY2(janela.carregarXml(xml.fileName(), &erro), qPrintable(erro));
    QCOMPARE(janela.findChild<QTableWidget *>()->rowCount(), 1);
    QCOMPARE(estoque.verificarSaldo("Capacete"), 20);

    QCheckBox *conferencia = janela.findChild<QCheckBox *>();
    QVERIFY(conferencia);
    conferencia->setChecked(true);
    QTimer::singleShot(20, [] {
        for (QWidget *widget : QApplication::topLevelWidgets())
            if (auto *mensagem = qobject_cast<QMessageBox *>(widget)) mensagem->accept();
    });
    QVERIFY(QMetaObject::invokeMethod(&janela, "confirmarConferencia", Qt::DirectConnection));
    QCOMPARE(estoque.verificarSaldo("Capacete"), 24);
}

QTEST_MAIN(TestNovasFuncionalidadesFuncional)
#include "test_novas_funcionalidades_funcional.moc"
