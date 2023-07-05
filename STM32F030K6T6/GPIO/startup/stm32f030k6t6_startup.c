#include <stdint.h>

#define SRAM_START        0x20000000U
#define SRAM_SIZE         (4U * 1024U) //4KB
#define SRAM_END          (SRAM_START + SRAM_SIZE)

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

#define STACK_START SRAM_END

int main(void);
void Reset_Handler                (void);

void NMI_Handler                  (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void SVCall_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void WWDG_Handler                 (void) __attribute__((weak, alias("Default_Handler")));
void RTC_Handler                  (void) __attribute__((weak, alias("Default_Handler")));
void FLASH_Handler                (void) __attribute__((weak, alias("Default_Handler")));
void RCC_Handler                  (void) __attribute__((weak, alias("Default_Handler")));
void EXTI0_1_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void EXTI2_3_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void EXTI4_15_Handler             (void) __attribute__((weak, alias("Default_Handler")));
void DMA_CH1_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void DMA_CH2_3_Handler            (void) __attribute__((weak, alias("Default_Handler")));
void DMA_CH4_5_Handler            (void) __attribute__((weak, alias("Default_Handler")));
void ADC_Handler                  (void) __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_UP_TRG_COM_Handler  (void) __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void TIM3_Handler                 (void) __attribute__((weak, alias("Default_Handler")));
void TIM6_Handler                 (void) __attribute__((weak, alias("Default_Handler")));
void TIM14_Handler                (void) __attribute__((weak, alias("Default_Handler")));
void TIM15_Handler                (void) __attribute__((weak, alias("Default_Handler")));
void TIM16_Handler                (void) __attribute__((weak, alias("Default_Handler")));
void TIM17_Handler                (void) __attribute__((weak, alias("Default_Handler")));
void I2C1_Handler                 (void) __attribute__((weak, alias("Default_Handler")));
void I2C2_Handler                 (void) __attribute__((weak, alias("Default_Handler")));
void SPI1_Handler                 (void) __attribute__((weak, alias("Default_Handler")));
void SPI2_Handler                 (void) __attribute__((weak, alias("Default_Handler")));
void USART1_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));
void USART2_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));
void USART3_4_5_6_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void USB_Handler                  (void) __attribute__ ((weak, alias("Default_Handler"))); 


uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
  (uint32_t) STACK_START,
  (uint32_t) Reset_Handler,
  (uint32_t) NMI_Handler,
  (uint32_t) HardFault_Handler,
  (uint32_t) SVCall_Handler,
  (uint32_t) PendSV_Handler,
  (uint32_t) SysTick_Handler,
  (uint32_t) WWDG_Handler,
  (uint32_t) 0,
  (uint32_t) RTC_Handler,
  (uint32_t) FLASH_Handler,
  (uint32_t) RCC_Handler,
  (uint32_t) RCC_Handler,
  (uint32_t) EXTI0_1_Handler,
  (uint32_t) EXTI2_3_Handler,
  (uint32_t) EXTI4_15_Handler,
  (uint32_t) 0,
  (uint32_t) DMA_CH1_Handler,
  (uint32_t) DMA_CH2_3_Handler,
  (uint32_t) DMA_CH4_5_Handler,
  (uint32_t) ADC_Handler,
  (uint32_t) TIM1_BRK_UP_TRG_COM_Handler,
  (uint32_t) TIM1_CC_Handler,
  (uint32_t) 0,
  (uint32_t) TIM3_Handler,
  (uint32_t) TIM6_Handler,
  (uint32_t) 0,
  (uint32_t) 0,
  (uint32_t) TIM14_Handler,
  (uint32_t) TIM15_Handler,
  (uint32_t) TIM16_Handler,
  (uint32_t) TIM17_Handler,
  (uint32_t) I2C1_Handler,
  (uint32_t) I2C2_Handler, 
  (uint32_t) SPI1_Handler,
  (uint32_t) SPI2_Handler,
  (uint32_t) USART1_Handler,
  (uint32_t) USART2_Handler,
  (uint32_t) USART3_4_5_6_Handler,
  (uint32_t) 0,
  (uint32_t) USB_Handler,
};

void Default_Handler(void) {
  while(1) {
    /* Do nothing */
  }
}

void Reset_Handler(void)
{
  uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;

  uint8_t *pDst = (uint8_t *)&_sdata; //SRAM
  uint8_t *pSrc = (uint8_t *)&_etext; //FLASH

  for (uint32_t i = 0; i < size; i++) 
  {
    *pDst++ = *pSrc++;
  }

  // Init .bss section to zero in SRAM
  size = (uint32_t)&_ebss - (uint32_t)&_sbss;
  pDst = (uint8_t *)&_sbss;
  for (uint32_t i = 0; i < size; i++)
  {
    *pDst++ = 0;
  }

  main();
}