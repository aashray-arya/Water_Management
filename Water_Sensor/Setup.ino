void setup()
{
  
  Serial.begin(115200);
  delay(10);
  connect_WiFi();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(W_SENSOR, INPUT_PULLUP);
  pinMode(SV, OUTPUT); 
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;
 
  attachInterrupt(digitalPinToInterrupt(W_SENSOR), pulseCounter, FALLING);
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

void connect_MQTT(){
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
//
//  // Connect to the WiFi
//  WiFi.begin(ssid, wifi_password);
//
//  // Wait until the connection has been confirmed before continuing
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//
//  // Debugging - Output the IP Address of the ESP8266
//  Serial.println("WiFi connected");
//  Serial.print("IP address: ");
//  Serial.println(WiFi.localIP());

  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  // If the connection is failing, make sure you are using the correct MQTT Username and Password (Setup Earlier in the Instructable)
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }
}
