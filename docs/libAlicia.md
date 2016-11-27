libAlicia.c
-----------

These methods extend Alicia to provide it with more functions from other databases.

Area|Function|Description|Parameters|Example|Example Return
-----|--------|-----------|-------------|----------|-----------
*S FUNCTIONS*|**slower**|Converts A field to all lower case text|a text field|`slower('HELLO')`|hello
*S FUNCTIONS*|**supper**|Converts A field to all upper case text|a text field|`supper('hello')`|HELLO
*S FUNCTIONS*|**sreverse**|Converts A field to the same text reversed|a text field|`sreverse('hello')`|olleh
*S FUNCTIONS*|**sleft**|returns the left len characters|(str, len)|`sleft('hello', 2)`|he
*S FUNCTIONS*|**sright**|returns the right len characters from the string str|(str, len)|`sright('hello', 2)`|lo
*S FUNCTIONS*|**sindex**|returns the 0 based index if the needle in haystack if it exists, else -1|(haystack, needle)|`sindex('hello', 'll')`|2
*S FUNCTIONS*|**ssubstr**|returns the portion of the string from start for len characters, 0-based.|(str, start, len)|`ssubstr('hello', 0, 3)`|hel
*S FUNCTIONS*|**suc_words**|returns the text field with words beginnings upper cased.|(str)|`suc_words('hello world')`|Hello World
*S FUNCTIONS*|**sascii**|returns the ascii decimal value of the character passed|(c)|`sascii('A')`|65
*S FUNCTIONS*|**schr**|returns the ascii char corresponding to int n|(n)|`schr(65)`|A
*S FUNCTIONS*|**sbtrim**|returns str with all of the characters in chars removed|(str, chars)|`sbtrim('xxaxybcxxy', 'xy')`|abc
*S FUNCTIONS*|**srpad**|returns str right-padded with fill repeatedly until it reaches length len|(str, len, fill)|`srpad('x', 5, 'yz')`|xyzyz
*S FUNCTIONS*|**slpad**|returns str left-padded with fill repeatedly until it reaches length len|(str, len, fill)|`slpad('x', 5, 'yz')`|yzyzx
*S FUNCTIONS*|**sreplace**|returns orig where rep is replaced with with|(orig, rep, with)|`sreplace('hello world', 'world', 'universe')`|hello universe
*S FUNCTIONS*|**srepeat**|returns str repeated n times|(str, n)|`srepeat('abc', 3)`|abcabcabc
*S FUNCTIONS*|**ssplit_part**|returns the 0-based field from  str split on delim|(str, delim, field)|`ssplit_part('hello world', ' ', 1)`|world
*S FUNCTIONS*|**sto_print**|returns the str with all non-printing characters removed|(str)|`sto_print('hello\nworld)`|helloworld
*S FUNCTIONS*|**sto_ascii**|returns the str with all non-ascii characters removed|(str)|`sto_ascii('hello˚, ˳world')`|helloworld
*S FUNCTIONS*|**sstrtotime**|not super functional, needs to be  coded out more. Only accepts 6 formats,  and epoch times|(str)|`sstrtotime('2016-11-05 03:14:59')`|1478315699
*S FUNCTIONS*|**sdate**|returns the date only of  the date-like string|(str)|`sstrtotime('2016-11-05 03:14:59')`|2016-11-05
*S FUNCTIONS*|**stimestamp**|returns the timestamp  the date-like string|(str)|`stimestamp('2016-11-05')`|2016-11-05 00:00:00
*S FUNCTIONS*|**sage**|returns the difference of date-like times e1 and e2|(e1, e2)|`sage('2016-11-05 03:14:59', '2016-11-05')`|0 years 0 days 3 hours 14 minutes 59 seconds
*S FUNCTIONS*|**scurrent_date**|returns the current date|()|`scurrent_date()`|2016-11-25
*S FUNCTIONS*|**scurrent_time**|returns the current time|()|`scurrent_time()`|14:33:32
*S FUNCTIONS*|**scurrent_timestamp**|returns the current timestamp|()|`scurrent_timestamp()`|2016-11-25 14:33:32
*S FUNCTIONS*|**sdate_part**|returns the piece of the timestamp specified as part; options are second, minute, hour, day, month, year, century, millenium, dow, doy|(part, timestamp)|`sdate_part('minute', '2016-11-25 14:33:32')`|33
*S FUNCTIONS*|**sdate_trunc**|returns the timestamp or date truncated at part; options are minute, hour, day, month, year|(part, timestamp)|`sdate_part('minute', '2016-11-25 14:33:32')`|2016-11-25 14:33:00
*A FUNCTIONS*|**covar_samp**|returns the sample covariance of expr1 and expr2|(expr1, expr2) both numeric|`covar_samp(expr1, expr2)`
*A FUNCTIONS*|**covar_pop**|returns the population covariance of expr1 and expr2|(expr1, expr2) both numeric|`covar_samp(expr1, expr2)`
*A FUNCTIONS*|**var_samp**|returns the sample variance of expr1|(expr1) numeric|`var_samp(expr1)`
*A FUNCTIONS*|**var_pop**|returns the population variance of expr1|(expr1) numeric|`var_pop(expr1)`
*A FUNCTIONS*|**regr_slope**|returns the slope of the line produced from expr1 and expr2|(expr1, expr2) numeric|`regr_slope(expr1, expr2)`
*A FUNCTIONS*|**regr_count**|returns the number of pairs in expr1 and expr2|(expr1, expr2) numeric|`regr_count(expr1, expr2)`
*A FUNCTIONS*|**corr**|returns the correlation constant produced from expr1 and expr2|(expr1, expr2) numeric|`corr(expr1, expr2)`
*A FUNCTIONS*|**stddev_pop**|returns the population standard deviation produced from expr1 and expr2|(expr1, expr2) numeric|`stddev_pop(expr1, expr2)`
*A FUNCTIONS*|**stddev_pop**|returns the sample standard deviation produced from expr1 and expr2|(expr1, expr2) numeric|`stddev_pop(expr1, expr2)`
*A FUNCTIONS*|**regr_avgx**|returns the average of the dependent variable x or expr1|(expr1, expr2) numeric|`regr_avgx(expr1, expr2)`
*A FUNCTIONS*|**regr_avgy**|returns the average of the independent variable y or expr2|(expr1, expr2) numeric|`regr_avgy(expr1, expr2)`
*A FUNCTIONS*|**regr_intercept**|returns the y intercept of the equation produced from expr1 and wxpr2|(expr1, expr2) numeric|`regr_intercept(expr1, expr2)`
*A FUNCTIONS*|**regr_sxx**|returns the validates model, like all other implementations|(expr1, expr2) numeric|`regr_sxx(expr1, expr2)`
*A FUNCTIONS*|**regr_syy**|returns the validates model, like all other implementations|(expr1, expr2) numeric|`regr_syy(expr1, expr2)`
*A FUNCTIONS*|**regr_sxy**|returns the validates model, like all other implementations|(expr1, expr2) numeric|`regr_sxy(expr1, expr2)`

To go along with these features there is also built-in regex and json support through the official sqlite extensions.
