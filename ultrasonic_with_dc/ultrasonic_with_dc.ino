int tri = 7;      // Ultrasonic sensor trigger pin
int eco = 6;      // Ultrasonic sensor echo pin
int a = 8;        // L293D Motor driver pin for IN1
int b = 9;        // L293D Motor driver pin for IN2
int buzzer = 11;  // Buzzer pin
int timeInMicro;
int distanceInCm;

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);

  // Configure the pins for ultrasonic sensor, motor driver, and buzzer
  pinMode(tri, OUTPUT);  // Trigger pin as output
  pinMode(eco, INPUT);   // Echo pin as input
  pinMode(a, OUTPUT);    // Motor driver pin IN1 as output
  pinMode(b, OUTPUT);    // Motor driver pin IN2 as output
  pinMode(buzzer, OUTPUT); // Buzzer pin as output
}

void loop() {
  // Send a short LOW pulse to ensure a clean start
  digitalWrite(tri, LOW);
  delayMicroseconds(2);

  // Send a 10-microsecond HIGH pulse to trigger the sensor
  digitalWrite(tri, HIGH);
  delayMicroseconds(10);  // Increased delay to 10µs as recommended for HC-SR04 sensors
  digitalWrite(tri, LOW);

  // Read the echo pulse duration in microseconds
  timeInMicro = pulseIn(eco, HIGH);

  // Calculate distance in cm (speed of sound in air ~343m/s, or 29µs per cm round-trip)
  distanceInCm = timeInMicro / 29 / 2;

  // Print the distance to the serial monitor
  Serial.println(distanceInCm);

  // Check if distance is less than or equal to 13 cm
  if (distanceInCm <= 13) {
    // Turn on the buzzer
    digitalWrite(buzzer, HIGH);

    // Turn on the motor (assuming you want to rotate in a specific direction)
    digitalWrite(a, HIGH);  // Motor moves in one direction
    digitalWrite(b, LOW);   // Set the other input low
  } else {
    // Turn off the buzzer
    digitalWrite(buzzer, LOW);

    // Turn off the motor
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
  }

  // Wait for 500ms before the next reading
  delay(500);
}
