#ifndef SRC_GAMEOBJECT_GAMEOBJECTS_PLAYER_HPP
#define SRC_GAMEOBJECT_GAMEOBJECTS_PLAYER_HPP
#include "../GameObject.hpp"
#include "../../ObjectManager.hpp"

enum GameType {
    TOPDOWN = 0,
    SIDEVIEW = 1
};

class Player : public GameObject {
public:
    Player() {}
    Player(Math::Rect<float> rect, Color colour, GameType gameType) : GameObject(rect, PLAYER), colour(colour), gameType(gameType) {}

    void update(float deltaTime, std::vector<GameObject*> objs, ObjectManager& objMan) override {
        Math::Vec2<float> velocity = { 0, 0 };
        if (IsKeyDown(KEY_W)) velocity.y -= speed*deltaTime;
        if (IsKeyDown(KEY_S)) velocity.y += speed*deltaTime;
        if (IsKeyDown(KEY_A)) velocity.x -= speed*deltaTime;
        if (IsKeyDown(KEY_D)) velocity.x += speed*deltaTime;
        if (IsKeyDown(KEY_LEFT_SHIFT)) velocity *= 5;

        bool moveX = true, moveY = true;

        Math::Rect<float> newRect = this->rect;
        newRect.x += velocity.x;
        for (int i = 0; i < objs.size(); i++)
            if (objs.at(i)->collides && newRect.IsCollidingWith(objs.at(i)->rect)) {
                moveX = false;
            }


        newRect.x = rect.x;
        newRect.y += velocity.y;
        for (int i = 0; i < objs.size(); i++)
            if (objs.at(i)->collides && newRect.IsCollidingWith(objs.at(i)->rect)) {
                moveY = false;
            }

        if (moveX) this->rect.x += velocity.x;
        if (moveY) this->rect.y += velocity.y;
    }

    void render(float deltaTime, Math::Vec2<float> screenRatio) override {
        Math::Rect<float> tmpRect = {
            rect.pos * screenRatio,
            rect.size * screenRatio
        };

        DrawRectangleRec({ tmpRect.x, tmpRect.y, tmpRect.w, tmpRect.h }, colour);
        DrawRectangleRec({ tmpRect.x-3, tmpRect.y-5, tmpRect.w+6, 10 }, RED);
    }

    Color colour;
    GameType gameType;
    float speed = 100;
    float speedMult = 1;
};

#endif /* SRC_GAMEOBJECT_GAMEOBJECTS_PLAYER_HPP */
