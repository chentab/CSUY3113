#include "Level2.h"

#define LEVEL2_WIDTH 40
#define LEVEL2_HEIGHT 8

#define LEVEL2_ENEMY_COUNT 5
#define LEVEL2_COIN_COUNT 4

unsigned int level2_data[] =
{
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71,
    71, 71, 71, 71, 71, 71, 71, 71, 71, 192,
    70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 
    70, 70, 70, 70, 70, 70, 70, 70, 70, 174,
    70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 
    70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 174,
    70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70,
    70, 70, 70, 70, 70, 70, 70, 70, 70, 174,
    70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 
    70, 70, 70, 70, 70, 70, 70, 70, 70, 174,
    69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
    69, 69, 69, 69, 69, 69, 69, 69, 69, 156,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
};

void Level2::Initialize() {

    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("spritesheet_tiles.png");
    state.map = new Map(LEVEL2_WIDTH, LEVEL2_HEIGHT, level2_data, mapTextureID, 1.0f, 18, 18);
    // Move over all of the player and enemy code from initialization.

     // Initialize Game Objects

    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(1, -3, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(300, 0, 0); //setting acceleration and never chngin the value
    state.player->speed = 2.0f;
    state.player->textureID = Util::LoadTexture("sports_race.png");


    state.player->height = 0.8f; //to fix floating
    state.player->width = 0.8f; //to fix floating

    state.player->jumpPower = 6.0f;

    state.coins = new Entity[LEVEL2_COIN_COUNT];
    GLuint coinsTextureID = Util::LoadTexture("coin_01.png");

    state.coins[0].entityType = COIN;
    state.coins[0].textureID = coinsTextureID;
    state.coins[0].position = glm::vec3(7, -5, 0);
    state.coins[0].isActive = true;


    state.coins[1].entityType = COIN;
    state.coins[1].textureID = coinsTextureID;
    state.coins[1].position = glm::vec3(15, -3, 0);
    state.coins[1].isActive = true;

    state.coins[2].entityType = COIN;
    state.coins[2].textureID = coinsTextureID;
    state.coins[2].position = glm::vec3(26, -4, 0);
    state.coins[2].isActive = true;

    state.coins[3].entityType = COIN;
    state.coins[3].textureID = coinsTextureID;
    state.coins[3].position = glm::vec3(32, -3, 0);
    state.coins[3].isActive = true;

    state.enemies = new Entity[LEVEL2_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("grassBlock.png");
    GLuint enemy2TextureID = Util::LoadTexture("ladyBug.png");

    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(10, -2, 0);
    state.enemies[0].speed = 3.0f;
    state.enemies[0].movement = glm::vec3(0, -1, 0);
    state.enemies[0].aiType = WALKER;
    state.enemies[0].aiState = WALKING;
    state.enemies[0].aiLevel = LEVEL2;
    state.enemies[0].isActive = true;

    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = enemy2TextureID;
    state.enemies[1].position = glm::vec3(20, -2, 0);
    state.enemies[1].speed = 7;
    state.enemies[1].aiType = WAITANDGO;
    state.enemies[1].aiState = IDLE;
    state.enemies[1].isActive = true;

    state.enemies[2].entityType = ENEMY;
    state.enemies[2].textureID = enemy2TextureID;
    state.enemies[2].position = glm::vec3(25, -4, 0);
    state.enemies[2].speed = 7;
    state.enemies[2].aiType = WAITANDGO;
    state.enemies[2].aiState = IDLE;
    state.enemies[2].isActive = true;

    state.enemies[3].entityType = ENEMY;
    state.enemies[3].textureID = enemyTextureID;
    state.enemies[3].position = glm::vec3(30, -5, 0);
    state.enemies[3].speed = 5.0f;
    state.enemies[3].movement = glm::vec3(0, -1, 0);
    state.enemies[3].aiType = WALKER;
    state.enemies[3].aiState = WALKING;
    state.enemies[3].aiLevel = LEVEL2;
    state.enemies[3].isActive = true;

    state.enemies[4].entityType = ENEMY;
    state.enemies[4].textureID = enemyTextureID;
    state.enemies[4].position = glm::vec3(37, -2, 0);
    state.enemies[4].speed = 5.0f;
    state.enemies[4].movement = glm::vec3(0, -1, 0);
    state.enemies[4].aiType = WALKER;
    state.enemies[4].aiState = WALKING;
    state.enemies[4].aiLevel = LEVEL2;
    state.enemies[4].isActive = true;
}

void Level2::Update(float deltaTime) {
    

    state.coins[0].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.coins, LEVEL2_COIN_COUNT, state.map);
    state.coins[1].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.coins, LEVEL2_COIN_COUNT, state.map);
    state.coins[2].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.coins, LEVEL2_COIN_COUNT, state.map);
    state.coins[3].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.coins, LEVEL2_COIN_COUNT, state.map);

    state.enemies[0].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.coins, LEVEL2_COIN_COUNT, state.map);
    state.enemies[1].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.coins, LEVEL2_COIN_COUNT, state.map);
    state.enemies[2].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.coins, LEVEL2_COIN_COUNT, state.map);
    state.enemies[3].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.coins, LEVEL2_COIN_COUNT, state.map);
    state.enemies[4].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.coins, LEVEL2_COIN_COUNT, state.map);

    state.player->Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.coins, LEVEL2_COIN_COUNT, state.map);
    if (state.player->position.x > 40) {

        state.nextScene = 3;
    }
}


void Level2::Render(ShaderProgram* program) {
    state.map->Render(program);
    state.enemies[0].Render(program);
    state.enemies[1].Render(program);
    state.enemies[2].Render(program);
    state.enemies[3].Render(program);
    state.enemies[4].Render(program);

    state.coins[0].Render(program);
    state.coins[1].Render(program);
    state.coins[2].Render(program);
    state.coins[3].Render(program);

    state.player->Render(program);
}