#ifndef SONNET_LOG_H
#define SONNET_LOG_H

#include <stdint.h>
#include <stdlib.h>

#define SONNET_LOG_FILE_MAX_SIZE_DEFAULT 0xA00000 // 10 MB


/** @brief Will print a custom error given to this preprocessor on to stderr and a .txt file that has been set in the sonnet_log_set_file_location() function. */
#define SERROR(...) do { \
    uint32_t size = snprintf(NULL, 0, __VA_ARGS__); \
    char *buffer = (char *)malloc(size + 1); \
    if (buffer != NULL) { \
        sprintf(buffer, __VA_ARGS__); \
        sonnet_log(buffer, "Error", 1); \
        free(buffer); \
        buffer = NULL; \
    } \
} while(0)

/** @brief Will print a custom log given to this preprocessor on to stderr and a .txt file that has been set in the sonnet_log_set_file_location() function. */
#define SLOG(...) do { \
    uint32_t size = snprintf(NULL, 0, __VA_ARGS__); \
    char *buffer = (char *)malloc(size + 1); \
    if (buffer != NULL) { \
        sprintf(buffer, __VA_ARGS__); \
        sonnet_log(buffer, "Log", 1); \
        free(buffer); \
        buffer = NULL; \
    } \
} while(0)

/** @brief Will print a custom info given to this preprocessor on to stderr and a .txt file that has been set in the sonnet_log_set_file_location() function. */
#define SINFO(...) do { \
    uint32_t size = snprintf(NULL, 0, __VA_ARGS__); \
    char *buffer = (char *)malloc(size + 1); \
    if (buffer != NULL) { \
        sprintf(buffer, __VA_ARGS__); \
        sonnet_log(buffer, "Info", 1); \
        free(buffer); \
        buffer = NULL; \
    } \
} while(0)

/** @brief Will print a custom message with no tag given to this preprocessor on to stderr. */
#define SNOLOG(...) do { \
    uint32_t size = snprintf(NULL, 0, __VA_ARGS__); \
    char *buffer = (char *)malloc(size + 1); \
    if (buffer != NULL) { \
        sprintf(buffer, __VA_ARGS__); \
        sonnet_log(buffer, NULL, 0); \
        free(buffer); \
        buffer = NULL; \
    } \
} while(0)

/** @brief Set the file location and name here, doesn't matter if the file already exists, this function must always be called first.
 *  And specify the maximum file size for the log file. Use SONNET_LOG_FILE_MAX_SIZE_DEFAULT for the default value "10 MB" */
extern void sonnet_log_set_file_info(const char *file_location_and_name, long file_max_size);

/** @brief Will print a custom message with a custom inputed tag name given to this function on to stderr and 
 * a .txt file that has been set in the sonnet_log_set_file_location() function and only if the log_on_or_off argument is 1. */
extern void sonnet_log(const char *msg, const char *tag_name, const int log_on_or_off);

#endif // ERROR_HANDLER_H