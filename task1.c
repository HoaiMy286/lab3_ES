// Prioritized Pre-emptive Scheduling with Time Slicing

#include <FreeRTOS.h>
#include <task.h>

TaskHandle_t task1Handle;
TaskHandle_t task2Handle;
TaskHandle_t task3Handle;

void task1(void *pvParameters) {
    for (;;) {
        Serial.println("Task1");
        vTaskDelay(pdMS_TO_TICKS(1000));  // Chờ 1000 milliseconds
    }
}

void task2(void *pvParameters) {
    for (;;) {
        Serial.println("Task2");
        vTaskDelay(pdMS_TO_TICKS(3000));  // Chờ 3000 milliseconds
    }
}

void task3(void *pvParameters) {
    for (;;) {
        Serial.println("Task3");
        vTaskDelay(pdMS_TO_TICKS(2000));  // Chờ 2000 milliseconds
    }
}

void setup() {
    Serial.begin(115200);

    xTaskCreate(task1, "Task1", 1000, NULL, 1, &task1Handle);
    xTaskCreate(task2, "Task2", 1000, NULL, 1, &task2Handle);
    xTaskCreate(task3, "Task3", 1000, NULL, 1, &task3Handle);

    vTaskStartScheduler();
}

void loop() {
    // Không có gì cần thực hiện trong loop vì các tasks sẽ chạy trong FreeRTOS scheduler
}
