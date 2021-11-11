void cheakWiFiConnection() {
  if ((WiFi.status() != WL_CONNECTED) && (conn_stat == 2) ) {
    conn_stat = 0;
  }
  switch (conn_stat) {
    case 0:    //   WiFi down: start WiFi
      Serial.println("WiFi down: start WiFi");
      WiFi.begin(esid.c_str(), epass.c_str());
      WiFi.begin(esid.c_str());
      WiFi.setSleep(false);
      Serial.println("Waiting... ");
      conn_stat = 1;
      waitCount = 0;
      digitalWrite(led, 0);
      break;
    case 1:    // Waiting Connection
      waitCount++;
      if (WiFi.status() == WL_CONNECTED)
      {
        WiFi.config(stIP, gateway, subnet);
        server.begin();
        Serial.println("Connected... " + String(waitCount));
        conn_stat = 2;
      }
      if (waitCount > 1000000)
      {
        conn_stat = 0;
        Serial.print("Denied for a while... Re-request connection ");
        conn_stat = 0;
      }
      digitalWrite(led, 1);
      break;
    case 2:   // Client Mode Connected
      server.handleClient();
      digitalWrite(led, 0);
      break;
  }
}

//////////////////////////////////////////////////////////
void varify()
{

  int j;
  for (j = 0; j <= 3; j++)
  {
    if (INCODE[j] != pass[j] || i != 4)
      j = 5;

    if (j == 3)  // if the password length in the line = the code length
    {
      Serial.println("Welcome");
      digitalWrite(relay, 1);
      digitalWrite(buzzer, 1);
      delay (700);
      digitalWrite(buzzer, 0);
      digitalWrite(relay, 0);
    };
  }
  if (j > 4) // if EOF is reached without reaching a valid password
  {
    Serial.println("Invalied Pass!");
    for (j = 0; j < 11; j++) {
      digitalWrite(buzzer, 1);
      delay(25);
      digitalWrite(buzzer, 0);
      delay(25);
    }
  }
}

/////////////////////////////////////////////////////
