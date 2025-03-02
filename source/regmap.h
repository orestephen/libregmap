#ifndef __REGMAP_H
#define __REGMAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define REGMAP_OK 0
#define REGMAP_ERROR -1
#define REGMAP_ERROR_VALUE -2
#define REGMAP_ERROR_ADDRESS -3
#define REGMAP_ERROR_ACCESS -4

#define REGMAP_ACCESS_READ 1
#define REGMAP_ACCESS_WRITE 2
#define REGMAP_ACCESS_FULL 3

struct regmap_struct {
  uint16_t address;
  uint8_t access;
  uint8_t word_size;
  uint16_t length;
  int32_t (*read)(uint32_t addr, void* val);
  int32_t (*write)(uint32_t addr, void* val);
};

int32_t regmap_read(struct regmap_struct* map, uint32_t addr, uint32_t* val);
int32_t regmap_write(struct regmap_struct* map, uint32_t addr, uint32_t val);
int32_t regmap_update_bits(struct regmap_struct* map, uint32_t addr, uint32_t mask, uint32_t val);

#ifdef __cplusplus
}
#endif

#endif
