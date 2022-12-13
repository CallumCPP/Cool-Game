#ifndef SRC_OBJECTMANAGER_HPP
#define SRC_OBJECTMANAGER_HPP
#include <vector>
#include <fstream>
#include "GameObject/GameObject.hpp"
#include "GameObject/GameObjects.hpp"

class ObjectManager {
public:
    ObjectManager(Math::Vec2<float> screenRatio) : _screenRatio(screenRatio) {}

    int AddToLow(GameObject* obj) {
        _lowLayer.push_back(obj);
        return _lowLayer.size()-1;
    }

    int AddToMid(GameObject* obj) {
        _midLayer.push_back(obj);
        return _midLayer.size()-1;
    }

    int AddToTop(GameObject* obj) {
        _topLayer.push_back(obj);
        return _topLayer.size()-1;
    }

    void update(float deltaTime) {
        for (int i = 0; i < _lowLayer.size(); i++) _lowLayer.at(i)->update(deltaTime, _lowLayer, *this);
        for (int i = 0; i < _midLayer.size(); i++) _midLayer.at(i)->update(deltaTime, _midLayer, *this);
        _player.update(deltaTime, _midLayer, *this);
        for (int i = 0; i < _topLayer.size(); i++) _topLayer.at(i)->update(deltaTime, _topLayer, *this);
    }

    void render(float deltaTime) {
        for (int i = 0; i < _lowLayer.size(); i++) _lowLayer.at(i)->render(deltaTime, _screenRatio);
        for (int i = 0; i < _midLayer.size(); i++) _midLayer.at(i)->render(deltaTime, _screenRatio);
        _player.render(deltaTime, _screenRatio);
        for (int i = 0; i < _topLayer.size(); i++) _topLayer.at(i)->render(deltaTime, _screenRatio);
    }

    void clear() {
        for (int i = 0; i < _lowLayer.size(); i++) delete _lowLayer.at(i);
        for (int i = 0; i < _midLayer.size(); i++) delete _midLayer.at(i);
        for (int i = 0; i < _topLayer.size(); i++) delete _topLayer.at(i);

        _lowLayer.clear();
        _midLayer.clear();
        _topLayer.clear();
    }

    void loadLevel(std::string lvlName) {
        clear();
        std::fstream lvlFile("Levels/" + lvlName + ".lvl");

        std::string line;
        int lineNum = 0;
        while (getline(lvlFile, line)) {
            if (lineNum == 3) break;
            int splitPos;
            while ((splitPos = line.find(';')) != std::string::npos) {
                std::string objStr = line.substr(0, splitPos);
                GameObject* obj;
                switch (atoi(objStr.substr(0, objStr.find(',')).c_str())) {
                    case COLOUREDTILE:
                        obj = new ColouredTile;
                        obj->deserialize(objStr.substr(objStr.find(',')+1));
                        break;

                    case TEXTUREDTILE:
                        obj = new TexturedTile;
                        obj->deserialize(objStr.substr(objStr.find(',')+1));
                        break;
                };

                switch (lineNum) {
                    case 0:
                        AddToLow(obj);
                        break;
                    
                    case 1:
                        AddToMid(obj);
                        break;

                    case 2:
                        AddToTop(obj);
                        break;
                };

                line = line.substr(splitPos+1);
            }

            lineNum++;
        } _player.gameType = (GameType)atoi(line.c_str());
    }

    void saveLevel(std::string lvlName) {
        std::fstream lvlFile("Levels/" + lvlName + ".lvl");
        for (auto obj : _lowLayer) lvlFile << obj->serialize();
        lvlFile << '\n';
        for (auto obj : _midLayer) lvlFile << obj->serialize();
        lvlFile << '\n';
        for (auto obj : _topLayer) lvlFile << obj->serialize();
        lvlFile << '\n';
        lvlFile << _player.gameType;

        lvlFile.close();
    }

    std::vector<GameObject*> GetLowLayer() {
       return _lowLayer;
    }

    std::vector<GameObject*> GetMidLayer() {
       return _midLayer;
    }

    std::vector<GameObject*> GetTopLayer() {
       return _topLayer;
    }

    Player* GetPlayer() {
        return &_player;
    }

    void SetPlayer(Player player) {
        _player = player;
    }

private:
    std::vector<GameObject*> _lowLayer;
    std::vector<GameObject*> _midLayer;
    std::vector<GameObject*> _topLayer;
    Math::Vec2<float> _screenRatio;
    Player _player;
};

#endif /* SRC_OBJECTMANAGER_HPP */
