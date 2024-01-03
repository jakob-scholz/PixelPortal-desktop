#include "Portal.h"
#include "Globals.h"

void Portal::resetPortal(){
  this->x = 0;
  this->y = 0;
  this->type = PortalType::Inactive;
  this->destination = 0;
  this->motion = 0;
  this->distance = 0;
  this->wave = 0;
}

void Portal::setPortal(uint8_t x, uint8_t y, PortalType type,uint8_t destination,uint8_t motion,uint8_t distance,uint8_t wave){
  this->x = x;
  this->y = y;
  this->type = type;
  this->destination = destination;
  this->motion = motion;
  this->distance = distance;
  this->wave = wave;
}
