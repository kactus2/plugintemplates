// Copyright Tampere University of Technology

#ifndef SAMPLEIMPORT_GLOBAL_H
#define SAMPLEIMPORT_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef SAMPLEIMPORT_LIB
# define SAMPLEIMPORT_EXPORT Q_DECL_EXPORT
#else
# define SAMPLEIMPORT_EXPORT Q_DECL_IMPORT
#endif

#endif // SAMPLEIMPORT_GLOBAL_H
