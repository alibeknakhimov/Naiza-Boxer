#include "display.h"
#include "config.h"
#include <Adafruit_NeoPixel.h>
#include "DFRobotDFPlayerMini.h"  // Включаем заголовочный файл для DFPlayer

// Объявляем NeoPixel объект
Adafruit_NeoPixel strip = Adafruit_NeoPixel(133, PIXELS_PIN, NEO_GRB + NEO_KHZ800);

// Внешние переменные управления анимациями
extern uint32_t tmr;
extern uint32_t tmrr;
extern int dir;
extern int duty;
extern int govno;
extern int cntr;
extern int num;
extern boolean continu;
extern boolean blin;
extern boolean startAnimation;
extern boolean ochistka;
extern boolean flag;
extern boolean motor;
extern boolean game;
extern boolean sost;
extern boolean stAnim;
extern boolean startTimer;
extern uint32_t animtime;
extern boolean music;
extern boolean zomus;
extern int sozvuk;

/*
  Схема пикселей:
          b
        a   c
          g
        f   d
          e
*/

// Массив сегментов
byte segments[7] = {
  //abcdefg
  0b0000001,     // Segment g
  0b0000010,     // Segment f
  0b0000100,     // Segment e
  0b0001000,     // Segment d
  0b0010000,     // Segment c
  0b0100000,     // Segment b
  0b1000000      // Segment a
};

// Массив цифр
byte digits[10] = {
  //abcdefg
  0b1111110,     // 0
  0b0011000,     // 1
  0b0110111,     // 2
  0b0111101,     // 3
  0b1011001,     // 4
  0b1101101,     // 5
  0b1101111,     // 6
  0b0111000,     // 7
  0b1111111,     // 8
  0b1111001      // 9
};

// Инициализация дисплея
void initDisplay() {
  strip.begin();
  clearDisplay();
}

// Отрисовка цифры на светодиодном матричном дисплее
void writeDigit(int index, int val) {
  byte digit = digits[val];
  for (int i = 6; i >= 0; i--) {
    int offset = index * (PIXELS_PER_SEGMENT * 7) + i * PIXELS_PER_SEGMENT;
    uint32_t color;
    
    if (digit & 0x01 != 0) {
      color = strip.Color(R, G, B);
    }
    else {
      color = strip.Color(0, 0, 0);
    }
    
    for (int j = offset; j < offset + PIXELS_PER_SEGMENT; j++) {
      strip.setPixelColor(j, color);
    }
    digit = digit >> 1;
  }
}

// Отрисовка цифры на малом дисплее
void write(int index, int val) {
  byte digit = digits[val];
  for (int i = 6; i >= 0; i--) {
    int offset = index * (2 * 7) + i * 2 + 21;
    uint32_t color;
    
    if (digit & 0x01 != 0) {
      color = strip.Color(R, G, B);
    }
    else {
      color = strip.Color(0, 0, 0);
    }
    
    for (int j = offset; j < offset + 2; j++) {
      strip.setPixelColor(j, color);
    }
    digit = digit >> 1;
  }
}

// Отрисовка сегмента на основном дисплее
void writeSegment(int index, int val) {
  byte seg = segments[val];
  for (int i = 6; i >= 0; i--) {
    int offset = index * (PIXELS_PER_SEGMENT * 7) + i * PIXELS_PER_SEGMENT;
    uint32_t color;
    if (seg & 0x01 != 0) {
      if (val == 0) color = strip.Color(255, 0, 0);
      if (val == 1) color = strip.Color(255, 0,  255);
      if (val == 2) color = strip.Color(255, 255, 0);
      if (val == 3) color = strip.Color(255, 0, 255);
      if (val == 4) color = strip.Color(0, 255,  0);
      if (val == 5) color = strip.Color(0, 255, 255);
      if (val == 6) color = strip.Color(0,  0, 255);
    }
    else
      color = strip.Color(0, 0, 0);

    for (int j = offset; j < offset + PIXELS_PER_SEGMENT; j++) {
      strip.setPixelColor(j, color);
    }
    seg = seg >> 1;
  }
}

// Отрисовка сегмента на малом дисплее
void writeSeg(int index, int val) {
  byte seg = segments[val];
  for (int i = 6; i >= 0; i--) {
    int offset = index * (2 * 7) + i * 2 + 21;
    uint32_t color;
    if (seg & 0x01 != 0) {
      if (val == 0) color = strip.Color(255, 0, 0);
      if (val == 1) color = strip.Color(255, 0, 255);
      if (val == 2) color = strip.Color(255, 255, 0);
      if (val == 3) color = strip.Color(255, 0, 255);
      if (val == 4) color = strip.Color(0, 255,  0);
      if (val == 5) color = strip.Color(0, 255, 255);
      if (val == 6) color = strip.Color(0,  0, 255);
      
    }
    else
      color = strip.Color(0, 0, 0);

    for (int j = offset; j < offset + 2; j++) {
      strip.setPixelColor(j, color);
    }
    seg = seg >> 1;
  }
}

// Очистка дисплея
void clearDisplay() {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}

