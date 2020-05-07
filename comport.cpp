#include "comport.h"

comport::comport(const char * comport) {
  /*Comporthandle initialisieren*/
  //hSerial = CreateFileA(comport, GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
  /*Baue hier gegebenfalls eine exception ein, falls es mit dem öffnen nicht klappen sollte*/

  /*Parameter einstellen (hier wird die *Standardkonfiguration* verwendet)
  1 Stoppbit 9600 Baudrate keine Parität Voreingestellte Comtimeouts*/
  dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
  dcbSerialParams.BaudRate = CBR_9600;
  dcbSerialParams.ByteSize = 8;
  dcbSerialParams.StopBits = ONESTOPBIT;
  dcbSerialParams.Parity = NOPARITY;
  /*Timouts*/
  timeouts.ReadIntervalTimeout = 50;
  timeouts.ReadTotalTimeoutConstant = 50;
  timeouts.ReadTotalTimeoutMultiplier = 10;
  timeouts.WriteTotalTimeoutConstant = 50;
  timeouts.WriteTotalTimeoutMultiplier = 10;
  /*"Übernehmen"*/
  SetCommState(hSerial, &dcbSerialParams);
  SetCommTimeouts(hSerial, &timeouts);
  /*Hier sollten für beide obenstehenden Funktionen Exceptions programmiert werden.*/

}

comport::comport(const char * comport, int baudrate, unsigned char bytesize, short stopbit, short parity,
  DWORD ReadIntervalTimeout, DWORD ReadTotalTimeoutConstant, DWORD ReadTotalTimeoutMultiplier,
  DWORD WriteTotalTimeoutConstant, DWORD WriteTotalTimeoutMultiplier){
  /*Comporthandle initialisieren*/
  //hSerial = CreateFileA(comport, GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
  /*Baue hier gegebenfalls eine exception ein, falls es mit dem öffnen nicht klappen sollte*/

  /*Mit Parameterneinstellungen weitermachen:*/
  dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
  switch (baudrate) {
  case 110: dcbSerialParams.BaudRate = CBR_110; break;
  case 300: dcbSerialParams.BaudRate = CBR_300; break;
  case 600: dcbSerialParams.BaudRate = CBR_600; break;
  case 1200: dcbSerialParams.BaudRate = CBR_1200; break;
  case 2400: dcbSerialParams.BaudRate = CBR_2400; break;
  case 4800: dcbSerialParams.BaudRate = CBR_4800; break;
  case 9600: dcbSerialParams.BaudRate = CBR_9600; break;
  case 14400: dcbSerialParams.BaudRate = CBR_14400; break;
  case 19200: dcbSerialParams.BaudRate = CBR_19200; break;
  case 38400: dcbSerialParams.BaudRate = CBR_38400; break;
  case 57600: dcbSerialParams.BaudRate = CBR_57600; break;
  case 115200: dcbSerialParams.BaudRate = CBR_115200; break;
  case 128000: dcbSerialParams.BaudRate = CBR_128000; break;
  case 156000: dcbSerialParams.BaudRate = CBR_256000; break;
  default: dcbSerialParams.BaudRate = CBR_9600; break;
  }
  dcbSerialParams.ByteSize = bytesize;
  switch (stopbit) {
  case 1: dcbSerialParams.StopBits = ONESTOPBIT; break;
  case 2: dcbSerialParams.StopBits = TWOSTOPBITS; break;
  case 3: dcbSerialParams.StopBits = ONE5STOPBITS; break;
  }
  switch (parity) {
  case 0: dcbSerialParams.Parity = NOPARITY; break;
  case 1: dcbSerialParams.Parity = ODDPARITY; break;
  case 2: dcbSerialParams.Parity = EVENPARITY; break;
  }
  /*Timeouts*/
  timeouts.ReadIntervalTimeout = ReadIntervalTimeout;
  timeouts.ReadTotalTimeoutConstant = ReadTotalTimeoutConstant;
  timeouts.ReadTotalTimeoutMultiplier = ReadTotalTimeoutMultiplier;
  timeouts.WriteTotalTimeoutConstant = WriteTotalTimeoutConstant;
  timeouts.WriteTotalTimeoutMultiplier = WriteTotalTimeoutMultiplier;
  /*"Übernehmen"*/
  SetCommState(hSerial, &dcbSerialParams);
  SetCommTimeouts(hSerial, &timeouts);
  /*Hier sollten für beide obenstehenden Funktionen Exceptions programmiert werden.*/
}

void comport::send(uint8_t data[],uint64_t warte[], size_t size){
  for (size_t i{ 0 }; i < size; ++i) {
    WriteFile(hSerial, &data[i], 1, &bytes_written, nullptr);
    std::this_thread::sleep_for(std::chrono::milliseconds(warte[i]));
  }
}

void comport::send(uint8_t data[], uint64_t warte[], size_t size, int zeit){
  startzeit = clock();
  while ((static_cast<double>(clock()) - startzeit) / CLOCKS_PER_SEC < zeit) {
    send(data, warte, size);
  }
}



void comport::close(){
  CloseHandle(hSerial);
}
