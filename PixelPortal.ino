#include <Arduboy2.h>
#include <Sprites.h>

#include "Globals.h"

uint8_t dest = 0;

void setup()
{
  arduboy.begin();
  arduboy.setFrameRate(fps);
  arduboy.clear();
  
}
void loop()
{
  if (!(arduboy.nextFrame())){
    return;
  }
  
  arduboy.pollButtons();
  
  if (gameState==GameState::MainMenu){
    titleScreen();
    if(arduboy.justPressed(A_BUTTON) or arduboy.justPressed(UP_BUTTON)){
      gameState=GameState::Game;
      level.loadLevel();
      arduboy.clear();
    }
  }
  
  if(gameState==GameState::Game){
    arduboy.clear();
    level.drawLevel();
    player.update();
    level.portalCoolDown = constrain(level.portalCoolDown-1, 0, 10);

    //If enter a portal
    if(player.currentPortal>-1){
      if(!level.portalCoolDown){
        player.jumpPortals();
      }
    }

    //If touching the key
    if(touchingKey()){
      level.keyTaken=true;
    }

    //
    if(touchingDoor()){
      arduboy.clear();
      level.resetPortals();
      level.currentLevel+=1;
      level.loadLevel();
      level.keyTaken=false;
      level.openDoor = false;
      arduboy.setCursor(30,30);
      arduboy.println("LEVEL CLEARED");
      arduboy.display();
      arduboy.delayShort(3000);
      if(level.currentLevel==LASTLEVEL){
        arduboy.clear();
        arduboy.setCursor(33,30);
        arduboy.println("THE END");
        arduboy.display();
        arduboy.delayShort(3000);
        gameState=GameState::MainMenu;
      }
    }
    player.processInputs();
  }
  arduboy.display();
}


void showValue(float x){
  arduboy.setCursor(1,1);
  arduboy.setTextSize(1);
  arduboy.print("          ");
  arduboy.setCursor(1,1);
  arduboy.print(x);
}


bool touchingKey(){
  uint8_t m = 2;
  if(level.keyTaken==false){
    if(player.x>=level.key[0]-m and player.x<=level.key[0]+3+m and player.y>=level.key[1]-m and player.y<=level.key[1]+m+6){
      return true;
    }
  }
  return false;
}


bool touchingDoor(){
  uint8_t m = 2;
  if(level.keyTaken==true){
    if(player.x>=level.door[0]-m and player.x<=level.door[0]+7+m and player.y>=level.door[1]-m and player.y<=level.door[1]+m+8){
      return true;
    }
  }
  return false;
}


void drawGameOver()
{
  arduboy.setCursor(37, 42);
  arduboy.print("Game Over");
  arduboy.display();
  arduboy.delayShort(4000);
}

boolean titleScreen()
{
  arduboy.clear();
  arduboy.setCursor(0,22);
  arduboy.setTextSize(2);
  arduboy.print("PiXelPoRtAl");
  arduboy.setTextSize(1);
  arduboy.setCursor(42, 45);
  arduboy.print("Press A");
  arduboy.display();
}