// Различные анимации в режиме ожидания
void disp_Animation() {
  // UP-DOWN
  if(duty == 1) {
    if(millis() - tmr >= 100){
      tmr = millis();
      dir++;
      if(dir == 5){
        dir = 0;
        govno++;
      }
      if(govno == 10){
        duty = random(1, 6);
        govno = 0;
      }
      for (int n = 0; n < PIXELS_DIGITS; n++) {
        if(n < 3) {
          writeSegment(n, x[dir]);
        } 
        if(n > 2 && n < 8) {
          writeSeg(n, x[dir]);
        }
      }
      strip.show();
    }
  }
  
  // CIRCLE
  else if(duty == 2) {
    if(millis() - tmr >= 100) {
      tmr = millis();
      dir++;
      if(dir == 6){
        dir = 0;
        govno++;
      }
      if(govno == 10){
        duty = random(1, 6);
        govno = 0;
      }
      for (int n = 0; n < PIXELS_DIGITS; n++) {
        if(n < 3) {
          writeSegment(n, y[dir]);
        } 
        if(n > 2 && n < 8) {
          writeSeg(n, y[dir]);
        }
      }
      strip.show();
    }
  }
  
  // ZIG-ZAG
  else if(duty == 3) {
    if(millis() - tmr >= 125) {
      tmr = millis();
      dir++;
      if(dir == 4) {
        dir = 0;
        govno++;
      }
      if(govno == 10) {
        duty = random(1, 6);
        govno = 0;
      }
      for (int n = 0; n < PIXELS_DIGITS; n++) {
        if(n < 3) {
          writeSegment(n, z[dir]);
        } 
        if(n > 2 && n < 8) {
          writeSeg(n, z[dir]);
        }
      }
      strip.show();
    }
  }
  
  // INFINITY
  else if(duty == 4) {
    if(millis() - tmr >= 100) {
      tmr = millis();
      dir++;
      if(dir == 8) {
        dir = 0;
        govno++;
      }
      if(govno == 10) {
        duty = random(1, 6);
        govno = 0;
      }
      for (int n = 0; n < PIXELS_DIGITS; n++) {
        if(n < 3) {
          writeSegment(n, w[dir]);
        } 
        if(n > 2 && n < 8) {
          writeSeg(n, w[dir]);
        }
      }
      strip.show();
    }
  }
  
  // Счетчик до максимального значения
  else if(duty == 5) {
    R = 0;
    G = 255;
    B = 0;
    writeSegment(0, 0);
    writeSegment(1, 0);
    writeSegment(2, 0);
    writeSeg(6, 0);
    writeSeg(7, 0);
    if(millis() - tmr >= 10) {
      tmr = millis();
      cntr++;
      if(continu == 1) {
        dir++;
      }
      if(dir == maximus) {
        continu = 0;
        if(cntr % (maximus/9) == 0) {
          blin = !blin;
        }
        if(blin == 0) {
          G = 255;
          digitalWrite(16, 1);
        }
        if(blin == 1) {
          G = 0; 
          digitalWrite(16, 0);
        }
      }
      if(cntr > maximus*2) {
        digitalWrite(16, 0);
        continu = 1;
        dir = 0;
        govno++;
        cntr = 0;
      }
      if(govno == 2) {
        duty = random(1, 6);
        govno = 0;
      }
      write(3, (dir / 100) % 10);
      write(4, (dir / 10) % 10);
      write(5, (dir / 1) % 10);
      strip.show();
    }
  }
}

// Обратный отсчет времени для игры
void disp_CountDOWN() {
  R = 255;
  G = 0;
  B = 0;
  if(millis() - tmrr >= 1000) {
    tmrr = millis();
    num -= 1;
    if(num < 0) {
      sum += 1;
      flag = 1;
      motor = 0;
      game = 0;
    }
    writeSeg(3, 0);
    write(4, num / 10);
    write(5, num % 10);
    strip.show();
  }
}

// Анимация нарастания результата
void disp_CountUP(int num) {
  extern DFRobotDFPlayerMini player;  // Указываем, что player определен в другом месте
  int wait = 0;
  
  player.playFolder(1, 1);
  music = 1;
  zomus = 1;
  sozvuk = 0;
  
  // Показываем нарастающий результат с эффектом изменения цвета
  for (int i = 0; i <= num; i++) {
    // Изменение цвета от зеленого до красного в зависимости от значения
    if(i >= 0 && i <= 333) {
      G = 255;
      R = 0;
    }
    if(i >= 333 && i <= 666) {
      R = (i-333)/1.3;
    }
    if(i >= 666 && i <= 999) {
      R = 255;
      G = 255 - (((i-666)/1.3));
    }
    if(i == 999) {
      R = 255;
      G = 0;
      B = 0;
    }

    writeDigit(0, (i / 100) % 10);
    writeDigit(1, (i / 10) % 10);
    writeDigit(2, (i / 1) % 10);
    strip.show();
    
    // Динамическое изменение времени задержки для плавного замедления
    if(i > (num*0.94)) {
      wait = (i - num*0.94) * (100 - 75) / (num - num*0.94) + 75;
    }
    
    // Изменение звука при достижении почти максимального значения
    if(i > (num*0.934) && i < (num*0.939) && music == 1) {
      player.stop();
      player.playFolder(2, 1);
      music = 0;
    }
    
    delay(wait);
  }
  
  // Воспроизведение звука в зависимости от силы удара
  if(num >= 0 && num <= 450 && sost == 0 && zomus == 1) {
    sozvuk = random(1, 6);
    player.playFolder(4, sozvuk); // слабый
    zomus = 0;
  }
  else if(num >= 450 && num <= 750 && sost == 0 && zomus == 1) {
    sozvuk = random(1, 5);
    player.playFolder(5, sozvuk); // средний
    zomus = 0;
  }
  else if(num >= 750 && num <= 900 && sost == 0 && zomus == 1) {
    sozvuk = random(1, 3);
    player.playFolder(6, sozvuk); // сильный
    zomus = 0;
  }
  else if(num >= 900 && num <= 999 && sost == 0 && zomus == 1) {
    sozvuk = random(1, 3);
    player.playFolder(7, sozvuk); // самый сильный
    zomus = 0;
  }
  else if(sost == 1 && zomus == 1) {
    sozvuk = random(1, 5);
    player.playFolder(8, sozvuk); // рекорд
    zomus = 0;
  }
  
  wait = 0;
}
