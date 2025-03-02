# libregmap

A simple regmap library

Library is intended to be used on small applications.

## Config

`cmake -S . -B build`

## Build

`cmake --build build`

### options

enable compile commands output

`-DCMAKE_EXPORT_COMPILE_COMMANDS=1`

enable ctest testing
`-REGMAP_TEST=1`

## Tests

run tests

`ctest --test-dir build/tests/`

### Unit Tests

 - test_api_read: ensure read api are functioning
 - test_api_write: ensure write api are functioning
 - test_api_update_bits: ensure update bits api are functioning
 - test_u8_array: ensure u8 array are functioning
 - test_u16_array: ensure u16 array are functioning
