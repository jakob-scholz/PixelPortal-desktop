#include "Level.h"
#include "Globals.h"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::RectangleShape rectangle(sf::Vector2f(0.f, 0.f));

void Level::resetLevel()
{
  for (int i = 0; i<12 ; i++){
      this->portals[i].resetPortal();
  }
  for (int i = 0; i<12 ; i++){
    this->walls[i].resetWall();
  }
  level.keyTaken=false;
  level.openDoor = false;
}


void Level::drawLevel(sf::RenderWindow* window){
  this->drawWalls(window);
  this->drawElements(window);
}

void Level::drawElements(sf::RenderWindow* window){
    for(int i = 0; i<12;i++){
      if(this->portals[i].motion==1){
        this->portals[i].wave=(this->portals[i].wave+1)%(2*this->portals[i].distance);
        if(this->portals[i].wave<this->portals[i].distance){
          this->portals[i].x+=1;
        }else{
          this->portals[i].x-=1;
        }
        
      }
      if(this->portals[i].type==PortalType::Normal){
   //     arduboy.drawRect(this->portals[i].x-2, this->portals[i].y-2, 4,4, WHITE);

        rectangle.setFillColor(sf::Color::White);
        rectangle.setSize(sf::Vector2f(4.f,4.f));
        rectangle.setPosition(this->portals[i].x-2, this->portals[i].y-2);
        window->draw(rectangle);

        rectangle.setFillColor(sf::Color::Black);
        rectangle.setSize(sf::Vector2f(2.f,2.f));
        rectangle.setPosition(this->portals[i].x-1, this->portals[i].y-1);
        window->draw(rectangle);

      }
      if(this->portals[i].type==PortalType::InvertV){
     //   arduboy.drawRect(this->portals[i].x-2, this->portals[i].y-2, 4,4, WHITE);
    //    arduboy.fillRect(this->portals[i].x-1, this->portals[i].y-2, 2,4, BLACK);

        rectangle.setFillColor(sf::Color::White);
        rectangle.setSize(sf::Vector2f(4.f,4.f));
        rectangle.setPosition(this->portals[i].x-2, this->portals[i].y-2);
        window->draw(rectangle);

        rectangle.setFillColor(sf::Color::Black);
        rectangle.setSize(sf::Vector2f(2.f,4.f));
        rectangle.setPosition(this->portals[i].x-2, this->portals[i].y-2);
        window->draw(rectangle);

      }
    }
  
    //door
 //   arduboy.drawRect(this->door[0], this->door[1], 7,9, WHITE);

    rectangle.setFillColor(sf::Color::White);
    rectangle.setSize(sf::Vector2f(9.f,7.f));
    rectangle.setPosition(this->door[0], this->door[1]);
    window->draw(rectangle);


    if(!this->keyTaken){
   // arduboy.fillRect(this->door[0], this->door[1], 7,9, WHITE);
  //  arduboy.drawLine(this->door[0]+3, this->door[1]+3,this->door[0]+5,this->door[1]+3, BLACK);

    rectangle.setFillColor(sf::Color::Black);
    rectangle.setSize(sf::Vector2f(3.f,1.f));
    rectangle.setPosition(this->door[0]+2, this->door[1]+3);
    window->draw(rectangle);
    }
    else{
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setSize(sf::Vector2f(7.f,5.f));
    rectangle.setPosition(this->door[0]+1, this->door[1]+1);
    window->draw(rectangle);

        }

    //key
    if(!this->keyTaken){
        rectangle.setFillColor(sf::Color::White);
        rectangle.setSize(sf::Vector2f(3,3));
        rectangle.setPosition(this->key[0], this->key[1]+3);
        window->draw(rectangle);
        rectangle.setFillColor(sf::Color::Black);
        rectangle.setSize(sf::Vector2f(1,1));
        rectangle.setPosition(this->key[0] + 1, this->key[1] + 4);
        window->draw(rectangle);

        rectangle.setFillColor(sf::Color::White);
        rectangle.setSize(sf::Vector2f(1,3));
        rectangle.setPosition(this->key[0] +1 , this->key[1]);
        window->draw(rectangle);

        rectangle.setFillColor(sf::Color::White);
        rectangle.setSize(sf::Vector2f(1,1));
        rectangle.setPosition(this->key[0] , this->key[1]);
        window->draw(rectangle);
    }
}

