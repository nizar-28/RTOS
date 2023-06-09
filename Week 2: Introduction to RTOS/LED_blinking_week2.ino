//Use 1 core
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

//Using built-in LED
static const int led_pin = 2;

//Blinking LED
void toggleLED(void *parameter){
  while(1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(500/portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(500/portTICK_PERIOD_MS);
  }
}
void setup() {

  //Configure pin as output
  pinMode(led_pin, OUTPUT);

  //Task to run forever
  xTaskCreatePinnedToCore(
    toggleLED,              //Function to be called
    "Toggle LED",           //Task name
    1024,                   //Stack size
    NULL,                   //Parameter to pass to function
    1,                      //Task priority (0-lowest, 24 highest)
    NULL,                   //Task Handle
    app_cpu);                 //Run on 1 core for demo

}

void loop() {

}
