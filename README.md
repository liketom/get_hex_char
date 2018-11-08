# get_hex_char
Get Chinese character hex encoding

# Installation
<pre name="code" class="c"> gcc get_hexadecimal_character.c -o get_hexadecimal_character </pre>  

# Usage
If your terminal is UTF-8 encoded:
<pre name="code" class="c">./get_hexadecimal_character -utf8 张

input data code is [-utf8]
GB2312 HEX : d5 c5 
UTF-8  HEX : e5 bc a0</pre>  

GB2312 encoded:
<pre name="code" class="c">./get_hexadecimal_character -gb2312 张

input data code is [-gb2312]
GB2312 HEX : d5 c5 
UTF-8  HEX : e5 bc a0</pre> 
