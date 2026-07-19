# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2026-07-19

### Changed

- `clap.c` is now `clap.h`, an [stb-style](https://github.com/nothings/stb) single file header.
- All functions and variables now use snake_case instead of camelCase.
- All functions and variables are now prefixed with `clap_`, macros `CLAP_`.
- Where the word `option` was used to refer to parsed arguments now use `parsed` instead.
- Update `example.c` to match these changes.
- Update `README.md` to reflect these changes.

## [0.1.0] - 2026-07-19

Initial release
