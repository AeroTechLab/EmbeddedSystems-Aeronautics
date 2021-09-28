# Passa-ou-Repassa

## Quick description

This project is about the infrastructure of a television-like gameshow where there is a question and each participant/team must be the first to hit their button in order to answer the question asked.

## Scope

### What the system must have:
- More than one button (one for each participant/team)
- Some visual indication of the "GO!" to the participants/teams so they know that it is the time to smash the button

### What the system must do:
- Indicate visually the start trigger (the "GO!")
- Indicate visually the first button (participant/team) that was smashed
- Must NOT have a computer connected to the embedded system when it is in use
  - But, to get information from the embedded system after its usage, a computer may be used.


### Optionals (plus to the project):
- Sound indication of the "GO!" trigger
- Before the start of the game, allow the choice of the trigger type. Some ideas of trigger types:
  1. A binary indicator: there is nothing then... suddenly... **GO!**
  2. A count-down trigger: **ready... set... GO!**
- Some kind of indication of which participant/team pressed the button before the "GO!" (jump the gun indication - "*queimou a largada*")
- The delay time between the "GO!" and the button press for each participant/group
- Visual indication for each of the optionals above
- Save interesting data (like the time delay for each participant/team) to a SD card, so there is no need to ever connect a computer to the embedded system.

### Example of Architecture description

![Image of Architecture]( https://github.com/gcaurin/EmbeddedSystems-Aeronautics/blob/2021.2/projects-descriptions/Arquitetura.jpg)
- This version was presented on the September 27th to serve as reference for the student projects
- Up to now,  we have the following IO requirements for the GPIO (still need to verify availability on the Viola Base Board
  1. 3 Output  - push buttons
  2. 3 Input  - leds / sign lamps
  3. One display output connection
