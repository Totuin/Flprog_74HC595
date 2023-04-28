
#include "flprog74HC595.h"

FLProgSPI spiBus(0);
FLProg74HC595 chip(&spiBus, 10);
uint8_t chips[1];
uint32_t startTime;
byte counter = 0;
void setup()
{
    startTime = millis();
    spiBus.begin();
    chip.setChips(chips, 1);
    chip.begin();
}

void loop()
{
    chip.pool();
    if (flprog::isTimer(startTime, 200))
    {
        counter++;
        if (counter == 8)
        {
            counter = 0;
        }
        for (uint8_t i = 0; i < 8; i++)
        {
            chip.writePin(0, i, (i == counter));
        }
        startTime = millis();
    }
}