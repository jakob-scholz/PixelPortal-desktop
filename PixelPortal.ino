#include <Arduboy2.h>
#include <Sprites.h>

#include "Globals.h"

uint8_t fps = 30;
uint8_t level = 1;
uint8_t finalLevel = 10;

//Cada portal una línea, con info de dirección y de destino.
// PARA RECORRERLOS: for (byte i = 0; i < sizeof(myStr) - 1; i++) {
uint8_t portals[8][6] = { { 0, 0, 1, 0,0,0 },
                      { 0, 0, 1, 0,0,0 },
                      { 0, 0, 0, 0,0,0 },
                      { 0, 0, 0, 0,0,0 },
                      { 0, 0, 0, 0,0,0 },
                      { 0, 0, 0, 0,0,0 },
                      { 0, 0, 0, 0,0,0 },
                      { 0, 0, 0, 0,0,0 } };

int wave = 0;
int portalActual = -1;
uint8_t portalCoolDown = 0;
uint8_t dest = 0;

uint8_t door[] = {0,0};
bool openDoor = false;

uint8_t key[] = { 0 , 0 };
bool keyTaken = false;

uint8_t jumpCounter=0;
uint8_t finalState = 12;

void setup()
{
  arduboy.begin();
  arduboy.setFrameRate(fps);
  arduboy.clear();
}

void loop()
{
  // pause render until it's time for the next frame
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
    drawMap(level);
    player.oldvy=player.vy;
    updateP();
    portalActual = inPortal();
    //showValue(portalActual);
    portalCoolDown = constrain(portalCoolDown-1, 0, 10);
    if(portalActual>-1){
      if(!portalCoolDown){
        dest = portals[portalActual][3];
        player.vx = 1.1*player.vx;
        if(portals[ dest ][2]==1){//NORMAL
          player.x = portals[ dest ][0] + portals[ portalActual ][0]-player.x;
          player.y = portals[ dest ][1] + portals[ portalActual ][1]-player.y;
          player.vy = 1*player.oldvy;
        }
        if(portals[ dest ][2]==2){//INVIERTE VERTICAL
          player.x = portals[ dest ][0];
          player.y = portals[ dest ][1];
          player.vy = -1*player.oldvy;
        }
        if(portals[ dest ][2]==6){//MOVIL HORIZONTAL
          player.x = portals[ dest ][0] + portals[ portalActual ][0]-player.x;
          player.y = portals[ dest ][1] + portals[ portalActual ][1]-player.y;
          player.vy = 1*player.oldvy;
        }
        portalCoolDown = 10;
        
      }
    }
    
    if(inKey()){
      keyTaken=true;
    }
    if(inDoor()){
      arduboy.clear();
      resetPortals();
      level+=1;
      loadMap(level);
      keyTaken=false;
      openDoor = false;
      arduboy.setCursor(30,30);
      arduboy.println("LEVEL CLEARED");
      arduboy.display();
      arduboy.delayShort(3000);
      if(level==finalLevel){
        arduboy.clear();
        arduboy.setCursor(33,30);
        arduboy.println("THE END");
        arduboy.display();
        arduboy.delayShort(3000);
        gameState=GameState::MainMenu;
      }
    }
    
    if(arduboy.pressed(LEFT_BUTTON)){
      player.vx -= player.ax;
    }
    if(arduboy.pressed(RIGHT_BUTTON)){
      player.vx += player.ax;
    }
    
    if(arduboy.justPressed(UP_BUTTON) and player.onFloor){
      player.vy = player.jump;
      jumpCounter=1;
    }
    if(arduboy.pressed(UP_BUTTON)){
      jumpCounter++;
    }else{
      jumpCounter=0;
    }
    player.vx = constrain(player.vx*0.6, -player.vmax, player.vmax);
    if(player.vx<0.2 and player.vx>-0.2){
      player.vx=0;
    }
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
  if(keyTaken==false){
    if(player.x>=key[0]-m and player.x<=key[0]+3+m and player.y>=key[1]-m and player.y<=key[1]+m+6){
      return true;
    }
  }
  return false;
}


