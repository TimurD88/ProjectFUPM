#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include "pdp.h"


byte mem[MEMSIZE];

void trace(char * str, ... ) {
    va_list ap; 
    va_start(ap, str);
    vprintf(str, ap);
    va_end(ap); 
    
}

void get_console(int argc, char * argv[]) {
    for(int i = 0; i < argc; ++i) {
        load_file(argv[i]);
    }
}

void test_mem() {
    byte b0 = 0x0a; 
    //байт - байт
    b_write(2, b0);
    byte bres = b_read(2); 
    assert( b0 == bres); 
    
    // 2 байта - слово
    adr a = 4; 
    word w = 0xcb0a;
    w_write(a, w); 
    word wres = w_read(a); 
    assert( w == wres); 
    //printf("%04hx=%04hx\n", w, wres); 
}

int main (int argc, char * argv[])
{   
    get_console(argc, argv);
    run();
    return 0; 
}

void b_write( adr a, byte b )
{
    mem[a] = b; 
} 
byte b_read( adr a )
{
    return mem[a]; 
}
word w_read( adr a )
{
    word w = ((word)mem[a + 1]) << 8; 
    w =  w | (mem[a] & 0xFF); 
    return w; 
}
void w_write( adr a, word w ){
    mem[a] = w & 0xFF;
    mem[a+1] = w >> 8 & 0xFF;
}
void load_file(const char* file)
{
    FILE * fl = fopen(file, "r"); 
    if ( fl == NULL ) {
        exit(0); 
    }
    else {
        adr a = 0;
        word w = 0; 
        unsigned short int n = 0; 
        int i;
        while ( fscanf(fl, "%04hx%02hx", &a, &n) == 2 ) {
            for ( i = 0; i < n; i+=2 ){
                fscanf(fl, "%02hx", &w);
                w_write(a + i, w); 
            }
        }
    }
}
void mem_dump(adr start, word n)
{
    for ( word i = 0; i < n; i += 2 )
    {
        trace("%06o : %06ho\n",start + i, w_read(start + i));
        //printf("%06o : %06ho\n",start + i, w_read(start + i));
    }
}
