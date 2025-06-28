QT       += core gui charts openglwidgets concurrent sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    UI/achievementwidget.cpp \
    UI/achievementtoast.cpp \
    #back_head/test.cpp \
    back_src/loadword.cpp \
    back_src\utils.cpp \
    UI/gamewidget.cpp \
    guess_according_to_description/guess_word.cpp \
    UI/guess_word_widget.cpp \
    UI/learnwidget.cpp \
    UI/loginwidget.cpp \
    main.cpp \
    UI/mainwindow.cpp \
    #painter.cpp \
    UI/querywidget.cpp \
    UI/registerwidget.cpp \
    UI/userwidget.cpp \
    UI/wordle.cpp \
    back_src/database.cpp \
    back_src/learner.cpp \
    API/dictionaryapi.cpp \
    UI/darktheme_win.cpp

HEADERS += \
    UI/achievementwidget.h \
    UI/achievementtoast.h \
    UI/gamewidget.h \
    UI/guess_word_widget.h \
    UI/learnwidget.h \
    UI/loginwidget.h \
    UI/mainwindow.h \
    UI/querywidget.h \
    UI/registerwidget.h \
    UI/userwidget.h \
    UI/wordle.h \
    back_head/database.h \
    back_head/utils.h\
    back_head/loadword.h \
    back_head/learner.h \
    API/dictionaryapi.h \
    UI/darktheme_win.h \
    guess_according_to_description/guess_word.h


FORMS += \
    UI/achievementwidget.ui \
    UI/gamewidget.ui \
    UI/guess_word_widget.ui \
    UI/learnwidget.ui \
    UI/loginwidget.ui \
    UI/mainwindow.ui \
    UI/querywidget.ui \
    UI/registerwidget.ui \
    UI/wordle.ui \
    UI/userwidget.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    UI/Resource.qrc \
    UI/logos.qrc

# 新增：为Windows平台链接dwmapi库
win32: LIBS += -ldwmapi

RC_FILE = UI/appicon.rc
