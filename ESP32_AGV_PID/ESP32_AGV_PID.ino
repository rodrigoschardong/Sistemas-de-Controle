// AGV PID
// Rodrigo Schardong
// Uergs
//================================================
//Libraries
  #include <Ultrasonic.h>
  #include <WiFi.h>
  #include <WebServer.h>

//================================================
//Acess Point Info
  const char* accessPointId = "SSID";  // Enter SSID here
  const char* accessPointPassword = "password";  //Enter Password here
  WebServer server(80);
  String index_html;
  String index_script_style;
  int serverRefresh = 200;
  int pageNumber = 0;


//================================================
//Ultrasonic
  #define PIN_TRIGGER   26
  #define PIN_ECHO      25
  Ultrasonic ultrasonic(PIN_TRIGGER, PIN_ECHO);
  float distance;
  float lastDistance;
  float setDistance = 20;

  
//================================================
//Motor

  //Servo PWM property
  const char motorRightPin = 32; // Pino do PWM
  const char motorLeftPin = 33; // Pino do PWM
  
  const char motorRightChannel = 0; 
  const char motorLeftChannel = 1;
  
  const char motorFreq = 25; //25Hz, T = 40ms

  const char motorResolution = 8;// o tempo de High do pwm vai de 0 a (2**8) -1

  unsigned char motorRightDutyCycle = 0; 
  unsigned char motorLeftDutyCycle = 0;

  char motorSpeedBase = 0;
  char motorRightSpeedBase = 0;
  char motorLeftSpeedBase = 0;
  
  const unsigned char motorMinDutyCicle = 127;
  const unsigned char motorMaxDutyCicle = 255;

  float motorRightPower = 2.55;
  float motorLeftPower = 2.22;

//================================================
//Controler
  float kp;
  float ki;
  float kd;
  float P;
  float I = 0;
  float D;
  float PID;
  uint32_t lastTime;

  bool pOn = true;
  bool iOn = true;
  bool dOn = false;
  


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Baud Rate da serial

  //Motor
    ledcSetup(motorRightChannel, motorFreq, motorResolution);
    ledcSetup(motorLeftChannel, motorFreq, motorResolution);
    ledcAttachPin(motorRightPin, motorRightChannel);
    ledcAttachPin(motorLeftPin, motorLeftChannel);

  //Ultrasonico
    pinMode(PIN_ECHO, INPUT); //DEFINE O PINO COMO ENTRADA (RECEBE)
    pinMode(PIN_TRIGGER, OUTPUT); //DEFINE O PINO COMO SAIDA (ENVIA)
  
  Serial.println("Starting... ");
  
  ControlSetup();
  lastDistance = GetDistance();
  lastTime = millis();
  CreateAccessPoint();
}

void loop() {
  // put your main code here, to run repeatedly:
  distance = distance + FilteredDistance();
  distance = distance / 2;
  if(motorSpeedBase != 0)
    PIDControl();
  else{
    motorRightDutyCycle = 0;
    motorLeftDutyCycle = 0;
    ledcWrite(motorRightChannel, motorRightDutyCycle);
    ledcWrite(motorLeftChannel, motorLeftDutyCycle);
    motorRightSpeedBase = 0;
    motorLeftSpeedBase = 0;
  }
  server.handleClient();
  if (WiFi.status() == WL_CONNECTED){
    Serial.println("Client Connected");
  }  
}
