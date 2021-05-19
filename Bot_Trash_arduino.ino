
/* 
 *NOMBRE DEL CODIGO: Control robot limpiador PIF
 *Diseñadoras: Isabela Ceballos Franco 1001539096
 *             Daniela Jurado Blandón 1001469387
 *Fecha de inicio: 21/05/2021
 *Fecha de finalizacion: 
 *Descripcion: Control remoto mediante una app diseñada en Appinventor para manejar un prototipo robotico que recoja basura
 */

/*#include <Servo.h>                // Incluye la libreria Servo
Servo servo1;                    // Crea el objeto servo1 con las caracteristicas de Servo

int izqA = 5; 
int izqB = 6; 
int derA = 9; 
int derB = 10; 
int vel = 255;            // Velocidad de los motores (0-255)*/
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

String message = "";
char inComigChar;
int contador = 0;
String coordenada;
unsigned long tiempoPres = 0;
//int estado = SerialBT.read();         // inicia detenido

void setup()  { 
  Serial.begin(115200);
  //Serial2.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  /*pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);
*/
  unsigned long tiempoTrans = millis();
  
} 

void loop(){
   
 if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  /*
  if (SerialBT.available()) {//solo escribe en el monitor, lee lo del android y lo muestra en el monitor
   int input = SerialBT.read(); //leyendo lo que android envio para arduino
   Serial.write(input);         //escibe en el monitor lo recibido de android
   SerialBT.write(input);       //envia lo que recibi al Android.
  }*/
  
  if (SerialBT.available()) {
    tiempoPres = millis()- tiempoPres;
    char inComingChar = SerialBT.read();
    if(inComingChar != '\n'){
      message += String(inComingChar);
    }
    if(contador > 0){
        coordenada += String(tiempoPres/1000);
        tiempoPres = millis();
    }
    if(message=="a"){           
        //analogWrite(derB, 0);     
        //analogWrite(izqB, 0); 
        //analogWrite(derA, vel);  
        //analogWrite(izqA, vel);       
        Serial.println("Adelante");
    }
    if(message=="b"){       
      //analogWrite(derB, 0);     
      //analogWrite(izqB, 0); 
      //analogWrite(derA, 0);  
      //analogWrite(izqA, vel);   
      Serial.println("Izquierda"); 
    }
    if(message=="c"){         
      //analogWrite(derB, 0);     
      //analogWrite(izqB, 0); 
      //analogWrite(derA, 0);    
      //analogWrite(izqA, 0); 
      Serial.println("Derecha");
    }
    if(message=="d"){         
      //analogWrite(derB, 0);     
      //analogWrite(izqB, 0);
      //analogWrite(izqA, 0);
      //analogWrite(derA, vel);  
      Serial.println("Atras");
    }
    if(message=="e"){          
      //analogWrite(derB, 0);     
      //analogWrite(izqB, 0);
      //analogWrite(izqA, 0);
      //analogWrite(derA, vel);  
      //Serial.println("Stop");
    }
    if(message=="f"){         
      //analogWrite(derB, 0);     
      //analogWrite(izqB, 0);
      //analogWrite(izqA, 0);a1b5d8
      //analogWrite(derA, vel);  
      Serial.println("Off");
      Serial.println(coordenada);
      
      uint8_t myBuffer[coordenada.length()];
      // Copy at most 32 bytes, but no more than there actually is, into the buffer
      memcpy(myBuffer, coordenada.c_str(),coordenada.length()); 
      //uint8_t* data[50];
      SerialBT.write(myBuffer,sizeof(myBuffer));
      coordenada = "";
    }
    
    coordenada += message;
    contador++;
    message="";
  }
      delay(20);

}
