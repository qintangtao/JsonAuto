
INCLUDEPATH += $$PWD

#DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/DataDecorator.h \
    $$PWD/StringDecorator.h \
    $$PWD/IntDecorator.h \
    $$PWD/DoubleDecorator.h \
    $$PWD/BoolDecorator.h  \
    $$PWD/DateTimeDecorator.h \
    $$PWD/EnumeratorDecorator.h \
    $$PWD/Entity.h \
    $$PWD/EntityCollection.h \
    $$PWD/CollectionObject.h \
    $$PWD/DataDecoratorCollection.h \
    $$PWD/JsonAuto.h

SOURCES += \
    $$PWD/DataDecorator.cpp \
    $$PWD/StringDecorator.cpp \
    $$PWD/IntDecorator.cpp \
    $$PWD/DoubleDecorator.cpp \
    $$PWD/BoolDecorator.cpp \
    $$PWD/DateTimeDecorator.cpp \
    $$PWD/EnumeratorDecorator.cpp \
    $$PWD/Entity.cpp

QT += core
