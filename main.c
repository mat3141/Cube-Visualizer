#include "cube.h"
#include <stdio.h>
#include <termios.h>
#include <string.h>

static struct termios old, new; //Taken from stackoverflow, used to store and change terminal settings

void usage(char * name){
  printf("Usage: %s [-size integer] [-ww double] [-wv double] [-fill char] [-space char] [-h] \n"
	 "where size is the size of the square window in \"pixels\", \nww is the distance between "
	 "the window and the world space (must be positive), \nwv is the distance between the window"
	 "and the virtual camera (must be greater than 2), \n"
	 "fill is the character used for fill and space is the character used for space.\n", name);
}

int main(int argc, char ** argv){

  int wSize = 35;
  double vDist = 2;
  double vDistZ = 10;
  char fill = 'X';
  char space = '.';

  //Parse arguments
  for(int i = 1; i < argc; i++){
    if(!strcmp(argv[i],"-h")){
      usage(argv[0]);
      return 0;
    }
    if(!strcmp(argv[i],"-size")){
      if(++i == argc){
	printf("Expected number.\n");
	usage(argv[0]);
	return 0;
      }
      sscanf(argv[i], "%d", &wSize);
    }
    if(!strcmp(argv[i],"-ww")){
      if(++i == argc){
	printf("Expected number.\n");
	usage(argv[0]);
	return 0;
      }
      sscanf(argv[i], "%lf", &vDist);
    }
    if(!strcmp(argv[i],"-wv")){
      if(++i == argc){
	printf("Expected number.\n");
	usage(argv[0]);
	return 0;
      }
      sscanf(argv[i], "%lf", &vDistZ);
    }
    if(!strcmp(argv[i],"-fill")){
      if(++i == argc){
	printf("Expected character.\n");
	usage(argv[0]);
	return 0;
      }
      sscanf(argv[i], "%c", &fill);
    }
    if(!strcmp(argv[i],"-space")){
      if(++i == argc){
	printf("Expected character.\n");
	usage(argv[0]);
	return 0;
      }
      sscanf(argv[i], "%c", &space);
    }
    if(!strcmp(argv[i],"-h")){
      usage(argv[0]);
      return 0;
    }
  }

  cube * a = newCube(wSize, vDist, vDistZ, fill, space);
  if(!a){
    printf("Check that arguments are valid.\n\n");
    usage(argv[0]);
    return 0;
  }

  //Taken from stackoverflow, used to change terminal settings so that characters are read continously
  tcgetattr(0, &old);
  new = old;
  new.c_lflag &= ~ICANON;
  new.c_lflag &= 0 ? ECHO : ~ECHO;
  tcsetattr(0, TCSANOW, &new);
  //

  while(1){
    printf("\033c"); //Clears terminal
    printf("Controls:\n A, D: yaw\n W, S: pitch\n Q, E: roll\n X: quit\n"); 
    render(a);

    char c = '\0';
    c = getchar();
    if(c == 'a') rotateBy(a, 0, 0, 5.625);
    if(c == 'd') rotateBy(a, 0, 0, -5.625);
    if(c == 'w') rotateBy(a, 0, 5.625, 0);
    if(c == 's') rotateBy(a, 0, -5.625, 0);
    if(c == 'q') rotateBy(a, 5.625, 0, 0);
    if(c == 'e') rotateBy(a, -5.625, 0, 0);
    if(c == 'x') break;
  }

  deleteCube(a);

  //Taken from stackoverflow, used to restore previous terminal settings
  tcsetattr(0, TCSANOW, &old);
  //
  
}
