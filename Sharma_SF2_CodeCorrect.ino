//A.Sharma
//Based on photoresistor input, LED and buzzer turn on or off.
//Novemeber 2nd, 2021

//set global values
const int ledPin = 13;
const int ButtonPin = 2;
const int photoPin = A0;
int speakerPin = 10;               //the pin that buzzer is connected to
int potPosition;  
int threshold = 700;
int photoresistor = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(ledPin, OUTPUT);
pinMode(ButtonPin, INPUT);
pinMode(photoPin, INPUT);
pinMode(speakerPin, OUTPUT);
Serial.begin(9600);
}


void loop() {

  // put your main code here, to run repeatedly:
  
  // When the photoresistor senses light, the LED(s) flash, and the buzzer produces a custom siren sound
 photoresistor = analogRead(A0);   //set photoresistor to a number between 0 and 1023 based on how bright the ambient light is
  Serial.println(photoresistor);    //print the value of photoresistor in the serial monitor on the computer

  if (photoresistor > threshold) {
  //flash LEDs
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  delay(100);
  
  //buzzer goes off
  alarm();
  
  //check if button pressed
 buttonCheck();

}
}

  // When the button is pushed, the board resets in 5 sec. While the board is resetting, deactivate the alarm. (add a 5 sec. delay to deactivate the alarm) 
  // After 5 sec, the alarm should be ready to detect intruders. 
  // When there is no light, LED(s) and the buzzer are off. 
  // Repeat! 
  
 //buzzer function
  void alarm(){
    play('g', 2);    
    play('g', 1);      
    play('a', 4);
    play('c', 3); 
    if (buttonCheck() == 1){
    noTone(speakerPin);
  }
  }

//button check 
int buttonCheck(){
  if (digitalRead(ButtonPin) == LOW){
    noTone(speakerPin);
    delay(5000);
    return 1;
  }else{
    return 0;
  }
}

    
 
 
void play( char note, int beats)
{
  int numNotes = 14;  // number of notes in our note and frequency array (there are 15 values, but arrays start at 0)

  //Note: these notes are C major (there are no sharps or flats)

  //this array is used to look up the notes
  char notes[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D', 'E', 'F', 'G', 'A', 'B', ' '};
  //this array matches frequencies with each letter (e.g. the 4th note is 'f', the 4th frequency is 175)
  int frequencies[] = {131, 147, 165, 175, 196, 220, 247, 262, 294, 330, 349, 392, 440, 494, 0};

  int currentFrequency = 0;    //the frequency that we find when we look up a frequency in the arrays
  int beatLength = 150;   //the length of one beat (changing this will speed up or slow down the tempo of the song)

  //look up the frequency that corresponds to the note
  for (int i = 0; i < numNotes; i++)  // check each value in notes from 0 to 14
  {
    if (notes[i] == note)             // does the letter passed to the play function match the letter in the array?
    {
      currentFrequency = frequencies[i];   // Yes! Set the current frequency to match that note
    }
  }

  //play the frequency that matched our letter for the number of beats passed to the play function
  tone(speakerPin, currentFrequency, beats * beatLength);
  delay(beats * beatLength);  //wait for the length of the tone so that it has time to play
  delay(50);                  //a little delay between the notes makes the song sound more natural

}
