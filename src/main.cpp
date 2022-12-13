#include <iostream>
#include <vector>
#include <raylib.h>
#include <cmath>

#include "ObjectManager.hpp"
#include "../Math.hpp"
#include "GameObject/GameObjects.hpp"

Math::Vec2<float> windowSize;
Math::Vec2<float> screenRatio;
int main() {
    InitWindow(0, 0, "Game!");
    ToggleFullscreen();
    windowSize = {(float)GetScreenWidth(), (float)GetScreenHeight()};
    LoadImagesToCache();
    screenRatio = windowSize / (Math::Vec2<float>){ 1920, 1080 };
    ObjectManager objMan(screenRatio);
    
    objMan.SetPlayer(Player({ 0, 0, 20, 40 }, PURPLE, TOPDOWN));
    Player& player = *objMan.GetPlayer();

    objMan.loadLevel("demo");
    
    Camera2D camera;
    while (true) {
        if (WindowShouldClose()) exit(0);
        float deltaTime = GetFrameTime();
        objMan.update(deltaTime);
        camera = {
            { (float)(windowSize.x/2), (float)(windowSize.y/2) },
            { (float)round(((player.rect.x)+(player.rect.w/2))*screenRatio.x), (float)round(((player.rect.y)+(player.rect.h/2))*screenRatio.y) },
            0, 1
        };

        BeginDrawing(); {
            ClearBackground(BLACK);
            BeginMode2D(camera);

            objMan.render(deltaTime);

            EndMode2D();
            DrawFPS(10, 10);
        } EndDrawing();
    }

    CloseWindow();
    return 0;
}