#include "regmap.h"

int32_t regmap_read(struct regmap_struct* map, uint32_t addr, uint32_t* val) {
  /* sanity check */
  if (!map) return REGMAP_ERROR;

  /* sanity check input */
  if (!val) return REGMAP_ERROR_VALUE;

  /* check access */
  if (!(map->access & REGMAP_ACCESS_READ)) return REGMAP_ERROR_ACCESS;

  /* check addressing */
  if (addr < map->address || addr > (map->address + map->length - 1)) return REGMAP_ERROR_ADDRESS;

  /* check callback */
  if (!map->read) return REGMAP_ERROR;

  /* read data */
  return map->read(addr - map->address, val);
}

int32_t regmap_write(struct regmap_struct* map, uint32_t addr, uint32_t val) {
  /* sanity check */
  if (!map) return REGMAP_ERROR;

  /* sanity check access */
  if (!(map->access & REGMAP_ACCESS_WRITE)) return REGMAP_ERROR_ACCESS;

  /* check addressing */
  if (addr < map->address || addr > (map->address + map->length - 1)) return REGMAP_ERROR_ADDRESS;

  /* write data */
  return map->write(addr - map->address, (void*)&val);
}

int32_t regmap_update_bits(struct regmap_struct* map, uint32_t addr, uint32_t mask, uint32_t val) {
  int32_t ret;
  uint32_t orig;
  uint32_t temp;

  ret = regmap_read(map, addr, &orig);
  if (ret) return ret;

  temp = orig & ~mask;
  temp |= val & mask;

  if (temp == orig) return REGMAP_OK;

  return regmap_write(map, addr, temp);
}
