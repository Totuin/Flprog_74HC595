#include "flprog74HC595.h"

FLProg74HC595::FLProg74HC595(AbstractFLProgSPI *device, uint16_t pinCS)
{
    spi = device;
    pin = pinCS;
}

void FLProg74HC595::begin()
{
    pinMode(pin, OUTPUT);
}

void FLProg74HC595::setChips(uint8_t *data, uint8_t size)
{
    chips = data;
    chipSize = size;
}
void FLProg74HC595::writePin(uint8_t chip, uint8_t pinNumber, bool value)
{
    if ((chip + 1) > chipSize)
    {
        return;
    }
    if (pinNumber > 7)
    {
        return;
    }
    if ((bitRead(chips[chip], pinNumber)) == value)
    {
        return;
    }
    bitWrite(chips[chip], pinNumber, value);
    isNeedSend = true;
}

void FLProg74HC595::pool()
{
    if (!isNeedSend)
    {
        return;
    }
    if (!isReady())
    {
        return;
    }
    if (chipSize > 0)
    {
        digitalWrite(pin, false);
        for (uint8_t i = 0; i < chipSize; i++)
        {
            spi->transfer(chips[i]);
        }
        digitalWrite(pin, true);
        isNeedSend = false;
    }
}

bool FLProg74HC595::isReady()
{
    if (spi == 0)
    {
        return false;
    }
    return spi->isReady();
}