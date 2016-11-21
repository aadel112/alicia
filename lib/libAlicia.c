use Inline C => << '...';

//STRING FUNCTIONS
//================

// not a complete list, but getting ideas from postgres
// https://www.postgresql.org/docs/9.1/static/functions-string.html

char* lower( char* str ) {
	int i;
	for(i = 0; strlen(str); ++i){
		str[i] = tolower(str[i]);
	}
	return str;
}

char* upper( char* str ) {
	int i;
	for(i = 0; strlen(str); ++i){
		str[i] = toupper(str[i]);
	}
	return str;
}

//this craftt answer taken from 
// http://stackoverflow.com/questions/784417/reversing-a-string-in-c
char* reverse(char * str) {
	if (str) {
		char * end = str + strlen(str) - 1;

		// swap the values in the two given variables
		// XXX: fails when a and b refer to same memory location
#   define XOR_SWAP(a,b) do\
		{\
			a ^= b;\
			b ^= a;\
			a ^= b;\
		} while (0)

		// walk inwards from both ends of the string, 
		// swapping until we get to the middle
		while (str < end) {
			XOR_SWAP(*str, *end);
			str++;
			end--;
		}
#   undef XOR_SWAP
	}
	return str;
}

char* left(char* str, int len) {
	if(strlen(str) >= len) {
		str[len+1] = '\0';
	}
	return str;
}

char* right(char* str, int len) {
	reverse(str);
	if(strlen(str) >= len) {
		str[len+1] = '\0';
	}
	return str;
}

int index(char* needle, char* haystack) {
    int l = strlen(haystack);
    int sl = strlen(needle);
    int i, ret = -1;
    int p, pa, f = 0;

    if( !sl || !l || sl > l ) {
        return ret;
    }

    for(i=0;i<l;++i) {
        if(haystack[i+p] == needle[p]) {
            pa = 1;
            ++p;
        }
        else {
            pa = 0;
            p = 0;
        }

        if( p >= sl ) {
            return i - p;
        }
    }
    return ret;
}

char* substr(char* str, int start, int len) {
    int l = strlen(str);
    int pos = start + len > l ? l : start + len;
    str[pos-1] = '\0';
    return str;
}

char* uc_words(char* str) { 
    int i;
    int x = strlen(string);
    for (i=1;i<x;i++){
         if (isalpha(str[i]) && str[i-1] == ' '){ 
             str[i]= toupper(str[i]);
         }
    } 
    return str; 
}

//TODO
// char* md5(char* str) { return str; } //STUB

int ascii(char c) {
	return (int)(c % 128);
}

char chr(int n) { 
    return (char)(n % 128); 
}

char* btrim(char* str, char* chars) { 
    int i,z, y;
    char* tmp = str;
    int l = strlen(chars);
    int l2 = strlen(str);

    for(i=0; i<l;++i){
        for(z=0;z<l2;++z){
            if(str[z] == chars[i]){
            }
            else {
                tmp[y] = str[z];
                ++y;
            }
        }
    }
    tmp[y] = '\0';
    
    return tmp;
}

char* rpad(char* str, int len, char* fill) { 
    char* tmp = str + len;
    int l = strlen(str);
    int l2 = strlen(fill);
    int i;

    if(l2+l > len)
        return str;

    strcpy(tmp, src, l);
    for(i=l;i<len;i+=l2){
        strcat(tmp, fill);
    }

    return tmp; 
}

char* lpad(char* str, int len, char* fill) { 
    char* tmp = str + len;
    int i;
    int l = strlen(str);
    int l2 = strlen(fill);

    if(l+l2>len)
        return str;
    
    for(i=l2;i<len;i+=l2){
        strcat(tmp,fill);
    }
    strcat(tmp,str);

    return tmp;
}

// taken from 
//http://stackoverflow.com/questions/779875/what-is-the-function-to-replace-string-in-c
char *replace(char *orig, char *rep, char *with) {
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

char* repeat(char* str, int n) { 
    int l = strlen(str);
    char* tmp = str * n;
    int i, z = 0;

    for(i=0;i<n;++i){
        for(z=0;z<l;++z) {
            tmp[i+z] = str[z];
        }
    }
    return tmp;
}

char* split_part(char* str, char* delim, int field) { 
    char* p = strtok(str, delim);
    int i;
    for(i=0;p;++i){
        if(i==field)
            return p;
        p = strtok(str, delim);
    }
    return str; 
}

char* to_print(char* str) { 
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

char* to_ascii(char* str) { 
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

%AliciaCore = (
		lower => 1,
		upper => 1,
        reverse => 1,
        left => 2,
        right => 2,
        index => 2,
        substr => 3,
        ascii => 1,
        chr => 1,
        btrim => 2,
        rpad => 3,
        lpad => 3,
        replace => 3,
        repeat => 2,
        split_part => 3,
        to_print => 1,
        to_ascii => 1
);

