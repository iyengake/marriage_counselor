// ------------
// The marriage counsellor
// ------------

/*-------------

The key issue in most marriages is lack of communication.
The marriage counsellor uses a non-intrusive mechanism to trigger a little less conversation and a little more action to break the barrier to communication.

Step 1: Partner A pushes their designated button to indicate a "ready" state
Step 2: Partner B pushes their designated button in reponse to the "ready" state
Step 3: It's on!

It's that easy! The marriage counsellor takes care of the rest by setting mood lighting for enabling quality distraction free communication
The marriage counsellor then turns all the lights off after an hour, ensuring nothing gets in the way of a good cuddle and pillow talk

-------------*/

// First, we're going to make some variables called Keerthi and Sangeetha

// Labels for clarification

int sangeetha_led = D2;
int keerthi_led = D3;
int keerthi_button = A0;
int sangeetha_button = D0;

// GLOBAL VARIABLES
// We'll use these booleans to set state once buttons are pushed.
// Note that I thought about using the debounce function (https://www.arduino.cc/en/Tutorial/Debounce) but it isn't necessary since we want to react only one way no matter how many times the button is pushed
bool keerthi=false;
bool sangeetha=false;
long dance_interval = 200; //make the LEDs dance faster / slower by changing this interval
long dim_interval = 3600000; //1 hour
//Do the dance only once
bool one_time_dim=true;
unsigned long previousMillis = 0;

void setup() {

  // We are going to tell our device that D0 and D7 (which we named led1 and led2 respectively) are going to be output
  // (That means that we will be sending voltage to them, rather than monitoring voltage that comes from them)

  // Define initial state
  pinMode(keerthi_button, INPUT);
  pinMode(sangeetha_button, INPUT);
  pinMode(sangeetha_led, OUTPUT);
  pinMode(keerthi_led, OUTPUT);
  digitalWrite(sangeetha_led, LOW);
  digitalWrite(keerthi_led, LOW);
  
}

// Next we have the loop function, the other essential part of a microcontroller program.
// This routine gets repeated over and over, as quickly as possible and as many times as possible, after the setup function is called.
// Note: Code that blocks for too long (like more than 5 seconds), can make weird things happen (like dropping the network connection).  The built-in delay function shown below safely interleaves required background activity, so arbitrarily long delays can safely be done if you need them.

void loop() {
  
  // Detect button push for Keeerthi
  if (digitalRead(keerthi_button) == HIGH){
      keerthi=true;
  }
  // Detect button push for Sangeetha
  if (digitalRead(sangeetha_button) == HIGH){
      sangeetha=true;
  }
  
  // Set state for Keerthi & Sangeetha
  if (keerthi == true && sangeetha == true){
      
      unsigned long currentMillis = millis();
      
      //Both buttons pressed
      digitalWrite(keerthi_led, HIGH);
      digitalWrite(sangeetha_led, HIGH);
      //Wait a couple of second
      delay(2000);
      
      //Kick off a one time activity for this state
      if(one_time_dim == true){
          //Set event state to dim lights
          Spark.publish("play_music");
          Spark.publish("light_dim");
          // set this once, becuase this is where we want to 0 the time
          previousMillis = currentMillis;
          // Do a little dance
          lightDance();
          // Don't run the above commands again until we've reset the state
          one_time_dim=false;
      }
      
      // Start counting down to an hour, and continuously check how long it's been
      if (currentMillis - previousMillis >= dim_interval) {
          //Set event state to turn off lights
          Spark.publish("light_off");
          resetState();
      }
          
          
  }
  // Set state for Keerthi
  if (keerthi == true && sangeetha ==false){
      digitalWrite(sangeetha_led, LOW);
      digitalWrite(keerthi_led, HIGH);
  }
  
  // Set state for Sangeetha
  if (keerthi == false && sangeetha ==true){
      digitalWrite(sangeetha_led, HIGH);
      digitalWrite(keerthi_led, LOW);
  }
}

// Flashing LED light dance
void lightDance() {
    int i = 0;
    while (i<10){
        digitalWrite(sangeetha_led, HIGH);
        digitalWrite(keerthi_led, LOW);
        //wait
        delay(dance_interval);
        digitalWrite(sangeetha_led, LOW);
        digitalWrite(keerthi_led, HIGH);
        //wait
        delay(dance_interval);
        //increment
        i++;
    }
    
}

void resetState() {
    // Set everything back to normal
    keerthi=false;
    sangeetha=false;
    one_time_dim=true;
    digitalWrite(sangeetha_led, LOW);
    digitalWrite(keerthi_led, LOW);
    
}
