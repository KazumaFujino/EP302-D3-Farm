#include <FS.h>
//#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 

#define SERIAL_SPEED 115200
#define WM_FIXERASECONFIG // use erase flash fix, esp8266 2.4.0

// Web page (Port 8080) 
ESP8266WebServer server(8080);
static const char* cpResponse200 = "<HTML>"
 "<BODY style='background-color:#ffffde;font-family:sans-serif;font-size:40px;'>"
 "CONTROL WEB<br/><br/>"
 "<a href=/cmd?CMD=dummy>DUMMY</a><br/>"
 "</BODY></HTML>\r\n";
//流量センサのパラメータ
#define PinSensorePIR D1
volatile int pulseCount;
float ryuuryou;
unsigned long oldTime;
float sam_ryuuryou=0;
const float keisuu=5; //流量調整係数

void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial.println("");

  //WiFiManager
  WiFiManager wifiManager;
  wifiManager.setBreakAfterConfig(true);
//  wifiManager.resetSettings();
    
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

  // Set up mDNS responder:
  if (!MDNS.begin("d3")) { // d3.local
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  Serial.println("");

  // WebServer Commands
  server.on("/cmd", WebCommand);
  
  /*// WebServer Handles
  server.on("/", [](){
    String html = HTML_HEADER "<h1>EP302 D3!</h1>" HTML_FOOTER;
    server.send(200, "text/html", html);
  });
  server.on("/member0", [](){
    String html = HTML_HEADER "<h1>Kazuma Fujino</h1>" HTML_FOOTER;
    server.send(200, "text/html", html);
  }); */
  
  server.begin();

  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 8080);

  //流量センサ
  pinMode(D1, INPUT);
  digitalWrite(PinSensorePIR, HIGH); // プルアップ
  oldTime = millis();
}

void WebCommand() {
  String cmd = server.arg("CMD");
  if (cmd == "dummy")  {
    // hogehoge...
  }
  else   if (cmd == "reset")  { //　resetコマンドでWiFi再設定
    WiFiManager wifiManager;
    delay(1000);
    Serial.println("");
    Serial.println("WiFi Reset !");
    Serial.println("");
    wifiManager.resetSettings();
    delay(3000);
    ESP.reset();
  }
  server.send(200, "text/html", cpResponse200);
}
void flow (){pulseCount++;}//割り込みに使うためのインクリメント関数

void loop() {
  MDNS.update();
  server.handleClient();

  //流量センサのループ
  attachInterrupt(digitalPinToInterrupt(PinSensorePIR), flow, RISING);//割り込み設定
  if(millis() >= (oldTime + 1000)){
  oldTime=millis();
  ryuuryou=((pulseCount / keisuu )/60);
  sam_ryuuryou=sam_ryuuryou+ryuuryou;
  pulseCount = 0;
  Serial.println(sam_ryuuryou);
  }
}
