// #include "CommunicationRadioLoRaRYLR89X.h"

// byte CommunicationRadioLoRaRYLR89X::setup(HardwareSerial* port, int address, int networkId, int baud) {
//     byte results = CommunicationRadioLoRa::setup(port, address, networkId, baud);
//     if (results > 0)
//         return results;

//     Serial.println(F("\tSetup communication radio LORA transceiver..."));

//     if (_port == nullptr)
//         return 1;

//     // _port->write("AT+IPR=");

//     Serial.println(F("\t...setup communication radio LORA transceiver finished."));

//     return 0;
// }

// int CommunicationRadioLoRaRYLR89X::available() {
//     if (_port == nullptr) {
//         Serial.println("Error: no port setup for the LoRa radio.");
//         return false;
//     }
//     return _port->available();
// }

// int CommunicationRadioLoRaRYLR89X::read() {
//     if (_port == nullptr) {
//         Serial.println("Error: no port setup for the LoRa radio.");
//         return 0;
//     }
//     return _port->read();
// }

// void CommunicationRadioLoRaRYLR89X::writeBytes(uint8_t* byteArray, size_t length) {
//     if (_port == nullptr) {
//         Serial.println("Error: no port setup for the LoRa radio.");
//         return;
//     }
//     _port->write(byteArray, length);
// }

// void CommunicationRadioLoRaRYLR89X::writeChars(const char* chars) {
//     if (_port == nullptr) {
//         Serial.println("Error: no port setup for the LoRa radio.");
//         return;
//     }
//     _port->write(chars);
// }