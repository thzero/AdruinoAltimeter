#ifndef _RADIO_H
#define _RADIO_H

extern byte setupRadioStart();
extern void radioProcess(unsigned long timestamp, unsigned long delta);
extern void radioWriteChar(char* byteArray, size_t length);
extern void radioWriteBytes(uint8_t* byteArray, size_t length);

#endif