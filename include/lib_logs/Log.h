/**
 * @addtogroup lib_logs
 * @{
 *
 * @file Log.h
 *
 * @brief Log definition
 *
 *
 * @author Carmelo Pintaudi
 *
 * Copyright (C) 2019, HENSOLDT Cyber GmbH
 */
#if !defined(LOG_H)
#define LOG_H

#include <stdint.h>

#define Log_NONE        0
#define Log_FATAL       1
#define Log_ERROR       2
#define Log_WARNING     3
#define Log_INFO        4
#define Log_DEBUG       5
#define Log_TRACE       6
#define Log_RESERVED    7

#define Log_MASK_ALL                        ((uint8_t) 0xFF)
#define Log_MASK_RESERVED                   ((uint8_t) 0x01 << Log_MAX_RESERVED)
#define Log_MASK_TRACE                      ((uint8_t) 0x01 << Log_TRACE)
#define Log_MASK_DEBUG                      ((uint8_t) 0x01 << Log_DEBUG)
#define Log_MASK_INFO                       ((uint8_t) 0x01 << Log_INFO)
#define Log_MASK_WARNING                    ((uint8_t) 0x01 << Log_WARNING)
#define Log_MASK_ERROR                      ((uint8_t) 0x01 << Log_ERROR)
#define Log_MASK_FATAL                      ((uint8_t) 0x01 << Log_FATAL)
#define Log_MASK_NONE                       ((uint8_t) 0x00)

typedef struct
{
    void*   context; // this is useful to add optional data like a timestamp
    char*   string;
    uint8_t level;
}
Log;


#define Log_ctor(log, msg, lev, ctx)                                            \
                (((log)->string = (msg)),                                       \
                ((log)->level = (lev)),                                         \
                ((log)->context = (ctx)), true)

#define Log_dtor(log)

#define Log_maskOfLevel(level)                                                  \
  ((level) > Log_RESERVED ? Log_MASK_NONE : ((uint8_t) 0x01 << (level)))


#endif /* <HEADER_UNIQUE_SYMBOL_H> */
/** @} */

