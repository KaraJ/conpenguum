#ifndef QTXMLPARSE_GLOBAL_H
#define QTXMLPARSE_GLOBAL_H

#include <QtCore/qglobal.h>
#include "Image.h"
#include <vector>
#include <qfile.h>
#include <qdom.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>

#if defined(QTXMLPARSE_LIBRARY)
#  define QTXMLPARSESHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTXMLPARSESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTXMLPARSE_GLOBAL_H
