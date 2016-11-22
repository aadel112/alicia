use Inline C => << '...';

//STRING FUNCTIONS
//================

// not a complete list, but getting ideas from postgres
// https:#www.postgresql.org/docs/9.1/static/functions-string.html

char* slower( char* str ) {
	int i;

    for(i = 0; i < strlen(str); ++i){
        str[i] = tolower(str[i]);
	}
	return str;
}

char* supper( char* str ) {
	int i;
	for(i = 0; i < strlen(str); ++i){
		str[i] = toupper(str[i]);
	}
	return str;
}

char* sreverse(char* str) {
    int l = strlen(str);
    int i;
    char* tmp = (char*)malloc(l);

    for(i=0;i<l;++i){
        tmp[i] = str[l-i-1];
    }
    tmp[i] = '\0';
    strcpy(str,tmp);
    free(tmp);

    return str;
}

char* sleft(char* str, int len) {
	if(strlen(str) > len) {
		str[len] = '\0';
	}
	return str;
}

char* sright(char* str, int len) {
	return sreverse(sleft(sreverse(str), len));
}

int sindex(char* haystack, char* needle) {
    char* p = strtok(haystack, needle);
    if(p) {
        return strlen(p);
    }
    return -1;
}

char* ssubstr(char* str, int start, int len) {
    int l = strlen(str);
    int i, z=0;

    if(start<0 || len + start > l || len<0) {
        return str;
    }

    char* tmp = (char*)malloc(len);
    for(i=start;i<start+len;++i){
        tmp[z] = str[i];
        ++z;
    }
    tmp[z] = '\0';
    strcpy(str, tmp);
    free(tmp);

    return str;
}

char* suc_words(char* str) { 
    int i;
    int x = strlen(str);
    for (i=0;i<x;++i){
         if (isalpha(str[i]) && (!i || str[i-1] == ' ')){ 
             str[i]= toupper(str[i]);
         }
    } 
    return str; 
}

//TODO
// char* md5(char* str) { return str; } #STUB

int sascii(char c) {
	return (int)(c % 128);
}

char schr(int n) { 
    return (char)(n % 128); 
}

char* sbtrim(char* str, char* chars) { 
    int i,z, y = 0;
    int l = strlen(chars);
    int l2 = strlen(str);
    char* tmp = (char*)malloc(l2);

    int cond = 1;

    for(z=0;z<l2;++z){
        cond = 1;
        for(i=0; i<l && cond;++i){
            if(str[z] != chars[i] && i + 1 == l){
                tmp[y] = str[z];
                ++y;
            }
            else if( str[z] == chars[i] ){
                cond = 0;
            }
        }
    }
    tmp[y] = '\0';
    strcpy(str, tmp);
    free(tmp);
    
    return str;
}

char* srpad(char* str, int len, char* fill) { 
    char* tmp = (char*)malloc(len);
    int l = strlen(str);
    int l2 = strlen(fill);
    int i, z, y = 0;

    if(l > len)
        return str;

    strcpy(tmp, str);
    for(i=l;i<len;i+=l2){
        for(z=0;z<l2;++z){
            if(i+z < len) {
                tmp[i+z] = fill[z];
                ++y;
            }
        }
    }
    tmp[y+l] = '\0';
    strcpy(str, tmp);
    free(tmp);

    return str; 
}

char* slpad(char* str, int len, char* fill) { 
    char* tmp = (char*)malloc(len);
    int l = strlen(str);
    int l2 = strlen(fill);
    int i, z, y = 0;

    if(l > len)
        return str;

    for(i=0;i<len-l;i+=l2){
        for(z=0;z<l2;++z){
            if(i+z < len - l) {
                tmp[i+z] = fill[z];
                ++y;
            }
        }
    }
    tmp[y] = '\0';
    strcat(tmp, str);
    tmp[y+l] = '\0';
    strcpy(str, tmp);
    free(tmp);

    return str; 
}

// taken from 
//http:#stackoverflow.com/questions/779875/what-is-the-function-to-replace-string-in-c
char *sreplace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig && !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}

char* srepeat(char* str, int n) { 
    int l = strlen(str);
    char* tmp = (char*)malloc( n * l );
    int i, z = 0;

    for(i=0;i<n;++i){
        for(z=0;z<l;++z) {
            tmp[(i*l)+z] = str[z];
        }
    }
//     printf("%s:%s\n", tmp, str);
    strcpy(str, tmp);
    free(tmp);

    return str;
}

char* ssplit_part(char* str, char* delim, int field) { 
    char* p = strtok(str, delim);
    int i;
    for(i=0;p;++i){
        if(i==field)
            return p;
        p = strtok(str, delim);
    }
    return str; 
}

char* sto_print(char* str) { 
    char* tmp = str;
    int len = strlen(str);
    int i, z = 0;
    for(i=0;i<len;++i){
        if(isprint(str[i])) {
            tmp[z] = str[i];
            ++z;
        }
    }
    tmp[z] = '\0';
    return tmp; 
}

//TODO
// char* to_hex(char* str) { 
//     return str; 
// }

char* sto_ascii(char* str) { 
    char* tmp = str;
    int len = strlen(str);
    int i, z = 0;
    for(i=0;i<len;++i){
        if(isascii(str[i])) {
            tmp[z] = str[i];
            ++z;
        }
    }
    tmp[z] = '\0';
    return tmp; 
}
...

%AliciaFuncs = (
		slower => 1,
		supper => 1,
        sreverse => 1,
        sleft => 2,
        sright => 2,
        sindex => 2,
        ssubstr => 3,
        suc_words => 1,
        sascii => 1,
        schr => 1,
        sbtrim => 2,
        srpad => 3,
        slpad => 3,
        sreplace => 3,
        srepeat => 2,
        ssplit_part => 3,
        sto_print => 1,
        sto_ascii => 1
);


