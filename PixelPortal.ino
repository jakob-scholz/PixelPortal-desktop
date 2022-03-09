#include <Arduboy2.h>
#include <Sprites.h>

#include "Globals.h"

// List of portals
// x, y, type, dest, motion, distance
uint8_t portals[8][6] = { 
  { 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0 } 
};

int wave = 0;
uint8_t dest = 0;

uint8_t finalState = 12;

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
      loadMap(1);
      arduboy.clear();
    }
  }
  
  if(gameState==GameState::Game){
    arduboy.clear();
    drawMap(level.currentLevel);
    player.update();
    player.currentPortal = inPortal();
    //showValue(player.currentPortal);
    level.portalCoolDown = constrain(level.portalCoolDown-1, 0, 10);
    if(player.currentPortal>-1){
      if(!level.portalCoolDown){
        dest = portals[player.currentPortal][3];
        player.vx = 1.1*player.vx;
        if(portals[ dest ][2]==1){//NORMAL
          player.x = portals[ dest ][0] + portals[ player.currentPortal ][0]-player.x;
          player.y = portals[ dest ][1] + portals[ player.currentPortal ][1]-player.y;
          player.vy = 1*player.oldvy;
        }
        if(portals[ dest ][2]==2){//INVIERTE VERTICAL
          player.x = portals[ dest ][0];
          player.y = portals[ dest ][1];
          player.vy = -1*player.oldvy;
        }
        if(portals[ dest ][2]==6){//MOVIL HORIZONTAL
          player.x = portals[ dest ][0] + portals[ player.currentPortal ][0]-player.x;
          player.y = portals[ dest ][1] + portals[ player.currentPortal ][1]-player.y;
          player.vy = 1*player.oldvy;
        }
        level.portalCoolDown = 10;
        
      }
    }
    
    if(inKey()){
      level.keyTaken=true;
    }
    if(inDoor()){
      arduboy.clear();
      resetPortals();
      level.currentLevel+=1;
      loadMap(level.currentLevel);
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

int inPortal(){
  uint8_t m = 2;
  for(uint8_t i=0; i<8;i++){
    if(portals[i][2]>0){
      if(player.x>=portals[i][0]-2-m and player.x<=portals[i][0]+m+2 and player.y>=portals[i][1]-2-m and player.y<=portals[i][1]+m+2){
        return i;
      }
    }
  }
  return -1;
}

bool inKey(){
  uint8_t m = 2;
  if(level.keyTaken==false){
    if(player.x>=level.key[0]-m and player.x<=level.key[0]+3+m and player.y>=level.key[1]-m and player.y<=level.key[1]+m+6){
      return true;
    }
  }
  return false;
}


bool inDoor(){
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

void loadMap(int map){
  if(map==1){
    player.x=5;
    player.y=50;
    level.key[0] = 50;
    level.key[1] = 56;
    level.door[0] = 100;
    level.door[1] = 22;
    //Portal info
    portals[0][0]=110;//x
    portals[0][1]=55;//y
    portals[0][2]=1;//type
    portals[0][3]=1;//destination
    portals[1][0]=10;
    portals[1][1]=25;
    portals[1][2]=1;
    portals[1][3]=0;
    
  }
  if(map==2){
    player.x=20;
    player.y=50;
    level.key[0] = 100;
    level.key[1] = 22;
    level.door[0] = 5;
    level.door[1] = 56;
    portals[0][0]=110;
    portals[0][1]=55;
    portals[0][2]=1;//type
    portals[0][3]=1;//destination
    portals[1][0]=10;
    portals[1][1]=25;
    portals[1][2]=1;
    portals[1][3]=0;
  }
  if(map==3){
    player.x=5;
    player.y=15;
    level.door[0] = 106;
    level.door[1] = 22;
    level.key[0] = 49;
    level.key[1] = 30-7;
    portals[0][0]=80;
    portals[0][1]=55;
    portals[0][2]=1;//type
    portals[0][3]=1;//destination
    portals[1][0]=80;
    portals[1][1]=20;
    portals[1][2]=1;
    portals[1][3]=0;
  }

  if(map==4){
    player.x=5;
    player.y=15;
    level.key[0] = 50;
    level.key[1] = 26;
    level.door[0] = 100;
    level.door[1] = 55;
    portals[0][0]=50;
    portals[0][1]=15;
    portals[0][2]=1;//type
    portals[0][3]=1;//destination
    portals[1][0]=50;
    portals[1][1]=55;
    portals[1][2]=1;
    portals[1][3]=0;
  }
  
  if(map==5){
    player.x=5;
    player.y=55;
    level.key[0] = 5;
    level.key[1] = 15;
    level.door[0] = 115;
    level.door[1] = 15;
    portals[0][0]=90;
    portals[0][1]=15;
    portals[0][2]=1;//type
    portals[0][3]=1;//destination
    portals[1][0]=20;
    portals[1][1]=5;
    portals[1][2]=1;
    portals[1][3]=0;
  }
  
  if(map==6){
    player.x=5;
    player.y=55;
    level.key[0] = 74;
    level.key[1] = 20;
    level.door[0] = 115;
    level.door[1] = 55;
    portals[0][0]=74;
    portals[0][1]=45;
    portals[0][2]=1;//type
    portals[0][3]=1;//destination
    portals[1][0]=10;
    portals[1][1]=12;
    portals[1][2]=1;
    portals[1][3]=0;
    
    portals[0][0]=74;
    portals[0][1]=45;
    portals[1][0]=10;
    portals[1][1]=12;
  }
  if(map==7){
    player.x=5;
    player.y=15;
    level.key[0] = 74;
    level.key[1] = 2;
    level.door[0] = 115;
    level.door[1] = 55;
    portals[0][0]=10;
    portals[0][1]=10;
    portals[0][2]=1;//type
    portals[0][3]=1;//destination
    portals[1][0]=10;
    portals[1][1]=55;
    portals[1][2]=1;
    portals[1][3]=0;
    
    portals[2][0]=40;
    portals[2][1]=55;
    portals[2][2]=2;//type
    portals[2][3]=3;//destination
    portals[3][0]=74;
    portals[3][1]=55;
    portals[3][2]=2;
    portals[3][3]=2;
  }
  if(map==8){
    player.x=10;
    player.y=20;
    level.key[0] = 74;
    level.key[1] = 2;
    level.door[0] = 115;
    level.door[1] = 55;
    portals[0][0]=10;
    portals[0][1]=10;
    portals[0][2]=1;//type
    portals[0][3]=1;//destination
    portals[1][0]=10;
    portals[1][1]=55;
    portals[1][2]=1;
    portals[1][3]=0;
    
    portals[2][0]=30;
    portals[2][1]=55;
    portals[2][2]=2;//type
    portals[2][3]=3;//destination
    portals[3][0]=74;
    portals[3][1]=55;
    portals[3][2]=2;
    portals[3][3]=2;
  }
  if(map==9){
    player.x=10;
    player.y=20;
    level.key[0] = 85;
    level.key[1] = 2;
    level.door[0] = 115;
    level.door[1] = 55;
    portals[0][0]=10;
    portals[0][1]=10;
    portals[0][2]=1;//type
    portals[0][3]=1;//destination
    portals[1][0]=10;
    portals[1][1]=55;
    portals[1][2]=1;
    portals[1][3]=0;
    
    portals[2][0]=25;
    portals[2][1]=55;
    portals[2][2]=2;//type
    portals[2][3]=4;//destination
    portals[3][0]=45;
    portals[3][1]=55;
    portals[3][2]=2;
    portals[3][3]=5;
    portals[4][0]=65;
    portals[4][1]=55;
    portals[4][2]=2;
    portals[4][3]=6;
    portals[5][0]=85;
    portals[5][1]=55;
    portals[5][2]=2;
    portals[5][3]=2;
    portals[6][0]=105;
    portals[6][1]=55;
    portals[6][2]=2;
    portals[6][3]=3;
  }
  if(map==10){
    player.x=124;
    player.y=55;
    level.key[0] = 50;
    level.key[1] = 56;
    level.door[0] = 100;
    level.door[1] = 22;
    //Portal info
    portals[0][0]=65;//x
    portals[0][1]=5;//y
    portals[0][2]=1;//type
    portals[0][3]=1;//destination
    portals[0][4]=1;//motion
    portals[0][5]=20;//distance
    portals[1][0]=10;
    portals[1][1]=55;
    portals[1][2]=1;
    portals[1][3]=0;
    
  }
  if(map==11){
    player.x=124;
    player.y=55;
    level.key[0] = 85;
    level.key[1] = 22;
    level.door[0] = 10;
    level.door[1] = 22;
    //Portal info
    portals[0][0]=75;//x
    portals[0][1]=5;//y
    portals[0][2]=1;//type
    portals[0][3]=1;//destination
    portals[0][4]=1;//motion
    portals[0][5]=20;//distance
    portals[1][0]=10;
    portals[1][1]=55;
    portals[1][2]=1;
    portals[1][3]=0;
    portals[2][0]=5;//x
    portals[2][1]=5;//y
    portals[2][2]=1;//type
    portals[2][3]=3;//destination
    portals[2][4]=1;//motion
    portals[2][5]=20;//distance
    portals[3][0]=100;
    portals[3][1]=55;
    portals[3][2]=1;
    portals[3][3]=2;
    
  }
}

void drawMap(int map){
    
    drawElements();
    
    //Borders
    arduboy.drawRect (0, 0, 128, 64, WHITE);
  
  if(map==1){
    //Walls
    arduboy.fillRect (0, 30, 128, 2, WHITE);
  }
  
  if(map==2){
    //Walls
    arduboy.fillRect (0, 30, 128, 2, WHITE);
  }
  
  if(map==3){
    
    //Walls
    arduboy.fillRect (104, 30, 12, 3, WHITE);
    arduboy.fillRect (44, 30, 12, 3, WHITE);
    
  }

  if(map==4){
    //Walls
    //arduboy.fillRect (104, 30, 12, 3, WHITE);
  }
  
  if(map==5){
    //Walls
    arduboy.fillRect (105, 30, 12, 3, WHITE);
    arduboy.fillRect (115, 45, 12, 3, WHITE);
    arduboy.fillRect (95, 55, 12, 3, WHITE);
  }
  
  if(map==6){
    //Walls
    arduboy.fillRect (0, 20, 20, 3, WHITE);
    arduboy.fillRect (20, 0, 3, 20, WHITE);
  }
  if(map==7){
    //Walls
    arduboy.fillRect (0, 20, 25, 3, WHITE);
  }
  if(map==8){
    //Walls
  }
  if(map==9){
    //Walls
    arduboy.fillRect (0, 20, 20, 3, WHITE);
  }
  if(map==10){
    //Walls
  }
  if(map==11){
    //Walls
    arduboy.fillRect (64, 0, 3, 64, WHITE);
  }
}

void drawElements(){
    //Portals
    for(int i = 0; i<8;i++){
      if(portals[i][4]==1){
        wave=(wave+1)%120;
        if(wave<60){
          portals[i][0]+=1;
        }else{
          portals[i][0]-=1;
        }
      }
      if(portals[i][2]==1){
        arduboy.drawRect(portals[i][0]-2, portals[i][1]-2, 4,4, WHITE);
      }
      if(portals[i][2]==2){
        arduboy.drawRect(portals[i][0]-2, portals[i][1]-2, 4,4, WHITE);
        arduboy.fillRect(portals[i][0]-1, portals[i][1]-2, 2,4, BLACK);
      }
    }
  
    //door
    arduboy.drawRect(level.door[0], level.door[1], 7,9, WHITE);
    if(!level.keyTaken){
    arduboy.fillRect(level.door[0], level.door[1], 7,9, WHITE);
    arduboy.drawLine(level.door[0]+3, level.door[1]+3,level.door[0]+5,level.door[1]+3, BLACK);
    }
    //key
    if(!level.keyTaken){
    arduboy.drawRect(level.key[0], level.key[1]+3, 3,3, WHITE);
    arduboy.drawLine(level.key[0]+1, level.key[1], level.key[0]+1, level.key[1]+3, WHITE);
    arduboy.drawLine(level.key[0], level.key[1], level.key[0]+1, level.key[1], WHITE);
    }
    
}

void resetPortals(){
  for (int i = 0; i<8 ; i++){
    for (int j=0; j<6;j++){
      portals[i][j]=0;
    }
  }
}
