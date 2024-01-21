#pragma once
#include "Point.h"
struct RectangleF {
    float x, y, w, h;
    RectangleF(float initX, float initY, float initWidth, float initHeight)
        : x(initX),
          y(initY),
          w(initWidth),
          h(initHeight) {}
    RectangleF(PointF initPoint, float initWidth, float initHeight)
        : x(initPoint.x),
          y(initPoint.y),
          w(initWidth),
          h(initHeight) {}
};