cmake_minimum_required(VERSION 3.16)

project(EpiStock VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
    QT NAMES Qt6 Qt5
    REQUIRED COMPONENTS
    Widgets
    LinguistTools
    Test
)

find_package(
    Qt${QT_VERSION_MAJOR}
    REQUIRED COMPONENTS
    Widgets
    LinguistTools
    Test
)

set(TS_FILES EpiStock_pt_BR.ts)


# ============================================================
# ARQUIVOS PRINCIPAIS DO PROJETO
# ============================================================

set(PROJECT_SOURCES

    main.cpp


    # ========================================================
    # VIEWS
    # ========================================================

    src/views/mainwindow.cpp
    src/views/mainwindow.h
    src/views/mainwindow.ui

    src/views/loginwindow.cpp
    src/views/loginwindow.h
    src/views/loginwindow.ui

    src/views/pedidowindow.cpp
    src/views/pedidowindow.h
    src/views/pedidowindow.ui

    src/views/estoquewindow.cpp
    src/views/estoquewindow.h
    src/views/estoquewindow.ui

    src/views/cadastroprodutowindow.cpp
    src/views/cadastroprodutowindow.h
    src/views/cadastroprodutowindow.ui

    src/views/usuariodialog.cpp
    src/views/usuariodialog.h

    src/views/funcionarioswindow.cpp
    src/views/funcionarioswindow.h

    src/views/importacaoxmlwindow.cpp
    src/views/importacaoxmlwindow.h

    src/views/reservawindow.cpp
    src/views/reservawindow.h
    src/views/reservawindow.ui


    # ========================================================
    # NOVA VIEW DE CLIENTES
    # ========================================================

    src/views/clienteswindow.cpp
    src/views/clienteswindow.h
    src/views/clienteswindow.ui


    # ========================================================
    # MODELS
    # ========================================================

    src/models/produto.cpp
    src/models/produto.h

    src/models/pedido.cpp
    src/models/pedido.h

    src/models/usuario.cpp
    src/models/usuario.h


    # ========================================================
    # NOVO MODEL DE CLIENTE
    # ========================================================

    src/models/cliente.cpp
    src/models/cliente.h


    # ========================================================
    # SERVICES
    # ========================================================

    src/services/estoqueserviceImpl.cpp
    src/services/estoqueserviceImpl.h

    src/services/pedidoserviceImpl.cpp
    src/services/pedidoserviceImpl.h

    src/services/UsuarioServiceImpl.cpp
    src/services/UsuarioServiceImpl.h


    # ========================================================
    # NOVO SERVIÇO DE CLIENTES
    # ========================================================

    src/services/ClienteServiceImpl.cpp
    src/services/ClienteServiceImpl.h


    # ========================================================
    # INTERFACES
    # ========================================================

    src/interfaces/IPedidoService.h
    src/interfaces/IEstoqueService.h
    src/interfaces/IUsuarioService.h


    # ========================================================
    # NOVA INTERFACE DE CLIENTES
    # ========================================================

    src/interfaces/IClienteService.h


    # ========================================================
    # TRADUÇÕES
    # ========================================================

    ${TS_FILES}
)


# ============================================================
# CRIAÇÃO DO EXECUTÁVEL PRINCIPAL
# ============================================================

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)

    qt_add_executable(
        EpiStock

        MANUAL_FINALIZATION

        ${PROJECT_SOURCES}
    )

    qt_create_translation(
        QM_FILES
        ${CMAKE_SOURCE_DIR}
        ${TS_FILES}
    )

else()

    if(ANDROID)

        add_library(
            EpiStock
            SHARED
            ${PROJECT_SOURCES}
        )

    else()

        add_executable(
            EpiStock
            ${PROJECT_SOURCES}
        )

    endif()

    qt5_create_translation(
        QM_FILES
        ${CMAKE_SOURCE_DIR}
        ${TS_FILES}
    )

endif()


# ============================================================
# BIBLIOTECAS QT
# ============================================================

target_link_libraries(
    EpiStock
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)


# ============================================================
# DIRETÓRIOS DE INCLUDE
# ============================================================

target_include_directories(
    EpiStock
    PRIVATE

    src/models
    src/services
    src/interfaces
    src/views
)


# ============================================================
# CONFIGURAÇÕES DO EXECUTÁVEL
# ============================================================

if(${QT_VERSION} VERSION_LESS 6.1.0)

    set(
        BUNDLE_ID_OPTION
        MACOSX_BUNDLE_GUI_IDENTIFIER
        com.example.EpiStock
    )

endif()


set_target_properties(
    EpiStock
    PROPERTIES

    ${BUNDLE_ID_OPTION}

    MACOSX_BUNDLE_BUNDLE_VERSION
    ${PROJECT_VERSION}

    MACOSX_BUNDLE_SHORT_VERSION_STRING
    ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}

    MACOSX_BUNDLE TRUE

    WIN32_EXECUTABLE TRUE
)


# ============================================================
# INSTALAÇÃO
# ============================================================

include(GNUInstallDirs)

install(
    TARGETS EpiStock

    BUNDLE DESTINATION .

    LIBRARY DESTINATION
    ${CMAKE_INSTALL_LIBDIR}

    RUNTIME DESTINATION
    ${CMAKE_INSTALL_BINDIR}
)


if(QT_VERSION_MAJOR EQUAL 6)

    qt_finalize_executable(EpiStock)

endif()


# ============================================================
# TESTES
# ============================================================

enable_testing()


# ============================================================
# TESTES UNITÁRIOS
# ============================================================

add_executable(
    test_novas_funcionalidades_unitario

    tests/unit/test_novas_funcionalidades_unitario.cpp


    # Models
    src/models/usuario.cpp
    src/models/usuario.h

    src/models/produto.cpp
    src/models/produto.h

    src/models/cliente.cpp
    src/models/cliente.h


    # Services
    src/services/UsuarioServiceImpl.cpp
    src/services/UsuarioServiceImpl.h

    src/services/estoqueserviceImpl.cpp
    src/services/estoqueserviceImpl.h

    src/services/ClienteServiceImpl.cpp
    src/services/ClienteServiceImpl.h


    # Interfaces
    src/interfaces/IUsuarioService.h
    src/interfaces/IEstoqueService.h
    src/interfaces/IClienteService.h
)


target_link_libraries(
    test_novas_funcionalidades_unitario

    PRIVATE

    Qt${QT_VERSION_MAJOR}::Test
)


target_include_directories(
    test_novas_funcionalidades_unitario

    PRIVATE

    src/models
    src/services
    src/interfaces
)


add_test(
    NAME novas_funcionalidades_unitario
    COMMAND test_novas_funcionalidades_unitario
)


# ============================================================
# TESTES FUNCIONAIS
# ============================================================

add_executable(
    test_novas_funcionalidades_funcional

    tests/functional/test_novas_funcionalidades_funcional.cpp


    # Views
    src/views/importacaoxmlwindow.cpp
    src/views/importacaoxmlwindow.h


    # Models
    src/models/produto.cpp
    src/models/produto.h


    # Services
    src/services/estoqueserviceImpl.cpp
    src/services/estoqueserviceImpl.h


    # Interfaces
    src/interfaces/IEstoqueService.h
)


target_link_libraries(
    test_novas_funcionalidades_funcional

    PRIVATE

    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Test
)


target_include_directories(
    test_novas_funcionalidades_funcional

    PRIVATE

    src/models
    src/services
    src/interfaces
    src/views
)


add_test(
    NAME novas_funcionalidades_funcional
    COMMAND test_novas_funcionalidades_funcional
)