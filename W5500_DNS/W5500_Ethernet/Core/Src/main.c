/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>
#include <string.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "w5500_spi.h"
#include "wizchip_conf.h"
#include "socket.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LISTEN_PORT 5000
#define RECEIVE_BUFF_SIZE 128
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
wiz_NetInfo gWIZNETINFO2 = {
		.mac = { 0x80, 0x34, 0x28, 0x74, 0xA5, 0xCB },//MSB - LSB
		.ip ={ 192, 168, 0, 112 },
		.sn = { 255, 255, 255, 0 },
		.gw ={ 192, 168, 0, 1 },
		.dns = { 8, 8, 8, 8 },
		.dhcp = NETINFO_STATIC };

uint8_t destination_ip[]={192,168,0,33};
uint16_t destination_port=5000;
uint8_t receive_buff[RECEIVE_BUFF_SIZE];//to receive data from client
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
static void UWriteData(const char data);
static void PHYStatusCheck(void);
static void PrintPHYConf(void);

static void simpleClientExample(void);
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
	setbuf(stdout, NULL);
	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_SPI1_Init();
	MX_USART2_UART_Init();
	/* USER CODE BEGIN 2 */
	W5500Init();
	ctlnetwork(CN_SET_NETINFO, (void*) &gWIZNETINFO2);

	wiz_PhyConf phyconf;

	phyconf.by = PHY_CONFBY_SW;
	phyconf.duplex = PHY_DUPLEX_FULL;
	phyconf.speed = PHY_SPEED_10;
	phyconf.mode = PHY_MODE_AUTONEGO;

	ctlwizchip(CW_SET_PHYCONF, (void*) &phyconf);

	PHYStatusCheck();
	PrintPHYConf();
	/* USER CODE END 2 */

	printf("\r\n*****************SIMPLE TCP ECHO SERVER******************\r\n");

	while (1) {
		printf("\r\nInitializing server socket\r\n");

		//Parameters in order socket_id, protocol TCP or UDP, Port number, Flags=0
		//Return value is socket ID on success
		if (socket(1, Sn_MR_TCP, LISTEN_PORT, 0) != 1) {
			//error
			printf("Cannot create Socket!\r\n");
			while (1)
				;		  //halt here
		}

		//success
		printf("Socket Created Successfully ! \r\n");

		uint8_t socket_io_mode = SOCK_IO_BLOCK;

		ctlsocket(1, CS_SET_IOMODE, &socket_io_mode);	//set blocking IO mode

		printf("Start listening on port %d ! \r\n", LISTEN_PORT);
		printf("Waiting for a client connection. \r\n");

		//Make it a passive socket (i.e. listen for connection)
		if (listen(1) != SOCK_OK)//our socket id is 1 (w5500 have 8 sockets from 0-7)
		{
			//error
			printf("Cannot listen on port %d", LISTEN_PORT);

			while (1)
				;

		}

		uint8_t sr = 0x00;		  //socket status register

		do {
			sr = getSn_SR(1);		  //read status reg (SR of socket 1)
		} while (sr != 0x17 && sr != 0x00);

		if (sr == 0x00) {
			printf("Some error occurred on server socket. Please restart.\r\n");
			while (1)
				;
		}

		if (sr == 0x17) {
			//we come here only when a client has connected.
			//Now we can read data from the socket
			printf("A client connected!\r\n");
			printf("Waiting for Client Data ...!\r\n");

			while (1) {
				int len = recv(1, receive_buff, RECEIVE_BUFF_SIZE);

				if (len == SOCKERR_SOCKSTATUS) {
					//client has disconnected
					printf("Client has disconnected\r\n");
					printf("*** SESSION OVER ***\r\n\r\n");
					break;
				}

				receive_buff[len] = '\0';

				printf("Received %d bytes from client\r\n", len);
				printf("Data Received: %s", receive_buff);

				//Echo the data back encloused in a [] pair
				send(1, (uint8_t*) "[", 1);			  //starting sq bracket
				send(1, receive_buff, len);			  // the data
				send(1, (uint8_t*) "]", 1);			  //closing sq bracket

				printf("\r\nECHO sent back to client\r\n");

				//Look for quit message and quit if received
				if (strcmp((char*) receive_buff, "QUIT") == 0) {
					printf("Received QUIT command from client\r\n");
					printf("Disconnecting ... \r\n");
					printf("*** SESSION OVER ***\r\n\r\n");
					disconnect(1);			  //disconnect from the clinet
					break;			  //come out of while loop
				}

			}			  //While loop (as long as client is connected)

		}			  //if block, client connect success
	}			  //while loop for next client wait
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */
  __HAL_SPI_ENABLE(&hspi1);
  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void UWriteData(const char data)
{
	while(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TXE)==RESET);

	huart2.Instance->TDR=data;

}

