#pragma once
#include <stdint.h>
#include <math.h>
#include "Arduino.h"
#include "flprogUtilites.h"
#include "flprogSPI.h"

class FLProg74HC595
{
public:
    FLProg74HC595(AbstractFLProgSPI *device, uint16_t pinCS);
    void begin();
    void setChips(uint8_t *data, uint8_t size);
    void writePin(uint8_t chip, uint8_t pinNumber, bool value);
    void pool();

private:

bool isReady();
    AbstractFLProgSPI *spi;
    uint16_t pin;
    uint8_t *chips;
    uint8_t chipSize = 0;
    bool isNeedSend = true;
    
};
