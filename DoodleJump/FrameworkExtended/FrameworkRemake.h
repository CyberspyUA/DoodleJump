#pragma once
#include "Framework.h"
class FrameworkRemake : public Framework
{
	public:
	void PreInit(int& width, int& height, bool& fullscreen) override
	{
		width = 800;
		height = 600;
		fullscreen = false;
	}

	bool Init() override
	{
		return true;
	}

	void Close() override
	{
		
	}

	bool Tick() override
	{
		
		showCursor(true);
		return false;
	}

	void onMouseMove(int x, int y, int xrelative, int yrelative) override
	{

	}

	void onMouseButtonClick(FRMouseButton button, bool isReleased) override
	{
		if(button == FRMouseButton::LEFT)
		{

		}
		else if(button == FRMouseButton::RIGHT)
		{

		}
		else if(button == FRMouseButton::MIDDLE)
		{

		}
	}

	void onKeyPressed(FRKey k) override
	{
		if(k == FRKey::RIGHT)
		{
			
		}
		else if(k == FRKey::LEFT)
		{
			
		}
		else if(k == FRKey::UP)
		{
			
		}
		else if(k == FRKey::DOWN)
		{
			
		}
	}

	void onKeyReleased(FRKey k) override
	{
	}

	const char* GetTitle() override
	{
		return "DoodleJump";
	}
};
struct Point {
  Point(int x, int y);
  Point() = default;
  int x;
  int y;
  Point operator+(const Point) const;
  Point operator-(const Point) const;
  Point operator*(const int)const;
  Point operator/(const int) const;
  Point &operator+=(const Point);
  Point &operator-=(const Point);
  Point &operator*=(const int);
  Point &operator/=(const int);
  operator SDL_Point();
};
