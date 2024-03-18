#define STEP    32
#define DIR     33
#define SENSOR  34
#define SW      35
const float RPM_MAX = 1000.0;

int sensor, interval, true_speed, pre_time;

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

  // Serial.printf("target_rpm: %d, true_rpm: %d\n", int((analogRead(SENSOR)/4095.0) * RPM_MAX), true_speed); 
}