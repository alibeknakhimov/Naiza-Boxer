#include "game_logic.h"
#include "display.h"
#include "config.h"

// Внешние переменные для MP3 плеера
extern DFRobotDFPlayerMini player;

// Глобальные переменные для игровой логики
extern int sum;
extern int num;
extern boolean sost;
extern boolean game;
extern boolean motor;
extern boolean startTimer;
extern boolean flag;
extern volatile unsigned long counter;
extern byte kol;
extern byte posl;
extern unsigned long timer1;
extern unsigned long timer2;
extern unsigned long res;
extern unsigned long late;
extern uint32_t animtime;
extern boolean stAnim;
extern byte R, G, B;
extern int maximus;

// Инициализация игровой логики
void initGameLogic() {
  pinMode(5, OUTPUT);    // Реле для соленоида
  pinMode(16, OUTPUT);   // Светодиод индикации
  pinMode(12, INPUT_PULLUP);  // Датчик удара
  pinMode(A0, INPUT_PULLUP);  // Кнопка запуска
  
  attachInterrupt(digitalPinToInterrupt(12), buttonTick, CHANGE);
  
  // Начальные значения
  num = 31;      // Время для игры
  startTimer = 0;
  motor = 0;
  game = 0;
}

// Обработка старта игры
void handleStartGame() {
  // Если есть кредиты и нажата кнопка старта
  if(sum > 0 && analogRead(A0) > 650 && analogRead(A0) < 920 && motor == 0 && game == 0) {
    num = 31;
    sost = 0;
    game = 1;
    motor = 0; 
  }
  
  // Если нет кредитов и нажата кнопка старта - сообщить
  if(sum == 0 && analogRead(A0) > 650 && analogRead(A0) < 920) {  
    player.playFolder(9, 1);
  }
  
  // Если игра активирована - запустить процесс
  if(game == 1) {
    player.stop();
    
    // Двойное срабатывание соленоида для сброса механизма
    digitalWrite(5, 1);
    delay(200);
    digitalWrite(5, 0);
    delay(500);
    digitalWrite(5, 1);  
    delay(200);
    digitalWrite(5, 0);
    delay(300);
    
    digitalWrite(16, 1);  // Включаем светодиод готовности
    player.playFolder(3, 1);  // Звук начала игры
    
    kol = 0;
    motor = 1;
    startTimer = 1;
    game = 0;
  }
}

// Обработка игрового процесса
void handleGameProcess() {
  // Обратный отсчет времени
  if(startTimer == 1) {
    disp_CountDOWN();
  }
  
  // Фиксация первого импульса от датчика
  if(kol > 0 && posl == 0) {
    if(motor == 1) {
      timer1 = counter;
      posl = kol;
    }
  }
  
  // Фиксация последнего импульса от датчика
  if(kol > posl) {
    if(motor == 1) {
      timer2 = counter;
      motor = 0;
    }
    posl = 0;
    kol = 0;
  }
}

// Расчет результата игры
void calculateResult() {
  if (timer1 != 0 && timer2 != 0 && timer2 > timer1 && kol == 0) {
    res = difficult / (timer2 - timer1);
    if(res > maximum) {
      res = maximum;
    }
    startTimer = 0;
    timer1 = 0;
    timer2 = 0;
  }
  
  if(res != late) {
    flag = 1;
    late = res;
  }
}

// Отображение результата игры
void displayResult() {
  if(flag == 1) {
    R = 0;
    G = 0;
    B = 0;
    sum -= 1;
    digitalWrite(16, 0);
    player.stop();
    startTimer = 0;
    
    // Если это новый рекорд
    if(maximus < res) {
      sost = 1;
    }
    
    // Анимация нарастания результата
    disp_CountUP(res);
    
    // Если установлен новый рекорд
    if(maximus < res) {
      sum += 1;  // Бонусная игра за рекорд
      maximus = res;
    }
    
    // Показ рекорда
    write(3, (maximus / 100) % 10);
    write(4, (maximus / 10) % 10);
    write(5, (maximus / 1) % 10);
    strip.show();
    
    // Если кредиты закончились, запускаем анимации
    if(sum == 0) {
      stAnim = 1;
      animtime = millis();
    }
    
    flag = 0;
  }
}

// Сброс игры каждые 24 часа
void resetGame() {
  extern uint32_t dfp;
  
  if(millis() - dfp >= (unsigned long) 24*60*60*1000 && sum == 0) {
    dfp = millis();
    maximus = 700;  // Сброс максимума к дефолтному значению
  }
}

// Обработчик прерывания для датчика удара
void buttonTick() {
  if(sum > 0 && motor == 1) {
    kol++;
    counter = ESP.getCycleCount();
  }
}
