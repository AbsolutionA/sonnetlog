#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "../include/sonnetlog.h"

static char*    sonnet_log_file_location = NULL;
static long     sonnet_log_max_size = 0;

inline void sonnet_log_set_file_info(const char *file_location_and_name, long file_max_size) {
    sonnet_log_file_location = (char *)file_location_and_name;
    if (sonnet_log_file_location == NULL) {
        fprintf(stderr, "Warning: File location not given!\n");
        return;
    }

    if(file_max_size > 0) {
        sonnet_log_max_size = file_max_size;
    } else {
        fprintf(stderr, "Error: The maximum size of the log file is not greater then 0.\n");
    }
}

long sonnet_log_get_file_size(const char* file_name) {
    FILE *file = fopen(file_name, "r");
    if (!file) {
        fprintf(stderr, "Error: Failed to open log file to get file size: '%s': %s\n", file_name, strerror(errno));
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    if (file_size == -1) {
        fprintf(stderr, "Error: Failed to get file size: %s\n", strerror(errno));
    }
    fclose(file);
    return file_size;
}

inline void sonnet_log(const char *msg, const char *tag_name, const int log_on_or_off) {
    static size_t i = 0;

    long log_size = sonnet_log_get_file_size(sonnet_log_file_location);
    if (log_size > sonnet_log_max_size && i == 0) {
        FILE *file = fopen(sonnet_log_file_location, "w");
        if (file == NULL) {
            fprintf(stderr, "Error: Failed to open log file to clear: %s\n", strerror(errno));
            return;
        }
        fclose(file);
    }

    
    
    FILE *file = fopen(sonnet_log_file_location, "a");
    if (!file) {
        fprintf(stderr, "Error: Failed to open log file: %s\n", strerror(errno));
        return;
    }


    if (i == 0 && log_on_or_off) {
        fprintf(file, "[New Session] ----------------------------------------------------------------------------------------\n");
        i++;
    }
    
    time_t now = time(NULL);
    char timestamp[256];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));

    if (tag_name != NULL) {
        if(log_on_or_off) {
            fprintf(file, "[%s] %s: %s", timestamp, tag_name, msg);
            fprintf(stderr, "[%s] %s: %s", timestamp, tag_name, msg);
        }
        else fprintf(stderr, "[%s] %s: %s", timestamp, tag_name, msg);
    }
    else if (tag_name == NULL && log_on_or_off) {
        fprintf(file, "[%s] %s", timestamp, msg);
        fprintf(stderr, "[%s] %s", timestamp, msg);
    }
    else fprintf(stderr, "[%s] %s", timestamp, msg);
    fclose(file);
}