#ifndef SAMPLESOURCEANALYZER_GLOBAL_H
#define SAMPLESOURCEANALYZER_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef SAMPLESOURCEANALYZER_LIB
# define SAMPLESOURCEANALYZER_EXPORT Q_DECL_EXPORT
#else
# define SAMPLESOURCEANALYZER_EXPORT Q_DECL_IMPORT
#endif

#endif // SAMPLEGENERATOR_GLOBAL_H
