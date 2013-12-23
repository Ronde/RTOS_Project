
#include <cstdio>
#include <unistd.h>
#include "miosix.h"

using namespace std;
using namespace miosix;

typedef Gpio<GPIOA_BASE,0> button;

int main()
{   
    button::mode(Mode::INPUT);
    for(;;){
        if(button::value()==1){
            printf("Hello World");
        }
    }
    //iprintf("Hello world, write your application here\n");
}
