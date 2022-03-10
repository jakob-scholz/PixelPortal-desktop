#include "level.h"

#include <Arduboy2.h>
#include "Globals.h"

void Level::resetLevel()
{
  for (int i = 0; i<8 ; i++){
      this->portals2[i] -> resetPortal();
  }
  level.keyTaken=false;
  level.openDoor = false;
}

void Level::loadLevel()
{
  uint8_t levelN = this->currentLevel;
  if(levelN==1){
    player.x=5;
    player.y=50;
    this->key[0] = 50;
    this->key[1] = 56;
    this->door[0] = 100;
    this->door[1] = 22;
    //Portal info
    this->portals2[0]->x=110;//x
    this->portals2[0]->y=55;//y
    this->portals2[0]->type=PortalType::Normal;//type
    this->portals2[0]->destination=1;//destination
    this->portals2[1]->x=10;
    this->portals2[1]->y=25;
    this->portals2[1]->type=PortalType::Normal;
    this->portals2[1]->destination=0;
    
  }
  if(levelN==2){
    player.x=20;
    player.y=50;
    this->key[0] = 100;
    this->key[1] = 22;
    this->door[0] = 5;
    this->door[1] = 56;
    this->portals2[0]->x=110;
    this->portals2[0]->y=55;
    this->portals2[0]->type=PortalType::Normal;//type
    this->portals2[0]->destination=1;//destination
    this->portals2[1]->x=10;
    this->portals2[1]->y=25;
    this->portals2[1]->type=PortalType::Normal;
    this->portals2[1]->destination=0;
  }
  if(levelN==3){
    player.x=5;
    player.y=15;
    this->door[0] = 106;
    this->door[1] = 22;
    this->key[0] = 49;
    this->key[1] = 30-7;
    this->portals2[0]->x=80;
    this->portals2[0]->y=55;
    this->portals2[0]->type=PortalType::Normal;//type
    this->portals2[0]->destination=1;//destination
    this->portals2[1]->x=80;
    this->portals2[1]->y=20;
    this->portals2[1]->type=PortalType::Normal;
    this->portals2[1]->destination=0;
  }

  if(levelN==4){
    player.x=5;
    player.y=15;
    this->key[0] = 50;
    this->key[1] = 26;
    this->door[0] = 100;
    this->door[1] = 55;
    this->portals2[0]->x=50;
    this->portals2[0]->y=15;
    this->portals2[0]->type=PortalType::Normal;//type
    this->portals2[0]->destination=1;//destination
    this->portals2[1]->x=50;
    this->portals2[1]->y=55;
    this->portals2[1]->type=PortalType::Normal;
    this->portals2[1]->destination=0;
  }
  
  if(levelN==5){
    player.x=5;
    player.y=55;
    this->key[0] = 5;
    this->key[1] = 15;
    this->door[0] = 115;
    this->door[1] = 15;
    this->portals2[0]->x=90;
    this->portals2[0]->y=15;
    this->portals2[0]->type=PortalType::Normal;//type
    this->portals2[0]->destination=1;//destination
    this->portals2[1]->x=20;
    this->portals2[1]->y=5;
    this->portals2[1]->type=PortalType::Normal;
    this->portals2[1]->destination=0;
  }
  
  if(levelN==6){
    player.x=5;
    player.y=55;
    this->key[0] = 74;
    this->key[1] = 20;
    this->door[0] = 115;
    this->door[1] = 55;
    this->portals2[0]->x=74;
    this->portals2[0]->y=45;
    this->portals2[0]->type=PortalType::Normal;//type
    this->portals2[0]->destination=1;//destination
    this->portals2[1]->x=10;
    this->portals2[1]->y=12;
    this->portals2[1]->type=PortalType::Normal;
    this->portals2[1]->destination=0;
    
    this->portals2[0]->x=74;
    this->portals2[0]->y=45;
    this->portals2[1]->x=10;
    this->portals2[1]->y=12;
  }
  if(levelN==7){
    player.x=5;
    player.y=15;
    this->key[0] = 74;
    this->key[1] = 2;
    this->door[0] = 115;
    this->door[1] = 55;
    this->portals2[0]->x=10;
    this->portals2[0]->y=10;
    this->portals2[0]->type=PortalType::Normal;//type
    this->portals2[0]->destination=1;//destination
    this->portals2[1]->x=10;
    this->portals2[1]->y=55;
    this->portals2[1]->type=PortalType::Normal;
    this->portals2[1]->destination=0;
    
    this->portals2[2]->x=40;
    this->portals2[2]->y=55;
    this->portals2[2]->type=PortalType::InvertV;//type
    this->portals2[2]->destination=3;//destination
    this->portals2[3]->x=74;
    this->portals2[3]->y=55;
    this->portals2[3]->type=PortalType::InvertV;
    this->portals2[3]->destination=2;
  }
  if(levelN==8){
    player.x=10;
    player.y=20;
    this->key[0] = 74;
    this->key[1] = 2;
    this->door[0] = 115;
    this->door[1] = 55;
    this->portals2[0]->x=10;
    this->portals2[0]->y=10;
    this->portals2[0]->type=PortalType::Normal;//type
    this->portals2[0]->destination=1;//destination
    this->portals2[1]->x=10;
    this->portals2[1]->y=55;
    this->portals2[1]->type=PortalType::Normal;
    this->portals2[1]->destination=0;
    
    this->portals2[2]->x=30;
    this->portals2[2]->y=55;
    this->portals2[2]->type=PortalType::InvertV;//type
    this->portals2[2]->destination=3;//destination
    this->portals2[3]->x=74;
    this->portals2[3]->y=55;
    this->portals2[3]->type=PortalType::InvertV;
    this->portals2[3]->destination=2;
  }
  if(levelN==9){
    player.x=17;
    player.y=5;
    this->key[0] = 85;
    this->key[1] = 2;
    this->door[0] = 115;
    this->door[1] = 55;
    this->portals2[0]->x=10;
    this->portals2[0]->y=10;
    this->portals2[0]->type=PortalType::Normal;//type
    this->portals2[0]->destination=1;//destination
    this->portals2[1]->x=10;
    this->portals2[1]->y=55;
    this->portals2[1]->type=PortalType::Normal;
    this->portals2[1]->destination=0;
    
    this->portals2[2]->x=25;
    this->portals2[2]->y=55;
    this->portals2[2]->type=PortalType::InvertV;//type
    this->portals2[2]->destination=4;//destination
    this->portals2[3]->x=45;
    this->portals2[3]->y=55;
    this->portals2[3]->type=PortalType::InvertV;
    this->portals2[3]->destination=5;
    this->portals2[4]->x=65;
    this->portals2[4]->y=55;
    this->portals2[4]->type=PortalType::InvertV;
    this->portals2[4]->destination=6;
    this->portals2[5]->x=85;
    this->portals2[5]->y=55;
    this->portals2[5]->type=PortalType::InvertV;
    this->portals2[5]->destination=2;
    this->portals2[6]->x=105;
    this->portals2[6]->y=55;
    this->portals2[6]->type=PortalType::InvertV;
    this->portals2[6]->destination=3;
  }
  if(levelN==10){
    player.x=124;
    player.y=55;
    this->key[0] = 50;
    this->key[1] = 56;
    this->door[0] = 100;
    this->door[1] = 22;
    //Portal info
    this->portals2[0]->x=65;//x
    this->portals2[0]->y=5;//y
    this->portals2[0]->type=PortalType::Normal;//type
    this->portals2[0]->destination=1;//destination
    this->portals2[0]->motion=1;//motion
    this->portals2[0]->distance=20;//distance
    this->portals2[1]->x=10;
    this->portals2[1]->y=55;
    this->portals2[1]->type=PortalType::Normal;
    this->portals2[1]->destination=0;
    
  }
  if(levelN==11){
    player.x=124;
    player.y=55;
    this->key[0] = 85;
    this->key[1] = 22;
    this->door[0] = 10;
    this->door[1] = 22;
    this->wave = 0;
    //Portal info
    this->portals2[0]->x=75;//x
    this->portals2[0]->y=5;//y
    this->portals2[0]->type=PortalType::Normal;//type
    this->portals2[0]->destination=1;//destination
    this->portals2[0]->motion=1;//motion
    this->portals2[0]->distance=20;//distance
    this->portals2[1]->x=10;
    this->portals2[1]->y=55;
    this->portals2[1]->type=PortalType::Normal;
    this->portals2[1]->destination=0;
    this->portals2[2]->x=5;//x
    this->portals2[2]->y=5;//y
    this->portals2[2]->type=PortalType::Normal;//type
    this->portals2[2]->destination=3;//destination
    this->portals2[2]->motion=1;//motion
    this->portals2[2]->distance=20;//distance
    this->portals2[3]->x=100;
    this->portals2[3]->y=55;
    this->portals2[3]->type=PortalType::Normal;
    this->portals2[3]->destination=2;
    
  }
}


