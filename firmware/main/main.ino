#include "config.h"
#include "display.h"
#include "payment.h"
#include "game_logic.h"
#include "audio.h"

// Глобальные переменные для анимационных паттернов
char x[5] = {5, 0, 2, 0, 5};  // UP-DOWN
char y[6] = {6, 5, 4, 3, 2, 1};  // CIRCLE
char z[4] = {6, 1, 4, 3};  // ZIG-ZAG
char w[8] = {6, 5, 4, 0, 1, 2, 3, 0};  // INFINITY

// Общие переменные
int num = 41;  // Начальное значение таймера
int cntr = 0;  // Счетчик для анимаций
uint32_t tmrr;  // Таймер для обратного отсчета
uint32_t tmr;  // Таймер для анимаций
uint32_t dfp;  // Таймер для суточного сброса
int dir = 0;  // Направление анимации
int duty = 1;  // Текущая анимация
int govno = 0;  // Счетчик повторений анимации
volatile unsigned long counter = 0;  // Счетчик циклов процессора
unsigned long timer1 = 0;  // Время первого импульса
unsigned long timer2 = 0;  // Время последнего импульса
unsigned long res = 0;  // Результат вычислений
unsigned long late = 0;  // Предыдущий результат

// Флаги состояния
boolean rusl = 0;
boolean ochistka = 0;
boolean startAnimation = 0;
boolean stAnim = 0;
boolean startTimer = 0;
boolean pol = 0;
boolean flag = 0;
boolean sost = 0;
boolean game = 0;
boolean motor = 0;
boolean music = 0;
boolean zomus = 0;
boolean continu = 1;
boolean blin = 0;

// Счетчики и индикаторы
byte kol = 0;  // Количество импульсов от датчика
byte posl = 0;  // Последний зарегистрированный импульс
byte R = 0;  // Красный цвет
byte G = 0;  // Зеленый цвет
byte B = 0;  // Синий цвет
int wait = 0;  // Задержка для эффектов
int money = 0;  // Счетчик импульсов купюроприемника
int sum = 0;  // Текущий баланс пользователя
int sumcoins = 0;  // Сумма монет
int lates = 0;  // Предыдущий баланс
int maximus = 700;  // Максимальный показанный результат
int coins = 0;  // Счетчик импульсов монетоприемника
int tokens = 0;  // Номинал монеты
int latcoin = 0;  // Предыдущий счетчик монет
int sozvuk = 0;  // Номер звукового файла
unsigned long timeCount1 = 0;  // Время первого импульса купюроприемника
unsigned long timeCount2 = 0;  // Время первого импульса монетоприемника
uint32_t animtime = 0;  // Таймер для анимаций в режиме ожидания




void setup() {
  // Инициализация всех подсистем
  initDisplay();
  initAudio();
  initGameLogic();
  initPaymentSystem();
    // Активация стартовой анимации
  startAnimation = 1;
}

void loop() {
  // Сброс максимального значения каждые 24 часа
  resetGame();
  
  // Обработка платежей
  processMoney();
  processCoins();
  updatePaymentDisplay();
  
  // Анимация в режиме ожидания
  if(startAnimation == 1) {
    ochistka = 1;
    disp_Animation();
  }
  if(stAnim == 1 && millis() - animtime >= 20000) {
    ochistka = 1;
    disp_Animation();
  }
  
  // Обработка игрового процесса
  handleStartGame();
  handleGameProcess();
  calculateResult();
  displayResult();
}