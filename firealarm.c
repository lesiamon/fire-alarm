float temp;
float vout;
float vout1;
int LED = 13;  // Red LED for fire alert
int gasSensor;
int piezo = 7;  // Buzzer
const int led = 8;  // Blue LED for motion detection
const int pir = 2;  // PIR pin
int motion;
const int greenLED = 9; // Green LED for normal operation

void setup() {
  // Initial setup for sensors and actuators
  pinMode(A0, INPUT);  // Gas sensor
  pinMode(A1, INPUT);  // Temperature sensor
  pinMode(LED, OUTPUT); // Fire LED (Red)
  pinMode(piezo, OUTPUT); // Buzzer
  pinMode(led, OUTPUT); // Blue LED for motion detection
  pinMode(pir, INPUT);  // PIR motion sensor
  pinMode(greenLED, OUTPUT); // Green LED for normal condition

  Serial.begin(9600);  // Start serial communication
}

void loop() {
  // Reading temperature sensor
  vout = analogRead(A1);  // Read temperature sensor value
  vout1 = (vout / 1023.0) * 5000;  // Convert sensor reading to voltage
  temp = (vout1 - 500) / 10;  // Convert voltage to temperature in Celsius

  // Reading gas sensor
  gasSensor = analogRead(A0);  // Read gas sensor value

  // Check for fire (temperature >= 80°C OR gas level >= 100)
  if (temp >= 80 || gasSensor >= 100) {
    // Fire detected: Turn on red LED, buzzer, and turn off green LED
    digitalWrite(LED, HIGH);  // Turn on red LED (fire alert)
    digitalWrite(piezo, HIGH);  // Turn on buzzer (fire alert)
    digitalWrite(greenLED, LOW);  // Turn off green LED (normal condition)

    // Check for motion (casualty detection)
    motion = digitalRead(pir);
    if (motion) {
      digitalWrite(led, HIGH);  // Turn on blue LED if motion is detected
    } else {
      digitalWrite(led, LOW);  // Turn off blue LED if no motion is detected
    }
  } else {
    // No fire detected: Turn off red LED, buzzer, and turn on green LED
    digitalWrite(LED, LOW);  // Turn off red LED (no fire)
    digitalWrite(piezo, LOW);  // Turn off buzzer
    digitalWrite(greenLED, HIGH);  // Turn on green LED (system normal)
    digitalWrite(led, LOW);  // Ensure blue LED is off (no motion being tracked)
  }

  // Serial output for debugging
  Serial.print("Temperature (C) = ");
  Serial.print(temp);
  Serial.print("\t");
  Serial.print("Gas Sensor Value = ");
  Serial.println(gasSensor);

  // Delay before the next loop iteration
  delay(1000);  // 1 second delay
}
