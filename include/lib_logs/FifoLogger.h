/**
 * @addtogroup LibLogs
 * @{
 *
 * @file FifoLogger.h
 *
 * @brief Logger that logs through a FIFO of logs
 *
 *
 * @author Carmelo Pintaudi
 *
 * Copyright (C) 2019, Hensoldt Cyber GmbH
 */

#ifndef FIFOLOGGER_H
#define FIFOLOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "LibLogs/Logger.h"
#include "LibLogs/LogFifo.h"

#define FifoLogger_TO_LOGGER(self) \
    (&((self)->parent))

typedef struct
{
    Logger      parent;
    LogFifo*    logFifo;
    bool        overflow;
}
FifoLogger;

bool
FifoLogger_ctor(FifoLogger* self,
                LogFifo* logFifo,
                uint8_t mask);
void
FifoLogger_dtor(Logger* logger);

Log*
FifoLogger_dequeue(Logger* logger);

void
FifoLogger_enqueue(Logger* logger, Log* log);

#ifdef __cplusplus
}
#endif

#endif /* FIFOLOGGER_H */

