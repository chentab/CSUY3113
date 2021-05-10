#include "Level3.h"

#define LEVEL3_WIDTH 40
#define LEVEL3_HEIGHT 8

#define LEVEL3_ENEMY_COUNT 6
#define LEVEL3_COIN_COUNT 6

unsigned int level3_data[] =
{

    69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 
    69, 69, 69, 69, 69, 69, 69, 69, 69, 192,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 174,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 
    48, 48, 48, 48, 48, 48, 48, 48, 48, 174,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 
    48, 48, 48, 48, 48, 48, 48, 48, 48, 174,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 174,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 
    48, 48, 48, 48, 48, 48, 48, 48, 48, 174,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 
    48, 48, 48, 48, 48, 48, 48, 48, 48, 174,
    71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 
    71, 71, 71, 71, 71, 71, 71, 71, 71, 192,
};

void Level3::Initialize() {

    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("spritesheet_tiles.png");
    state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, level3_data, mapTextureID, 1.0f, 18, 18);
    // Move over all of the player and enemy code from initialization.

     // Initialize Game Objects

    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(1, -3, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(400, 0, 0); //setting acceleration and never chngin the value
    state.player->speed = 2.0f;
    state.player->textureID = Util::LoadTexture("sports_race.png");

    state.player->height = 0.8f; //to fix floating
    state.player->width = 0.8f; //to fix floating

    state.player->jumpPower = 6.0f;

    state.coins = new Entity[LEVEL3_COIN_COUNT];
    GLuint coinsTextureID = Util::LoadTexture("coin_01.png");

    state.coins[0].entityType = COIN;
    state.coins[0].textureID = coinsTextureID;
    state.coins[0].position = glm::vec3(7, -5, 0);
    state.coins[0].isActive = true;


    state.coins[1].entityType = COIN;
    state.coins[1].textureID = coinsTextureID;
    state.coins[1].position = glm::vec3(16, -1, 0);
    state.coins[1].isActive = true;

    state.coins[2].entityType = COIN;
    state.coins[2].textureID = coinsTextureID;
    state.coins[2].position = glm::vec3(21, -5, 0);
    state.coins[2].isActive = true;

    state.coins[3].entityType = COIN;
    state.coins[3].textureID = coinsTextureID;
    state.coins[3].position = glm::vec3(26, -4, 0);
    state.coins[3].isActive = true;

    state.coins[4].entityType = COIN;
    state.coins[4].textureID = coinsTextureID;
    state.coins[4].position = glm::vec3(32, -3, 0);
    state.coins[4].isActive = true;

    state.coins[5].entityType = COIN;
    state.coins[5].textureID = coinsTextureID;
    state.coins[5].position = glm::vec3(36, -2, 0);
    state.coins[5].isActive = true;


    state.enemies = new Entity[LEVEL3_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("spider.png");
    GLuint enemy2TextureID = Util::LoadTexture("mouse.png");

    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(13, -2, 0);
    state.enemies[0].speed = 3.0f;
    state.enemies[0].movement = glm::vec3(0, -1, 0);
    state.enemies[0].aiType = WALKER;
    state.enemies[0].aiState = WALKING;
    state.enemies[0].aiLevel = LEVEL2;
    state.enemies[0].isActive = true; 


    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = enemyTextureID;
    state.enemies[1].position = glm::vec3(15, -5, 0);
    state.enemies[1].speed = 3.0f;
    state.enemies[1].movement = glm::vec3(0, 1, 0);
    state.enemies[1].aiType = WALKER;
    state.enemies[1].aiState = WALKING;
    state.enemies[1].aiLevel = LEVEL2;
    state.enemies[1].isActive = true;

    state.enemies[2].entityType = ENEMY;
    state.enemies[2].textureID = enemyTextureID;
    state.enemies[2].position = glm::vec3(20, -2, 0);
    state.enemies[2].speed = 3.0f;
    state.enemies[2].movement = glm::vec3(0, 1, 0);
    state.enemies[2].aiType = WALKER;
    state.enemies[2].aiState = WALKING;
    state.enemies[2].aiLevel = LEVEL2;
    state.enemies[2].isActive = true;

    state.enemies[3].entityType = ENEMY;
    state.enemies[3].textureID = enemyTextureID;
    state.enemies[3].position = glm::vec3(22, -5, 0);
    state.enemies[3].speed = 3.0f;
    state.enemies[3].movement = glm::vec3(0, -1, 0);
    state.enemies[3].aiType = WALKER;
    state.enemies[3].aiState = WALKING;
    state.enemies[3].aiLevel = LEVEL2;
    state.enemies[3].isActive = true;

    state.enemies[4].entityType = ENEMY;
    state.enemies[4].textureID = enemy2TextureID;
    state.enemies[4].position = glm::vec3(30, -3, 0);
    state.enemies[4].speed = 6;
    state.enemies[4].aiType = WAITANDGO;
    state.enemies[4].aiState = IDLE;
    state.enemies[4].isActive = true;

    state.enemies[5].entityType = ENEMY;
    state.enemies[5].textureID = enemy2TextureID;
    state.enemies[5].position = glm::vec3(35, -1, 0);
    state.enemies[5].speed = 6;
    state.enemies[5].aiType = WAITANDGO;
    state.enemies[5].aiState = IDLE;
    state.enemies[5].isActive = true;
}

void Level3::Update(float deltaTime) {

    state.coins[0].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.coins, LEVEL3_COIN_COUNT, state.map);
    state.coins[1].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.coins, LEVEL3_COIN_COUNT, state.map);
    state.coins[2].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.coins, LEVEL3_COIN_COUNT, state.map);
    state.coins[3].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.coins, LEVEL3_COIN_COUNT, state.map);
    state.coins[4].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.coins, LEVEL3_COIN_COUNT, state.map);
    state.coins[5].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.coins, LEVEL3_COIN_COUNT, state.map);

    state.enemies[0].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.coins, LEVEL3_COIN_COUNT, state.map);
    state.enemies[1].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.coins, LEVEL3_COIN_COUNT, state.map);
    state.enemies[2].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.coins, LEVEL3_COIN_COUNT, state.map);
    state.enemies[3].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.coins, LEVEL3_COIN_COUNT, state.map);
    state.enemies[4].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.coins, LEVEL3_COIN_COUNT, state.map);
    state.enemies[5].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.coins, LEVEL3_COIN_COUNT, state.map);

    state.player->Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.coins, LEVEL3_COIN_COUNT, state.map);

    
}


void Level3::Render(ShaderProgram* program) {

    GLuint fontTextureID = Util::LoadTexture("font1.png");

    state.map->Render(program);
    state.enemies[0].Render(program);
    state.enemies[1].Render(program);
    state.enemies[2].Render(program);
    state.enemies[3].Render(program);
    state.enemies[4].Render(program);
    state.enemies[5].Render(program);

    state.coins[0].Render(program);
    state.coins[1].Render(program);
    state.coins[2].Render(program);
    state.coins[3].Render(program);
    state.coins[4].Render(program);
    state.coins[5].Render(program);


    if (state.player->position.x > 40) {

        Util::DrawTexts(program, fontTextureID, "You Won!", 0.5f, -0.25f, glm::vec3(33, -1, 0));
        Util::DrawTexts(program, fontTextureID, "Press esc to exit the game", 0.5f, -0.25f, glm::vec3(31, -2, 0));
        Util::DrawTexts(program, fontTextureID, "Press Enter to start the game!", 0.5f, -0.25f, glm::vec3(31, -3, 0));

    }

    state.player->Render(program);
}