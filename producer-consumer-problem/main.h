#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> // for rand()
#include <pthread.h>

#include "./buffer/buffer.h"

#define THREADSLEEP_MAX 5
#define TRUE 1
#define FALSE 0