#include "Level1.h"

#define LEVEL1_WIDTH 40
#define LEVEL1_HEIGHT 8

#define LEVEL1_ENEMY_COUNT 4
#define LEVEL1_COIN_COUNT 4

unsigned int level1_data[] =
{
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 
    185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 306,
    184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184,
    184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 288,
    184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 
    184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 288,
    184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184,
    184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 288,
    184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184,
    184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 288,
    183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183,
    183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 270,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
};

void Level1::Initialize() {

    state.nextScene = -1;

	GLuint mapTextureID = Util::LoadTexture("spritesheet_tiles.png");
	state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 18, 18);
	// Move over all of the player and enemy code from initialization.

     // Initialize Game Objects

    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(1, -3, 0);
    state.player->movement = glm::vec3(1, 0, 0);
    state.player->velocity = glm::vec3(1, 0, 0);
    state.player->acceleration = glm::vec3(200, 0, 0); //setting acceleration and never chngin the value
    state.player->speed = 4.0f;
    state.player->textureID = Util::LoadTexture("sports_race.png");

    state.player->height = 0.8f; //to fix floating
    state.player->width = 0.8f; //to fix floating


    state.coins = new Entity[LEVEL1_COIN_COUNT];
    GLuint coinsTextureID = Util::LoadTexture("coin_01.png");

    state.coins[0].entityType = COIN;
    state.coins[0].textureID = coinsTextureID;
    state.coins[0].position = glm::vec3(14, -3, 0);
    state.coins[0].isActive = true;
    state.coins[0].height = 1.2f;
    state.coins[0].width = 1.2f;


    state.coins[1].entityType = COIN;
    state.coins[1].textureID = coinsTextureID;
    state.coins[1].position = glm::vec3(20, -1, 0);
    state.coins[1].isActive = true;
    state.coins[1].height = 1.2f;
    state.coins[1].width = 1.2f;

    state.coins[2].entityType = COIN;
    state.coins[2].textureID = coinsTextureID;
    state.coins[2].position = glm::vec3(28, -5, 0);
    state.coins[2].isActive = true;
    state.coins[2].height = 1.2f;
    state.coins[2].width = 1.2f;

    state.coins[3].entityType = COIN;
    state.coins[3].textureID = coinsTextureID;
    state.coins[3].position = glm::vec3(37, -5, 0);
    state.coins[3].isActive = true;
    state.coins[3].height = 1.2f;
    state.coins[3].width = 1.2f;


    state.enemies = new Entity[LEVEL1_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("frog.png");

    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(20, -5, 0);
    state.enemies[0].speed = 4;
    state.enemies[0].aiType = WAITANDGO;
    state.enemies[0].aiState = IDLE;
    state.enemies[0].isActive = true;


    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = enemyTextureID;
    state.enemies[1].position = glm::vec3(25, -2, 0);
    state.enemies[1].speed = 4;
    state.enemies[1].aiType = WAITANDGO;
    state.enemies[1].aiState = IDLE;
    state.enemies[1].isActive = true;

    state.enemies[2].entityType = ENEMY;
    state.enemies[2].textureID = enemyTextureID;
    state.enemies[2].position = glm::vec3(30, -3, 0);
    state.enemies[2].speed = 4;
    state.enemies[2].aiType = WAITANDGO;
    state.enemies[2].aiState = IDLE;
    state.enemies[2].isActive = true;

    state.enemies[3].entityType = ENEMY;
    state.enemies[3].textureID = enemyTextureID;
    state.enemies[3].position = glm::vec3(35, -2, 0);
    state.enemies[3].speed = 4;
    state.enemies[3].aiType = WAITANDGO;
    state.enemies[3].aiState = IDLE;
    state.enemies[3].isActive = true;


}

void Level1::Update(float deltaTime) {

    state.coins[0].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.coins, LEVEL1_COIN_COUNT, state.map);
    state.coins[1].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.coins, LEVEL1_COIN_COUNT, state.map);
    state.coins[2].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.coins, LEVEL1_COIN_COUNT, state.map);
    state.coins[3].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.coins, LEVEL1_COIN_COUNT, state.map);

    state.enemies[0].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.coins, LEVEL1_COIN_COUNT, state.map);
    state.enemies[1].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.coins, LEVEL1_COIN_COUNT, state.map);
    state.enemies[2].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.coins, LEVEL1_COIN_COUNT, state.map);
    state.enemies[3].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.coins, LEVEL1_COIN_COUNT, state.map);

	state.player->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.coins, LEVEL1_COIN_COUNT, state.map);

    if (state.player->position.x > 40) {

        state.nextScene = 2;
    }
}

void Level1::Render(ShaderProgram* program) {
	state.map->Render(program);
    state.enemies[0].Render(program);
    state.enemies[1].Render(program);
    state.enemies[2].Render(program);
    state.enemies[3].Render(program);

    state.coins[0].Render(program);
    state.coins[1].Render(program);
    state.coins[2].Render(program);
    state.coins[3].Render(program);

	state.player->Render(program);
	

}