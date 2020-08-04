
% set is difference from list.

% set has: union, difference, intersection, ...
% to be to define by iss.

% Y sis A and B :- A1 sis A,B1 sis B,findall(X,(member(X,A1),member(X,B1)),Y).

% Y sis A or B :- A1 sis A,B1 sis B,findall(X,(member(X,A1);(member(X,B1),not(member(X,A1)))),Y).

% Y sis A-B :- A1 sis A,B1 sis B,findall(X,(member(X,A1),not(member(X,B1))),Y).

%------------------------------

% X =..[member,A,L ] == X = member(A,L).
% X =..[colour,red] == X = color(red).
% ?- colour(red) >> true.

% ?- data(6,green,mypred(26,blue))=..L >> L = [data,6,green,mypred(26,blue)].

% ?- X=write('hello world'),call(X). >>
%       hello world
%       X = write('hello world').
% call esegue il contenuto di una variabile.

% The functor/3 Predicate -built-in
% The built-in predicate functor/3 takes three arguments. If the first argument is an
% atom or a compound term or a variable bound to one of those, and the other two
% arguments are unbound, the second argument will be bound to the functor of the
% first argument and the third will be bound to its arity. For this purpose an atom is
% considered to have arity zero.

% ?- functor(a+b,F,A). >> F = (+) , A = 2.

% The arg/3 Predicate -built-in
% The built-in predicate arg/3 can be used to find a specified argument of a compound
% term. The first two arguments must be bound to a positive integer and a compound
% term, respectively. If the third argument is an unbound variable, it is bound to the
% value of the specified argument of the compound term.
% ?- arg(3,person(mary,jones,doctor,london),X).
% X = doctor

% ?- N=2,T=person(mary,jones,doctor,london),arg(N,T,X).
% N = 2,
% T = person(mary,jones,doctor,london) ,
% X = jones

%-----------------------------------------------------------------------------

rl9 :- consult( 'dogs9.pl' ).

% ?- op( 700, xfy, easy ).
% ?- op( 700, fx, head ).

% fx su head vuol dire che accetta la grammatica e la lega come funzione,
% ma attenzione a chiamare head(X), da errore, non c'è match.

easy( X, Y ) :- functor(Y,N,A), ( ( N=head; N=tail ), A is 1  ), arg( 1, Y, L ),
                C=[N,L,X], C2=..C, call(C2), !.

% C=[N,L,X] crea un nuovo insieme, poichè call non può eseguire una Variabile dentro l'altra.

tail( [ H | T ], V ) :- reverse( [ H | T ], L2 ), head( L2, V ).
head( [ H | T ], V ) :- V=H.

collectArg( X, A, L1 ) :- ( A>0, arg( A, X, Atom ), A2 is A-1,
                            collectArg( X, A2, L2 ), A3 = [ Atom | [] ], append( L2, A3, L1 ), !;
                            A=0, L1=[] ).

addArg( X, Y, T ) :- functor(X,N,A), collectArg(X,A,L1), L2=[N|L1], 
                     Y2 = [ Y | [] ], append( L2, Y2, L3 ),
                     X2=..L3, T=X2.

%-----------------------------------------------------------------------------
% AI
%-----------------------------------------------------------------------------

% nomi generali di oggetto o essere vivente = noun.
% altricoli determinativi e non = determiner.
% aggettivi = adjective.
% verbi = verb.

% The –>/2 operator can be read as 'is a' or 'comprises' or 'is made up of'. So the first
% clause indicates that a sentence can comprise a noun, followed by a verb, followed
% by a noun. As usual in Prolog we place the more specific clause before the more
% general one. (Note that the –> operator is three keystrokes: two hyphens followed
% by a 'greater than' symbol.)
% This would be a possible way of defining sentences, but is very limited. It
% would allow 'man saw' and 'man saw dog' but not 'the man saw a dog'. Our
% first improvement to the above prototype program will be to change noun to
% 'noun_phrase' which we will define as an optional determiner followed by a noun.
% (The words 'the', 'a' and 'an' are called determiners.)
% This change brings us closer to a usable definition of a sentence, but we also need
% to define some nouns and verbs. Putting all these definitions together gives us a first
% version of a Prolog program defining the grammar of a very restricted version of
% English.

% in pratica `-->`:
% usa gli atomi come se fossero variabili ( variabili interne non modificabili ).
% per considerare gli atomi in modo coerente ( atomico ), è necessario:
% racchiudere l'elemento in un insieme :: [ atomo ].

% salto capitolo 12 e 13.
