/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "wwdg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t ADC_Value[150];
uint8_t i;
uint32_t ad1,ad2,ad3;
int delayOnTimer=0;
int setDelayOnTimer=0;


int autoOntimer=10;
int autoOfftimer=10;

int setAutoOntimer=10;
int setAutoOfftimer=10;
int auto_run=1;
int state=0;
int lastH1=0;
int lastH2=0;
#define delayOnTimerMax 30
#define HIGH 1
#define LOW 0
#define NO 1
#define OFF 0
#define min 60
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC_Init();
  //MX_WWDG_Init();
  /* USER CODE BEGIN 2 */

  HAL_ADC_Start_DMA(&hadc, (uint32_t*)&ADC_Value, 60);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
      for(i = 0,ad1 =0,ad2=0,ad3=0 ;i < 60;)
      {
          ad1 += ADC_Value[i++];
          ad2 += ADC_Value[i++];
          ad3 += ADC_Value[i++];
      }
      //ADC MAX=4096 409600m=> 409s
      ad1 /= 20;//1-10m
      ad2 /= 20;//3-720m (0.05hr-12hr)
      ad3 /= 20;//0-3m
      setAutoOntimer=ad1*1.66;		//10/6=1.66
	  setAutoOfftimer=ad2*120; 		//720m/6m=120
      setDelayOnTimer=ad3/2; 		//409s=6m 409s/2=3m

      if(auto_run&&lastH1!=1&&lastH2!=1){
    	  switch(state){
    	  case 0:
    		  HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1_Pin, HIGH);
    		  HAL_GPIO_WritePin(RELAY_2_GPIO_Port, RELAY_2_Pin, HIGH);
    		  HAL_GPIO_WritePin(RELAY_3_GPIO_Port, RELAY_3_Pin, HIGH);
    		  if(autoOfftimer>0){
    			  autoOfftimer--;
    		  }else{
    			  autoOfftimer=setAutoOfftimer;
    			  state=1;
    		  }

    		  break;
    	  case 1:
    		  HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1_Pin, LOW);
    		  HAL_GPIO_WritePin(RELAY_2_GPIO_Port, RELAY_2_Pin, LOW);
    		  HAL_GPIO_WritePin(RELAY_3_GPIO_Port, RELAY_3_Pin, LOW);
    		  if(autoOntimer>0){
    			  autoOntimer--;
    		  }else{
    			  autoOntimer=setAutoOntimer;
    			  state=0;
    		  }
    		  break;
    	  }
      }
     if(HAL_GPIO_ReadPin(H1_GPIO_Port, H1_Pin)==0){//H1觸發
    	 HAL_GPIO_WritePin(RELAY_3_GPIO_Port, RELAY_3_Pin, HIGH);
    	 lastH1=1;
    	 if(delayOnTimer<setDelayOnTimer){
    		 delayOnTimer++;
    	 }
     }else{
    	 delayOnTimer=0;
    	 if(lastH1==1){
    	 HAL_GPIO_WritePin(RELAY_3_GPIO_Port, RELAY_3_Pin, LOW);
    	 lastH1=0;
    	 }
     }

     if(delayOnTimer>=delayOnTimerMax){
    	 HAL_GPIO_WritePin(RELAY_4_GPIO_Port, RELAY_4_Pin, HIGH);
     }else{
    	 HAL_GPIO_WritePin(RELAY_4_GPIO_Port, RELAY_4_Pin, LOW);
     }

     if(HAL_GPIO_ReadPin(H2_GPIO_Port, H2_Pin)==0){//H2觸發
    	 HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1_Pin, HIGH);
    	 HAL_GPIO_WritePin(RELAY_2_GPIO_Port, RELAY_2_Pin, HIGH);
    	 HAL_GPIO_WritePin(RELAY_5_GPIO_Port, RELAY_5_Pin, HIGH);
    	 lastH2=1;
     }else{
    	 if(lastH2==1){
    	 HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1_Pin, LOW);
    	 HAL_GPIO_WritePin(RELAY_2_GPIO_Port, RELAY_2_Pin, LOW);
    	 HAL_GPIO_WritePin(RELAY_5_GPIO_Port, RELAY_5_Pin, LOW);
    	 lastH2=0;
    	 }
     }

     //HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
	 HAL_Delay(100);

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
