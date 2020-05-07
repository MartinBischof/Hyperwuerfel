#ifndef COMPORT_H
#define COMPORT_H

#include <Windows.h>
#include <fileapi.h>
#include <iostream>
#include <cstdint>
#include<thread>
#include<chrono>
#include <ctime>

class comport {
public:
  /*Standardkonstruktor (1 Stopbit, Keine Parität, 9600 Baudrate), als Parameter wird der Komportname
  erwartet.*/
  comport(const char* comport);
  /*Konstruktor mit gewünschten einstellungen:*/
  comport(const char* comport, int baudrate, unsigned char bytesize, short stopbit, short parity,
    DWORD ReadIntervalTimeout, DWORD ReadTotalTimeoutConstant, DWORD ReadTotalTimeoutMultiplier,
    DWORD WriteTotalTimeoutConstant, DWORD WriteTotalTimeoutMultiplier);

  /*
  Funktion send() kriegt das Array mit den zu sendenden Daten und ein Array mit den Wartezeiten in Millisekunden
  pro einzelnes Bfehl rein. Der Grund ist, da die befehle 8Bit lang sind kann mann nur zahlen bis 255 ((2^8)-1) darstellen
  und somit wäre die längste Zeit die man warten kann 255 Millisekunden lang (angenommen man hätte die Wartezeit
  in dem selben array spezifiziert)
  */
  ///WICHTIG: Beide Arrays müssen gleich lang sein UND das WARTE array darf KEINE 0er erhalten
  void send(uint8_t data[], uint64_t warte[], size_t size);
  ///Überladung um ein Frame zeit lang auf dem Würfel darzustellen
  void send(uint8_t data[], uint64_t warte[], size_t size, int zeit);
  /*Funktion close beendet und schließt den Comport*/
  void close();

private:
  HANDLE hSerial;
  DCB dcbSerialParams;
  COMMTIMEOUTS timeouts;
  DWORD bytes_written;
  size_t size;
  clock_t startzeit;
};


#endif // COMPORT_H
