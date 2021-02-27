#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, ballMatrix, playerOneMatrix, playerTwoMatrix, projectionMatrix;

float Player_1 = 0;
float xdist1 = 0;
float xdist2 = 0;
float ydist1 = 0;
float ydist2 = 0;
float Player_2 = 0;
float player_speed = 3.0f;
float ball_speed = 3.0f;
float player1_width = 0.3f;
float player1_height = 1.0f;
float player2_width = 0.3f;
float player2_height = 1.0f;
float ball_width = 1.0f;
float ball_height = 1.0f;


glm::vec3 player1_position = glm::vec3(4.9, 0, 0);
glm::vec3 player2_position = glm::vec3(-4.9, 0, 0);
glm::vec3 ball_position = glm::vec3(0, 0, 0);


glm::vec3 player1_movement = glm::vec3(0, 0, 0);
glm::vec3 player2_movement = glm::vec3(0, 0, 0);
glm::vec3 ball_movement = glm::vec3(-1.0, 0, 0);



GLuint playerOneTextureID;
GLuint playerTwoTextureID;
GLuint ballTextureID;

GLuint LoadTexture(const char* filePath) {
    int w, h, n;
    unsigned char* image = stbi_load(filePath, &w, &h, &n, STBI_rgb_alpha);
    if (image == NULL) {
        std::cout << "Unable to load image. Make sure the path is correct\n";
        assert(false);
    }
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_image_free(image);
    return textureID;
}

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Textured!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);

#ifdef _WINDOWS
    glewInit();
#endif

    glViewport(0, 0, 640, 480);

    //program.Load("shaders/vertex.glsl", "shaders/fragment.glsl");
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl"); //loading a texture shaders

    viewMatrix = glm::mat4(1.0f);
    playerOneMatrix = glm::mat4(1.0f);
    playerTwoMatrix = glm::mat4(1.0f);
    ballMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);

    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    //program.SetColor(1.0f, 0.0f, 0.0f, 1.0f);

    glUseProgram(program.programID);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    glEnable(GL_BLEND);
    // Good setting for transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    playerOneTextureID = LoadTexture("paddle.png");
    playerTwoTextureID = LoadTexture("paddle.png");
    ballTextureID = LoadTexture("ball.png");

}

void ProcessInput() {

    player1_movement = glm::vec3(0);
    player2_movement = glm::vec3(0);

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
            case SDLK_SPACE:
                // Some sort of action
                break;
            }
            break; // SDL_KEYDOWN
        }
    }
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_UP]) {
        if (player1_position.y > 3.25f) {
            player1_movement.y = 0.0f;
        }
        else player1_movement.y = 1.0f;
    }
    else if (keys[SDL_SCANCODE_DOWN]) {
        if (player1_position.y < -3.25f) {
            player1_movement.y = 0.0f;
        }
        else player1_movement.y = -1.0f;
    }
    if (keys[SDL_SCANCODE_W]) {
        if (player2_position.y > 3.25f) {
            player2_movement.y = 0.0f;
        }
        else player2_movement.y = 1.0f;
    }
    else if (keys[SDL_SCANCODE_S]) {
        if (player2_position.y < -3.25f) {
            player2_movement.y = 0.0f;
        }
        else player2_movement.y = -1.0f;
    }
    if (glm::length(player1_movement) > 1.0f) {
        player1_movement = glm::normalize(player1_movement);
    }
    if (glm::length(player2_movement) > 1.0f) {
        player2_movement = glm::normalize(player2_movement);
    }
    
    // Notice the above use SDL_SCANCODE_ and not SDLK_
}

float lastTicks = 0.0f;


void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;
    // Add (direction * units per second * elapsed time)
    player1_position += player1_movement * player_speed * deltaTime;
    player2_position += player2_movement * player_speed * deltaTime;
    ball_position += ball_movement * ball_speed * deltaTime;

    playerOneMatrix = glm::mat4(1.0f);
    playerTwoMatrix = glm::mat4(1.0f);
    ballMatrix = glm::mat4(1.0f);

    playerOneMatrix = glm::translate(playerOneMatrix, player1_position);
    playerTwoMatrix = glm::translate(playerTwoMatrix, player2_position);
    ballMatrix = glm::translate(ballMatrix, ball_position);

    xdist1 = fabs(ball_position.x - player1_position.x) - ((ball_width + player1_width) / 2.0f);
    xdist2 = fabs(ball_position.x - player2_position.x) - ((ball_width + player2_width) / 2.0f);
    ydist1 = fabs(ball_position.y - player1_position.y) - ((ball_height + player1_height) / 2.0f);
    ydist2 = fabs(ball_position.y - player2_position.y) - ((ball_height + player2_height) / 2.0f);
    
    if (xdist2 < 0 && ydist2 < 0) {
        // diretion of the ball acccording to where it hits the racket.
        ball_movement.y = ((ball_position.y - player2_position.y) / player2_height) - 0.1f;
        ball_movement.x = fabs(ball_movement.x); 
    }

    // hit by right racket?
    else if (xdist1 < 0 && ydist1 < 0) {
        // diretion of the ball acccording to where it hits the racket.
        ball_movement.y = ((ball_position.y - player1_position.y) / player1_height) - 0.1f;
        ball_movement.x = -fabs(ball_movement.x); 
    }

    // hit left wall
    else if (ball_position.x < -5.0f) {
        gameIsRunning = false;
    }

    // hit right wall
    else if (ball_position.x > 5.0f) {
        gameIsRunning = false;
    }

    // hit top wall
    else if (ball_position.y > 3.75f) {
        ball_movement.y = -fabs(ball_movement.y); 
    }

    // hit bottom wall
    else if (ball_position.y < -3.75f) {
        ball_movement.y = fabs(ball_movement.y); 
    }
}

//void Render() {
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    program.SetModelMatrix(modelMatrix);
//
//    float vertices[] = { 0.5f, -0.5f, 0.0f, 0.5f, -0.5f, -0.5f };
//    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
//    glEnableVertexAttribArray(program.positionAttribute);
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//    glDisableVertexAttribArray(program.positionAttribute);
//
//    SDL_GL_SwapWindow(displayWindow);
//}

void Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    program.SetModelMatrix(playerOneMatrix);
    float sunVertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float sunCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, sunVertices);
    glEnableVertexAttribArray(program.positionAttribute);
    glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, sunCoords);

    glEnableVertexAttribArray(program.texCoordAttribute);
    glBindTexture(GL_TEXTURE_2D, playerOneTextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);


    program.SetModelMatrix(playerTwoMatrix);
    glBindTexture(GL_TEXTURE_2D, (playerTwoTextureID));
    glDrawArrays(GL_TRIANGLES, 0, 6);

    program.SetModelMatrix(ballMatrix);
    glBindTexture(GL_TEXTURE_2D, ballTextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(program.positionAttribute);
    glDisableVertexAttribArray(program.texCoordAttribute);


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
        Render();
    }

    Shutdown();
    return 0;
}