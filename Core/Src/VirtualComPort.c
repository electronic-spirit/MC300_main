
#include "VirtualComPort.h"
#include "string.h"

char strtx[100];
char strrx[100];

void VirtualComPort_process(void)
{
	sprintf(strtx, "USB transmit\r\n");
	CDC_Transmit_FS((uint8_t*)strtx, strlen(strtx));
}
