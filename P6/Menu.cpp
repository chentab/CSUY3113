#include "Menu.h"
#include "Util.h"

#define MENU_WIDTH 16
#define MENU_HEIGHT 8

#define MENU_ENEMY_COUNT 0
#define MENU_COIN_COUNT 2

unsigned int Menu_data[] =
{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 
    101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101,
    101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101,
    101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101,
    101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101,
    101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
};

void Menu::Initialize() {
    

    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("spritesheet_tiles.png");
    state.map = new Map(MENU_WIDTH, MENU_HEIGHT, Menu_data, mapTextureID, 1.0f, 18, 18);
    // Move over all of the player and enemy code from initialization.

     // Initialize Game Objects

    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(5.5, -5, 0);
    state.player->textureID = Util::LoadTexture("sports_race.png");

    
    state.player->height = 0.8f; //to fix floating
    state.player->width = 0.8f; //to fix floating


    state.coins = new Entity[MENU_COIN_COUNT];
    GLuint coinsTextureID = Util::LoadTexture("coin_01.png");

    state.coins[0].entityType = COIN;
    state.coins[0].textureID = coinsTextureID;
    state.coins[0].position = glm::vec3(8, -5, 0);
    state.coins[0].scale = glm::vec3(0.5f, 0.5f, 0.5f);
    state.coins[0].isActive = true;


    state.coins[1].entityType = COIN;
    state.coins[1].textureID = coinsTextureID;
    state.coins[1].position = glm::vec3(3, -5, 0);
    state.coins[1].scale = glm::vec3(0.5f, 0.5f, 0.5f);
    state.coins[1].isActive = true;


}

void Menu::Update(float deltaTime) {

    state.coins[0].Update(deltaTime, state.player, state.enemies, MENU_ENEMY_COUNT, state.coins, MENU_COIN_COUNT, state.map);
    state.coins[1].Update(deltaTime, state.player, state.enemies, MENU_ENEMY_COUNT, state.coins, MENU_COIN_COUNT, state.map);
   
    state.player->Update(deltaTime, state.player, state.enemies, MENU_ENEMY_COUNT, state.coins, MENU_COIN_COUNT, state.map);

}

void Menu::Render(ShaderProgram* program) {

    GLuint fontTextureID = Util::LoadTexture("font1.png");

    state.map->Render(program);
   
    state.coins[0].Render(program);
    state.coins[1].Render(program);

    Util::DrawTexts(program, fontTextureID, "Final Project", 0.5f, -0.25f, glm::vec3(4, -1, 0));
    Util::DrawTexts(program, fontTextureID, "Use the arrow keys to move up and down", 0.5f, -0.25f, glm::vec3(1, -1.5, 0));
    Util::DrawTexts(program, fontTextureID, "Use the right arrow to momentarily", 0.5f, -0.25f, glm::vec3(1, -2, 0));
    Util::DrawTexts(program, fontTextureID, "speed up ", 0.5f, -0.25f, glm::vec3(1, -2.5, 0));
    Util::DrawTexts(program, fontTextureID, "Collect coins for points! ", 0.5f, -0.25f, glm::vec3(1, -3, 0));
    Util::DrawTexts(program, fontTextureID, "Points will be lost when losing lives", 0.5f, -0.25f, glm::vec3(1, -3.5, 0));
    Util::DrawTexts(program, fontTextureID, "Have fun!", 0.5f, -0.25f, glm::vec3(4.5, -7, 0));
    Util::DrawTexts(program, fontTextureID, "Press Enter to start the game!", 0.5f, -0.25f, glm::vec3(2, -6, 0));
   
    state.player->Render(program);


}