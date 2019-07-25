/* This version of the shell is going to include a little game.
 * Enter "doors" to play the game. Enter your name into the prompt and then the
 * game will start. Choose the number that corresponds with the door that
 * you think *won't* give you a game over...
 * The game keeps track of your high score. Get 10 doors right to win. */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define KEY "ilovecs"

char usercommand[30];

int main() {
  int prt = 0;
  int newlines = 0;
  char prompt[30];
  char name[100];
  int high = 0;

  fprintf(stdout, "\"b\" or \"bye\" to exit the shell\n");
  fprintf(stdout, "Play the game by inputting \"doors\"!!!\n");
  while (1) {

    /* Checks if prompt should be default or if it should change to a new
     * prompt by checking the int prt.
     */
    if (prt == 0) fprintf(stdout, "%d$ ", getpid());
    else fprintf(stdout, "%d%s$ ", getpid(), prompt);

    fgets(usercommand, sizeof(usercommand), stdin);

    /* If user just enters a newline */
    if (usercommand[0] == '\n') {
      newlines++;
      if (newlines == 3) {
        fprintf(stdout, "Calm down\n");
        newlines = 0;
      }
      continue;
    } else newlines = 0;

    /* Prevent overflow of usercommand[] */
    int len = strlen(usercommand);
    if (len > 0 && usercommand[len - 1] == '\n') {
      usercommand[len -1] = '\0';
    }

    /* "b" or "bye" to exit */
    if (strcmp(usercommand, "b") == 0 || strcmp(usercommand, "bye") == 0) {
      fprintf(stdout, "GOODBYE\n");
      exit(0);
    }

    /* "defprt" to change the prompt back to default */
    if (strcmp(usercommand, "defprt") == 0) {
      prt = 0;
      continue;
    }

    /* newprt check. I first check if the 6th spot of usercommand is a space
     * and if it is I break usercommand by adding a null character at that
     * space. This is so I can check if the command is newprt or not. Then
     * I copy the rest of the string to a separate string used for the prompt.
     */
    if (usercommand[6] == ' ') {
      usercommand[6] = '\0';
      if (strcmp(usercommand, "newprt") == 0) {
        usercommand[6] = ' ';
        int i = 0;
        while (usercommand[i + 7] != '\0') {
          prompt[i] = usercommand[i + 7];
          i++;
        }
        prompt[i] = '\0';
        prt = 1;
      }
      continue;
    }

    if (strcmp(usercommand, "doors") == 0) {
      fprintf(stdout, "Please enter your name: ");
      fscanf(stdin, " %[^\n]", name);
      printf("name : %s\n", name);
      srand(time(0));
      int round = 1;
      int door = 0;
      int choice = 0;
      while (1) {
        door = (rand() % 2) + 1 + (round - 1) * 2;
        //printf("FOR DEBUGGING door is: %d\n", door);
        fprintf(stdout, "Round %d: Choose door %d or %d\n",
                round, round * 2 - 1, round * 2);
        fscanf(stdin, "%d", &choice);
        if (choice == door) {
          round++;
          if (round > high) high = round;
          if (round == 11) {
            printf("Wow I'm really surprised you got this far...\n"
                "How much time did you waste?? Was it all worth it??\n"
                "Welp, I guess you won.\n.\n.\nWell actually this game doesn't "
                "end.\nCall it DLC.\n");
          }
          continue;
        } else {
          printf("\n");
          if (round == 1) {
            int round1 = rand() % 4;
            if (round1 == 0)
              printf("WOWWWWWWWWW YOU COULDN'T EVEN GET PAST THE FIRST ONE??\n");
            else if (round1 == 1)
              printf("Your parents would be disappointed in you...\n");
            else if (round1 == 2) {
              printf("I would say try again...\n");
              sleep(1);
              printf("but you don't give me much hope that you'd do better next time\n");
            }
            else printf("His palms are sweaty...\n");
          }
          if (round == 2) {
            int round2 = rand() % 3;
            if (round2 == 0)
              printf("You know if you're this bad you can probably just edit the "
                  "code to win\n");
            else if (round2 == 1)
              printf("At least you got past the first round...\n");
            else printf("Knees weak, arms are heavy...\n");
          }
          if (round == 3 || round == 4) {
            int round34 = rand() % 3;
            if (round34 == 0)
              printf("Vomit on his sweater already...\n");
            else if (round34 == 1)
              printf("Well you did better than I thought you would at least\n");
            else if (round34 == 2) {
              printf("I tried so hard\n");
              sleep(1);
              printf("And got so far\n");
              sleep(1);
              printf("But in the end\n");
              sleep(1);
              printf("It doesn't even matter...\n");
            }
          }
          if (round > 4) {
            int round5 = rand() % 3;
            if (round5 == 0)
              printf("Mom's spaghetti\n");
            else if (round5 == 1)
              printf("I got too lazy to make more comments\n"
                  "So you're just gonna need to live with this one.\n");
            else printf("I wonder if you're going to look at the"
                " code for this\n");
          }
          sleep(2);
          fprintf(stderr, "\n********** GAME OVER *********\n");
          sleep(2);
          fprintf(stderr, "You ONLY got to round %d?!?\n", round);
          sleep(2);
          fprintf(stderr, "HIGHEST NUMBER OF DOORS: %d\n\n", high);
          round = 1;
          break;
        }
      }
      continue;
    }

    pid_t k;
    int status;

    if ((k = fork()) == 0) {
      fprintf(stderr, "I'm the child: %s %d\n", usercommand, getpid());
      if (execlp(usercommand, usercommand, NULL) == -1) {
        fprintf(stderr, "Not a valid binary name\n");
        exit(1);
      }
    } else {
      waitpid(k, &status, 0);
    }
  }
  return 0;
}
