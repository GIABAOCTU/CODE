#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "esp_adc_cal.h"

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (18) // Define the output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_5_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY               (24) // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define LEDC_FREQUENCY          (100000) // Frequency in Hertz. Set frequency at 5 kHz
#define ADC3_TEST_CHANNEL (3)
#define ADC2_TEST_CHANNEL (6)
//#define ADC6_TEST_CHANNEL (6)
//#define ADC4_TEST_CHANNEL (4) //GPIO 32


 static void example_ledc_init(void)
{
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 5 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}


void adc1task(void* arg)
{
    // initialize ADC
    adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(ADC3_TEST_CHANNEL,ADC_ATTEN_11db);
  //  adc1_config_channel_atten(ADC2_TEST_CHANNEL,ADC_ATTEN_11db);
   // adc1_config_channel_atten(ADC6_TEST_CHANNEL,ADC_ATTEN_11db);


    while(1){
    	printf("Phan tram do am probe :%d",100-(adc1_get_raw (ADC3_TEST_CHANNEL)*100-460*100)/(1036-460)); // n*100 / l-n
    	       printf(" %% \n ");
    	        printf("Gia tri Analog %d\n",adc1_get_raw (ADC3_TEST_CHANNEL));
    	        printf("-------------------------------------------------------------------------------------------- \n\n\n\n");
    	      ///  printf("------------------- \n");
    	     //  printf("Phan tram do am chong ri :%d",100-(adc1_get_raw (ADC2_TEST_CHANNEL)*100-1000*100)/(2700-1000)); // n*100 / l-n
    	    //  printf(" %% \n ");
    	     // printf("Gia tri Anaglog: %d\n",adc1_get_raw (ADC2_TEST_CHANNEL));
    	    //  printf("-------------------------------------------------------------------------------------------- \n\n\n\n");
         vTaskDelay(3000/portTICK_PERIOD_MS);

}
}

void app_main(void)
{
    // Set the LEDC peripheral configuration
    example_ledc_init();
    // Set duty to 50%
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY));
    // Update duty to apply the new value
ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
   xTaskCreate(adc1task, "adc1task", 1024*3, NULL, 10, NULL);
}

