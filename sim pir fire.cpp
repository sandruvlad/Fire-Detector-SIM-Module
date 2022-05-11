 #include <SoftwareSerial.h>
SoftwareSerial sim800L(2, 3);// SIM Module pins RX and TX

int Flame_sensor = 5;        // IR sensor Pin
int Flame_detected = HIGH;   // The sensor state is HIGH
int sensor = 6;              // Pir Sensor Pin D6
int state = LOW;             // default state is no movement
int val = 0;                 // variable to store the sensor status (value)

const String Phone = "Phone Number";  // Phone number to send the messages to

void setup() {                      // Starting setup of the device
  Serial.begin(9600);                // Serial begin at 9600 rate
  sim800L.begin(9600);                //SIM begin at 9600 rate
  pinMode(sensor, INPUT);             // Assign the pins as an input for the tow variables
  pinMode(Flame_sensor, INPUT);
  Serial.println("Accessing the SIM800L Module"); // serial print the welcome screen
  sim800L.println("AT+CMGF=1");       // the module will accept both sms and call fuctions
}

void loop() {                           // Starting the loop
  while(sim800L.available()){           // accessing the sim module
  Serial.println(sim800L.readString());     // read and store the message
    }
  {
  Flame_detected = digitalRead(Flame_sensor);     // Checking the fire sensor
  if (Flame_detected == HIGH) {                   // If the state is high then send message
    Serial.println("Fire detected, Check other Parameters Urgently!");
    sending_message();                            // send message
  }
  else
  {
    digitalWrite(Flame_detected, LOW);          // else change the state to low
    }
  {
    val = digitalRead(sensor);                 // read pir sensor 
  if (val == HIGH) {                          // if the sensor is high    
    if (state == LOW) {                       // state is low
      Serial.println(" Attention! Person detected! Check Device For Tampering!");     // serial print message
      state = HIGH;                         // change the state to high
      sending_message1();                   // send message
    }
  } 
  else {
        state = LOW;     }                    // change state to low
    }
}  
 delay (500);               // delay
}
void sending_message()          // function of the first message for fire
{
  if(Phone != ""){            //  if the phone number is any
    Serial.print("Phone: ");    //serial print message
    send_message("Alert: Fire detected, Check other Parameters Urgently!", Phone);    // send message to phone
  }
}
void sending_message1()         // function of the secod message for movement
{
  if (Phone != ""){           // check the phone number
    Serial.print("Phone: ");    // serial print the message
    send_message(" Attention! Person detected! Check Device For Tampering!", Phone);    //send the message to phone
  }
}
void send_message(String text, String phone)    // standard settings from the documentation of the SIM module
{
    Serial.println("Sending Message....");          // serial print message that the message will be sent to device
    //delay(500);
    sim800L.print("AT+CMGF=1\r");
    //delay(1000);
    sim800L.print("AT+CMGS=\""+phone+"\"\r");
    delay(1000);
    sim800L.print(text);
    delay(500);
    sim800L.write(0x1A);
    delay(8000);
}
