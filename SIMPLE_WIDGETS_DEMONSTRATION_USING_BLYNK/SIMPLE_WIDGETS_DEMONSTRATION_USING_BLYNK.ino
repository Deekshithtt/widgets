#define BLYNK_TEMPLATE_ID "TMPL3Xbb1AnsQ"
#define BLYNK_TEMPLATE_NAME "IOT"
#define BLYNK_AUTH_TOKEN "ysuaEFfXwRCLTbhMeh86D8U_LS030Z5k"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "ysuaEFfXwRCLTbhMeh86D8U_LS030Z5k";
char ssid[] = "DON";
char pass[] = "00001111";

const int dcMotor = D1;
int slider;
const int inPut = D0;
int mappedValue = 0;
int relayPin = D2;
const int ultrasonicTrigPin = D4;
const int ultrasonicEchoPin = D5;
const int potPin = A0;

BlynkTimer timer;

void setup()
{
  Serial.begin(115200);

  Serial.println("Connecting to WiFi...");
 Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
 pinMode(relayPin, OUTPUT);
  pinMode(dcMotor, OUTPUT);
  pinMode(inPut, OUTPUT);
  digitalWrite(inPut, HIGH);

  pinMode(ultrasonicTrigPin, OUTPUT);
  pinMode(ultrasonicEchoPin, INPUT);

  timer.setInterval(1000L, sendUltrasonicData);
}

void loop()
{
  Blynk.run();
  // Potentiometer control
  int potValue = analogRead(potPin);
  int mappedPotValue = map(potValue, 0, 1023, 0, 255);
  Blynk.virtualWrite(V5, potValue);
  timer.run();
}

BLYNK_WRITE(V0) {
  int relayState = param.asInt(); // Get value from Blynk app (0 or 1)

  // Set the relay state
  digitalWrite(relayPin, relayState);
}


void sendUltrasonicData()
{
  long duration, distance;
  digitalWrite(ultrasonicTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTrigPin, LOW);
  duration = pulseIn(ultrasonicEchoPin, HIGH);
  distance = (duration * 0.0343) / 2;
  Blynk.virtualWrite(V3, distance);
}
BLYNK_WRITE(V6) {
  slider = param.asInt();
  mappedValue = map(slider, 0, 1023, 0, 255);
  // generate PWM signal
  analogWrite(dcMotor, mappedValue);

  // Print information to Serial Monitor
  Serial.print("Slider Value: ");
  Serial.print(slider);
  Serial.print(" | Mapped Value: ");
  Serial.println(mappedValue);
}



