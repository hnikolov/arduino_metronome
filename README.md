# arduino_metronome
Simple Metronome and Tabata classes in C++ for arduino implementation

**Description**
- Use the arduino tone() function to output the ticks and tocks on a pin
- Ticks and tocks are created by short (5ms) signals (~1-3KHz) with a standard buzzer module
- No interrupts are used. Instead, an update() function is provided that needs to be called regularly in the arduino loop() function
- The provided interfaces should enable an easy integration in other projects
