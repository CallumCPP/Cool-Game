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
    Player(Math::Rect<float> rect, Color colour, GameType gameType) : GameObject(rect, PLAYER), colour(colour) {
        SetGameType(gameType);
    }

    void update(float deltaTime, std::vector<GameObject*> objs, ObjectManager& objMan) override {
        (this->*Player::_update)(deltaTime, objs, objMan);
    }

    void updateSideView(float deltaTime, std::vector<GameObject*> objs, ObjectManager& objMan) {
        if (IsKeyReleased(KEY_SPACE)) SetGameType(TOPDOWN);
        this->rect.y += 100 * deltaTime;
    }

    void updateTopDown(float deltaTime, std::vector<GameObject*> objs, ObjectManager& objMan) {
        Math::Vec2<float> velocity = { 0, 0 };
        if (IsKeyReleased(KEY_SPACE)) SetGameType(SIDEVIEW);
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

    void SetGameType(GameType gameType) {
        this->_gameType = gameType;
        if (gameType == TOPDOWN) {
            _update = &Player::updateTopDown;
        } else {
            _update = &Player::updateSideView;
        }
    }

    GameType GetGameType() {
        return _gameType;
    }

    Color colour;
    float speed = 100;
    float speedMult = 1;
private:
    void (Player::*_update)(float deltaTime, std::vector<GameObject*> objs, ObjectManager& objMan);
    GameType _gameType;
};

#endif /* SRC_GAMEOBJECT_GAMEOBJECTS_PLAYER_HPP */
