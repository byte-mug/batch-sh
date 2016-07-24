/*
 * Copyright (c) 2016 Simon Schmidt
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
 * SOFTWARE.
 */
#include <stdio.h>
#include "token.h"
#include "compile.h"
//char buffer[1<<12];


int main(int argc,const char* const* argv){
	size_t pos[2];
	int count=0;
	for(;;){
		/*
		if(!fgets(buffer,sizeof(buffer),stdin))return 0;
		pos[1]=0;
		while(next_token(buffer,pos)){
			if(count++>10)break;
			sds str = sdsnewlen(buffer+pos[0],pos[1]-pos[0]);
			printf("%d: (%d,%d) %s\n", count, (int)(pos[0]), (int)(pos[1]) ,str);
		}
		break;
		*/
		sds str = compile_line(stdin);
		if(!str)continue;
		printf("%s\n",str);
		sdsfree(str);
	}
}
