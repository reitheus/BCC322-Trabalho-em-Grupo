cmake_minimum_required(VERSION 3.16)

project(EpiStock VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES EpiStock_pt_BR.ts)

set(PROJECT_SOURCES
    main.cpp

    src/views/mainwindow.cpp
    src/views/mainwindow.h
    src/views/mainwindow.ui

    src/views/loginwindow.cpp
    src/views/loginwindow.h
    src/views/loginwindow.ui

    src/views/pedidowindow.cpp
    src/views/pedidowindow.h
    src/views/pedidowindow.ui



    src/views/reservawindow.ui

    src/models/produto.cpp
    src/models/produto.h

    src/models/pedido.cpp
    src/models/pedido.h

    src/models/usuario.cpp
    src/models/usuario.h

    src/services/estoqueserviceImpl.cpp
    src/services/estoqueserviceImpl.h

    src/services/pedidoserviceImpl.cpp
    src/services/pedidoserviceImpl.h

    src/interfaces/IPedidoService.h
    src/interfaces/IEstoqueService.h

    ${TS_FILES}
)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(EpiStock
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        src/views/reservawindow.h
        src/views/reservawindow.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET EpiStock APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(EpiStock SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(EpiStock
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(EpiStock PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(EpiStock PRIVATE
    src/models
    src/services
    src/interfaces
    src/views
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.EpiStock)
endif()
set_target_properties(EpiStock PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS EpiStock
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(EpiStock)
endif()
