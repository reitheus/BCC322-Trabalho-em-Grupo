#include "EstoqueServiceImpl.h"
#include "PedidoServiceImpl.h"
#include "UsuarioServiceImpl.h"
#include "ClienteServiceImpl.h"

#include "loginwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("EpiStock");
    QCoreApplication::setApplicationName("EpiStock");

    QTranslator translator;

    const QStringList uiLanguages =
        QLocale::system().uiLanguages();

    for (const QString &locale : uiLanguages)
    {
        const QString baseName =
            "EpiStock_" + QLocale(locale).name();

        if (translator.load(
                ":/i18n/" + baseName))
        {
            a.installTranslator(&translator);

            break;
        }
    }


    // ========================================================
    // SERVIÇO DE ESTOQUE
    // ========================================================

    IEstoqueService *estoqueService =
        new EstoqueServiceImpl();


    // ========================================================
    // SERVIÇO DE USUÁRIOS
    // ========================================================

    IUsuarioService *usuarioService =
        new UsuarioServiceImpl();


    // ========================================================
    // SERVIÇO DE CLIENTES
    // ========================================================

    IClienteService *clienteService =
        new ClienteServiceImpl();


    // ========================================================
    // SERVIÇO DE PEDIDOS
    //
    // O serviço de pedidos depende do serviço de estoque.
    // ========================================================

    IPedidoService *pedidoService =
        new PedidoServiceImpl(
            estoqueService);


    // ========================================================
    // JANELA DE LOGIN
    //
    // Os serviços são injetados na LoginWindow e posteriormente
    // repassados para as demais janelas da aplicação.
    // ========================================================

    LoginWindow w(
        pedidoService,
        estoqueService,
        usuarioService,
        clienteService);

    w.show();


    return QApplication::exec();
}