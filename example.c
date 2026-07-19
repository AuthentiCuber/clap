#include "clap.c"

int main(int argc, char **argv) {
    // { "option-text", num-parameters, "help-text" }
    Arg myargs[] = {
        {"--option", 1, "configure a thing"},
        {"--help", 0, "show this help message"},
        {"run", 1, "run a file"},
    };
    argArray expected = {
        myargs,
        sizeof(myargs) / sizeof(myargs[0]) // the number of arguments
    };

    // allocate space for the parsed args
    optArray *options = malloc(sizeof(optArray));
    // parsing populates `options` from argv
    int parseErr = parseArgs(&expected, argc, argv, options);
    if (parseErr != 0) { // non-zero means error
        fprintf(stderr, "failed to parse args!");
        return 1;
    }

    // use `hasFlag` to check for the presence of a flag
    // i.e. it has no arguments/you dont need them
    if (hasFlag(options, "--help")) {
        // `showHelp` generates and prints a help message
        showHelp(&expected, argv[0], NULL);
        return 0;
    }

    // This variable is reused for each getOpt
    Option *opt;

    // getOpt returns the actual Option, or NULL if it
    // wasn't passed
    if ((opt = getOpt(options, "--option")) != NULL) {
        size_t value = strtoul(opt->params[0], NULL, 10);
        printf("Setting something to %zu\n", value);
    }

    if ((opt = getOpt(options, "run")) != NULL) {
        printf("Running %s...\n", opt->params[0]);
        return 0;
    }

    showHelp(&expected, argv[0], NULL);
    return 1;
}
