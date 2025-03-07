#include "color.h"
#include <algorithm>
Color operator*(const Color& c, const float& scale)
{
    return Color(
            std::min(0xFF, std::max(0x00, static_cast<int>(c.r * scale)))&0xFF, 
            std::min(0xFF, std::max(0x00, static_cast<int>(c.g * scale)))&0xFF, 
            std::min(0xFF, std::max(0x00, static_cast<int>(c.b * scale)))&0xFF
            );
}
// Dithering/quantizing algorithm adapted from https://github.com/dschmenk/DITHER16

enum {
    RED = 0,
    GRN,
    BLU,
    BRI
};

static const uint32_t ddithmask[16] = // Color dither
{
    0x00000000L,
    0x88000000L,
    0x88002200L,
    0x8800AA00L,
    0xAA00AA00L,
    0xAA44AA00L,
    0xAA44AA11L,
    0xAA44AA55L,
    0xAA55AA55L,
    0xAADDAA55L,
    0xAADDAA77L,
    0xAADDAAFFL,
    0xAAFFAAFFL,
    0xEEFFAAFFL,
    0xEEFFBBFFL,
    0xEEFFFFFFL,
};
static const uint32_t bdithmask[16] = // Color dither
{
    0x00000000L,
    0x88000000L,
    0x88002200L,
    0x8800AA00L,
    0xAA00AA00L,
    0xAA44AA00L,
    0xAA44AA11L,
    0xAA44AA55L,
    0xAA55AA55L,
    0xAADDAA55L,
    0xAADDAA77L,
    0xAADDAAFFL,
    0xAAFFAAFFL,
    0xEEFFAAFFL,
    0xEEFFBBFFL,
    0xFFFFFFFFL
};
uint8_t Color::dither(int x, int y) const
{
    uint8_t l = std::max(std::max(r, g), b);
    uint8_t pixbrush[4][4];
    uint32_t *brush = reinterpret_cast<uint32_t*>(pixbrush);
    if (l > 0x7F)
    {
        brush[BRI] = bdithmask[(l >> 3) & 0x0F];
        brush[BLU] = bdithmask[(b << 4) / (l + 8)];
        brush[GRN] = bdithmask[(g << 4) / (l + 8)];
        brush[RED] = bdithmask[(r << 4) / (l + 8)];
    }
    else
    {
        if ((3*l - r - g - b) < 8)
        {
            if (l > 0x3F)
            {
                const int offset = (l - 64) >> 2;
                brush[BRI] = ~ddithmask[offset];
                brush[BLU] =
                brush[GRN] =
                brush[RED] = ddithmask[offset];
            }
            else
            {
                brush[BRI] = ddithmask[l >> 2];
                brush[BLU] = 0;
                brush[GRN] = 0;
                brush[RED] = 0;
            }
        }
        else
        {
            brush[BRI] = 0;
            brush[BLU] = ddithmask[b >> 3];
            brush[GRN] = ddithmask[g >> 3];
            brush[RED] = ddithmask[r >> 3];
        }
    }
    const uint8_t pix = 
        (((pixbrush[BRI][y & 3] >> (x & 3)) & 0x01) << BRI) |
        (((pixbrush[BLU][y & 3] >> (x & 3)) & 0x01) << BLU) |
        (((pixbrush[GRN][y & 3] >> (x & 3)) & 0x01) << GRN) |
        (((pixbrush[RED][y & 3] >> (x & 3)) & 0x01) << RED);

    return pix;
}

uint8_t Color::quantize() const
{
    uint8_t pix = 0;
    uint8_t l = std::max(std::max(r, g), b);
    if (l > 0x7F)
    {
        pix = 0x08 | ((r & 0x80) >> 7) | ((g & 0x80) >> 6) | ((b & 0x80) >> 5);
    }
    else if ((3*l - r - g - b) < 8)
    {
        switch (l >> 5)
        {
        case 0:
            pix = 0;
            break;
        case 1:
            pix = 0x08;
            break;
        default:
            pix = 0x07;
        }
        if (l > 0x3F)
        {
            pix = 0x07;
        }
        else if (l > 0x1F)
        {
            pix = 0x08;
        }
        else
        {
            pix = 0;
        }
    }
    else
    {
        pix = ((r & 0x40) >> 6) | ((g & 0x40) >> 5) | ((b & 0x40) >> 4);
    }

    return pix;
}