int __io_putchar(int ch)
{
	UWriteData(ch);
	return ch;
}

void PHYStatusCheck(void)
{
	uint8_t tmp;


	do
	{
		printf("\r\nChecking Ethernet Cable Presence ...");
		ctlwizchip(CW_GET_PHYLINK, (void*) &tmp);

		if(tmp == PHY_LINK_OFF)
		{
			printf("NO Cable Connected!");
			HAL_Delay(1500);
		}
	}while(tmp == PHY_LINK_OFF);

	printf("Good! Cable got connected!");

}

void PrintPHYConf(void)
{
	wiz_PhyConf phyconf;

	ctlwizchip(CW_GET_PHYCONF, (void*) &phyconf);

	if(phyconf.by==PHY_CONFBY_HW)
	{
		printf("\n\rPHY Configured by Hardware Pins");
	}
	else
	{
		printf("\n\rPHY Configured by Registers");
	}

	if(phyconf.mode==PHY_MODE_AUTONEGO)
	{
		printf("\n\rAutonegotiation Enabled");
	}
	else
	{
		printf("\n\rAutonegotiation NOT Enabled");
	}

	if(phyconf.duplex==PHY_DUPLEX_FULL)
	{
		printf("\n\rDuplex Mode: Full");
	}
	else
	{
		printf("\n\rDuplex Mode: Half");
	}

	if(phyconf.speed==PHY_SPEED_10)
	{
		printf("\n\rSpeed: 10Mbps");
	}
	else
	{
		printf("\n\rSpeed: 100Mbps");
	}
}

static void simpleClientExample(void)
{
	  W5500Init();
	  ctlnetwork(CN_SET_NETINFO, (void* )&gWIZNETINFO2);

	  wiz_PhyConf phyconf;

	  phyconf.by = PHY_CONFBY_SW;
	  phyconf.duplex = PHY_DUPLEX_FULL;
	  phyconf.speed = PHY_SPEED_10;
	  phyconf.mode = PHY_MODE_AUTONEGO;

	  ctlwizchip(CW_SET_PHYCONF, (void*)&phyconf);

	  PHYStatusCheck();
	  PrintPHYConf();
	  /* USER CODE END 2 */


	  /* Infinite loop */
	  /* USER CODE BEGIN WHILE */
	  if(socket(1, Sn_MR_TCP, 0, 0)==1)
	  {
		  printf("\r\nSocket Created Successfully");
	  }
	  else
	  {
		  printf("\r\nCannot create socket");
		  while(1);
	  }

	  printf("\r\nConnecting to server: %d.%d.%d.%d @ TCP Port: %d",destination_ip[0],destination_ip[1],destination_ip[2],destination_ip[3],destination_port);
	  if(connect(1, destination_ip, destination_port)==SOCK_OK)
	  {
		  printf("\r\nConnected with server.");
	  }
	  else
	  {
		  //failed
		  printf("\r\nCannot connect with server!");
		  while(1);
	  }

	  while (1)
	  {
		  //Return value of the send() function is the amount of data sent
		  if(send(1, "JAI SHREE RAM!\r\n", 16)<=SOCK_ERROR)
		  {
			  printf("\r\nSending Failed!");
			  while(1);

		  }
		  else
		  {
			  printf("\r\nSending Success!");
		  }

		  HAL_Delay(1000);
	  }
}
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