void Level::drawElements(){
    for(int i = 0; i<8;i++){
      if(this->portals2[i]->motion==1){
        this->wave=(this->wave+1)%120;
        if(this->wave<60){
          this->portals2[i]->x+=1;
        }else{
          this->portals2[i]->x-=1;
        }
      }
      if(this->portals2[i]->type==PortalType::Normal){
        arduboy.drawRect(this->portals2[i]->x-2, this->portals2[i]->y-2, 4,4, WHITE);
      }
      if(this->portals2[i]->type==PortalType::InvertV){
        arduboy.drawRect(this->portals2[i]->x-2, this->portals2[i]->y-2, 4,4, WHITE);
        arduboy.fillRect(this->portals2[i]->x-1, this->portals2[i]->y-2, 2,4, BLACK);
      }
    }
  
    //door
    arduboy.drawRect(this->door[0], this->door[1], 7,9, WHITE);
    if(!this->keyTaken){
    arduboy.fillRect(this->door[0], this->door[1], 7,9, WHITE);
    arduboy.drawLine(this->door[0]+3, this->door[1]+3,this->door[0]+5,this->door[1]+3, BLACK);
    }
    //key
    if(!this->keyTaken){
    arduboy.drawRect(this->key[0], this->key[1]+3, 3,3, WHITE);
    arduboy.drawLine(this->key[0]+1, this->key[1], this->key[0]+1, this->key[1]+3, WHITE);
    arduboy.drawLine(this->key[0], this->key[1], this->key[0]+1, this->key[1], WHITE);
    }
    
}

