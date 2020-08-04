
% A Note on Declarative Programming:
%
% dog(fido). dog(rover). dog(jane). dog(tom). dog(fred).
% dog(henry).
% cat(bill). cat(steve). cat(mary). cat(harry).
% large(rover). large(william). large(martin).
% large(tom). large(steve).
% large(jim). large(mike).
% large_animal(X):- dog(X),large(X).
% large_animal(Z):- cat(Z),large(Z).

% test(X):-X>0,write(positive),nl.
% test(0):-write(zero),nl.
% test(X):-X<0,write(negative),nl.

rl4:-consult('dogs4.pl').

mother(ann,henry).
mother(ann,mary).
mother(jane,mark).
mother(jane,francis).
mother(annette,jonathan).
mother(mary,bill).
mother(janice,louise).
mother(lucy,janet).
mother(louise,caroline).
mother(caroline,david).
mother(caroline,janet).

father(henry,jonathan).
father(john,mary).
father(francis,william).
father(francis,louise).
father(john,mark).
father(gavin,lucy).
father(john,francis).

%Extra----------------
father(steve,john).
father(quoll,steve).
%---------------------

parent(victoria,george).
parent(victoria,edward).

parent(X,Y):-mother(X,Y).
parent(X,Y):-father(X,Y).

parent(elizabeth,charles).
parent(elizabeth,andrew).

ancestor(X,Y):-parent(X,Y).
ancestor(X,Y):-parent(X,Z),ancestor(Z,Y).


response( no ) :- write( ' not have childs ' ).
response( Y ) :- not( Y = no ), write( ' have child: ' ), write( Y ).

child_of( A, B ) :- parent( A, Y ), parent( B, Y ),
                    write( A ), write( ' e ' ), write( B ),
                    response( Y ).

child_of( A, B ) :- not( parent( A, Y ) ),
                    write( A ), write( ' e ' ), write( B ),
                    response( no ).

child_of( A, B ) :- parent( A, Y ), not( parent( B, Y ) ),
                    write( A ), write( ' e ' ), write( B ),
                    response( no ).

grandfather_of( X ) :- father( Y, X ), write( ' GF = ' ), write( Y ).
grandmother_of( X ) :- mother( Y, X ), write( ' GM = ' ), write( Y ).

grandfather_of( A, B ) :- grandfather_of( A ).
grandfather_of( A, B ) :- grandfather_of( B ).

grandmother_of( A, B ) :- grandmother_of( A ).
grandmother_of( A, B ) :- grandmother_of( B ).

%Extra---------------------------------------
grandfather_of( A, B, Y ) :- father( Y, A ).
grandfather_of( A, B, Y ) :- father( Y, B ).
%--------------------------------------------

bisnonno( A, B ) :- grandfather_of( A, B, X ),
                    father( Y, X ), write( ' GGF = ' ), write( Y ).

% Any user-defined predicate with one argument (a unary predicate) can be
% converted to a prefix operator.
% isa_dog fred
% instead of
% isa_dog(fred)

likes( X, Y ) :- write( ' To ' ), write( X ), write( ' Like '), write( Y ).

% xfx, xfy or yfx meaning that the predicate is binary and is to be converted to an infix
% operator
% fx or fy meaning that the predicate is unary and is to be converted to an prefix
% operator
% xf or yf meaning that the predicate is unary and is to be converted to a postfix
% operator.

public(op/3).

%-Exemple---------------
% op( 150, xfy, likes).
% op( 150, fx, speed ).
%-----------------------

% sfortunamente op non è chiamabile da file.pl
% una volta modificato op, il comportamento delle Variabili,
% del Backtrack e degli atomi resterà uguale.

% rmangono comunque usabili a priori i seguenti codes ( 'liberi' ):
% X > Y.
% X >= Y.
% .......

% is e = sono due funzioni builtin con op(..) già preconfigurato,
% in modo da constire un loro uso slegato dalle parentesi come in python.
% differenze tra is e =:
%       is è ricorsivo e risolve x e y ( è un operatore binario ).
%	= è un operato anche esso binario ma si limita alla superficie.
