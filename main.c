#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_GPIO GPIO_NUM_14
int i = 1;

void led_task(void *param){
  int led_state=0;
  while(1){
    led_state = !led_state;

    gpio_set_level(LED_GPIO, led_state);

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void print_task(void *param){
  while(1){
    printf("int is %d bytes.\n", i);
    i++;
    vTaskDelay(pdMS_TO_TICKS(300));
  }
}

void app_main(void){
  gpio_set_direction(LED_GPIO,GPIO_MODE_OUTPUT);
  gpio_set_level(LED_GPIO,0);

  xTaskCreate(led_task,"led_task", 2048,NULL,1,NULL);
  xTaskCreate(print_task,"print_task", 2048,NULL,1,NULL);
}

