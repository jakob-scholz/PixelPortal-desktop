#include "Player.h"

#include <Arduboy2.h>
#include "Globals.h"

void Player::update(){
  
  this->oldvy=this->vy;
  arduboy.drawPixel(this->x,this->y,0);
  this->move();
  arduboy.drawPixel(this->x,this->y,1);
  this->portalCoolDown = constrain(this->portalCoolDown-1, 0, 10);

  //If enter a portal
  if(this->currentPortal>-1){
    if(this->portalCoolDown==0){
      this->jumpPortals();
    }
  }

  //If touching the key
  if(this->touchingKey()){
    level.keyTaken=true;
  }
}
void Player::processInputs(){
  
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
void Player::move(){
  
  this->tryMoveX(this->vx);
  this->tryMoveY(this->vy);
  
  this->currentPortal = this->inPortal();
  
  if(arduboy.getPixel(this->x,this->y+1)==WHITE and this->currentPortal==-1){
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
  int dest = level.portals[this->currentPortal]->destination;
  this->vx = 1.1*this->vx;
  if(level.portals[ dest ]->type==PortalType::Normal){
    this->x = level.portals[ dest ]->x + level.portals[ this->currentPortal ]->x-this->x;
    this->y = level.portals[ dest ]->y + level.portals[ this->currentPortal ]->y-this->y;
    this->vy = 1*this->oldvy;
  }
  if(level.portals[ dest ]->type==PortalType::InvertV){
    this->x = level.portals[ dest ]->x-(level.portals[ this->currentPortal ]->x-this->x);
    this->y = level.portals[ dest ]->y-(level.portals[ this->currentPortal ]->y-this->y);
    this->vy = -1*this->oldvy;
  }
  this->portalCoolDown = 10;   
}


int Player::inPortal(){
  uint8_t m = 2;
  for(uint8_t i=0; i<12;i++){
    if(level.portals[i]->type!=PortalType::Inactive){
      if(this->x>=level.portals[i]->x-2-m and this->x<=level.portals[i]->x+m+2 and this->y>=level.portals[i]->y-2-m and this->y<=level.portals[i]->y+m+2){
        return i;
      }
    }
  }
  return -1;
}


bool Player::touchingKey(){
  uint8_t m = 2;
  if(level.keyTaken==false){
    if(this->x>=level.key[0]-m and this->x<=level.key[0]+3+m and this->y>=level.key[1]-m and this->y<=level.key[1]+m+6){
      return true;
    }
  }
  return false;
}

bool Player::touchingDoor(){
  uint8_t m = 2;
  if(level.keyTaken==true){
    if(this->x>=level.door[0]-m and this->x<=level.door[0]+7+m and this->y>=level.door[1]-m and this->y<=level.door[1]+m+8){
      return true;
    }
  }
  return false;
}
