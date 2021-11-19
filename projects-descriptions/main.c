// -------------------------------------------------------------|
// Source     - adapted from:
//              https://www.embarcados.com.br/maquina-de-estado/
// Original   - Pedro Bertoleti
// Adapted by - Glauco Caurin
// Last change- 18/11/2021
// -------------------------------------------------------------|

#include <stdlib.h>
#include <stdio.h>
#include <stdio_ext.h>

//Global variables:
void (*PointerToFunction)(); // Pointer to the functions (states) of the state machine. 
                             // It points to the function that must run on the state machine

//prototypes:
void Starting_State(void);       //function representing the initial state of the state machine
void Game_Running_State(void);   //function representing the state after Play Push-Button is pressed
void Player_1_Score_State(void); //function representing the state after Push-Button 1 is pressed
void Player_2_Score_State(void); //function representing the state after Push-Button 2 is pressed

//Initial state. Only changes when the Play Button is pressed - Prototype Letter 'p'
void Starting_State(void)
{
  char ReadButton;
  printf("- Power On  \n");    //needs to be replaced by an GPIO output Power Led ON
  printf("- Play Off  \n");    //needs to be replaced by an GPIO output Play Led OFF
  printf("- Player 1 Score Off  \n"); //needs to be replaced by an GPIO output Player 1 Led OFF
  printf("- Player 2 Score Off  \n"); //needs to be replaced by an GPIO output Player 2 Led OFF

  //reads the keyboard - prototype
  //needs to be replaced by an GPIO input
  //fflush(stdin); //cleans keyboard buffer
  __fpurge(stdin);
  ReadButton = getchar();
  //scanf("%c", &ReadButton);

  if (ReadButton == 'p')
    PointerToFunction = Game_Running_State;
  else 
    printf("\n- Press p to play. You are at Starting_State \n"); 
}

//Switch to the next state if key pressed is 'b'. Otherwise, return to initial state (waits for letter 'p')
void Game_Running_State(void)
{
  char ReadButton;
  printf("- Game On   \n");
  printf("- Listen to the question and Press the Button if you know the answer \n");
  printf("- Power On  \n");    //needs to be replaced by an GPIO output Power Led ON
  printf("- Play On  \n");    //needs to be replaced by an GPIO output Play Led OFF
  printf("- Player 1 Score Off  \n"); //needs to be replaced by an GPIO output Player 1 Led OFF
  printf("- Player 2 Score Off  \n"); //needs to be replaced by an GPIO output Player 2 Led OFF

  //reads the pressed key on th keyboard - prototype
  //needs to be replaced by an GPIO input
  //fflush(stdin); //cleans keyboard buffer
  __fpurge(stdin);
  ReadButton = getchar();
  //scanf("%c", &ReadButton);
  printf("You entered %c  \n", ReadButton);

  if (ReadButton == 'b')
    PointerToFunction = Player_1_Score_State;
  else
  {
    printf("\n- Expected char: b. Readen char: %c. Back to the initial state \n",ReadButton);
    PointerToFunction = Starting_State;
  }
}

//Switch to the next state if key pressed is 'c'. Otherwise, return to initial state (waits for letter 'p')
void Player_1_Score_State(void)
{
  char ReadButton;
  //reads the pressed key on th keyboard - prototype
  //fflush(stdin); //cleans keyboard buffer
  __fpurge(stdin);
  ReadButton = getchar();
  //scanf("%c", &ReadButton);
  printf("You entered %c  \n", ReadButton);

  if (ReadButton == 'c')
    PointerToFunction = Player_2_Score_State;
  else
  {
    printf("\n- Expected char: c. Readen char: %c. Back to the initial state \n",ReadButton);
    PointerToFunction = Starting_State;
  } 
}

//Validate the state if key pressed is 'd'. Otherwise, return to initial state (waits for letter 'p')
void Player_2_Score_State(void)
{
  char ReadButton;
  //reads the pressed key on th keyboard - prototype
  //fflush(stdin); //cleans keyboard buffer
  __fpurge(stdin);
  ReadButton = getchar();
  //scanf("%c", &ReadButton);
  
  printf("You entered %c  \n", ReadButton);

  if (ReadButton != 'd')
    printf("\n- Expected char: d. Readen char: %c. Back to the initial state\n",ReadButton);
  else
    printf("OK\n\n"); //the sequence of input letter is ok. Rights "OK" in the screen and goes back to initial state

  PointerToFunction = Starting_State;
}


int main(int argc, char *argv[])
{
  PointerToFunction = Starting_State; //points to the initial state. 
                                      //Never forget to inform the initial state 
                                      //(otherwise, in this specific case, fatal error may occur/ hard fault).
  printf("\n- Welcome - Ready - Lets Play ? - Press P to start \n");
  while(1)
  {
    (*PointerToFunction)();  //calls a function pointed out by the pointer to function (thus, calls the current state)
  }
  system("PAUSE"); 
  return 0;
}