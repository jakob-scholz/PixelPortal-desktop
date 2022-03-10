#pragma once

#include <Arduboy2.h>

class Player{
public:
  float x = 5;
  float y = 5;
  float vx = 0;
  float vy = 0;
  float oldvy = 0;
  bool onFloor = false;
  int currentPortal = -1;
  float ax = 1;
  float vmax = 2;
  float jump = -2.3;
  float g = 0.3;
  uint8_t jumpCounter=0;
  uint8_t portalCoolDown = 0;

public:
  void processInputs();
  void move();
  void update();
  void tryMoveX(int dist);
  void tryMoveY(int dist);
  void jumpPortals();
  int inPortal();
  bool touchingKey();
  bool touchingDoor();
};
