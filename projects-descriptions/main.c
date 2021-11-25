// -------------------------------------------------------------|
// Code developed for Toradex hardware
//   +  Computer on Module COM - Colibri VF50
//   +  Base Board  - Viola
// -------------------------------------------------------------|
// State Machine Code adapted from: 
//              https://www.embarcados.com.br/maquina-de-estado/
//              Original   - Pedro Bertoleti

// -------------------------------------------------------------|

#include <stdlib.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>


//Global variables:
void (*PointerToFunction)(); // Pointer to the functions (states) of the state machine. 
                             // It points to the function that must run on the state machine
int Player1_Points;          // Collects the points from Player 1 for display
int Player2_Points;          // Collects the points from Player 2 for display
int fd_start_button;         // start_button_file_descriptor

struct pollfd poll_gpio;



//prototypes:
void Starting_State(void);       //function representing the initial state of the state machine
void Game_Running_State(void);   //function representing the state after Play Push-Button is pressed
void Player_1_Score_State(void); //function representing the state after Push-Button 1 is pressed
void Player_2_Score_State(void); //function representing the state after Push-Button 2 is pressed
void TurnGoSignON(void);
void TurnGoSignOFF(void);

//Initial state. Only changes when the Play Button is pressed - Prototype Letter 'p'
void Starting_State(void)
{
  // char ReadButton;
 
  char value;
  printf("Ready? Lets Play? Press the Start Button to play. You are at Starting_State \n"); 
  printf("*******************************************************************\n");
  printf("*** Player 1 ******   %d   points **********************************\n", Player1_Points);
  printf("*** Player 2 ******   %d   points **********************************\n", Player2_Points);
  printf("*******************************************************************\n\n");
  printf("- Power On  \n");    //needs to be replaced by an GPIO output Power Led ON
  printf("- Play Off  \n");    //needs to be replaced by an GPIO output Play Led OFF
  printf("- Player 1 Score Off  \n"); //needs to be replaced by an GPIO output Player 1 Led OFF
  printf("- Player 2 Score Off  \n"); //needs to be replaced by an GPIO output Player 2 Led OFF

  //reads the keyboard - prototype
 
  poll(&poll_gpio, 1, -1); // discard first IRQ
  read(fd_start_button, &value, 1);
 
  // wait for interrupt
  while(1){
      poll(&poll_gpio, 1, -1);
      if((poll_gpio.revents & POLLPRI) == POLLPRI){
            lseek(fd_start_button, 0, SEEK_SET);
            read(fd_start_button, &value, 1);
            printf("Interrupt GPIO val: %c\n", value); 
            break;
      }
  }

  //fflush(stdin); //cleans keyboard buffer
  //__fpurge(stdin);
  //ReadButton = getchar();
  //scanf("%c", &ReadButton);
  
  if (value == '0')
    PointerToFunction = Game_Running_State;
  else 
    printf("\n- Press the Start Button to play. You are at Starting_State \n"); 
}

//Switch to the next state if key pressed is 'b'. Otherwise, return to initial state (waits for letter 'p')
void Game_Running_State(void)
{
  int fd;
  char ReadButton;
  printf("                       Game On   \n");
  printf("- Listen to the question and Press the Button if you know the answer \n");
  printf("- Power On  \n");    
  // Turn GO-Sign ON
  TurnGoSignON();
  // ----------------------------------------------------------|
  printf("- Play On  \n");    //needs to be replaced by an GPIO output Play Led OFF
  printf("- Player 1 Score Off  \n"); //needs to be replaced by an GPIO output Player 1 Led OFF
  printf("- Player 2 Score Off  \n"); //needs to be replaced by an GPIO output Player 2 Led OFF

  //reads the pressed key on th keyboard - prototype
  //needs to be replaced by an GPIO input
  __fpurge(stdin);
  ReadButton = getchar();
 
  printf("You entered %c  \n", ReadButton);

  if (ReadButton == 'b')
    PointerToFunction = Player_1_Score_State;
  else if (ReadButton == 'c')
    PointerToFunction = Player_2_Score_State;
  else
  {
    printf("\n- Expected char: b or c. Readen char: %c.Game goes on \n",ReadButton);
  }
}

