
INCLUDEPATH += $$PWD

#DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/DataDecorator.h \
    $$PWD/StringDecorator.h \
    $$PWD/IntDecorator.h \
    $$PWD/DateTimeDecorator.h \
    $$PWD/EnumeratorDecorator.h \
    $$PWD/Entity.h \
    $$PWD/EntityCollection.h

SOURCES += \
    $$PWD/DataDecorator.cpp \
    $$PWD/StringDecorator.cpp \
    $$PWD/IntDecorator.cpp \
    $$PWD/DateTimeDecorator.cpp \
    $$PWD/EnumeratorDecorator.cpp \
    $$PWD/Entity.cpp \
    $$PWD/EntityCollection.cpp

QT += core
