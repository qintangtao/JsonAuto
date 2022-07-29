#ifndef JSONAUTO_H
#define JSONAUTO_H

#include <QtCore/qglobal.h>

#if defined(JSONAUTO_LIBRARY)
    #define JSONAUTOSHARED_EXPORT Q_DECL_EXPORT
#else
    #if defined(JSONAUTO_SOURCE)
        #define JSONAUTOSHARED_EXPORT
    #else
        #define JSONAUTOSHARED_EXPORT Q_DECL_IMPORT
    #endif
#endif


#endif // JSONAUTO_H
