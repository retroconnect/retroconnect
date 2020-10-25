#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"
#include "xtensa/core-macros.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#define LOW 0
#define HIGH 1
#define PARALLEL_0 12
#define GPIO_OUTPUT_PIN_SEL ((1<<PARALLEL_0) | (1<<(PARALLEL_0+1)) | (1<<(PARALLEL_0+2)) | (1<<(PARALLEL_0+3)) | (1<<(PARALLEL_0+4)) | (1<<(PARALLEL_0+5)) | (1<<(PARALLEL_0+6)) | (1<<(PARALLEL_0+7)))

static portMUX_TYPE my_mutex;
static uint32_t timer;
uint32_t cycles_current;
uint32_t cycles_difference;

//       | GEN     ESP32  Genesis    |
const uint8_t PIN_1 = 12; // UP          YELLOW
const uint8_t PIN_2 = 13; // DOWN        ORANGE
const uint8_t PIN_3 = 14; // LEFT        RED
const uint8_t PIN_4 = 15; // RIGHT       BROWN
//const uint8_t PIN_5;    // (5V unused) BLACK
const uint8_t PIN_6 = 16; // FIRE1       GREEN
const uint8_t PIN_7 = 18; // SELECT      BLUE
const uint8_t PIN_9 = 17; // FIRE2       WHITE
//PIN_RX = 21 //20
//PIN_TX = 22 //21         

uint8_t data[2];
bool sixButtonMode = true;
int state = 0;
int stateCap = 4;
bool wasHigh = true;
bool isHigh;

const uint8_t PIN_1_BIT = 0;
const uint8_t PIN_2_BIT = 1;
const uint8_t PIN_3_BIT = 2;
const uint8_t PIN_4_BIT = 3;
const uint8_t PIN_6_BIT = 4;
//const uint8_t PIN_7_BIT;
const uint8_t PIN_9_BIT = 5;
const uint8_t PIN_BITMASK = (1 << PIN_1_BIT) | (1 << PIN_2_BIT) |(1 << PIN_3_BIT) |(1 << PIN_4_BIT) |(1 << PIN_6_BIT) |(1 << PIN_9_BIT); // bit mask for PORTD write updates

/*
  Low = pressed

  Pin  Connection
  ---  ---------------
  5   Power: +5 Volts
  7   Select signal
  8   Power: Ground

  Pin  Connection with select low  Connection with select high
  ---  --------------------------  ---------------------------
  2   joypad up signal            joypad up signal
  3   joypad down signal          joypad down signal
  4   logic low (ground)          joypad left signal
  5   logic low (ground)          joypad right signal
  6   Button A signal             Button B signal
  9   Start button signal         Button C signal
*/

void gpio_setup() {
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);
}

