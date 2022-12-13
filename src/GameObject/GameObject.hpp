#ifndef SRC_GAMEOBJECT_GAMEOBJECT_HPP
#define SRC_GAMEOBJECT_GAMEOBJECT_HPP
#include <raylib.h>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <sstream>
#include "../../Math.hpp"

std::unordered_map<std::string, Texture2D> imgCache;
Texture2D GetTexture(std::string imgName) {
    std::unordered_map tmp = imgCache;
    std::string imgPath = ((std::string)"Textures/" + imgName);
    return imgCache.at(imgPath);
}

void LoadImagesToCache() {
    for (auto entry : std::filesystem::directory_iterator("Textures/")) {
        imgCache.emplace(entry.path(), LoadTexture(entry.path().c_str()));
    }

    std::unordered_map tmp = imgCache;
}

void DrawTexture(Math::Rect<float> rect, std::string texName) {
    Texture2D texture = GetTexture(texName);
    DrawTexturePro(texture,
        { 0, 0, (float)texture.width, (float)texture.height },
        { rect.x, rect.y, rect.w, rect.h },
        { 0, 0 }, 0, WHITE);
}

void DrawTextureTiled(Math::Rect<float> rect, std::string texName, Math::Vec2<float> tileSize) {
    Texture2D texture = GetTexture(texName);
    for (float i = 0; i < rect.w; i += tileSize.x) {
        for (float j = 0; j < rect.h; j += tileSize.y) {
            Math::Vec2<float> ratio = { 1, 1 };

            if (tileSize.x > rect.w-i) ratio.x = (rect.w-i)/tileSize.x;
            if (tileSize.y > rect.h-j) ratio.y = (rect.h-j)/tileSize.y;

            DrawTexturePro(texture,
                { 0, 0, ratio.x*texture.width, ratio.y*texture.height },
                { rect.x+i, rect.y+j, ratio.x*tileSize.x, ratio.y*tileSize.y },
                { 0, 0 }, 0, WHITE);
        }
    }
}

enum ObjectIDs {
    GAMEOBJECT = 0,
    PLAYER = 1,
    COLOUREDTILE = 2,
    TEXTUREDTILE = 3
};

class ObjectManager;
class GameObject {
public:
    GameObject() {}
    GameObject(Math::Rect<float> rect, int objID, bool collides = false) : rect(rect), objID(objID) {}
    virtual ~GameObject() {}

    virtual void update(float deltaTime, std::vector<GameObject*> objs, ObjectManager& objMan) {};
    virtual void interact(float deltaTime) {};
    virtual void render(float deltaTime, Math::Vec2<float> screenRatio) {};
    virtual std::string serialize() { return NULL; };
    virtual void deserialize(std::string data) {};

    Math::Rect<float> rect;
    bool collides;
    int objID = 0;
};

#endif /* SRC_GAMEOBJECT_GAMEOBJECT_HPP */
