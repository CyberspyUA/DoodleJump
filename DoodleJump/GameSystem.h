#pragma once
#include <Framework.h>
#include <vector>
class GameSystem
{
	private:
    void makeGameScene();
    int recordHeight_ = 0;

    SceneState state_ = SceneState::menu;

    Framework* win_;
    InputManager inputMan_;

    std::vector<Scene*> scenes_;
    MenuScene menuScene_;
    PauseScene pauseScene_;
    GameScene* gameScene_ = nullptr;
    GameoverScene* gameoverScene_ = nullptr;
};

