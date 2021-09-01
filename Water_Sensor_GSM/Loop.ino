void loop()
{
  float a = analogRead(W_SENSOR);
  SerialMon.print("Connecting to APN: ");
  SerialMon.print(apn);
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    SerialMon.println(" fail");
  }
  else {
    SerialMon.println(" OK");

    SerialMon.print("Connecting to ");
    SerialMon.print(server);
    if (!client.connect(server, port)) {
      SerialMon.println(" fail");
    }
    else {
      SerialMon.println(" OK");
      //SerialMon.setTimeout(2000);
      String hs = "Total: " + String((float)totalMilliLitres);
      String ts = "Sensor Val: " + String((float)b);
      currentMillis = millis();
      if (currentMillis - previousMillis > interval)
      {

        pulse1Sec = pulseCount;
        pulseCount = 0;

        flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
        previousMillis = millis();

        flowMilliLitres = (flowRate / 60) * 1000;
        flowLitres = (flowRate / 60);

        totalMilliLitres += flowMilliLitres;
        totalLitres += flowLitres;

        // Print the flow rate for this second in litres / minute
        SerialMon.print("Flow rate: ");
        SerialMon.print(float(flowRate));  // Print the integer part of the variable
        SerialMon.print("L/min");
        SerialMon.print("\t");
        SerialMon.print("total ");
        SerialMon.print(float(totalMilliLitres));  // Print the integer part of the variable
        SerialMon.print("mL");
        SerialMon.print("\n");// Print tab space
      }
      String httpRequestData = "api_key=" + apiKeyValue + "&ESP_ID=" + String(ESPId) + "&Water_flown=" + String((float)totalMilliLitres) + "&SV_state=" + String((float)b) + "&Water_level=" + String(float(a)) + "";
        client.print(String("POST ") + resource + " HTTP/1.1\r\n");
        client.print(String("Host: ") + server + "\r\n");
        client.println("Connection: close");
        client.println("Content-Type: application/x-www-form-urlencoded");
        client.print("Content-Length: ");
        client.println(httpRequestData.length());
        client.println();
        client.println(httpRequestData);

        unsigned long timeout = millis();
        while (client.connected() && millis() - timeout <= 10000L) {
          // Print available data (HTTP response from server)
          while (client.available()) {
            char c = client.read();
            SerialMon.print(c);
            timeout = millis();
        }
      }
      client.stop();
      SerialMon.println(F("Server disconnected"));
      modem.gprsDisconnect();
      SerialMon.println(F("GPRS disconnected"));
    }
  }
  if (a >= 1800)
        { digitalWrite(SV, HIGH);
          b = 1;
        }
  else if(a<550){
    digitalWrite(SV,LOW);
    b =0;
  }
}
