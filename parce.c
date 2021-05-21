#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>

#include <ctype.h>




#define trace_level 1

const char * STR = "developer.mozilla.org";

typedef struct {
    char * protocol;
    char * domain;
    char * port;
    char * path;
    char * param;
    char * anchor;
} Url; 



void trace(char * str, ... ) {
    if ( trace_level == 0 )
        return;
    va_list ap; 
    va_start(ap, str);
    vprintf(str, ap);
    va_end(ap); 
    
}

void free_all (Url res) {
    free(res.protocol);
    free(res.domain);
    free(res.port);
    free(res.path);
    free(res.param);
    free(res.anchor); 
}


Url parce_url( char * url ) 
{
    Url res = {NULL, NULL, NULL, NULL, NULL, NULL};
    if ( strstr(url, "://") == NULL ) 
        return res;

    char * s = strdup( url );
    char * domen = strstr(url, "://") + 3 ;  
    *( s + ( domen - url ) ) = '\0'; 
    res.protocol = strdup(s); 
    free(s);
    
    s = strdup(domen);// ??
    
    char * anchor  = strchr( s , '#');
    if( anchor != NULL) {
        res.anchor = strdup(anchor);
        *( anchor ) = '\0';
    }
    char * param = strstr( s, "?" ); 
    if ( param != NULL ) {
        res.param = strdup(param); 
        *( param ) = '\0';
    }
    char * path = strstr( s, "/" ); 
    if ( path != NULL ) {
        res.path = strdup(path);
        *( path ) = '\0'; 
    }
    char * port = strstr( s, ":" ); 
    if ( port != NULL ) {
        res.port = strdup(port); 
        *( port ) = '\0'; 
    } 
    if ( s == NULL ) 
        printf( "%s\n", url ); 
    else 
        res.domain = strdup(s); 
    free(s);
    return res; 
        
}
/*
void load_file ( const char * file )
{    
    char str[2048];
    Url res; 
    FILE * fl = fopen(file, "r"); 
    if ( fl != NULL ) { 
        while ( fscanf(fl, "%s\n", str ) == 1 ) {
            res = parce_url(str);
            if ( res.domain != NULL ) {
                if ( strcmp( STR, res.domain ) == 0 )
                    printf( "%s\n", str );
                free_all(res);
            }
        }
    }
    else 
        exit(0);
}
*/

char * get_new_line ( char * s ) 
{
    char * end; 
    for ( end = s + strlen(s) - 1; ( end >= s ) && isspace(*(end)) > 0; end-- ) {
        *(end) = '\0';
    }
    return s; 
    
}






void load_file ( const char * file )
{
    FILE * fl = fopen(file, "r"); 
    Url res = {NULL,NULL,NULL,NULL,NULL,NULL}; 
    char * str = NULL;
    
    //char * a = NULL;
    size_t len = 0;
    if ( fl != NULL ) { 
        while ( getline(&str, &len, fl) > 0 ) {
            str = get_new_line(str);
            res = parce_url(str);
            //a = strdup(res.domain);
            
            if ( res.domain != NULL ) {
                if ( strcmp( STR, res.domain ) == 0 ) {
                    fputs(str, stderr);
                    printf("\n");
                    //printf("%s\n", str);
                }
            }
            //free(a);
            free_all(res);
            
        }
        if ( str ) 
            free(str);
    fclose(fl);
    }
    
    else {
        fclose(fl);
        return;
    }
}




void get_console ( int argc, char * argv[] ) 
{ 
    if ( argc == 1 ) 
        exit(0);
    for ( int i =  1; i < argc; i++ ) {
        load_file(argv[i]);
    }
}

int main(int argc, char* argv[])
{
    get_console(argc, argv);
    /*
    char * str = "https://developer.mozilla.org";
    Url res = parce_url(str);
    trace("protocol - %s\n", res.protocol);
    trace("domain - %s\n", res.domain);
    trace("port - %s\n", res.port);
    trace("path - %s\n",res.path);
    trace("param - %s\n",res.param);
    trace("anchor - %s\n",res.anchor);
   
    int a = strcmp( STR, res.domain); 
    if ( a == 0 )
        printf("%s\n", "YES");
    printf("%d\n", a );
    free_all(res);
    */
    return 0;
}








