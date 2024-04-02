#define TICK_PIN 17

#include "metronome.h"
#include "tabata.h"

Metronome metronome = Metronome(TICK_PIN);

Tabata tabata = Tabata(8, 3);
//Tabata tabata = Tabata();

uint32_t begin_time;

void setup()
{
/*  
  pinMode(TICK_PIN, OUTPUT);
  for(int i = 0; i < 50; i++)
  {
    // for a tick-tock sound
    // For more efficient output, use PWM pins with analogWriteFrequency().
    tone(TICK_PIN, 2600, 5);
    delay(500);
    tone(TICK_PIN, 1300, 5);
    delay(500);
    tone(TICK_PIN, 1300, 5);
    delay(500);
    tone(TICK_PIN, 1300, 5);
    delay(500);    
  }
//*/
	delay(2000);
  Serial.begin(115200); // Debug via USB-Serial (Teensy's programming interface, where 250000 is maximum speed)
  Serial.println();
  Serial.println("Tabata/Metronome");

  //tabata.setPracticeTime(20);
  //tabata.setRestTime(10);
  //tabata.start();

  metronome.setBPM(60);
  //metronome.decBPM(20);
  metronome.start();
  begin_time = millis();
}
  
void loop()
{
/*
  tabata.update();
  delay(100);

  if( tabata.isRunning() )
  {
    if( millis() - begin_time > 22000 )
    {
      tabata.stop();
    }
  }
//*/
  metronome.update();
  delay(100);

  if( metronome.isRunning() )
  {
    if( millis() - begin_time > 6000 && millis() - begin_time < 6100)
    {
      metronome.incBPM(80);
      metronome.setTimeSignature(3); // 3/4
    }
    if( millis() - begin_time > 24000 )
    {
      metronome.stop();
    }
  }
//*
}
