#include "main.h"
__IO uint32_t LocalTime = 0;
uint32_t timingDelay;
#define SYSTEMTICK_PERIOD_MS 10

unsigned int ADC3_VALUE = 0;
void uartPutch(char s)
{
    USART_SendData(USART3, (unsigned short int) s);
    while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
}
void UsartTask()
{
	printf("ADCValue: %04d\n", ADC3_VALUE);
}


//Initialize GPIO and USART3
void initUSART3(void){

	//Enable GPIO Clocks For USART3
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	//Enable Clocks for USART2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	

	//Structure With Data For GPIO Configuration
	GPIO_InitTypeDef GPIO_InitStructure;

	//Structure With Data For USART Configuration
	USART_InitTypeDef USART_InitStructure;

	//GPIO Configuration
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//Connect USART pins to AF
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

	//USART Parameters
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx ;

	//Configuring And Enabling USART2
	USART_Init(USART3, &USART_InitStructure);
	USART_Cmd(USART3, ENABLE);

}
void initADC(void){
    ADC_InitTypeDef ADC_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    DMA_InitTypeDef DMA_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

    DMA_InitStructure.DMA_Channel = DMA_Channel_2;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (unsigned int)0x4001224C;
    DMA_InitStructure.DMA_Memory0BaseAddr =(unsigned int) &ADC3_VALUE;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = 1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream0, &DMA_InitStructure);
    DMA_Cmd(DMA2_Stream0, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStructure);

    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    ADC_Init(ADC3, &ADC_InitStructure);

    ADC_RegularChannelConfig(ADC3, ADC_Channel_3, 1, ADC_SampleTime_3Cycles);

    ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);

    ADC_DMACmd(ADC3, ENABLE);

    ADC_Cmd(ADC3, ENABLE);

    ADC_SoftwareStartConv(ADC3);
}

void initLED()
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_InitTypeDef gpio;
    GPIO_StructInit(&gpio);
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOD, &gpio);
    GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
}

void toggleLED()
{
    GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	Delay(100);
    GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	Delay(100);
}
char data[100];
struct udp_pcb *upcb;
void udp_connection_init(void)
{
	struct ip_addr DestIPaddr;
	upcb = (struct udp_pcb *)udp_new();
	IP4_ADDR(&DestIPaddr, 192, 168, 141, 177 );
	udp_connect(upcb, &DestIPaddr, 7777);
//	udp_remove(upcb);
}
void udp_echoclient_connect(void)
{
	struct pbuf *p;
	err_t err;
	sprintf((char*)data, "sending udp client message");
	p = pbuf_alloc(PBUF_TRANSPORT,strlen((char*)data), PBUF_POOL);
	if (p != NULL) {
		pbuf_take(p, (char*)data, strlen((char*)data));
		udp_send(upcb, p); 
		pbuf_free(p);
	}
	else {
		printf("ERR pbuf_alloc: %d\n", err);
	}

}
void udp_send_msg(void)
{


}
int main() {
	SystemInit();
	ETH_BSP_Config();
	initLED();
	initADC();
	initUSART3();
	LwIP_Init();
	udp_connection_init();
    do {
		UsartTask();
		udp_echoclient_connect();
		toggleLED();
		if (ETH_CheckFrameReceived())
		{
			LwIP_Pkt_Handle();
		}
		LwIP_Periodic_Handle(LocalTime);
    } while (1);
	while (1) printf("SYSTEM DOWN\n");
}

void Delay(uint32_t nCount) {
    timingDelay = LocalTime + nCount;
    while(timingDelay > LocalTime) {
        __NOP();
    }
}

void Time_Update() {
	LocalTime += SYSTEMTICK_PERIOD_MS;
}

