
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid="esp_test";     //wifi ssid and password
const char *password="18092000";

ESP8266WebServer server(80);      //server port

void handleRoot(){

                      //Main page fontend
                            //convert html to cpp string == https://tomeko.net/online_tools/cpp_text_escape.php?lang=en
  
  server.send(200,"text/html"," <!DOCTYPE html>\n"
" <html lang=\"en\">  \n"
" <head>  \n"
"     <meta charset=\"UTF-8\">  \n"
"     <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">  \n"
"     <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">  \n"
"     <style>  \n"
"         body{  \n"
"             display: flex;  \n"
"             flex-direction: column;  \n"
"             justify-content: center;  \n"
"             justify-items: center;  \n"
"             background-color: rgb(201, 201, 201);  \n"
"         }  \n"
"         h1{  \n"
"             text-align: center;  \n"
"         }  \n"
"         div{  \n"
"             width: 50vw;  \n"
"             height: 20vw;  \n"
"             margin-left: 25vw;  \n"
"             margin-top: 10vh;  \n"
"             border-color:black ;  \n"
"             border-width: 1vw;  \n"
"             border-radius: 10vw;  \n"
"             border-style: solid;  \n"
"             text-align: center;  \n"
"         }  \n"
"         div a{  \n"
"             margin-top: 40%;  \n"
"             font-size: 7vw;  \n"
"             text-decoration: none;  \n"
"               \n"
"         }  \n"
"         #d0{  \n"
"             background-color: rgb(231, 197, 45);  \n"
"         }  \n"
"         #d1{  \n"
"             background-color: rgb(80, 238, 80);  \n"
"         }  \n"
"         #d2{  \n"
"             background-color: rgb(68, 205, 223);  \n"
"         }  \n"
"         #d3{  \n"
"             background-color: rgb(219, 64, 155);  \n"
"         }  \n"
"     </style>  \n"
"     <title>Home control</title>  \n"
" </head>  \n"
" <body>  \n"
"     <h1>Well come </h1>  \n"
"     <div id=\"d0\">  \n"
"         <a href='/l0'>Tube_1</a>  \n"
"     </div>  \n"
"     <div id=\"d1\">  \n"
"         <a href='/l1'>Tube_2</a>  \n"
"     </div>  \n"
"     <div id=\"d2\">  \n"
"         <a href='/l2'>Others</a>  \n"
"     </div>  \n"
"     <div id=\"d3\">  \n"
"         <a href='/fan'>Fan</a>  \n"
"     </div>  \n"
"         <h2>::About::</h2>  \n"
" </body>  \n"
" </html>  ");
}
              //function for other pages
void cont1(){
  Serial.println("Tube_1");
  handleRoot();
  }

void cont2(){
  Serial.println("Tube_2");
  handleRoot();
  }
void cont3(){
  Serial.println("Other");
  handleRoot();
  }
void cont4(){
  Serial.println("Fan");
  handleRoot();
  }
void setup(){
  delay(2000);
  Serial.begin(9600);
  WiFi.softAP(ssid,password);     //esp8266 use as a acces point
  IPAddress myIP = WiFi.softAPIP();   //store the ip address
  Serial.print("AP IP address: ");
  Serial.println(myIP);             
  server.on("/",handleRoot);  //this is for home page(call the handleRoot function)
  server.on("/l0",cont1);     //other page
  server.on("/l1",cont2);
  server.on("/l2",cont3);
  server.on("/fan",cont4);
  server.begin();
  
  Serial.println("HTTP server is now  start.");
  delay(2000);
  }
void loop(){
  server.handleClient();
  }
