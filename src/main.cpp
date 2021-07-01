#include <Watchy.h> //include the Watchy library
#include "NunitoSans_Bold28pt7b.h"
#include "NunitoSans_Light28pt7b.h"

class WatchFace : public Watchy
{ //inherit and extend Watchy class
protected:
  uint16_t lines;
  void displayLine(const char *s)
  {
    display.print(s);
    lines += 1;
    display.setCursor(8, lines * 47 - 5);
  }

public:
  void drawWatchFace()
  { //override this method to customize how the watch face looks
    Serial.printf("drawWatchFace currentTime %02d:%02d\n", currentTime.Hour, currentTime.Minute);
    const char *lows[12] = {"twelve", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven"};
    const char *teens[9] = {"eleven", "twelve", "thir", "four", "fifteen", "sixteen", "seven", "eigh", "nine"};
    const char *teens2[9] = {nullptr, nullptr, "teen", "teen", nullptr, nullptr, "teen", "teen", "teen"};
    const char *tens[10] = {"oh", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    //drawbg
    display.fillScreen(GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);
    display.setTextWrap(false);

    weatherData wd = Watchy::getWeatherData();

    //drawtime
    lines = 1;
    display.setCursor(8, lines * 47 - 5);
    display.setFont(&NunitoSans_Bold28pt7b);
    // hour
    displayLine(lows[currentTime.Hour % 12]);
    display.setFont(&NunitoSans_Light28pt7b);
    // minutes, can be up to two lines
    // exactly on the hour
    if (currentTime.Minute == 0)
    {
      if (currentTime.Hour == 0)
      {
        displayLine("midnight");
      }
      else if (currentTime.Hour == 12)
      {
        displayLine("noon");
      }
      else
      {
        displayLine("o'clock");
      }
      return;
    }
    // eleven to nineteen
    if (10 < currentTime.Minute && currentTime.Minute < 20)
    {
      displayLine(teens[currentTime.Minute - 11]);
      if (teens2[currentTime.Minute - 11] != nullptr)
      {
        displayLine(teens2[currentTime.Minute - 11]);
      }
    }
    // zero to ten or twenty to fifty nine
    else
    {
      displayLine(tens[currentTime.Minute / 10]);
      if (currentTime.Minute % 10 > 0)
      {
        displayLine(lows[currentTime.Minute % 10]);
      }
    }
  }
};

WatchFace m; //instantiate your watchface

void setup()
{
  m.init(); //call init in setup
}

void loop()
{
  // this should never run, Watchy deep sleeps after init();
}