#include "setup_lora.h"
#include <LoRa.h>
// LoRa Modes
#define RX_MODE 0
#define TX_MODE 1
int mode = RX_MODE;
volatile bool receivedFlag = false;
static int _last_pkt_size = 0;

void IRAM_ATTR onReceiveISR() {
  receivedFlag = true;   // Keep ISR short!
}

void setup_lora_communication(){
  // setup LoRa
  LoRa.setPins(cs, reset, dio0);

  pinMode(dio0, INPUT);
  attachInterrupt(digitalPinToInterrupt(dio0), onReceiveISR, RISING);

  pinMode(led_when_receive, OUTPUT);
  pinMode(led_on_t_mode, OUTPUT);

  if (!LoRa.begin(frequency)){
    Serial.println("LoRa init failed");
    while (1);
    }
  setMode(RX_MODE);          // by default
  Serial.println("LoRa ready to operate");
};

void setMode(int status){
    if(status== RX_MODE){
      LoRa.receive();                       // set to receive mode
      digitalWrite(led_on_t_mode, LOW);
    //   digitalWrite(led_on_r_mode, HIGH);    // indicate my led
    }
    else{
    //   digitalWrite(led_on_r_mode, LOW);      // set to transmit mode indicate my led
      digitalWrite(led_on_t_mode, HIGH);      
    }
};

void send_msg(std::string &msg){
    mode = TX_MODE;
    setMode(TX_MODE);
    std::string my_msg = msg;
    delay(50);

    LoRa.beginPacket();
    LoRa.print(my_msg.c_str());
    LoRa.endPacket();

    Serial.print("Sent: ");
    Serial.print(my_msg.c_str());

    mode = RX_MODE;     // go back to receiving mode
    setMode(mode);
}

std::string get_msg(){
  receivedFlag = false;
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
      std::string msg = "";
      while (LoRa.available()) {
        msg += (char)LoRa.read();
        }
      return msg;
        }
  return "";
}

void send_packet(const lora_packet_struct &pkt){
  // lora packet is send from here.
  // disable interrupt
  detachInterrupt(digitalPinToInterrupt(dio0));
  mode = TX_MODE;
  setMode(mode);
  delay(50);

  Serial.println("Before Sending.");
  Serial.print("Size of lora packet: ");
  Serial.println(8 + pkt.PAY_LEN);

  LoRa.beginPacket();
  LoRa.write((uint8_t*)&pkt, 8 + pkt.PAY_LEN);

  int result = LoRa.endPacket(false);  // false blocking TX

  Serial.print("EndPacket result: ");
  Serial.println(result);  // 1 = success, 0 = failed

  // enable interrupt
  attachInterrupt(digitalPinToInterrupt(dio0), onReceiveISR, RISING);
  
  mode = RX_MODE;
  setMode(RX_MODE);
  Serial.println("Packet Sent.");
}

int get_packet_size(){

  noInterrupts();
  receivedFlag = false;
  interrupts();
  _last_pkt_size = LoRa.parsePacket();
  if(_last_pkt_size == 0){
    mode = RX_MODE;     // go back to receiving mode
    setMode(mode);
    return 0;
  }
  return _last_pkt_size;
}

lora_packet_struct get_packet(){

  lora_packet_struct pkt;
  memset(&pkt, 0, sizeof(pkt));

  int i = 0;
  while (LoRa.available() && i < (int)sizeof(lora_packet_struct))
  {
    ((uint8_t*)&pkt)[i++] = LoRa.read();
  }

  mode = RX_MODE;     // go back to receiving mode
  setMode(mode);

  return pkt;
}

bool is_packet_available(){
  return receivedFlag;
}