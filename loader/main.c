
#include "shared.h"
void low_put_char(int c);

void start_loader(void){
    low_put_char('M');
    for(;;);
    return;
    }
