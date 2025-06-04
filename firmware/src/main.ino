#include <Adafruit_NeoPixel.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h" 
#define kzt 100
#define difficult 916076207
#define PIXELS_PER_SEGMENT  3     // Number of LEDs in each Segment
#define PIXELS_DIGITS       8     // Number of connected Digits 
#define PIXELS_PIN          4     // GPIO Pin
#define maximum  999
#define PIN_MP3_TX  0 
#define PIN_MP3_RX  2 
#define coinPin  14
#define moneyPin  13
#define timeAllPulse1 1300 
#define timeAllPulse2 1300
int num = 41;
int cntr = 0;
uint32_t tmrr;
uint32_t tmr;
uint32_t dfp;
int dir = 0;
int duty = 1;
int govno = 0;
char x[5] = {5, 0, 2, 0, 5};
char y[6] = {6, 5, 4, 3, 2, 1};
char z[4] = {6, 1, 4, 3};
char w[8] = {6, 5, 4, 0, 1, 2, 3, 0};
volatile unsigned long counter = 0;
unsigned long timer1 = 0;
unsigned long timer2 = 0;
unsigned long res = 0;
unsigned long late = 0;
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
byte kol = 0;
byte posl = 0;
byte R = 0;
byte G = 0;
byte B = 0;
int wait = 0;
int money = 0;
int sum=0;
int sumcoins = 0;
int lates = 0;
int maximus = 700;
int coins = 0;
int tokens = 0;
int latcoin = 0;
int sozvuk = 0;
unsigned long timeCount1=0;
unsigned long timeCount2=0;
uint32_t animtime=0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(133, PIXELS_PIN, NEO_GRB + NEO_KHZ800);
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
DFRobotDFPlayerMini player;
//Pixel Arrangement
/*
          b
        a   c
          g
        f   d
          e

*/
// Segment array
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

//Digits array
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

void writeDigit(int index, int val) {
  byte digit = digits[val];
  for (int i = 6; i >= 0; i--) {
    int offset = index * (PIXELS_PER_SEGMENT * 7) + i * PIXELS_PER_SEGMENT;
    uint32_t color;
    
    if (digit & 0x01 != 0) {
      if (val == 1) color = strip.Color(R, G, B);
      if (val == 2) color = strip.Color(R, G, B);
      if (val == 3) color = strip.Color(R, G, B);
      if (val == 4) color = strip.Color(R, G, B);
      if (val == 5) color = strip.Color(R, G, B);
      if (val == 6) color = strip.Color(R, G, B);
      if (val == 7) color = strip.Color(R, G, B);
      if (val == 8) color = strip.Color(R, G, B);
      if (val == 9) color = strip.Color(R, G, B);
      if (val == 0) color = strip.Color(R, G, B);
    }
    else
      color = strip.Color(0, 0, 0);
    
    for (int j = offset; j < offset + PIXELS_PER_SEGMENT; j++) {
      strip.setPixelColor(j, color);
    }
    digit = digit >> 1;
  }
}


void write(int index, int val) {
  byte digit = digits[val];
  for (int i = 6; i >= 0; i--) {
    int offset = index * (2 * 7) + i * 2 + 21;
    uint32_t color;
    
    if (digit & 0x01 != 0) {
      if (val == 1) color = strip.Color(R, G, B);
      if (val == 2) color = strip.Color(R, G, B);
      if (val == 3) color = strip.Color(R, G, B);
      if (val == 4) color = strip.Color(R, G, B);
      if (val == 5) color = strip.Color(R, G, B);
      if (val == 6) color = strip.Color(R, G, B);
      if (val == 7) color = strip.Color(R, G, B);
      if (val == 8) color = strip.Color(R, G, B);
      if (val == 9) color = strip.Color(R, G, B);
      if (val == 0) color = strip.Color(R, G, B);
    }
    else
      color = strip.Color(0, 0, 0);
    
    
    for (int j = offset; j < offset + 2; j++) {
      strip.setPixelColor(j, color);
    }
    digit = digit >> 1;
  }
}

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

void clearDisplay() {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}

void disp_Animation() {
  //UP-DOWN
  if(duty == 1){
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
for (int n = 0; n < PIXELS_DIGITS; n++)
{
      if(n<3){
      writeSegment(n, x[dir]);
      } 
      if(n>2 && n<8){
      writeSeg(n, x[dir]);
      }
}
strip.show();
}
}
 
  //CIRCLE
  
