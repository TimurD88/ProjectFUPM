#include <stdio.h>
#include <assert.h>
#include <stdarg.h>

typedef unsigned char byte; //8bit
typedef unsigned short int word;//16bit
typedef word adr; //16bit

#define MEMSIZE ( 64*1024 )

byte mem[MEMSIZE];

void b_write( adr a, byte b ); 
byte b_read( adr a ); 
void w_write( adr a, word w ); 
word w_read( adr a ); 
void load_file();
void mem_dump(adr start, word n);


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
/*
int main ()
{
    test_mem();
    //load_file();
    mem_dump(0x40,4);
    return 0; 
}
*/
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
void load_file()
{
    adr a;
    unsigned short int n;
    byte b = 0x00;
    int i;
    while(1) {
        int in = scanf("%04hx%04hx", &a, &n);
        if( in != 2){
            break;
        }
        for (i = 0; i < n; i++) {
            scanf("%02hhx", &b);
            b_write(a + i, b);
        }
    }
}
void mem_dump(adr start, word n)
{
    for ( word i = 0; i < n; i += 2 )
    {
        printf("%06o : %06ho\n",start + i, w_read(start + i));
    }
}
