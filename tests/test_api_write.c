#include "regmap.h"

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define ARRAY_SIZE 100
static uint8_t array[ARRAY_SIZE];

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
  map.read = NULL;
  map.write = array_u8_write;

  array_data[0] = 0x11;
  array_data[1] = 0x22;

  /* test read element 0 */
  assert(regmap_write(&map, 0, 0x33) == REGMAP_OK);
  assert(array_data[0] == 0x33);

  /* test read element 0 */
  assert(regmap_write(&map, 1, 0x44) == REGMAP_OK);
  assert(array_data[1] == 0x44);
}

