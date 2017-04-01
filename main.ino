#include<SoftwareSerial.h>
SoftwareSerial esp(2, 3); //Rx, tx
long duration ;
String data;
String city_name = "Chennai"; // City Name
String rfid_value = "30"; //RFID Value the one you will get from the reader 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  esp.begin(9600);
  esp.println("AT");
  response(3000);
  esp.println("AT+CIOBAUD=9600");
  response(1000);
  esp.println("AT+CWMODE=1");
  response(2000);

  esp.println("AT+CWJAP=\"san\",\"asdfasdf\""); // Change the Wifi Settings
  response(10000);
  pinMode(9,OUTPUT);
  pinMode(10,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
       digitalWrite(9,LOW);
       delayMicroseconds(2);
       digitalWrite(9,HIGH);
       delayMicroseconds(10);
       digitalWrite(9,LOW);
       duration = pulseIn(10,HIGH);
  data ="rfid_value="+rfid_value+"&city_name="+city_name;
     
  
  
  esp.println("AT+CIPSTART=\"TCP\",\"192.168.43.32\",80");
  response(5000);
  esp.println("AT+CIPSEND=80");
  response(2000);
  esp.print("GET http://192.168.43.32/yathrack/update_from_maa.php?");

  esp.print(data);

    

}

void response(int waitTime)
{
  for (int i = 0 ; i < waitTime; i++)
  {
    if (esp.available() > 0)
    {
      char x = esp.read();
      Serial.print(x);

    }
    delay(1);
  }
}


