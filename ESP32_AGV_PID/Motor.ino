void CurvaHoraria(float PID){
  motorRightDutyCycle = motorSpeedBase * motorRightPower;
  motorLeftDutyCycle = motorSpeedBase * motorLeftPower;

  motorRightDutyCycle = motorRightDutyCycle + PID;

  motorRightSpeedBase = motorRightDutyCycle * 100 / 255;
  motorLeftSpeedBase = motorSpeedBase;

  ledcWrite(motorRightChannel, motorRightDutyCycle);
  ledcWrite(motorLeftChannel, motorLeftDutyCycle);
}

void CurvaAntiHoraria(float PID){
  motorRightDutyCycle = motorSpeedBase * motorRightPower;
  motorLeftDutyCycle = motorSpeedBase * motorLeftPower;
  
  motorLeftDutyCycle = motorLeftDutyCycle - PID;

  motorRightSpeedBase = motorSpeedBase;
  motorLeftSpeedBase = motorLeftDutyCycle * 100 / 255;

  ledcWrite(motorRightChannel, motorRightDutyCycle);
  ledcWrite(motorLeftChannel, motorLeftDutyCycle);
}

void handle_increaseSpeed(){
  if(motorSpeedBase < 100){
    motorSpeedBase = motorSpeedBase + 5;
  }
  server.send(serverRefresh, "text/html", index_html);
}

void handle_increaseSpeedPlus(){
  motorSpeedBase = 100;
  server.send(serverRefresh, "text/html", index_html);
}

void handle_decreaseSpeed(){
  if(motorSpeedBase > 0)
    motorSpeedBase = motorSpeedBase - 5;
  server.send(serverRefresh, "text/html", index_html);
}

void handle_decreaseSpeedPlus(){
  motorSpeedBase = 0;
  server.send(serverRefresh, "text/html", index_html);
}
