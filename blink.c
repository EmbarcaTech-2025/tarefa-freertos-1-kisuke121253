#include "FreeRTOS.h"
#include "task.h"

#include <stdio.h>
#include "pico/stdlib.h"

#define PIN_LED_RED 13
#define PIN_LED_GREEN 11
#define PIN_LED_BLUE 12
#define PIN_BUTTON_A 5
#define PIN_BUTTON_B 6
#define PIN_BUZZER_1 21
#define PIN_BUZZER_2 10

// Handles das tarefas pra usar vTaskSuspend e vTaskResume
TaskHandle_t ledTaskHandle = NULL;
TaskHandle_t buzzerTaskHandle = NULL;

// Tarefa que controla o LED RGB
void led_task(void *pv) {
    uint colors[3] = {PIN_LED_RED, PIN_LED_GREEN, PIN_LED_BLUE};

    // configura pinos como saída
    for(int i = 0; i < 3; i++) {
        gpio_init(colors[i]);
        gpio_set_dir(colors[i], GPIO_OUT);
    }
    int idx = 0;

    while (true) {
        // apaga todos primeiro
        for(int i = 0; i < 3; i++) {
            gpio_put(colors[i], 0);
        }
        // acende o atual
        gpio_put(colors[idx], 1);
        idx = (idx + 1) % 3;

        vTaskDelay(pdMS_TO_TICKS(500)); // 500ms
    }
}

// Tarefa que controla o buzzer
void buzzer_task(void *pv) {
    // configura pinos como saída
    gpio_init(PIN_BUZZER_1);
    gpio_set_dir(PIN_BUZZER_1, GPIO_OUT);
    gpio_init(PIN_BUZZER_2);
    gpio_set_dir(PIN_BUZZER_2, GPIO_OUT);

    while (true) {
        // faz um "bipe" de 100ms
        gpio_put(PIN_BUZZER_1, 1);
        gpio_put(PIN_BUZZER_2, 1);
        vTaskDelay(pdMS_TO_TICKS(100)); 
        gpio_put(PIN_BUZZER_1, 0);
        gpio_put(PIN_BUZZER_2, 0);
        vTaskDelay(pdMS_TO_TICKS(1000)); // 1s de intervalo
    }
}

// Tarefa que verifica o Botão A para pausar/retomar o LED
void buttonA_task(void *pvParameters) {
    gpio_init(PIN_BUTTON_A);
    gpio_set_dir(PIN_BUTTON_A, GPIO_IN);
    gpio_pull_up(PIN_BUTTON_A);
    for(;;) {
        if (gpio_get(PIN_BUTTON_A) == 0) { // Botão A apertado
            if (eTaskGetState(ledTaskHandle) == eSuspended) {
                vTaskResume(ledTaskHandle);
            } else {
                vTaskSuspend(ledTaskHandle);
            }
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

// Tarefa que verifica o Botão B para pausar/retomar o Buzzer
void buttonB_task(void *pvParameters) {
    gpio_init(PIN_BUTTON_B);
    gpio_set_dir(PIN_BUTTON_B, GPIO_IN);
    gpio_pull_up(PIN_BUTTON_B);
    for(;;) {
        if (gpio_get(PIN_BUTTON_B) == 0) { // Botão B apertado
            if (eTaskGetState(buzzerTaskHandle) == eSuspended) {
                vTaskResume(buzzerTaskHandle);
            } else {
                vTaskSuspend(buzzerTaskHandle);
            }
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

int main()
{
    stdio_init_all();

    xTaskCreate(led_task, "LED_Task", 256, NULL, 1, &ledTaskHandle);
    xTaskCreate(buzzer_task, "Buzzer_Task", 256, NULL, 1, &buzzerTaskHandle);
    xTaskCreate(buttonA_task, "BtnA_Task", 256, NULL, 2, NULL);
    xTaskCreate(buttonB_task, "BtnB_Task", 256, NULL, 2, NULL);

    vTaskStartScheduler();

    while (1) { }
}
