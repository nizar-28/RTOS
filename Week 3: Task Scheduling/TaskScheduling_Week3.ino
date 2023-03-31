//Use 1 core
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

//Print string
const char msg[] = "Testing one two three. ";

//Task handles
static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;

//*****************************************************

//Tasks

//Print to Serial terminal with lower priority
void startTask1(void *parameter){

  //Count character numbers in string
  int msg_len = strlen(msg);

  //Print string to the terminal
  while(1) {
    Serial.println();
    for(int i = 0; i < msg_len; i++) {
      Serial.print(msg[i]);
    }
    Serial.println();
    vTaskDelay(1000/portTICK_PERIOD_MS);
    
  }
}

//Print to Serial terminal with higher priority
void startTask2(void *parameter) {
  while(1) {
    Serial.print('*');
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

//******************************************************
//Main(runs as own task with priority 1 core 1)

void setup() {

  //Configure Serial (slow to observe)
  Serial.begin(300);

  //Wait to start (not to miss Serial output)
  vTaskDelay(1000/portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---RTOS Task Demo---");

  //Self priority print
  Serial.print("Setup and loop task running on core ");
  Serial.print(xPortGetCoreID());
  Serial.print(" with priority ");
  Serial.println(uxTaskPriorityGet(NULL));

  //Task to forever run
  xTaskCreatePinnedToCore(startTask1,
  "Task 1",
  1024,
  NULL,
  1,
  &task_1,
  app_cpu);

  //Task to run once with higher priority
  xTaskCreatePinnedToCore(startTask2,
  "Task 2",
  1024,
  NULL,
  2,
  &task_2,
  app_cpu);

}

void loop() {

  //Suspend higher priority task for intervals
  for(int i = 0; i < 3; i++) {
    vTaskSuspend(task_2);
    vTaskDelay(2000/portTICK_PERIOD_MS);
    vTaskResume(task_2);
    vTaskDelay(2000/portTICK_PERIOD_MS);
  }

//Delete lower priority task
if(task_1 !=NULL) {
  vTaskDelete(task_1);
  task_1 = NULL;
 }
}
