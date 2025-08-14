#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../include/config.h"

bool load_env(const char *filename) {
    FILE *file_path = fopen(filename, "r");
    if (!file_path) return false;

    char line[0x100];
    while (fgets(line, sizeof(line), file_path)) {
        line[strcspn(line, "\n")] = 0x0;
        if (line[0x0] == '#' || strlen(line) == 0x0) continue;

        char *eq = strchr(line, '=');
        if (!eq) continue;

        *eq = 0x0;
        setenv(line, eq + 0x1, 0x1);
    }

    fclose(file_path);
    return true;
}