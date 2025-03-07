#include "buffer.h"

Point2d operator+(const Point2d& lhs, const Point2d& rhs) {return Point2d(lhs.x + rhs.x, lhs.y + rhs.y);}
Point2d operator-(const Point2d& lhs, const Point2d& rhs) {return Point2d(lhs.x - rhs.x, lhs.y - rhs.y);}

