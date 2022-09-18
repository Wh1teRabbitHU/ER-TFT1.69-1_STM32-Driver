#ifndef ST7789V_H
#define ST7789V_H

#include "main.h"

#define GET_BIT_VALUE(binary, pos) (((binary >> pos) & 1) == 1 ? 1 : 0)

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
