#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "config.h"

// Функции игровой логики
void handleStartGame();
void handleGameProcess();
void calculateResult();
void displayResult();
void resetGame();

// Инициализация игровых параметров
void initGameLogic();

// Обработчик прерывания для датчика удара
void buttonTick();

#endif
