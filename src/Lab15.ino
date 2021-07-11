/*
 * Project Lab15
 * Description:
 * Author:
 * Date:
 */
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
os_thread_t thread1;
os_thread_t thread2;
os_thread_t thread3;
os_mutex_t mutex;
uint16_t count = 0;  // num of transitions
uint16_t ranNum;
void myThread1(void *args) {
  while (1) { // we must NEVER return from this function / thread
    // your code here
    // ran num every second
    ranNum = rand() * 10;
    
    WITH_LOCK(Serial) {
      Serial.println(ranNum);
      
    }
    delay(1000);
  }
}
void myThread2(void *args) {
  while (1) { // we must NEVER return from this function / thread
    // your code here
    // counts every half second
    count++;
    WITH_LOCK(Serial) {
      // your serial port code code here
      Serial.println(count);
      
    }
    delay(500);
    
    
  }
}
void myThread3(void *args) {
  while (1) { // we must NEVER return from this function / thread
    // your serial port code code here
    //  flashes 4 times second
      delay(125);
      digitalWrite(D7,HIGH);
      delay(125);
      digitalWrite(D7,LOW);
      
      
    
  }
}

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(D7,OUTPUT); //led
  os_thread_create(&thread1, "thread1", OS_THREAD_PRIORITY_DEFAULT, myThread1, NULL, 1024);
  os_thread_create(&thread2, "thread2", OS_THREAD_PRIORITY_DEFAULT, myThread2, NULL, 1024);
  os_thread_create(&thread3, "thread3", OS_THREAD_PRIORITY_DEFAULT, myThread3, NULL, 1024);
  os_mutex_create(&mutex);
  
  Serial.begin(9600); 
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  // in loop or some other code, before you want to do something with exclusive access call
  os_mutex_lock(mutex);
  // do your important stuff
  os_mutex_unlock(mutex);
}