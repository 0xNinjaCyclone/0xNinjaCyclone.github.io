#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char data[256];
    char *cpReadData;
    int nSize;
} Buffer;

Buffer buf_new() {
    return (Buffer) { 0x00 };
}

void buf_write(Buffer *pBuf, char *cpData, size_t n) {
    if ( pBuf->nSize ) 
        pBuf->data[ pBuf->nSize-1 ] = ' ';

    memcpy( pBuf->data + pBuf->nSize, cpData, n );
    pBuf->nSize += n;
}

void buf_read(Buffer *pBuf) {
    if ( !pBuf->cpReadData )
        pBuf->cpReadData = pBuf->data;

    printf( pBuf->cpReadData );
    pBuf->cpReadData += pBuf->nSize;
}

void buf_readall(Buffer *pBuf) {
    printf( pBuf->data );
}

void main() {
    Buffer buf = buf_new();
    int nChoice, c;

    for ( ;; ) {
        printf( "\n\n1- Write\n2- Read\n3- Read full data\n4- Exit\n\nChoose: " );
        scanf( "%d", &nChoice );

        // Clearing the buffer so nothing breaks `getdelim` later ;)
        while ( (c = getchar()) != 0x0a && c != EOF ); 
        
        if ( nChoice == 1 ) {
            char *cpLine = NULL;
            size_t n = 0;
            printf( "Data: " );
            n = getdelim( (char **)&cpLine, &n, 0x0a, stdin );
            if ( ~n ) // Sanity check to avoid calling `buf_write` if `getdelim` failed
                buf_write( &buf, cpLine, n );
            free( cpLine );
        }

        else if ( nChoice == 2 )
            buf_read( &buf );

        else if ( nChoice == 3 )
            buf_readall( &buf );

        else if ( nChoice == 4 )
            break;
        
        else 
            puts( "[-] Invalid choice!" );
    }
}