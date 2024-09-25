
#include <WiFi.h>
#include <WiFiClientSecure.h>

const char* host = "script.google.com";
const int httpsPort = 443;

String GAS_ID = "AKfycbzQyhI3eesB-f2declASmRIDDdhlVFr5qKT0n0-eB-KbomOeeR2tguQhLgwg55UeD2yWQ";

const char* ssid = "MANDevices Laboratory";
const char* password = "MANDevices";


WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  //delay(50);

  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //delay(50);
  }

  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  client.setInsecure();
}

void loop() {
  int nd = random(20,40);
  //int dm = random(70,95);
  Serial.println(nd);
 // Serial.println(dm);

  sendata(nd);
  delay(50);
}

void sendata(int c){
  Serial.print("connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/macros/s/" + GAS_ID + "/exec?error=" + String(c);
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");
 Serial.println("OK");
 //
 while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }
  
  String response = client.readString();
  Serial.println("Response: " + response);

  client.stop();  // Đảm bảo kết nối được ngắt sau khi gửi dữ liệu
  Serial.println("Connection closed");
}
