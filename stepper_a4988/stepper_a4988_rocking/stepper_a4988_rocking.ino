#include <uTimerLib.h>

#define STEP    32
#define DIR     33
#define SENSOR  34

float RPM_MAX = 30.0;
int sensor;
float angle = 45;
int steps = angle*2/1.8;

unsigned long tmr;
int move_direction = 0;
int speed = 0;
float angle_now = 0;

int interval = (int)((3.0/(10.0 * RPM_MAX)) * 1000000);

void setup() {
  Serial.begin(115200); 
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(SENSOR, INPUT);

  digitalWrite(DIR, LOW);
  digitalWrite(STEP, LOW);

  // タイマ割り込み設定
  TimerLib.setInterval_us(measure, 500000);
}

void loop() {
  if(move_direction)  digitalWrite(DIR, HIGH);
  else                digitalWrite(DIR, LOW);
  
  for (int i=0; i<steps; i++) {
      tmr = millis();
      digitalWrite(STEP, HIGH);
      delayMicroseconds(interval/2);
      digitalWrite(STEP, LOW);
      delayMicroseconds(interval/2);
      if(move_direction)  angle_now+=1.8;
      else                angle_now-=1.8;
      speed = 1/200.0 * 1/((millis() - tmr)/1000.0)*60.0;
  }
  
  move_direction = ~move_direction;  // 値を反転
}


 
void measure() {
  printf("speed[RPM] : %d\t angle[deg] : %f\n", speed, angle_now);
}