bool inDoor(){
  uint8_t m = 2;
  if(keyTaken==true){
    if(player.x>=door[0]-m and player.x<=door[0]+7+m and player.y>=door[1]-m and player.y<=door[1]+m+8){
      return true;
    }
  }
  return false;
}

void tryMoveY(int dist){
  while(dist!=0){
    if(dist>0){
      player.y = player.y + 1;
      if(arduboy.getPixel(player.x,player.y)==WHITE){
        player.y=player.y-1;
        if(inPortal()==false){
          player.vy=0;
        }
        break;
      }
      dist-=1;
    }
    if(dist<0){
      player.y = player.y - 1;
      if(arduboy.getPixel(player.x,player.y)==WHITE){
        player.y=player.y+1;
        if(inPortal()==false){
          player.vy=0;
        }
        break;
      }
      dist+=1;
    }
  }
}

void tryMoveX(int dist){
  while(dist!=0){
    if(dist>0){
      player.x = player.x + 1;
      if(arduboy.getPixel(player.x,player.y)==WHITE){
        player.x=player.x-1;
        player.vx=0;
        break;
      }
      dist-=1;
    }
    if(dist<0){
      player.x = player.x - 1;
      if(arduboy.getPixel(player.x,player.y)==WHITE){
        player.x=player.x+1;
        player.vx=0;
        break;
      }
      dist+=1;
    }
  }
}

void moveP()
{
  
  tryMoveX(player.vx);
  tryMoveY(player.vy);
  
  if(arduboy.getPixel(player.x,player.y+1)==WHITE){
    player.onFloor=true;
    player.vy=player.vy/2;
  }else{
    player.onFloor=false;
  }

  if(!player.onFloor){
    if(player.vy>-0.5 and player.vy<0.5){
      player.vy = 0.5;
    }
    if(jumpCounter>1 and jumpCounter<16){
      player.vy = player.vy+player.g*0.2;
      //arduboy.print(player.vy);
    }else{
      player.vy = player.vy+player.g;
    }
  }

  
  
}

void updateP()
{
  arduboy.drawPixel(player.x,player.y,0);
  moveP();
  arduboy.drawPixel(player.x,player.y,1);
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
    key[0] = 50;
    key[1] = 56;
    door[0] = 100;
    door[1] = 22;
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
    key[0] = 100;
    key[1] = 22;
    door[0] = 5;
    door[1] = 56;
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
    door[0] = 106;
    door[1] = 22;
    key[0] = 49;
    key[1] = 30-7;
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
    key[0] = 50;
    key[1] = 26;
    door[0] = 100;
    door[1] = 55;
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
    key[0] = 5;
    key[1] = 15;
    door[0] = 115;
    door[1] = 15;
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
    key[0] = 74;
    key[1] = 20;
    door[0] = 115;
    door[1] = 55;
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
    key[0] = 74;
    key[1] = 2;
    door[0] = 115;
    door[1] = 55;
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
    key[0] = 74;
    key[1] = 2;
    door[0] = 115;
    door[1] = 55;
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
    key[0] = 85;
    key[1] = 2;
    door[0] = 115;
    door[1] = 55;
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
    key[0] = 50;
    key[1] = 56;
    door[0] = 100;
    door[1] = 22;
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
    key[0] = 85;
    key[1] = 22;
    door[0] = 10;
    door[1] = 22;
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
    arduboy.drawRect(door[0], door[1], 7,9, WHITE);
    if(!keyTaken){
    arduboy.fillRect(door[0], door[1], 7,9, WHITE);
    arduboy.drawLine(door[0]+3, door[1]+3,door[0]+5,door[1]+3, BLACK);
    }
    //key
    if(!keyTaken){
    arduboy.drawRect(key[0], key[1]+3, 3,3, WHITE);
    arduboy.drawLine(key[0]+1, key[1], key[0]+1, key[1]+3, WHITE);
    arduboy.drawLine(key[0], key[1], key[0]+1, key[1], WHITE);
    }
    
}

void resetPortals(){
  for (int i = 0; i<8 ; i++){
    for (int j=0; j<6;j++){
      portals[i][j]=0;
    }
  }
}