void Level::drawWalls(sf::RenderWindow* window){
  
  //Draw each wall
  for(int i = 0; i<12;i++){
   // arduboy.fillRect (this->walls[i].x, this->walls[i].y, this->walls[i].w, this->walls[i].h, WHITE);
    if (this->walls[i].h || this->walls[i].w){
        rectangle.setFillColor(sf::Color::White);
        rectangle.setSize(sf::Vector2f(this->walls[i].w, this->walls[i].h));
        rectangle.setPosition(this->walls[i].x, this->walls[i].y);
        window->draw(rectangle);
        std::cout << "drawWall " << (int)this->walls[i].w << " " << (int)this->walls[i].h << std::endl;
        std::cout << "at " << (int)this->walls[i].x << " " << (int)this->walls[i].y << std::endl;
    }
  }
    
  //Draw screen Borders
  if(this->border){
   // arduboy.drawRect (0, 0, 128, 64, WHITE);
    rectangle.setFillColor(sf::Color::White);
    rectangle.setSize(sf::Vector2f(128,64));
    rectangle.setPosition(0,0);
    window->draw(rectangle);

    rectangle.setFillColor(sf::Color::Black);
    rectangle.setSize(sf::Vector2f(126,62));
    rectangle.setPosition(1,1);
    window->draw(rectangle);



  }
}

