

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Set these to run example.
#define FIREBASE_HOST "arduinowear-36fbb-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "klyQzBUltQFnDysAWxJ5qpVGBfU8PLZfKgr634wl"
#define WIFI_SSID "DarrelSteve"
#define WIFI_PASSWORD "12345@#$_"

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  delay(1000);
}

int n = 0;

void loop() {
  if(Serial.available()){
    if(Firebase.pushInt(firebaseData, "/Bpm", Serial.read())){
      Serial.println("Bpm updated successfuly");
      delay(1000);
      }else{
        Serial.println(firebaseData.errorReason());
        }
   }else{
     Serial.println("No data from sensor please wait");
    }

    delay(1000);
}
