#include "Player.h"

#include <Arduboy2.h>
#include "Globals.h"

void Player::processInputs()
{
    if(arduboy.pressed(LEFT_BUTTON)){
      this->vx -= this->ax;
    }
    if(arduboy.pressed(RIGHT_BUTTON)){
      this->vx += this->ax;
    }
    
    if(arduboy.justPressed(UP_BUTTON) and this->onFloor){
      this->vy = this->jump;
      this->jumpCounter=1;
    }
    if(arduboy.pressed(UP_BUTTON)){
      this->jumpCounter++;
    }else{
      this->jumpCounter=0;
    }
    this->vx = constrain(this->vx*0.6, -this->vmax, this->vmax);
    if(this->vx<0.2 and this->vx>-0.2){
      this->vx=0;
    }
}
void Player::update()
{
  player.oldvy=player.vy;
  arduboy.drawPixel(this->x,this->y,0);
  this->move();
  arduboy.drawPixel(this->x,this->y,1);

}
void Player::move()
{
  this->tryMoveX(player.vx);
  this->tryMoveY(player.vy);
  
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
    if(player.jumpCounter>1 and player.jumpCounter<16){
      player.vy = player.vy+player.g*0.2;
      //arduboy.print(player.vy);
    }else{
      player.vy = player.vy+player.g;
    }
  }
}

void Player::tryMoveX(int dist){
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

void Player::tryMoveY(int dist){
  while(dist!=0){
    if(dist>0){
      player.y = player.y + 1;
      if(arduboy.getPixel(player.x,player.y)==WHITE){
        player.y=player.y-1;
        if(this->currentPortal==-1){
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
        if(this->currentPortal==-1){
          player.vy=0;
        }
        break;
      }
      dist+=1;
    }
  }
}