void Level::loadLevel()
{
  if(this->currentLevel==1){
    /*
     * |--------------------------------
     * |                                |
     * |                                |
     * |  1                        E    |
     * |--------------------------------|
     * |                                |
     * |                                |
     * |  P           K            0    |
     * |--------------------------------
     */
    player.x=5;
    player.y=50;
    this->key[0] = 50;
    this->key[1] = 56;
    this->door[0] = 100;
    this->door[1] = 22;
    this->border = true;
    
    this->portals[0].setPortal(110,55,PortalType::Normal,1,0,0,0);
    this->portals[1].setPortal(10,25,PortalType::Normal,0,0,0,0);
    
    this->walls[0].setWall(0,30,128,2);
  }
  if(this->currentLevel==2){
    /*
     * |--------------------------------
     * |                                |
     * |                                |
     * |  1                        K   |
     * |--------------------------------|
     * |                                |
     * |                                |
     * |  E           P            0    |
     * |--------------------------------
     */
    player.x=50;
    player.y=50;
    this->key[0] = 100;
    this->key[1] = 22;
    this->door[0] = 5;
    this->door[1] = 56;
    this->border = true;
    
    this->portals[0].setPortal(110,55,PortalType::Normal,1,0,0,0);
    this->portals[1].setPortal(10,25,PortalType::Normal,0,0,0,0);
    
    this->walls[0].setWall(0, 30, 128, 2);
  }
  if(this->currentLevel==3){
    /*
     * |--------------------------------
     * |                                |
     * |  P                  1          |
     * |            K               E   |
     * |           ---             ---  |
     * |                                |
     * |                                |
     * |                     0          |
     * |--------------------------------
     */
    player.x=5;
    player.y=15;
    this->door[0] = 106;
    this->door[1] = 22;
    this->key[0] = 49;
    this->key[1] = 30-7;
    this->border = true;
    
    this->portals[0].setPortal(80,55,PortalType::Normal,1,0,0,0);
    this->portals[1].setPortal(80,20,PortalType::Normal,0,0,0,0);

    this->walls[0].setWall(104, 30, 12, 2);
    this->walls[1].setWall(44, 30, 12, 2);
  }

  if(this->currentLevel==4){
    /*
     * |--------------------------------
     * |                                |
     * |            1                   |
     * |            K                   |
     * |                                |
     * |                                |
     * |                                |
     * |   P        0               E   |
     * |--------------------------------
     */
    player.x=5;
    player.y=10;
    this->key[0] = 50;
    this->key[1] = 26;
    this->door[0] = 100;
    this->door[1] = 55;
    this->border = true;
    
    this->portals[0].setPortal(50,15,PortalType::Normal,1,0,0,0);
    this->portals[1].setPortal(50,55,PortalType::Normal,0,0,0,0);
  }
  if(this->currentLevel==5){
    /*
     * |--------------------------------
     * |     1                          |
     * |  K                 0           |
     * |                             E  |
     * |                                |
     * |                     ---        |
     * |               ---              |
     * |          ---                   |
     * |--------------------------------
     */
    player.x=30;
    player.y=10;
    this->key[0] = 5;
    this->key[1] = 25;
    this->door[0] = 115;
    this->door[1] = 15;
    this->border = true;
    
    this->portals[0].setPortal(95,15,PortalType::Normal,1,0,0,0);
    this->portals[1].setPortal(20,15,PortalType::Normal,0,0,0,0);

    this->walls[0].setWall(100, 35, 12, 2);
    this->walls[1].setWall(75, 45, 12, 2);
    this->walls[2].setWall(50, 55, 12, 2);
  }
  
  if(this->currentLevel==6){
    /*
     * |--------------------------------
     * |     |                          |
     * |  1  |                          |
     * |-----             K             |
     * |                                |
     * |                  0             |
     * |                                |
     * |  P                         E   |
     * |--------------------------------
     */
    player.x=5;
    player.y=55;
    this->key[0] = 74;
    this->key[1] = 20;
    this->door[0] = 115;
    this->door[1] = 55;
    this->border = true;
    
    this->portals[0].setPortal(74,45,PortalType::Normal,1,0,0,0);
    this->portals[1].setPortal(10,12,PortalType::Normal,0,0,0,0);
    
    this->walls[0].setWall(0, 20, 20, 2);
    this->walls[1].setWall(20, 0, 2, 20);
  }
  if(this->currentLevel==7){
    /*
     * |--------------------------------
     * | 1                  K           |
     * |-----                           |
     * |                                |
     * |                                |
     * |                                |
     * |                                |
     * | 0  P    2          3        E  |
     * |--------------------------------
     */
    player.x=5;
    player.y=15;
    this->key[0] = 74;
    this->key[1] = 2;
    this->door[0] = 115;
    this->door[1] = 55;
    this->border = true;
    
    this->portals[0].setPortal(10,10,PortalType::Normal,1,0,0,0);
    this->portals[1].setPortal(10,55,PortalType::Normal,0,0,0,0);
    this->portals[2].setPortal(40,55,PortalType::InvertV,3,0,0,0);
    this->portals[3].setPortal(74,55,PortalType::InvertV,2,0,0,0);
    
    this->walls[1].setWall(0, 20, 25, 2);
  }
  if(this->currentLevel==8){
    /*
     * |--------------------------------
     * |   1                K           |
     * |                                |
     * |                                |
     * |   P                            |
     * |                                |
     * |                                |
     * |   0     2          3       E   |
     * |--------------------------------
     */
    player.x=10;
    player.y=20;
    this->key[0] = 74;
    this->key[1] = 2;
    this->door[0] = 115;
    this->door[1] = 55;
    this->border = true;
    
    this->portals[0].setPortal(10,10,PortalType::Normal,1,0,0,0);
    this->portals[1].setPortal(10,55,PortalType::Normal,0,0,0,0);
    this->portals[2].setPortal(30,55,PortalType::InvertV,3,0,0,0);
    this->portals[3].setPortal(74,55,PortalType::InvertV,2,0,0,0);
  }
  if(this->currentLevel==9){
    /*
     * |--------------------------------
     * | 1                K             |
     * |-----                           |
     * |                                |
     * |                                |
     * |                                |
     * |                                |
     * | 0    2   3   4   5   6     E   |
     * |--------------------------------
     */
    player.x=17;
    player.y=5;
    this->key[0] = 85;
    this->key[1] = 2;
    this->door[0] = 115;
    this->door[1] = 55;
    this->border = true;
    
    this->portals[0].setPortal(10,10,PortalType::Normal,1,0,0,0);
    this->portals[1].setPortal(10,55,PortalType::Normal,0,0,0,0);
    this->portals[2].setPortal(25,55,PortalType::InvertV,4,0,0,0);
    this->portals[3].setPortal(45,55,PortalType::InvertV,5,0,0,0);
    this->portals[4].setPortal(65,55,PortalType::InvertV,6,0,0,0);
    this->portals[5].setPortal(85,55,PortalType::InvertV,2,0,0,0);
    this->portals[6].setPortal(105,55,PortalType::InvertV,3,0,0,0);

    this->walls[1].setWall(0, 20, 20, 2);
  }
  if(this->currentLevel==10){
    /*
     * |--------------------------------
     * |               [  ~   1  ~   ]  |
     * |                                |
     * |                          E     |
     * |                                |
     * |                                |
     * |                                |
     * | 0        K                  P  |
     * |--------------------------------
     */
    player.x=124;
    player.y=55;
    this->key[0] = 50;
    this->key[1] = 56;
    this->door[0] = 100;
    this->door[1] = 22;
    this->border = true;

    this->portals[0].setPortal(65,5,PortalType::Normal,1,1,20,0);
    this->portals[1].setPortal(10,55,PortalType::Normal,0,0,0,0);    
    
  }
  if(this->currentLevel==11){
    /*
     * |--------------------------------
     * | [  ~   1  ~   ]| [  ~   3  ~  ]|
     * |                |               |
     * |   E            |               |
     * |                |               |
     * |                |               |
     * |                |               |
     * |   2            |       0       |
     * |--------------------------------
     */
    player.x=124;
    player.y=55;
    this->key[0] = 85;
    this->key[1] = 22;
    this->door[0] = 10;
    this->door[1] = 22;
    this->border = true;

    this->portals[0].setPortal(115,5,PortalType::Normal,1,1,40,40);
    this->portals[1].setPortal(10,55,PortalType::Normal,0,0,0,0);
    this->portals[2].setPortal(15,5,PortalType::Normal,3,1,40,0);
    this->portals[3].setPortal(100,55,PortalType::Normal,2,0,0,0);

    this->walls[1].setWall(64, 0, 2, 64);
  }
  
  if(this->currentLevel==12){
    /*   10          55   75         110            
     * |--------------------------------
     * | 6              | 9             |15
     * |      7   8     |      10 11    |
     * |              E | K             |25
     * |--------------------------------|
     * | 0              | 3             |35
     * |      1   2     |      4  5     |
     * | P              |               |55
     * |--------------------------------
     */
    player.x=10;
    player.y=55;
    this->key[0] = 75;
    this->key[1] = 25;
    this->door[0] = 50;
    this->door[1] = 25;
    this->border = true;

    this->portals[0].setPortal(10,45,PortalType::InvertV,2,0,0,0);
    this->portals[1].setPortal(30,45,PortalType::InvertV,2,0,0,0);
    this->portals[2].setPortal(50,45,PortalType::InvertV,3,0,0,0);
    this->portals[3].setPortal(75,45,PortalType::InvertV,0,0,0,0);
    this->portals[4].setPortal(95,45,PortalType::InvertV,0,0,0,0);
    this->portals[5].setPortal(115,45,PortalType::InvertV,6,0,0,0);
    this->portals[6].setPortal(10,15,PortalType::InvertV,9,0,0,0);
    this->portals[7].setPortal(30,15,PortalType::InvertV,1,0,0,0);
    this->portals[8].setPortal(50,15,PortalType::InvertV,0,0,0,0);
    this->portals[9].setPortal(75,15,PortalType::InvertV,11,0,0,0);
    this->portals[10].setPortal(95,15,PortalType::InvertV,11,0,0,0);
    this->portals[11].setPortal(115,15,PortalType::InvertV,0,0,0,0);

    this->walls[0].setWall(64, 0, 2, 64);
    this->walls[1].setWall(0,32 , 128, 2);
  }
  
  if(this->currentLevel==13){
    /*
     * |--------------------------------
     * |K[  ~   2  ~   ]| [  ~   3  ~ ]E|
     * |                |               |
     * | [  ~   1  ~   ]|               |
     * |                |               |
     * | [  ~   0  ~   ]|               |
     * |                |               |
     * |   P            |       0       |
     * |--------------------------------
     */
    player.x=10;
    player.y=55;
    this->key[0] = 70;
    this->key[1] = 55;
    this->door[0] = 120;
    this->door[1] = 1;
    this->border = true;

    this->portals[0].setPortal(10,55,PortalType::Normal,1,1,40,0);
    this->portals[1].setPortal(25,30,PortalType::Normal,2,1,40,15);
    this->portals[2].setPortal(50,10,PortalType::Normal,3,1,40,40);
    this->portals[3].setPortal(120,50,PortalType::Normal,0,0,0,0);
    this->portals[4].setPortal(70,55,PortalType::Normal,5,1,40,0);
    this->portals[5].setPortal(95,30,PortalType::Normal,6,1,40,15);
    this->portals[6].setPortal(110,15,PortalType::Normal,7,1,40,40);
    this->portals[7].setPortal(110,3,PortalType::Normal,0,0,0,0);

    this->walls[1].setWall(64, 0, 2, 64);
  }
  if(this->currentLevel==14){
    player.x=16;
    player.y=35;
    this->key[0] = 48;
    this->key[1] = 5;
    this->door[0] = 120;
    this->door[1] = 3;
    this->border = true;
    /*
     * |--------------------------------
     * |   1        K                  E|
     * |        |       |       |       |
     * |        |       |       |       |
     * |        |       |       |       |
     * |        |       |       |       |
     * |        |       |       |       |
     * | 0 P  2 |3    4 |5     6|7     8|
     * |--------------------------------
     */

    this->portals[0].setPortal(8,55,PortalType::Normal,1,0,0,0);
    this->portals[1].setPortal(16,5,PortalType::Normal,0,0,0,0);
    this->portals[2].setPortal(24,55,PortalType::InvertV,2,0,0,0);
    this->portals[3].setPortal(40,55,PortalType::InvertV,4,0,0,0);
    this->portals[4].setPortal(52,55,PortalType::InvertV,0,0,0,0);
    this->portals[5].setPortal(70,55,PortalType::InvertV,0,0,0,0);
    this->portals[6].setPortal(82,55,PortalType::InvertV,5,0,0,0);
    this->portals[7].setPortal(104,55,PortalType::InvertV,8,0,0,0);
    this->portals[8].setPortal(120,55,PortalType::InvertV,0,0,0,0);

    this->walls[0].setWall(30, 20, 2, 48);
    this->walls[1].setWall(60, 20, 2, 48);
    this->walls[2].setWall(90, 20, 2, 48);
  }
  if(this->currentLevel==15){
    player.x=16;
    player.y=15;
    this->key[0] = 52;
    this->key[1] = 55;
    this->door[0] = 120;
    this->door[1] = 55;
    this->border = false;
    /*
     * |                                
     * |   0        4       8       12  |
     * |        |       |       |       |
     * |   P    |       |       |       |
     * |        |       |       |       |
     * |        |       |       |       |
     * |        |       |       |       |
     * | 1 2  3 |5 6  7 |9 10 11|K     E|
     * |                                
     */

    this->portals[0].setPortal(16,5,PortalType::Normal,0,0,0,0);
    
    this->portals[1].setPortal(10,55,PortalType::Normal,0,0,0,0);
    this->portals[2].setPortal(16,55,PortalType::Normal,0,0,0,0);
    this->portals[3].setPortal(22,55,PortalType::Normal,4,0,0,0);
    
    this->portals[4].setPortal(46,5,PortalType::Normal,0,0,0,0);
    
    this->portals[5].setPortal(40,55,PortalType::Normal,7,0,0,0);
    this->portals[6].setPortal(46,55,PortalType::Normal,0,0,0,0);
    //this->portals[7].setPortal(54,55,PortalType::Normal,0,0,0,0);
    
    this->portals[7].setPortal(76,5,PortalType::Normal,0,0,0,0);
    
    this->portals[8].setPortal(70,55,PortalType::Normal,0,0,0,0);
    this->portals[9].setPortal(76,55,PortalType::Normal,0,0,0,0);
    this->portals[10].setPortal(82,55,PortalType::Normal,11,0,0,0);
    
    this->portals[11].setPortal(120,5,PortalType::Normal,0,0,0,0);

    this->walls[0].setWall(30, 20, 2, 48);
    this->walls[1].setWall(60, 20, 2, 48);
    this->walls[2].setWall(90, 20, 2, 48);
  }
  
  if(this->currentLevel==16){
    /*
     * |                                
     * |   P      |    0     |     2    |
     * |          |          |          |
     * |  ----    |          |          |
     * |          |    E     |     K    |
     * |          |          |   ----   |
     * |          |          |          |
     * |          |    1     |          |
     * |                                
     */
    player.x=20;
    player.y=15;
    this->key[0] = 100;
    this->key[1] = 50;
    this->door[0] = 60;
    this->door[1] = 35;
    this->border = false;
    
    this->portals[0].setPortal(64,5,PortalType::Normal,1,0,0,0);
    this->portals[1].setPortal(64,55,PortalType::Normal,2,0,0,0);
    this->portals[2].setPortal(100,5,PortalType::Normal,0,0,0,0);
    
    this->walls[0].setWall(40, 0, 2, 64);
    this->walls[1].setWall(80, 0, 2, 64);
    this->walls[2].setWall(10, 35, 20, 2);
    this->walls[3].setWall(90, 25, 20, 2);
  }
}
