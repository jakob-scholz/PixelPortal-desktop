#pragma once

#include <Arduboy2.h>
#include "PortalType.h"

class Portal
{
public:
  uint8_t x = 0;
  uint8_t y = 0;
  PortalType type = PortalType::Inactive;
  uint8_t destination = 0;
  uint8_t motion = 0;
  uint8_t distance = 0;
  uint8_t wave = 0;
  uint8_t direction[2] = { 0 , 0 };

public:
  void resetPortal();
  void setPortal(uint8_t x, uint8_t y, PortalType type,uint8_t destination,uint8_t motion,uint8_t distance,uint8_t wave);
};
