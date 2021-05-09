#pragma once 
typedef unsigned char byte; //8bit
typedef unsigned short int word;//16bit
typedef word adr; //16bit

#define MEMSIZE ( 64*1024 )

#define pc reg[7]

#define NO_PARAMS 0
#define HAS_DD 1 
#define HAS_SS 2 

typedef struct {
    word val;
    word a;
} Arg;

typedef struct { 
    Arg ss; 
    Arg dd; 
    word _byte; 
}Obj;

typedef struct {
    word masc; 
    word opcode; 
    char * name;
    void (*do_func)(Obj ob); 
    //char params; 
} Command; 


void do_mov (Obj ob);
void do_add (Obj ob);
void do_movb (Obj ob);
void do_sob (Obj ob);
void do_clr (Obj ob);
void do_halt ();
void do_nothing ();






void trace(char * str, ... );
void test_mem();
void b_write( adr a, byte b );
byte b_read( adr a );
word w_read( adr a );
void w_write( adr a, word w );
void load_file(const char* file);
void mem_dump(adr start, word n);














