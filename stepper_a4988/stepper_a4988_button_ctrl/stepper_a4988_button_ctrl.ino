#define STEP    32
#define DIR     33
#define SENSOR  34
#define SW1     14
#define SW2     27
#define SW3     26
#define SW4     25

float RPM_MAX = 1000.0;
int sensor, interval, true_speed, pre_time;
bool on_sw1, on_sw2, on_sw3, on_sw4;
float rpm_list[4] = {10.0, 50.0, 100.0, 150.0};

void setup() {
  Serial.begin(115200); 
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(SENSOR, INPUT);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(SW4, INPUT_PULLUP);
  on_sw1=on_sw2=on_sw3=on_sw4=false;

  digitalWrite(DIR, LOW);
  digitalWrite(STEP, LOW);
}

void loop() {
  sensor = analogRead(SENSOR);
  if (sensor > 300){
    interval = (int)((3.0/(10.0 * (analogRead(SENSOR)/4095.0) * RPM_MAX)) * 1000000);
    digitalWrite(DIR, HIGH);
    // Serial.printf("FFFFF: %d, RRRRR: %f, RRRRR: %d\n", analogRead(SENSOR), (3.0/(10.0 * (analogRead(SENSOR)/4095.0) * RPM_MAX)) * 1000000, interval);

    // for (int i=0; i<200; i++) {
      // pre_time = micros();
      digitalWrite(STEP, HIGH);
      delayMicroseconds(interval/2);
      digitalWrite(STEP, LOW);
      delayMicroseconds(interval/2);
      // true_speed = int((3.0/(10.0*float(micros()-pre_time)))*1000000);
  }

  else{
    digitalWrite(STEP, LOW);
  }

  // if      (!on_sw1 && digitalRead(SW1)==LOW) {on_sw1=true; RPM_MAX=rpm_list[0];}// Serial.println("test SW1");}
  // else if (!on_sw2 && digitalRead(SW2)==LOW) {on_sw2=true; RPM_MAX=rpm_list[1];}// Serial.println("test SW2");}
  // else if (!on_sw3 && digitalRead(SW3)==LOW) {on_sw3=true; RPM_MAX=rpm_list[2];}// Serial.println("test SW3");}
  // else if (!on_sw4 && digitalRead(SW4)==LOW) {on_sw4=true; RPM_MAX=rpm_list[3];}// Serial.println("test SW4");}
  // else                                      {on_sw1=on_sw2=on_sw3=on_sw4=false;}
  // Serial.printf("SW1: %d, SW2: %d, SW3: %d, SW4: %d\n", digitalRead(SW1), digitalRead(SW2), digitalRead(SW3), digitalRead(SW4));
  // Serial.printf("target_rpm: %d, true_rpm: %d\n", int((analogRead(SENSOR)/4095.0) * RPM_MAX), true_speed); 
}