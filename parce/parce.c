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

void trace(char * str, ... ) {
    va_list ap; 
    va_start(ap, str);
    vprintf(str, ap);
    va_end(ap); 
    
}

//"http://www.example.com:80/path/to/myfile.html?key1=value1&key2=value2#SomewhereInTheDocument";://www.example.com:80/path/to/myfile.html?key1=value1&key2=value2#SomewhereInTheDocument"; 


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



Url parce_url( const char * url )
{
    Url res;
    char * dmn = NULL; // domain..
    char * prt = NULL; // port..
    char * pth = NULL; // path.. 
    char * prm = NULL; // param..
    char * anc = NULL; // anchor
    
    /*
    char * dmn = strstr( url, "://" ); // domain..
    char * prt = strstr( dmn+3, ":" ); // port..
    char * pth = strstr( prt, "/" ); // path.. 
    char * prm = strstr( pth, "?" ); // param..
    char * anc = strstr( prm, "#" ); // anchor
    */
    dmn = strstr( url, "://" ); // domain..
    if ( dmn != NULL ) 
        prt = strstr( dmn+3, ":" ); // port..
    if ( prt != NULL )
        pth = strstr( prt, "/" ); // path.. 
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
                res.domain = get_parce(res.domain, dmn, prt);
                break;
                /*if ( dmn != NULL ) {
                        if ( ( strlen ( dmn + 3 ) - strlen(prt) ) < K ) { 
                        sscanf(dmn+3, "%[^:]", res.domain);
                        trace("domain - %s \n", res.domain);
                        break;
                    }
                    else {
                        res.domain = realloc( res.domain, strlen ( dmn ) - strlen( prt ) +K );
                        sscanf(dmn+3, "%[^:]", res.domain);
                        trace("domain - %s \n", res.domain);
                        break;
                    }
                }
                else {
                    res.domain = NULL;
                    trace("domain - %s \n", res.domain);
                    break;
                }*/
            case 2 :
                    res.port = malloc(K);
                    res.port = get_parce(res.port, prt, pth);
                    break;
                    /*
                    if ( prt != NULL ) {
                    if ( ( strlen ( prt ) - strlen(pth) ) < K ) { 
                        sscanf(prt, "%[^/]", res.port);
                        trace("port - %s \n", res.port);
                        break;
                    }
                    else {
                        res.port = realloc( res.port, strlen ( prt ) - strlen( pth )  + K);
                        sscanf(prt, "%[^/]", res.port);
                        trace("port - %s \n", res.port);
                        break;
                    }
                    }
                    else{
                    res.port = NULL;
                    trace("port - %s \n", res.port);
                    break;
                }*/
            case 3 : 
                res.path = malloc(K);
                res.path = get_parce(res.path, pth, prm ); 
                break;
                /*if ( pth != NULL ) {
                if ( ( strlen ( pth ) - strlen(prm) ) < K ) { 
                    sscanf(pth, "%[^?]", res.path);
                    trace("path - %s \n", res.path);
                    break;
                }
                else {
                    res.path = realloc( res.path, strlen ( pth ) - strlen( prm ) + K );
                    sscanf(pth, "%[^?]", res.path);
                    trace("path - %s \n", res.path);
                    break;
                }
                }
                else{
                    res.path = NULL;
                    trace("path - %s \n", res.path);
                    break;
                }*/
            case 4 : 
                res.param = malloc(K);
                res.param = get_parce(res.param, prm, anc); 
                break;
                /*if ( prm != NULL ) {
                if ( ( strlen ( prm ) - strlen(anc) ) < K ) { 
                    sscanf(prm, "%[^#]", res.param);
                    trace("param - %s \n", res.param);
                    break;
                
                }
                else {
                    res.param = realloc( res.param, strlen ( prm ) - strlen(anc) + K );
                    sscanf(prm, "%[^#]", res.param);
                    trace("param - %s \n", res.param);
                    break;
                }
                }
                else {
                    res.param = NULL;
                    trace("param - %s \n", res.param);
                    break;
                }*/
            case 5 : 
                res.anchor = malloc(K);
                res.anchor = get_parce( res.anchor, anc, NULL ); 
                break;
                /*if ( anc != NULL ) {
                if (  strlen(anc) < K ) { 
                    sscanf(anc, "%s", res.anchor);
                    trace("anchor - %s \n", res.anchor);
                    break;
                }
                else {
                    res.anchor = realloc( res.anchor, strlen(anc) + K );
                    sscanf(anc, "%s ", res.anchor);
                    trace("anchor - %s \n", res.anchor);
                    break;
                }
                }
                else {
                    res.anchor = NULL;
                    trace("anchor - %s \n", res.anchor);
                    break;
                }*/
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
    //const char * str = "http://www.example.com:80/path/to/myfile.html?key1=value1&key2=value2#SomewhereInTheDocument";
    const char * str = "http://www.example.com:80";
    Url res = parce_url(str); 
    //trace( "%s://\n%s\n:%s\n%s\n%s\n#%s\n", res.protocol, res.domain, res.port, res.param, res.path, res.anchor );
    //trace( "%s\n%s\n%s", res.protocol, res.domain, res.port);
    //trace( "%s\n%s\n%s\n%s\n%s\n%s\n", res.protocol, res.domain, res.port, res.path, res.param, res.anchor);
    free(res.protocol);
    free(res.domain);
    free(res.port);
    free(res.path);
    free(res.param);
    free(res.anchor);
    /*
    char * dmn = NULL; // domain..
    char * prt = NULL; // port..
    char * pth = NULL; // path.. 
    char * prm = NULL; // param..
    char * anc = NULL; // anchor
    
    
    char * dmn = strstr( url, "://" ); // domain..
    char * prt = strstr( dmn+3, ":" ); // port..
    char * pth = strstr( prt, "/" ); // path.. 
    char * prm = strstr( pth, "?" ); // param..
    char * anc = strstr( prm, "#" ); // anchor
    
    dmn = strstr( str, "://" ); // domain..
    if ( dmn != NULL ) 
        prt = strstr( dmn+3, ":" ); // port..
    if ( prt != NULL )
        pth = strstr( prt, "/" ); // path.. 
    if ( pth != NULL )
        prm = strstr( pth, "?" ); // param..
    if ( prm != NULL )
        anc = strstr( prm, "#" ); // anchor
    
    
    trace( "%s \n %s \n %s \n %s \n %s \n",  dmn, prt, pth, prm, anc ) ; 
    */
    return 0;
}
