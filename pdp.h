typedef unsigned char byte; //8bit
typedef unsigned short int word;//16bit
typedef word adr; //16bit



void b_write( adr a, byte b ); 
byte b_read( adr a ); 
void w_write( adr a, word w ); 
word w_read( adr a ); 
void load_file();
void mem_dump(adr start, word n);
void trace(char * str, ... );
