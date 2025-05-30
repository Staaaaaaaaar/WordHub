QT       += core gui sql network testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    achievementwidget.cpp \
    #back_head/test.cpp \
    back_src/loadword.cpp \
    back_src\utils.cpp \
    gamewidget.cpp \
    guess_according_to_description/guess_word.cpp \
    #guess_word.cpp \
    guess_word_widget.cpp \
    learnwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    querywidget.cpp \
    userwidget.cpp \
    wordle.cpp \
    back_src/database.cpp \
    back_src/learner.cpp \
    API/dictionaryapi.cpp

HEADERS += \
    achievementwidget.h \
    gamewidget.h \
    guess_according_to_description_h/guess_word.h \
    guess_word_widget.h \
    learnwidget.h \
    mainwindow.h \
    querywidget.h \
    userwidget.h \
    wordle.h \
    back_head/database.h \
    back_head/utils.h\
    back_head/loadword.h \
    back_head/learner.h \
    API/dictionaryapi.h \


FORMS += \
    achievementwidget.ui \
    gamewidget.ui \
    guess_word_widget.ui \
    learnwidget.ui \
    mainwindow.ui \
    querywidget.ui \
    wordle.ui \
    userwidget.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
