#pragma once
#include <cstdint>

class Wall
{
public:
  uint8_t x = 0;
  uint8_t y = 0;
  uint8_t w = 0;
  uint8_t h = 0;

public:
  void resetWall();
  void setWall(uint8_t x, uint8_t y, uint8_t w,uint8_t h);
};
