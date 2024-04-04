#define TICK_PIN 17

#include "metronome.h"
#include "tabata.h"
#include "tabata_metronome.h"

Metronome metronome = Metronome(TICK_PIN);

Tabata tabata = Tabata(8, 5, TICK_PIN);
//Tabata tabata = Tabata();

Tabata_Metronome tm = Tabata_Metronome(20, 10, TICK_PIN);

uint32_t begin_time;

void test_metronome()
{
  while( 1 )
  {
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
        return;
      }
    }
  }
}

void test_tabata()
{
  while( 1 )
  {
    tabata.update();
    delay(100);

    if( tabata.isRunning() )
    {
      if( millis() - begin_time > 26000 )
      {
        tabata.stop();
      }
    }
  }
}

void test_tabata_metronome()
{
  while( 1 )
  {
    tm.update();
    delay(100);

    if( tm.isRunning() )
    {
      if((millis() - begin_time > 26000) && (millis() - begin_time < 26100))
      {
        tm.enableMetronome(true);
      }

      if( millis() - begin_time >= 50000 )
      {
        tm.stop();
        return;
      }
    }
  }
}

void setup()
{
	delay(2000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Tabata/Metronome");

  begin_time = millis();

  ////tabata.setPracticeTime(20);
  ////tabata.setRestTime(10);
  //tabata.start();
  //test_tabata();

  //metronome.setBPM(60);
  ////metronome.decBPM(20);
  //metronome.start();
  //test_metronome();

  tm.setPracticeTime(8);
  tm.setRestTime(5);
  tm.enableMetronome(false);
  tm.start();
  test_tabata_metronome();
}

void loop()
{
}
