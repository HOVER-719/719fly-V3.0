#ifndef __TFMINI_H
#define __TFMINI_H
#include "main.h"
extern uint16_t TFminiStrength;
extern uint8_t TFminiDistance;
//extern uint8_t TFminiMode,TFminiCheckSum;
void TFmini_Init(void);
void MUSART1_SendData(uint8_t data);

#endif
