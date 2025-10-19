// #ifndef _COMMUNICATION_RADIO_QUEUE_H
// #define _COMMUNICATION_RADIO_QUEUE_H

// #include <stdint.h>
// #include <Arduino.h>
// #include <limits.h>

// // #define DEBUG

// #include <CircularQueue.hpp>
// #include <map>

// #include <communicationData.h>
// #include <communicationRadio.h>

// #define COMMUNICATION_QUEUE_LENGTH 5
// // #define DEBUG_COMMUNICATION
// // #define DEBUG_COMMUNICATION_COMMAND
// // #define DEBUG_COMMUNICATION_INTERNAL
// // #define DEBUG_COMMUNICATION_PROCESS
// // #define DEBUG_COMMUNICATION_QUEUE
// // #define DEBUG_COMMUNICATION_READ
// // #define DEBUG_COMMUNICATION_SEND

// class CommunicationQueue {
//   public:
//     CommunicationQueue() {
//     }

//     void initCommand(uint16_t command, CommunicationCommandFunctionPtr func);
//     virtual int process(unsigned long timestamp, unsigned long delta);
//     virtual byte setup(CommunicationRadio* radio);
//     int queue(uint16_t command);
//     int queue(uint16_t command, uint8_t *byteArray, size_t size);

//     template <typename T>
//     // int queuePacked(uint16_t command, const T& val, const uint16_t& size = sizeof(T));
//     int queuePacked(uint16_t command, const T& val, const uint16_t& size = sizeof(T)) {
//       // convert packaged struct into byte array
//       uint8_t byteArray[size];
//       // uint8_t* ptr = (uint8_t*)&val;
//       // for (uint16_t i = index; i < size; i++) {
//       //   byteArray[i] = *ptr;
//       //   ptr++;
//       // }
//       memcpy(byteArray, &val, size);

//       return queue(command, byteArray, size);
//     }

//     size_t read(CommunicationHandlerFunctionPtr func, unsigned long timestamp, unsigned long delta);

//   protected:
//     CommunicationCommandFunctionPtr getCommandFunction(uint16_t command);
//     virtual void write(uint8_t* byteArray, size_t length);

//     CommunicationRadio* _radio;

//     std::map<uint16_t, CommunicationCommandFunctionEntry*> _commands;
//     CircularQueue<CommuicationQueueMessageStruct, COMMUNICATION_QUEUE_LENGTH> _queueing;
// };

// #endif