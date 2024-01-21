/*
 * Framework
 */
#include "Framework.h"
/*
 * C++ Standart library
 */
#include <iostream>
#include <cmath>
#include <ctime>
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
    bool started = false;
    bool play = true;
    bool facingRight = true;
    bool facingLeft = false;
    bool facingUp = false;
    bool springed = false;
    bool isMovingRight = false;
    bool isMovingLeft = false;
    bool goodForAgain = false;
    bool goodForStartGame = false;
    Sprite *lookRight = nullptr;
    Sprite *lookLeft = nullptr;
    Sprite *lookUp = nullptr;
    Sprite *background = nullptr;
    Sprite *block = nullptr;
    Sprite *backgroundlost = nullptr;
    Sprite *playagain = nullptr;
    Sprite *digits[10];
    Sprite *bulletspr = nullptr;
    Sprite *nose = nullptr;
    Sprite *enemy = nullptr;
    Sprite *topscore = nullptr;
    Sprite *scoreWord = nullptr;
    Sprite *jumpspring = nullptr;
    Sprite *platformTemp = nullptr;
    Sprite *playStart = nullptr;
    Sprite *coin = nullptr;
    float playerx;
    float playery;
    float mousex, mousey;
    float dy = 0, grav = 500;
    float gap;
    int wPlatform, hPlatform, hPlayer, wPlayer, wButtonAgain, hButtonAgain;
    int a[8][2];
    int Width, Height;
    float dt;
    float spring;
    float lastTick;
    float startSpring;
    float stopSpring;
    int score = 0;
    int scorepx = 0;
    int firstDigit[20], secondDigit[20];
    int aux, firstCounter = 0, secondCounter = 0;
    int lifes = 3;
    int wEnemy, hEnemy, wBullet, hBullet, wDigit, hDigit, wSpring, hSpring, wPlayStart, hPlayStart, wCoin = 15, hCoin = 15;
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    std::vector<Spring> springs;
    std::vector<TempPlat> tmplats;
    std::vector<Coin> coins;

