#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ARGS_CONTAINS(argc, argv, ...) \
    args_has_any(argc, argv, \
        (sizeof((const char*[]){__VA_ARGS__}) / sizeof(const char*)), \
        (const char*[]){__VA_ARGS__})

char* read_file(char* file_path);
bool args_has(int argc, char** argv, char* target);
bool args_has_any(int argc, char** argv, int targetc, const char** targetv);

// gcc src/main.c -std=c17 -Wall -Wextra -Wpedantic -g -O0 -o out; ./out
int main(int argc, char** argv) {
    if (argc == 1) {
        printf("help page\n");
        exit(0);
    }

    bool flag_number = ARGS_CONTAINS(argc, argv, "-n", "--number");
    printf("%s\n", flag_number ? "true" : "false");

    // char* file_path = argv[1];
    // char* buf = read_file(file_path);

    // printf("%s\n", buf);

    return 0;
}

char* read_file(char* file_path) {
    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("failed to read file\n");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file); 

    char* buf = (char*)malloc(size + 1);
    if (buf == NULL) {
        printf("failed to allocate memory for buffer\n");
        fclose(file);
        exit(1);
    }

    fread(buf, 1, size, file);
    buf[size] = '\0';

    fclose(file);
    return buf;
}

bool args_has(int argc, char** argv, char* target) {
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], target) == 0) {
            return true;
        }
    }
    return false;
}

bool args_has_any(int argc, char** argv, int targetc, const char** targetv) {
    for (int i = 0; i < argc; ++i) {
        for (int j = 0; j < targetc; ++j) {
            if (strcmp(argv[i], targetv[j]) == 0) {
                return true;
            }
        }
    }
    return false;
}