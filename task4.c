#include <FreeRTOS.h>
#include <task.h>

TaskHandle_t core1TaskHandle;

volatile uint32_t core1Counter = 0;

// Define the idle task hook for Core 0
void vApplicationIdleHook(void) {

    // Calculate CPU utilization for Core 0
    uint32_t totalRunTime = vTaskGetRunTimeCounter(NULL);
    float utilization = (1.0 - (float)totalRunTime / (float)configTICK_RATE_HZ) * 100.0;
    Serial.printf("Core 0 CPU Utilization: %.2f%%\n", utilization);
}

// Define the idle task hook for Core 1
void vApplicationIdleHookCore1(void) {
    // Calculate CPU utilization for Core 1
    uint32_t totalRunTime = vTaskGetRunTimeCounter(NULL);
    float utilization = (1.0 - (float)totalRunTime / (float)configTICK_RATE_HZ) * 100.0;
    Serial.printf("Core 1 CPU Utilization: %.2f%%\n", utilization);
}

// Task running on Core 1
void core1Task(void *pvParameters) {
    for (;;) {
        core1Counter++;
        Serial.printf("Core 1 Work: Counter = %u\n", core1Counter);
        vTaskDelay(pdMS_TO_TICKS(1000));  // Chờ 1000 milliseconds
    }
}

void setup() {
    Serial.begin(115200);

    // Create a task on Core 1
    xTaskCreatePinnedToCore(core1Task, "Core1Task", 1000, NULL, 1, &core1TaskHandle, 1);

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();
}

void loop() {
    // This loop can remain empty as tasks run under FreeRTOS
}
