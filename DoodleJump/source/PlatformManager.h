#pragma once
#include <vector>
#include "Framework.h"
#include "Platforms/RegularPlatform.h"

class PlatformManager
{
	private:
    std::vector<RegularPlatform> platforms;
    int screenWidth, screenHeight;

public:
    PlatformManager(int screenW, int screenH) : screenWidth(screenW), screenHeight(screenH) {}

    void generateRandomPlatforms(int numPlatforms, int platformWidth, int platformHeight);

    void drawPlatforms();
};

