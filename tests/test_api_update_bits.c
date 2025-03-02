#include "regmap.h"

#include <stdint.h>
#include <assert.h>

#define ARRAY_SIZE 100
static uint8_t array[ARRAY_SIZE];

static int32_t array_u8_read(uint32_t addr, void* val) {
  *(uint32_t*)val = (uint32_t)(((uint8_t*)array)[addr]);
  return REGMAP_OK;
}

static int32_t array_u8_write(uint32_t addr, void* val) {
  ((uint8_t*)array)[addr] = *(uint8_t*)val;
  return REGMAP_OK;
}

int32_t main(int32_t argc, char* argv[]) {
  struct regmap_struct map;
  uint8_t* array_data;

  array_data = ((uint8_t*)array);

  map.address = 0;
  map.access = REGMAP_ACCESS_FULL;
  map.word_size = sizeof(uint8_t);
  map.length = 2;
  map.read = array_u8_read;
  map.write = array_u8_write;

  array_data[0] = 0x11;
  array_data[1] = 0x22;

  /* test update bits, in mask */
  assert(regmap_update_bits(&map, 0, 0x20, 0x20) == REGMAP_OK);
  assert(array_data[0] == 0x31);

  /* test update bits, in mask */
  assert(regmap_update_bits(&map, 1, 0x40, 0x80) == REGMAP_OK);
  assert(array_data[1] == 0x22);
}

