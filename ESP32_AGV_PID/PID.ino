void ControlSetup(){
  float L = 0.145; //trocar os valores T1 e T2
  float T = 0.255;
  kp = 1.2 * T / L;
  ki = 2 * L;
  kd = L /2;
}


void PIDControl(){
  float error;
  uint32_t deltaTime = millis() - lastTime;
  
  lastTime = deltaTime + lastTime;
  error = setDistance - distance;
  deltaTime = deltaTime / 1000;
  if(pOn)
    P = error * kp;
  else
    P = 0;
  if(iOn)
    I = (I + (error * ki)) * deltaTime ; // * variacaodotempo
  else
    I = 0;
  if(dOn)
    D = (lastDistance - distance) * kd * deltaTime; //*variacaodotempo
  else
    D = 0;
  PID = P + I + D;
  //Serial.print("PID: ");
  //Serial.println(PID);
  if(PID < 0){
    CurvaHoraria(PID);
  }
  else{
    CurvaAntiHoraria(PID);
  }
}

void handle_P(){
  pOn = !pOn;
  server.send(serverRefresh, "text/html", index_html);
}
void handle_I(){
  iOn = !iOn;
  server.send(serverRefresh, "text/html", index_html);
}
void handle_D(){
  dOn = !dOn;
  server.send(serverRefresh, "text/html", index_html);
}
