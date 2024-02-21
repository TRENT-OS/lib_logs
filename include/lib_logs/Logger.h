/*
 * Copyright (C) 2019-2024, HENSOLDT Cyber GmbH
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * For commercial licensing, contact: info.cyber@hensoldt.net
 */

/**
 * @addtogroup lib_logs
 * @{
 *
 * @file Logger.h
 *
 * @brief The Logger Chain of Responsibility abstract Class. A logger is a
 *        simple abstraction of something that can enqueue and dequeue logs.
 *        Logs are enqueued when their log leve is according to the logger log
 *        levels mask. When a logger is logged in enqueued and "passed" to the
 *        next logger appended.
 *
 * @author Carmelo Pintaudi
 */

#if !defined(LOGGER_H)
#define LOGGER_H

#include "lib_logs/Log.h"

#include <stdint.h>
#include <stdbool.h>

#if !defined(DEBUG_CONFIG_H_FILE)
#   define Debug_ASSERT_SELF(x)
#else
#   include "lib_debug/Debug.h"
#endif
#include "lib_compiler/compiler.h"

struct Logger;
typedef struct Logger Logger;

typedef void
(*Logger_DtorT)(Logger* self);

typedef void
(*Logger_LogEnqueueT)(Logger* self, Log* log);

// The persistence of the return value is until a next call of dequeue occurs
typedef Log*
(*Logger_LogDequeueT)(Logger* self);


typedef struct
{
    Logger_DtorT        dtor;
    Logger_LogEnqueueT	enqueue;
    Logger_LogDequeueT	dequeue;
}
Logger_Iface;

struct Logger
{
    const Logger_Iface* vtable;
    void*
    context; // can be useful in the processing of the loggers chain
    void*               next;
    uint8_t             mask;
};

/* Ecported virtual functions ----------------------------------------------- */

INLINE void
Logger_dtor(Logger* self)
{
    Debug_ASSERT_SELF(self);
    self->vtable->dtor(self);
}

INLINE Log*
Logger_dequeue(Logger* self)
{
    Debug_ASSERT_SELF(self);
    return self->vtable->dequeue(self);
}

INLINE void
Logger_enqueue(Logger* self, Log* log)
{
    Debug_ASSERT_SELF(self);
    return (self)->vtable->enqueue(self, log);
}

/* Exported static functions  ----------------------------------------------- */

/**
 * @brief constructor
 *
 * @param self pointer to self
 * @param mask for the abled Log_Level of the logger
 *
 * @return self
 *
 */
bool
Logger_ctor(Logger* self, uint8_t mask);

/**
 * @brief distructor
 */
void
Logger_staticDtor(Logger* self);

/**
 * @brief distructor along the chain, self excluded
 */
void
Logger_chainDtor(Logger* self);

INLINE uint8_t
Logger_getMask(const Logger* self)
{
    Debug_ASSERT_SELF(self);
    return self->mask;
}

INLINE void
Logger_setMask(Logger* self, uint8_t mask)
{
    Debug_ASSERT_SELF(self);
    self->mask = mask;
}

INLINE Logger*
Logger_getNext(const Logger* self)
{
    Debug_ASSERT_SELF(self);

    return self->next;
}

INLINE void
Logger_setNext(Logger* self, Logger* next)
{
    Debug_ASSERT_SELF(self);
    self->next = next;
}

/**
 * @brief log function, it calls the log enqueue function according to the masks
 * and levels forwarding this behaviour along the chain
 *
 * @param self pointer to self
 * @param level the level kind of the log (eg debug, info etc)
 * @param msg the log string
 *
 */
void
Logger_log(Logger* self, uint8_t level, const char* msg);

/**
 * @brief dequeue a log message
 *
 * @param self pointer to self
 *
 * @return a char pointer to the first next log message, NULL if none
 *
 */
char const*
Logger_getLogMsg(Logger* self);

/**
 * @brief find a logger in the chain
 *
 * @param self pointer to the head of chain
 * @param logger pointer to the logger to find
 *
 * @return true if found else false
 *
 */
bool
Logger_findInChain(const Logger* self, Logger* logger);

/**
 * @brief it appends a logger on the queue of the chain calling recursively until
 * a NULL next is reached
 *
 * @param self pointer to self
 * @param logger the given logger to append
 *
 */
void
Logger_app(Logger* self, Logger* logger);

/**
 * @brief it appends a logger on the queue of the chain calling recursively until
 * a NULL next is reached
 *
 * @param self pointer to self
 * @param logger the given logger to append
 *
 * @return true if success else false
 *
 */
bool
Logger_remFromChain(Logger* self, Logger* logger);


#endif /* <HEADER_UNIQUE_SYMBOL_H> */
/** @} */

