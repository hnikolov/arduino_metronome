class Tabata
{
private:
  uint16_t practice_time;
  uint16_t rest_time;
  uint16_t practice_cnt = 0;
  uint16_t rest_cnt = 0;
  uint16_t second = 0;
  uint32_t started_at = 0;
  bool running = false;
  enum TbStates {Tb_practice, Tb_rest};
  TbStates _tbstate = Tb_practice;

public:
  Tabata(uint16_t practice_time=45, uint16_t rest_time=15):
    practice_time(practice_time * 1000), // ms
    rest_time(rest_time * 1000) {} // ms

  bool isRunning() { return running; }
  bool isPractice() { return _tbstate == Tb_practice; }
  bool isRest() { return _tbstate == Tb_rest; }
  uint16_t getPracticeCnt() { return practice_cnt; }
  uint16_t getRestCnt() { return rest_cnt; }

  void setPracticeTime( uint16_t seconds ) { practice_time = seconds * 1000;  }
  void setRestTime( uint16_t seconds )     { rest_time = seconds * 1000;      }
  void incPracticeTime( uint16_t seconds ) { practice_time += seconds * 1000; }
  void incRestTime( uint16_t seconds )     { rest_time += seconds * 1000;     }

  void decPracticeTime( uint16_t seconds )
  {
    if( practice_time < seconds * 1000 ) { practice_time = 0; }
    else { practice_time -= seconds * 1000; }
  }
  
  void decRestTime( uint16_t seconds )
  {
    if( rest_time < seconds * 1000 ) { rest_time = 0; }
    else { rest_time -= seconds * 1000; }
  }

  void start()
  {
    _tbstate = Tb_practice;
    practice_cnt = 0;
    rest_cnt = rest_time / 1000; // seconds
    started_at = millis();
    second = started_at;
    running = true;
    Serial.println("Tabata start");
  }
  
  void stop()
  {
    if( running == true )
    {
      Serial.println("Tabata stopped");
      _tbstate = Tb_practice;
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

            if( now - started_at >= practice_time )
            {
              started_at = millis();
              _tbstate = Tb_rest;
              rest_cnt = (rest_time-1) / 1000; // seconds
              Serial.println("Tabata: Rest");
            }
          }
        break;
      
        case Tb_rest:
          if( now - second >= 1000 ) // 1 second 
          {
            Serial.println("Rest: " + String(rest_cnt));
            rest_cnt--;
            second = now;
          
            if( now - started_at >= rest_time )
            {
              started_at = millis();
              _tbstate = Tb_practice;
              practice_cnt = 0;
              Serial.println("Tabata: Practice");
            }
          }
        break;

        default:
        break;
      }
    }
  }
};
