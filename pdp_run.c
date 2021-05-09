#include <stdio.h>
#include <stdlib.h>
#include "pdp.h"

word reg[8]; // регистра р0 ... р7

Command cmd[] = {
    {0170000, 0010000, "mov", do_mov},
    {0170000, 0060000, "add", do_add},
    {0170000, 0110000, "movb", do_movb},
    {0177000, 0077000, "sob", do_sob},
    {0177700, 0005000, "clr", do_clr},
    {0177777, 0000000, "halt", do_halt},
    {0000000, 0000000, "nothing", do_nothing}
};

Arg get_mr( word w ) 
{
    Arg res; 
    int r = w & 7; 
    int mode = ( w >> 3 ) & 7; 
    switch ( mode ) {
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
            reg[r] += 2; // todo  +1 
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

Arg get_arg( word w, adr a ) {
    Arg res;
    res.val = w;
    res.a = a;
    return res;
}

Obj get_obj ( word w, adr a ){
    Obj res; 
    Arg arg = get_arg(w, a);
    res.dd = get_dd(arg);
    res.ss = get_ss(arg);
    return res; 
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
void do_mov(Obj ob) 
{
    w_write(ob.ss.a, ob.dd.val);
}
void do_movb(Obj ob) {    
    b_write(ob.ss.a, ob.dd.val);
    //trace("%06o : %06ho\n",start + i, w_read(start + i));
}
void do_add(Obj ob) 
{
    word res = w_read(ob.dd.a) + ob.ss.val;
    w_write(ob.dd.a, res); 
    //trace("%06o : %06ho\n",start + i, w_read(start + i));
}
void do_nothing() 
{
    exit(0);
}
/*
void do_sob (Obj ob) {
    
}
*/
void do_clr( Obj ob ) {
    w_write(ob.dd.a, 0); 
    //trace("%06o : %06ho\n",start + i, w_read(start + i));
}
void run() 
{
    pc = 01000;
    while (1) {

        word w = w_read(pc);
        Obj kk = get_obj(w);
        trace("06o % 06: \n", pc, w);
        pc += 2;
        if ( (w&0177777) == 0 ) {
            trace("halt ");
            do_halt(); 
        }
        else if ( (w & 0170000) == 0010000 ) { // 01SSDD
            trace("mov ");
            do_mov(kk);
        }
        
        else if ( (w & 0170000) == 0060000 ) {
            trace("add ");
            do_add(kk);
        }
        else if ( (w & 0177700 ) == 0005000) {
            trace("clr ");
            do_clr(kk);
        }
        else if ( w == 0 ) {
            trace("nothing ");
            do_nothing();
        }
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