void init_uart() {
  /* Configure parameters of an UART driver,
   * communication pins and install the driver */
  uart_config_t uart_config = {
    .baud_rate = 921600,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
  };
  // Configure UART parameters
  ESP_ERROR_CHECK(uart_param_config(UART_NUM_1, &uart_config));
  ESP_ERROR_CHECK(uart_set_pin(UART_NUM_1, 22, 21, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
  ESP_ERROR_CHECK(uart_driver_install(UART_NUM_1, 2048, 0, 0, NULL, 0));
}

void parallel_write(uint8_t value) {
  uint32_t signal_output =
    (REG_READ(GPIO_OUT_REG) & ~(0xFF << PARALLEL_0)) | (((uint32_t)value) << PARALLEL_0);
  //printf("OLD: %d, NEW: %d\n", value, signal_output);
  REG_WRITE(GPIO_OUT_REG, signal_output);
}

IRAM_ATTR void updatePORT(int pin1, int pin2, int pin3, int pin4, int pin6, int pin9) {
  int newVal = (pin1 << PIN_1_BIT) | (pin2 << PIN_2_BIT) | (pin3 << PIN_3_BIT) | (pin4 << PIN_4_BIT) | (pin6 << PIN_6_BIT) | (pin9 << PIN_9_BIT); // form mask of new values
  parallel_write(newVal); // clear all of the masked pins by anding with the inverted bitmask... then or in the updated bit data  
}

IRAM_ATTR void Select( void * parameter) {
  portENTER_CRITICAL(&my_mutex);
  while(1) {
    isHigh = REG_READ(GPIO_IN_REG) & (1<<PIN_7);//(GPIO.in >> PIN_7) & 0x1;
    if (!wasHigh && isHigh) {
      //printf("HIGH\n");
      switch (state) {
        case 1:
        case 3:
        case 7:
          updatePORT(data[0] & 1, (data[0] & 2) >> 1, (data[0] & 4) >> 2, (data[0] & 8) >> 3, (data[0] & 16) >> 4, (data[0] & 32) >> 5);
          break;    
        case 5:
          updatePORT((data[1] & 2) >> 1, (data[1] & 4) >> 2, (data[1] & 8) >> 3, data[1] & 1, (data[0] & 16) >> 4, (data[0] & 32) >> 5);
          break;
        default:
          state++;
          break;
      } 
      wasHigh = true;
      state = (state+1) % stateCap;
    }
    else if (wasHigh && !isHigh) {
      //printf("LOW\n");

      //Restart every 70us for 3 button mode pulse sets
      if (sixButtonMode) {
        cycles_current = XTHAL_GET_CCOUNT();
        cycles_difference = cycles_current - timer;
        if (cycles_difference > 33600 || cycles_current < timer) { //70us @ 240mhz = 16800  // 140us @ 240mz = 33600
          state = 0;
          timer = cycles_current;
        }
      } 

      switch(state) {
        case 0:
        case 2:
          updatePORT(data[0] & 1, (data[0] & 2) >> 1, LOW, LOW, (data[0] & 64) >> 6, (data[0] & 128) >> 7);
          break;
        case 4:
          updatePORT(LOW, LOW, LOW, LOW, (data[0] & 64) >> 6, (data[0] & 128) >> 7);
          break;
        case 6:
          updatePORT(HIGH, HIGH, HIGH, HIGH, (data[0] & 64) >> 6, (data[0] & 128) >> 7);
          break;
        default:
          state++;
          break;
      }
      wasHigh = false;
      state = (state+1) % stateCap;
    }
  }
}

IRAM_ATTR void SerialHandler( void * parameter) {
  int i = 0;
  while(1) {
    //Read data from UART
    int bytes_available = 0;
    uart_get_buffered_data_len(UART_NUM_1, (size_t*)&bytes_available);
    if (bytes_available >= 2) {
      uart_read_bytes(UART_NUM_1, data, 2, 100);
      updatePORT(data[0] & 1, (data[0] & 2) >> 1, (data[0] & 4) >> 2, (data[0] & 8) >> 3, (data[0] & 16) >> 4, (data[0] & 32) >> 5);
      //printf("%d - First byte: %u\n", i, data[0]);
      //printf("%d - Second Byte: %u\n", i, data[1]);
      i++;
    }
  }
}

void app_main(void)
{
  printf("Started program!\n");
  
  //GPIO handling From here: https://stackoverflow.com/questions/52348930/esp32-direct-port-manipulation
  
  init_uart();
  gpio_setup();
  gpio_set_direction(PIN_7, GPIO_MODE_INPUT); // SELECT
  
  data[0] = 255;
  data[1] = 255;

  updatePORT(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH);

  if (sixButtonMode) {
    stateCap = 8;
  } else {
    stateCap = 4;
  }
  
  vPortCPUInitializeMutex(&my_mutex);
  timer = XTHAL_GET_CCOUNT();

  TaskHandle_t Task2;
  xTaskCreatePinnedToCore(
      Select,   /* Function to implement the task */
      "Select", /* Name of the task */
      10000,           /* Stack size in words */
      NULL,            /* Task input parameter */
      25,               /* Priority of the task */
      &Task2,          /* Task handle. */
      1);              /* Core where the task should run */

  TaskHandle_t Task1;
  xTaskCreatePinnedToCore(
      SerialHandler,   /* Function to implement the task */
      "SerialHandler", /* Name of the task */
      10000,           /* Stack size in words */
      NULL,            /* Task input parameter */
      24,               /* Priority of the task */
      &Task1,          /* Task handle. */
      0);              /* Core where the task should run */
}
