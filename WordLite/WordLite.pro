QT       += core gui
QT += sql # 启用SQL模块（数据库）

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    achievementwidget.cpp \
    # back_head/test.cpp \
    gamewidget.cpp \
    learnwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    querywidget.cpp \
    reviewwidget.cpp \
    userwidget.cpp \
    wordwidget.cpp \
    back_src/database.cpp

HEADERS += \
    achievementwidget.h \
    gamewidget.h \
    learnwidget.h \
    mainwindow.h \
    querywidget.h \
    reviewwidget.h \
    userwidget.h \
    wordwidget.h \
    back_head/database.h

FORMS += \
    achievementwidget.ui \
    gamewidget.ui \
    learnwidget.ui \
    mainwindow.ui \
    querywidget.ui \
    reviewwidget.ui \
    userwidget.ui \
    wordwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
