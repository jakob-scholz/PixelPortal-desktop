#include "Wall.h"

#include <Arduboy2.h>

void Wall::resetWall(){
  this->x = 0;
  this->y = 0;
  this->w = 0;
  this->h = 0;
}

void Wall::setWall(uint8_t x, uint8_t y, uint8_t w,uint8_t h){
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
}
