// #include "text_protocol.h"


// uint8_t my_user_id;
// uint8_t my_node_id;
// uint8_t user_id_r;
// uint8_t node_id_r;

// uint8_t msg_id = 0x00;
// void set_my_add(uint8_t user_id, uint8_t node_id){
//     my_user_id = user_id;
//     my_node_id = node_id;
// }

// void set_r_add(uint8_t user_id, uint8_t node_id){
//     user_id_r = user_id;
//     node_id_r = node_id;
// }

// void send_message(){
//     lora_packet_struct rts_pkt = get_rts(my_user_id, my_node_id, user_id_r, node_id_r, msg_id);
//     Serial.print("pkt_type: ");
//     Serial.println(rts_pkt.PKT_TYPE);
// }

// void develop_msg_packet(const std::string &my_msg){
//     lora_packet_struct rts_pkt = get_rts(my_user_id, my_node_id, user_id_r, node_id_r, msg_id);
//     rts_pkt.PAY_LEN = my_msg.length();

//     //memcpy(rts_pkt.PAYLOAD, my_msg.c_stexpressionr(), rts_pkt.PAY_LEN);

//     Serial.print("Received: ");
//         for (int i = 0; i < rts_pkt.PAY_LEN; i++) {
//             Serial.print((char)rts_pkt.PAYLOAD[i]);
//         }
// }

// void perform_handshake(){
//     lora_packet_struct rts_pkt = get_rts(my_user_id, my_node_id, user_id_r, node_id_r, msg_id);
//     Serial.println("RTS packet is sending..");
//     send_packet(rts_pkt);
// }

// bool is_for_me(uint8_t u_id_r, uint8_t n_id_r){
//     if(u_id_r== my_user_id && n_id_r == my_node_id){
//         return true;
//     }
//     else{
//         return false;
//     }
// }

// void handle_packet(){
//     int packet_size = get_packet_size();
//     lora_packet_struct pkt = {0};

//     if(packet_size < 8){
//         Serial.println("Invalid packet too small");
//         return;
//     }

//     pkt = get_packet();

//     // validate payload length
//     if(pkt.PAY_LEN > 50){
//         Serial.println("Invalid PAY_LEN");
//         return;
//     }

//     // Check total size mismatch

//     if(packet_size != 8 + pkt.PAY_LEN){
//         Serial.println("Size mismatch");
//         return;
//     }

//     // now we can further process the packet
//     Serial.println("Received: ");
//     Serial.print("Packet type: ");
//     Serial.println(pkt.PKT_TYPE);
//     Serial.print("Flags: ");
//     Serial.println(pkt.FLAGS);
//     Serial.print("user_id_s: ");
//     Serial.println(pkt.USER_ID_S);
//     Serial.print("user_id_r: ");
//     Serial.println(pkt.USER_ID_R);

//     for (int i = 0; i < pkt.PAY_LEN; i++){
//         Serial.print((char)pkt.PAYLOAD[i]);
//     }
// }

// void perform_two_way_handshake(){
//     perform_handshake();   
// }

// void respone_rts(){
//     int packet_size = get_packet_size();
//     lora_packet_struct pkt;

//     if(packet_size < 8){
//         Serial.println("Invalid packet too small");
//         return;
//     }

//     pkt = get_packet();

//     // validate payload length
//     if(pkt.PAY_LEN > 50){
//         Serial.println("Invalid PAY_LEN");
//         return;
//     }

//     // Check total size mismatch

//     if(packet_size != 8 + pkt.PAY_LEN){
//         Serial.println("Size mismatch");
//         return;
//     }

//     // now we can further process the packet
//     Serial.println("Received: ");
//     Serial.print("Packet type: ");
//     Serial.println(pkt.PKT_TYPE);
//     Serial.print("Flags: ");
//     Serial.println(pkt.FLAGS);
//     Serial.print("user_id_s: ");
//     Serial.println(pkt.USER_ID_S);
//     Serial.print("user_id_r: ");
//     Serial.println(pkt.USER_ID_R);

//     if(is_for_me(pkt.USER_ID_R, pkt.NODE_ID_R)){
//         Serial.println("This packet is for me.");
//         lora_packet_struct cts_pkt = get_cts(my_user_id, my_node_id, user_id_r, node_id_r, msg_id);
//         send_packet(cts_pkt);
//     }
//     else{
//         Serial.println("This packet is not for me.");
//     }
// }
