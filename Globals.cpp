
#include "Globals.h"
#include "Player.h"
Arduboy2 arduboy;

ArduboyTones sound(arduboy.audio.enabled);

GameState gameState = GameState::MainMenu;

Player player;
