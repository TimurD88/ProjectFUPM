#include <stdio.h>
#include <stdlib.h>
#include "pdp.h"
#include "pdp11.h"

word reg[8]; // регистра р0 ... р7
#define pc reg[7]

#define NO_PARAMS 0
#define HAS_DD 1 
#define HAS_SS 2 
/*
typedef struct { 
    
}Param;  

*/
typedef struct {
    word masc; 
    word opcode; 
    char * name;
    void (*do_func)(void); 
    //char params; 
} Command; 

typedef struct {
    word val;
    word a;
} Arg;


Arg ss = {0, 0}; 
Arg dd = {0, 0};  

Command cmd[] = {
    {0170000, 0010000, "mov", do_mov},
    {0170000, 0060000, "add", do_add},
    {0170000, 0110000, "movb", do_movb},
    {0177000, 0077000, "sob", do_sob},
    {0177700, 0005000, "clr", do_clr},
    {0177777, 0000000, "halt", do_halt},
    {0000000, 0000000, "nothing", do_nothing}
}

Arg get_mr( word w ) 
{
    Arg res; 
    int r = w & 7; 
    int mode = ( w >> 3 ) & 7; 
    switch ( m ) {
        case 0 : // R3
            res.a = r; 
            res.val = reg[r]; 
            trace("R%o", r); 
            break;
        case 1 : // (R3)
            res.a = reg[r]; 
            res.val = w_read(res.a); // todo b_read 
            trace("(R%o)", r); 
            break; 
        case 2 : // (R3) + #3
            res.a = reg[r]; 
            res.val = w_read(res.a); // todo b_read
            reg[r] += 2 // todo  +1 
            if ( r == 7 ) 
                trace("#%o", r); 
            else
                trace("(R%o)", r); 
            break; 
        default: 
            fprintf(stderr,
                    "Mode %o not made yet \n", mode); 
            exit(1); 
    }
}



Arg get_ss(word w)
{
    return get_mr( w >> 6 );
}
Arg get_dd(word w)
{
    return get_mr( w ); 
}

void do_halt()
{
    trace("THE END!!!\n");
    exit(0);
}
void do_mov(Arg w) 
{
    w_write(w.wal);
    //trace("%06o : %06ho\n",start + i, w_read(start + i));
}
void do_movb(Arg w) {    
    b_write(w.val);
    //trace("%06o : %06ho\n",start + i, w_read(start + i));
}
void do_add(word w) 
{
    word res = dd.val + ss.val;  
    w_write(dd.a, res); 
    //trace("%06o : %06ho\n",start + i, w_read(start + i));
}
void do_nothing() 
{
    exit(0);
}
void do_sob (word w) {
    word a = ( w >> 6 ) & 7; 
    reg[a] -= 1;
    if ( reg[a] != 0 ) 
        pc -= (sizeof(word)/sizeof(byte)) * ( w & 63 );  
}
void do_clear( word w ) {
    int a = ( w & 7 ); 
}
void run() 
{
    pc = 01000;
    while (1) {
        word w = w_read(pc);
        trace("06o % 06: \n", pc, w);
        pc += 2; 
        if ( w == 0 ) {
            trace("halt ");
            do_halt(); 
        }
        else if ( (w & 0170000) == 0010000 ) { // 01SSDD
            trace("mov ");
            
            //? do_move(w);
        }
        /*
        else if () {
        
        }
        else if () {
        
        }
        else if () {
        
        }*/
    }
}
/*
word is_byte (word w) {
    return (w >> 15) & 1; 
}


int main()
{
    return 0;
}
*/
