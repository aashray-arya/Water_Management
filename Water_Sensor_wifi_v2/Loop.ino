void loop()
{
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Your Domain name with URL path or IP address with path
    http.begin(client, server);
    a = analogRead(W_SENSOR);
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {

      pulse1Sec = pulseCount;
      pulseCount = 0;

      flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
      previousMillis = millis();

      flowMilliLitres = (flowRate / 60) * 1000;
      totalMilliLitres += flowMilliLitres;


      Serial.print("\n");// Print tab space
    }
    String httpRequestData = "api_key=" + apiKeyValue + "&ESP_ID=" + String(ESPId) + "&Water_flown=" + String((float)totalMilliLitres) + "&SV_state=" + String((float)b) + "&Water_level=" + String(float(a)) + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    int httpResponseCode = http.POST(httpRequestData);

    // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");

    // If you need an HTTP request with a content type: application/json, use the following:
    //http.addHeader("Content-Type", "application/json");
    //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");


    //    client.println("Content-Type: application/x-www-form-urlencoded");
    //    client.print("Content-Length: ");
    //    client.println(httpRequestData.length());
    //    client.println();
    //    client.println(httpRequestData);
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  if (a >= 600)
  { digitalWrite(SV, LOW);
    b = 0;
  }
  else if (a < 400) {
    digitalWrite(SV, HIGH);
    b = 1;
  }
}
