#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <string>
using namespace std;

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include <SDL_mixer.h>


#include "Entity.h"
#include "Map.h"
#include "Util.h"
#include "Scene.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Menu.h"
#include "GameOver.h"

SDL_Window* displayWindow;
bool gameIsRunning = true;

bool start = false;

int lives = 3;
int points = 0;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;
glm::vec3 livesMatrix, textMatrix, pointsMatrix;

Scene* currentScene;
Scene* sceneList[5];

Mix_Music* music;
Mix_Chunk* coin;


void SwitchToScene(Scene* scene) {
    currentScene = scene;
    currentScene->Initialize();
}


void Initialize() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
    displayWindow = SDL_CreateWindow("Textured!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);

#ifdef _WINDOWS
    glewInit();
#endif

    glViewport(0, 0, 640, 480);

    program.Load("shaders/vertex_textured.glsl", "shaders/effects_textured.glsl");
    //program.Load("shaders/vertex_lit.glsl", "shaders/fragment_lit.glsl");

    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);

    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);

    glUseProgram(program.programID);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    music = Mix_LoadMUS("car.mp3");
    Mix_PlayMusic(music, -1);

    coin = Mix_LoadWAV("coin.wav");
   

    livesMatrix = glm::vec3(1, -0.3f, 0);
    pointsMatrix = glm::vec3(5, -0.3f, 0);
    textMatrix = glm::vec3(5, -4, 0);

    sceneList[0] = new Menu();
    sceneList[1] = new Level1();
    sceneList[2] = new Level2();
    sceneList[3] = new Level3();
    sceneList[4] = new GameOver();
    SwitchToScene(sceneList[0]);

}

void ProcessInput() {

    currentScene->state.player->movement = glm::vec3(0);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
        case SDL_WINDOWEVENT_CLOSE:
            gameIsRunning = false;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                // Move the player left
                break;

            case SDLK_RIGHT:
                // Move the player right
                break;
            case SDLK_UP:
                // Move the player up
                break;

            case SDLK_DOWN:
                // Move the player down
                break;


            case SDLK_SPACE:
                
                break;

            case SDLK_RETURN:
                start = true;
                break;

            case SDLK_ESCAPE:
                gameIsRunning = false;
                break; // SDL_KEYDOWN
            }
        }
    }

    const Uint8* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_RIGHT]) {
        currentScene->state.player->movement.x = 1.0f;
        currentScene->state.player->animIndices = currentScene->state.player->animRight;
    }
    else if (keys[SDL_SCANCODE_UP]) {
        currentScene->state.player->movement.y = 1.0f;
        //currentScene->state.player->animIndices = currentScene->state.player->animRight;
    }
    else if (keys[SDL_SCANCODE_DOWN]) {
        currentScene->state.player->movement.y = -1.0f;
        //urrentScene->state.player->animIndices = currentScene->state.player->animRight;
    }
   


    if (glm::length(currentScene->state.player->movement) > 1.0f) {
        currentScene->state.player->movement = glm::normalize(currentScene->state.player->movement);
    }

}

float lastTicks = 0.0f;

#define FIXED_TIMESTEP 0.0166666f
float accumulator = 0.0f;

bool lastCollidedBottom = false;

void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;
    deltaTime += accumulator;

    if (deltaTime < FIXED_TIMESTEP) {
        accumulator = deltaTime;
        return;
    }

    while (deltaTime >= FIXED_TIMESTEP) {
        // Update. Notice it's FIXED_TIMESTEP. Not deltaTime
        currentScene->Update(FIXED_TIMESTEP);

        program.SetLightPosition(currentScene->state.player->position);




        deltaTime -= FIXED_TIMESTEP;
    }
    accumulator = deltaTime;

    viewMatrix = glm::mat4(1.0f);
    if (currentScene->state.player->position.x > 5 && currentScene->state.player->position.x <= 34.5f) {
        viewMatrix = glm::translate(viewMatrix, glm::vec3(-currentScene->state.player->position.x, 3.75, 0));
        livesMatrix = glm::vec3(currentScene->state.player->position.x - 4, -0.3f, 0);
        pointsMatrix = glm::vec3(currentScene->state.player->position.x, -0.3f, 0);
        textMatrix = glm::vec3(currentScene->state.player->position.x - 2, -4, 0);
        
        
    }
    else if (currentScene->state.player->position.x >= 34.5f) {
        viewMatrix = glm::translate(viewMatrix, glm::vec3(-34.5f, 3.75f, 0));
    }
    else {
        viewMatrix = glm::translate(viewMatrix, glm::vec3(-5, 3.75, 0));
        livesMatrix = glm::vec3(1, -0.3f, 0);
        pointsMatrix = glm::vec3(5, -0.3f, 0);
        textMatrix = glm::vec3(5, -4, 0);
    }


    if (start == true) {
        currentScene->state.nextScene = 1;
        lives = 3;
        points = 0;
        start = false;
    }
    
}


void Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint fontTextureID = Util::LoadTexture("font1.png");


    program.SetViewMatrix(viewMatrix);

    if (lives == 0) {

        currentScene->state.nextScene = 4;

    }

    


    glUseProgram(program.programID);

    currentScene->Render(&program);

    Util::DrawTexts(&program, fontTextureID, "Lives: " + to_string(lives), 0.5f, -0.25f, livesMatrix);
    Util::DrawTexts(&program, fontTextureID, "Points: " + to_string(points), 0.5f, -0.25f, pointsMatrix);




    SDL_GL_SwapWindow(displayWindow);
}


void Shutdown() {
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    Initialize();

    while (gameIsRunning) {
        ProcessInput();
        Update();

        if (currentScene->state.player->enemyCollision) {

 
            SwitchToScene(currentScene);
            lives -= 1;
            if (points > 0){ points -= 10; }

            currentScene->state.player->enemyCollision = false;
            
        }
        else if (currentScene->state.player->coinCollision) {
            Mix_PlayChannel(-1, coin, 0);
            points += 10;
            //currentScene->state.player->coinCollision = false;
        }
        else {

            if (currentScene->state.nextScene >= 0) { SwitchToScene(sceneList[currentScene->state.nextScene]); }
        }
        

        Render();
    }

    Shutdown();
    return 0;
}