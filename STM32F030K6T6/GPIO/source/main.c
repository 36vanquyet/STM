#include <stdint.h>
#include <stdbool.h>

typedef struct {
  uint32_t MODER;
  uint32_t OTYPER;
  uint32_t OSPEEDR;
  uint32_t PUPDR;
  uint32_t IDR;
  uint32_t ODR;
  uint32_t BSRR;
  uint32_t LCKR;
  uint32_t AFRL;
} GPIO_t;

typedef struct {
  uint32_t CR;
  uint32_t CFGR;
  uint32_t CIR;
  uint32_t APB2RSTR;
  uint32_t APB1RSTR;
  uint32_t AHBENR;
  uint32_t APB2ENR;
  uint32_t APB1ENR;
  uint32_t BDCR;
  uint32_t CSR;
  uint32_t AHBRSTR;
  uint32_t CFGR2;
  uint32_t CFRG3;
  uint32_t CR2;
} RCC_t;

RCC_t *RCC = (RCC_t *)0x40021000;

GPIO_t *GPIOA = (GPIO_t *)0x48000000;

int main(void) {
  // // Enable SYSCFG clock
  // RCC->APB2ENR |= (0x01UL << 0U);
  // uint32_t temp = (RCC->APB2ENR) & (0x01UL << 0U);
  // // Enable PWR clock
  // RCC->APB1ENR |= (0x1UL << 28U);
  // temp = (RCC->APB1ENR) & (0x1UL << 28U);

  // // Enable HSI clock
  // RCC->CR |= (0x1UL << 0);
  // // Configure HSI clock
  // RCC->CR = ((RCC->CR) & (~(0x1FUL << 3U))) | (0x10UL << 3);

  // // Configure the main PLL clock source, predivider and multiplication factor
  // RCC->CFGR2 = ((RCC->CFGR2) & (~(0xFUL << 0U))) | (0U);
  // RCC->CFGR = ((RCC->CFGR) & (~((0xFUL << 18U) | (0x1UL << 16U)))) | (0x0U);

  // // Enable the main PLL
  // RCC->CR |= (0x1UL << 24U);

  //   /* Set the highest APB divider in order to ensure that we do not go through
  //      a non-spec phase whatever we decrease or increase HCLK. */
  // RCC->CFGR = ((RCC->CFGR) & (~(0x7UL << 8U))) | (0x7UL << (8U));
  // // Set the new HCLK clock divider
  // RCC->CFGR = ((RCC->CFGR) & (~(0xFUL << 4U))) | (0U);

  // // SYSCLK Configuration
  // RCC->CFGR = ((RCC->CFGR) & (~(0x3UL << 0U))) | (0x02U);

  // // PCLK1 Configuration
  // RCC->CFGR = ((RCC->CFGR) & (~(0x7UL << 8U))) | 0;

  // Enable GPIOA clock
  RCC->AHBENR |= (0x1UL << 17U);
  // temp = RCC->AHBENR & (0x1UL << 17U);
  // (void)temp;

  GPIOA->MODER |= 1 << 16;
  GPIOA->OTYPER &= ~(1 << 8);
  GPIOA->OSPEEDR |= 1 << 16;
  GPIOA->PUPDR &= ~(3 << 16);
  GPIOA->BSRR |= (1 << 8);

  bool status = false;

  while (1) {
    status = !status;
    GPIOA->ODR = status << 8;
    for (uint32_t i = 0; i < 0x3ffff; i++) {

    }
  }

  return 0;
}