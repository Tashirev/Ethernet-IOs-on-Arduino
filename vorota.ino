#include <SPI.h>        
#include <Ethernet.h>
#include <EthernetUdp.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 };
IPAddress ip(192, 168, 0, 230);
unsigned int localPort = 8888;      // local port to listen on

char remote_IP[]="192.168.0.231";
int remote_Port = 8888;

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

byte relay_IN[1];  // элемент управления реле полученное из сети, 
byte relay_OUT[1]; // элемент состояние реле для передачи в сеть.

int relay_IN_pin = 7; // номер выхода для управления реле
int relay_OUT_pin = 8;  // номер входа состояния реле, для передачи в сеть

void setup() {

  pinMode (relay_IN_pin, OUTPUT);
  pinMode (relay_OUT_pin, INPUT);
  
  // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);

}

void loop() {

Udp.read(relay_IN,1);  // получение состояния кнопки из сети
 
  if (relay_IN[0] == 1)  
    digitalWrite(relay_IN_pin,HIGH);
  else
    digitalWrite(relay_IN_pin,LOW);
    
delay (50);

 relay_OUT[0]= digitalRead(relay_OUT_pin);  // получение состояния реле
    
Udp.beginPacket(remote_IP,remote_Port);
Udp.write(relay_OUT,1);  // отправление состояния реле в сеть
Udp.endPacket();

}
