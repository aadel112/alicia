use Inline C => << '...';

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

char* uc_words(char* str) { return str; } //STUB
char* md5(char* str) { return str; } //STUB
int ascii(char c) { return c; } //STUB
char chr(int n) { return n; } //STUB
char* btrim(char* str, char* chars) { return str; } //STUB
char* rpad(char* str, int len, char* fill) { return str; } //STUB
char* lpad(char* str, int len, char* fill) { return str; } //STUB
char* replace(char* str, char* search, char* replace) { return str; } //STUB
char* repeat(char* str, int n) { return str; } //STUB
char* split_part(char* str, char* delim, int field) { return str; } //STUB
char* to_print(char* str) { return str; } //STUB
char* to_hex(char* str) { return str; } //STUB
char* to_ascii(char* str) { return str; } //STUB

...

%AliciaCore = (
		lower => 1,
		upper => 1,
        reverse => 1,
        left => 2,
        right => 2,
        index => 2,
        substr => 3
);

