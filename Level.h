#pragma once

#include <Arduboy2.h>
#include "Portal.h"

class Level
{
public:

  uint8_t currentLevel = 1;
  
  Portal portals[8] = {};
  uint8_t portalCoolDown = 0;
  
  uint8_t playerInitialPosition[2] = {0,0};
  
  uint8_t door[2] = {0,0};
  bool openDoor = false;
  
  uint8_t key[2] = { 0 , 0 };
  bool keyTaken = false;

  

public:
  void resetPortals();
  void loadLevel();
};
