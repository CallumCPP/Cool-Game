#ifndef SRC_GAMEOBJECT_GAMEOBJECTS_COLOUREDTILE_HPP
#define SRC_GAMEOBJECT_GAMEOBJECTS_COLOUREDTILE_HPP
#include "../GameObject.hpp"

class ColouredTile : public GameObject {
public:
    ColouredTile() {}
    ColouredTile(Math::Rect<float> rect, Color colour, bool collides = false) : GameObject(rect, COLOUREDTILE), colour(colour) { this->collides=collides; }

    void render(float deltaTime, Math::Vec2<float> screenRatio) override {
        Math::Rect<float> tmpRect = {
            rect.pos * screenRatio,
            rect.size * screenRatio
        };

        DrawRectangleRec({ tmpRect.x, tmpRect.y, tmpRect.w, tmpRect.h }, colour);
    }

    std::string serialize() override {
        std::stringstream ss;
        ss << COLOUREDTILE << ',';
        ss << rect.x << ',' << rect.y << ',' << rect.w << ',' << rect.h << ',';
        ss << (int)colour.r << ',' << (int)colour.g << ',' << (int)colour.b << ',' << (int)colour.a << ',';
        ss << collides << ';';

        return ss.str();
    }

    void deserialize(std::string data) override {
        rect.x = atof(data.substr(0, data.find(',')).c_str());
        data = data.substr(data.find(',')+1);
        rect.y = atof(data.substr(0, data.find(',')).c_str());
        data = data.substr(data.find(',')+1);
        rect.w = atof(data.substr(0, data.find(',')).c_str());
        data = data.substr(data.find(',')+1);
        rect.h = atof(data.substr(0, data.find(',')).c_str());
        data = data.substr(data.find(',')+1);

        colour.r = atoi(data.substr(0, data.find(',')).c_str());
        data = data.substr(data.find(',')+1);
        colour.g = atoi(data.substr(0, data.find(',')).c_str());
        data = data.substr(data.find(',')+1);
        colour.b = atoi(data.substr(0, data.find(',')).c_str());
        data = data.substr(data.find(',')+1);
        colour.a = atoi(data.substr(0, data.find(',')).c_str());
        data = data.substr(data.find(',')+1);

        collides = atoi(data.substr(0, data.find(',')).c_str());
    }

    Color colour;
};

#endif /* SRC_GAMEOBJECT_GAMEOBJECTS_COLOUREDTILE_HPP */
