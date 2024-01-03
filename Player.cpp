#include "Player.h"
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Level.h"
#include "Wall.h"

sf::RectangleShape rectangle0(sf::Vector2f(0.f, 0.f));

float constrain(float x, int lo, int hi){
    if (x < lo){
        return lo;
    }
    if (x > hi){
        return hi;
    }
    return x;
}
void Player::update(sf::RenderWindow* window){
  
    this->oldvy=this->vy;
	rectangle0.setSize(sf::Vector2f(1.f, 1.f));
	rectangle0.setPosition(this->x,this->y);
 	window->draw(rectangle0);
    this->move(window);

	rectangle0.setSize(sf::Vector2f(1.f, 1.f));
	rectangle0.setPosition(this->x,this->y);
 	window->draw(rectangle0);
    this->portalCoolDown = constrain(this->portalCoolDown-1, 0, 10);

  //If enter a portal
  if(this->currentPortal > -1){
    if(this->portalCoolDown==0){
      uint8_t dest = level.portals[this->currentPortal].destination;
      this->jumpPortals(dest);
    }
  }

  //If touching the key
  if(this->touchingKey()){
    level.keyTaken=true;
  }
}
void Player::processInputs(){
  
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
      this->vx -= this->ax;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
      this->vx += this->ax;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->onFloor){
      this->vy = this->jump;
      this->jumpCounter=1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
      this->jumpCounter++;
    }else{
      this->jumpCounter=0;
    }
    this->vx = constrain(this->vx*0.6, -this->vmax, this->vmax);
    if(this->vx < 0.2 and this->vx > -0.2){
      this->vx=0;
    }
    this->vy = constrain(this->vy, -5, 5);
}

void Player::move(sf::RenderWindow* window){

    this->tryMoveX(this->vx);
    this->tryMoveY(this->vy);

    this->currentPortal = this->inPortal();



    // floor detection
    //
    // false if not atleast on on wall or the border
/*
    this->onFloor=false;
    for (int i = 0; i <= 12; i++){
        if ((this->x > level.walls[i].x && this->x < level.walls[i].x + level.walls[i].w) && ((this->y +2 > level.walls[i].y) && (this->y +1 < level.walls[i].y + level.walls[i].h))){ // poition between wallstart and wallstart + width
            this->onFloor=true;
            this->vy = constrain(this->vy, 0, 15);
        }
        if (level.border){
            this->x = constrain(this->x, 1, 127);
            if (this->y > 62){
                this->onFloor = true;
                this->y = 62;
                this->vy = constrain(this->vy, 0, 15);
            }
        }
    }
*/   
    if(!this->onFloor){
        if(this->vy > -0.5 and this->vy < 0.5){         //if Y velocity between -0.5 and 0.5 then yv is 0.5
            this->vy = 0.5;
        }
        if(this->jumpCounter > 1 and this->jumpCounter < 16){
            this->vy = this->vy + this-> g * 0.2;
        }
        else {
            this->vy = this->vy + this-> g;
        }
    }
    if(this->y > 64){                   
         this->jumpPortals(0);
    }
}

bool Player::testBorder(){      // returns true if border is in y or x
    if (level.border){
        if (this->y > 62 || this->y < 1){
            return true;
        }
        if (this->x > 126 || this->y < 1){
            return true;
        return false;
        }
    }
    return false;
}
bool Player::testDestination(int i){        //returns true if x or y is in wall
    return (this->x > level.walls[i].x && this->x < level.walls[i].x + level.walls[i].w
            && this->y > level.walls[i].y && this->y < level.walls[i].y + level.walls[i].h);

}

void Player::tryMoveX(int dist){
    this->currentPortal = this->inPortal();
    while(dist!=0){
        if(dist>0){
            this->x = this->x + 1;
            for (int i = 0; i <= 12; i++){
	            if (this->testDestination(i)|| this->testBorder()){
                    this->x=this->x-1;
                    this->vx=0;             
                    break;
                }
            }
            dist-=1;
        }
        if(dist<0){
            this->x = this->x - 1;
            for (int i = 0; i <= 12; i++){
	            if (this->testDestination(i) || this->testBorder()){
                    this->x=this->x+1;
                    this->vx=0;             
                    break;
                }
            }
            dist+=1;
        } 
    }
}

void Player::tryMoveY(int dist){
    while(dist!=0){
        if(dist>0){
            this->y = this->y + 1;
            this->onFloor = false;
            for (int i = 0; i <= 12; i++){
                if (this->testDestination(i) || this->testBorder()){
                    this->y=this->y-1;
                    this->onFloor = true;
                    if(this->currentPortal==-1){
                        this->vy=0;
                    }
                    break;
                }
            }
            dist-=1;
        }
        if(dist<0){
            this->y = this->y - 1;
            this->onFloor = false;
            for (int i = 0; i <= 12; i++){
                if (this->testDestination(i) || this->testBorder()){
                    this->y=this->y+1;
                    if(this->currentPortal==-1){
                        this->vy=0;
                    }
                    break;
                }
            }
            dist+=1;
        }
    }
}

void Player::jumpPortals(uint8_t dest){
  //int dest = level.portals[this->currentPortal].destination;
  this->vx = 1.1*this->vx;
  if(level.portals[ dest ].type==PortalType::Normal){
    this->x = level.portals[ dest ].x;// + level.portals[ this->currentPortal ].x-this->x;
    this->y = level.portals[ dest ].y;// + level.portals[ this->currentPortal ].y-this->y;
    this->vy = 1*this->oldvy;
  }
  if(level.portals[ dest ].type==PortalType::InvertV){
    this->x = level.portals[ dest ].x;//-(level.portals[ this->currentPortal ].x-this->x);
    this->y = level.portals[ dest ].y;//-(level.portals[ this->currentPortal ].y-this->y);
    this->vy = -1*this->oldvy;
  }
  this->portalCoolDown = 10;   
}


int Player::inPortal(){
  uint8_t m = 2;
  for(uint8_t i=0; i<12;i++){
    if(level.portals[i].type!=PortalType::Inactive){
      if(this->x >= level.portals[i].x -m and this->x <= level.portals[i].x +m and this->y >= level.portals[i].y -m and this->y <= level.portals[i].y +m){
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
