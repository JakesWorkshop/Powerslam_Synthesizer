 # Voltage to Frequency Lookup Table
 Hello, this little library will help you convert a voltage to a frequency.
 It implements the two functions voltageToFrequency() and noteToFrequency(). Both return a float.
  
 voltageToFrequency expects an int between 0 and 1023 (the output of the analogRead() Function at 10 Bit resolution)
 noteToFrequency expects an int between 0 and 60 (you can use the map() function for example)
 
 inputs outside this Range will return garbage or break something.
 
 Both functions represent 5 Octaves, starting with C1 as their first Value and ending with C6 as their last note
 this way you can use analogRead() to acheive a conversion with exactly 1Volt per octave
 (0V = C1, 1V = C2, 2V = C3, 3V = C4, 4V = C5, 5V = C6)\
 
 These Values were calculated from a polynom function, the frequencies may be off by up to 1Hz from absolute perfect values.
 But it should serve as being "close enough" for most applications.
