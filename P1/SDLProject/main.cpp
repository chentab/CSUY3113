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
glm::mat4 viewMatrix, sunMatrix, carMatrix, moonMatrix, projectionMatrix;

float sun = 0;
float car = 0;
float moon = 0;
float sun_rotate = 0;
bool changeDirection = true;
bool shrink = true;

GLuint moonTextureID;
GLuint sunTextureID;
GLuint carTextureID;

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
    sunMatrix = glm::mat4(1.0f);
    moonMatrix = glm::mat4(1.0f);
    carMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);

    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    //program.SetColor(1.0f, 0.0f, 0.0f, 1.0f);

    glUseProgram(program.programID);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    glEnable(GL_BLEND);
    // Good setting for transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    sunTextureID = LoadTexture("sun.png");
    moonTextureID = LoadTexture("star.png");
    carTextureID = LoadTexture("ctg.png");

}

void ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            gameIsRunning = false;
        }
    }
}

float lastTicks = 0.0f;


void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;

    if ((car > 1) & (car < 6)) {
        changeDirection = false;
    }
    if ((car > -6) & (car < -1)) {
        changeDirection = true;
    }

    if ((moon > 1) & (moon < 6)) {
        shrink = false;
    }
    if ((moon > -6) & (moon < -1)) {
        shrink = true;
    }

    if (changeDirection) {
        car += 1.0f * deltaTime;
    }
    else {
        car -= 1.0f * deltaTime;
    }
    
    if (shrink) {
        moon += 1.0f * deltaTime;
    }
    else {
        moon -= 1.0f * deltaTime;
    }

    sun += 1.0f * deltaTime;
    //moon += 1.0f * deltaTime;
    sun_rotate += 90.0f * deltaTime;
    //car += 1.0f * deltaTime;
    moonMatrix = glm::mat4(1.0f);
    sunMatrix = glm::mat4(1.0f);
    carMatrix = glm::mat4(1.0f);
    
    carMatrix = glm::translate(carMatrix, glm::vec3(3.0, -3.0f, 0.0f));
    moonMatrix = glm::translate(moonMatrix, glm::vec3(3.0, 2.0f, 0.0f));
    sunMatrix = glm::translate(sunMatrix, glm::vec3(-3.0, 2.0f, 0.0f));
    carMatrix = glm::translate(carMatrix, glm::vec3(car, 0.0f, 0.0f));

        
    moonMatrix = glm::scale(moonMatrix, glm::vec3(moon, moon, 1.0f));
       
    sunMatrix = glm::rotate(sunMatrix, glm::radians(sun_rotate), glm::vec3(0.0f, 0.0f, 1.0f));

    //modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0001f, 0.0f, 0.0f)); //translate move each frame
    //modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //rotate
    //modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f, 2.0f, 1.0f));



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
    program.SetModelMatrix(sunMatrix);
    float sunVertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float sunCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, sunVertices);
    glEnableVertexAttribArray(program.positionAttribute);
    glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, sunCoords);

    glEnableVertexAttribArray(program.texCoordAttribute);
    glBindTexture(GL_TEXTURE_2D, sunTextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);


    program.SetModelMatrix(carMatrix);
    glBindTexture(GL_TEXTURE_2D, carTextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    program.SetModelMatrix(moonMatrix);
    glBindTexture(GL_TEXTURE_2D, moonTextureID);
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