/*
 * Framework
 */
#include "Framework.h"
/*
 * C++ Standard library
 */
#include <iostream>
#include <cmath>
#include <vector>
/**
 * Game elements
 */
#include "source/Bullet/Bullet.h"
#include "source/Enemy/Enemy.h"
#include "source/Items/Spring.h"
#include "source/Items/Coin.h"
#include "source/Platforms/TempPlat.h"
/**
 * UI
 */
#include "source/GameUtilities/UI.h"

/**
 * Gameplay mechanics
 */
#include "source/GameUtilities/Gameplay.h"

/* Framework realization */
class ExtendedFramework : public Framework
{

private:
	/**
	 * Game stages bool variables
	 */
	bool started = false;
    bool play = true;
    bool goodForAgain = false;
    bool goodForStartGame = false;
	/**
	 * Player bool variables
	 */
	bool facingRight = true;
    bool facingLeft = false;
    bool facingUp = false;
    bool springed = false;
    bool isMovingRight = false;
    bool isMovingLeft = false;
    bool playerHitTempPlatform = false;
    bool isImmuneToFall = false;
	/**
	 * Player sprites
	 */
	Sprite *lookRight = nullptr;
    Sprite *lookLeft = nullptr;
    Sprite *lookUp = nullptr;
    Sprite *nose = nullptr;
	/**
	 * Platforms sprites
	 */
	Sprite *block = nullptr;
    Sprite *platformTemp = nullptr;
	/**
	 * UI sprites
	 */
	Sprite *background = nullptr;
    Sprite *playStart = nullptr;
    Sprite *backgroundlost = nullptr;
    Sprite *playagain = nullptr;
    Sprite *digits[10];
    Sprite *topscore = nullptr;
    Sprite *scoreWord = nullptr;
    Sprite *moneyBag = nullptr; // Icon left to the counter of collected coins.
	/**
	 * Bullet sprite
	 */
	Sprite *bulletspr = nullptr;
	/**
	 * Enemy sprite
	 */
	Sprite *enemy = nullptr;

	/**
	 * Items sprites
	 */
	Sprite *jumpSpring = nullptr;
    Sprite *coin = nullptr;
	/**
	 * Player numeric variables
	 */
	float playerx;
    float playery;
    float mousex, mousey;
    int  hPlayer, wPlayer;
    int lifes = 3;
    int wPlayStart, hPlayStart;
    /**
     *Engine numeric variables
     */
    float deltaY = 0, gravity = 500;
    float lastTick;
    float deltaTime;
	float springJumpHeight;
    float startSpring;
    float stopSpring;
    float startImmune;
    float stopImmune;
    int a[8][2];

	/**
	 * UI numeric variables 
	 */
	float gap;
    int Width, Height; // Screen Width and Height
    int score = 0;
    int scorepx = 0;
    int heightDigits[20], scoreDigits[20], coinDigits[10];
    int aux;
    int heightCounter = 0;
    int scoreCounter = 0;
    int wDigit, hDigit;
    int wButtonAgain;
    int hButtonAgain;
    int coinScore = 0;
    int coinCounter = 0;
    /**
     * Platform numeric variables
     */
    int wPlatform, hPlatform;
    int indTempPlatform;
    int indPlatformForCoinToRender;
    /**
     * Enemy numeric variables
     */
    int wEnemy, hEnemy;
    /**
     * Bullet numeric variables
     */
    int  wBullet, hBullet;
    /**
     * Items numeric variables
     */
    int wSpring, hSpring,  wCoin = 15, hCoin = 15;
	/**
	 * Structure variables
	 */
	std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    std::vector<Spring> springs;
    std::vector<TempPlat> tmplats;
    std::vector<Coin> coins;

public:
       
	/**
	 * \Preinitializing parameters and settings before running the framework.
	 * \param width - Window width
	 * \param height - Window height
	 * \param fullscreen - enable fullscreen mode?
	 */
	void PreInit(int &width, int &height, bool &fullscreen) override
    {
        std::cout << "Enter window width and height: (use space to split values)\n";
        std::cin >> width;
        std::cin >> height;
        fullscreen = false;
    }

