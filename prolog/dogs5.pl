rl5:-consult('dogs5.pl').

% builtin for is:
% XCY
% X-Y
% X*Y
% X/Y
% X//Y
% X mod Y
% X ^ Y
% -X
% abs(X)
% sin(X)
% cos(X)
% max(X,Y)
% round(X)
% sqrt(X)
% The sum of X and Y
% The difference of X and Y
% The product of X and Y
% The quotient of X and Y
% The ‘integer quotient’ of X and Y (the result is
% truncated to the nearest integer between it and zero)
% The remainder when X is divided by Y
% The value of X to the power of Y
% The negative of X
% The absolute value of X
% The sine of X (for X measured in radians)
% The cosine of X (for X measured in radians)
% The larger of X and Y
% The value of X rounded to the nearest integer
% The square root of X

% work but is a wrong way: { increase(N):-N is N+1. }
increase(N,M) :- M is N+1.

%----------------------
% Equality Operators
%----------------------

% use =:= like is for equals number evaluation

%----------------------------------------
% Arithmetic Expression Inequality =\=
%----------------------------------------
%----------------------
% Terms Identical ==
%----------------------
%---------------------------
% Terms Not Identical \==
%---------------------------
%-------------------------------------
% Terms Identical With Unification =
%-------------------------------------
%---------------------------------------
% Non-Unification Between Two Terms \=
%---------------------------------------
%---------------------------------------------------------------------------------------|
% The Disjunction Operator ; ---------------------------------------------------------- |
%      is used to represent ----------------------------------------------------------- |
%      ‘or’. It is an infix operator that takes two arguments, both of which are goals. |
%      Goal1;Goal2 succeeds if either Goal1 or Goal2 succeeds. ------------------------ |
%---------------------------------------------------------------------------------------|
%------------------------------------------------------|
% More About Operator Precedence builtin               |
% Precedence Type Operator(s)                          |
% 1100       xfy  ;                                    |
% 1000       fy   not                                  |
% 700        xfx  is < > =< >= =:= =\= = \= == \==     |
% 500        yfx  + -                                  |
% 400        yfx  * / //                               |
% 200        xfy  ^                                    |
% 200        fy   + -                                  |
%------------------------------------------------------|

% With not properly declared as of type fy a:
% sequence of two or more not operators is permitted

% not not not not dog(fido). is ok

dog(fido).
dog(rover).
dog(tom).
dog(fred).

cat(mary).
cat(jane).
cat(harry).
cat(henry).
cat(bill).
cat(steve).

large(fido).
large(mary).
large(fred).
large(henry).
large(steve).
large(mike).
large(jim).
large_dog(X):- dog(X),large(X).

small(rover).
small(jane).
small(tom).
small_animal(A):- dog(A),small(A).
small_animal(B):- cat(B),small(B).

chases(X,Y):- large_dog(X),small_animal(Y),
              write(X),write(' chases '),write(Y),nl.

easy1( X ) :- op( 1200, fx, X ).
easy2( X ) :- op( 1200, xfy, X ).

reduce_animal :- easy1( cat ), easy1( dog ),
                 easy1( large ), easy1( small ),
                 easy1( small_animal ),
                 easy1( large_dog ),
                 easy2( chases ).

mid( A, B, Equal ) :- Equal is ( A+B )/2.
sqrtp( A, B, Equal ) :- Equal is sqrt( A*B ).
larger( A, B, Equal ) :- A >= B, Equal is A-B+1; Equal is B-A+1.

% Equal quando non è un vuoto metcha con B-A+1, se Equal viene riempito con un atomo,
% allora è un confronto.

% get input --> read( X )
% see ASCII value for passing non-printing characters (such as space and tab).

% Outputting Characters >> built-in predicate put/1. number from 0 to 255 or an int expression.

% Inputting Characters >> built-in predicates are get0/1, get/1. ( read ASCII text, return int ).

% get read more char,
% get0 read a single char, but with * is possible create a QUEUE of chars.

% Input and Output Using Files
%       File Output: Changing the Current Output Stream >> tell, told, telling, append
%       File Input: Changing the Current Input Stream >> see, seen, seeing
%
% tell, see for direct use ( open )
% told, seen for reset ( close )
% telling, seeing for causes the variable to be bound to the name of the current input stream.

% Reading from Files: End of File
% If the end of file is encountered when evaluating the goal read(X), variable X will
% be bound to the atom end_of_file.
% If the end of file is encountered while evaluating the goal get(X) or get0(X),
% variable X will be bound to a 'special' numerical value. As ASCII values must be
% in the range 0 to 255 inclusive, this will typically be -1, but may vary from one
% implementation of Prolog to another.

% Reading from Files: End of Record
% The end of a line of input at the user's terminal and the end of a record in a file
% will typically both be indicated by the ASCII value 10 and that is the assumption
% we will make in this book. In some Prolog systems different values are used. (For
% example the end of a line of input at the user's terminal is sometimes represented by
% 13 and the end of a record in a file is sometimes represented by two ASCII values:
% 13 followed by 10.)
% The following program shows how to read in a series of characters from the
% keyboard and print them out, one per line.

readline:-get0(X),process(X).
process(10).
process(X):-X=\=10,put(X),nl,readline.

% Chapter Summary
% Describes the principal built-in predicates available for both term by term and
% character by character input and output and for reading and writing files. Also
% introduces the notion of the ASCII value of a character.

getXY :- get0( X ), get0( Y ), difference( X,Y,R ), write( R ).
difference( X,Y,R ) :- X>=Y, R is X-Y; R is Y-X.

toLower( X ) :- Y is X+32, X>64, X<91, put( Y ); put( X ).
processing( X ) :- not( X=10 ), toLower( X ), makelower; put( 10 ).
makelower :- get0( X ), processing( X ).

%------------------------------------
% load predicate from file
%------------------------------------

cp_procc :- read( Y ), not( Y = 'end_of_file' ), cp_procc( Y ); seen.
cp_procc( Y ) :- write( Y ), put( 46 ), put( 10 ), cp_procc.
copyterms( X ) :- see( X ), cp_procc.

%------------------------------------
% load evry readble char from file
%------------------------------------

cp_procc2 :- get( Y ), not( Y = -1 ), X is Y, cp_procc2( X,Y ); seen.
cp_procc2( X,Y ) :- put( Y ), put( 46 ), write( ': ' ), write( X ), put( 10 ), cp_procc2.
copyterms2( X ) :- see( X ), cp_procc2.

%------------------------------------
% open from file1 to file2
%------------------------------------

cp_procc3 :- read( A ), not( A = 'end_of_file' ), cp_procc3( A ); seen, told.
cp_procc3( Y ) :- write( Y ), put( 46 ), put( 10 ), cp_procc3.
copyterms3( X,Y ) :- see( X ), tell( Y ), cp_procc3.