void Level::drawLevel(){
  this->drawWalls();
  this->drawElements();
  
}

void Level::drawWalls(){
    
  //Screen Borders
  arduboy.drawRect (0, 0, 128, 64, WHITE);
    
  int levelN = level.currentLevel;
  if(levelN==1){
    //Walls
    arduboy.fillRect (0, 30, 128, 2, WHITE);
  }
  
  if(levelN==2){
    //Walls
    arduboy.fillRect (0, 30, 128, 2, WHITE);
  }
  
  if(levelN==3){
    
    //Walls
    arduboy.fillRect (104, 30, 12, 3, WHITE);
    arduboy.fillRect (44, 30, 12, 3, WHITE);
    
  }

  if(levelN==4){
    //Walls
    //arduboy.fillRect (104, 30, 12, 3, WHITE);
  }
  
  if(levelN==5){
    //Walls
    arduboy.fillRect (105, 30, 12, 3, WHITE);
    arduboy.fillRect (115, 45, 12, 3, WHITE);
    arduboy.fillRect (95, 55, 12, 3, WHITE);
  }
  
  if(levelN==6){
    //Walls
    arduboy.fillRect (0, 20, 20, 3, WHITE);
    arduboy.fillRect (20, 0, 3, 20, WHITE);
  }
  if(levelN==7){
    //Walls
    arduboy.fillRect (0, 20, 25, 3, WHITE);
  }
  if(levelN==8){
    //Walls
  }
  if(levelN==9){
    //Walls
    arduboy.fillRect (0, 20, 20, 3, WHITE);
  }
  if(levelN==10){
    //Walls
  }
  if(levelN==11){
    //Walls
    arduboy.fillRect (64, 0, 3, 64, WHITE);
  }
}
