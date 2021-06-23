//
// Created by Admin on 2021/6/22.
//

#ifndef LINUXC_DEMO_LOGGER_H
#define LINUXC_DEMO_LOGGER_H

/*
 * Log level configurator
 * Default is LOG_MAX_LEVEL_ERROR_WARNING_STATUS
 */

#define LOG_MAX_LEVEL_ERROR 0
#define LOG_MAX_LEVEL_ERROR_WARNING_STATUS 1
#define LOG_MAX_LEVEL_ERROR_WARNING_STATUS_DEBUG 2

void logger_set_log_level(const int level);

/*
 * Logging methods by levels
 */
void log_debug(char *format, ...);

void log_error(char *format, ...);

void log_warning(char *format, ...);

void log_status(char *format, ...);

/*
 * Set target type
 * Default is syslog
 */
void logger_reset_state();

int logger_set_log_file(const char *filename);

void logger_set_out_stdout();

#endif //LINUXC_DEMO_LOGGER_H
