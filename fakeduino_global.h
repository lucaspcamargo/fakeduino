#ifndef FAKEDUINO_GLOBAL_H
#define FAKEDUINO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FAKEDUINO_LIBRARY)
#  define FAKEDUINO_EXPORT Q_DECL_EXPORT
#else
#  define FAKEDUINO_EXPORT Q_DECL_IMPORT
#endif

#endif // FAKEDUINO_GLOBAL_H
