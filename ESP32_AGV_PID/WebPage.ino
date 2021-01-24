//https://lastminuteengineers.com/esp32-dht11-dht22-web-server-tutorial/

void SetWebPage() {
  String script;
  String style;
  String body;

  index_html = R"rawliteral(<!DOCTYPE HTML><html><head><title>ESP AGV</title><meta name="viewport" content="width=device-width, initial-scale=1 , user-scalable=no"></head>)rawliteral";
    
  script = R"rawliteral(
      <script>
        setInterval(loadDoc,200);
        function loadDoc() {
          var xhttp = new XMLHttpRequest()
          xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
              document.getElementById("webpage").innerHTML =this.responseText
            }
          };
          xhttp.open("GET", "/", true);
          xhttp.send();
        }
      </script>)rawliteral";

  style = R"rawliteral(
    <style>
      html {font-family: Helvetica;
            display: inline-block; 
            margin: 0px auto; 
            text-align: center;}
      body {margin-top: 10px;} 
      h1 {  color: #333333;
            margin: 20px auto;} 
      h3 {  color: #666666;
            margin-bottom: 10px;}      
      p {   font-size: 24px;
            color: #666666;
            padding-top: 5px;
            padding-bottom: 5px;}
      .tittle { display: block;
                background-color: #3498db;
                border-radius: 50px;
                margin-bottom: 0px;
                padding-top: 1px;
                padding-bottom: 1px;}
      .display{ background-color: #67b2e4;
                border-radius: 10px;
                padding-top: 1px;
                padding-bottom: 15px;
                margin: 1px auto;
                margin-top: 5px;}
      .data{    background-color: #69bad4;
                border-radius: 20px;
                padding-top: 0px;
                padding-bottom: 6px; 
                padding-right: 10px;
                padding-left: 10px;
                width:200px;
                height:60px;
                margin: 0px auto;} 
      .control{ grid-gap: 10px;
                background-color: #67b2e4;
                border-radius: 10px;
                padding-top: 10px;
                padding-bottom: 10px;
                padding-left: 10px;
                margin: 0px auto;
                display: grid;
                grid-template-columns: 1fr 1fr;}
      .setting{ background-color: #69bad4;
                border-radius: 40px;
                padding-top: 0px;
                padding-bottom: 0px; 
                padding-right: 10px;
                padding-left: 10px;
                width:60px;
                height:260px;
                margin: 0px auto;}
      .list{    background-color: #69bad4;
                border-radius: 40px;
                padding-top: 20px;
                padding-bottom: 0px; 
                padding-right: 10px;
                padding-left: 10px;
                width:88px;
                height:240px;
                margin: 0px auto;}
      .button { display: block;
                width: 50px;
                background-color: #3498db;
                border: none;
                color: white;
                padding: 0px 0px;
                text-decoration: none;
                font-size:  20px;
                margin: 0px auto 5px;
                cursor: pointer;
                border-radius: 5px;}
      .button2 {display: block;
                width: 90px;
                background-color: #3498db;
                border: none;
                color: white;
                padding: 0px 0px;
                text-decoration: none;
                font-size:  20px;
                margin: 0px auto 5px;
                cursor: pointer;
                border-radius: 5px;
                padding-top: 2px;
                padding-bottom: 2px;}
      .bottom { display: block;
                background-color: #3498db;
                border-radius: 5px;
                margin-bottom: 10px;
                padding-top: 5px;
                padding-bottom: 10px;}
    </style>)rawliteral";
    
  body = "<body><div id = \"webpage\">";
  
  body += "</div></body></html>";

  index_html += script;
  index_html += style;
  index_html += body;
}

void CreateAccessPoint(){
  WiFi.mode(WIFI_MODE_AP); // Setting acess point mode
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(accessPointId, accessPointPassword);
  //Apparently the ip is always  192.168.4.1
  //Check it on serial
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", handle_OnConnect);
  server.on("/increase", handle_increase);
  server.on("/increasePlus", handle_increasePlus);
  server.on("/decrease", handle_decrease);
  server.on("/decreasePlus", handle_decreasePlus);

  server.on("/distance", handle_distance);
  server.on("/PID", handle_PID);
  server.on("/motor", handle_motor);
  server.on("/right", handle_right);
  server.on("/left", handle_left);
  server.on("/onoff", handle_onoff);

  server.on("/P", handle_P);
  server.on("/I", handle_I);
  server.on("/D", handle_D);
  
  server.begin();
  Serial.println("HTTP server started");
  SetWebPage();
}

void handle_increase(){
  if(pageNumber == 0){
    handle_increaseCm();
  }
  else{
    handle_increaseSpeed();
  }
}
void handle_increasePlus(){
  if(pageNumber == 0){
    handle_increaseCmPlus();
  }
  else{
    handle_increaseSpeedPlus();
  }
}
void handle_decrease(){
  if(pageNumber == 0){
    handle_decreaseCm();
  }
  else{
    handle_decreaseSpeed();
  }
}
void handle_decreasePlus(){
  if(pageNumber == 0){
    handle_decreaseCmPlus();
  }
  else{
    handle_decreaseSpeedPlus();
  }
}

void handle_OnConnect() {
  server.send(serverRefresh, "text/html", index_html);
}

void handle_distance(){
  pageNumber = 0;
  SetWebPage();
  server.send(serverRefresh, "text/html", index_html);
}
void handle_PID(){
  pageNumber = 2;
  SetWebPage();
  server.send(serverRefresh, "text/html", index_html);
}
void handle_motor(){
  pageNumber = 3;
  SetWebPage();
  server.send(serverRefresh, "text/html", index_html);
}
void handle_right(){
  server.send(serverRefresh, "text/html", index_html);
}
void handle_left(){
  server.send(serverRefresh, "text/html", index_html);
}
void handle_onoff(){
  server.send(serverRefresh, "text/html", index_html);
}
