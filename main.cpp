
#include "EstoqueServiceImpl.h"
#include "PedidoServiceImpl.h"
#include "loginwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "EpiStock_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    IEstoqueService *estoqueService = new EstoqueServiceImpl();

    IPedidoService *pedidoService =
        new PedidoServiceImpl(estoqueService);
    LoginWindow w(pedidoService,
                  estoqueService);
    w.show();
    return QApplication::exec();
}