public:
    virtual void PreInit(int &width, int &height, bool &fullscreen)
    {

        fullscreen = false;
    }

    virtual bool Init()
    {
        /**
         * Preinitializing parameters
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
        //Projectile
        bulletspr = createSprite("data/Player/meteor.png");
        //Platforms
        block = createSprite("data/Platforms/RegularPlatform.png");
        platformTemp = createSprite("data/Platforms/VanishingPlatform.png");
        //Background
        background = createSprite("data/Background/space-bck@2x.png");
        //Items
        jumpspring = createSprite("data/Items/springIdle.png");
        coin = createSprite("data/Items/coin.png");
        //Enemies
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
        getSpriteSize(jumpspring, wSpring, hSpring);
        getSpriteSize(playStart, wPlayStart, hPlayStart);
        getSpriteSize(coin, wCoin, hCoin);
        int platformCount = 9;
        gap = (float)(Height / platformCount);
        generatePlatforms(a, gap, Width, Height, wPlatform,  hPlatform, coins);
        dt = 0;
        lastTick = getTickCount();
        lifes = 3;
        spring = 1;
        return true;
    }

    virtual void Close()
    {
    }

    virtual bool Tick()
    {
        if (started)
        {
            if (play == true)
            {
                dt = (getTickCount() - lastTick) / 1000.0f;
                if (dt > 0.015)
                    dt = 0.015;
                lastTick = getTickCount();
                drawSprite(background, 0, 0);
                drawSprite(topscore, 0, 0);
                drawSprite(scoreWord, 0, 0);
                for (int i = 1; i <= 6; i++)
                    drawSprite(block, a[i][0], a[i][1]);

                firstCounter = 0;
                numberToDigits(score, firstDigit, firstCounter);

                for (int i = firstCounter - 1; i >= 0; i--)
                {
                    drawSprite(digits[firstDigit[i]], Width / 3 - i * 25, 7);
                }

                secondCounter = 0;
                numberToDigits(scorepx, secondDigit, secondCounter);

                for (int i = secondCounter - 1; i >= 0; i--)
                {
                    drawSprite(digits[secondDigit[i]], Width - i * 25 - (wDigit + wDigit / 2), 7);
                }

                for (int i = 0; i < enemies.size(); i++)
                {
                    drawSprite(enemy, enemies[i].x, enemies[i].y);
                }

                for (int i = 0; i < springs.size(); i++)
                {
                    drawSprite(jumpspring, springs[i].x, springs[i].y);
                }

                for (int i = 0; i < tmplats.size(); i++)
                {
                    drawSprite(platformTemp, tmplats[i].x, tmplats[i].y);
                }

              
                // hitting the platform
                // player jumps , and score is increased
                for (int i = 1; i <= 6; i++)
                {
                    if ((floor(playery + hPlayer) == a[i][1] + 3 || floor(playery + hPlayer) == a[i][1] + 1 || floor(playery + hPlayer) == a[i][1] + 2 || floor(playery + hPlayer) == a[i][1] + 5 || floor(playery + hPlayer) == a[i][1] + 4 || floor(playery + hPlayer) == a[i][1] + 6) && floor(playerx) >= a[i][0] - wPlayer + 25 && floor(playerx) <= a[i][0] + wPlatform - 20 && dy > 0)
                    {
                        dy = -(800) * spring;
                        score += 1;
                        scorepx += Height - a[i][1];
                    }
                }

                // jump from temporary platforms
                for (int i = 0; i < tmplats.size(); i++)
                {
                    if ((floor(playery + hPlayer) == tmplats[i].y + 3 || floor(playery + hPlayer) == tmplats[i].y + 1 || floor(playery + hPlayer) == tmplats[i].y + 2 || floor(playery + hPlayer) == tmplats[i].y + 5 || floor(playery + hPlayer) == tmplats[i].y + 4 || floor(playery + hPlayer) == tmplats[i].y + 6) && floor(playerx) >= tmplats[i].x - wPlayer + 25 && floor(playerx) <= tmplats[i].x + wPlatform - 20 && dy > 0)
                    {
                        dy = -(800) * spring;
                        score += 1;
                        scorepx += Height - a[i][1];
                    }
                }

                dy += grav * dt;
                playery += dy * dt;

                // Calculations for the jumping of the doodle
                if (dt < 0.002)
                {
                    if (dy * 0.002 > -0.7 && dy < 0)
                    {
                        dy = -dy;
                    }
                }
                else if (dt > 0.004)
                {
                    if (dy * 0.004 > -0.7 && dy < 0)
                    {
                        dy = -dy;
                    }
                }
                else
                {
                    if (dy * dt > -0.7 && dy < 0)
                    {
                        dy = -dy;
                    }
                }

                //  Spring ability last for 1 seconds, after that spring is set to 1,
                //  the jump speed being multiplied by spring it will come back to normal after setting it to 1
                //  and it will speed up when the spring boots is on
                if (springed == true)
                {
                    if ((getTickCount() - startSpring) / 1000 > 1)
                    {
                        springed = false;
                        spring = 1;
                        stopSpring = getTickCount();
                    }
                }

                // the algorithm for keeping the player at max the center of the screen
                // and making it seem like he is going up, and platforms down
                if (playery < Height / 2)
                {
                    // keeping player at max the center of the screen
                    playery = Height / 2;
                    for (int i = 1; i <= 6; i++)
                    {
                        // moving the platforms down
                        a[i][1] -= dy * dt;
                        if (a[i][1] > Height)
                        {
                            // erase the enemy from the paltform that got off the screen
                            for (int j = 0; j < enemies.size(); j++)
                                if (enemies[j].plt == i)
                                    enemies.erase(enemies.begin() + j);
                            // erase the spring from the paltform that got off the screen
                            for (int j = 0; j < springs.size(); j++)
                                if (springs[j].plt == i)
                                    springs.erase(springs.begin() + j);

                            score += 1;
                            a[i][1] = 0;
                            if (a[i - 1][0] > Width / 2)
                                a[i][0] = rand() % (Width / 2 - wPlatform);
                            else
                                a[i][0] = rand() % (Width / 2 - wPlatform) + Width / 2;

                            /**
                             *  Second Task
                             *  A platform that allows you to jump using it only once, after which it gets destroyed.
                             *
                             */
                            int randPlatTemp = rand() % 999;
                            // 1% of time a platform will be created
                            if (randPlatTemp < 50)
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

                            if ((getTickCount() - startSpring) / 1000 > 20 && (getTickCount() - stopSpring) / 1000 > 10)
                            {
                                int randomSpring = rand() % 999;
                                // 1% of time spring will be created
                                if (randomSpring < 60 && random > 60)
                                {
                                    Spring newSpring = {a[i][0] + wPlatform / 2 - wSpring / 2, a[i][1] - hSpring, i};
                                    springs.push_back(newSpring);
                                }
                            }
                            updateCoinPositions(coins, dy);
                        }
                        // enemy moves down with the platform it belongs to
                        for (int j = 0; j < enemies.size(); j++)
                            enemies[j].y = a[enemies[j].plt][1] - hEnemy;
                        // spring moves down with the platform it belongs to
                        for (int j = 0; j < springs.size(); j++)
                            springs[j].y = a[springs[j].plt][1] - hSpring;
                        
                    }
                     
                    // temp platforms move down with the platforms
                    for (int i = 0; i < tmplats.size(); i++)
                        tmplats[i].y -= dy * dt;
                }

                renderBullets(bullets, dt, bulletspr);
                
                renderCoins(coins, coin);

                bulletDestroysEnemy(bullets, enemies, wEnemy, hEnemy, wBullet);

                playerInteractWithEnemy(enemies, playerx, playery, wPlayer, hPlayer, wEnemy, hEnemy, dy, play);

                playerInteractWithSpring(springs, playerx, playery, wPlayer, hPlayer, wSpring, hSpring, dy, springed, spring, startSpring);

                playerInteractWithCoin(coins, playerx, playery, wPlayer, hPlayer);
                // remove temp platforms out of the screen
                for (int i = 0; i < tmplats.size(); i++)
                {
                    if (tmplats[i].y > Height)
                        tmplats.erase(tmplats.begin() + i);
                }

                // if player is out of the screen then he appears on the other side
                if (playerx + wPlayer > Width)
                    playerx = 0;
                else if (playerx + wPlayer < 0)
                    playerx = Width - wPlayer;

                // left right speed
                if (isMovingRight)
                {
                    playerx += 300 * dt;
                    //First task. The player moves faster by 50% while on the right side.
                    if( playerx >= 400)
                    {
	                    playerx += 600 * dt;
                    }
                }
                if (isMovingLeft)
                {
                    playerx -= 300 * dt;
                }

                // if shooting then doodle has the nose up
                if (!bullets.size())
                {
                    if (facingRight)
                        drawSprite(lookRight, playerx, playery);
                    else if (facingLeft)
                        drawSprite(lookLeft, playerx, playery);
                }
                // else he looks normal
                else
                {
                    drawSprite(lookUp, playerx, playery);
                    drawSprite(nose, playerx + wPlayer / 2.5, playery);
                }

                // Player has 3 lifes, if it falls down, it loses one life
                //  and it gets spawned on the lowest platform
                if (playery > Height - hPlayer)
                {
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
                // if player loses all lifes, he lost, and after that he can play again
                if (lifes == 0)
                    play = false;
            }
            if (play == false)
            {
                // draw playagain screen
                drawSprite(background, 0, 0);
                drawSprite(topscore, 0, 0);
                drawSprite(scoreWord, 0, 0);
                drawSprite(playagain, Width / 3, Height / 2);
                firstCounter = 0;
                numberToDigits(score, firstDigit, firstCounter);

                for (int i = firstCounter - 1; i >= 0; i--)
                {
                    drawSprite(digits[firstDigit[i]], Width / 3 - i * 25, 10);
                }

                secondCounter = 0;
                numberToDigits(scorepx, secondDigit, secondCounter);

                for (int i = secondCounter - 1; i >= 0; i--)
                {
                    drawSprite(digits[secondDigit[i]], Width - i * 25 - (wDigit + wDigit / 2), 10);
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

    virtual void onMouseMove(int x, int y, int xrelative, int yrelative)
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

    virtual void onMouseButtonClick(FRMouseButton button, bool isReleased)
    {
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
            dy = 0;
            grav = 500;
            score = 0;
            scorepx = 0;
            int platformCount = 6;
            float gap = (float)(Height / platformCount);
            generatePlatforms(a, gap, Width, Height, wPlatform, hPlatform, coins);
            lifes = 3;
            spring = 1;
            springed = false;
        }
        // Shoot projectile
        if (button == FRMouseButton::LEFT && isReleased == true)
        {
            Bullet newBullet = {playerx, playery, -700, -700, true, mousex};
            bullets.push_back(newBullet);
        }
    }

    virtual void onKeyPressed(FRKey k)
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

    virtual void onKeyReleased(FRKey k)
    {
        if (k == FRKey::RIGHT)
            isMovingRight = false;
        else if (k == FRKey::LEFT)
            isMovingLeft = false;
    }

    virtual const char *GetTitle() override
    {
        return "Doodle Jump";
    }
};

int main(int argc, char *argv[])
{
    return run(new ExtendedFramework);
}