    virtual bool Init()
    {
        /**
         * Initializing parameters
         */
        //Screen
        getScreenSize(Width, Height);
        //Player
        playerx = Width / 2;
        playery = Height / 2;
        lookRight = createSprite("data/Player/space-right.png");
        lookLeft = createSprite("data/Player/space-left.png");
        lookUp = createSprite("data/Player/space-puca.png");
        nose = createSprite("data/Player/jungle-njuska.png");
        //Scoreboard
        digits[0] = createSprite("data/ScoreBoard/zero.png");
        digits[1] = createSprite("data/ScoreBoard/one.png");
        digits[2] = createSprite("data/ScoreBoard/two.png");
        digits[3] = createSprite("data/ScoreBoard/three.png");
        digits[4] = createSprite("data/ScoreBoard/four.png");
        digits[5] = createSprite("data/ScoreBoard/five.png");
        digits[6] = createSprite("data/ScoreBoard/six.png");
        digits[7] = createSprite("data/ScoreBoard/seven.png");
        digits[8] = createSprite("data/ScoreBoard/eight.png");
        digits[9] = createSprite("data/ScoreBoard/nine.png");
        topscore = createSprite("data/ScoreBoard/score_board.png");
        scoreWord = createSprite("data/ScoreBoard/score.png");
        moneyBag = createSprite("data/ScoreBoard/money-bag.png");
        //Projectile
        bulletspr = createSprite("data/Player/meteor.png");
        //Platforms
        block = createSprite("data/Platforms/RegularPlatform.png");
        platformTemp = createSprite("data/Platforms/VanishingPlatform.png");
        //Background
        background = createSprite("data/Background/space-bck@2x.png");
        //Items
        jumpSpring = createSprite("data/Items/springIdle.png");
        coin = createSprite("data/Items/coin.png");
        //Enemy
        enemy = createSprite("data/Enemies/RadarMonster.png");
        playStart = createSprite("data/UI/play.png");
        setSpriteSize(background, Width, Height);
        setSpriteSize(topscore, Width, Height / 15);
        playagain = createSprite("data/UI/play-again-on.png");
        getSpriteSize(playagain, wButtonAgain, hButtonAgain);
        getSpriteSize(lookRight, wPlayer, hPlayer);
        getSpriteSize(block, wPlatform, hPlatform);
        getSpriteSize(enemy, wEnemy, hEnemy);
        getSpriteSize(bulletspr, wBullet, hBullet);
        getSpriteSize(digits[9], wDigit, hDigit);
        getSpriteSize(jumpSpring, wSpring, hSpring);
        getSpriteSize(playStart, wPlayStart, hPlayStart);
        getSpriteSize(coin, wCoin, hCoin);
        int platformCount = 9;
        gap = (float)(Height / platformCount);
        generatePlatforms(a, gap, Width, Height, wPlatform);
        deltaTime = 0;
        lastTick = getTickCount();
        lifes = 3;
        springJumpHeight = 1;
        return true;
    }

    virtual void Close()
    {
    }

	

