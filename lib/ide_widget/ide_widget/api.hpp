#ifndef IDE_API_HPP
#define IDE_API_HPP

#include <QtCore/QtGlobal>

#if defined(IDE_WIDGET_LIBRARY)
#  define IDE_WIDGET_LIB_EXPORT Q_DECL_EXPORT
#else
#  define IDE_WIDGET_LIB_EXPORT Q_DECL_IMPORT
#endif

#endif // IDE_API_HPP
