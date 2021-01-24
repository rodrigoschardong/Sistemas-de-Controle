float GetDistance()
{
    //faz a leitura das informacoes do sensor (em cm)
    float distanceCm;
    long microsec = ultrasonic.timing();
    // pode ser um float ex: 20,42 cm se declarar a var float 
    distanceCm = ultrasonic.convert(microsec, Ultrasonic::CM);
    // distancia = ultrassom.Ranging(CM);
    //Serial.print("Distance: ");
    //Serial.println(distanceCm);
    return distanceCm;
}

float FilteredDistance(){
  #define forCycles 10
  float distanceCm = 0;
  char i;
  for(i = 0; i < forCycles; i++)
    distanceCm = distanceCm + GetDistance();
  distanceCm = distanceCm / forCycles;
  return distanceCm;   
}

void handle_increaseCm(){
  setDistance = setDistance + 0.01;
  server.send(serverRefresh, "text/html", index_html);

void handle_increaseCmPlus(){
  server.send(serverRefresh, "text/html", index_html);
}

void handle_decreaseCm(){
  setDistance = setDistance - 0.01;
  SetWebPage();
  server.send(serverRefresh, "text/html", index_html);
}

void handle_decreaseCmPlus(){
  setDistance--;
  server.send(serverRefresh, "text/html", index_html);
}
