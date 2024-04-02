class Tabata
{
private:
  uint8_t cTICK_PIN;
  uint16_t accent_click = 2600; // Hz
  uint16_t normal_click = accent_click / 2; // Hz

  uint16_t practice_time;
  uint16_t rest_time;
  uint16_t practice_cnt = 0;
  uint16_t rest_cnt = 0;
  uint16_t second = 0;
  bool running = false;
  enum TbStates {Tb_practice, Tb_rest};
  TbStates _tbstate = Tb_rest;

public:
  Tabata(uint16_t practice_time=45, uint16_t rest_time=15, uint8_t tick_pin=7):
    cTICK_PIN(tick_pin),
    practice_time(practice_time), // seconds
    rest_time(rest_time) {} // seconds

  bool isRunning() { return running; }
  bool isPractice() { return _tbstate == Tb_practice; }
  bool isRest() { return _tbstate == Tb_rest; }
  uint16_t getPracticeCnt() { return practice_cnt; }
  uint16_t getRestCnt() { return rest_cnt; }

  void setPracticeTime( uint16_t seconds ) { practice_time = seconds;  }
  void setRestTime( uint16_t seconds )     { rest_time = seconds;      }
  void incPracticeTime( uint16_t seconds ) { practice_time += seconds; }
  void incRestTime( uint16_t seconds )     { rest_time += seconds;     }

  void decPracticeTime( uint16_t seconds )
  {
    if( practice_time < seconds ) { practice_time = 0; }
    else { practice_time -= seconds; }
  }
  
  void decRestTime( uint16_t seconds )
  {
    if( rest_time < seconds ) { rest_time = 0; }
    else { rest_time -= seconds; }
  }

  void start()
  {
    _tbstate = Tb_rest;
    rest_cnt = 4; // Ready: 3-2-1 count before start practicing
    second = millis();
    running = true;
    Serial.println("Tabata start");
  }
  
  void stop()
  {
    if( running == true )
    {
      Serial.println("Tabata stopped");
      running = false;
    }
  }

  void update()
  // Not using interrupts, so this function must be called very regularly in the Arduino loop() function
  {
    if( running == true )
    {
      uint32_t now = millis();
      switch( _tbstate )
      {
        case Tb_practice:
          if( now - second >= 1000 ) // 1 second 
          {
            practice_cnt++;
            second = now;
            Serial.println("Practice: " + String(practice_cnt));

            if( practice_cnt >= practice_time )
            {
              _tbstate = Tb_rest;
              rest_cnt = rest_time; // seconds
              Serial.println("Tabata: Rest");
              tone(cTICK_PIN, normal_click, 5);
            }
            else if( practice_cnt >= practice_time - 3 )
            {
              tone(cTICK_PIN, accent_click, 5);
            }
          }
        break;
      
        case Tb_rest:
          if( now - second >= 1000 ) // 1 second 
          {
            Serial.println("Rest: " + String(rest_cnt));
            rest_cnt--;
            second = now;
          
            if( rest_cnt == 0 )
            {
              _tbstate = Tb_practice;
              practice_cnt = 0;
              Serial.println("Tabata: Practice");
              tone(cTICK_PIN, accent_click, 5);
            }
            else if( rest_cnt <= 3 ) 
            {
              tone(cTICK_PIN, normal_click, 5);
            }
          }
        break;

        default:
        break;
      }
    }
  }
};