//Switch to the next state if key pressed is 'b'. Otherwise, stay in Game_Running_State (waits for letters 'b' or 'c')
void Player_1_Score_State(void)
{
  char ReadButton;
  printf("- Point for player 1  \n");
  printf("- Power On  \n");    //needs to be replaced by an GPIO output Power Led ON
  printf("- Play Off  \n");    //needs to be replaced by an GPIO output Play Led OFF
  printf("- Player 1 Score On  \n"); //needs to be replaced by an GPIO output Player 1 Led ON
  printf("- Player 2 Score Off  \n"); //needs to be replaced by an GPIO output Player 2 Led OFF
  printf("- Press RESET to restart the game \n"); //needs to be replaced by an GPIO input push button
  //reads the pressed key on th keyboard - prototype

  __fpurge(stdin);
  ReadButton = getchar();

  printf("You entered %c  \n", ReadButton);

  if (ReadButton == 'r')
    PointerToFunction = Starting_State;
  else
  {
    printf("\n- Expected char: r. Readen char: %c. Press reset to go back to the initial state \n",ReadButton);
  } 
  Player1_Points++;
}

//Validate the state if key pressed is 'd'. Otherwise, return to initial state (waits for letter 'p')
void Player_2_Score_State(void)
{
  char ReadButton;
  printf("- Point for player 2  \n");
  printf("- Power On  \n");    //needs to be replaced by an GPIO output Power Led ON
  printf("- Play Off  \n");    //needs to be replaced by an GPIO output Play Led OFF
  printf("- Player 1 Score Off  \n"); //needs to be replaced by an GPIO output Player 1 Led OFF
  printf("- Player 2 Score On  \n"); //needs to be replaced by an GPIO output Player 2 Led ON
  printf("- Press RESET to restart the game \n"); //needs to be replaced by an GPIO input push button
  //reads the pressed key on the keyboard - prototype
  __fpurge(stdin);
  ReadButton = getchar();
  
  printf("You entered %c  \n", ReadButton);

  if (ReadButton == 'r')
    PointerToFunction = Starting_State;
  else
  {
    printf("\n- Expected char: r. Readen char: %c. Press reset to go back to the initial state \n",ReadButton);
  } 
  Player2_Points++;
}

void TurnGoSignON(void)
{
  int fd;
  // Turn GO-Sign ON
  fd = open("/sys/class/gpio/gpio89/value", O_WRONLY | O_SYNC);
  write(fd, '0', 1);
  close(fd);
  // ----------------------------------------------------------|
}

void TurnGoSignOFF(void)
{
  int fd;
  // Turn GO-Sign ON
  fd = open("/sys/class/gpio/gpio89/value", O_WRONLY | O_SYNC);
  write(fd, '0', 1);
  close(fd);
  // ----------------------------------------------------------|
}

int main(int argc, char *argv[])
{
  PointerToFunction = Starting_State; //points to the initial state. 
                                      //Never forget to inform the initial state 
                                      //(otherwise, in this specific case, fatal error may occur/ hard fault).
  Player1_Points = 0;
  Player2_Points = 0;
  int fd;


  //------------------------------------------------------|
  // CREATE GO-Sign in 3 steps  OUTPUT SIGNAL
  // Step 1 - expose hardware to user space
  // Linux GPIO 89 corresponds to Viola Pin X09.8
  // export GPIO
  fd = open("/sys/class/gpio/export", O_WRONLY);
  write(fd, "89", 2);
  close(fd);
  // Step 2 - Configure GPIO as output
  fd = open("/sys/class/gpio/gpio89/direction", O_WRONLY);
  write(fd, "out", 3);
  close(fd);
  // Step 3 - Initiate GO-Sign off
  TurnGoSignOFF();
  //------------------------------------------------------|

  //------------------------------------------------------|
  // CREATE Start Button in 3 steps  INPUT SIGNAL
  // Step 1 - expose hardware to user space
  // Linux GPIO 88 corresponds to Viola Pin X09.10

    poll_gpio.events = POLLPRI;
    // export GPIO
    fd_start_button = open("/sys/class/gpio/export", O_WRONLY);
    write(fd_start_button, "88", 2);
    close(fd_start_button);
 
    // configure as input
    fd_start_button = open("/sys/class/gpio/gpio88/direction", O_WRONLY);
    write(fd_start_button, "in", 2);
    close(fd_start_button);

    // read GPIO once
    // configure interrupt
    fd_start_button = open("/sys/class/gpio/gpio88/edge", O_WRONLY);
    write(fd_start_button, "rising", 6); // configure as rising edge
    close(fd_start_button);
 
    // open value file
    fd_start_button = open("/sys/class/gpio/gpio88/value", O_RDONLY);
    poll_gpio.fd = fd_start_button;

  //------------------------------------------------------|

  printf("\n                   Welcome            \n\n");
  while(1)
  {
    (*PointerToFunction)();  //calls a function pointed out by the pointer to function (thus, calls the current state)
  }
  system("PAUSE"); 
  return 0;
}