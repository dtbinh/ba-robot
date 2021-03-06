#ifndef _STRINGARRAY_H
#define _STRINGARRAY_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// private List with Data and Pointer to next element
struct Liste
{
  String data;
  Liste* next;
};

class StringArray
{
public:
  StringArray();
  void AddString(String string);
  String GetString(int index);
  void DeleteString(int index);
  int GetElementCount() {
    return elements;
  }
  int GetStringAsInt(int index);
  String GetAsConcatedString(String delim);
  String GetAsConcatedString();  
private:  
  int elements;
  Liste *completeListe;
  Liste *currentListe;
};

#endif // _STRINGARRAY_H

