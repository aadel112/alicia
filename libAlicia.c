package libAlicia {
use Inline C => << '...';
/*
 * MIT License
 * Copyright (c) 2016 Aaron Adel
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 */

//EVIL MACROS
//===========

#define swap(x,y) do \
{ unsigned char swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1]; \
    memcpy(swap_temp,&y,sizeof(x)); \
    memcpy(&y,&x,       sizeof(x)); \
    memcpy(&x,swap_temp,sizeof(x)); \
} while(0)

// #define SWAP_PRIMITIVE(a,b,t) do { t c = a; a = b; b = c;}while(0)

#define eq(a,b) !strcmp(a,b)

#define SECOND "second"
#define MINUTE "minute"
#define HOUR "hour"
#define DAY "day"
#define MONTH "month"
#define YEAR "year"
#define CENTURY "century"
#define DOW "dow"
#define DOY "doy"
#define MILLENIUM "millenium"

#define BUFSIZE 80
#define MEDBUF 1024

#define QLNV(l,i) (SvNOK(*av_fetch(l, i, 0)) ? ((double)SvNV(*av_fetch(l, i, 0))) : 0)


//STRING FUNCTIONS
//================

// not a complete list, but getting ideas from postgres
// https:#www.postgresql.org/docs/9.1/static/functions-string.html

/*
 * @area: S FUNCTIONS
 * @function: lower
 * @example: lower('HELLO')
 * @example return: hello
 * @description: Converts A field to all lower case text
 * @parameters: a text field
 * @return: a text field
 */ 
char* _lower( char* str ) {
    int i;

    for(i = 0; i < strlen(str); ++i){
        str[i] = tolower(str[i]);
    }
    return str;
}


/*
 * @area: S FUNCTIONS
 * @function: upper
 * @example: upper('hello')
 * @example return: HELLO
 * @description: Converts A field to all upper case text
 * @parameters: a text field
 * @return: a text field
 */ 
char* _upper( char* str ) {
    int i;
    for(i = 0; i < strlen(str); ++i){
        str[i] = toupper(str[i]);
    }
    return str;
}


/*
 * @area: S FUNCTIONS
 * @function: reverse
 * @example: reverse('hello')
 * @example return: olleh
 * @description: Converts A field to the same text reversed
 * @parameters: a text field
 * @return: a text field
 */
