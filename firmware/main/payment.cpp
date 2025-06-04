#include "payment.h"
#include "display.h"
#include "config.h"

// Глобальные переменные для работы с оплатой
extern int sum;
extern int money;
extern unsigned long timeCount1;
extern int coins;
extern int sumcoins;
extern unsigned long timeCount2;
extern int tokens;
extern int latcoin;
extern boolean startAnimation;
extern boolean stAnim;
extern boolean ochistka;
extern boolean pol;
extern int lates;
extern byte R, G, B;
extern byte kol;

// Инициализация системы платежей
void initPaymentSystem() {
  pinMode(moneyPin, INPUT);
  pinMode(coinPin, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(coinPin), count_pulse2, FALLING);
  attachInterrupt(digitalPinToInterrupt(moneyPin), count_pulse1, FALLING);
}

// Обработка поступления бумажных денег
void processMoney() {
  if(money > 0 && (millis() - timeCount1) > timeAllPulse1) {
    sum += (money * 100) / kzt;
    kol = 0;
    R = 255;
    G = 0;
    B = 0;
    money = 0;
  }
}

// Обработка монет
void processCoins() {
  if(coins > 0 && (millis() - timeCount2) > timeAllPulse2) {
    switch(coins) {
      case 2:
        tokens = 10;
        break;
      case 4:
        tokens = 20;
        break;
      case 6:
        tokens = 50;
        break;
      case 8:
        tokens = 100;
        break;
      case 10:
        tokens = 200;
        break;
    }
    sumcoins += tokens;

    if(sumcoins / kzt > latcoin) {
      sum += sumcoins / kzt - latcoin;
      latcoin = sumcoins / kzt;
      kol = 0;
      R = 255;
      G = 0;
      B = 0;
    }
    coins = 0;
  }
}

// Обновление дисплея с информацией о платежах
void updatePaymentDisplay() {
  if(sum != lates) {
    pol = 1;
    lates = sum;
  }
  
  if(pol == 1) {
    startAnimation = 0;
    if(sum > 0) {
      stAnim = 0;
    }
    if(ochistka == 1) {
      clearDisplay();
      ochistka = 0;
    }
    write(6, sum / 10);
    write(7, sum % 10);
    strip.show();
    pol = 0;
  }
}

// Обработчик прерывания для купюроприемника
ICACHE_RAM_ATTR void count_pulse1() {
  detachInterrupt(digitalPinToInterrupt(moneyPin));
  money++;
  if(money == 1)
    timeCount1 = millis();
  attachInterrupt(digitalPinToInterrupt(moneyPin), count_pulse1, FALLING);
}

// Обработчик прерывания для монетоприемника
ICACHE_RAM_ATTR void count_pulse2() {
  detachInterrupt(digitalPinToInterrupt(coinPin));
  coins++;
  if(coins == 1)
    timeCount2 = millis();
  attachInterrupt(digitalPinToInterrupt(coinPin), count_pulse2, FALLING);
}
