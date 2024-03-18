#define STEP    32
#define DIR     33
#define SENSOR  34

float RPM_MAX = 80.0;
int sensor, interval=2;
float angle = 90;
int steps = angle*2/1.8;

void setup() {
  Serial.begin(115200); 
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(SENSOR, INPUT);

  digitalWrite(DIR, LOW);
  digitalWrite(STEP, LOW);
}

void loop() {
  sensor = analogRead(SENSOR);
  if (sensor > 300){
  // interval = (int)(3.0/(10.0 * RPM_MAX) * 1000000);
    interval = (int)((3.0/(10.0 * (analogRead(SENSOR)/4095.0) * RPM_MAX)) * 1000000);
    digitalWrite(DIR, HIGH);
    // Serial.printf("FFFFF: %d, RRRRR: %f, RRRRR: %d\n", analogRead(SENSOR), (3.0/(10.0 * (analogRead(SENSOR)/4095.0) * RPM_MAX)) * 1000000, interval);

    for (int i=0; i<steps; i++) {
      // pre_time = micros();
      digitalWrite(STEP, HIGH);
      delayMicroseconds(interval/2);
      digitalWrite(STEP, LOW);
      delayMicroseconds(interval/2);
      // true_speed = int((3.0/(10.0*float(micros()-pre_time)))*1000000);
    }
    delay(500);

    digitalWrite(DIR, LOW);
    for (int i=0; i<steps; i++) {
      // pre_time = micros();
      digitalWrite(STEP, HIGH);
      delayMicroseconds(interval/2);
      digitalWrite(STEP, LOW);
      delayMicroseconds(interval/2);
      // true_speed = int((3.0/(10.0*float(micros()-pre_time)))*1000000);
    }
    delay(500);
  }

  // else{
  //   digitalWrite(STEP, LOW);
  // }
}