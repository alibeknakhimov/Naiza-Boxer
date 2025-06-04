#ifndef PAYMENT_H
#define PAYMENT_H

#include "config.h"

// Функции для обработки платежей
void processMoney();
void processCoins();
void updatePaymentDisplay();

// Инициализация системы оплаты
void initPaymentSystem();

// Обработчики прерываний
void count_pulse1();
void count_pulse2();

#endif
