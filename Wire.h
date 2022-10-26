
#ifndef WIRE_H
#define	WIRE_H

#include <xc.h> // include processor files - each processor file is guarded. 



//Middle level application
void Wire_begin(unsigned long c);
void Wire_beginTransmission(unsigned char address);
void Wire_write(unsigned char data);
void Wire_writeNBytes(const unsigned char* data, unsigned char data_len);
unsigned char Wire_endTransmission();
unsigned char Wire_readByte(unsigned char address);
void Wire_readNBytes(unsigned char address, unsigned char* rx_data, unsigned char data_len);

//Low level application
void Wire_wait();
unsigned char Wire_status(unsigned char status);
void Wire_NACK(void);
void Wire_ACK(void);
void Wire_stop();
void Wire_restart(void);
void Wire_start(void);

#endif

