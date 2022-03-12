#include <Arduboy2.h>
#include <Sprites.h>

#include "Globals.h"

uint8_t px = 5;
uint8_t py = 80;


void setup(){
  arduboy.begin();
  arduboy.setFrameRate(fps);
  arduboy.clear();
}
void loop(){
  if (!(arduboy.nextFrame())){
    return;
  }
  
  arduboy.pollButtons();
  
  if (gameState==GameState::MainMenu){
    titleScreen();
    if(arduboy.justPressed(A_BUTTON) or arduboy.justPressed(UP_BUTTON)){
      gameState=GameState::Game;
      level.currentLevel = 1;
      level.loadLevel();
      arduboy.clear();
    }
  }
  
  if(gameState==GameState::Game){
    arduboy.clear();
    level.drawLevel();
    player.update();

    if(player.touchingDoor()){
      gameState=GameState::NextLevel;
      if(level.currentLevel==LASTLEVEL){
        gameState=GameState::EndGame;
      }
    }
    player.processInputs();
  }
  if(gameState==GameState::NextLevel){
      nextLevelScreen();
      
      level.resetLevel();
      level.currentLevel+=1;
      level.loadLevel();
      
      gameState=GameState::Game;
  }
  if(gameState==GameState::EndGame){
      endGameScreen();
      
      level.resetLevel();
      level.currentLevel+=1;
      level.loadLevel();
      
      gameState=GameState::MainMenu;
  }
  arduboy.display();
}

boolean titleScreen(){
  arduboy.clear();
  arduboy.drawPixel (px, py, WHITE);
  px = px - 2;
  if(px<28 and py<30){
    px = 92;
    py = 58;
  }
  if(px<28 and py>30){
    px = 92;
    py = 4;
  }
  arduboy.drawRect (0, 0, 128, 64, WHITE);
  arduboy.drawRect (9, 9, 110, 46, WHITE);
  arduboy.drawRect (24, 3, 4, 4, WHITE);
  arduboy.drawRect (94, 3, 4, 4, WHITE);
  arduboy.drawRect (24, 57, 4, 4, WHITE);
  arduboy.drawRect (94, 57, 4, 4, WHITE);
  arduboy.setCursor(0,22);
  arduboy.setTextSize(2);
  arduboy.print("PiXelPoRtAl");
  arduboy.setTextSize(1);
  arduboy.setCursor(42, 45);
  arduboy.print("Press A");
  arduboy.display();
}

void nextLevelScreen(){
      arduboy.clear();
      arduboy.setCursor(30,30);
      arduboy.println("LEVEL CLEARED");
      arduboy.display();
      arduboy.delayShort(3000);
}

void endGameScreen(){
      arduboy.clear();
      arduboy.setCursor(33,30);
      arduboy.println("THE END");
      arduboy.display();
      arduboy.delayShort(3000);
}
