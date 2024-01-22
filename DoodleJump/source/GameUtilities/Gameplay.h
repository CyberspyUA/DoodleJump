#pragma once
/**
 * \brief Level generator
 * \param a - matrix that represents screen, where game object can be placed. 
 * \param gap - float value, used to represent a gap between platforms.
 * \param Width - screen width
 * \param Height - screen height
 * \param wPlatform - platform weight
 */
inline void generatePlatforms(int a[][2], float gap, int Width, int Height, int wPlatform)
{
    srand(time(NULL));
    a[1][0] = Width / 2;
    a[1][1] = Height - 60;
    for (int i = 2; i <= 6; i++)
    {
        if (a[i - 1][0] > Width / 2)
            a[i][0] = rand() % (Width / 2 - wPlatform);
        else
            a[i][0] = rand() % (Width / 2 - wPlatform) + Width / 2;
        a[i][1] = (gap * i) - gap;
    }
}

/**
 * \brief Destroying the enemy when bullet hit the enemy
 * \param bullets 
 * \param enemies 
 * \param wEnemy 
 * \param hEnemy 
 * \param wBullet 
 */
inline void bulletDestroysEnemy(std::vector<Bullet> &bullets, std::vector<Enemy> &enemies, int wEnemy, int hEnemy, int wBullet)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        for (int j = 0; j < enemies.size(); j++)
        {
            if (bullets[i].x >= enemies[j].x && bullets[i].x - wBullet <= enemies[j].x + wEnemy && bullets[i].y >= enemies[j].y && bullets[i].y <= enemies[j].y + hEnemy)
            {
                enemies.erase(enemies.begin() + j);
                bullets.erase(bullets.begin() + i);
            }
        }
    }
}

inline void playerInteractWithEnemy(std::vector<Enemy> &enemies, float playerx, float playery, int wPlayer, int hPlayer, int wEnemy, int hEnemy, float dy, bool &play)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        if (floor(playerx) >= enemies[i].x - wPlayer && floor(playerx) <= enemies[i].x + wEnemy)
        {
            if ((floor(playery + hPlayer) == enemies[i].y + 3 || floor(playery + hPlayer) == enemies[i].y + 1 || floor(playery + hPlayer) == enemies[i].y + 2 || floor(playery + hPlayer) == enemies[i].y + 5 || floor(playery + hPlayer) == enemies[i].y + 4 || floor(playery + hPlayer) == enemies[i].y + 6) && dy > 0)
            {
                enemies.erase(enemies.begin() + i);
            }
            else if ((floor(playery + hPlayer) == enemies[i].y + hEnemy + 3 || floor(playery + hPlayer) == enemies[i].y + hEnemy + 1 || floor(playery + hPlayer) == enemies[i].y + hEnemy + 2 || floor(playery + hPlayer) == enemies[i].y + hEnemy + 5 || floor(playery + hPlayer) == enemies[i].y + hEnemy + 4 || floor(playery + hPlayer) == enemies[i].y + hEnemy + 6) && dy < 0)
            {
                play = false;
            }
        }
    }
}

inline void playerInteractWithSpring(std::vector<Spring> &springs, float playerx, float playery, int wPlayer, int hPlayer, int wEnemy, int hEnemy, float dy, bool &springed, float &spring, float &startSpring)
{
    for (int i = 0; i < springs.size(); i++)
    {
        if (floor(playerx) >= springs[i].x - wPlayer && floor(playerx) <= springs[i].x + wEnemy)
        {
            if ((floor(playery + hPlayer) == springs[i].y + 3 || floor(playery + hPlayer) == springs[i].y + 1 || floor(playery + hPlayer) == springs[i].y + 2 || floor(playery + hPlayer) == springs[i].y + 5 || floor(playery + hPlayer) == springs[i].y + 4 || floor(playery + hPlayer) == springs[i].y + 6) && dy > 0)
            {
                springs.erase(springs.begin() + i);
                springed = true;
                spring = 1.5;
                startSpring = getTickCount();
            }
        }
    }
}

inline void playerInteractWithCoin(std::vector<Coin>& coins, float playerx, float playery, int wPlayer, int hPlayer, int score) {
    for (int i = 0; i < coins.size(); i++) {
        if (coins[i].isActive &&
            playerx + wPlayer > coins[i].x &&
            playerx < coins[i].x &&
            playery + hPlayer > coins[i].y &&
            playery < coins[i].y) {
            // Player collected the coin
            coins[i].isActive = false;
            score += 100;
        }
    }
}


inline void playerInteractWithTempPlat(std::vector<TempPlat>& tmplats, float playerx, float playery, int wPlayer, int hPlayer, float& dy, float spring, bool& didPlayerHitPlatform, int wPlatform, int hPlatform)
{
    for (int i = 0; i < tmplats.size(); i++)
    {
        if (tmplats[i].isPlatformUsed &&
	    playerx + wPlayer > tmplats[i].x &&
	    playerx < tmplats[i].x + wPlatform &&
	    playery + hPlayer > tmplats[i].y &&
	    playery < tmplats[i].y + hPlatform)
			{
			    didPlayerHitPlatform = true;
			    // Jump off the temporary platform
			    dy = -(800) * spring;
			    // Set the temporary platform as used
			    tmplats[i].isPlatformUsed = true;
			}
    }
}
inline void renderBullets(std::vector<Bullet> &bullets, float dt, Sprite *bulletspr)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        Bullet &bullet = bullets[i];
        if (bullet.isActive)
        {
            float angle = atan2(bullet.y, bullet.x - bullet.mouseX);
            bullet.y += bullet.deltaY * dt * sin(angle);
            bullet.x += bullet.deltaX * dt * cos(angle);
            drawSprite(bulletspr, bullet.x, bullet.y);
            if (bullet.y < 0)
            {
                bullet.isActive = false;
                bullets.erase(bullets.begin() + i);
                i--;
            }
        }
    }
}
inline void renderCoins(std::vector<Coin>& coins, Sprite* coinSprite, int wPlatform, int hPlatform)
{
    for (int i = 0; i < coins.size(); i++)
    {
        if (coins[i].isActive)
        {
            // Check if the coin is on a platform and render accordingly
            if (coins[i].platformID >= 1 && coins[i].platformID <= 3)
            {
                int platformX = coins[i].x - wPlatform / 2;
                int platformY = coins[i].y + hPlatform;
                drawSprite(coinSprite, platformX, platformY);
                std::cout << "X: " << platformX << "Y: " << platformY << "\n";
          
            }
            else
            {
                // Render the coin as usual
                drawSprite(coinSprite, coins[i].x, coins[i].y);
            }
        }
    }
}
inline void RenderEnemies(std::vector<Enemy>&enemies, Sprite* enemy)
{
	/**
    * Rendering enemies
    */
	for (int i = 0; i < enemies.size(); i++)
	{
		drawSprite(enemy, enemies[i].x, enemies[i].y);
	}
}

inline void updateCoinPositions(std::vector<Coin>& coins, float dy, float dt)
{
    for (int i = 0; i < coins.size(); i++)
    {
        if (coins[i].isActive)
        {
            coins[i].y -= dy * dt;
        }
    }
}