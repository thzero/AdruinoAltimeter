#include <Arduino.h>
#if defined(ESP32)
#include <mutex>
#endif
#if defined(TEENSYDUINO)
#include <TeensyThreads.h>
#endif

#include "communicationRadioLoRa.h"

#if defined(ESP32)
SemaphoreHandle_t communicationRadioMutexOutput;
// std::mutex serial_mtx;
#endif
#if defined(TEENSYDUINO)
Threads::Mutex communicationRadioMutexOutput;
#endif

byte CommunicationRadioLoRa::setup(HardwareSerial* port, uint8_t pin_m0, uint8_t pin_m1, uint8_t pin_aux, int baud) {
    if (port == nullptr)
        return 1;

    _port = port;
    _baud = baud;

    Serial.println(F("\tSetup radio Serial..."));
    _port->setTimeout(10);
    _port->begin(9600);
    Serial.println(F("\t...radio Serial finished."));
    
    return 0;
}

void CommunicationRadioLoRa::initCommand(uint16_t command, CommunicationCommandFunctionPtr func) {
  CommunicationCommandFunctionEntry *item = (CommunicationCommandFunctionEntry *)malloc(sizeof(CommunicationCommandFunctionEntry));
  item->command = command;
  item->func = func;
  item->next = NULL;

  // if (commandsHead == NULL)
  //   commandsHead = item;
  // if (commandsLatest != NULL)
  //   commandsLatest->next = item;
  // commandsLatest = item;

  _commands.insert(std::make_pair(command, item));
}

int CommunicationRadioLoRa::process(unsigned long timestamp, unsigned long delta) {
#if defined(TEENSYDUINO)
  // Threads::Scope m(communicationRadioMutexOutput); // lock on creation
  communicationRadioMutexOutput.lock();
#endif
#if defined(ESP32)
  if (xSemaphoreTake(communicationRadioMutexOutput, portMAX_DELAY)) {
#endif

  if (_queueing.isEmpty()) {
    // Serial.println(F("communication-radio-lora-process: nothing to send."));
#if defined(TEENSYDUINO)
    communicationRadioMutexOutput.unlock();
#endif

#if defined(ESP32)
    xSemaphoreGive(communicationRadioMutexOutput); // Release the mutex
#endif
    return 2; // nothing to send.
  }

// TODO: stuff as many queued messages as will fit in the BUFFER_MAX_SIZE buffer using the START_BYTE as demarkation

  CommuicationQueueMessageStruct message = _queueing.front();
  _queueing.dequeue();

#ifdef DEBUG_COMMUNICATION_PROCESS
  Serial.printf(F("communication-radio-lora-process: message command to send: %d\n"), message.command);
  Serial.printf(F("communication-radio-lora-process: message bytes size to send: %d\n"), message.size);

  Serial.println(F("communication-radio-lora-process: message bytes to send: "));
  for (size_t i = 0; i < message.size; i++)
      Serial.printf(F("%d "), message.buffer[i]);
  Serial.println();
#endif

  // _port.write(message.buffer, message.size);

// TODO
  // uint16_t sendSize = _transfer.txObj(message.buffer, 0, message.size); // Stuff buffer with array
  // _transfer.sendData(sendSize, message.command);

  memset(message.buffer, 0, BUFFER_MAX_SIZE);

#ifdef DEBUG_COMMUNICATION_PROCESS
  Serial.println(F("communication-radio-lora-process: sent buffer."));
#endif

#if defined(ESP32)
    xSemaphoreGive(communicationRadioMutexOutput); // Release the mutex
  }
#endif
#if defined(TEENSYDUINO)
  communicationRadioMutexOutput.unlock();
#endif

  return 1;
}

