#ifndef ST7789V_H
#define ST7789V_H

#include "main.h"

#define GET_BIT_VALUE(binary, pos) (((binary >> pos) & 1) == 1 ? 1 : 0)

#define COLOR_BLACK		0x0000
#define COLOR_WHITE		0xFFFF
#define COLOR_RED		0xF800
#define COLOR_LIME		0x07E0
#define COLOR_BLUE		0x001F
#define COLOR_YELLOW	0xFFE0
#define COLOR_CYAN		0x07FF
#define COLOR_MAGENTA	0xF81F
#define COLOR_SILVER	0xC618
#define COLOR_GRAY		0x8410
#define COLOR_MAROON	0x8000
#define COLOR_OLIVE		0x8400
#define COLOR_GREEN		0x0400
#define COLOR_PURPLE	0x8010
#define COLOR_TEAL		0x0410
#define COLOR_NAVY		0x0010

uint16_t ST7789V_convert24BitRGBTo16Bit(uint32_t rgbValue);

void ST7789V_Initial(void);
void ST7789V_ClearScreen(uint16_t bColor);
void ST7789V_SendCmd(uint8_t cmd);
void ST7789V_Send8BitData(uint8_t data);
void ST7789V_Send16BitData(uint16_t data);

void ST7789V_ShowChar(uint16_t x, uint16_t y, char value, uint16_t dcolor, uint16_t bgcolor);
void ST7789V_ShowString(uint16_t x, uint16_t y, char *str, uint16_t dcolor, uint16_t bgcolor);
void ST7789V_ShowPicture(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t *picture);

void ST7789V_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void ST7789V_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void ST7789V_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
void ST7789V_DrawCircle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color);

void ST7789V_SetPosition(uint16_t Xstart,uint16_t Ystart,uint16_t Xend,uint16_t Yend);

#endif
