#include "Level.h"

#include <Arduboy2.h>
#include "Globals.h"

void Level::resetPortals()
{
  for (int i = 0; i<8 ; i++){
    this->portals[i].resetPortal();
  }
  
}

void Level::loadLevel()
{
  
}
