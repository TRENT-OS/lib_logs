/**
 * @addtogroup LibLogs
 * @{
 *
 * @file LogFifo.h
 *
 * @brief Fifo of LogElements, a LogElement is a composition of a Log that
 *        points to a static buffer containing the log string
 *
 * @author Carmelo Pintaudi
 *
 * Copyright (C) 2019, Hensoldt Cyber GmbH
 */

#ifndef LOGFIFO_H
#define LOGFIFO_H

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(LOGS_CONFIG_H_FILE)
#   if !defined(Logs_Config_LOG_STRING_SIZE)
#       define Logs_Config_LOG_STRING_SIZE 128
#   endif
#else
#   define Debug_XSTR(d)    Debug_STR(d)
#   define Debug_STR(d)     #d
#   include Debug_XSTR(LOGS_CONFIG_H_FILE)
#endif

#include "LibUtil/FifoT.h"
#include "LibLogs/Log.h"

typedef struct
{
    Log     log;
    char    logString[Logs_Config_LOG_STRING_SIZE];
}
LogFifo_Element;

typedef FifoT_TYPE(LogFifo_Element, size_t) LogFifo;

FifoT_DECLARE(LogFifo_Element, LogFifo, size_t);

#ifdef __cplusplus
}
#endif

#endif /* LOGFIFO_H */

