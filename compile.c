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
#include <string.h>
#include "compile.h"
#include "token.h"

char buffer[1<<12];

static inline int stcmp(const char* str,const char* pref){
	for(;*pref;pref++,str++){
		if(*str!=*pref)return 1;
	}
	return 0;
}


static inline int isIdentFirst(char x){
	return ((x>='a')&&(x<='z'))|((x>='A')&&(x<='Z'))|x=='_';
}

enum {
	F_isPiped = 1<<0,
	F_isAssign = 1<<1,
	F_isSubexpr = 1<<2
};

static sds compile_stock(const char* str,size_t *pos,sds first,int cnt){
	while((cnt>0)&&next_token(str,pos)){
		switch(*str){
		case '(':cnt++;
		case ')':cnt--;
		}
		first = sdscat(first," ");
		if(!stcmp(str+pos[0],"~&")){
			first = sdscat(first,"|");
		}else if(!stcmp(str+pos[0],"~&")){
			first = sdscat(first,"#");
		}else if(str[pos[0]]=='$'){
			first = sdscat(first,"_S.");
			first = sdscatlen(first,str+pos[0]+1,pos[1]-(pos[0]+1));
		}else{
			first = sdscatlen(first,str+pos[0],pos[1]-pos[0]);
		}
	}
	return first;
}
static inline sds compile_shell(const char* str,size_t len, sds first){
	switch(*str){
	case '"':
	case '\'':
		return sdscatlen(first,str,len);
	case '$':
		first = sdscat(first,"_S.");
		first = sdscatlen(first,str+1,len-1);
		return first;
	}
	first = sdscatrepr(first,str,len);
	return first;
}

static sds compile_expr(const char* str,int flags,size_t *pos){
	sds first,s1;
	int param;
	if(!next_token(str,pos))return NULL;
	
	if(isIdentFirst(str[pos[0]])){
		first = sdsnewlen(str+pos[0],pos[1]-pos[0]);
		if(!next_token(str,pos)) {sdsfree(first); return NULL;}
		if(str[pos[0]]=='(') /*)*/{
			if(flags&F_isPiped){
				s1 = sdsnew("_slot("); /*)*/
				s1 = sdscatsds(s1,first);
				sdsfree(first);
				first = s1;
				s1 = NULL;
				first = sdscat(first,",");
			}else{
				first = sdscat(first,"(");
			}
			first = compile_stock(str,pos,first,1);
		}else{
			if(flags&F_isPiped){
				s1 = sdsnew("_slot(_execp,"); /*)*/
			}else{
				s1 = sdsnew("_spawnp(");/*)*/
			}
			s1 = compile_shell(first,sdslen(first),s1);
			sdsfree(first);
			first = s1;
			s1 = NULL;
			do{
				first = sdscat(first,",");
				first = compile_shell(str+pos[0],pos[1]-pos[0],first);
			}while(next_token(str,pos));
			/*(*/
			first = sdscat(first,")");
		}
		return first;
	}
	return NULL;
}

sds compile_line(FILE* src){
	size_t pos[2];
	pos[1]=0;
	if(!fgets(buffer,sizeof(buffer),src))return NULL;
	return compile_expr(buffer,F_isPiped,pos);
}

