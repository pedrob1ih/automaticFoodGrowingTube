#include <SoftwareSerial.h>
SoftwareSerial BT1(3, 2); // RX | TX
String W =" ";
char w ;
char uCDLR ;
boolean comandoRecibido;
  
  void setup(){  
  Serial.begin(9600);
  BT1.begin(9600);
  pinMode(13, OUTPUT);
  comandoRecibido=true;
  uCDLR='a';
  login();
  }
    
  void login(){
    String ordenes[]={
      "AT",
      "AT+RST",
      "AT+CWMODE=3",
      "AT+CWQAP",
      "AT+CWJAP=\"Alfonso Javier\",\"Valencia1990\"",
      "AT+CIFSR" ,
      "AT+CIPMUX=1",
      "AT+CIPSERVER=1,80",
      "END"                 // Para reconocer el fin de los comandos AT
    };

    String respuesta[]={
      "OK",
      "ready",
      "no change",
      "OK",
      "OK",
      "192.168.1.40",
      "OK",
      "OK",
      "END"                 // Para reconocer el fin de los comandos AT
    };
    
  int index = 0;
    while(ordenes[index] != "END"){
      if(comandoRecibido){
        BT1.println(ordenes[index]);
        comandoRecibido=false;
        uCDLR=respuesta[index].charAt(respuesta[index].length()-1);
      }
        

      if (BT1.available()){
        w = BT1.read() ;
        Serial.print(w);
        W = W + w ;                    // Vamos montando un String con lo que entra
      }
  
      if ( w==uCDLR){// Sin han pulsado intro 
        if ( W.indexOf(respuesta[index]) > 0 ){    // Comprobamos si P13 esta incluido en el string
          String mensaje="comando ";
          mensaje.concat(index);
          Serial.println('\n'+mensaje);
          comandoRecibido=true;
         }
         W = "" ;  
         w = ' ' ;                    // Limpiamos las variables
         index++;
      }
    }
  }
  
void loop(){       
      if (BT1.available()){
        w = BT1.read() ;
        Serial.print(w);
        W = W + w ;                    // Vamos montando un String con lo que entra
      }
      if (Serial.available()){
        char s = Serial.read();
        BT1.print(s);
      }
      if ( w == '\n'){// Sin han pulsado intro 
        if ( W.indexOf("P13") > 0 ){    // Comprobamos si P13 esta incluido en el string
          digitalWrite( 13, !digitalRead(13)) ;
          Serial.println("Invirtiendo pin 13");
         }
         W = "" ;  w = ' ' ;                    // Limpiamos las variables
      }
  }
