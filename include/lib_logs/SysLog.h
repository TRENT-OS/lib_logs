/**
 * @addtogroup LibLogs
 * @{
 *
 * @file SysLog.h
 *
 * @brief The System Head of Loggers chain of resposibility
 *
 * @author Carmelo Pintaudi
 *
 * Copyright (C) 2019, Hensoldt Cyber GmbH
 */
#if !defined(SYSLOG_H)
#define SYSLOG_H

#if !defined(LOGS_CONFIG_H_FILE)
#   if !defined(Logs_Config_LOG_STRING_SIZE)
#       define Logs_Config_LOG_STRING_SIZE 128
#   endif
#else
#   define Debug_XSTR(d)    Debug_STR(d)
#   define Debug_STR(d)     #d
#   include Debug_XSTR(LOGS_CONFIG_H_FILE)
#endif

#include "LibLogs/Logger.h"

/* Exported macro ------------------------------------------------------------*/

#if Logs_Config_INCLUDE_LEVEL_IN_MSG == 0
#define SysLog_LOG(LEVEL, LEVEL_STR, ...) \
        SysLog_log(LEVEL, "" __VA_ARGS__)
#else
#define SysLog_LOG(LEVEL, LEVEL_STR, ...) \
        SysLog_log(LEVEL, LEVEL_STR ": " __VA_ARGS__)
#endif

#if     Logs_Config_SYSLOG_LEVEL < Log_TRACE
#define log_trace(...)
#else
#define log_trace(...)      SysLog_LOG(Log_TRACE,   "TRACE",    __VA_ARGS__)
#endif
#if     Logs_Config_SYSLOG_LEVEL < Log_DEBUG
#define log_debug(...)
#else
#define log_debug(...)      SysLog_LOG(Log_DEBUG,   "DEBUG",    __VA_ARGS__)
#endif
#if     Logs_Config_SYSLOG_LEVEL < Log_INFO
#define log_info(...)
#else
#define log_info(...)       SysLog_LOG(Log_INFO,    "INFO",     __VA_ARGS__)
#endif
#if     Logs_Config_SYSLOG_LEVEL < Log_WARNING
#define log_warning(...)
#else
#define log_warning(...)    SysLog_LOG(Log_WARNING, "WARNING",  __VA_ARGS__)
#endif
#if     Logs_Config_SYSLOG_LEVEL < Log_ERROR
#define log_error(...)
#else
#define log_error(...)      SysLog_LOG(Log_ERROR,   "ERROR",    __VA_ARGS__)
#endif
#if     Logs_Config_SYSLOG_LEVEL < Log_FATAL
#define log_fatal(...)
#else
#define log_fatal(...)      SysLog_LOG(Log_FATAL,   "FATAL",    __VA_ARGS__)
#endif


/* Exported functions ------------------------------------------------------- */

/**
 * @brief constructor
 *
 * @return true if ok, else fale
 *
 */
bool
SysLog_ctor(void);

/**
 * @brief distructor: be careful! this will not destroy the chain, it could
 * produce garbage. If you want to destroy the chain..use Logger_chainDtor()
 */
void
SysLog_dtor();

bool
SysLog_app(Logger* logger);

/**
 * @brief syslog log function to call the begin of the chain
 */
void
SysLog_log(uint8_t level, char const* fmt, ...);

/**
 * @brief this function safely removes a Logger from the system chain
 *
 * @param logger this is the pointer to the Logger that we have to manipulate
 *
 * @return true if ok else false
 *
 */
bool
SysLog_remFromChain(Logger* logger);

Logger*
SysLog_getChainHead(void);

#endif /* <HEADER_UNIQUE_SYMBOL_H> */
/** @} */

