#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>



typedef struct {
    char * protocol;
    char * domain;
    char * port;
    char * path;
    char * param;
    char * anchor;
} Url; 

#define K 10
#define trace_level 0

void trace(char * str, ... ) {
    if ( trace_level == 0 )
        return;
    va_list ap; 
    va_start(ap, str);
    vprintf(str, ap);
    va_end(ap); 
    
}

//"http://www.example.com:80/path/to/myfile.html?key1=value1&key2=value2#SomewhereInTheDocument";
void free_all (Url res) {
    free(res.protocol);
    free(res.domain);
    free(res.port);
    free(res.path);
    free(res.param);
    free(res.anchor); 
}


char * get_parce ( char * res, char * start, char * end) {
    if ( start == NULL && end == NULL ) {
        return res = NULL; 
    }
    if ( start != NULL && end != NULL ) { 
        if ( ( strlen(start) - strlen(end) ) < K ) {
            strncpy(res, start, strlen(start) - strlen(end));
            trace(" - %s \n", res);
            return res;
        }
        else {
            res = realloc( res, strlen(start) - strlen(end) + K ); 
            strncpy(res, start, strlen(start) - strlen(end));
            trace( " - %s \n", res); 
            return res; 
        }
    }
    else if ( start != NULL && end == NULL ) {
        if ( strlen( start) < K ) {
            strncpy(res, start, strlen(start)); 
            trace( " - %s \n", res); 
            return res; 
        }
        else {
            res = realloc( res, strlen(start) + K ); 
            strncpy(res, start, strlen(start));
            trace( " - %s \n", res); 
            return res; 
        }
    }
    return res;
} 



Url parce_url( const char * url ) // для полной строки с портом, якорем и аргументом
{
    Url res = {NULL, NULL, NULL, NULL, NULL, NULL};
    char * dmn = NULL; // domain..
    char * prt = NULL; // port..
    char * pth = NULL; // path.. 
    char * prm = NULL; // param..
    char * anc = NULL; // anchor
    //"http://www.example.com:80/path/to/myfile.html?key1=value1&key2=value2#SomewhereInTheDocument";
    //const char * str = "https://developer.mozilla.org/ru/docs/Learn/";
    //const char * str = "https://developer.mozilla.org/ru/search?q=URL";    
    dmn = strstr( url, "://" ); // domain..
    
    if ( dmn != NULL ) 
        dmn = dmn + 3;
    else 
        return res;
    if ( dmn != NULL ) 
        prt = strstr( dmn+3, ":" ); // port..
    if ( prt != NULL )
        pth = strstr( prt, "/" ); // path..
    else 
        pth = strstr( dmn + 3, "/" ); 
    if ( pth != NULL )
        prm = strstr( pth, "?" ); // param..
    if ( prm != NULL )
        anc = strstr( prm, "#" ); // anchor
    
    trace("dmn - %s\n prt- %s\n pth - %s\n prm - %s\n anc - %s\n", dmn, prt, pth, prm, anc); 
    
    for ( int i = 0; i < 6; i++ ) {
        switch ( i )
        {
            case 0 : 
            /*
                res.protocol = malloc(K);
                res.protocol = get_parce(res.protocol, url, dmn);
                break;*/
                if ( strstr(url, "://") != NULL ) { 
                    res.protocol = malloc(K * sizeof(char));
                    if ( ( strlen ( url ) - strlen(strstr(url, "://")) ) < K ) { 
                        sscanf(url, "%[^://]", res.protocol);
                        trace("protocol - %s \n", res.protocol);
                        break;
                    }
                    else {
                        res.protocol = realloc( res.protocol, strlen ( url ) - strlen(strstr(url, "://")) + K );
                        sscanf(url, "%[^://]", res.protocol);
                        trace("protocol - %s \n", res.protocol);
                        break;
                    }
                }
                else { 
                    res.protocol = NULL; 
                    trace("protocol - %s \n", res.protocol);
                    break;
                }
            case 1 : 
                res.domain = malloc(K);
                if ( prt != NULL ) 
                    res.domain = get_parce(res.domain, dmn, prt);
                else 
                    res.domain = get_parce(res.domain, dmn, pth);
                break;
                
            case 2 :
                    res.port = malloc(K);
                    res.port = get_parce(res.port, prt, pth);
                    break;
                    
            case 3 : 
                res.path = malloc(K);
                res.path = get_parce(res.path, pth, prm ); 
                break;
               
            case 4 : 
                res.param = malloc(K);
                res.param = get_parce(res.param, prm, anc); 
                break;
                
            case 5 : 
                res.anchor = malloc(K);
                res.anchor = get_parce( res.anchor, anc, NULL ); 
                break;
                
        }
    }
    return res; 
    //sscanf(url, "%[^://]://%[^:]:%[^/]%[^?]%[^#]#%s", res.protocol, res.domain, res.port, res.path, res.param, res.anchor);
}
/*
    char * pth = strstr( prt, "/" ); // path..
    char * prm = strstr( pth, "?" ); // param..
    char * anc = strstr( prm, "#" ); // ancho
  */
//fscanf(fl, "%s\n", str)
void load_file ( const char * file )
{    
    const char * str = malloc(2048);
    Url res; 
    FILE * fl = fopen(file, "r"); 
    if ( fl != NULL ) { 
        while ( fscanf(fl, "%s\n", str ) == 1 ) {
            res = parce_url(str);
            if ( res.domain != NULL ) {
                if ( strcmp( "developer.mozilla.org", res.domain ) == 0 )
                    printf( "%s\n", str );
                free_all(res);
            }
        }
    }
    else 
        exit(0);
}
/*
void get_console(int argc, char * argv[]) {
    for(int i = 0; i < argc; ++i) {
        load_file(argv[i]);
    }
*/



int main()
{
    //get_console(argc, argv);
    load_file("url_list.txt");
    /*
    const char * str = "http://www.example.com:80/path/to/myfile.html?key1=value1&key2=value2#SomewhereInTheDocument";
    //const char * str = "https://developer.mozilla.org/ru/docs/Learn/";
    //const char * str = "https://developer.mozilla.org/ru/search?q=URL";
    //const char * str = "URL";
    
    Url res = parce_url(str); 
    
    trace ( "|...|\n protocol - %s \n domen - %s \n port - %s \n path - %s \n param - %s \n acn - %s \n ",
     res.protocol, res.domain, res.port, res.path, res.param, res.anchor);
    
    free_all(res);*/
    //
    //return 0;
}