int CommunicationRadioLoRa::queue(uint16_t command) {
#ifdef DEBUG_COMMUNICATION_QUEUE
  Serial.printf(F("communication-radio-lora-queue: message command: "));
  Serial.printf(F("%d\n"), command);
#endif

#if defined(TEENSYDUINO)
  // Threads::Scope m(communicationRadioMutexOutput); // lock on creation
  communicationRadioMutexOutput.lock();
#endif
#if defined(ESP32)
  if (xSemaphoreTake(communicationRadioMutexOutput, portMAX_DELAY)) {
#endif

  if (_queueing.size() >= COMMUNICATION_QUEUE_LENGTH) {
    Serial.println(F("communication-radio-lora-queue: all queues are full."));
    
#if defined(ESP32)
    xSemaphoreGive(communicationRadioMutexOutput); // Release the mutex
#endif
#if defined(TEENSYDUINO)
    communicationRadioMutexOutput.unlock();
#endif

    return -2; // exceeded queue length
  }

  CommuicationQueueMessageStruct message;
  uint8_t byteArray[1];
  byteArray[1] = 0;
  memcpy(message.buffer, byteArray, 1);
  message.size = 1;
  message.command = command;

#ifdef DEBUG_COMMUNICATION_QUEUE
  Serial.printf(F("communication-radio-lora-queue: message command to send: %d\n"), message.command);
  Serial.printf(F("communication-radio-lora-queue: message size to send: %d\n"), message.size);
  Serial.println(F("communication-radio-lora-queue: message bytes: "));
  for (size_t i = 0; i < message.size; i++)
      Serial.printf(F("%d "), message.buffer[i]);
  Serial.println();
#endif

  _queueing.enqueue(message);

#ifdef DEBUG_COMMUNICATION_QUEUE
  Serial.println(F("communication-radio-lora-queue: message queued."));
#endif

#if defined(ESP32)
    xSemaphoreGive(communicationRadioMutexOutput); // Release the mutex
  }
#endif
#if defined(TEENSYDUINO)
  communicationRadioMutexOutput.unlock();
#endif

  return 1;
}

int CommunicationRadioLoRa::queue(uint16_t command, uint8_t *byteArray, size_t size) {
  if (size > BUFFER_MAX_MESSAGE_SIZE) {
    Serial.printf(F("communication-radio-lora-queue: message is too long, max size is %d."), BUFFER_MAX_SIZE);
    return -1; // exceeded queue length
  }

#ifdef DEBUG_COMMUNICATION_QUEUE
  Serial.printf(F("communication-radio-lora-queue: message command: %d\n"), command);
  Serial.println(F("communication-radio-lora-queue: requested bytes: "));
  for (size_t i = 0; i < size; i++)
      Serial.printf(F("%d "), byteArray[i]);
  Serial.println();
#endif

  CommuicationQueueMessageStruct message;
  memcpy(message.buffer, byteArray, size);
  message.size = size;
  message.command = command;

#ifdef DEBUG_COMMUNICATION_QUEUE
  Serial.printf(F("communication-radio-lora-queue: message command to send: %d\n"), message.command);
  Serial.printf(F("communication-radio-lora-queue: message size to send: %d\n"), message.size);
  Serial.println(F("communication-radio-lora-queue: message bytes: "));
  for (size_t i = 0; i < message.size; i++)
      Serial.printf(F("%d "), message.buffer[i]);
  Serial.println();
#endif

#if defined(TEENSYDUINO)
  // Threads::Scope m(communicationRadioMutexOutput); // lock on creation
  communicationRadioMutexOutput.lock();
#endif
#if defined(ESP32)
  if (xSemaphoreTake(communicationRadioMutexOutput, portMAX_DELAY)) {
#endif

  if (_queueing.size() >= COMMUNICATION_QUEUE_LENGTH) {
    Serial.println(F("communication-radio-lora-queue: all queues are full."));

#if defined(ESP32)
    xSemaphoreGive(communicationRadioMutexOutput); // Release the mutex
#endif
#if defined(TEENSYDUINO)
    communicationRadioMutexOutput.unlock();
#endif

    return -2; // exceeded queue length
  }

  _queueing.enqueue(message);

#ifdef DEBUG_COMMUNICATION_QUEUE
  Serial.println(F("communication-radio-lora-queue: message queued."));
#endif

#if defined(ESP32)
    xSemaphoreGive(communicationRadioMutexOutput); // Release the mutex
  }
#endif
#if defined(TEENSYDUINO)
  communicationRadioMutexOutput.unlock();
#endif

  return 1;
}

