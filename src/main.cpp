#include <Watchy.h> //include the Watchy library
#include "OptimaLTStd24pt7b.h"
#include "OptimaLTStdBlack34pt7b.h"

class WatchFace : public Watchy
{ //inherit and extend Watchy class
protected:
  void displayLine(const char *s)
  {
    display.print(s);
  }

public:
  void drawWatchFace()
  { //override this method to customize how the watch face looks
    Serial.printf("drawWatchFace currentTime %02d:%02d\n", currentTime.Hour, currentTime.Minute);
    const char *lows[12] = {"twelve", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven"};
    const char *teens[9] = {"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    const char *tens[10] = {"oh", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    //drawbg
    display.fillScreen(GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);
    display.setTextWrap(false);

    weatherData wd = Watchy::getWeatherData();

    //drawtime
    display.setFont(&OptimaLTStd_Black34pt7b);
    // hour
    display.setCursor(0, 70);
    displayLine(lows[currentTime.Hour % 12]);
    display.setCursor(0, 120);
    display.setFont(&OptimaLTStd24pt7b);
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
    }
    // zero to ten or twenty to fifty nine
    else
    {
      displayLine(tens[currentTime.Minute / 10]);
      display.setCursor(0, 170);
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