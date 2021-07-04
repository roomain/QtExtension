#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QT_EXTENSION_LIB)
#  define QT_EXTENSION_EXPORT Q_DECL_EXPORT
# else
#  define QT_EXTENSION_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTCLASSLIBRARY1_EXPORT
#endif
