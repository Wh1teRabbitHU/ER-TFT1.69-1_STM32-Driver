#include "ST7789V.h"
#include "font_6_12.h"

void HAL_GPIO_FastWritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) {
	if (PinState == GPIO_PIN_RESET) {
		GPIOx->BRR = (uint32_t)GPIO_Pin;
	} else {
		GPIOx->BSRR = (uint32_t)GPIO_Pin;
	}
}

uint16_t ST7789V_convert24BitRGBTo16Bit(uint32_t rgbValue) {
	uint16_t r = ((rgbValue >> 19) & 0b11111);
	uint16_t g = ((rgbValue >> 10) & 0b111111);
	uint16_t b = ((rgbValue >> 3) & 0b11111);

	return (r << 11) | (g << 5) | b;
}

void ST7789V_SetDataPins(uint8_t data) {
	HAL_GPIO_FastWritePin(DATA_0_GPIO_Port, DATA_0_Pin, GET_BIT_VALUE(data, 0));
	HAL_GPIO_FastWritePin(DATA_1_GPIO_Port, DATA_1_Pin, GET_BIT_VALUE(data, 1));
	HAL_GPIO_FastWritePin(DATA_2_GPIO_Port, DATA_2_Pin, GET_BIT_VALUE(data, 2));
	HAL_GPIO_FastWritePin(DATA_3_GPIO_Port, DATA_3_Pin, GET_BIT_VALUE(data, 3));
	HAL_GPIO_FastWritePin(DATA_4_GPIO_Port, DATA_4_Pin, GET_BIT_VALUE(data, 4));
	HAL_GPIO_FastWritePin(DATA_5_GPIO_Port, DATA_5_Pin, GET_BIT_VALUE(data, 5));
	HAL_GPIO_FastWritePin(DATA_6_GPIO_Port, DATA_6_Pin, GET_BIT_VALUE(data, 6));
	HAL_GPIO_FastWritePin(DATA_7_GPIO_Port, DATA_7_Pin, GET_BIT_VALUE(data, 7));
}

void ST7789V_Initial(void) {
	HAL_Delay(5);
	HAL_GPIO_FastWritePin(Display_RST_GPIO_Port, Display_RST_Pin, 0);
	HAL_Delay(10);
	HAL_GPIO_FastWritePin(Display_RST_GPIO_Port, Display_RST_Pin, 1);
	HAL_Delay(120);

	ST7789V_SendCmd(0x36);			// Memory data access control
    ST7789V_Send8BitData(0x00);

	ST7789V_SendCmd(0x3A); 			// Interface pixel format
	ST7789V_Send8BitData(0x05);

	ST7789V_SendCmd(0xB2); 			// Porch control
	ST7789V_Send8BitData(0x0C);
	ST7789V_Send8BitData(0x0C);
	ST7789V_Send8BitData(0x00);
	ST7789V_Send8BitData(0x33);
	ST7789V_Send8BitData(0x33);

	ST7789V_SendCmd(0xB7); 			// Gate control
	ST7789V_Send8BitData(0x35);

	ST7789V_SendCmd(0xBB); 			// VCOM Settings
	ST7789V_Send8BitData(0x32); 	// VCOM = 1.35V

	ST7789V_SendCmd(0xC2); 			// VDV and VRH Command Enable
	ST7789V_Send8BitData(0x01);

	ST7789V_SendCmd(0xC3); 			// VRH Set
	ST7789V_Send8BitData(0x15); 	// GVDD = 4.8V

	ST7789V_SendCmd(0xC4); 			// VDV Setting
	ST7789V_Send8BitData(0x20); 	// VDV, 0x20:0v

	ST7789V_SendCmd(0xC6); 			// FR Control
	ST7789V_Send8BitData(0x0F);		// 0x0F:60Hz

	ST7789V_SendCmd(0xD0); 			// Power Control
	ST7789V_Send8BitData(0xA4);
	ST7789V_Send8BitData(0xA1);

	ST7789V_SendCmd(0xE0); 			// Positive voltage gamma control
	ST7789V_Send8BitData(0xD0);
	ST7789V_Send8BitData(0x08);
	ST7789V_Send8BitData(0x0E);
	ST7789V_Send8BitData(0x09);
	ST7789V_Send8BitData(0x09);
	ST7789V_Send8BitData(0x05);
	ST7789V_Send8BitData(0x31);
	ST7789V_Send8BitData(0x33);
	ST7789V_Send8BitData(0x48);
	ST7789V_Send8BitData(0x17);
	ST7789V_Send8BitData(0x14);
	ST7789V_Send8BitData(0x15);
	ST7789V_Send8BitData(0x31);
	ST7789V_Send8BitData(0x34);

	ST7789V_SendCmd(0xE1); 			// Negative voltage gamma control
	ST7789V_Send8BitData(0xD0);
	ST7789V_Send8BitData(0x08);
	ST7789V_Send8BitData(0x0E);
	ST7789V_Send8BitData(0x09);
	ST7789V_Send8BitData(0x09);
	ST7789V_Send8BitData(0x15);
	ST7789V_Send8BitData(0x31);
	ST7789V_Send8BitData(0x33);
	ST7789V_Send8BitData(0x48);
	ST7789V_Send8BitData(0x17);
	ST7789V_Send8BitData(0x14);
	ST7789V_Send8BitData(0x15);
	ST7789V_Send8BitData(0x31);
	ST7789V_Send8BitData(0x34);

	ST7789V_SendCmd(0x21); 			// Display inversion on

 	ST7789V_SendCmd(0x11); 			// Sleep out

	HAL_Delay(120);

	ST7789V_SendCmd(0x29); 			// Display on
}

