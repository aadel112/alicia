libAlicia.c
-----------

These methods extend Alicia to provide it with more functions from other databases.

Area|Function|Description|Parameters|Example|Example Return
-----|--------|-----------|-------------|----------|-----------
*S FUNCTIONS*|**lower**|Converts A field to all lower case text|a text field|`lower('HELLO')`|hello
*S FUNCTIONS*|**upper**|Converts A field to all upper case text|a text field|`upper('hello')`|HELLO
*S FUNCTIONS*|**reverse**|Converts A field to the same text reversed|a text field|`reverse('hello')`|olleh
*S FUNCTIONS*|**leftstr**|returns the left len characters|(str, len)|`leftstr('hello', 2)`|he
*S FUNCTIONS*|**rightstr**|returns the right len characters from the string str|(str, len)|`rightstr('hello', 2)`|lo
*S FUNCTIONS*|**index**|returns the 0 based index if the needle in haystack if it exists, else -1|(haystack, needle)|`index('hello', 'll')`|2
*S FUNCTIONS*|**substr**|returns the portion of the string from start for len characters, 0-based.|(str, start, len)|`substr('hello', 0, 3)`|hel
*S FUNCTIONS*|**uc_words**|returns the text field with words beginnings upper cased.|(str)|`uc_words('hello world')`|Hello World
*S FUNCTIONS*|**ascii**|returns the ascii decimal value of the character passed|(c)|`ascii('A')`|65
*S FUNCTIONS*|**chr**|returns the ascii char corresponding to int n|(n)|`chr(65)`|A
*S FUNCTIONS*|**btrim**|returns str with all of the characters in chars removed|(str, chars)|`btrim('xxaxybcxxy', 'xy')`|abc
*S FUNCTIONS*|**rpad**|returns str right-padded with fill repeatedly until it reaches length len|(str, len, fill)|`rpad('x', 5, 'yz')`|xyzyz
*S FUNCTIONS*|**lpad**|returns str left-padded with fill repeatedly until it reaches length len|(str, len, fill)|`lpad('x', 5, 'yz')`|yzyzx
*S FUNCTIONS*|**replace**|returns orig where rep is replaced with with|(orig, rep, with)|`replace('hello world', 'world', 'universe')`|hello universe
*S FUNCTIONS*|**repeat**|returns str repeated n times|(str, n)|`repeat('abc', 3)`|abcabcabc
*S FUNCTIONS*|**split_part**|returns the 0-based field from  str split on delim|(str, delim, field)|`split_part('hello world', ' ', 1)`|world
*S FUNCTIONS*|**to_print**|returns the str with all non-printing characters removed|(str)|`to_print('hello\nworld)`|helloworld
*S FUNCTIONS*|**to_ascii**|returns the str with all non-ascii characters removed|(str)|`to_ascii('hello˚, ˳world')`|helloworld
*S FUNCTIONS*|**_strtotime**|not super functional, needs to be  coded out more. Only accepts 6 formats,  and epoch times|(str)|`_strtotime('2016-11-05 03:14:59')`|1478315699
*S FUNCTIONS*|**date**|returns the date only of  the date-like string|(str)|`date('2016-11-05 03:14:59')`|2016-11-05
*S FUNCTIONS*|**timestamp**|returns the timestamp  the date-like string|(str)|`timestamp('2016-11-05')`|2016-11-05 00:00:00
*S FUNCTIONS*|**age**|returns the difference of date-like times e1 and e2|(e1, e2)|`age('2016-11-05 03:14:59', '2016-11-05')`|0 years 0 days 3 hours 14 minutes 59 seconds
*S FUNCTIONS*|**current_date**|returns the current date|()|`current_date()`|2016-11-25
*S FUNCTIONS*|**current_time**|returns the current time|()|`current_time()`|14:33:32
*S FUNCTIONS*|**current_timestamp**|returns the current timestamp|()|`current_timestamp()`|2016-11-25 14:33:32
*S FUNCTIONS*|**date_part**|returns the piece of the timestamp specified as part; options are second, minute, hour, day, month, year, century, millenium, dow, doy|(part, timestamp)|`date_part('minute', '2016-11-25 14:33:32')`|33
*S FUNCTIONS*|**date_trunc**|returns the timestamp or date truncated at part; options are minute, hour, day, month, year|(part, timestamp)|`date_part('minute', '2016-11-25 14:33:32')`|2016-11-25 14:33:00
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
*M FUNCTIONS*|**pi**|returns pi|()|`pi()`|3.14159265358979
*M FUNCTIONS*|**e**|returns e|()|`e()`|2.71828182845905
*M FUNCTIONS*|**hypot**|returns the hypotenuse of sides s1 and s2|(double s1, double s2)|`hypot(3, 4)`|5
*M FUNCTIONS*|**deg2rad**|returns the radian representation of a number of degrees|(double s1)|`deg2rad(360) / pi()`|2
*M FUNCTIONS*|**rad2deg**|returns the degree representation of a number of randians|(double s1)|`rad2deg(2*pi())`|360
*M FUNCTIONS*|**sin**|returns the sine of s1|(double s1)|`round(sin(2*pi()),10)`|0
*M FUNCTIONS*|**cos**|returns the cosine of s1|(double s1)|`round(cos(2*pi()),10)`|1
*M FUNCTIONS*|**tan**|returns the tangent of s1|(double s1)|`round(tan(2*pi()),10)`|0
*M FUNCTIONS*|**arctan**|returns the archtan of s1|(double s1)|`round(arctan(-1),10)`|-0.7853981634
*M FUNCTIONS*|**arcsin**|returns the archsin of s1|(double s1)|`round(arcsin(-1),10)`|-1.5707963268
*M FUNCTIONS*|**arcsin**|returns the archcos of s1|(double s1)|`round(arccos(-1),10)`|3.1415926536
*M FUNCTIONS*|**arctan2**|returns atan2 of s1 and s2|(double s1, double s2)|`round(arctan2(-1,1),10)`|-0.7853981634
*M FUNCTIONS*|**sinh**|returns the hyperbolic sine of s1|(double s1)|`round(sinh(2*pi()),10)`|267.744894041
*M FUNCTIONS*|**cosh**|returns the hyperbolic cosine of s1|(double s1)|`round(cosh(2*pi()),10)`|267.744894041
*M FUNCTIONS*|**tanh**|returns the hyperbolic tangent of s1|(double s1)|`round(tanh(2*pi()),10)`|0.9999930253
*M FUNCTIONS*|**arctanh**|returns the hyperbolic arctan of s1|(double s1)|`round(arctanh(2*pi()),10)`|1.0000069747
*M FUNCTIONS*|**arctanh**|returns the hyperbolic arcsin of s1|(double s1)|`round(arcsinh(2*pi()),10)`|0.0037348985
*M FUNCTIONS*|**arccosh**|returns the hyperbolic arccos of s1|(double s1)|`round(arccosh(2*pi()),10)`|0.0037348724
*M FUNCTIONS*|**unwrap**|returns the value if it's less than or equal to pi, else the 2pi - the value mod 2pi|(double s1)|`unwrap(8)`|1.71681469282041
*M FUNCTIONS*|**fix**|returns the int value of s1|(double s1)|`fix(-8.1)`|-8
*M FUNCTIONS*|**floor**|returns the floor of s1|(double s1)|`floor(-8.1)`|-9
*M FUNCTIONS*|**ceil**|returns the ceil of s1|(double s1)|`ceil(8.1)`|9
*M FUNCTIONS*|**trunc**|returns the value of s1 with its decimal digits removed|(double s1)|`trunc(8.1)`|8
*M FUNCTIONS*|**logaddexp**|returns log(exp(c1) + exp(c2))|(double c1, double c2)|`logaddexp(e(), pi())`|3.64531816098924
*M FUNCTIONS*|**logaddexp2**|returns log2(exp2(c1) + exp2(c2))|(double c1, double c2)|`logaddexp2(e(), pi())`|3.94540767250265
*M FUNCTIONS*|**signbit**|returns 1 if v >= 0 else 0|(double v)|`signbit(-e())`|0
*M FUNCTIONS*|**copysign**|returns v1 with the sign of v2|(double v1, double v2)|`copysign(8,-1)`|-8
*M FUNCTIONS*|**clip**|returns min if v is less than min, max if v is greater than max, else v|(double v, double min, double max)|`clip(8,-1, 1)`|1

To go along with these features there is also built-in regex and json support through the official sqlite extensions.
