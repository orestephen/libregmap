#include "regmap.h"

#include <stdint.h>
#include <assert.h>

#define ARRAY_SIZE 100
static uint8_t array[ARRAY_SIZE];

static int32_t array_u8_read(uint32_t addr, void* val) {
  REGMAP_READ_WORD(val, ((uint8_t*)array)[addr]);
  return REGMAP_OK;
}

static int32_t array_u8_write(uint32_t addr, void* val) {
  REGMAP_WRITE_WORD(val, ((uint8_t*)array)[addr]);
  return REGMAP_OK;
}

int32_t main(int32_t argc, char* argv[]) {
  struct regmap_struct map;
  uint8_t* array_data;
  uint32_t address;
  uint32_t data;

  array_data = ((uint8_t*)array);

  map.address = 0;
  map.access = REGMAP_ACCESS_FULL;
  map.word_size = sizeof(uint8_t);
  map.length = 2;
  map.read = array_u8_read;
  map.write = array_u8_write;

  array_data[0] = 0x11;
  array_data[1] = 0x12;

  /* element 0 test */
  data = 0;
  address = 0;
  assert(regmap_read(&map, address, &data) == REGMAP_OK);
  assert(data == 0x11);
  assert(regmap_write(&map, address, 0x01) == REGMAP_OK);
  assert(array_data[address] == 0x01);

  /* element next test */
  data = 0;
  address = 1;
  assert(regmap_read(&map, address, &data) == REGMAP_OK);
  assert(data == 0x12);
  assert(regmap_write(&map, address, 0x02) == REGMAP_OK);
  assert(array_data[address] == 0x02);

  /* out of bounds element test */
  data = 0;
  address = 2;
  assert(regmap_read(&map, address, &data) == REGMAP_ERROR_ADDRESS);
}
