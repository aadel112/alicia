
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
    sto_ascii => 1,
    sstrtotime => 1,
    sdate => 1,
    stimestamp => 1,
    sage => 2,
    scurrent_date => 0,
    scurrent_time => 0,
    scurrent_timestamp => 0,
    sdate_part => 2,
    sdate_trunc => 2
);

%AliciaAggs = (
    Variance => 1,
    Corr => 2
);


use Inline C => << '...';

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
#define die exit(1)

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


//TODO fiz this, it'a modifying str
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

char *trim(char *str) {
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

    time(&t);

    ts = *localtime(&t);
    return ts;
}

//not ultra functional, in the sense that it's really not able to get too many formats right
int sstrtotime(char *s) {
    time_t t;
    struct tm tm;
    int dd, mm, yy;
    int hrs = 0, min = 0, sec = 0;

    //     printf("GOT %s\n", s);

    s = trim(s);
    int len = strlen(s);

    if( !len ) {
        return (int)time(NULL);
    }

    if( len == 10 && is_all_digits(s) ) {
        return atoi(s);
    }

    if(sscanf(s, "%4d-%2d-%2d %2d:%2d:%2d", &yy, &mm, &dd, &hrs, &min, &sec) == 6)
        goto okay;
    else if(sscanf(s, "%4d/%2d/%2d %2d:%2d:%2d", &yy, &mm, &dd, &hrs, &min, &sec) == 6)
        goto okay;
    else if(sscanf(s, "%2d/%2d/%4d %2d:%2d:%2d", &mm, &dd, &yy, &hrs, &min, &sec) == 6)
        goto okay;
    else if(sscanf(s, "%2d-%2d-%4d %2d:%2d:%2d", &mm, &dd, &yy, &hrs, &min, &sec) == 6)
        goto okay;
    else if(sscanf(s, "%4d-%2d-%2d", &yy, &mm, &dd) == 3)
        goto okay;
    else if(sscanf(s, "%4d/%2d/%2d", &yy, &mm, &dd) == 3)
        goto okay;
    else if(sscanf(s, "%2d/%2d/%4d", &mm, &dd, &yy) == 3)
        goto okay;
    else if(sscanf(s, "%2d-%2d-%4d", &mm, &dd, &yy) == 3)
        goto okay;

    return 0;

okay:
    //TODO - Do some sanity checking to rule out 2015-mar-35 and such

    //     printf("PARSED %d, %d, %d\n", yy, mm, dd);

    if( mm > 12 || dd > 31 ) {
        swap(dd, mm);
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

char* sdate(char* str) {
    int epoch = sstrtotime(str);

    //     char* buf = str + BUFSIZE * sizeof(char*);
    str = (char*)malloc(BUFSIZE);
    memset(str, 0, BUFSIZE);
    time_t t = (time_t)epoch;
    struct tm ts;

    time(&t);

    ts = *localtime(&t);
    strftime(str, sizeof(str)*sizeof(char*), "%Y-%m-%d", &ts);

    //     str = (char*)malloc(BUFSIZE * sizeof(char*));
    //     strcpy(str, buf);
    return str;
}

char* stimestamp(char* str) {
    int epoch = sstrtotime(str);
    //     char* buf = str;
    str = (char*)malloc(BUFSIZE);
    memset(str, 0, BUFSIZE);
    time_t t = (time_t)epoch;
    struct tm ts;

    time(&t);

    ts = *localtime(&t);
    strftime(str, sizeof(str)*sizeof(char*), "%Y-%m-%d %T", &ts);

    //BAD

    //     str = (char*)malloc(BUFSIZE * sizeof(char*));
    //     strcpy(str, buf);
    return str;
}

//inspired by 
//https://www.postgresql.org/docs/9.1/static/functions-datetime.html

char* sage(char* timestamp1, char* timestamp2) {
    int e1 = sstrtotime(timestamp1);
    int e2 = sstrtotime(timestamp2);

    timestamp1 = (char*)malloc(MEDBUF);
    memset(timestamp1, 0, MEDBUF);

    int diff = e1 - e2;
    int negative = diff < 0 ? 1 : 0;
    int sec = 0, min = 0, hour = 0, dd = 0, yy = 0;
    //     char* buf = timestamp1 + BUFSIZE;
    //     memset(buf, 0, BUFSIZE);

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

    //     strcpy(timestamp1, buf);
    //     free( buf );

    return timestamp1;
}

char* scurrent_date() {
    return sdate("");
}

char* scurrent_time() {
    return ssplit_part(stimestamp(""), " ", 1);
}

char* scurrent_timestamp() {
    return stimestamp("");
}

char* sdate_part(char* part, char* timestamp) {
    char* tmp = slower(part);
    swap(tmp, part);

    int epoch = sstrtotime(timestamp);

    char* buf = timestamp;
    //     char* buf = (char*)malloc(BUFSIZE);
    //     memset(buf, 0, BUFSIZE);
    time_t t = (time_t)epoch;
    struct tm ts;

    time(&t);

    ts = *localtime(&t);

    if( eq(part, SECOND) ) {
        strftime(buf, sizeof(buf), "%S", &ts);
    }
    else if(eq(part, MINUTE)) {
        strftime(buf, sizeof(buf), "%M", &ts);
    }
    else if(eq(part, HOUR)){
        strftime(buf, sizeof(buf), "%C", &ts);    
    }
    else if(eq(part, DAY)) {
        strftime(buf, sizeof(buf), "%d", &ts);
    }
    else if(eq(part, MONTH)) {
        strftime(buf, sizeof(buf), "%m", &ts);
    }
    else if(eq(part, YEAR)) {
        strftime(buf, sizeof(buf), "%Y", &ts);
    }
    else if(eq(part, CENTURY)) {
        strftime(buf, sizeof(buf), "%C", &ts);
    }
    else if(eq(part, DOW)) {
        sprintf(buf, "%d", (int)ts.tm_wday); 
    }
    else if(eq(part, DOY)) {
        strftime(buf, sizeof(buf), "%j", &ts);
    }
    else if(eq(part, MILLENIUM)) {
        strftime(buf, sizeof(buf), "%C", &ts);
        int m = (atoi(buf) / 1000) + 1;
        memset(buf, 0, BUFSIZE);
        sprintf(buf, "%d", m);    
    }
    else {
        return "";
    }
    strcpy(timestamp, buf);

    return timestamp;
}

char* sdate_trunc(char* part, char* timestamp) {
    int epoch = sstrtotime(timestamp);
    struct tm ts = epoch_to_tm(epoch);
    //     char* buf[BUFSIZE];
    char* buf = timestamp;
    //     memset(buf, 0, BUF);

    //     int dayepoch = epoch / (24*3600);
    //     dayepoch *= (24*3600);
    // 
    //     char* buf = (char*)malloc(BUFSIZE);
    //     memset(buf, 0, BUFSIZE);

    if(eq(part, MINUTE)) {
        ts.tm_sec = 0;
        strftime(buf, sizeof(buf)*sizeof(char*), "%Y-%m-%d %T", &ts);
        //         epoch /= 60;
        //         epoch *= 60;
        //         sprintf(part, "%d", epoch);
        //         return stimestamp(part);
    }
    else if(eq(part, HOUR)){
        ts.tm_sec = 0;
        ts.tm_min = 0;
        strftime(buf, sizeof(buf)*sizeof(char*), "%Y-%m-%d %T", &ts);
        //         epoch /= 3600;
        //         epoch *= 3600;
        //         sprintf(part, "%d", epoch);
        //         return stimestamp(part);
    }
    else if(eq(part, DAY)) {
        ts.tm_sec = 0;
        ts.tm_min = 0;
        ts.tm_hour = 0;
        strftime(buf, sizeof(buf)*sizeof(char*), "%Y-%m-%d %T", &ts);
        //         epoch = dayepoch;
        //         sprintf(part, "%d", epoch);
        //         strcpy(timestamp, part);
        //         memset(part, 0, partSIZE);
        //         sprintf(part, "%s-%s-%s", sdate_buf(YEAR, sdate(part)), sdate_buf(MONTH, sdate(part)), sdate_buf(DAY, sdate(part)) );
        //         return part;
    }
    else if(eq(part, MONTH)) {
        ts.tm_sec = 0;
        ts.tm_min = 0;
        ts.tm_hour = 0;
        ts.tm_mday = 1;
        strftime(buf, sizeof(buf)*sizeof(char*), "%Y-%m-%d", &ts); 
        //         epoch = dayepoch;
        //         sprintf(part, "%d", epoch);
        //         strcpy(timestamp, part);
        //         memset(part, 0, partSIZE);
        //         sprintf(part, "%s-%s-01", sdate_buf(YEAR, sdate(part)), sdate_buf(MONTH, sdate(part)));
        //         return part;
    }
    else if(eq(part, YEAR)) {
        ts.tm_sec = 0;
        ts.tm_min = 0;
        ts.tm_hour = 0;
        ts.tm_mday = 1;
        ts.tm_mon = 0;
        strftime(buf, sizeof(buf)*sizeof(char*), "%Y-%m-%d", &ts);

        //         epoch = dayepoch;
        //         sprintf(part, "%d", epoch);
        //         strcpy(timestamp, part);
        //         memset(part, 0, partSIZE);
        //         sprintf(part, "%s-01-01", sdate_buf(YEAR, sdate(part)) );
        //         return part;
    }
    strcpy(timestamp, buf);
    return timestamp;
}

//AGGREGATE FUNCTIONS
//===================
// Ideas from
// https://www.postgresql.org/docs/9.5/static/functions-aggregate.html
...
do 'lib/Variance.c';
do 'lib/Corr.c';

