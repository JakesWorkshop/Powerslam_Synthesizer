/* Hi, this is the code for a quite simple Trigger Sequencer.
 * This features 8 inputs, Buttons for example, and 8 digital (0V or 5V) outputs
 * Using potentiometers you can adjust the number of steps you use from 1 to 128.
 * It also features an internal Timer based Trigger LFO. 
 * You can adjust the timing from 30 to 300 BPM using the second potentiometer.
 * This code is meant for Arduino Nano or other Pin compatible 328 boards.
 * 
 * Find the project at https://github.com/JakesWorkshop/Powerslam_Synthesizer
 * Find me on Twitter: https://twitter.com/Jakesworkshop
*/

//My hardware version uses active inputs that put 5V into a pin when active and pull it low when not
//If you want to instead use a regular Button you will have to add Pulldown resistors.

#include <TimerOne.h>           //we are Using https://github.com/PaulStoffregen/TimerOne
byte data = 0b00000000;
int tracksize = 2;
bool trigger = 0;
long timing = 0;
byte track[265];                //This array needs to be at least twice as long as the number of steps
byte trackposition = 0;
bool triggermode = 0;
bool extrigger = 0;

void setup() {
  DDRD = 0b11111111;            //You can Set up what Pins by Writing to the respective Registers
  DDRB = 0b00100000;            //1 means output, 0 means input          
  DDRC = 0b00000000;
  
  //8 = in 8
  //9 = in 7
  //10 = in 6
  //11 = in 5
  //12 = in 4
  //13 = active out
  //14 = in 3
  //15 = in 2
  //16 = in 1
  //17 = trigger mode
  //18 = delete in
  //19 = hold in
  //A6 = speed in
  //A7 = size in
  
  pinMode(17, INPUT);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  Timer1.initialize(1000000);           //This sets up Timer1 to trigger a function
  Timer1.attachInterrupt(toggle);
}

//This function is triggered by the timer twice per step 
void toggle(){                      
  if (digitalRead(19)){           
    digitalWrite(13, trigger);
    trigger = !trigger;
    trackposition++;                    //If the pause button is not pressed the position on the track advances
  }
  if (trackposition > tracksize){
    trackposition = 1;                  //And is set back to 1 if the last position would be exceeded
  }
}

void loop() {                           //Controls the switching from internal to external trigger
  if (digitalRead(17) & !triggermode){
    triggermode = 1;
    pinMode(13, INPUT);                 //For external we read the status of Pin 13
    Timer1.detachInterrupt();           //and disable the Timer based intterupts
  }
  if (!digitalRead(17) & triggermode){
    triggermode = 0;
    pinMode(13, OUTPUT);                //For internal we write to Pin 13
    Timer1.attachInterrupt(toggle);
  }

  //This section deals with an external trigger
  if(triggermode){                      
    if(digitalRead(13) & !extrigger){
      if(digitalRead(19)){
        trackposition++;                //At the rising edge we advance the track
      }
      extrigger = 1;
    }
    if(!digitalRead(13) & extrigger){
      if(digitalRead(19)){
        trackposition++;                //At the falling edge we also advance the track
      }
      extrigger = 0;
    }
    if (trackposition > tracksize){
        trackposition = 1;              //Set back to 1 if the last position would be exceeded
    }
  }

  //This reads the inputs.
  data = PINC & 0b00000111;             
  data = data << 5 | PINB & 0b00011111;

  if(digitalRead(18)){                  
    track[trackposition] |= data;       //Normally the data we read would be saved to the track
  }
  else{
    track[trackposition] = 0;           //Unless the delete button is pushed
  }
  PORTD = track[trackposition];         //Finally, put out the data from the track to the outputs.

  //Potentiometers are handled here
  timing = map(analogRead(A6), 0, 1023, 100, 10);     //300bpm = 10Hz 60 bpm = 1Hz (times 10 for better math)
  tracksize = 2 << map(analogRead(A7), 0, 1023, 7, 0);//this works, don't question it
  Timer1.setPeriod(5000000/timing);                   //Finally, set the timing of Timer 1
}
/* I will readily admit 128 steps is a silly length so just change it in any way you want.
 * Keep the size of the track array in mind tho.
 * To change the maximum selectable size of the track, change the 7 in the map function that sets the tracksize
 * 7 = 128 steps    6 = 64 steps
 * 5 = 32 steps     4 = 16 steps
 * 3 = 8 steps      2 = 4 steps
 * 1 = 2 steps      0 = 1 step
*/
