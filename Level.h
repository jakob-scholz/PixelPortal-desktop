#pragma once

#include <Arduboy2.h>
#include "Portal.h"
#include "Wall.h"

class Level
{
public:

  uint8_t currentLevel = 1;

  Portal portals[12] {};

  Wall walls[12] {};

  uint8_t playerInitialPosition[2] = {0,0};
  
  uint8_t door[2] = {0,0};
  bool openDoor = false;
  
  uint8_t key[2] = { 0 , 0 };
  bool keyTaken = false;

  bool border = true;

public:
  void resetLevel();
  void loadLevel();
  void drawLevel();
  void drawElements();
  void drawWalls();
};
