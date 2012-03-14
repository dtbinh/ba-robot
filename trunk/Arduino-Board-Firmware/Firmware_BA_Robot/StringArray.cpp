#include "StringArray.h"

StringArray::StringArray()
{
  elements = 0;  
}

void StringArray::AddString(String string)
{
  if (elements == 0)
  {
    Liste* list = new Liste;
    list->data = string;
    completeListe = list;
    currentListe = completeListe;
  }
  else
  {
    Liste* newList = new Liste;
    newList->data = string;
    currentListe->next = newList;
    currentListe = newList;
  }
  elements++;
}

String StringArray::GetString(int index)
{
  if (index >= elements)
    return "Error";

  Liste* tempList = completeListe;
  for (int i = 0; i  <= index; i++)
  {
    if (i == index)
    {
      return tempList->data;
    }
    tempList = tempList->next;
  }
}

void StringArray::DeleteString(int index)
{
  if (index >= elements)
    return;

  Liste* tempList = completeListe;

  if (index == 0)
  {
    completeListe = completeListe->next;
    return;
  }

  for (int i = 1; i  <= index; i++)
  {
    if (i == index)
    {
      if (index == elements - 1)
      {
        tempList->next = NULL;
        elements--;
        return;
      }
      else
      {
        tempList->next = tempList->next->next;
        elements--;
        return;
      }
    }
    tempList = tempList->next;
  }
}

int StringArray::GetStringAsInt(int index)
{
  String tempData = "";
  if (index >= elements)
    return 0x00;

  Liste* tempList = completeListe;
  for (int i = 0; i  <= index; i++)
  {
    if (i == index)
    {
      tempData = tempList->data;
      break;
    }
    tempList = tempList->next;
  }

  char tempArray[tempData.length() + 1];
  tempData.toCharArray(tempArray,tempData.length() + 1);
  tempArray[tempData.length()] = '\0';
  int tempInt = atoi(tempArray);

  return tempInt;
}