    virtual bool Tick()
    {
        /**
         * If player started the game
         */
        if (started)
        {
            /**
             * If player pressed play button - entering the game.
             */
            if (play == true)
            {
                /**
                 * Drawing top UI
                 */
                deltaTime = (getTickCount() - lastTick) / 1000.0f;
                if (deltaTime > 0.015)
                    deltaTime = 0.015;
                lastTick = getTickCount();
                drawSprite(background, 0, 0);
                drawSprite(topscore, 0, 0);
                drawSprite(scoreWord, 0, 0);
                drawSprite(moneyBag, 300, 0);
                for (int i = 1; i <= 6; i++)
                    drawSprite(block, a[i][0], a[i][1]);
                scoreCounter = 0;
                numberToDigits(score, heightDigits, scoreCounter);

                for (int i = scoreCounter - 1; i >= 0; i--)
                {
                    drawSprite(digits[heightDigits[i]], Width / 5 - i * 25, 7);
                }

                heightCounter = 0;
                numberToDigits(scorepx, scoreDigits, heightCounter);

                for (int i = heightCounter - 1; i >= 0; i--)
                {
                    drawSprite(digits[scoreDigits[i]], Width - i * 25 - (wDigit + wDigit / 2), 7);
                }
                RenderEnemies(enemies, enemy);
                /**
                 * Rendering springs
                 */
                for (int i = 0; i < springs.size(); i++)
                {
                    drawSprite(jumpSpring, springs[i].x, springs[i].y);
                }
                /**
                 * Rendering temporary platforms
                 */
                for (int i = 0; i < tmplats.size(); i++)
                {
                    drawSprite(platformTemp, tmplats[i].x, tmplats[i].y);
                }
                /**
                 * Rendering coins
                 */
                renderCoins(coins, coin, wPlatform, hPlatform);
                /**
                 * Hitting the platform gameplay mechanic.
                 * Player jumps off a platform, and the score is increased
                 */
                
                for (int i = 1; i <= 6; i++)
                {
                    if ((floor(playery + hPlayer) == a[i][1] + 3 || floor(playery + hPlayer) == a[i][1] + 1 || floor(playery + hPlayer) == a[i][1] + 2 || floor(playery + hPlayer) == a[i][1] + 5 || floor(playery + hPlayer) == a[i][1] + 4 || floor(playery + hPlayer) == a[i][1] + 6) && floor(playerx) >= a[i][0] - wPlayer + 25 && floor(playerx) <= a[i][0] + wPlatform - 20 && deltaY > 0)
                    {
                        deltaY = -(800) * springJumpHeight;
                        score += 1;
                        scorepx += Height - a[i][1];
                    }
                }
                 /**
                 * Player jumps off a temporary platform.
                 */
                
                for (int i = 0; i < tmplats.size(); i++)
                {
                    if ((floor(playery + hPlayer) == tmplats[i].y + 3 || floor(playery + hPlayer) == tmplats[i].y + 1 || floor(playery + hPlayer) == tmplats[i].y + 2 || floor(playery + hPlayer) == tmplats[i].y + 5 || floor(playery + hPlayer) == tmplats[i].y + 4 || floor(playery + hPlayer) == tmplats[i].y + 6) && floor(playerx) >= tmplats[i].x - wPlayer + 25 && floor(playerx) <= tmplats[i].x + wPlatform - 20 && deltaY > 0)
                    {
                        deltaY = -(800) * springJumpHeight;
                        score += 1;
                        scorepx += Height - a[i][1];
                    }
                }

                deltaY += gravity * deltaTime;
                playery += deltaY * deltaTime;

                /**
                 * Calculations for the doodle.
                 */
                if (deltaTime < 0.002)
                {
                    if (deltaY * 0.002 > -0.7 && deltaY < 0)
                    {
                        deltaY = -deltaY;
                    }
                }
                else if (deltaTime > 0.004)
                {
                    if (deltaY * 0.004 > -0.7 && deltaY < 0)
                    {
                        deltaY = -deltaY;
                    }
                }
                else
                {
                    if (deltaY * deltaTime > -0.7 && deltaY < 0)
                    {
                        deltaY = -deltaY;
                    }
                }

                /**
                 *  Spring ability last for 1 seconds, after that spring is set to 1,
                 *  the jump speed being multiplied by spring it will come back to normal after setting it to 1
                 *  and it will speed up when the spring boots is on.
                 */
                if (springed == true)
                {
                    if ((getTickCount() - startSpring) / 1000 > 1)
                    {
                        springed = false;
                        springJumpHeight = 1;
                        stopSpring = getTickCount();
                    }
                }
                /**
                 * Immune ability for 20 seconds.
                 * It lasts for 20 seconds.
                 * The player can’t fall (they will jump off the bottom side of the screen).
                 * However, they can still die from enemies.
                 */
                 if (isImmuneToFall == true)
                 {
                    if ((getTickCount() - startImmune) / 1000 > 20)
                    {
                        
                        stopImmune = getTickCount();
                    }
                    else
                    {
	                    destroySprite(lookLeft);
			            destroySprite(lookRight);
			            destroySprite(lookUp);
                        lookRight = createSprite("data/Player/space-right.png");
						lookLeft = createSprite("data/Player/space-left.png");
						lookUp = createSprite("data/Player/space-puca.png");
                        isImmuneToFall = false;
                    }
                 }
                /**
                 * Game view adjust method.
                 * Keep the player at max the center of the screen
                 * and making it seem like he is going up, and platforms down.
                 */
                if (playery < Height / 2)
                {
                    /**
                     * Keep the player at the max center of the screen
                     */
                    playery = Height / 2;
                    for (int i = 1; i <= 6; i++)
                    {
                        /**
                         * Move the platforms down
                         */
                        a[i][1] -= deltaY * deltaTime;
                        if (a[i][1] > Height)
                        {
                            /**
                             * Erase the enemy from the platform that got off the screen.
                             */
                            for (int j = 0; j < enemies.size(); j++)
                                if (enemies[j].platformID == i)
                                    enemies.erase(enemies.begin() + j);
                            /**
                             * Erase the spring from the paltform that got off the screen.
                             */
                            for (int j = 0; j < springs.size(); j++)
                                if (springs[j].platformID == i)
                                    springs.erase(springs.begin() + j);

                            score += 1;
                            a[i][1] = 0;
                            if (a[i - 1][0] > Width / 2)
                                a[i][0] = rand() % (Width / 2 - wPlatform);
                            else
                                a[i][0] = rand() % (Width / 2 - wPlatform) + Width / 2;

                            int randCoin = rand() % 100;
					        // 5% chance of generating a coin on the platform
					        if (randCoin < 50) {
					            Coin newCoin = { a[i][0] + wPlatform / 2, a[i][1] - hPlatform, i, true };
					            coins.push_back(newCoin);
					        }
                            int randPlatTemp = rand() % 999;
                            // 10% of time a platform will be created
                            if (randPlatTemp < 100)
                            {
                                TempPlat newPlatform = {rand() % (Width - wPlatform), a[i][1] + hPlatform + rand() % ((int)gap - 2 * hPlatform), getTickCount()};
                                tmplats.push_back(newPlatform);
                            }
                            int random = rand() % 999;
                            // 6% of time an enemy will be created
                            if (random < 60)
                            {
                                Enemy newEnemy = {a[i][0] + wPlatform / 2 - wEnemy / 2, a[i][1] - hEnemy, i};
                                enemies.push_back(newEnemy);
                            }
                            
                            if ((getTickCount() - startSpring) / 1000 > 1 && (getTickCount() - stopSpring) / 1000 > 1)
                            {
                                int randomSpring = rand() % 999;
                                // 1% of time spring will be created
                                if (randomSpring < 60 && random > 60)
                                {
                                    Spring newSpring = {a[i][0] + wPlatform / 2 - wSpring / 2, a[i][1] - hSpring, i};
                                    springs.push_back(newSpring);
                                }
                            }
                            
                        }

                        /**
                         * Enemy moves down with the platform it belongs to
                         */
                        for (int j = 0; j < enemies.size(); j++)
                            enemies[j].y = a[enemies[j].platformID][1] - hEnemy;
                        /**
                         * Spring moves down with the platform it belongs to
                         */
                        for (int j = 0; j < springs.size(); j++)
                            springs[j].y = a[springs[j].platformID][1] - hSpring;
                        
                    }
                     /**
                      * Temp platforms move down
                      */
                    for (int i = 0; i < tmplats.size(); i++)
                        tmplats[i].y -= deltaY * deltaTime;
                }

                renderBullets(bullets, deltaTime, bulletspr);

                bulletDestroysEnemy(bullets, enemies, wEnemy, hEnemy, wBullet);

                playerInteractWithEnemy(enemies, playerx, playery, wPlayer, hPlayer, wEnemy, hEnemy, deltaY, play);

                playerInteractWithSpring(springs, playerx, playery, wPlayer, hPlayer, wSpring, hSpring, deltaY, springed, springJumpHeight, startSpring);

                playerInteractWithTempPlat(tmplats, playerx, playery, wPlayer, hPlayer, deltaY, springJumpHeight, playerHitTempPlatform, wPlatform, hPlatform);

                playerInteractWithCoin(coins, playerx, playery, wPlayer, hPlayer, score, coinScore);
                std::cout << "Coins claimed: " << coinScore << "\n";
                for (int j = 0; j < coins.size(); j++)
				coins[j].y = a[coins[j].platformID][1] - hCoin;
                /**
                 * Remove temporary if:
                 *  1) Player jumped on the temporary platform, so it can be deleted.
                 *  2) Platforms out of the screen;
                 */
                std::vector<int> indicesToRemove;

				for (int i = 0; i < tmplats.size(); i++)
				{
				    if(playerHitTempPlatform && tmplats[i].isPlatformUsed)
				    {
				        indicesToRemove.push_back(i);
                        playerHitTempPlatform = false;
				    }
				    if (tmplats[i].y > Height)
				        indicesToRemove.push_back(i);
				}

				// Remove elements marked for removal in reverse order
				for (int i = indicesToRemove.size() - 1; i >= 0; i--)
				{
				    tmplats.erase(tmplats.begin() + indicesToRemove[i]);
				}
				/**
				 * In case: player is out of the screen - he appears on the other side.
				 */
                if (playerx + wPlayer > Width)
                    playerx = 0;
                else if (playerx + wPlayer < 0)
                    playerx = Width - wPlayer;

               /**
                * Left-Right moving
                */
                if (isMovingRight)
                {
                    playerx += 300 * deltaTime;
                    /**
                     * First major task. The player moves faster by 50% while on the right side.
                     */
                    if( playerx >= Width/2.0f)
                    {
	                    playerx += 600 * deltaTime;
                    }
                }
                if (isMovingLeft)
                {
                    playerx -= 300 * deltaTime;
                }
                /**
                 * If player is not shooting, draw a sprite where it is facing
                 */
                if (!bullets.size())
                {
                    if (facingRight)
                        drawSprite(lookRight, playerx, playery);
                    else if (facingLeft)
                        drawSprite(lookLeft, playerx, playery);
                }
                /**
                 * Else, draw the nose up and change sprite to looking up
                 */
                else
                {
                    drawSprite(lookUp, playerx, playery);
                    drawSprite(nose, playerx + wPlayer / 2.5, playery);
                }
                /**
                 * Player has 3 lifes, if it falls down, it loses one life
                 * and it gets spawned on the lowest platform.
                 */
                if (playery > Height - hPlayer)
                {
                    if(isImmuneToFall == false)
						lifes--;
                    for (int i = 1; i <= 6; i++)
                    {
                        if (a[i][1] < Height && a[i][1] > Height - (Height / 4))
                        {
                            playery = a[i][1] - 2 * hPlayer;
                            playerx = a[i][0] + wPlatform / 2 - wPlayer / 2;
                        }
                    }
                }
                /**
                 * If player loses all lifes, he lost, and after that it can play again
                 */
                if (lifes == 0)
                    play = false;
                std::cout << "Lifes: " << lifes << "\n";
            }
            if (play == false)
            {
                /**
                 * Draw play the again screen
                 */
                drawSprite(background, 0, 0);
                drawSprite(topscore, 0, 0);
                drawSprite(scoreWord, 0, 0);
                drawSprite(playagain, Width / 3, Height / 2);
                scoreCounter = 0;
                numberToDigits(score, heightDigits, scoreCounter);

                for (int i = scoreCounter - 1; i >= 0; i--)
                {
                    drawSprite(digits[heightDigits[i]], Width / 3 - i * 25, 10);
                }

                heightCounter = 0;
                numberToDigits(scorepx, scoreDigits, heightCounter);

                for (int i = heightCounter - 1; i >= 0; i--)
                {
                    drawSprite(digits[scoreDigits[i]], Width - i * 25 - (wDigit + wDigit / 2), 10);
                }
            }
        }
        else
        {
            drawSprite(background, 0, 0);
            drawSprite(playStart, Width / 2 - wPlayStart / 2, Height / 2 - hPlayStart / 2);
        }
        return false;
    }

