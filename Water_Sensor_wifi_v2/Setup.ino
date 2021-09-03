void setup()
{
  
  Serial.begin(115200);
  delay(10);
  connect_WiFi();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(W_METER, INPUT_PULLUP);
  pinMode(SV, OUTPUT);
  digitalWrite(SV,HIGH); 
  pinMode(W_SENSOR, INPUT);
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;
  a = 0;
  b=1;
  attachInterrupt(digitalPinToInterrupt(W_METER), pulseCounter, FALLING);
}
void connect_WiFi(){
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
