#ifndef CONFIG_H
#define CONFIG_H

// Определяем тип byte, который используется в Arduino
typedef unsigned char byte;

// Основные настройки
#define kzt 100                 // Курс валюты
#define difficult 916076207     // Коэффициент расчета силы удара
#define maximum 999             // Максимальное значение силы
#define timeAllPulse1 1300      // Время ожидания для импульсов купюроприемника
#define timeAllPulse2 1300      // Время ожидания для импульсов монетоприемника

// LED настройки
#define PIXELS_PER_SEGMENT 3    // Количество светодиодов в каждом сегменте
#define PIXELS_DIGITS 8         // Количество подключенных цифр
#define PIXELS_PIN 4            // GPIO пин для светодиодной ленты

// Пины для DFPlayer Mini
#define PIN_MP3_TX 0
#define PIN_MP3_RX 2

// Пины для монетоприемника и купюроприемника
#define coinPin 14              // Пин для монетоприемника
#define moneyPin 13             // Пин для купюроприемника

// Глобальные переменные
extern int maximus;             // Текущий максимальный результат
extern byte R, G, B;            // Параметры цвета (RGB)
extern int sum;                 // Текущая сумма кредитов

// Анимационные паттерны
extern char x[5];  // UP-DOWN
extern char y[6];  // CIRCLE
extern char z[4];  // ZIG-ZAG
extern char w[8];  // INFINITY

#endif