if(duty == 2){
  
    if(millis() - tmr >= 100){
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
for (int n = 0; n < PIXELS_DIGITS; n++)
{
      if(n<3){
      writeSegment(n, y[dir]);
      } 
      if(n>2 && n<8){
      writeSeg(n, y[dir]);
      }
}
strip.show();
}
}  
 

  
  //ZIG-ZAG
  
  if(duty == 3){
  
    if(millis() - tmr >= 125){
  tmr = millis();
  dir++;
  if(dir == 4){
    dir = 0;
    govno++;
  }
  if(govno == 10){
    duty = random(1, 6);
    govno = 0;
  }
for (int n = 0; n < PIXELS_DIGITS; n++)
{
      if(n<3){
      writeSegment(n, z[dir]);
      } 
      if(n>2 && n<8){
      writeSeg(n, z[dir]);
      }
}
strip.show();
}
}  
  
//INFINITY

  if(duty == 4){
  
    if(millis() - tmr >= 100){
  tmr = millis();
  dir++;
  if(dir == 8){
    dir = 0;
    govno++;
  }
  if(govno == 10){
    duty = random(1, 6);
    govno = 0;
  }
for (int n = 0; n < PIXELS_DIGITS; n++)
{
      if(n<3){
      writeSegment(n, w[dir]);
      } 
      if(n>2 && n<8){
      writeSeg(n, w[dir]);
      }
}
strip.show();
}
}
  
 if(duty == 5){
  R = 0;
  G = 255;
  B = 0;
  writeSegment(0, 0);
  writeSegment(1, 0);
  writeSegment(2, 0);
  writeSeg(6, 0);
  writeSeg(7, 0);
  if(millis() - tmr >= 10){
  tmr = millis();
  cntr++;
  if(continu == 1){
  dir++;
  }
  if(dir == maximus){
    continu = 0;
    if(cntr%(maximus/9) == 0){
      blin = !blin;
    }
    if(blin == 0){
      G = 255;
      digitalWrite(16, 1);
    }
    if(blin == 1){
      G = 0; 
      digitalWrite(16, 0);
    }
  }
  if(cntr > maximus*2){
    digitalWrite(16, 0);
    continu = 1;
    dir = 0;
    govno++;
    cntr = 0;
  }
  if(govno == 2){
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

void disp_CountDOWN() {
  R = 255;
  G = 0;
  B = 0;
  if(millis() - tmrr >= 1000){
    tmrr = millis();
    num-=1;
    if(num < 0){
      sum+=1;
      flag = 1;
      res = 1;
      motor = 0;
      game = 0;
    }
    writeSeg(3, 0);
    write(4, num / 10);
    write(5, num % 10);
    strip.show();
  }
}

void disp_CountUP(int num) {
  player.playFolder(1, 1);
  music = 1;
  zomus = 1;
  sozvuk = 0;
  for (int i = 0; i <= num; i++) {
    if(i>=0 && i<=333){
       G = 255;
     }
    if(i>=333 && i<=666){
       R = (i-333)/1.3;
     }
    if(i>=666 && i<=999){
       R = 255;
       G = 255 - (((i-666)/1.3));
      
     }
    if(i == 999){
      R = 255;
      G = 0;
      B = 0;
    }

    writeDigit(0, (i / 100) % 10);
    writeDigit(1, (i / 10) % 10);
    writeDigit(2, (i / 1) % 10);
    strip.show();
    if(i > (num*0.94)){
        wait = (i - num*0.94) * (100 - 75) / (num - num*0.94) + 75;
    }
    if(i > (num*0.934) && i < (num*0.939) && music == 1){
        player.stop();
        player.playFolder(2, 1);
        music = 0;
    }
    delay(wait);
  }
  //======================Музыка==========================

  if(num >= 0 && num <= 450 && sost == 0 && zomus == 1){
    sozvuk = random(1, 6);
    player.playFolder(4, sozvuk);//слабый
    zomus = 0;
  }

  if(num >= 450 && num <= 750 && sost == 0 && zomus == 1){
    sozvuk = random(1, 5);
    player.playFolder(5, sozvuk);//средний
    zomus = 0;
  }

  if(num >= 750 && num <= 900 && sost == 0 && zomus == 1){
    sozvuk = random(1, 3);
    player.playFolder(6, sozvuk);//сильный
    zomus = 0;
  }
  
  if(num >= 900 && num <= 999 && sost == 0 && zomus == 1){
    sozvuk = random(1, 3);
    player.playFolder(7, sozvuk);//самый сильный
    zomus = 0;
  }
  
  if(sost == 1 && zomus == 1){
    sozvuk = random(1, 5);
    player.playFolder(8, sozvuk);//рекорд
    zomus = 0;
  }
  
  //======================================================
  wait = 0;
}

ICACHE_RAM_ATTR void count_pulse1()
{
detachInterrupt(digitalPinToInterrupt(moneyPin));
money++;
if(money==1)
timeCount1=millis();
attachInterrupt(digitalPinToInterrupt(moneyPin), count_pulse1, FALLING);
}

ICACHE_RAM_ATTR void count_pulse2()
{
detachInterrupt(digitalPinToInterrupt(coinPin));
coins++;
if(coins==1)
timeCount2=millis();
attachInterrupt(digitalPinToInterrupt(coinPin), count_pulse2, FALLING);
}


ICACHE_RAM_ATTR void buttonTick() {
  if(sum>0 && motor == 1){
  kol++;
  counter = ESP.getCycleCount();
  }
}

void setup() {
  
  strip.begin();
  softwareSerial.begin(9600);
  clearDisplay();
  if (player.begin(softwareSerial)) {
    player.volume(30);
  } 
  
  startAnimation = 1;
  pinMode(5, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(moneyPin,INPUT);
  pinMode(coinPin, INPUT);
  pinMode(12, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(12), buttonTick, CHANGE);
  attachInterrupt(digitalPinToInterrupt(coinPin), count_pulse2, FALLING);
  attachInterrupt(digitalPinToInterrupt(moneyPin),count_pulse1,FALLING);
}

void loop() {
  if(millis() - dfp >= (unsigned long) 24*60*60*1000 && sum == 0){
    dfp = millis();
    maximus = 700;
  }
// ==========================деньги============================

 if(money>0 && (millis()-timeCount1)>timeAllPulse1){
  sum+=(money*100)/kzt;
  kol = 0;
  R = 255;
  G = 0;
  B = 0;
  money=0;
}

if(coins>0 && (millis()-timeCount2)>timeAllPulse2)
{
  switch(coins)
{
    
    case 2:
        tokens=10;
        break;
    case 4:
        tokens=20;
        break;
    case 6:
        tokens=50;
        break;
    case 8:
        tokens=100;
        break;
    case 10:
        tokens=200;
        break;
}
sumcoins+=tokens;

if(sumcoins/kzt > latcoin){
sum += sumcoins/kzt - latcoin;
latcoin = sumcoins/kzt;
kol = 0;
R = 255;
G = 0;
B = 0;
}
coins=0;
}

if(sum != lates){
  pol = 1;
  lates = sum;
}
if(pol == 1){
  startAnimation = 0;
  if(sum>0){
    stAnim = 0;
  }
  if(ochistka == 1){
     clearDisplay();
     ochistka = 0;
  }
  write(6, sum / 10);
  write(7, sum % 10);
  strip.show();
  pol = 0;
}
// ============================================================
// =========================анимация===========================

if(startAnimation == 1){
    ochistka = 1;
    disp_Animation();
}
if(stAnim == 1 && millis() - animtime >= 20000){
    ochistka = 1;
    disp_Animation();
}

// ============================================================
if(sum>0 && analogRead(A0) > 650 && analogRead(A0) < 920 && motor == 0 && game == 0){
      num = 31;
      sost = 0;
      game = 1;
      motor = 0; 
}
if(sum==0 && analogRead(A0) > 650 && analogRead(A0) < 920){  
       player.playFolder(9, 1);
}

 if(game == 1){
   player.stop();
   digitalWrite(5, 1);
   delay(200);
   digitalWrite(5, 0);
   delay(500);
   digitalWrite(5, 1);  
   delay(200);
   digitalWrite(5, 0);
   delay(300);
   digitalWrite(16, 1);
   player.playFolder(3, 1);
   kol = 0;
   motor = 1;
   startTimer = 1;
   game = 0;
 }

if(startTimer == 1){
    disp_CountDOWN();
}
 if(kol > 0 && posl == 0){
   if(motor == 1){
     timer1 = counter;
     posl = kol;
   }
 }
 if(kol > posl){
   if(motor == 1){
   timer2 = counter;
   motor = 0;
   }
   posl = 0;
   kol = 0;
 }

if ( timer1 != 0 && timer2 != 0 && timer2 > timer1 && kol == 0)
    {
        res = difficult/(timer2 - timer1);
        if(res > maximum){
          res = maximum;
        }
        startTimer = 0;
        timer1 = 0;
        timer2 = 0;
    }
  
if(res != late){
     flag = 1;
     late = res;
  }
if(flag == 1){
    R = 0;
    G = 0;
    B = 0;
    sum -=1;
    digitalWrite(16, 0);
    player.stop();
    startTimer = 0;
    if(maximus < res){
      sost = 1;
    }
    disp_CountUP(res);
    if(maximus < res){
      sum+=1;
    maximus = res;
    }
    write(3, (maximus / 100) % 10);
    write(4, (maximus / 10) % 10);
    write(5, (maximus / 1) % 10);
    strip.show();
    if(sum == 0){
      stAnim = 1;
      animtime = millis();
    }
    flag = 0;
  }
   
   
}