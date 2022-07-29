

INCLUDEPATH += $$PWD/include

#DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/include/DataDecorator.h \
    $$PWD/include/StringDecorator.h \
    $$PWD/include/IntDecorator.h \
    $$PWD/include/DoubleDecorator.h \
    $$PWD/include/BoolDecorator.h  \
    $$PWD/include/DateTimeDecorator.h \
    $$PWD/include/EnumeratorDecorator.h \
    $$PWD/include/Entity.h \
    $$PWD/include/EntityCollection.h \
    $$PWD/include/CollectionObject.h \
    $$PWD/include/DataDecoratorCollection.h \
    $$PWD/include/JsonAuto.h

SOURCES += \
    $$PWD/src/DataDecorator.cpp \
    $$PWD/src/StringDecorator.cpp \
    $$PWD/src/IntDecorator.cpp \
    $$PWD/src/DoubleDecorator.cpp \
    $$PWD/src/BoolDecorator.cpp \
    $$PWD/src/DateTimeDecorator.cpp \
    $$PWD/src/EnumeratorDecorator.cpp \
    $$PWD/src/Entity.cpp \
    $$PWD/src/CollectionObject.cpp

QT += core
