class Metronome
{
private:
  uint8_t cTICK_PIN;
  uint16_t bpm = 100;
  bool running = false;
  uint32_t started_at = 0;
  uint32_t interval = 0;
  uint32_t dotted_interval = 0;
  uint32_t next_click = 0;

  uint16_t accent_click = 2600; // Hz
  uint16_t normal_click = accent_click / 2; // Hz
  uint8_t time_signature = 4; // = 4/4; 3 = 3/4
  uint16_t sig[4] = {accent_click, normal_click, normal_click, normal_click};
  uint8_t idx = 0;

public:
  Metronome(uint8_t tick_pin):
    cTICK_PIN(tick_pin) {}

  uint16_t bpm_to_interval()
  {
    uint16_t per_second = (60.0 / bpm) * 1000; // ms
    dotted_interval = per_second * 1.5;
    return per_second;
  }

  void setTimeSignature( uint8_t ts) { time_signature = ts; }
  void setBPM( uint16_t _bpm ) { bpm = _bpm; }
  uint16_t getBPM() { return bpm; }
  bool isRunning() { return running; }
  void stop()
  {
    if( running == true )
    {
      Serial.println("Metronome stopped");
      running = false;
    }
  }

  void start()
  {
    running = true;
    interval = bpm_to_interval();
    started_at = millis();
    next_click = started_at + interval;
    Serial.println("Metronome start, " + String(bpm) + " bpm, interval: " + String(interval));
  }

  void update()
  // Not using interrupts, so this function must be called very regularly in the Arduino loop() function
  {
    if( running == true )
    {
      uint32_t now = millis();
      if( now >= next_click )
      {
        next_click = now + interval;
        Serial.println("Click");
        /*
        tone(TICK_PIN, sig[idx++], 5);
        if( idx == ksig ) { idx = 0; }
        //*/
        // if( idx == 0 ) { tone(cTICK_PIN, accent_click, 5); next_click = now + dotted_interval;} // For irregular time signatures, TODO: 3/4 == 7/8
        if( idx == 0 ) { tone(cTICK_PIN, accent_click, 5); }
        else           { tone(cTICK_PIN, normal_click, 5); }
        idx++;
        if( idx == time_signature ) { idx = 0; }
        //*/
      }
    }
  }

  void incBPM( uint16_t val )
  {
    bpm += val;
    if( bpm > 300 ) { bpm = 300; }
    interval = bpm_to_interval();
    Serial.println("Metronome change, " + String(bpm) + " bpm, interval: " + String(interval));
  }

  void decBPM( uint16_t val )
  {
    if( bpm < val ) { bpm = 0; }
    else { bpm -= val; }
    interval = bpm_to_interval();
    Serial.println("Metronome change, " + String(bpm) + " bpm, interval: " + String(interval));
  }
};
