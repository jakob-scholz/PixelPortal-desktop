#include "Portal.h"

#include <Arduboy2.h>
#include "Globals.h"

void Portal::resetPortal()
{
  this->active = false;
  this->x = 0;
  this->y = 0;
  this->type = 0;
  this->destination = 0;
  this->motion = 0;
  this->distance = 0;
}
