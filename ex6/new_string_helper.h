/*
 * Copyright (c) 2018           Jinyi Xian <jinyi.xian@student.manchester.ac.uk>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. *
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define BUFSIZE 26

/*********************************************
 ******* EXAMPLE USAGE ***********************

int getNextString(char *buffer, int size, FILE *stream);

int main() {
    int numStr;
    int numQuery;

    scanf("%d", &numStr);
    scanf("%d", &numQuery);

    char *buffer = calloc(BUFSIZE, sizeof(char));
    
    int len = getNextString(buffer, BUFSIZE, stdin);
    printf("%s\n", buffer);
    len = getNextString(buffer, BUFSIZE, stdin);
    printf("%s\n", buffer);
    len = getNextString(buffer, BUFSIZE, stdin);
    printf("%s\n", buffer);

    len = getNextString(buffer, BUFSIZE, stdin);
    printf("%s\n", buffer);
    len = getNextString(buffer, BUFSIZE, stdin);
    printf("%s\n", buffer);
    len = getNextString(buffer, BUFSIZE, stdin);
    printf("%s\n", buffer);

    free(buffer);
    return 0;
}
*/

/*
 * int getNextString(char *buffer, int size, FILE *stream);
 * 
 *         **buffer**       points to the position to put the string
 * 
 *         **size**         should be the size of the buffer
 *                              getNextString will read at most size-1 characters surrounded
 *                              by quotes, and put a \0 after the last character chosen
 * 
 *         **stream**       the FILE pointer to the stream to read characters from
 * 
 * 
 * RETURN VALUE
 * 
 *       -1 when parse error or EOF
 *       the length of the string surrounded by the quotes otherwise
*/
int getNextString(char *buffer, int size, FILE *stream) {

    int ch = fgetc(stream);
    // find the left quote
    while (ch != EOF && ch != '"')
        ch = fgetc(stream);

    // EOF or parsing error
    if (ch != '"')
        return -1;

    int nbytes = 0;
    const int maxSz = size-1;
    ch = fgetc(stream);
    while (nbytes != maxSz && ch != '"') {
        buffer[nbytes] = ch;
        ch = fgetc(stream);
        ++nbytes;
    }

    buffer[nbytes] = 0;
    return nbytes;
}

