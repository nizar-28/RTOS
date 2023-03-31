//Use only core 1 for demo
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

//Perform some task
void testTask(void *parameter) {
  while(1) {
    int a = 1;
    int b[100];

    //Do some stuff with array so that it's not optimized out by compiler
    for (int i = 0; i < 100; i++) {
      b[i] = a + 1;
    }
    Serial.println(b[0]);
  

    //Print out remaining stack memory (words)
    Serial.print("High water mark (words): ");
    Serial.println(uxTaskGetStackHighWaterMark(NULL));

    //Print out free heap memory bytes before malloc
    Serial.print("Heap before malloc (bytes): ");
    Serial.println(xPortGetFreeHeapSize());
    int *ptr = (int*)pvPortMalloc(1024 * sizeof(int));

    //One way to prevenet heap overflow = check malloc output
    if (ptr == NULL) {
      Serial.println("Not enough heap.");
    } else {

     //Do something with memory so it's not optimized out by compiler
     for (int i = 0; i < 1024; i++) {
      ptr[i] = 3;
     }
    }

     //Print out free heap memory bytes after malloc
     Serial.print("Heap after malloc (bytes): ");
     Serial.println(xPortGetFreeHeapSize());

     //Free up allocated memory
     vPortFree(ptr);

     //Delay
     vTaskDelay(100/portTICK_PERIOD_MS);
  }
}
void setup() {

  //Customize Serial
  Serial.begin(115200);

  //Delay to start to not miss Serial output
  vTaskDelay(1000/portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---RTOS Memory Demo---");

  //Start other task
  xTaskCreatePinnedToCore(testTask,
  "Test Task",
  1500,
  NULL,
  1,
  NULL,
  app_cpu);

  //Delete the "setup and loop" task
  vTaskDelete(NULL);
}

void loop() {

}
