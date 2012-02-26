#ifndef _STRINGARRAY_H
#define _STRINGARRAY_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class StringArray
{
public:
  StringArray();
  void AddString(String string);
  String GetString(int index);
  
private:
  
  int elements;
};

#endif
