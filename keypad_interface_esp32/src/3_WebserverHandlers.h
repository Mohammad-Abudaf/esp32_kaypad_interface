void webserverHandlers()
{
  server.on("/smsm", HTTP_GET, []() {
        server.sendHeader("Connection", "close");
        server.send(200, "text/plain", "Welcome");
        digitalWrite(relay, 1);
        digitalWrite(buzzer, 1);
        delay (700);
        digitalWrite(buzzer, 0);
        digitalWrite(relay, 0);});
        
  server.on("/updatePass", HTTP_GET, []() {
        server.sendHeader("Connection", "close");
        server.send(200, "text/html", updatePage);});
 
  server.on("/update", HTTP_POST, []() {
        server.sendHeader("Connection", "close");
        server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
        ESP.restart();}, 
        []() {
                HTTPUpload& upload = server.upload();
                if (upload.status == UPLOAD_FILE_START) 
                {
                  Serial.printf("Update: %s\n", upload.filename.c_str());
                  if (!Update.begin(UPDATE_SIZE_UNKNOWN)) Update.printError(Serial);
                } 
                else if (upload.status == UPLOAD_FILE_WRITE) 
                {
                  if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) Update.printError(Serial);
                } 
                else if (upload.status == UPLOAD_FILE_END) 
                {
                  if (Update.end(true)) Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
                  else Update.printError(Serial);
                }
        });
}
