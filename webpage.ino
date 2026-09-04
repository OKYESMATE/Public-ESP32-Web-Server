#include <WiFi.h>
#include <WebServer.h>
#include <SuperDMZ.h>

// WiFi settings, replace tese with ur actual WiFi name and password
const char* WIFI_SSID     = "my_network";
const char* WIFI_PASSWORD = "my_pass";

// Tunnel settings — get this from the panel at https://superdmz.com/login/
// after creating an HTTP tunnel. It's a 48-hex-character token.
const char* SUPERDMZ_TOKEN = "abc123";
const uint16_t LOCAL_PORT  = 80; // must match the WebServer port below,
                                  // and the local_port set on the tunnel in the panel

WebServer server(80);
SuperDMZ  tunnel;

void onTunnelStatus(bool online, const char* publicUrl) {
  if (online) {
    Serial.print("Tunnel is UP. Public URL: ");
    Serial.println(publicUrl);
  } else {
    Serial.println("Tunnel is DOWN, attempting reconnect...");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempts = 0;
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts += 1;
  }

  Serial.println();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wi-Fi connected");
    Serial.print("Local IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("Channel: ");
    Serial.println(WiFi.channel());
    Serial.print("RSSI: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
  } else {
    Serial.print("WiFi connection failed, status code: ");
    Serial.println(WiFi.status());
    return; // don't bother starting server/tunnel if we're not connected
  }

  // Local routes
  server.on("/", []() {
    server.send(
      200,
      "text/html",
      "<!DOCTYPE html>"
      "<html>"
      "<head>"
      "<title>Hello World Webpage</title>"
      "</head>"
      "<body>"
        "<h1>If you can see this from whatever step we are on to making the ESP32 website hosting world wide, you have succeeded!</h1>"
        "<h5>Replace this code with whatever you want</h5>"
      "</body>"
      "</html>"
    );
  });

  server.begin();
  Serial.println("Local web server started.");

  // Start the tunnel — must be called after WiFi is connected
  tunnel.onStatus(onTunnelStatus);
  bool started = tunnel.begin(SUPERDMZ_TOKEN, LOCAL_PORT);
  if (!started) {
    Serial.println("Failed to start SuperDMZ tunnel — check token.");
  }
}

void loop() {
  server.handleClient();
  tunnel.loop(); // required every loop — omitting this causes endless reconnect
}
