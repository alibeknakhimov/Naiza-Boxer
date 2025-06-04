#ifndef DISPLAY_H
#define DISPLAY_H

#include "config.h"
#include <Adafruit_NeoPixel.h>
#include "DFRobotDFPlayerMini.h"  // Добавляем для возможности использовать DFPlayer в функциях дисплея

// Объявление внешних переменных
extern Adafruit_NeoPixel strip;

// Определение segements и digits
extern byte segments[7];
extern byte digits[10];

// Функции для работы с дисплеем
void writeDigit(int index, int val);
void write(int index, int val);
void writeSegment(int index, int val);
void writeSeg(int index, int val);
void clearDisplay();

// Функции для анимаций и эффектов
void disp_Animation();
void disp_CountDOWN();
void disp_CountUP(int num);

// Инициализация дисплея
void initDisplay();

#endif
