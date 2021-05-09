#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>

typedef struct {
    char protocol[40];
    char domain[40];
    char port[40];
    char path[40];
    char param[40];
    char anchor[40];
} Url; 

void trace(char * str, ... ) {
    va_list ap; 
    va_start(ap, str);
    vprintf(str, ap);
    va_end(ap); 
    
}


Url parce_url( const char * url )
{
    Url res; 
    sscanf(url, "%[^://]://%[^:]:%[^/]%[^?]%[^#]#%s", res.protocol, res.domain, res.port, res.param, res.path, res.anchor);
    //sscanf(url, "%[^://]://%[^:]:%[^/]/%[^?]?%[^#]#%s", 
//res.protocol, res.domain, res.port, res.param, res.path, res.anchor);  
    return res; 
}


int main()
{
    const char * str = "http://www.example.com:80/path/to/myfile.html?key1=value1&key2=value2#SomewhereInTheDocument";
    Url res = parce_url(str); 
    //trace( "%s  ", &res.protocol, &res.domain, &res.port, &res.param, &res.path, &res.anchor );
    printf("%s\n ", res.protocol);
    printf("%s\n ", res.domain);
    printf("%s\n ", res.port);
    printf("%s\n ", res.param);
    printf("%s\n ", res.path);
    printf("%s\n ", res.anchor);
    return 0;
}
