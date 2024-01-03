#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "GameState.h"

/// Globals
/// test
const int windowsizeX = 128;
const int windowsizeY = 64;
uint8_t px = 5;
uint8_t py = 80;
sf::Text text;
sf::RenderWindow window(sf::VideoMode(windowsizeX,windowsizeY), "Pixelportal - Desktop", sf::Style::Default);

void printtitlescreentext(){

  text.setString("PiXelPoRtAl");
  text.setCharacterSize(20);
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Bold | sf::Text::Underlined);
  text.setPosition(0, 23);
  window.draw(text);

  text.setString("Press A");
  text.setCharacterSize(10);
  text.setFillColor(sf::Color::Cyan);
  text.setStyle(sf::Text::Bold | sf::Text::Underlined);
  text.setPosition(40,40);
  window.draw(text);

}
void titleScreen(){
    window.clear();

    sf::RectangleShape rectangle(sf::Vector2f(0.f, 0.f));    /// this rectangle is used to draw every box, 
                                                             /// now that it is initialized it can be resized and moved

    // border + inner box
    rectangle.setSize(sf::Vector2f(128.f, 64.f));
    rectangle.setPosition(0,0);
    window.draw(rectangle);

    rectangle.setFillColor(sf::Color::Black);
    rectangle.setSize(sf::Vector2f(126.f, 62.f));
    rectangle.setPosition(1,1);
    window.draw(rectangle);

    rectangle.setFillColor(sf::Color::White);
    rectangle.setSize(sf::Vector2f(110.f, 46.f));
    rectangle.setPosition(9,9);
    window.draw(rectangle);

    rectangle.setFillColor(sf::Color::Black);
    rectangle.setSize(sf::Vector2f(108.f, 44.f));
    rectangle.setPosition(10,10);
    window.draw(rectangle);


    //portals
    rectangle.setFillColor(sf::Color::White);
    rectangle.setSize(sf::Vector2f(4.f, 4.f));
    rectangle.setPosition(24,3);
    window.draw(rectangle);

    rectangle.setFillColor(sf::Color::Black);
    rectangle.setSize(sf::Vector2f(2.f, 2.f));
    rectangle.setPosition(25,4);
    window.draw(rectangle);

    rectangle.setFillColor(sf::Color::White);
    rectangle.setSize(sf::Vector2f(4.f, 4.f));
    rectangle.setPosition(94,3);
    window.draw(rectangle);

    rectangle.setFillColor(sf::Color::Black);
    rectangle.setSize(sf::Vector2f(2.f, 2.f));
    rectangle.setPosition(95,4);
    window.draw(rectangle);

    rectangle.setFillColor(sf::Color::White);
    rectangle.setSize(sf::Vector2f(4.f, 4.f));
    rectangle.setPosition(24,57);
    window.draw(rectangle);

    rectangle.setFillColor(sf::Color::Black);
    rectangle.setSize(sf::Vector2f(2.f, 2.f));
    rectangle.setPosition(25,58);
    window.draw(rectangle);

    rectangle.setFillColor(sf::Color::White);
    rectangle.setSize(sf::Vector2f(4.f, 4.f));
    rectangle.setPosition(94,57);
    window.draw(rectangle);

    rectangle.setFillColor(sf::Color::Black);
    rectangle.setSize(sf::Vector2f(2.f, 2.f));
    rectangle.setPosition(95,58);
    window.draw(rectangle);


    rectangle.setFillColor(sf::Color::White);
    rectangle.setSize(sf::Vector2f(1.f,1.f));
    rectangle.setPosition(px,py);
    window.draw(rectangle);

    px -= 2;

    if (px < 28 && py < 30) {
        px = 92;
        py = 58;
    }
    if (px < 28 && py > 30) {
        px = 92;
        py = 4;
    }

    printtitlescreentext();
    window.display();
}



void nextLevelScreen(){

    text.setString("LEVEL CLEARED");
    text.setCharacterSize(19);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(0, 23);
    window.draw(text);
    window.display();
    sf::sleep(sf::seconds(3));
}

void endGameScreen(){
   
    text.setString("THE END");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(0, 23);
    window.draw(text);
    window.display();
    sf::sleep(sf::seconds(3));
    gameState=GameState::MainMenu;
}


int main(){

  window.setFramerateLimit(fps);

    sf::Font font;
    font.loadFromFile("./resources/font.ttf"); /// placeholderfont
    text.setFont(font);
while (window.isOpen()){

    sf::Event event;                    /// Event handling

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
                                        /// start of the actual game
    if (gameState==GameState::MainMenu){
        titleScreen();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){       
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
          gameState=GameState::Game;
          window.clear();
          level.currentLevel = 1;
          level.resetLevel();
          level.loadLevel();
          level.drawLevel(&window);
          }
      }
      if(gameState==GameState::Game){
        window.clear();
        level.drawLevel(&window);
        player.processInputs();
        player.update(&window); 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){       
                gameState=GameState::MainMenu;
        }
        if(player.touchingDoor()){
          gameState=GameState::NextLevel;
          if(level.currentLevel==LASTLEVEL){
            gameState=GameState::EndGame;
          }
        }
        
      }
      if(gameState==GameState::NextLevel){
          window.clear();
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
      window.display();
    }
}
