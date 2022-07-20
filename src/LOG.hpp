/**================================================================================================
*
Basic logger utility.
Has three levels. Use LOG_DEBUG(T), LOG_INFO(T) or LOG_ERROR(T) to log.

Doesn't log if LOG_LEVEL is undefined.
Priorities are as follows: [LOG_LEVEL_ERROR] > [LOG_LEVEL_INFO] > [LOG_LEVEL_DEBUG]

================================================================================================**/

#pragma once
#include <string>
#include <iostream>

#if defined(LOG_LEVEL_DEBUG)
#define LOG_DEBUG(msg) std::cout << "DEBUG: "; std::cout << msg << std::endl;
#endif
#if not defined(LOG_LEVEL_DEBUG)
#define LOG_DEBUG(msg);
#endif

#if defined(LOG_LEVEL_DEBUG) || defined(LOG_LEVEL_INFO)
#define LOG_INFO(msg) std::cout << "INFO: "; std::cout << msg << std::endl;
#endif
#if not defined(LOG_LEVEL_DEBUG) || defined(LOG_LEVEL_INFO)
#define LOG_INFO(msg);
#endif

#if defined(LOG_LEVEL_DEBUG) || defined(LOG_LEVEL_INFO) || defined(LOG_LEVEL_ERROR)
#define LOG_ERROR(msg) std::cout << "ERROR: "; std::cout << msg << std::endl;
#endif
#if not defined(LOG_LEVEL_DEBUG) || defined(LOG_LEVEL_INFO) || defined(LOG_LEVEL_ERROR)
#define LOG_ERROR(msg);
#endif