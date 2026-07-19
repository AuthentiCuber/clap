#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAKE_ARRAY(Type, name) \
    typedef struct {           \
        Type *items;           \
        size_t count;          \
    } name

typedef struct {
    char *name;
    int numParams;
    char *help;
} Arg;

MAKE_ARRAY(Arg, argArray);

typedef struct {
    char *name;
    char **params;
    int numParams;
} Option;

MAKE_ARRAY(Option, optArray);

int parseArgs(argArray *toParse, int argc, char **argv, optArray *options) {
    options->items = calloc(toParse->count, sizeof(Option));
    for (int argvIdx = 1; argvIdx < argc; argvIdx++) {
        char *inp = argv[argvIdx];
        for (size_t expectedArgIdx = 0; expectedArgIdx < toParse->count;
             expectedArgIdx++) {
            Arg currArg = toParse->items[expectedArgIdx];
            if (strcmp(inp, currArg.name) == 0) {
                char **params = calloc(currArg.numParams, sizeof(char *));
                int paramHeadIdx = 0;
                for (int i = 0; i < currArg.numParams; i++) {
                    if (argvIdx + 1 >= argc) return 1;
                    params[paramHeadIdx++] = argv[++argvIdx];
                }
                options->items[options->count++] =
                    (Option){currArg.name, params, currArg.numParams};
            }
        }
    }
    return 0;
}

Option *getOpt(optArray *options, const char *optName) {
    for (size_t i = 0; i < options->count; i++) {
        Option *opt = &options->items[i];
        if (strcmp(opt->name, optName) == 0) return opt;
    }
    return NULL;
}

bool hasFlag(optArray *options, const char *flagName) {
    return getOpt(options, flagName) != NULL;
}

void showHelp(argArray *expected, const char *progName, const char *usage) {
    printf("Usage: %s ", progName);
    if (usage == NULL) {
        printf("[OPTIONS]");
    } else {
        printf("%s", usage);
    }
    printf("\n\nAvailable options:\n");

    const char *argStr = "<arg>";
    int longestLen = 0;
    for (size_t i = 0; i < expected->count; i++) {
        Arg opt = expected->items[i];
        int currLen = strlen(opt.name) + opt.numParams * (1 + strlen(argStr));
        if (currLen > longestLen) { longestLen = currLen; }
    }
    for (size_t i = 0; i < expected->count; i++) {
        Arg opt = expected->items[i];
        printf("  ");
        int lineLen = printf("%s", opt.name);
        for (int j = 0; j < opt.numParams; j++) {
            lineLen += printf(" %s", argStr);
        }
        while (lineLen < longestLen) {
            putchar(' ');
            lineLen++;
        }
        printf("  %s\n", opt.help);
    }
}
