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

#define K 1

void trace(char * str, ... ) {
    va_list ap; 
    va_start(ap, str);
    vprintf(str, ap);
    va_end(ap); 
    
}

 //"http://www.example.com:80/path/to/myfile.html?key1=value1&key2=value2#SomewhereInTheDocument";

Url parce_url( const char * url )
{
    Url res;
    
    char * dmn = strstr( url, "://" ); // domain..
    char * prt = strstr( dmn+3, ":" ); // port..
    char * pth = strstr( prt, "/" ); // path..
    char * prm = strstr( pth, "?" ); // param..
    char * anc = strstr( prm, "#" ); // anchor
    
    for ( int i = 0; i < 6; i++ ) {
        switch ( i )
        {
            case 0 : 
                if ( strstr(url, "://") != NULL) { 
                    res.protocol = malloc(K * sizeof(char));
                    if ( ( strlen ( url ) - strlen(strstr(url, "://")) ) < K ) { 
                        sscanf(url, "%[^://]", res.protocol);
                        break;
                    }
                    else {
                        res.protocol = realloc( res.protocol, strlen ( url ) - strlen(strstr(url, "://")) + K );
                        sscanf(url, "%[^://]", res.protocol);
                        break;
                    }
                }
                else { 
                    trace( "no protocol exists" ); 
                    break;
                }
            case 1 : 
                res.domain = malloc(K);
                if ( dmn != NULL ) {
                        if ( ( strlen ( dmn + 3 ) - strlen(prt) ) < K ) { 
                        sscanf(dmn+3, "%[^:]", res.domain);
                        break;
                    }
                    else {
                        res.domain = realloc( res.domain, strlen ( dmn ) - strlen( prt ) +K );
                        sscanf(dmn+3, "%[^:]", res.domain);
                        break;
                    }
                }
                else {
                    break;
                }
            case 2 : 
                    res.port = malloc(K);
                    if ( ( strlen ( prt ) - strlen(pth) ) < K ) { 
                        sscanf(prt, "%[^/]", res.port);
                        break;
                    }
                    else {
                        res.port = realloc( res.port, strlen ( prt ) - strlen( pth )  + K);
                        sscanf(prt, "%[^/]", res.port);
                        break;
                    }
            case 3 : 
                res.path = malloc(K);
                if ( ( strlen ( pth ) - strlen(prm) ) < K ) { 
                    sscanf(pth, "%[^?]", res.path);
                    break;
                }
                else {
                    res.path = realloc( res.path, strlen ( pth ) - strlen( prm ) + K );
                    sscanf(pth, "%[^?]", res.path);
                    break;
                }
            case 4 : 
                res.param = malloc(K);
                memset(res.param, 0, K);
                if ( ( strlen ( prm ) - strlen(anc) ) < K ) { 
                    sscanf(prm, "%[^#]", res.param);
                    break;
                }
                else {
                    res.param = realloc( res.param, strlen ( prm ) - strlen(anc) + K );
                    sscanf(prm, "%[^#]", res.param);
                    break;
                }
            case 5 : 
                res.anchor = malloc(K);
                memset(res.anchor, 0, K);
                if (  strlen(anc) < K ) { 
                    sscanf(anc, "%s", res.anchor);
                    break;
                }
                else {
                    res.anchor = realloc( res.anchor, strlen(anc) + K );
                    sscanf(anc, "%s ", res.anchor);
                    break;
                }
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


int main()
{
    const char * str = "http://www.example.com:80/path/to/myfile.html?key1=value1&key2=value2#SomewhereInTheDocument";
    //const char * str = "http://www.exam";
    Url res = parce_url(str); 
    //trace( "%s://\n%s\n:%s\n%s\n%s\n#%s\n", res.protocol, res.domain, res.port, res.param, res.path, res.anchor );
    
    /*
    char * dmn = strstr( str, "://" ); // domain..
    char * prt = strstr( dmn+3, ":");
    char * pth = strstr( prt, "/" ); // path..
    char * prm = strstr( pth, "?" ); // param..
    char * anc = strstr( prm, "#" ); // ancho
    trace( "%s \n %s \n ",prm, anc);
    */
    
    trace( "%s\n%s\n%s\n%s\n%s\n%s\n", res.protocol, res.domain, res.port, res.path, res.param, res.anchor);
    free(res.protocol);
    free(res.domain);
    free(res.port);
    free(res.path);
    free(res.param);
    free(res.anchor);
    return 0;
}