    void onMouseMove(int x, int y, int xrelative, int yrelative) override
    {
        if (x >= Width / 3 && x <= Width / 3 + wButtonAgain && y >= Height / 2 && y <= Height / 2 + hButtonAgain && play == false)
            goodForAgain = true;
        else
            goodForAgain = false;
        if (x >= Width / 2 - wPlayStart / 2 && x <= Width / 2 + wPlayStart && y >= Height / 2 - hPlayStart / 2 && y <= Height / 2 + hPlayStart / 2 && started == false)
            goodForStartGame = true;
        mousex = x;
        mousey = y;
    }

    void onMouseButtonClick(FRMouseButton button, bool isReleased) override
    {
        // Level Start
        if (button == FRMouseButton::LEFT && goodForStartGame == true && started == false)
            started = true;
        // Level Restart
        if (button == FRMouseButton::LEFT && goodForAgain == true && play == false)
        {
            play = true;
            playerx = Width / 2;
            playery = Height / 2;
            bullets.clear();
            enemies.clear();
            springs.clear();
            tmplats.clear();
            deltaY = 0;
            gravity = 500;
            score = 0;
            scorepx = 0;
            coinScore = 0;
            int platformCount = 9;
            const float gap = (float)(Height / platformCount);
            generatePlatforms(a, gap, Width, Height, wPlatform);
            lifes = 3;
            springJumpHeight = 1;
            springed = false;
            /**
             *Restart immune ability
             */
            isImmuneToFall = false;
        	destroySprite(lookLeft);
            destroySprite(lookRight);
            destroySprite(lookUp);
            lookLeft = createSprite("data/Player/space-left.png");
            lookRight = createSprite("data/Player/space-right.png");
            lookUp = createSprite("data/Player/space-puca.png");
        }
        // Shoot projectile
        if (button == FRMouseButton::LEFT && isReleased == true)
        {
            Bullet newBullet = {playerx, playery, -700, -700, true, mousex};
            bullets.push_back(newBullet);
        }
        if(button == FRMouseButton::RIGHT && coinScore >= 20)
        {
            destroySprite(lookLeft);
            destroySprite(lookRight);
            destroySprite(lookUp);
            lookLeft = createSprite("data/Player/shield-space-left.png");
            lookRight = createSprite("data/Player/shield-space-right.png");
            lookUp = createSprite("data/Player/shield-space-puca.png");
            coinScore-= 20;
	        isImmuneToFall = true;
        }
    }

    void onKeyPressed(FRKey k) override
    {
        if (k == FRKey::RIGHT)
        {
            facingRight = true;
            facingLeft = false;
            isMovingRight = true;
        }
        else if (k == FRKey::LEFT)
        {
            facingRight = false;
            facingLeft = true;
            isMovingLeft = true;
        }
    }

    void onKeyReleased(FRKey k) override
    {
        if (k == FRKey::RIGHT)
            isMovingRight = false;
        else if (k == FRKey::LEFT)
            isMovingLeft = false;
    }

	const char *GetTitle() override
    {
        return "Doodle Jump";
    }
};

int main(int argc, char *argv[])
{
    return run(new ExtendedFramework);
}