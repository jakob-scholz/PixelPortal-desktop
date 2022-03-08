#pragma once

#include <Arduboy2.h>
#include <ArduboyTones.h>

class Player
{
public:
  float x = 5;
  float y = 5;
  float vx = 0;
  float vy = 0;
  float oldvy = 0;
  bool onFloor = false;
  float ax = 1;
  float vmax = 2;
  float jump = -2;
  float g = 0.3;

public:
  void move();
};