void ST7789V_SetPosition(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend) {
	Ystart += 20;
	Yend += 20;

	ST7789V_SendCmd(0x2a);
	ST7789V_Send8BitData(Xstart>>8);
	ST7789V_Send8BitData(Xstart);
 	ST7789V_Send8BitData(Xend>>8);
	ST7789V_Send8BitData(Xend);

	ST7789V_SendCmd(0x2b);
	ST7789V_Send8BitData(Ystart>>8);
	ST7789V_Send8BitData(Ystart);
	ST7789V_Send8BitData(Yend>>8);
	ST7789V_Send8BitData(Yend);

  	ST7789V_SendCmd(0x2c);
}

void ST7789V_ClearScreen(uint16_t bColor) {
	uint16_t i, j;

	ST7789V_SetPosition(0, 0, 239, 279);

	for (i = 0; i < 280; i++) {
	   for (j = 0; j < 240; j++) {
		   ST7789V_Send16BitData(bColor);
	   }
	}
}

void ST7789V_SendCmd(uint8_t data) {
	HAL_GPIO_FastWritePin(Display_RS_GPIO_Port, Display_RS_Pin, 0);
	HAL_GPIO_FastWritePin(Display_CS_GPIO_Port, Display_CS_Pin, 0);

	ST7789V_SetDataPins(data);

	HAL_GPIO_FastWritePin(Display_WR_GPIO_Port, Display_WR_Pin, 0);
	HAL_GPIO_FastWritePin(Display_WR_GPIO_Port, Display_WR_Pin, 1);

	HAL_GPIO_FastWritePin(Display_CS_GPIO_Port, Display_CS_Pin, 1);
}

void ST7789V_Send8BitData(uint8_t data) {
	HAL_GPIO_FastWritePin(Display_RS_GPIO_Port, Display_RS_Pin, 1);
	HAL_GPIO_FastWritePin(Display_CS_GPIO_Port, Display_CS_Pin, 0);

	ST7789V_SetDataPins(data);

	HAL_GPIO_FastWritePin(Display_WR_GPIO_Port, Display_WR_Pin, 0);
	HAL_GPIO_FastWritePin(Display_WR_GPIO_Port, Display_WR_Pin, 1);

	HAL_GPIO_FastWritePin(Display_CS_GPIO_Port, Display_CS_Pin, 1);
}

