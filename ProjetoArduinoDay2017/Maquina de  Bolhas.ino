#include <Ethernet.h>
#include<SPI.h>
#include <Servo.h>   

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 1, 111 };
EthernetServer server(80);

// maquina de bollhas
Servo servo1;
Servo servo2;
int soprar= 11;
int btn=12;
int pos = 0;   
int estadoBtn=0;
//*******

String readString;
int Pin = 6;
void setup(){
  pinMode(Pin, OUTPUT);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(9600);
  
  //**** maquina
  servo1.attach(10);  // attaches the servo on pin 9 to the servo object 
  servo2.attach(9);
  pinMode(soprar, OUTPUT);
  pinMode(btn,INPUT);
  //****
} 

void loop(){
  estadoBtn=digitalRead(btn);
   
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
         if (readString.length() < 100) {
          readString += c;             
        }
 
        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();         
          client.println("<HTML>");
           client.println(" <meta charset=utf-8> <meta name=description content=\"\"> <meta name=viewport content=\"width=device-width, initial-scale=1\">");
          client.println("<BODY style=\"background: #2A2828; color:#16B5D6;text-align: center;\">");
          client.println("<H1>Faça bolhas aqui!</H1>");
          client.println("<hr />");
          client.println("<br />");          
          client.println("<a  href=\"/?ledon\"><button>Ligar Maquina</button>]</a>");
         // client.println("<a href=\"/?ledoff\">Desligar o led</a><br />");              
          client.println("</BODY>");
          client.println("</HTML>");         
          delay(1);
          client.stop();

          if(readString.indexOf("?ledon") > 0)
          {
            digitalWrite(Pin, HIGH);
            Serial.println("Acionando maquina de Bolhas");
            start();
            
          }
          else {
            if(readString.indexOf("?ledoff") > 0)
            {
              digitalWrite(Pin, LOW);
              Serial.println("opa!!");
            }
          }
          readString="";    
        }
      }
    }
  }
}

void start(){
  Servo servo1;
Servo servo2;
int soprar= 11;
int btn=12;
int pos = 0;   
int estadoBtn=0;
  Serial.println("passo 1");
  digitalWrite(soprar,HIGH); // desligado --> HIGH
 // servo1.write(0);//55 - 0 * - 66
 // servo2.write(66);// 66 - 0 * 
 
  
  // gira a base
  for(pos = 55; pos >0; pos --){                                  
    servo1.write(pos);              
    delay(18);                       
  }
  delay(1000);
  Serial.println("passo 2");
  // move o braço para baixo
  for(pos = 0; pos<=66; pos ++)     // goes from 180 degrees to 0 degrees 
  {                                
    servo2.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(18);                       // waits 15ms for the servo to reach the position 
  }
  delay(1500);
  Serial.println("passo 3");
  // sobe o braço
  for(pos = 66; pos >0; pos --){                                  
    servo2.write(pos);              
    delay(18);
    if(pos == 40){
      delay(1000);
    }    
  }
  delay(1000);

  for(pos = 0; pos<=66; pos ++)     // goes from 180 degrees to 0 degrees 
  {                                
    servo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
  Serial.println("ventilador ok");
  delay(3000);
  digitalWrite(soprar, LOW);
  delay(1000);
  digitalWrite(soprar, HIGH);
  delay(3000);
  Serial.println("*:*:*:*:*:  Fim :*:*:*:*:\n\n");
  //*/
  
}
