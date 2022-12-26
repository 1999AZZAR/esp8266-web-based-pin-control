#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "your-ssid";
const char* password = "your-password";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());

  // Set pin modes
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);

  // Set routes
  server.on("/pin", []() {
    String message;
    if (server.arg("D0") == "ON") {
      digitalWrite(D0, HIGH);
      message += "Pin D0 is turned on. ";
    } else if (server.arg("D0") == "OFF") {
      digitalWrite(D0, LOW);
      message += "Pin D0 is turned off. ";
    }
    if (server.arg("D1") == "ON") {
      digitalWrite(D1, HIGH);
      message += "Pin D1 is turned on. ";
    } else if (server.arg("D1") == "OFF") {
      digitalWrite(D1, LOW);
      message += "Pin D1 is turned off. ";
    }
    // ...
    server.send(200, "text/html", "<h1>ESP8266 Pin Control</h1>"
                                   "<p>" + message + "</p>"
                                   "<form action=\"/pin\" method=\"post\">"
                                   "  <input type=\"submit\" name=\"D0\" value=\"ON\">"
                                   "  <input type=\"submit\" name=\"D0\" value=\"OFF\">"
                                   "  <br>"
                                   "  <input type=\"submit\" name=\"D1\" value=\"ON\">"
                                   "  <input type=\"submit\" name=\"D1\" value=\"OFF\">"
                                   "  <br>"
                                   // ...
                                   "</form>");
  });
}

void loop() {
  server.handleClient();
}
