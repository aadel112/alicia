use Inline C => << '...';

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
...

%AliciaCore = (
    lower => 1,
    upper => 1
);

