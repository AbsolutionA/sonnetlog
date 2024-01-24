#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "../include/sonnetlog.h"

static char* sonnet_log_file_location = NULL;

void sonnet_log_set_file_location_and_name(const char *file_location_and_name) {
    sonnet_log_file_location = (char *)file_location_and_name;
    if (sonnet_log_file_location == NULL) {
        fprintf(stderr, "Warning: File location not given!\n");
        return;
    }
}

void sonnet_log(const char *msg, const char *tag_name, const int log_on_or_off) {

    static size_t i = 0;
    
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