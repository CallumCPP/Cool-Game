#ifndef SRC_GAMEOBJECT_GAMEOBJECTS_TEXTUREDTILE_HPP
#define SRC_GAMEOBJECT_GAMEOBJECTS_TEXTUREDTILE_HPP
#include "../GameObject.hpp"

enum TileType {
    TILED = 0,
    STRETCHED
};

class TexturedTile : public GameObject {
public:
    TexturedTile() {}
    TexturedTile(Math::Rect<float> rect, std::string texName, Math::Vec2<float> tileSize, TileType type, bool collides = false) : 
    GameObject(rect, TEXTUREDTILE), texName(texName), tileSize(tileSize), type(type) { 
        this->collides=collides; 
    }

    TexturedTile(Math::Rect<float> rect, std::string texName, TileType type, bool collides = false) : 
    GameObject(rect, TEXTUREDTILE), texName(texName), tileSize(20, 20), type(type) { 
        this->collides=collides; 
    }

    void render(float deltaTime, Math::Vec2<float> screenRatio) override {
        Math::Rect<float> tmpRect = {
            rect.pos * screenRatio,
            rect.size * screenRatio
        };

        switch (type) {
            case TILED: {
                DrawTextureTiled(tmpRect, texName, tileSize);
                break;
            }
            case STRETCHED: {
                DrawTexture(tmpRect, texName);
                break;
            }
        };
    }

    std::string serialize() override {
        std::stringstream ss;
        ss << TEXTUREDTILE << ',';
        ss << rect.x << ',' << rect.y << ',' << rect.w << ',' << rect.h << ',';
        ss << texName << ',' << type << ',';
        ss << tileSize.x << ',' << tileSize.y << ',';
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

        texName = data.substr(0, data.find(','));
        data = data.substr(data.find(',')+1);

        type = (TileType)atoi(data.substr(0, data.find(',')).c_str());
        data = data.substr(data.find(',')+1);

        tileSize.x = atof(data.substr(0, data.find(',')).c_str());
        data = data.substr(data.find(',')+1);
        tileSize.y = atof(data.substr(0, data.find(',')).c_str());
        data = data.substr(data.find(',')+1);

        collides = atoi(data.substr(0, data.find(',')).c_str());
    }

    TileType type;
    std::string texName;
    Math::Vec2<float> tileSize;
};

#endif /* SRC_GAMEOBJECT_GAMEOBJECTS_TEXTUREDTILE_HPP */
