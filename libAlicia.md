<table>
<colgroup>
<col width="100%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left"><div id="projectname">
Alicia  <span id="projectnumber">0.01</span>
</div>
<div id="projectbrief">
Doyouhaveanunhealthyloveofsqlandwishyoucoulddevelopeverythinginit?Wellnowyoucan.Aliciaaimstoprovideultrahighspeeddatacalculations,alongwithallofthefunctionalityoftop-flightdatabasessuchaspostgresql.Itrunsasasingleinstanceofsqlitein-memory,withallconcurrencyprotectionsofftoprovideitevenmorespeedasasinglethreadedapplication.Becauseitssqlite,thedataishyper-compressed.Infactyou'llfindprogramsyou\'vewritteninotherhigh-levellanguageswilltakethousandsoftimestheamountofmemory.andstillrunmuchmoreslowly.Especiallywithproperindexing.AlloftheextendedfinctionsarewritteninC,asissqliteitself.Ifyou,theuserwanttoaddanotherfunction,thistooisabreezetodo.
</div></td>
</tr>
</tbody>
</table>

-   [<span>Main Page</span>](index.html)
-   [<span>Files</span>](files.html)
-   <span class="left"> <img src="search/mag_sel.png" id="MSearchSelect" /> </span><span class="right"> <a href="javascript:searchBox.CloseResultsWindow()" id="MSearchClose"><img src="search/close.png" id="MSearchCloseImg" /></a> </span>

-   [<span>File List</span>](files.html)
-   [<span>Globals</span>](globals.html)

