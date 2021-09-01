void loop()
{
  
  //Serial.setTimeout(2000);
  String hs="Total: "+String((float)totalMilliLitres);
  String ts="Sensor Val: "+String((float)b);
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
    Serial.print("Flow rate: ");
    Serial.print(float(flowRate));  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\t");
    Serial.print("total ");
    Serial.print(float(totalMilliLitres));  // Print the integer part of the variable
    Serial.print("mL");
    if(totalMilliLitres>=1000)
    {digitalWrite(SV,HIGH);
    b=1;
    }
    Serial.print("\n");// Print tab space
}
if (currentMillis - pM > inte) {
  pM= millis();
  connect_MQTT();
 if (client.publish(Wsensor_topic, String(totalMilliLitres).c_str())) {
    Serial.println("Total sent!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("Total failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(Wsensor_topic, String(totalMilliLitres).c_str());
  }

  // PUBLISH to the MQTT Broker (topic = Humidity, defined at the beginning)
  if (client.publish(solenoid_topic, String(b).c_str())) {
    Serial.println("solenoid state sent!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("solenoid state failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(solenoid_topic, String(b).c_str());
  }
  client.disconnect();  // disconnect from the MQTT broker
}
}
