#ifndef SERIAL_IO_H
#define SERIAL_IO_H

#include <Arduino.h>
#include <string>

// initialize serial communication
void serialIO_init(unsigned long baudrate);

// check if string is available
bool serialIO_available();

// get received string
std:: string serialIO_read();

// print string to serial
void serialIO_print(const std::string& msg);

#endif