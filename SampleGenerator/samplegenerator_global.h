// Copyright Tampere University of Technology

#ifndef SAMPLEGENERATOR_GLOBAL_H
#define SAMPLEGENERATOR_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef SAMPLEGENERATOR_LIB
# define SAMPLEGENERATOR_EXPORT Q_DECL_EXPORT
#else
# define SAMPLEGENERATOR_EXPORT Q_DECL_IMPORT
#endif

#endif // SAMPLEGENERATOR_GLOBAL_H