char* _reverse(char* str) {
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

/*
 * @area: S FUNCTIONS
 * @function: leftstr
 * @example: leftstr('hello', 2)
 * @example return: he
 * @description: returns the left len characters 
 * from the string str
 * @parameters: (str, len)
 * @return: a text field
 */
char* _leftstr(char* str, int len) {
    if(strlen(str) > len) {
        str[len] = '\0';
    }
    return str;
}


/*
 * @area: S FUNCTIONS
 * @function: rightstr
 * @example: rightstr('hello', 2)
 * @example return: lo
 * @description: returns the right len characters from the string str
 * @parameters: (str, len)
 * @return: a text field
 */
char* _rightstr(char* str, int len) {
    return _reverse(_leftstr(_reverse(str), len));
}


/*
 * @area: S FUNCTIONS
 * @function: index
 * @example: index('hello', 'll')
 * @example return: 2
 * @description: returns the 0 based index if the needle in haystack if it exists, else -1
 * @parameters: (haystack, needle)
 * @return: int
 */
int _index(char* haystack, char* needle) {
    char* p = strtok(haystack, needle);
    if(p) {
        return strlen(p);
    }
    return -1;
}


/*
 * @area: S FUNCTIONS
 * @function: substr
 * @example: substr('hello', 0, 3)
 * @example return: hel
 * @description: returns the portion of the string from start for len characters, 0-based.
 * @parameters: (str, start, len)
 * @return: a text field
 */
char* _substr(char* str, int start, int len) {
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


/*
 * @area: S FUNCTIONS
 * @function: uc_words
 * @example: uc_words('hello world')
 * @example return: Hello World
 * @description: returns the text field with words beginnings upper cased.
 * @parameters: (str)
 * @return: a text field
 */
char* _uc_words(char* str) { 
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

/*
 * @area: S FUNCTIONS
 * @function: ascii
 * @example: ascii('A')
 * @example return: 65
 * @description: returns the ascii decimal value of the character passed
 * @parameters: (c)
 * @return: int
 */
int _ascii(char c) {
    return (int)(c % 128);
}

/*
 * @area: S FUNCTIONS
 * @function: chr
 * @example: chr(65)
 * @example return: A
 * @description: returns the ascii char corresponding to int n
 * @parameters: (n)
 * @return: char
 */
char _chr(int n) { 
    return (char)(n % 128); 
}

/*
 * @area: S FUNCTIONS
 * @function: btrim
 * @example: btrim('xxaxybcxxy', 'xy')
 * @example return: abc
 * @description: returns str with all of the characters in chars removed
 * @parameters: (str, chars)
 * @return: a text field
 */
char* _btrim(char* str, char* chars) { 
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


/*
 * @area: S FUNCTIONS
 * @function: rpad
 * @example: rpad('x', 5, 'yz')
 * @example return: xyzyz
 * @description: returns str right-padded with fill repeatedly until it reaches length len
 * @parameters: (str, len, fill)
 * @return: a text field
 */
char* _rpad(char* str, int len, char* fill) { 
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


/*
 * @area: S FUNCTIONS
 * @function: lpad
 * @example: lpad('x', 5, 'yz')
 * @example return: yzyzx
 * @description: returns str left-padded with fill repeatedly until it reaches length len
 * @parameters: (str, len, fill)
 * @return: a text field
 */
char* _lpad(char* str, int len, char* fill) { 
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

/*
 * @area: S FUNCTIONS
 * @function: replace
 * @example: replace('hello world', 'world', 'universe')
 * @example return: hello universe
 * @description: returns orig where rep is replaced with with
 * @parameters: (orig, rep, with)
 * @return: a text field
 */
char* _replace(char *orig, char *rep, char *with) {
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


/*
 * @area: S FUNCTIONS
 * @function: repeat
 * @example: repeat('abc', 3)
 * @example return: abcabcabc
 * @description: returns str repeated n times
 * @parameters: (str, n)
 * @return: a text field
 */
char* _repeat(char* str, int n) { 
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


/*
 * @area: S FUNCTIONS
 * @function: split_part
 * @example: split_part('hello world', ' ', 1)
 * @example return: world
 * @description: returns the 0-based field from  str split on delim
 * @parameters: (str, delim, field)
 * @return: a text field
 */
char* _split_part(char* str, char* delim, int field) { 
    char* p = strtok(str, delim);
    int i = 0;
    while(p){
        if( i == field ) {
            return p;
        }
        p = strtok(NULL, delim);
        ++i;
    }

    return str;
}


/*
 * @area: S FUNCTIONS
 * @function: to_print
 * @example: to_print('hello\nworld)
 * @example return: helloworld
 * @description: returns the str with all non-printing characters removed
 * @parameters: (str)
 * @return: a text field
 */
char* _to_print(char* str) { 
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


/*
 * @area: S FUNCTIONS
 * @function: to_ascii
 * @example: to_ascii('hello˚, ˳world')
 * @example return: helloworld
 * @description: returns the str with all non-ascii characters removed
 * @parameters: (str)
 * @return: a text field
 */
char* _to_ascii(char* str) { 
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

//DATE FUNCTIONS - TODO improve
//==============

// base taken from 
//http://stackoverflow.com/questions/19407944/convert-time-t-to-integer
//I just extended it
int strtomonth(int *mm, const char *str) {
    static const char *sname[] = {
        "jan", "feb", "mar", "apr", "may", "jun",
        "jul", "aug", "sep", "oct", "nov", "dec",
        NULL
    };    
    int i;

    for (i = 0; sname[i]; i++) {
        if (strcmp(sname[i], str) == 0) {
            *mm = i + 1;
            return 1;
        }
    }

    return 0;
}

int is_all_digits(char* str) {
    int l = strlen(str);
    int i;
    for(i=0;i<l;++i){
        if(!isdigit(str[i]))
            return 0;
    }
    return 1;
}

char* trim(char *str) {
    char *end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end+1) = 0;

    return str;
}

struct tm epoch_to_tm(int epoch) {
    time_t t = (time_t)epoch;
    struct tm ts;
    ctime(&t);
    ts = *localtime(&t);
    return ts;
}

//not ultra functional, in the sense that it's really not able to get too many formats right


/*
 * @area: S FUNCTIONS
 * @function: _strtotime
 * @example: _strtotime('2016-11-05 03:14:59')
 * @example return: 1478315699
 * @description: not super functional, needs to be  coded out more. Only accepts 6 formats,  and epoch times
 * returns the epoch if the date-like string
 * @parameters: (str)
 * @return: int epoch
 */
int _strtotime(char *s) {
    time_t t;
    struct tm tm;
    int dd, mm, yy;
    int hrs = 0, min = 0, sec = 0;
    int f0, f1, f2, f3=0, f4=0, f5=0;

    struct tm ts = epoch_to_tm((int)time(NULL));
    int current_year = ts.tm_year + 1900;

    s = trim(s);
    int len = strlen(s);

    if( !len ) {
        return (int)time(NULL);
    }

    if( len == 10 && is_all_digits(s) ) {
        return atoi(s);
    }

    if(sscanf(s, "%d-%d-%d %d:%d:%d", &f0, &f1, &f2, &f3, &f4, &f5) == 6)
        goto okay;
    else if(sscanf(s, "%d/%d/%d %d:%d:%d", &f0, &f1, &f2, &f3, &f4, &f5) == 6)
        goto okay;
    else if(sscanf(s, "%d-%d-%d", &f0, &f1, &f2) == 3)
        goto okay;
    else if(sscanf(s, "%d/%d/%d", &f0, &f1, &f2) == 3)
        goto okay;
    else if(sscanf(s, "%d/%d/%d", &f0, &f1, &f2) == 3)
        goto okay;
    return 0;

okay:
    //TODO - Do some sanity checking to rule out 2015-mar-35 and such

    hrs = f3;
    min = f4;
    sec = f5;
    
    if(f0>=100){
        yy=f0;
        mm=f1;
        dd=f2;
    }
    else if(f1>=100){
        yy=f1;
        mm=f0;
        dd=f2;
    }
    else if(f2>=100){
        yy=f2;
        mm=f0;
        dd=f1;
    }
    else {
        //assume mmddyy
        mm=f0;
        dd=f1;
        yy=f2;
    }

//     printf("PARSED %d, %d, %d\n", yy, mm, dd);

    if( mm > 12 || dd > 31 ) {
        swap(dd, mm);
    }

    if( yy < 100 ) {
        int tmp = ((current_year / 100) * 100) + yy;
        yy = tmp > current_year ? tmp - 100 : tmp;
    }

    tm.tm_sec = sec;
    tm.tm_min = min;
    tm.tm_hour = hrs;
    tm.tm_mday = dd;
    tm.tm_mon = mm - 1;
    tm.tm_year = yy - 1900;

    t = mktime(&tm);
    return (int)t;
}


/*
 * @area: S FUNCTIONS
 * @function: date
 * @example: date('2016-11-05 03:14:59')
 * @example return: 2016-11-05
 * @description: returns the date only of  the date-like string
 * @parameters: (str)
 * @return: a text field
 */
char* _date(char* str) {
    int epoch = _strtotime(str);

    str = (char*)malloc(BUFSIZE);
    memset(str, 0, BUFSIZE);
    time_t t = (time_t)epoch;
    struct tm ts;
    ctime(&t);
    ts = *localtime(&t);
    strftime(str, sizeof(str)*sizeof(char*), "%Y-%m-%d", &ts);

    return str;
}


/*
 * @area: S FUNCTIONS
 * @function: timestamp
 * @example: timestamp('2016-11-05')
 * @example return: 2016-11-05 00:00:00
 * @description: returns the timestamp  the date-like string
 * @parameters: (str)
 * @return: a text field
 */
char* _timestamp(char* str) {
    int epoch = _strtotime(str);
    str = (char*)malloc(BUFSIZE);
    memset(str, 0, BUFSIZE);
    time_t t = (time_t)epoch;
    struct tm ts;
    ctime(&t);
    ts = *localtime(&t);
    strftime(str, sizeof(str)*sizeof(char*), "%Y-%m-%d %T", &ts);

    return str;
}

//inspired by 
//https://www.postgresql.org/docs/9.1/static/functions-datetime.html


/*
 * @area: S FUNCTIONS
 * @function: age
 * @example: age('2016-11-05 03:14:59', '2016-11-05')
 * @example return: 0 years 0 days 3 hours 14 minutes 59 seconds
 * @description: returns the difference of date-like times e1 and e2
 * the date-like string
 * @parameters: (e1, e2)
 * @return: a text field
 */
char* _age(char* timestamp1, char* timestamp2) {
    int e1 = _strtotime(timestamp1);
    int e2 = _strtotime(timestamp2);

    timestamp1 = (char*)malloc(MEDBUF);
    memset(timestamp1, 0, MEDBUF);

    int diff = e1 - e2;
    int negative = diff < 0 ? 1 : 0;
    int sec = 0, min = 0, hour = 0, dd = 0, yy = 0;

    if( negative ) {
        diff = -1 * diff;
    }

    sec = diff % 60;
    diff /= 60;
    min = diff % 60;
    diff /= 60;
    hour = diff % 24;
    diff /= 24;
    dd = diff % 365;
    diff /= 365;
    yy = diff;

    sprintf(timestamp1, "%s%d years %d days %d hours %d minutes %d seconds", negative?"-":"", yy, dd, hour, min, sec);


    return timestamp1;
}


/*
 * @area: S FUNCTIONS
 * @function: current_date
 * @example: current_date()
 * @example return: 2016-11-25
 * @description: returns the current date
 * @parameters: ()
 * @return: a text field
 */
char* _current_date() {
    return _date("");
}


/*
 * @area: S FUNCTIONS
 * @function: current_time
 * @example: current_time()
 * @example return: 14:33:32
 * @description: returns the current time
 * @parameters: ()
 * @return: a text field
 */
char* _current_time() {
    return _split_part(_timestamp(""), " ", 1);
}


/*
 * @area: S FUNCTIONS
 * @function: current_timestamp
 * @example: current_timestamp()
 * @example return: 2016-11-25 14:33:32
 * @description: returns the current timestamp
 * @parameters: ()
 * @return: a text field
 */
char* _current_timestamp() {
    return _timestamp("");
}


/*
 * @area: S FUNCTIONS
 * @function: date_part
 * @example: date_part('minute', '2016-11-25 14:33:32')
 * @example return: 33
 * @description: returns the piece of the timestamp specified as part; options are second, minute, hour, day, month, year, century, millenium, dow, doy
 * @parameters: (part, timestamp)
 * @return: a text field
 */
char* _date_part(char* part, char* timestamp) {
    char* tmp = _lower(part);
    swap(tmp, part);

    int epoch = _strtotime(timestamp);

//     char* buf = timestamp;
    time_t t = (time_t)epoch;
    struct tm ts;

    ctime(&t);

    ts = *localtime(&t);

    if( eq(part, SECOND) ) {
        strftime(timestamp, sizeof(timestamp), "%S", &ts);
    }
    else if(eq(part, MINUTE)) {
        strftime(timestamp, sizeof(timestamp), "%M", &ts);
    }
    else if(eq(part, HOUR)){
        strftime(timestamp, sizeof(timestamp), "%C", &ts);    
    }
    else if(eq(part, DAY)) {
        strftime(timestamp, sizeof(timestamp), "%d", &ts);
    }
    else if(eq(part, MONTH)) {
        strftime(timestamp, sizeof(timestamp), "%m", &ts);
    }
    else if(eq(part, YEAR)) {
        strftime(timestamp, sizeof(timestamp), "%Y", &ts);
    }
    else if(eq(part, CENTURY)) {
        strftime(timestamp, sizeof(timestamp), "%C", &ts);
    }
    else if(eq(part, DOW)) {
        sprintf(timestamp, "%d", (int)ts.tm_wday); 
    }
    else if(eq(part, DOY)) {
        strftime(timestamp, sizeof(timestamp), "%j", &ts);
    }
    else if(eq(part, MILLENIUM)) {
        strftime(timestamp, sizeof(timestamp), "%C", &ts);
        int m = (atoi(timestamp) / 1000) + 1;
        memset(timestamp, 0, BUFSIZE);
        sprintf(timestamp, "%d", m);    
    }
    else {
        return "";
    }
//     strcpy(timestamp, buf);

    return timestamp;
}


/*
 * @area: S FUNCTIONS
 * @function: date_trunc
 * @example: date_part('minute', '2016-11-25 14:33:32')
 * @example return: 2016-11-25 14:33:00
 * @description: returns the timestamp or date truncated at part; options are minute, hour, day, month, year
 * @parameters: (part, timestamp)
 * @return: a text field
 */
char* _date_trunc(char* part, char* timestamp) {
    int epoch = _strtotime(timestamp);
    struct tm ts = epoch_to_tm(epoch);
    char* buf = timestamp;
//     printf("Z: %s, %d\n", timestamp, epoch);

    if(eq(part, MINUTE)) {
        ts.tm_sec = 0;
        strftime(buf, sizeof(buf)*sizeof(char*), "%Y-%m-%d %T", &ts);
    }
    else if(eq(part, HOUR)){
        ts.tm_sec = 0;
        ts.tm_min = 0;
        strftime(buf, sizeof(buf)*sizeof(char*), "%Y-%m-%d %T", &ts);
    }
    else if(eq(part, DAY)) {
        ts.tm_sec = 0;
        ts.tm_min = 0;
        ts.tm_hour = 0;
        strftime(buf, sizeof(buf)*sizeof(char*), "%Y-%m-%d %T", &ts);
    }
    else if(eq(part, MONTH)) {
        ts.tm_sec = 0;
        ts.tm_min = 0;
        ts.tm_hour = 0;
        ts.tm_mday = 1;
        strftime(buf, sizeof(buf)*sizeof(char*), "%Y-%m-%d", &ts); 
    }
    else if(eq(part, YEAR)) {
        ts.tm_sec = 0;
        ts.tm_min = 0;
        ts.tm_hour = 0;
        ts.tm_mday = 1;
        ts.tm_mon = 0;
        strftime(buf, sizeof(buf)*sizeof(char*), "%Y-%m-%d", &ts);

    }
    strcpy(timestamp, buf);
//     printf("A: %s\n", timestamp);
    return timestamp;
}

//AGGREGATE FUNCTIONS
//===================
// Ideas from
// https://www.postgresql.org/docs/9.5/static/functions-aggregate.html
//Got the reg calculations from oracle's docs
//https://docs.oracle.com/cd/B28359_01/server.111/b28286/functions139.htm#SQLRF00696


/*
 * @area: A FUNCTIONS
 * @function: covar_samp
 * @example: covar_samp(expr1, expr2)
 * @description: returns the sample covariance of expr1 and expr2
 * @parameters: (expr1, expr2) both numeric
 * @return: double
 */
double covar_sample( SV* arr_ref ) {
    AV* a = (AV*)SvRV(arr_ref);
    int i;
    ssize_t n = av_tindex(a) + 1;
    if( n < 2 )
        return 0;
    int size = n / 2;
    int div = 0;

    double v, suma = 0, sumb = 0, meana, meanb, sos = 0;
    double A[size];
    double B[size];

    for(i=0;i<n;++i) {
        div = i/2;
        v = SvNV(*av_fetch(a, i, 0));
        if(i%2) {
            sumb += v;
            B[div] = v;
        }
        else {
            suma += v;
            A[div] = v;
        }
    }
    ++div;
    meana = suma / div;
    meanb = sumb / div;

    for(i=0;i<div;++i) {
        sos += (A[i] - meana) * (B[i] - meanb);
    }
    
    return sos / (div - 1);
}


/*
 * @area: A FUNCTIONS
 * @function: covar_pop
 * @example: covar_samp(expr1, expr2)
 * @description: returns the population covariance of expr1 and expr2
 * @parameters: (expr1, expr2) both numeric
 * @return: double
 */
double covar_population( SV* arr_ref ) {
    AV* a = (AV*)SvRV(arr_ref);
    int i;
    ssize_t n = av_tindex(a) + 1;
    if( n < 2 )
        return 0;
    int size = n / 2;
    int div = 0;

    double v, suma = 0, sumb = 0, meana, meanb, sos = 0;
    double A[size];
    double B[size];

    for(i=0;i<n;++i) {
        div = i/2;
        v = SvNV(*av_fetch(a, i, 0));
        if(i%2) {
            sumb += v;
            B[div] = v;
        }
        else {
            suma += v;
            A[div] = v;
        }
    }
    ++div;
    meana = suma / div;
    meanb = sumb / div;

    for(i=0;i<div;++i) {
        sos += (A[i] - meana) * (B[i] - meanb);
    }
    
    return sos / (div);
}


/*
 * @area: A FUNCTIONS
 * @function: var_samp
 * @example: var_samp(expr1)
 * @description: returns the sample variance of expr1
 * @parameters: (expr1) numeric
 * @return: double
 */
double var_sample(SV* arr_ref) {
    AV* a = (AV*)SvRV(arr_ref);
    int i;
    ssize_t n = av_tindex(a) + 1;
    if( n < 2 )
        return 0;
    
    double mu = 0;
    for(i=0;i<n;++i) {
        mu += SvNV(*av_fetch(a, i, 0));
    }
    mu /= (double)n;

    double sigma = 0;
    for(i=0;i<n;++i) {
        sigma += pow(SvNV(*av_fetch(a, i, 0)) - mu, 2);
    }
    sigma = sigma / (double)(n-1);
    return sigma;
}


/*
 * @area: A FUNCTIONS
 * @function: var_pop
 * @example: var_pop(expr1)
 * @description: returns the population variance of expr1
 * @parameters: (expr1) numeric
 * @return: double
 */
double var_population(SV* arr_ref) {
    AV* a = (AV*)SvRV(arr_ref);
    int i;
    ssize_t n = av_tindex(a) + 1;
    if( n < 2 )
        return 0;
    
    double mu = 0;
    for(i=0;i<n;++i) {
        mu += SvNV(*av_fetch(a, i, 0));
    }
    mu /= (double)n;

    double sigma = 0;
    for(i=0;i<n;++i) {
        sigma += pow(SvNV(*av_fetch(a, i, 0)) - mu, 2);
    }
    sigma = sigma / (double)(n);
    return sigma;
}

double cvar_population(double a[], int n) {
    int i;
    if( n < 2 )
        return 0;
    
    double mu = 0;
    for(i=0;i<n;++i) {
        mu += a[i];
    }
    mu /= (double)n;

    double sigma = 0;
    for(i=0;i<n;++i) {
        sigma += pow(a[i] - mu, 2);
    }
    sigma = sigma / (double)(n);
    return sigma;
}

double mean(double a[], int n) {
    int i;
    if( n < 2 )
        return 0;
    double sum = 0;
    for(i=0;i<n;++i) {
        sum += a[i];
    }
    return sum / n;
}


/*
 * @area: A FUNCTIONS
 * @function: regr_slope
 * @example: regr_slope(expr1, expr2)
 * @description: returns the slope of the line produced from expr1 and expr2
 * @parameters: (expr1, expr2) numeric
 * @return: double
 */
double regr_slope(SV* arr_ref) {
    AV* a = (AV*)SvRV(arr_ref);
    int i;
    ssize_t n = av_tindex(a) + 1;
    if( n < 2 )
        return 0;
    int size = n / 2;
    int div = 0;

    double B[size];

    for(i=0;i<n;++i) {
        div = i/2;
        if(i%2 == 0) {
            B[div] = SvNV(*av_fetch(a, i, 0));
        }
    }

    return covar_population(arr_ref) 
        / cvar_population(B, size);
}


/*
 * @area: A FUNCTIONS
 * @function: regr_count
 * @example: regr_count(expr1, expr2)
 * @description: returns the number of pairs in expr1 and expr2
 * @parameters: (expr1, expr2) numeric
 * @return: int
 */
int regr_count(SV* arr_ref) {
    AV* a = (AV*)SvRV(arr_ref);
    ssize_t n = av_tindex(a) + 1;
    return (int)n/2; 
}

//Non Helpers


/*
 * @area: A FUNCTIONS
 * @function: corr
 * @example: corr(expr1, expr2)
 * @description: returns the correlation constant produced from expr1 and expr2
 * @parameters: (expr1, expr2) numeric
 * @return: double
 */
double corr(SV* arr_ref) {
    AV* a = (AV*)SvRV(arr_ref);
    int i;
    ssize_t n = av_tindex(a) + 1;
    if( n < 2 )
        return 0;
    int size = n / 2;
    int div = 0;

    double xx[size];
    double yy[size];
    double v, xsum = 0, ysum = 0, xysum = 0, 
           xsqsum = 0, ysqsum = 0, num, deno, coeff;

    for(i=0;i<n;++i) {
        div = i/2;
        v = SvNV(*av_fetch(a, i, 0));
        if(i%2) {
            yy[div] = v;
            xsum += xx[div];
            ysum += yy[div];
            xysum += (xx[div] * yy[div]);
            xsqsum += (xx[div] * xx[div]);
            ysqsum += (yy[div] * yy[div]);
        }
        else {
            xx[div] = v;
        }
    }
    ++div;

	num = ((div * xysum) - (xsum * ysum));
	deno = ((div * xsqsum - xsum * xsum)* (div * ysqsum - ysum * ysum));

	coeff = num / sqrt(deno);

    return coeff;
}


/*
 * @area: A FUNCTIONS
 * @function: stddev_pop
 * @example: stddev_pop(expr1, expr2)
 * @description: returns the population standard deviation produced from expr1 and expr2
 * @parameters: (expr1, expr2) numeric
 * @return: double
 */
double stddev_population(SV* self) {
    double m, standardDeviation = 0.0;
    AV* a = (AV*)SvRV(self);
    int i;
    int n = (int)av_tindex(a) + 1;
    if( n < 2 )
        return 0;

    double data[n];
    for(i=0;i<n;++i){
        data[i] = SvNV(*av_fetch(a, i, 0));
    }
    m = mean(data, n);

    for(i=0; i<n; ++i)
        standardDeviation += pow(data[i] - m, 2);

    return sqrt(standardDeviation/(n));
}


/*
 * @area: A FUNCTIONS
 * @function: stddev_pop
 * @example: stddev_pop(expr1, expr2)
 * @description: returns the sample standard deviation produced from expr1 and expr2
 * @parameters: (expr1, expr2) numeric
 * @return: double
 */
double stddev_sample(SV* self) {
    double m, standardDeviation = 0.0;
    AV* a = (AV*)SvRV(self);
    int i;
    int n = (int)av_tindex(a) + 1;
    if( n < 2 )
        return 0;

    double data[n];
    for(i=0;i<n;++i){
        data[i] = SvNV(*av_fetch(a, i, 0));
    }
    m = mean(data, n);

    for(i=0; i<n; ++i)
        standardDeviation += pow(data[i] - m, 2);

    return sqrt(standardDeviation/(n-1));
}


/*
 * @area: A FUNCTIONS
 * @function: regr_avgx
 * @example: regr_avgx(expr1, expr2)
 * @description: returns the average of the dependent variable x or expr1
 * @parameters: (expr1, expr2) numeric
 * @return: double
 */
double regr_avgx(SV* self) {
    AV* a = (AV*)SvRV(self);
    int i;
    int n = regr_count(self);
    if( n < 1 )
        return 0;
    int div = 0;

    double B[n];

    for(i=0;i<n*2;++i) {
        div = i/2;
        if(i%2 == 0) {
            B[div] = SvNV(*av_fetch(a, i, 0));
        }
    }

    return mean(B, n);
}


/*
 * @area: A FUNCTIONS
 * @function: regr_avgy
 * @example: regr_avgy(expr1, expr2)
 * @description: returns the average of the independent variable y or expr2
 * @parameters: (expr1, expr2) numeric
 * @return: double
 */
double regr_avgy(SV* self) {
    AV* a = (AV*)SvRV(self);
    int i;
    int n = regr_count(self);
    if( n < 1 )
        return 0;
    int div = 0;

    double A[n];

    for(i=0;i<n*2;++i) {
        div = i/2;
        if(i%2 != 0) {
            A[div] = SvNV(*av_fetch(a, i, 0));
        }
    }

    return mean(A, n);
}


/*
 * @area: A FUNCTIONS
 * @function: regr_intercept
 * @example: regr_intercept(expr1, expr2)
 * @description: returns the y intercept of the equation produced from expr1 and wxpr2
 * @parameters: (expr1, expr2) numeric
 * @return: double
 */
double regr_intercept(SV* self) {
    AV* a = (AV*)SvRV(self);
    int i;
    ssize_t n = av_tindex(a) + 1;
    if( n < 2 )
        return 0;
    int size = n / 2;
    int div = 0;

    double A[size], B[size];

    for(i=0;i<n;++i) {
        div = i/2;
        if(i%2 != 0) {
            A[div] = SvNV(*av_fetch(a, i, 0));
        }
        else {
            B[div] = SvNV(*av_fetch(a, i, 0));
        }
    }
    return mean(A, size) - regr_slope(self) * mean(B, size);
}


/*
 * @area: A FUNCTIONS
 * @function: regr_sxx
 * @example: regr_sxx(expr1, expr2)
 * @description: returns the validates model, like all other implementations 
 * @parameters: (expr1, expr2) numeric
 * @return: double
 */
double regr_sxx(SV* self) {
    AV* a = (AV*)SvRV(self);
    int i;
    int n = regr_count(self);
    if( n < 1 )
        return 0;
    int div = 0;

    double B[n];

    for(i=0;i<n*2;++i) {
        div = i/2;
        if(i%2 == 0) {
            B[div] = SvNV(*av_fetch(a, i, 0));
        }
    }

    return n * cvar_population(B, n);
}


/*
 * @area: A FUNCTIONS
 * @function: regr_syy
 * @example: regr_syy(expr1, expr2)
 * @description: returns the validates model, like all other implementations 
 * @parameters: (expr1, expr2) numeric
 * @return: double
 */
double regr_syy(SV* self) {
    AV* a = (AV*)SvRV(self);
    int i;
    int n = regr_count(self);
    if( n < 1 )
        return 0;
    int div = 0;

    double A[n];

    for(i=0;i<n*2;++i) {
        div = i/2;
        if(i%2 != 0) {
            A[div] = SvNV(*av_fetch(a, i, 0));
        }
    }

    return n * cvar_population(A, n);
}


/*
 * @area: A FUNCTIONS
 * @function: regr_sxy
 * @example: regr_sxy(expr1, expr2)
 * @description: returns the validates model, like all other implementations 
 * @parameters: (expr1, expr2) numeric
 * @return: double
 */
double regr_sxy(SV* self) {
    int n = regr_count(self);
    if( n < 1 )
        return 0;

    return n * covar_population(self);
}

//SCIPY MATH FUNCTIONS
//====================
//FROM - https://docs.scipy.org/doc/numpy/reference/routines.math.html

//SFUNCTIONS
//==========

//MFUNCTIONS
//==========

/*
 * @area: M FUNCTIONS
 * @function: pi
 * @example: pi()
 * @example return: 3.14159265359
 * @description: returns pi
 * @parameters: () 
 * @return: double
 */
double _pi() {
    return 3.14159265359;
}


/*
 * @area: M FUNCTIONS
 * @function: e
 * @example: e()
 * @example return: 2.71828182846
 * @description: returns e
 * @parameters: () 
 * @return: double
 */
double _e() {
    return 2.71828182846;
}


/*
 * @area: M FUNCTIONS
 * @function: hypot
 * @example: hypot(3, 4)
 * @example return: 5
 * @description: returns the hypotenuse of sides s1 and s2
 * @parameters: (double s1, double s2)
 * @return: double
 */
double _hypot( double s1, double s2 ) {
    return sqrt( (s1*s1) + (s2*s2) );
}


/*
 * @area: M FUNCTIONS
 * @function: deg2rad
 * @example: deg2rad(360)
 * @example return: 6.28318530718 
 * @description: returns the radian representation of a number of degrees
 * @parameters: (double s1)
 * @return: double
 */
double _deg2rad( double s1 ) {
    return s1 * _pi() / 180;
}

/*
 * @area: M FUNCTIONS
 * @function: rad2deg
 * @example: rad2deg(deg2rad(360))
 * @example return: 360
 * @description: returns the degree representation of a number of randians
 * @parameters: (double s1)
 * @return: double
 */
double _rad2deg( double s1 ) {
    return 180 * s1 / _pi();
}

double _sin(double v) {
    return sin(v);
}

double _cos(double v) {
    return cos(v);
}

double _tan(double v) {
    return tan(v); 
}

double _arctan(double v) {
    return 1 / _tan(v);
}
double _arcsin(double v) {
    return 1 / _sin(v);
}
double _arccos(double v) {
    return 1 / _cos(v);
}
double _arctan2(double v1, double v2) {
    return atan2(v1, v2); 
}

double _sinh(double v) {
    return sinh(v);
}

double _cosh(double v) {
    return cosh(v);
}

double _tanh(double v) {
    return tanh(v);
}

double _arctanh(double v) {
    return 1 / _tanh(v);
}

double _arcsinh(double v) {
    return 1 / _sinh(v);
}

double _arccosh(double v) {
    return 1 / _cosh(v);
}

double _unwrap( double v ) {
    v = fmod(fabs(v), (2*_pi()));
    return v > _pi() ? -(2*_pi()) - v : v;
}

int _fix(double v){
    return (int)v;
}

int _floor(double v){
    return floor(v);
}

int _ceil(double v){
    return ceil(v);
}

int _trunc(double v){
   return trunc(v);
}

double _logaddexp(double c1, double c2){
    return log(exp(c1) + exp(c2));    
}

double _logaddexp2(double c1, double c2){
    return log2( exp2(c1) + exp2(c2) ); 
}

int _signbit(double v) {
    return v >= 0;
}

double _copysign(double v1, double v2){
    return v2 >= 0 ? fabs(v1) : -1 * fabs(v1);
}

double _clip(double v, double min, double max){
    return v <= max && v >= min ? v : ( v > max ? max : min );
}

double _exp(double v) {
    return exp(v);
}

double _expm1(double v) {
    return exp(v) - 1;
}

double _exp2(double v) {
    return pow(2,v);
}

double _exp10(double v) {
    return pow(10,v);
}

double _expn(int n, double v) {
    return pow(n,v);
}

double _frexp(double x, int exp){
    return frexp(x, &exp);
}

double _ldexp(double x, int exp){
    return ldexp(x, exp);
}

double _log(double x) {
    return log(x);
}

double _log10(double x) {
    return log10(x);
}

double _log2(double x) {
    return 1 / _exp2(x);
}

double _log1p(double x) {
    return 1+_log(x);
}

double _logn(int n, double v) {
    return 1 / _expn(n, v);
}
 

//AGGREGATES
//==========

double cprod(double* arr, int n) {
    double ret = 0;
    int i = 0;
    for(; i < n; ++i){
        ret *= arr[i];
    }
    return ret;
}

double csum(double* arr, int n) {
    double ret = 0;
    int i = 0;
    for(; i < n; ++i){
        ret += arr[i];
    }
    return ret;
}

double nansum(SV* self) {
    AV* a = (AV*)SvRV(self);
    int i;
    ssize_t n = av_tindex(a) + 1;
    double A[n];
    for(i=0;i<n;++i) {
        A[i] = SvNOK(*av_fetch(a, i, 0)) ? 
            SvNV(*av_fetch(a, i, 0)) : 0.0;
    }
    return csum(A, (int)n);
}

double nanprod(SV* self) {
    AV* a = (AV*)SvRV(self);
    int i;
    ssize_t n = av_tindex(a) + 1;
    double A[n];
    for(i=0;i<n;++i) {
        A[i] = SvNOK(*av_fetch(a, i, 0)) ? 
            SvNV(*av_fetch(a, i, 0)) : 1.0;
    }
    return cprod(A, (int)n);
}

double cumprod(SV* self) {
    AV* a = (AV*)SvRV(self);
    int i;
    ssize_t n = av_tindex(a) + 1;
    double A[n];
    for(i=0;i<n;++i) {
        A[i] = SvNV(*av_fetch(a, i, 0));
    }
    return cprod(A, (int)n);
}

double cumsum(SV* self) {
    AV* a = (AV*)SvRV(self);
    int i;
    ssize_t n = av_tindex(a) + 1;
    double A[n];
    for(i=0;i<n;++i) {
        A[i] = SvNV(*av_fetch(a, i, 0));
    }
    return csum(A, (int)n);
}



//SETS TODO 
//=========
// diff, ediff1d, gradient, cross, trapz
//i0, sinc
// interp

//UNKNOWN TODO
//angle, real, imag, conj
//convolve, 

...
}; # end package

%AliciaFuncs = (
    'libAlicia::_lower' => 1,
    'libAlicia::_upper' => 1,
    'libAlicia::_reverse' => 1,
    'libAlicia::_leftstr' => 2,
    'libAlicia::_rightstr' => 2,
    'libAlicia::_index' => 2,
    'libAlicia::_substr' => 3,
    'libAlicia::_uc_words' => 1,
    'libAlicia::_ascii' => 1,
    'libAlicia::_chr' => 1,
    'libAlicia::_btrim' => 2,
    'libAlicia::_rpad' => 3,
    'libAlicia::_lpad' => 3,
    'libAlicia::_replace' => 3,
    'libAlicia::_repeat' => 2,
    'libAlicia::_split_part' => 3,
    'libAlicia::_to_print' => 1,
    'libAlicia::_to_ascii' => 1,
    'libAlicia::_strtotime' => 1,
    'libAlicia::_date' => 1,
    'libAlicia::_timestamp' => 1,
    'libAlicia::_age' => 2,
    'libAlicia::_current_date' => 0,
    'libAlicia::_current_time' => 0,
    'libAlicia::_current_timestamp' => 0,
    'libAlicia::_date_part' => 2,
    'libAlicia::_date_trunc' => 2,
    'libAlicia::_e' => 0,
    'libAlicia::_pi' => 0,
    'libAlicia::_hypot' => 2,
    'libAlicia::_deg2rad' => 1,
    'libAlicia::_rad2deg' => 1,
    'libAlicia::_rad2deg' => 1,
    'libAlicia::_sin' => 1,
    'libAlicia::_cos' => 1,
    'libAlicia::_tan' => 1,
    'libAlicia::_sinh' => 1,
    'libAlicia::_cosh' => 1,
    'libAlicia::_tanh' => 1,
    'libAlicia::_arcsin' => 1,
    'libAlicia::_arccos' => 1,
    'libAlicia::_arctan' => 1,
    'libAlicia::_arctan2' => 2,
    'libAlicia::_arcsinh' => 1,
    'libAlicia::_arccosh' => 1,
    'libAlicia::_arctanh' => 1,
    'libAlicia::_unwrap' => 1,
    'libAlicia::_fix' => 1,
    'libAlicia::_floor' => 1,
    'libAlicia::_ceil' => 1,
    'libAlicia::_trunc' => 1,
    'libAlicia::_logaddexp' => 2,
    'libAlicia::_logaddexp2' => 2,
    'libAlicia::_signbit' => 1,
    'libAlicia::_copysign' => 2,
    'libAlicia::_clip' => 1,
    'libAlicia::_exp' => 1,
    'libAlicia::_expm1' => 1,
    'libAlicia::_exp2' => 1,
    'libAlicia::_exp10' => 1,
    'libAlicia::_frexp' => 2,
    'libAlicia::_ldexp' => 2,
    'libAlicia::_log' => 1,
    'libAlicia::_log10' => 1,
    'libAlicia::_log2' => 1,
    'libAlicia::_log1p' => 1,
    'libAlicia::_logn' => 2,
    'libAlicia::_expn' => 2,

);

%AliciaAggs = (
    Corr => 2,
    Covar_Samp => 2,
    Covar_Pop => 2,
    Regr_Avgx => 2,
    Regr_Avgy => 2,
    Regr_Count => 2,
    Regr_Slope => 2,
    Regr_Intercept => 2,
    Regr_Sxx => 2,
    Regr_Syy => 2,
    Regr_Sxy => 2,
    Stddev_Samp => 1,
    Stddev_Pop => 1,
    Var_Samp => 1,
    Var_Pop => 1,
    CumSum => 1,
    NanSum => 1,
    CumProd => 1,
    NanProd => 1
);

package Regr_Sxx {
    sub new { bless [], shift; }
    sub step { 
        my $self = shift; 
        push @$self, ($_[0]?$_[0]:0); 
        push @$self, ($_[1]?$_[1]:0);
    }
    sub finalize { libAlicia::regr_sxx($_[0]) }
};

package Regr_Syy {
    sub new { bless [], shift; }
    sub step { 
        my $self = shift; 
        push @$self, ($_[0]?$_[0]:0); 
        push @$self, ($_[1]?$_[1]:0);
    }
    sub finalize { libAlicia::regr_syy($_[0]) }
};

package Regr_Sxy {
    sub new { bless [], shift; }
    sub step { 
        my $self = shift; 
        push @$self, ($_[0]?$_[0]:0); 
        push @$self, ($_[1]?$_[1]:0);
    }
    sub finalize { libAlicia::regr_sxy($_[0]) }
};

package Regr_Slope {
    sub new { bless [], shift; }
    sub step { 
        my $self = shift; 
        push @$self, ($_[0]?$_[0]:0); 
        push @$self, ($_[1]?$_[1]:0);
    }
    sub finalize { libAlicia::regr_slope($_[0]) }
};

package Regr_Intercept {
    sub new { bless [], shift; }
    sub step { 
        my $self = shift; 
        push @$self, ($_[0]?$_[0]:0); 
        push @$self, ($_[1]?$_[1]:0);
    }
    sub finalize { libAlicia::regr_intercept($_[0]) }
};

package Regr_Count {
    sub new { bless [], shift; }
    sub step { 
        my $self = shift; 
        push @$self, ($_[0]?$_[0]:0); 
        push @$self, ($_[1]?$_[1]:0);
    }
    sub finalize{ libAlicia::regr_count($_[0]) }
};

package Var_Pop {
    sub new { bless [], shift; }
    sub step { push @{$_[0]}, $_[1] }
    sub finalize { libAlicia::var_population($_[0]) }
};

package Var_Samp{
    sub new { bless [], shift; }
    sub step { push @{$_[0]}, $_[1] }
    sub finalize { libAlicia::var_sample($_[0]) }
};

package Stddev_Samp {
    sub new { bless [], shift; }
    sub step { push @{$_[0]}, $_[1] }
    sub finalize { libAlicia::stddev_sample($_[0]) }
};

package Stddev_Pop {
    sub new { bless [], shift; }
    sub step { push @{$_[0]}, $_[1] }
    sub finalize { libAlicia::stddev_population($_[0]) }
};

package Corr {
    sub new { bless [], shift; }
    sub step { 
        my $self = shift; 
        push @$self, ($_[0]?$_[0]:0); 
        push @$self, ($_[1]?$_[1]:0);
    }
    sub finalize { libAlicia::corr($_[0]) }
};

package Covar_Pop {
    sub new { bless [], shift; }
    sub step { 
        my $self = shift; 
        push @$self, ($_[0]?$_[0]:0); 
        push @$self, ($_[1]?$_[1]:0);
    }
    sub finalize{ libAlicia::covar_population($_[0]) }
};

package Covar_Samp {
    sub new { bless [], shift; }
    sub step { 
        my $self = shift; 
        push @$self, ($_[0]?$_[0]:0); 
        push @$self, ($_[1]?$_[1]:0);
    }
    sub finalize{ libAlicia::covar_sample($_[0]) }
};

package Regr_Avgx {
    sub new { bless [], shift; }
    sub step { 
        my $self = shift; 
        push @$self, ($_[0]?$_[0]:0); 
        push @$self, ($_[1]?$_[1]:0);
    }
    sub finalize { libAlicia::regr_avgx($_[0]) }
};

package Regr_Avgy {
    sub new { bless [], shift; }
    sub step { 
        my $self = shift; 
        push @$self, ($_[0]?$_[0]:0); 
        push @$self, ($_[1]?$_[1]:0);
    }
    sub finalize { libAlicia::regr_avgy($_[0]) }
};


package CumSum {
    sub new { bless [], shift; }
    sub step { push @{$_[0]}, $_[1] }
    sub finalize { libAlicia::cumsum($_[0]) }
};

package NanSum {
    sub new { bless [], shift; }
    sub step { push @{$_[0]}, $_[1] }
    sub finalize { libAlicia::nansum($_[0]) }
};

package CumProd {
    sub new { bless [], shift; }
    sub step { push @{$_[0]}, $_[1] }
    sub finalize { libAlicia::cumprod($_[0]) }
};

package NanProd {
    sub new { bless [], shift; }
    sub step { push @{$_[0]}, $_[1] }
    sub finalize { libAlicia::nanprod($_[0]) }
};


