#include <stdio.h>
#include <assert.h>

typedef unsigned char byte; //8bit
typedef unsigned short int word;//16bit
typedef word Adress; //16bit

#define MEMSIZE ( 64*1024 )

byte mem[MEMSIZE];

void b_write( Adress adr, byte b ); 
byte b_read( Adress adr ); 
void w_write( Adress adr, word w ); 
word w_read( Adress adr ); 

void test_mem() {
    byte b0 = 0x0a; 
    //байт - байт
    b_write(2, b0);
    byte bres = b_read(2); 
    assert( b0 == bres); 
    
    // 2 байта - слово
    Adress a = 4; 
    word w = 0xcb0a;
    w_write(a, w); 
    word wres = w_read(a); 
    assert( w == wres); 
    //printf("%04hx=%04hx\n", w, wres); 
}

int main ()
{
    test_mem();
    return 0; 
}

void b_write( Adress adr, byte b )
{
    mem[adr] = b; 
} 
byte b_read( Adress adr )
{
    return mem[adr]; 
}
word w_read( Adress adr )
{
    word w = ((word)mem[adr + 1]) << 8; 
    w = w | mem[adr]; 
    return w; 
}
void w_write( Adress adr, word w ){
    mem[adr] = w ;
    mem[adr+1] = w >> 8;
        
}