void ST7789V_Send16BitData(uint16_t data) {
	uint8_t dataHigh = data >> 8;
	uint8_t dataLow = data;

	HAL_GPIO_FastWritePin(Display_RS_GPIO_Port, Display_RS_Pin, 1);
	HAL_GPIO_FastWritePin(Display_CS_GPIO_Port, Display_CS_Pin, 0);

	ST7789V_SetDataPins(dataHigh);

	HAL_GPIO_FastWritePin(Display_WR_GPIO_Port, Display_WR_Pin, 0);
	HAL_GPIO_FastWritePin(Display_WR_GPIO_Port, Display_WR_Pin, 1);

	ST7789V_SetDataPins(dataLow);

	HAL_GPIO_FastWritePin(Display_WR_GPIO_Port, Display_WR_Pin, 0);
	HAL_GPIO_FastWritePin(Display_WR_GPIO_Port, Display_WR_Pin, 1);

	HAL_GPIO_FastWritePin(Display_CS_GPIO_Port, Display_CS_Pin, 1);
}

void ST7789V_ShowChar(uint16_t x, uint16_t y, char value, uint16_t dcolor, uint16_t bgcolor) {
	uint8_t i, j;
	uint8_t *temp = fontData;

    ST7789V_SetPosition(x, y, x + 7, y + 11);

	temp += (value - 32) * FONT_HEIGHT;

	for (j = 0; j < FONT_HEIGHT; j++) {
		for (i = 0; i < 8; i++) {
		 	if ((*temp & (1 << (7 - i))) != 0) {
				ST7789V_Send16BitData(dcolor);
			} else {
				ST7789V_Send16BitData(bgcolor);
			}
		}

		temp++;
	}
}

void ST7789V_ShowString(uint16_t x, uint16_t y, char *str, uint16_t dcolor, uint16_t bgcolor) {
	uint16_t x1 = x;
	uint16_t y1 = y;

	while (*str != '\0') {
		ST7789V_ShowChar(x1, y1, *str, dcolor, bgcolor);
		x1 += FONT_WIDTH + FONT_SPACING;
		str++;
	}
}

void ST7789V_ShowPicture(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t *picture) {
	uint8_t i, j;
	uint16_t n = 0;

	ST7789V_SetPosition(x, y, x + width, y + height);

	for (j = 0; j < height; j++) {
		for (i = 0; i < width; i++) {
            ST7789V_Send16BitData(picture[n++]);
	    }
	}
}

void ST7789V_DrawPoint(uint16_t x, uint16_t y, uint16_t color) {
	ST7789V_SetPosition(x, y, x, y);
	ST7789V_Send16BitData(color);
}

void ST7789V_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
	uint16_t t;
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int incx, incy, uRow, uCol;
	delta_x = x2 - x1;
	delta_y = y2 - y1;
	uRow = x1;
	uCol = y1;

	if (delta_x > 0) {
		incx = 1;
	} else if (delta_x == 0) {
		incx = 0;
	} else {
		incx = -1;
		delta_x = -delta_x;
	}

	if (delta_y > 0) {
		incy = 1;
	} else if (delta_y == 0) {
		incy = 0;
	} else {
		incy = -1;
		delta_y = -delta_x;
	}

	if (delta_x > delta_y) {
		distance=delta_x;
	} else {
		distance=delta_y;
	}

	for(t = 0; t < distance + 1; t++) {
		ST7789V_DrawPoint(uRow, uCol, color);

		xerr += delta_x;
		yerr += delta_y;

		if (xerr > distance) {
			xerr -= distance;
			uRow += incx;
		}

		if (yerr > distance) {
			yerr -= distance;
			uCol += incy;
		}
	}
}

void ST7789V_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
	ST7789V_DrawLine(x1, y1, x2, y1, color);
	ST7789V_DrawLine(x1, y1, x1, y2, color);
	ST7789V_DrawLine(x1, y2, x2, y2, color);
	ST7789V_DrawLine(x2, y1, x2, y2, color);
}

void ST7789V_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color) {
	int a = 0;
	int b = r;

	while (a <= b) {
		ST7789V_DrawPoint(x0-b,y0-a,color);             //3
		ST7789V_DrawPoint(x0+b,y0-a,color);             //0
		ST7789V_DrawPoint(x0-a,y0+b,color);             //1
		ST7789V_DrawPoint(x0-a,y0-b,color);             //2
		ST7789V_DrawPoint(x0+b,y0+a,color);             //4
		ST7789V_DrawPoint(x0+a,y0-b,color);             //5
		ST7789V_DrawPoint(x0+a,y0+b,color);             //6
		ST7789V_DrawPoint(x0-b,y0+a,color);             //7

		a++;

		if ((a*a+b*b) > (r*r)) {
			b--;
		}
	}
}
