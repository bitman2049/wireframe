#pragma once
#include <cstdint>

class Color
{
public:
    Color(uint32_t rgb) : r(rgb&0xFF), g((rgb >> 8)&0xFF), b((rgb >> 16)&0xFF) { a = ((rgb & 0xFF000000L) != 0);}
    Color(uint8_t r, uint8_t g, uint8_t b, bool a=true) : r(r), g(g), b(b), a(a) {}
    uint8_t dither(int x, int y) const;
    uint8_t quantize() const;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    bool a = true;
};
Color operator*(const Color& c, const float& scale); 
            