size_t CommunicationRadioLoRa::read(CommunicationHandlerFunctionPtr func, unsigned long timestamp, unsigned long delta) {
    return 0;
//   if (_transfer.available()) { // TODO
//     CommuicationQueueMessageStruct communication;
//     // uint8_t command;
//     // uint8_t buffer[BUFFER_MAX_SIZE];
//     // size_t size;
//     communication.command = _transfer.currentCommand();
// #ifdef DEBUG_COMMUNICATION_READ
//     Serial.printf(F("communication-radio-lora-read: message command received: %d %d %d\n"), communication.command, _transfer.currentCommand(), (communication.command == _transfer.currentCommand()));
// #endif
//     communication.size = _transfer.currentReceived();
// #ifdef DEBUG_COMMUNICATION_READ
//     Serial.printf(F("communication-radio-lora-read: message bytes to receive: %d\n"), communication.size);
// #endif
// //     uint16_t recSize = 0;  // bytes we've processed from the receive buffer
// //     recSize = _transfer.rxObj(communication.size, sizeof(size_t));
// #ifdef DEBUG_COMMUNICATION_READ
//     Serial.printf(F("communication-radio-lora-read: message bytes to receive: %d\n"), communication.size);
// #endif
//     // recSize = _transfer.rxObj(communication.buffer, recSize, communication.size);
//     uint16_t recSize = _transfer.rxObj(communication.buffer, 0, communication.size);
// #ifdef DEBUG_COMMUNICATION_READ
//     Serial.printf(F("communication-radio-lora-read: message bytes to received: %d\n"), recSize);
//     Serial.printf(F("communication-radio-lora-read: message bytes received: "));
//     for (size_t i = 0; i < communication.size; i++)
//         Serial.printf(F("%d "), communication.buffer[i]);
//     Serial.println();
// #endif

//     CommunicationHandlerFunctionPtr commandFunc = getCommandFunction(communication.command);

//     if (commandFunc != nullptr)
//       commandFunc(timestamp, delta, communication);
//     else if (func != nullptr)
//       func(timestamp, delta, communication);

//     // TODO: read as many sent messages as are in the buffer using the START_BYTE as demarkation

//     return communication.size;
//   }

// //   if (Serial2.available() > 0) { // Check if data is available
// //     //  Serial.println(F("Serial2.available..."));
// //     CommuicationQueueMessageStruct communication;

// //     communication.size = Serial2.readBytesUntil(';', communication.buffer, BUFFER_MAX_SIZE - 1);
    
// // #ifdef DEBUG_COMMUNICATION_READ
// //     Serial.printf(F("communication-radio-lora-read: message size received: %d\n"), communication.size);
// // #endif
// //     // recSize = _transfer.rxObj(communication.buffer, recSize, communication.size);

// // #ifdef DEBUG_COMMUNICATION_READ
// //     Serial.println(F("communication-radio-lora-read: message bytes to receive: "));
// //     for (int i = 0; i < communication.size; i++)
// //       Serial.printf(F(%d "), communication.buffer[i]);
// //     Serial.println();
// // #endif

//   //   if (func != nullptr)
//   //       func(timestamp, delta, communication);

//   //   return communication.size;
//   // }
//   return 0;
}

void CommunicationRadioLoRa::writeBytes(uint8_t* byteArray, size_t length) {
}

void CommunicationRadioLoRa::writeChars(char* chars) {
}