#include "GameOver.h"
#include "Util.h"

#define GO_WIDTH 16
#define GO_HEIGHT 8

#define GO_ENEMY_COUNT 0
#define GO_COIN_COUNT 2

unsigned int GO_data[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

void GameOver::Initialize() {


    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("spritesheet_tiles.png");
    state.map = new Map(GO_WIDTH, GO_HEIGHT, GO_data, mapTextureID, 1.0f, 18, 18);
    // Move over all of the player and enemy code from initialization.

     // Initialize Game Objects

    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(5.5, -5, 0);
    state.player->textureID = Util::LoadTexture("sports_race.png");


    state.player->height = 0.8f; //to fix floating
    state.player->width = 0.8f; //to fix floating


    state.coins = new Entity[GO_COIN_COUNT];
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

void GameOver::Update(float deltaTime) {

    state.coins[0].Update(deltaTime, state.player, state.enemies, GO_ENEMY_COUNT, state.coins, GO_COIN_COUNT, state.map);
    state.coins[1].Update(deltaTime, state.player, state.enemies, GO_ENEMY_COUNT, state.coins, GO_COIN_COUNT, state.map);

    state.player->Update(deltaTime, state.player, state.enemies, GO_ENEMY_COUNT, state.coins, GO_COIN_COUNT, state.map);

}

void GameOver::Render(ShaderProgram* program) {

    GLuint fontTextureID = Util::LoadTexture("font1.png");

    state.map->Render(program);

    state.coins[0].Render(program);
    state.coins[1].Render(program);

    Util::DrawTexts(program, fontTextureID, "GAME OVER!", 0.5f, -0.25f, glm::vec3(4, -1, 0));
    Util::DrawTexts(program, fontTextureID, "Press esc to exit the game", 0.5f, -0.25f, glm::vec3(2, -2.5, 0));
    Util::DrawTexts(program, fontTextureID, "Press Enter to start the game!", 0.5f, -0.25f, glm::vec3(2, -6, 0));

    state.player->Render(program);


}