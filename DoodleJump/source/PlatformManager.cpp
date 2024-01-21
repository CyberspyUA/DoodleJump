#include "PlatformManager.h"
#include "Platforms/BreakablePlatform.h"
#include "Platforms/DissapearingPlatform.h"
#include "Platforms/MovablePlatform.h"

void PlatformManager::generateRandomPlatforms(int numPlatforms, int platformWidth, int platformHeight)
{
		platforms.clear();  // Clear existing platforms
        for (int i = 0; i < numPlatforms; ++i) {
            int x = rand() % (screenWidth - 50);  // Replace 50 with the desired platform width
            int y = rand() % (screenHeight - 20);  // Replace 20 with the desired platform height

            // Randomly choose the platform type
            int platformType = rand() % 4;

            switch (platformType) {
                case 0:
                    platforms.push_back(new RegularPlatform(50, 20, x, y));  // Replace with actual dimensions
                    break;
                case 1:
                    platforms.push_back(new BreakablePlatform( 50, 20, x, y));  // Replace with actual dimensions
                    break;
                case 2:
                    platforms.push_back(new MovablePlatform(x, y, 50, 20, x + 100, y, 3));  // Replace with actual dimensions and destination
                    break;
                case 3:
                    platforms.push_back(new DissapearingPlatform(x, y, 50, 20));  // Replace with actual dimensions
                    break;
                // Add more cases for other platform types
            }
        }
}

void PlatformManager::drawPlatforms()
{
	for (const auto& platform : platforms) 
    {
		drawSprite(nullptr, platform.getX(), platform.getY());  // Replace nullptr with the actual platform sprite
    }
}
