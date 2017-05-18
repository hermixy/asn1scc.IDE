/* ***************************************************************************************************************** */
/* ***************************************************************************************************************** */
/* **************************************      LEXER    ************************************************************ */
/* ***************************************************************************************************************** */
/* ***************************************************************************************************************** */

lexer grammar asnLexer;

PLUS_INFINITY : 'PLUS-INFINITY';
MINUS_INFINITY	: 'MINUS-INFINITY';		
GeneralizedTime  :	'GeneralizedTime';
UTCTime  :	'UTCTime';
MANTISSA	: 'mantissa';
BASE		: 'base';
EXPONENT	: 'exponent';
UnionMark  :  '|'|'UNION';
IntersectionMark  :	'^' | 'INTERSECTION';
DEFINITIONS :	 'DEFINITIONS';
EXPLICIT:	 'EXPLICIT';
TAGS 	:	'TAGS';
IMPLICIT:	'IMPLICIT';
AUTOMATIC	:	'AUTOMATIC';
EXTENSIBILITY	:	'EXTENSIBILITY';
IMPLIED :	'IMPLIED';
BEGIN	:	'BEGIN';
END	:	'END';
EXPORTS	:	'EXPORTS';
ALL	: 	'ALL';
IMPORTS	:	'IMPORTS';
FROM	:	'FROM';
UNIVERSAL	: 'UNIVERSAL';
APPLICATION	: 'APPLICATION';
PRIVATE		:'PRIVATE';
BIT	: 'BIT';
STRING	:	'STRING';
BOOLEAN :	'BOOLEAN';
ENUMERATED	:'ENUMERATED';
INTEGER	:	'INTEGER';
REAL	:	'REAL';
CHOICE	:	'CHOICE';
SEQUENCE	:'SEQUENCE';
OPTIONAL	:'OPTIONAL';
SIZE	:	'SIZE';
OF	:	'OF';
OCTET	:	'OCTET';
MIN	: 	'MIN';
MAX	:	'MAX';
TRUE	:	'TRUE';
FALSE	:	'FALSE';
ABSENT	:	'ABSENT';
PRESENT	:	'PRESENT';
WITH 	:	'WITH';
COMPONENT	: 'COMPONENT';		
COMPONENTS 	: 'COMPONENTS';
DEFAULT 	: 'DEFAULT';
NULLVAL		:'NULL';
PATTERN		:'PATTERN';
OBJECT 		:'OBJECT';
IDENTIFIER	:'IDENTIFIER';
RELATIVE_OID	:'RELATIVE-OID';
NumericString	:'NumericString';
PrintableString	:'PrintableString';
VisibleString	:'VisibleString';
IA5String	:'IA5String';
TeletexString	:'TeletexString';
VideotexString	:'VideotexString';
GraphicString	:'GraphicString';
GeneralString	:'GeneralString';
UniversalString	:'UniversalString';
BMPString	:'BMPString';
UTF8String	:'UTF8String';
INCLUDES	:'INCLUDES';
EXCEPT		:'EXCEPT';
SET		:'SET';
ASSIG_OP		: '::=';
L_BRACKET	:	'{';	
R_BRACKET	:	'}';	
L_PAREN		:	'(';
R_PAREN		:	')';
COMMA		:	',';

EXT_MARK	: '...';
DOUBLE_DOT  : '..';


LESS_THAN			: '<';


BitStringLiteral	:
	'\'' ('0'|'1'|' ' | '\t' | '\r' | '\n')* '\'B'
	;
	



OctectStringLiteral	:
	'\'' ('0'..'9'|'a'..'f'|'A'..'F'|' ' | '\t' | '\r' | '\n')* '\'H'
	;

StringLiteral 	: 	STR+ ;

fragment
STR 	:	'"' (.)*? '"' ; 
			
UID  :   ('A'..'Z') ('a'..'z'|'A'..'Z'|'0'..'9'|'-')*
    ;

LID  :   ('a'..'z') ('a'..'z'|'A'..'Z'|'0'..'9'|'-')*
    ;

fragment
INT	:	('+'|'-')? ( '0' | ('1'..'9') ('0'..'9')*); 


	
fragment
DIGITS
	:	('0'..'9')+;

FloatingPointLiteral
     :
	(/* integer */ INT | /* exponential notation */ INT DOT? (DIGITS)? (Exponent)+ | /* floating point */ DIGITS DOT DIGITS)
    ;

	
	
DOT	:	 '.';	





fragment
Exponent : ('e'|'E') ('+'|'-')? ('0'..'9')+ ;


WS  :   (' ' | '\t' | '\r' | '\n')+ -> channel(HIDDEN)
    ;

COMMENT
    :   '/*' (.)*? '*/' -> channel(HIDDEN)
    ;

/*
COMMENT2
    :   '--' ( options {greedy=false;} : . )* ('--'|'\r'?'\n') {$channel=HIDDEN;}
    ;
*/

COMMENT2
    : '--' ~('\n' | '\r')* '\r'? '\n'? -> channel(HIDDEN)
    ;



