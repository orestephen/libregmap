#include "regmap.h"

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define ARRAY_SIZE 100
static uint8_t array[ARRAY_SIZE];

static int32_t array_u8_read(uint32_t addr, void* val) {
  *(uint32_t*)val = (uint32_t)(((uint8_t*)array)[addr]);
  return REGMAP_OK;
}

int32_t main(int32_t argc, char* argv[]) {
  struct regmap_struct map;
  uint8_t* array_data;
  uint32_t data;

  array_data = ((uint8_t*)array);

  map.address = 0;
  map.access = REGMAP_ACCESS_FULL;
  map.word_size = sizeof(uint8_t);
  map.length = 2;
  map.read = array_u8_read;
  map.write = NULL;

  array_data[0] = 0x11;
  array_data[1] = 0x22;

  /* test read element 0 */
  data = 0;
  assert(regmap_read(&map, 0, &data) == REGMAP_OK);
  assert(data == 0x11);

  /* test read element 0 */
  data = 0;
  assert(regmap_read(&map, 1, &data) == REGMAP_OK);
  assert(data == 0x22);
}

