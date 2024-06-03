QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add.cpp \
    calculator.cpp \
    divide.cpp \
    expressiontransformer.cpp \
    facade.cpp \
    main.cpp \
    mainwindow.cpp \
    multiply.cpp \
    operatorcreator.cpp \
    substract.cpp \
    token.cpp \
    translator.cpp \
    validationchecker.cpp

HEADERS += \
    MathError.h \
    SyntaxError.h \
    add.h \
    calculator.h \
    divide.h \
    expressiontransformer.h \
    facade.h \
    mainwindow.h \
    multiply.h \
    operator.h \
    operatorcreator.h \
    substract.h \
    token.h \
    translator.h \
    validationchecker.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
