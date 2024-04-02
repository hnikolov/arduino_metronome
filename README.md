# arduino_metronome
Simple Metronome and Tabata classes in C++ for arduino implementation

**Description**
- Uses the arduino tone() function to output the ticks and tocks on any pin
- Ticks and tocks are created by short (5ms) signals (~1-3KHz) with a standard buzzer module
  - Why? Well, radio station WWV uses a 5 ms long pulse of 1000 Hz (i.e. 5 cycles) to make the sound of a "tick"
- For more efficient output, analogWriteFrequency() on PWM pins can be used instead of tone()
- No interrupts are used. Instead, an update() function is provided that needs to be called regularly in the arduino loop() function
- The provided interfaces should enable an easy integration in other projects
