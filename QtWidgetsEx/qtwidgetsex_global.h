#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QTWIDGETSEX_LIB)
#  define QTWIDGETSEX_EXPORT Q_DECL_EXPORT
# else
#  define QTWIDGETSEX_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTWIDGETSEX_EXPORT
#endif
