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
  this->currentPortal = this->inPortal();
  this->oldvy=this->vy;
  arduboy.drawPixel(this->x,this->y,0);
  this->move();
  arduboy.drawPixel(this->x,this->y,1);

}
void Player::move()
{
  this->tryMoveX(this->vx);
  this->tryMoveY(this->vy);
  
  if(arduboy.getPixel(this->x,this->y+1)==WHITE){
    this->onFloor=true;
    this->vy=this->vy/2;
  }else{
    this->onFloor=false;
  }

  if(!this->onFloor){
    if(this->vy>-0.5 and this->vy<0.5){
      this->vy = 0.5;
    }
    if(this->jumpCounter>1 and this->jumpCounter<16){
      this->vy = this->vy+this->g*0.2;
      //arduboy.print(this->vy);
    }else{
      this->vy = this->vy+this->g;
    }
  }
}

void Player::tryMoveX(int dist){
  while(dist!=0){
    if(dist>0){
      this->x = this->x + 1;
      if(arduboy.getPixel(this->x,this->y)==WHITE){
        this->x=this->x-1;
        this->vx=0;
        break;
      }
      dist-=1;
    }
    if(dist<0){
      this->x = this->x - 1;
      if(arduboy.getPixel(this->x,this->y)==WHITE){
        this->x=this->x+1;
        this->vx=0;
        break;
      }
      dist+=1;
    }
  }
}

void Player::tryMoveY(int dist){
  while(dist!=0){
    if(dist>0){
      this->y = this->y + 1;
      if(arduboy.getPixel(this->x,this->y)==WHITE){
        this->y=this->y-1;
        if(this->currentPortal==-1){
          this->vy=0;
        }
        break;
      }
      dist-=1;
    }
    if(dist<0){
      this->y = this->y - 1;
      if(arduboy.getPixel(this->x,this->y)==WHITE){
        this->y=this->y+1;
        if(this->currentPortal==-1){
          this->vy=0;
        }
        break;
      }
      dist+=1;
    }
  }
}


void Player::jumpPortals(){
  int dest = level.portals2[this->currentPortal]->destination;
  this->vx = 1.1*this->vx;
  if(level.portals2[ dest ]->type==PortalType::Normal){
    this->x = level.portals2[ dest ]->x + level.portals2[ this->currentPortal ]->x-this->x;
    this->y = level.portals2[ dest ]->y + level.portals2[ this->currentPortal ]->y-this->y;
    this->vy = 1*this->oldvy;
  }
  if(level.portals2[ dest ]->type==PortalType::InvertV){
    this->x = level.portals2[ dest ]->x;
    this->y = level.portals2[ dest ]->y;
    this->vy = -1*this->oldvy;
  }
  level.portalCoolDown = 10;   
}


int Player::inPortal(){
  uint8_t m = 2;
  for(uint8_t i=0; i<8;i++){
    if(level.portals2[i]->type!=PortalType::Inactive){
      if(this->x>=level.portals2[i]->x-2-m and this->x<=level.portals2[i]->x+m+2 and this->y>=level.portals2[i]->y-2-m and this->y<=level.portals2[i]->y+m+2){
        return i;
      }
    }
  }
  return -1;
}
