#include <ESP8266WiFi.h>
#include <WiFiManager.h> 

#define SERIAL_SPEED 115200 // ボーレート
#define WM_FIXERASECONFIG // use erase flash fix, esp8266 2.4.0
#define PinSensorePIR D1  // water sensorのPIR

// HTTP サーバサイドの情報
#define IMG_BUF 4096
const char* host   = "172.18.8.205"; //サーバip
const int httpPort = 80;
const char* path   = "/";

WiFiClient client;
char buf[IMG_BUF];
 
// 水流センサのパラメータ
volatile int pulseCount;
float amount;
unsigned long oldTime;
float total_amount=0;
const float coefficient=5; //流量調整係数

void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial.println("");

  //ネットワークに接続 wifimanager
  WiFiManager wifiManager;
  wifiManager.setBreakAfterConfig(true);
//  wifiManager.resetSettings(); //wifi情報リセット
    
  if (!wifiManager.autoConnect("WaterSensor", "password")) {
    Serial.println("failed to connect, we should reset as see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  Serial.println("");
  Serial.println("WiFi Connected.");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
  Serial.println("");

  //流量センサ
  pinMode(D1, INPUT);
  digitalWrite(PinSensorePIR, HIGH); // プルアップ
  oldTime = millis();
}

void flow (){pulseCount++;}//割り込みに使うためのインクリメント関数

void loop() {
  //流量センサのループ
  attachInterrupt(digitalPinToInterrupt(PinSensorePIR), flow, RISING);//割り込み設定
  if(millis() >= (oldTime + 1000)){
  oldTime=millis();
  amount=((pulseCount /coefficient)/60);
  total_amount += amount;
  pulseCount = 0;
//  Serial.println(total_amount);//総水量の表示

  // HTTP サーバ接続
  Serial.println("送信します");
  if (!client.connect(host, httpPort)){Serial.println("接続に失敗しました");return;}

    String body = String(total_amount);
    client.print(String("POST ") + path + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "Content-Length:" + String(body.length()) + "\r\n" +
                "Connection: close\r\n\r\n" +
                body);

    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 10000) {
        Serial.println(">>> タイムアウトしました");
        client.stop();
        return;
      }
    }
    Serial.println("--------------------");
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
    Serial.println("");
    Serial.println("--------------------");
  }
}
