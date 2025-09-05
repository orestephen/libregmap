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

## Usage

### API Notes

`read` and `write` callbacks must have a return code.

`word_size` is not checked when reading or writing to a regmap. This may be done in the future.

### example

```code
#include "regmap.h"

struct regmap_struct map;
uint8_t reg[10];

int32_t read(uint32_t addr, void* val) {
  REGMAP_READ_WORD(val, ((uint8_t*)reg)[addr]);
  return REGMAP_OK;
}

int32_t write(uint32_t addr, void* val) {
  REGMAP_WRITE_WORD(val, ((uint8_t*)reg)[addr]);
  return REGMAP_OK;
}

void init(void) {
  map.address = 0x00;
  map.access = REGMAP_ACCESS_FULL;
  map.word_size = sizeof(reg);
  map.length = 10;
  map.read = &read;
  map.write = &write;
}

...

ret = regmap_write(&map, 0, 0xAA);
if (ret) {
  printf("regmap error: %d\r\n", ret);
}

...

uint32_t data;
ret = regmap_read(&map, 0, &data);
if (ret) {
  printf("regmap error: %d\r\n", ret);
}

...

ret = regmap_update_bits(&map, 0, 0x0F, 0x05);
if (ret) {
  printf("regmap error: %d\r\n", ret);
}
```

## Tests

run tests

`ctest --test-dir build/tests/`

### Unit Tests

[![CMake CI](https://github.com/orestephen/libregmap/actions/workflows/ci.yml/badge.svg)](https://github.com/orestephen/libregmap/actions/workflows/ci.yml)

 - test_api_read: ensure read api are functioning
 - test_api_write: ensure write api are functioning
 - test_api_update_bits: ensure update bits api are functioning
 - test_u8_array: ensure u8 array are functioning
 - test_u16_array: ensure u16 array are functioning
