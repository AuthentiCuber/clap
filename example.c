#include <stdlib.h>
#define CLAP_IMPLEMENTATION
#include "clap.h"

int main(int argc, char **argv) {
    // { "option-text", num-parameters, "help-text" }
    clap_arg myargs[] = {
        {"--option", "-o", 1, "configure a numeric setting"},
        {"--help", "-h", 0, "show this help message"},
        {"run", "", 1, "run a file"},
    };
    clap_arg_array expected = {
        myargs,
        sizeof(myargs) / sizeof(myargs[0]) // the number of arguments
    };

    // allocate space for the parsed args
    clap_parsed_array *options = malloc(sizeof(clap_parsed_array));
    // as well as for any positianal/unexpected arguments
    clap_unexpected_array *unexpected = malloc(sizeof(clap_unexpected_array));
    // parsing populates `options`, `unexpected` from argv
    int parseErr = clap_parse_args(&expected, argc, argv, options, unexpected);
    if (parseErr) { // non-zero means error
        fprintf(stderr, "failed to parse args!");
        return 1;
    }

    // use `has_flag` to check for the presence of a flag
    // i.e. it has no arguments/you dont need them
    if (clap_has_flag(options, "--help")) {
        // `showHelp` generates and prints a help message
        clap_show_help(&expected, argv[0], NULL);
        return 0;
    }

    // This variable is reused for each getOpt
    clap_parsed *opt;

    // get_opt returns the parsed option, or NULL if it
    // wasn't passed. get_opt ant has_flag also check for
    // the provided aliases
    if ((opt = clap_get_opt(options, "--option")) != NULL) {
        size_t value = strtoul(opt->params[0], NULL, 10);
        printf("Setting something to %zu\n", value);
    }

    if ((opt = clap_get_opt(options, "run")) != NULL) {
        printf("Running %s...\n", opt->params[0]);
        return 0;
    }

    // use this for when you have (multiple) positional arguments
    // that aren't part of a subcommand
    if (unexpected->count > 0) {
        printf("Doing something with %s\n", unexpected->items[0]);
        return 0;
    }

    clap_show_help(&expected, argv[0], NULL);
    return 1;
}
