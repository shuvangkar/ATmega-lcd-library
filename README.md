# LCD Library for Microcontroller

I am wokring with the atmega family microcontroller for more than 5 years. Most of the time I used other people library for printing somethin on LCD display. In my last project, I used Arduino LiquidCrystal Library. It has many drawbacks. Among these what I faced was that the LCD was not working with interrut(adc auto running mode).

The LCD library I have used so far has few drawbacks
- Most of the libraries are slow enough
- These libraries are good for project and drastically bad for production environment 
- These LCD library uses long delay between commands. This delay() could have easily avoided using the [Busy flag]()
