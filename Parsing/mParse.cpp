#include "../Algebra2/expression.h"
#include <string>
#include <map>

#define RB ')'
#define LB '('
#define ADD '+'
#define SUBTRACT '-'
#define MULTIPLY '*'
#define DIVIDE '/'
#define RATIONAL_BEGIN '{'
#define ROOT_START '['
#define EXPONENT_BEGIN '^'
#define FUNCTION_BEGIN 'f'
#define ESCAPE_CHARACTER '|'

// The characters above will be special characters, not forming a string in keeping with these
// special characters will mean that the string is not well formed and the function will return
// an error.

// BNF Grammar using an extended definition where * denotes repition (0 - infinity), and
// ? denotes binary inclusion, and / denotes set subtraction

// ===================

// Expression ::= (Term | '(' Expression ')') *(('+' | '-') (Term | '(' Expression ')')) ?AuxillaryOperation

// Term ::= Multiplication | Division

// Multiplication ::= (Constant *Variable) ?AuxillaryOperation

// Division ::= (Term '/' Term) ?AuxillaryOperation

// AuxillaryOperation ::= Root | Exponent

// Root ::= 'v' Expression EscapeCharacter

// Exponent ::= '^' Expression EscapeCharacter

// EscapeCharacter ::= '|'

// Constant ::= *('1' - '9') *('0' - '9')

// Variable ::= ('a' - 'z') / ('v')

// ===================