[Macros](#define-members) | [Functions](#func-members) | [Variables](#var-members)

libAlicia.c File Reference

[]() Macros
-----------

\#define 
<a href="libAlicia_8c.html#a369180e5e0a23addbc2a6a9e24fee590" class="el">swap</a>(x, y)
 
\#define 
<a href="libAlicia_8c.html#a4c9ae5d808e2562483ca8e5282d26fc8" class="el">eq</a>(a, b)   !strcmp(a,b)
 
\#define 
<a href="libAlicia_8c.html#a2792e9deb49be0bc37ba0b81a6d8ebb2" class="el">die</a>   exit(1)
 
\#define 
<a href="libAlicia_8c.html#a94212be2394d2d37d9dfd33d07d82dba" class="el">SECOND</a>   "second"
 
\#define 
<a href="libAlicia_8c.html#ac1454fa04f41c693f39425697a137d82" class="el">MINUTE</a>   "minute"
 
\#define 
<a href="libAlicia_8c.html#a4698ae12cf6a8acb5886fffd0ec897e6" class="el">HOUR</a>   "hour"
 
\#define 
<a href="libAlicia_8c.html#a509a01c55cbe47386fe24602b7c7fda1" class="el">DAY</a>   "day"
 
\#define 
<a href="libAlicia_8c.html#a3729d06495d9713592f79f3122c9e677" class="el">MONTH</a>   "month"
 
\#define 
<a href="libAlicia_8c.html#a5871356500f559add06ea81d60331b1b" class="el">YEAR</a>   "year"
 
\#define 
<a href="libAlicia_8c.html#a82156999d58c7a1ae01480ee67a3f417" class="el">CENTURY</a>   "century"
 
\#define 
<a href="libAlicia_8c.html#a9d21648a758cb23b074808186e95692f" class="el">DOW</a>   "dow"
 
\#define 
<a href="libAlicia_8c.html#ae2f2a5b452584dec223ab0a050c11e8d" class="el">DOY</a>   "doy"
 
\#define 
<a href="libAlicia_8c.html#a25ed60bfa916205abc4fd6aa9e23804d" class="el">MILLENIUM</a>   "millenium"
 
\#define 
<a href="libAlicia_8c.html#aeca034f67218340ecb2261a22c2f3dcd" class="el">BUFSIZE</a>   80
 
\#define 
<a href="libAlicia_8c.html#a0ca0ee8ea801d2d3ce712d4644a8f186" class="el">MEDBUF</a>   1024
 
\#define 
<a href="libAlicia_8c.html#a1d074c0b0cf82b5e84a269acc5af96b6" class="el">QLNV</a>(l, i)   (SvNOK(\*av\_fetch(l, i, 0)) ? ((double)SvNV(\*av\_fetch(l, i, 0))) : 0)
 
[]() Functions
--------------

char \* 
<a href="libAlicia_8c.html#aa3fe51647c6fd75aff0d6df508e664bf" class="el">slower</a> (char \*str)
 
char \* 
<a href="libAlicia_8c.html#a7d25b31c850ea3535c0452a21ea14da4" class="el">supper</a> (char \*str)
 
char \* 
<a href="libAlicia_8c.html#a194dd20df46e91275e5d5646c5733964" class="el">sreverse</a> (char \*str)
 
char \* 
<a href="libAlicia_8c.html#a4d73f0077da0ccfc8ca53cd6d2258fd0" class="el">sleft</a> (char \*str, int len)
 
char \* 
<a href="libAlicia_8c.html#ae26b99f4bcecb788bb125e7ae7c742cc" class="el">sright</a> (char \*str, int len)
 
int 
<a href="libAlicia_8c.html#a4bb39f69d4f93fcad3135d2e2e749894" class="el">sindex</a> (char \*haystack, char \*needle)
 
char \* 
<a href="libAlicia_8c.html#ac56033dd2efa609363d0e91335cd5f26" class="el">ssubstr</a> (char \*str, int start, int len)
 
char \* 
<a href="libAlicia_8c.html#ac75b72da906ff7d032c900561c9cbaef" class="el">suc_words</a> (char \*str)
 
int 
<a href="libAlicia_8c.html#ac4c1bb37bd56ff9f45167bfbff0638e5" class="el">sascii</a> (char c)
 
char 
<a href="libAlicia_8c.html#aeff4d7480f5038987166e9358ee87591" class="el">schr</a> (int n)
 
char \* 
<a href="libAlicia_8c.html#ad487bfc81dd42b1d2d52f504229dad26" class="el">sbtrim</a> (char \*str, char \*chars)
 
char \* 
<a href="libAlicia_8c.html#a23ffec05dc4a6650f75d17160622599d" class="el">srpad</a> (char \*str, int len, char \*fill)
 
char \* 
<a href="libAlicia_8c.html#a8771cc5890b27e14ea609c17c227def2" class="el">slpad</a> (char \*str, int len, char \*fill)
 
char \* 
<a href="libAlicia_8c.html#a6a840b0f0328da7f239648cb0cc973d1" class="el">sreplace</a> (char \*orig, char \*rep, char \*with)
 
char \* 
<a href="libAlicia_8c.html#a4392af20697468de64c484e1d00a934e" class="el">srepeat</a> (char \*str, int n)
 
char \* 
<a href="libAlicia_8c.html#a527f08686272dbafebb08ab451289c9b" class="el">ssplit_part</a> (char \*str, char \*delim, int field)
 
char \* 
<a href="libAlicia_8c.html#a02998dd0e355f69144f809f33766a741" class="el">sto_print</a> (char \*str)
 
char \* 
<a href="libAlicia_8c.html#a1a623fd0bdbbb965484ce4d98fd115f1" class="el">sto_ascii</a> (char \*str)
 
int 
<a href="libAlicia_8c.html#a1d2738b5bc0a88c5f221b76e2c82da3e" class="el">strtomonth</a> (int \*mm, const char \*str)
 
int 
<a href="libAlicia_8c.html#a00ecd456f7e5012745d9c9781b00faae" class="el">is_all_digits</a> (char \*str)
 
char \* 
<a href="libAlicia_8c.html#a06798d058792d39a2eb6f3b784ae1532" class="el">trim</a> (char \*str)
 
struct tm 
<a href="libAlicia_8c.html#a40a8323b6333f9e474c4854a9e84ab3d" class="el">epoch_to_tm</a> (int epoch)
 
int 
<a href="libAlicia_8c.html#aa0d3f3dcb77d40e08f78642eabe1807b" class="el">sstrtotime</a> (char \*s)
 
char \* 
<a href="libAlicia_8c.html#a907609a144ae91d1ca85bca2b2688126" class="el">sdate</a> (char \*str)
 
char \* 
<a href="libAlicia_8c.html#a3767b8dda41af0b04049d75f63de3180" class="el">stimestamp</a> (char \*str)
 
char \* 
<a href="libAlicia_8c.html#a8b61aed8eaa037bbe98049949587631a" class="el">sage</a> (char \*timestamp1, char \*timestamp2)
 
char \* 
<a href="libAlicia_8c.html#aa80e2ef043dcfcdd4776f95d27eff7fd" class="el">scurrent_date</a> ()
 
char \* 
<a href="libAlicia_8c.html#a5d6bb20e72d506e3e5f5366fe9d6c938" class="el">scurrent_time</a> ()
 
char \* 
<a href="libAlicia_8c.html#a37da7b5424e3f72378afd69e6e91718b" class="el">scurrent_timestamp</a> ()
 
char \* 
<a href="libAlicia_8c.html#a650fe63670c4904ea0f4327d508d258e" class="el">sdate_part</a> (char \*part, char \*timestamp)
 
char \* 
<a href="libAlicia_8c.html#a7a22ebb746fe2faeb77f3ea4f0357788" class="el">sdate_trunc</a> (char \*part, char \*timestamp)
 
double 
<a href="libAlicia_8c.html#add787d1ac835ed79c1baf4621c65da26" class="el">covar_sample</a> (SV \*arr\_ref)
 
double 
<a href="libAlicia_8c.html#ac1d38a2bd804f13ddc5156ebf97d917e" class="el">covar_population</a> (SV \*arr\_ref)
 
double 
<a href="libAlicia_8c.html#a12e7735a0fdc3fe5270e87969d224fec" class="el">var_sample</a> (SV \*arr\_ref)
 
double 
<a href="libAlicia_8c.html#aab936461bf91782c8ba9547c5efda4f6" class="el">var_population</a> (SV \*arr\_ref)
 
double 
<a href="libAlicia_8c.html#ad352d52a0f33bee47bcaf57fa1180c5f" class="el">cvar_population</a> (double a\[\], int n)
 
double 
<a href="libAlicia_8c.html#aff57a3637f3b23839ee1de27ce507426" class="el">mean</a> (double a\[\], int n)
 
double 
<a href="libAlicia_8c.html#a728959ac8df5363e40b27e78a073dd60" class="el">regr_slope</a> (SV \*arr\_ref)
 
int 
<a href="libAlicia_8c.html#a80094d0198f5f421f9faed34ec7548dd" class="el">regr_count</a> (SV \*arr\_ref)
 
double 
<a href="libAlicia_8c.html#acf05c56e48d78d25d39e8b8f74d0816d" class="el">corr</a> (SV \*arr\_ref)
 
double 
<a href="libAlicia_8c.html#aa54cbaed0a9bfe89fd282c43654b82ae" class="el">stddev_population</a> (SV \*self)
 
double 
<a href="libAlicia_8c.html#ac86d50f62b28522eb837caccdb817f45" class="el">stddev_sample</a> (SV \*self)
 
double 
<a href="libAlicia_8c.html#a8bf44e0166731499c06e286e02a0fa81" class="el">regr_avgx</a> (SV \*self)
 
double 
<a href="libAlicia_8c.html#a358828fd28b74830d7351c92684e90ab" class="el">regr_avgy</a> (SV \*self)
 
double 
<a href="libAlicia_8c.html#a1f02f5d335fe005c45def3f62170d01a" class="el">regr_intercept</a> (SV \*self)
 
double 
<a href="libAlicia_8c.html#a14568b04834c13d0190f03b2f480aee2" class="el">regr_sxx</a> (SV \*self)
 
double 
<a href="libAlicia_8c.html#a79e32408ceea878b79fb0dbf81a49939" class="el">regr_syy</a> (SV \*self)
 
double 
<a href="libAlicia_8c.html#a52d3e3e38e855d54719d8b614d5b23bd" class="el">regr_sxy</a> (SV \*self)
 
[]() Variables
--------------

use Inline 
<a href="libAlicia_8c.html#af992a27e99799e8cf07513d252c0dde1" class="el">C</a> =&gt; &lt;&lt; '...'
 
 
<a href="libAlicia_8c.html#a6ea63323dfeddf17864790e71e7a03f3" class="el">AliciaFuncs</a>
 
 
<a href="libAlicia_8c.html#a5bec494b6ade802227e28c3f3b2a986b" class="el">AliciaAggs</a>
 
package 
<a href="libAlicia_8c.html#a3ce1c0e644e38239999376323e625edf" class="el">Regr_Sxx</a>
 
package 
<a href="libAlicia_8c.html#aec5e23ecdaf67b11f043907b5875babd" class="el">Regr_Syy</a>
 
package 
<a href="libAlicia_8c.html#af64d8fb842520b5585185b55e648da9e" class="el">Regr_Sxy</a>
 
package 
<a href="libAlicia_8c.html#a87c59b87cb7eb7d74b5e4ebd841bfec5" class="el">Regr_Slope</a>
 
package 
<a href="libAlicia_8c.html#a9ea8d04002d75ab73628c30718e7b279" class="el">Regr_Intercept</a>
 
package 
<a href="libAlicia_8c.html#aaa0135be330031aac512addbf6aa417c" class="el">Regr_Count</a>
 
package 
<a href="libAlicia_8c.html#ac662b4b5b64885752702e4e7dc6d2cd4" class="el">Var_Pop</a>
 
package 
<a href="libAlicia_8c.html#a2d9cf6282a72f1f477fc9cea2ee12488" class="el">Var_Samp</a>
 
package 
<a href="libAlicia_8c.html#ab98559fba3e80a92758c5dd84a9cd164" class="el">Stddev_Samp</a>
 
package 
<a href="libAlicia_8c.html#a210b1bacb8cdcd7b4ef1dc425bf47acf" class="el">Stddev_Pop</a>
 
package 
<a href="libAlicia_8c.html#a3a3f47b459839ae6818e7b5789fbd03d" class="el">Corr</a>
 
package 
<a href="libAlicia_8c.html#af28e3de4bd85423c5abf76839f5fff02" class="el">Covar_Pop</a>
 
package 
<a href="libAlicia_8c.html#a0d67dd008aed8b7e6bf1c93153a6123d" class="el">Covar_Samp</a>
 
package 
<a href="libAlicia_8c.html#a09985b44a207edf18bcf5f28615118aa" class="el">Regr_Avgx</a>
 
package 
<a href="libAlicia_8c.html#ac420b6da091cc508a8a8aa5e62214ada" class="el">Regr_Avgy</a>
 
Macro Definition Documentation
------------------------------

<a href="" id="aeca034f67218340ecb2261a22c2f3dcd" class="anchor"></a>
|                       |
|-----------------------|
| \#define BUFSIZE   80 |

<a href="" id="a82156999d58c7a1ae01480ee67a3f417" class="anchor"></a>
|                              |
|------------------------------|
| \#define CENTURY   "century" |

<a href="" id="a509a01c55cbe47386fe24602b7c7fda1" class="anchor"></a>
|                      |
|----------------------|
| \#define DAY   "day" |

<a href="" id="a2792e9deb49be0bc37ba0b81a6d8ebb2" class="anchor"></a>
|                        |
|------------------------|
| \#define die   exit(1) |

<a href="" id="a9d21648a758cb23b074808186e95692f" class="anchor"></a>
|                      |
|----------------------|
| \#define DOW   "dow" |

<a href="" id="ae2f2a5b452584dec223ab0a050c11e8d" class="anchor"></a>
|                      |
|----------------------|
| \#define DOY   "doy" |

<a href="" id="a4c9ae5d808e2562483ca8e5282d26fc8" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">#define eq</td>
<td align="left">(</td>
<td align="left"> </td>
<td align="left">a,</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left"> </td>
<td align="left">b </td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left">   !strcmp(a,b)</td>
</tr>
</tbody>
</table>

<a href="" id="a4698ae12cf6a8acb5886fffd0ec897e6" class="anchor"></a>
|                        |
|------------------------|
| \#define HOUR   "hour" |

<a href="" id="a0ca0ee8ea801d2d3ce712d4644a8f186" class="anchor"></a>
|                        |
|------------------------|
| \#define MEDBUF   1024 |

<a href="" id="a25ed60bfa916205abc4fd6aa9e23804d" class="anchor"></a>
|                                  |
|----------------------------------|
| \#define MILLENIUM   "millenium" |

<a href="" id="ac1454fa04f41c693f39425697a137d82" class="anchor"></a>
|                            |
|----------------------------|
| \#define MINUTE   "minute" |

<a href="" id="a3729d06495d9713592f79f3122c9e677" class="anchor"></a>
|                          |
|--------------------------|
| \#define MONTH   "month" |

<a href="" id="a1d074c0b0cf82b5e84a269acc5af96b6" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">#define QLNV</td>
<td align="left">(</td>
<td align="left"> </td>
<td align="left">l,</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left"> </td>
<td align="left">i </td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left">   (SvNOK(*av_fetch(l, i, 0)) ? ((double)SvNV(*av_fetch(l, i, 0))) : 0)</td>
</tr>
</tbody>
</table>

<a href="" id="a94212be2394d2d37d9dfd33d07d82dba" class="anchor"></a>
|                            |
|----------------------------|
| \#define SECOND   "second" |

<a href="" id="a369180e5e0a23addbc2a6a9e24fee590" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">#define swap</td>
<td align="left">(</td>
<td align="left"> </td>
<td align="left">x,</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left"> </td>
<td align="left">y </td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left"></td>
</tr>
</tbody>
</table>

**Value:**
<span class="keywordflow">do</span> \\

{ <span class="keywordtype">unsigned</span> <span class="keywordtype">char</span> swap\_temp\[<span class="keyword">sizeof</span>(x) == <span class="keyword">sizeof</span>(y) ? (signed)<span class="keyword">sizeof</span>(x) : -1\]; \\

memcpy(swap\_temp,&y,<span class="keyword">sizeof</span>(x)); \\

memcpy(&y,&x, <span class="keyword">sizeof</span>(x)); \\

memcpy(&x,swap\_temp,<span class="keyword">sizeof</span>(x)); \\

} <span class="keywordflow">while</span>(0)

<a href="" id="a5871356500f559add06ea81d60331b1b" class="anchor"></a>
|                        |
|------------------------|
| \#define YEAR   "year" |

Function Documentation
----------------------

<a href="" id="acf05c56e48d78d25d39e8b8f74d0816d" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">double corr</td>
<td align="left">(</td>
<td align="left">SV * </td>
<td align="left"><em>arr_ref</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="ac1d38a2bd804f13ddc5156ebf97d917e" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">double covar_population</td>
<td align="left">(</td>
<td align="left">SV * </td>
<td align="left"><em>arr_ref</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="add787d1ac835ed79c1baf4621c65da26" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">double covar_sample</td>
<td align="left">(</td>
<td align="left">SV * </td>
<td align="left"><em>arr_ref</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="ad352d52a0f33bee47bcaf57fa1180c5f" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">double cvar_population</td>
<td align="left">(</td>
<td align="left">double </td>
<td align="left"><em>a</em>[],</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left">int </td>
<td align="left"><em>n</em> </td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a40a8323b6333f9e474c4854a9e84ab3d" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">struct tm epoch_to_tm</td>
<td align="left">(</td>
<td align="left">int </td>
<td align="left"><em>epoch</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a00ecd456f7e5012745d9c9781b00faae" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">int is_all_digits</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>str</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="aff57a3637f3b23839ee1de27ce507426" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">double mean</td>
<td align="left">(</td>
<td align="left">double </td>
<td align="left"><em>a</em>[],</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left">int </td>
<td align="left"><em>n</em> </td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a8bf44e0166731499c06e286e02a0fa81" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">double regr_avgx</td>
<td align="left">(</td>
<td align="left">SV * </td>
<td align="left"><em>self</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a358828fd28b74830d7351c92684e90ab" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">double regr_avgy</td>
<td align="left">(</td>
<td align="left">SV * </td>
<td align="left"><em>self</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a80094d0198f5f421f9faed34ec7548dd" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">int regr_count</td>
<td align="left">(</td>
<td align="left">SV * </td>
<td align="left"><em>arr_ref</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a1f02f5d335fe005c45def3f62170d01a" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">double regr_intercept</td>
<td align="left">(</td>
<td align="left">SV * </td>
<td align="left"><em>self</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a728959ac8df5363e40b27e78a073dd60" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">double regr_slope</td>
<td align="left">(</td>
<td align="left">SV * </td>
<td align="left"><em>arr_ref</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a14568b04834c13d0190f03b2f480aee2" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">double regr_sxx</td>
<td align="left">(</td>
<td align="left">SV * </td>
<td align="left"><em>self</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a52d3e3e38e855d54719d8b614d5b23bd" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">double regr_sxy</td>
<td align="left">(</td>
<td align="left">SV * </td>
<td align="left"><em>self</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a79e32408ceea878b79fb0dbf81a49939" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">double regr_syy</td>
<td align="left">(</td>
<td align="left">SV * </td>
<td align="left"><em>self</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a8b61aed8eaa037bbe98049949587631a" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* sage</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>timestamp1</em>,</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left">char * </td>
<td align="left"><em>timestamp2</em> </td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="ac4c1bb37bd56ff9f45167bfbff0638e5" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">int sascii</td>
<td align="left">(</td>
<td align="left">char </td>
<td align="left"><em>c</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="ad487bfc81dd42b1d2d52f504229dad26" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* sbtrim</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>str</em>,</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left">char * </td>
<td align="left"><em>chars</em> </td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="aeff4d7480f5038987166e9358ee87591" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char schr</td>
<td align="left">(</td>
<td align="left">int </td>
<td align="left"><em>n</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="aa80e2ef043dcfcdd4776f95d27eff7fd" class="anchor"></a>
<table>
<colgroup>
<col width="20%" />
<col width="20%" />
<col width="20%" />
<col width="20%" />
<col width="20%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* scurrent_date</td>
<td align="left">(</td>
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a5d6bb20e72d506e3e5f5366fe9d6c938" class="anchor"></a>
<table>
<colgroup>
<col width="20%" />
<col width="20%" />
<col width="20%" />
<col width="20%" />
<col width="20%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* scurrent_time</td>
<td align="left">(</td>
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a37da7b5424e3f72378afd69e6e91718b" class="anchor"></a>
<table>
<colgroup>
<col width="20%" />
<col width="20%" />
<col width="20%" />
<col width="20%" />
<col width="20%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* scurrent_timestamp</td>
<td align="left">(</td>
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a907609a144ae91d1ca85bca2b2688126" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* sdate</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>str</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a650fe63670c4904ea0f4327d508d258e" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* sdate_part</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>part</em>,</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left">char * </td>
<td align="left"><em>timestamp</em> </td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a7a22ebb746fe2faeb77f3ea4f0357788" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* sdate_trunc</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>part</em>,</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left">char * </td>
<td align="left"><em>timestamp</em> </td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a4bb39f69d4f93fcad3135d2e2e749894" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">int sindex</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>haystack</em>,</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left">char * </td>
<td align="left"><em>needle</em> </td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a4d73f0077da0ccfc8ca53cd6d2258fd0" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* sleft</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>str</em>,</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left">int </td>
<td align="left"><em>len</em> </td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="aa3fe51647c6fd75aff0d6df508e664bf" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* slower</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>str</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a8771cc5890b27e14ea609c17c227def2" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* slpad</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>str</em>,</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left">int </td>
<td align="left"><em>len</em>,</td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left"></td>
<td align="left">char * </td>
<td align="left"><em>fill</em> </td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a4392af20697468de64c484e1d00a934e" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* srepeat</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>str</em>,</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left">int </td>
<td align="left"><em>n</em> </td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a6a840b0f0328da7f239648cb0cc973d1" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* sreplace</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>orig</em>,</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left">char * </td>
<td align="left"><em>rep</em>,</td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left"></td>
<td align="left">char * </td>
<td align="left"><em>with</em> </td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a194dd20df46e91275e5d5646c5733964" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* sreverse</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>str</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="ae26b99f4bcecb788bb125e7ae7c742cc" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* sright</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>str</em>,</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left">int </td>
<td align="left"><em>len</em> </td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a23ffec05dc4a6650f75d17160622599d" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* srpad</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>str</em>,</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left">int </td>
<td align="left"><em>len</em>,</td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left"></td>
<td align="left">char * </td>
<td align="left"><em>fill</em> </td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a527f08686272dbafebb08ab451289c9b" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* ssplit_part</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>str</em>,</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left">char * </td>
<td align="left"><em>delim</em>,</td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left"></td>
<td align="left">int </td>
<td align="left"><em>field</em> </td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="aa0d3f3dcb77d40e08f78642eabe1807b" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">int sstrtotime</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>s</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="ac56033dd2efa609363d0e91335cd5f26" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* ssubstr</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>str</em>,</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left">int </td>
<td align="left"><em>start</em>,</td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left"></td>
<td align="left">int </td>
<td align="left"><em>len</em> </td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="aa54cbaed0a9bfe89fd282c43654b82ae" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">double stddev_population</td>
<td align="left">(</td>
<td align="left">SV * </td>
<td align="left"><em>self</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="ac86d50f62b28522eb837caccdb817f45" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">double stddev_sample</td>
<td align="left">(</td>
<td align="left">SV * </td>
<td align="left"><em>self</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a3767b8dda41af0b04049d75f63de3180" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* stimestamp</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>str</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a1a623fd0bdbbb965484ce4d98fd115f1" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* sto_ascii</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>str</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a02998dd0e355f69144f809f33766a741" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* sto_print</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>str</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a1d2738b5bc0a88c5f221b76e2c82da3e" class="anchor"></a>
<table>
<colgroup>
<col width="25%" />
<col width="25%" />
<col width="25%" />
<col width="25%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">int strtomonth</td>
<td align="left">(</td>
<td align="left">int * </td>
<td align="left"><em>mm</em>,</td>
</tr>
<tr class="even">
<td align="left"></td>
<td align="left"></td>
<td align="left">const char * </td>
<td align="left"><em>str</em> </td>
</tr>
<tr class="odd">
<td align="left"></td>
<td align="left">)</td>
<td align="left"></td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="ac75b72da906ff7d032c900561c9cbaef" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* suc_words</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>str</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a7d25b31c850ea3535c0452a21ea14da4" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* supper</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>str</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a06798d058792d39a2eb6f3b784ae1532" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">char* trim</td>
<td align="left">(</td>
<td align="left">char * </td>
<td align="left"><em>str</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="aab936461bf91782c8ba9547c5efda4f6" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">double var_population</td>
<td align="left">(</td>
<td align="left">SV * </td>
<td align="left"><em>arr_ref</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

<a href="" id="a12e7735a0fdc3fe5270e87969d224fec" class="anchor"></a>
<table style="width:100%;">
<colgroup>
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
<col width="16%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left">double var_sample</td>
<td align="left">(</td>
<td align="left">SV * </td>
<td align="left"><em>arr_ref</em></td>
<td align="left">)</td>
<td align="left"></td>
</tr>
</tbody>
</table>

Variable Documentation
----------------------

<a href="" id="a5bec494b6ade802227e28c3f3b2a986b" class="anchor"></a>
|            |
|------------|
| AliciaAggs |

**Initial value:**
= (

<a href="libAlicia_8c.html#a3a3f47b459839ae6818e7b5789fbd03d" class="code">Corr</a> =&gt; 2,

<a href="libAlicia_8c.html#a0d67dd008aed8b7e6bf1c93153a6123d" class="code">Covar_Samp</a> =&gt; 2,

<a href="libAlicia_8c.html#af28e3de4bd85423c5abf76839f5fff02" class="code">Covar_Pop</a> =&gt; 2,

<a href="libAlicia_8c.html#a09985b44a207edf18bcf5f28615118aa" class="code">Regr_Avgx</a> =&gt; 2,

<a href="libAlicia_8c.html#ac420b6da091cc508a8a8aa5e62214ada" class="code">Regr_Avgy</a> =&gt; 2,

<a href="libAlicia_8c.html#aaa0135be330031aac512addbf6aa417c" class="code">Regr_Count</a> =&gt; 2,

<a href="libAlicia_8c.html#a87c59b87cb7eb7d74b5e4ebd841bfec5" class="code">Regr_Slope</a> =&gt; 2,

<a href="libAlicia_8c.html#a9ea8d04002d75ab73628c30718e7b279" class="code">Regr_Intercept</a> =&gt; 2,

<a href="libAlicia_8c.html#a3ce1c0e644e38239999376323e625edf" class="code">Regr_Sxx</a> =&gt; 2,

<a href="libAlicia_8c.html#aec5e23ecdaf67b11f043907b5875babd" class="code">Regr_Syy</a> =&gt; 2,

<a href="libAlicia_8c.html#af64d8fb842520b5585185b55e648da9e" class="code">Regr_Sxy</a> =&gt; 2,

<a href="libAlicia_8c.html#ab98559fba3e80a92758c5dd84a9cd164" class="code">Stddev_Samp</a> =&gt; 1,

<a href="libAlicia_8c.html#a210b1bacb8cdcd7b4ef1dc425bf47acf" class="code">Stddev_Pop</a> =&gt; 1,

<a href="libAlicia_8c.html#a2d9cf6282a72f1f477fc9cea2ee12488" class="code">Var_Samp</a> =&gt; 1,

<a href="libAlicia_8c.html#ac662b4b5b64885752702e4e7dc6d2cd4" class="code">Var_Pop</a> =&gt; 1

)

[Regr\_Intercept](libAlicia_8c.html#a9ea8d04002d75ab73628c30718e7b279)

package Regr\_Intercept

**Definition:** libAlicia.c:1536

[Stddev\_Pop](libAlicia_8c.html#a210b1bacb8cdcd7b4ef1dc425bf47acf)

package Stddev\_Pop

**Definition:** libAlicia.c:1574

[Var\_Samp](libAlicia_8c.html#a2d9cf6282a72f1f477fc9cea2ee12488)

package Var\_Samp

**Definition:** libAlicia.c:1562

[Regr\_Sxx](libAlicia_8c.html#a3ce1c0e644e38239999376323e625edf)

package Regr\_Sxx

**Definition:** libAlicia.c:1496

[Regr\_Sxy](libAlicia_8c.html#af64d8fb842520b5585185b55e648da9e)

package Regr\_Sxy

**Definition:** libAlicia.c:1516

[Corr](libAlicia_8c.html#a3a3f47b459839ae6818e7b5789fbd03d)

package Corr

**Definition:** libAlicia.c:1580

[Var\_Pop](libAlicia_8c.html#ac662b4b5b64885752702e4e7dc6d2cd4)

package Var\_Pop

**Definition:** libAlicia.c:1556

[Regr\_Slope](libAlicia_8c.html#a87c59b87cb7eb7d74b5e4ebd841bfec5)

package Regr\_Slope

**Definition:** libAlicia.c:1526

[Regr\_Syy](libAlicia_8c.html#aec5e23ecdaf67b11f043907b5875babd)

package Regr\_Syy

**Definition:** libAlicia.c:1506

[Covar\_Pop](libAlicia_8c.html#af28e3de4bd85423c5abf76839f5fff02)

package Covar\_Pop

**Definition:** libAlicia.c:1590

[Covar\_Samp](libAlicia_8c.html#a0d67dd008aed8b7e6bf1c93153a6123d)

package Covar\_Samp

**Definition:** libAlicia.c:1600

[Stddev\_Samp](libAlicia_8c.html#ab98559fba3e80a92758c5dd84a9cd164)

package Stddev\_Samp

**Definition:** libAlicia.c:1568

[Regr\_Avgy](libAlicia_8c.html#ac420b6da091cc508a8a8aa5e62214ada)

package Regr\_Avgy

**Definition:** libAlicia.c:1620

[Regr\_Count](libAlicia_8c.html#aaa0135be330031aac512addbf6aa417c)

package Regr\_Count

**Definition:** libAlicia.c:1546

[Regr\_Avgx](libAlicia_8c.html#a09985b44a207edf18bcf5f28615118aa)

package Regr\_Avgx

**Definition:** libAlicia.c:1610

<a href="" id="a6ea63323dfeddf17864790e71e7a03f3" class="anchor"></a>
|             |
|-------------|
| AliciaFuncs |

**Initial value:**
= (

<a href="libAlicia_8c.html#aa3fe51647c6fd75aff0d6df508e664bf" class="code">slower</a> =&gt; 1,

<a href="libAlicia_8c.html#a7d25b31c850ea3535c0452a21ea14da4" class="code">supper</a> =&gt; 1,

<a href="libAlicia_8c.html#a194dd20df46e91275e5d5646c5733964" class="code">sreverse</a> =&gt; 1,

<a href="libAlicia_8c.html#a4d73f0077da0ccfc8ca53cd6d2258fd0" class="code">sleft</a> =&gt; 2,

<a href="libAlicia_8c.html#ae26b99f4bcecb788bb125e7ae7c742cc" class="code">sright</a> =&gt; 2,

<a href="libAlicia_8c.html#a4bb39f69d4f93fcad3135d2e2e749894" class="code">sindex</a> =&gt; 2,

<a href="libAlicia_8c.html#ac56033dd2efa609363d0e91335cd5f26" class="code">ssubstr</a> =&gt; 3,

<a href="libAlicia_8c.html#ac75b72da906ff7d032c900561c9cbaef" class="code">suc_words</a> =&gt; 1,

<a href="libAlicia_8c.html#ac4c1bb37bd56ff9f45167bfbff0638e5" class="code">sascii</a> =&gt; 1,

<a href="libAlicia_8c.html#aeff4d7480f5038987166e9358ee87591" class="code">schr</a> =&gt; 1,

<a href="libAlicia_8c.html#ad487bfc81dd42b1d2d52f504229dad26" class="code">sbtrim</a> =&gt; 2,

<a href="libAlicia_8c.html#a23ffec05dc4a6650f75d17160622599d" class="code">srpad</a> =&gt; 3,

<a href="libAlicia_8c.html#a8771cc5890b27e14ea609c17c227def2" class="code">slpad</a> =&gt; 3,

<a href="libAlicia_8c.html#a6a840b0f0328da7f239648cb0cc973d1" class="code">sreplace</a> =&gt; 3,

<a href="libAlicia_8c.html#a4392af20697468de64c484e1d00a934e" class="code">srepeat</a> =&gt; 2,

<a href="libAlicia_8c.html#a527f08686272dbafebb08ab451289c9b" class="code">ssplit_part</a> =&gt; 3,

<a href="libAlicia_8c.html#a02998dd0e355f69144f809f33766a741" class="code">sto_print</a> =&gt; 1,

<a href="libAlicia_8c.html#a1a623fd0bdbbb965484ce4d98fd115f1" class="code">sto_ascii</a> =&gt; 1,

<a href="libAlicia_8c.html#aa0d3f3dcb77d40e08f78642eabe1807b" class="code">sstrtotime</a> =&gt; 1,

<a href="libAlicia_8c.html#a907609a144ae91d1ca85bca2b2688126" class="code">sdate</a> =&gt; 1,

<a href="libAlicia_8c.html#a3767b8dda41af0b04049d75f63de3180" class="code">stimestamp</a> =&gt; 1,

<a href="libAlicia_8c.html#a8b61aed8eaa037bbe98049949587631a" class="code">sage</a> =&gt; 2,

<a href="libAlicia_8c.html#aa80e2ef043dcfcdd4776f95d27eff7fd" class="code">scurrent_date</a> =&gt; 0,

<a href="libAlicia_8c.html#a5d6bb20e72d506e3e5f5366fe9d6c938" class="code">scurrent_time</a> =&gt; 0,

<a href="libAlicia_8c.html#a37da7b5424e3f72378afd69e6e91718b" class="code">scurrent_timestamp</a> =&gt; 0,

<a href="libAlicia_8c.html#a650fe63670c4904ea0f4327d508d258e" class="code">sdate_part</a> =&gt; 2,

<a href="libAlicia_8c.html#a7a22ebb746fe2faeb77f3ea4f0357788" class="code">sdate_trunc</a> =&gt; 2

)

[slower](libAlicia_8c.html#aa3fe51647c6fd75aff0d6df508e664bf)

char \* slower(char \*str)

**Definition:** libAlicia.c:72

[sright](libAlicia_8c.html#ae26b99f4bcecb788bb125e7ae7c742cc)

char \* sright(char \*str, int len)

**Definition:** libAlicia.c:154

[srpad](libAlicia_8c.html#a23ffec05dc4a6650f75d17160622599d)

char \* srpad(char \*str, int len, char \*fill)

**Definition:** libAlicia.c:308

[ssubstr](libAlicia_8c.html#ac56033dd2efa609363d0e91335cd5f26)

char \* ssubstr(char \*str, int start, int len)

**Definition:** libAlicia.c:188

[sreverse](libAlicia_8c.html#a194dd20df46e91275e5d5646c5733964)

char \* sreverse(char \*str)

**Definition:** libAlicia.c:111

[sleft](libAlicia_8c.html#a4d73f0077da0ccfc8ca53cd6d2258fd0)

char \* sleft(char \*str, int len)

**Definition:** libAlicia.c:136

[sto\_ascii](libAlicia_8c.html#a1a623fd0bdbbb965484ce4d98fd115f1)

char \* sto\_ascii(char \*str)

**Definition:** libAlicia.c:520

[sindex](libAlicia_8c.html#a4bb39f69d4f93fcad3135d2e2e749894)

int sindex(char \*haystack, char \*needle)

**Definition:** libAlicia.c:169

[stimestamp](libAlicia_8c.html#a3767b8dda41af0b04049d75f63de3180)

char \* stimestamp(char \*str)

**Definition:** libAlicia.c:711

[scurrent\_time](libAlicia_8c.html#a5d6bb20e72d506e3e5f5366fe9d6c938)

char \* scurrent\_time()

**Definition:** libAlicia.c:804

[sascii](libAlicia_8c.html#ac4c1bb37bd56ff9f45167bfbff0638e5)

int sascii(char c)

**Definition:** libAlicia.c:243

[sto\_print](libAlicia_8c.html#a02998dd0e355f69144f809f33766a741)

char \* sto\_print(char \*str)

**Definition:** libAlicia.c:491

[sage](libAlicia_8c.html#a8b61aed8eaa037bbe98049949587631a)

char \* sage(char \*timestamp1, char \*timestamp2)

**Definition:** libAlicia.c:745

[sbtrim](libAlicia_8c.html#ad487bfc81dd42b1d2d52f504229dad26)

char \* sbtrim(char \*str, char \*chars)

**Definition:** libAlicia.c:270

[slpad](libAlicia_8c.html#a8771cc5890b27e14ea609c17c227def2)

char \* slpad(char \*str, int len, char \*fill)

**Definition:** libAlicia.c:344

[sdate\_part](libAlicia_8c.html#a650fe63670c4904ea0f4327d508d258e)

char \* sdate\_part(char \*part, char \*timestamp)

**Definition:** libAlicia.c:833

[srepeat](libAlicia_8c.html#a4392af20697468de64c484e1d00a934e)

char \* srepeat(char \*str, int n)

**Definition:** libAlicia.c:439

[sdate\_trunc](libAlicia_8c.html#a7a22ebb746fe2faeb77f3ea4f0357788)

char \* sdate\_trunc(char \*part, char \*timestamp)

**Definition:** libAlicia.c:901

[sreplace](libAlicia_8c.html#a6a840b0f0328da7f239648cb0cc973d1)

char \* sreplace(char \*orig, char \*rep, char \*with)

**Definition:** libAlicia.c:383

[sstrtotime](libAlicia_8c.html#aa0d3f3dcb77d40e08f78642eabe1807b)

int sstrtotime(char \*s)

**Definition:** libAlicia.c:612

[ssplit\_part](libAlicia_8c.html#a527f08686272dbafebb08ab451289c9b)

char \* ssplit\_part(char \*str, char \*delim, int field)

**Definition:** libAlicia.c:467

[scurrent\_date](libAlicia_8c.html#aa80e2ef043dcfcdd4776f95d27eff7fd)

char \* scurrent\_date()

**Definition:** libAlicia.c:790

[sdate](libAlicia_8c.html#a907609a144ae91d1ca85bca2b2688126)

char \* sdate(char \*str)

**Definition:** libAlicia.c:681

[supper](libAlicia_8c.html#a7d25b31c850ea3535c0452a21ea14da4)

char \* supper(char \*str)

**Definition:** libAlicia.c:92

[schr](libAlicia_8c.html#aeff4d7480f5038987166e9358ee87591)

char schr(int n)

**Definition:** libAlicia.c:257

[scurrent\_timestamp](libAlicia_8c.html#a37da7b5424e3f72378afd69e6e91718b)

char \* scurrent\_timestamp()

**Definition:** libAlicia.c:818

[suc\_words](libAlicia_8c.html#ac75b72da906ff7d032c900561c9cbaef)

char \* suc\_words(char \*str)

**Definition:** libAlicia.c:219

<a href="" id="af992a27e99799e8cf07513d252c0dde1" class="anchor"></a>
|                                   |
|-----------------------------------|
| use Inline C =&gt; &lt;&lt; '...' |

<a href="" id="a3a3f47b459839ae6818e7b5789fbd03d" class="anchor"></a>
|              |
|--------------|
| package Corr |

**Initial value:**
{

sub <span class="keyword">new</span> { bless \[\], shift; }

sub step {

my $self = shift;

push @$self, ($\_\[0\]?$\_\[0\]:0);

push @$self, ($\_\[1\]?$\_\[1\]:0);

}

sub finalize { <a href="libAlicia_8c.html#acf05c56e48d78d25d39e8b8f74d0816d" class="code">main::corr</a>($\_\[0\]) }

}

[corr](libAlicia_8c.html#acf05c56e48d78d25d39e8b8f74d0816d)

double corr(SV \*arr\_ref)

**Definition:** libAlicia.c:1185

<a href="" id="af28e3de4bd85423c5abf76839f5fff02" class="anchor"></a>
|                    |
|--------------------|
| package Covar\_Pop |

**Initial value:**
{

sub <span class="keyword">new</span> { bless \[\], shift; }

sub step {

my $self = shift;

push @$self, ($\_\[0\]?$\_\[0\]:0);

push @$self, ($\_\[1\]?$\_\[1\]:0);

}

sub finalize{ <a href="libAlicia_8c.html#ac1d38a2bd804f13ddc5156ebf97d917e" class="code">main::covar_population</a>($\_\[0\]) }

}

[covar\_population](libAlicia_8c.html#ac1d38a2bd804f13ddc5156ebf97d917e)

double covar\_population(SV \*arr\_ref)

**Definition:** libAlicia.c:1002

<a href="" id="a0d67dd008aed8b7e6bf1c93153a6123d" class="anchor"></a>
|                     |
|---------------------|
| package Covar\_Samp |

**Initial value:**
{

sub <span class="keyword">new</span> { bless \[\], shift; }

sub step {

my $self = shift;

push @$self, ($\_\[0\]?$\_\[0\]:0);

push @$self, ($\_\[1\]?$\_\[1\]:0);

}

sub finalize{ <a href="libAlicia_8c.html#add787d1ac835ed79c1baf4621c65da26" class="code">main::covar_sample</a>($\_\[0\]) }

}

[covar\_sample](libAlicia_8c.html#add787d1ac835ed79c1baf4621c65da26)

double covar\_sample(SV \*arr\_ref)

**Definition:** libAlicia.c:957

<a href="" id="a09985b44a207edf18bcf5f28615118aa" class="anchor"></a>
|                    |
|--------------------|
| package Regr\_Avgx |

**Initial value:**
{

sub <span class="keyword">new</span> { bless \[\], shift; }

sub step {

my $self = shift;

push @$self, ($\_\[0\]?$\_\[0\]:0);

push @$self, ($\_\[1\]?$\_\[1\]:0);

}

sub finalize { <a href="libAlicia_8c.html#a8bf44e0166731499c06e286e02a0fa81" class="code">main::regr_avgx</a>($\_\[0\]) }

}

[regr\_avgx](libAlicia_8c.html#a8bf44e0166731499c06e286e02a0fa81)

double regr\_avgx(SV \*self)

**Definition:** libAlicia.c:1291

<a href="" id="ac420b6da091cc508a8a8aa5e62214ada" class="anchor"></a>
|                    |
|--------------------|
| package Regr\_Avgy |

**Initial value:**
{

sub <span class="keyword">new</span> { bless \[\], shift; }

sub step {

my $self = shift;

push @$self, ($\_\[0\]?$\_\[0\]:0);

push @$self, ($\_\[1\]?$\_\[1\]:0);

}

sub finalize { <a href="libAlicia_8c.html#a358828fd28b74830d7351c92684e90ab" class="code">main::regr_avgy</a>($\_\[0\]) }

}

[regr\_avgy](libAlicia_8c.html#a358828fd28b74830d7351c92684e90ab)

double regr\_avgy(SV \*self)

**Definition:** libAlicia.c:1320

<a href="" id="aaa0135be330031aac512addbf6aa417c" class="anchor"></a>
|                     |
|---------------------|
| package Regr\_Count |

**Initial value:**
{

sub <span class="keyword">new</span> { bless \[\], shift; }

sub step {

my $self = shift;

push @$self, ($\_\[0\]?$\_\[0\]:0);

push @$self, ($\_\[1\]?$\_\[1\]:0);

}

sub finalize{ <a href="libAlicia_8c.html#a80094d0198f5f421f9faed34ec7548dd" class="code">main::regr_count</a>($\_\[0\]) }

}

[regr\_count](libAlicia_8c.html#a80094d0198f5f421f9faed34ec7548dd)

int regr\_count(SV \*arr\_ref)

**Definition:** libAlicia.c:1168

<a href="" id="a9ea8d04002d75ab73628c30718e7b279" class="anchor"></a>
|                         |
|-------------------------|
| package Regr\_Intercept |

**Initial value:**
{

sub <span class="keyword">new</span> { bless \[\], shift; }

sub step {

my $self = shift;

push @$self, ($\_\[0\]?$\_\[0\]:0);

push @$self, ($\_\[1\]?$\_\[1\]:0);

}

sub finalize { <a href="libAlicia_8c.html#a1f02f5d335fe005c45def3f62170d01a" class="code">main::regr_intercept</a>($\_\[0\]) }

}

[regr\_intercept](libAlicia_8c.html#a1f02f5d335fe005c45def3f62170d01a)

double regr\_intercept(SV \*self)

**Definition:** libAlicia.c:1349

<a href="" id="a87c59b87cb7eb7d74b5e4ebd841bfec5" class="anchor"></a>
|                     |
|---------------------|
| package Regr\_Slope |

**Initial value:**
{

sub <span class="keyword">new</span> { bless \[\], shift; }

sub step {

my $self = shift;

push @$self, ($\_\[0\]?$\_\[0\]:0);

push @$self, ($\_\[1\]?$\_\[1\]:0);

}

sub finalize { <a href="libAlicia_8c.html#a728959ac8df5363e40b27e78a073dd60" class="code">main::regr_slope</a>($\_\[0\]) }

}

[regr\_slope](libAlicia_8c.html#a728959ac8df5363e40b27e78a073dd60)

double regr\_slope(SV \*arr\_ref)

**Definition:** libAlicia.c:1137

<a href="" id="a3ce1c0e644e38239999376323e625edf" class="anchor"></a>
|                   |
|-------------------|
| package Regr\_Sxx |

**Initial value:**
{

sub <span class="keyword">new</span> { bless \[\], shift; }

sub step {

my $self = shift;

push @$self, ($\_\[0\]?$\_\[0\]:0);

push @$self, ($\_\[1\]?$\_\[1\]:0);

}

sub finalize { <a href="libAlicia_8c.html#a14568b04834c13d0190f03b2f480aee2" class="code">main::regr_sxx</a>($\_\[0\]) }

}

[regr\_sxx](libAlicia_8c.html#a14568b04834c13d0190f03b2f480aee2)

double regr\_sxx(SV \*self)

**Definition:** libAlicia.c:1381

<a href="" id="af64d8fb842520b5585185b55e648da9e" class="anchor"></a>
|                   |
|-------------------|
| package Regr\_Sxy |

**Initial value:**
{

sub <span class="keyword">new</span> { bless \[\], shift; }

sub step {

my $self = shift;

push @$self, ($\_\[0\]?$\_\[0\]:0);

push @$self, ($\_\[1\]?$\_\[1\]:0);

}

sub finalize { <a href="libAlicia_8c.html#a52d3e3e38e855d54719d8b614d5b23bd" class="code">main::regr_sxy</a>($\_\[0\]) }

}

[regr\_sxy](libAlicia_8c.html#a52d3e3e38e855d54719d8b614d5b23bd)

double regr\_sxy(SV \*self)

**Definition:** libAlicia.c:1439

<a href="" id="aec5e23ecdaf67b11f043907b5875babd" class="anchor"></a>
|                   |
|-------------------|
| package Regr\_Syy |

**Initial value:**
{

sub <span class="keyword">new</span> { bless \[\], shift; }

sub step {

my $self = shift;

push @$self, ($\_\[0\]?$\_\[0\]:0);

push @$self, ($\_\[1\]?$\_\[1\]:0);

}

sub finalize { <a href="libAlicia_8c.html#a79e32408ceea878b79fb0dbf81a49939" class="code">main::regr_syy</a>($\_\[0\]) }

}

[regr\_syy](libAlicia_8c.html#a79e32408ceea878b79fb0dbf81a49939)

double regr\_syy(SV \*self)

**Definition:** libAlicia.c:1410

<a href="" id="a210b1bacb8cdcd7b4ef1dc425bf47acf" class="anchor"></a>
|                     |
|---------------------|
| package Stddev\_Pop |

**Initial value:**
{

sub <span class="keyword">new</span> { bless \[\], shift; }

sub step { push @{$\_\[0\]}, $\_\[1\] }

sub finalize { <a href="libAlicia_8c.html#aa54cbaed0a9bfe89fd282c43654b82ae" class="code">main::stddev_population</a>($\_\[0\]) }

}

[stddev\_population](libAlicia_8c.html#aa54cbaed0a9bfe89fd282c43654b82ae)

double stddev\_population(SV \*self)

**Definition:** libAlicia.c:1233

<a href="" id="ab98559fba3e80a92758c5dd84a9cd164" class="anchor"></a>
|                      |
|----------------------|
| package Stddev\_Samp |

**Initial value:**
{

sub <span class="keyword">new</span> { bless \[\], shift; }

sub step { push @{$\_\[0\]}, $\_\[1\] }

sub finalize { <a href="libAlicia_8c.html#ac86d50f62b28522eb837caccdb817f45" class="code">main::stddev_sample</a>($\_\[0\]) }

}

[stddev\_sample](libAlicia_8c.html#ac86d50f62b28522eb837caccdb817f45)

double stddev\_sample(SV \*self)

**Definition:** libAlicia.c:1262

<a href="" id="ac662b4b5b64885752702e4e7dc6d2cd4" class="anchor"></a>
|                  |
|------------------|
| package Var\_Pop |

**Initial value:**
{

sub <span class="keyword">new</span> { bless \[\], shift; }

sub step { push @{$\_\[0\]}, $\_\[1\] }

sub finalize { <a href="libAlicia_8c.html#aab936461bf91782c8ba9547c5efda4f6" class="code">main::var_population</a>($\_\[0\]) }

}

[var\_population](libAlicia_8c.html#aab936461bf91782c8ba9547c5efda4f6)

double var\_population(SV \*arr\_ref)

**Definition:** libAlicia.c:1077

<a href="" id="a2d9cf6282a72f1f477fc9cea2ee12488" class="anchor"></a>
|                   |
|-------------------|
| package Var\_Samp |

**Initial value:**
{

sub <span class="keyword">new</span> { bless \[\], shift; }

sub step { push @{$\_\[0\]}, $\_\[1\] }

sub finalize { <a href="libAlicia_8c.html#a12e7735a0fdc3fe5270e87969d224fec" class="code">main::var_sample</a>($\_\[0\]) }

}

[var\_sample](libAlicia_8c.html#a12e7735a0fdc3fe5270e87969d224fec)

double var\_sample(SV \*arr\_ref)

**Definition:** libAlicia.c:1047

------------------------------------------------------------------------

Generated by  [<img src="doxygen.png" alt="doxygen" class="footer" />](http://www.doxygen.org/index.html) 1.8.11
