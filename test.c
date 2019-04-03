#include <stdlib.h>

void main(int argc, char** argv){

  if(argc){

    printf("There were %d arguments and the first one was %s\n",argc,argv[0]);

    return 0;

  }

  else{

    printf("There were no arguments");

  }

}
