//Use 1 core
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

//LED rate
static const int rate1 = 500;
static const int rate2 = 300;

//Using built-in LED
static const int led_pin = 2;

//Blinking LED at rate 1
void toggleLED1(void *parameter){
  while(1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(rate1/portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(rate1/portTICK_PERIOD_MS);
  }
}


//Blinking LED at  rate 2
void toggleLED2(void *parameter){
  while(1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(rate2/portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(rate2/portTICK_PERIOD_MS);
  }
}

void setup() {

  //Configure pin as output
  pinMode(led_pin, OUTPUT);

  //Task to run forever
  xTaskCreatePinnedToCore(
    toggleLED1,              //Function to be called
    "Toggle LED 1",           //Task name
    1024,                   //Stack size
    NULL,                   //Parameter to pass to function
    1,                      //Task priority (0-lowest, 24 highest)
    NULL,                   //Task Handle
    app_cpu);                 //Run on 1 core for demo


  //Task to run forever
  xTaskCreatePinnedToCore(
    toggleLED2,              //Function to be called
    "Toggle LED 2",           //Task name
    1024,                   //Stack size
    NULL,                   //Parameter to pass to function
    1,                      //Task priority (0-lowest, 24 highest)
    NULL,                   //Task Handle
    app_cpu);                 //Run on 1 core for demo


}

void loop() {

}
