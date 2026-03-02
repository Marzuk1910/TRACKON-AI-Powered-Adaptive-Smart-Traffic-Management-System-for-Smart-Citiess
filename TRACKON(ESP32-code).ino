#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "mazx";
const char* password = "mazx.1910";

String channelID = "3236956";
String readAPIKey = "NFJVRNYWOAV36256";

// ===== ROAD 1 =====
#define R1_RED     23
#define R1_YELLOW  26
#define R1_GREEN   27

// ===== ROAD 2 =====
#define R2_RED     14
#define R2_YELLOW  12
#define R2_GREEN   13

// ===== ROAD 3 =====
#define R3_RED     18
#define R3_YELLOW  19
#define R3_GREEN   21

// ===== ROAD 4 =====
#define R4_RED     5
#define R4_YELLOW  17
#define R4_GREEN   16

int vehicleCount = 0;
int greenTime = 10;

// ===== GREEN TIME LOGIC =====
int calculateGreenTime(int count) {
  if (count <= 5) return 10;
  else if (count <= 10) return 20;
  else if (count <= 20) return 30;
  else return 40;
}

// ===== ALL RED FUNCTION =====
void allRed() {
  digitalWrite(R1_RED, HIGH);
  digitalWrite(R2_RED, HIGH);
  digitalWrite(R3_RED, HIGH);
  digitalWrite(R4_RED, HIGH);

  digitalWrite(R1_YELLOW, LOW);
  digitalWrite(R2_YELLOW, LOW);
  digitalWrite(R3_YELLOW, LOW);
  digitalWrite(R4_YELLOW, LOW);

  digitalWrite(R1_GREEN, LOW);
  digitalWrite(R2_GREEN, LOW);
  digitalWrite(R3_GREEN, LOW);
  digitalWrite(R4_GREEN, LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(R1_RED, OUTPUT);
  pinMode(R1_YELLOW, OUTPUT);
  pinMode(R1_GREEN, OUTPUT);

  pinMode(R2_RED, OUTPUT);
  pinMode(R2_YELLOW, OUTPUT);
  pinMode(R2_GREEN, OUTPUT);

  pinMode(R3_RED, OUTPUT);
  pinMode(R3_YELLOW, OUTPUT);
  pinMode(R3_GREEN, OUTPUT);

  pinMode(R4_RED, OUTPUT);
  pinMode(R4_YELLOW, OUTPUT);
  pinMode(R4_GREEN, OUTPUT);

  allRed();

  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
}

void loop() {

  // ===== READ VEHICLE COUNT =====
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = "http://api.thingspeak.com/channels/" + channelID +
                 "/fields/1/last.txt?api_key=" + readAPIKey;

    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      vehicleCount = http.getString().toInt();
      greenTime = calculateGreenTime(vehicleCount);

      Serial.print("Vehicle Count: ");
      Serial.println(vehicleCount);
      Serial.print("Green Time: ");
      Serial.println(greenTime);
    }
    http.end();
  }

  // ===== ROAD 1 =====
  allRed();
  digitalWrite(R1_RED, LOW);
  digitalWrite(R1_GREEN, HIGH);
  delay(greenTime * 1000);

  digitalWrite(R1_GREEN, LOW);
  digitalWrite(R1_YELLOW, HIGH);
  delay(3000);
  digitalWrite(R1_YELLOW, LOW);
  digitalWrite(R1_RED, HIGH);

  // ===== ROAD 2 =====
  allRed();
  digitalWrite(R2_RED, LOW);
  digitalWrite(R2_GREEN, HIGH);
  delay(greenTime * 1000);

  digitalWrite(R2_GREEN, LOW);
  digitalWrite(R2_YELLOW, HIGH);
  delay(3000);
  digitalWrite(R2_YELLOW, LOW);
  digitalWrite(R2_RED, HIGH);

  // ===== ROAD 3 =====
  allRed();
  digitalWrite(R3_RED, LOW);
  digitalWrite(R3_GREEN, HIGH);
  delay(greenTime * 1000);

  digitalWrite(R3_GREEN, LOW);
  digitalWrite(R3_YELLOW, HIGH);
  delay(3000);
  digitalWrite(R3_YELLOW, LOW);
  digitalWrite(R3_RED, HIGH);

  // ===== ROAD 4 =====
  allRed();
  digitalWrite(R4_RED, LOW);
  digitalWrite(R4_GREEN, HIGH);
  delay(greenTime * 1000);

  digitalWrite(R4_GREEN, LOW);
  digitalWrite(R4_YELLOW, HIGH);
  delay(3000);
  digitalWrite(R4_YELLOW, LOW);
  digitalWrite(R4_RED, HIGH);
}
