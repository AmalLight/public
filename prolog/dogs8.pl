
rl8 :- consult( 'dogs8.pl' ).

%-------------
% List:
%-------------
%
%: [ Head  | [ el1, el2, el3, el4 ] ]
%            [ el1, el2, el3, el4 ] è una coda
%
%    Head è la testa.
%

% può andare bene per una Queue = lifo, arriverà per forza a [ Head | [] ].

% Stack = Fifo :: [ [ el1, el2, el3 ] | [ Tail ] ]

list1( X ) :- X = [ a, b, c, d, e, f ].

write_head1( [ Head, Tail ] ) :- write( Head ).      % work on [ a, [ b, c, d, e, f ] ].
write_head2( [ Head | Tail ] ) :- write( Head ).     % work on [ a, b, c, d, e, f ].
write_head3( [ Head | [ Tail ] ] ) :- write( Head ). % work on [ a, [ b, c, d, e, f ] ].

write_head4( [ Head, [ Tail ] ] ) :- write( Head ).  % work on [ a, [ [ b, c, d, e, f ] ] ].

% write_head2( [ Head | Tail ] ) work on list1( X ).
% write_head2 work on X.

% write_head2 is Decomposing a List.

lenght( [ H | T ], N ) :- Y is N+1, T \= [], lenght( T, Y ), N is Y.

contains( [ H | T ], E ) :- ( H=E, !; T \= [], contains( T, E ) ).

getIndex( [ H | T ], N, E ) :- Y is N-1, ( Y=0, E=H, !; ( T=[], E=none, !; getIndex( T, Y, E ) )).

addInHead( L1, E, L2 ) :- L2 = [ E | L1 ]. % aggiunta in testa.

% addInTail( L1, E, L2 ) :- reverse( L1, L3 ), addInHead( L3, E, L4 ), reverse( L4, L2 ).

addInTail( [ H | T ], E, L2 ) :- ( T = [], L3 = [ E | [] ], L2 = [ H | L3 ], !;
                                 addInTail( T, E, L3 ), L2 = [ H | L3 ] ).

% l'ultimo addInTail( [ H | T ], E, L2 ) è molto interessante:
% L2 diventa a ogni ricorsione L3 ( è nuovo = slegato = assegnabile ),
% dopo di che viene valutato e da L3 ritorna a essere L2, che però in quel caso,
% si riferisce a un nuovo L2 ancora mai assegnato.

view( [ H | T ] ) :- write( H ), write( ' ' ), ( T \= [], view( T ); true, ! ).

% Built-in Predicate: member
% The ability to represent data in the form of lists is such a valuable feature of Prolog
% that several built-in predicates have been provided for it. The most commonly used
% of these are described in this and the following sections.
% The member built-in predicate takes two arguments. If the first argument is any
% term except a variable and the second argument is a list, member succeeds if the
% first argument is a member of the list denoted by the second argument (i.e. one of
% its list elements).

% other user for member:
% ?- member(X,[a,b,c]).
% X = a;
% X = b;
% X = c;
% false.

% Built-in Predicate: length
% The length built-in predicate takes two arguments. The first is a list. If the second is
% an unbound variable it is bound to the length of the list, i.e. the number of elements
% it contains.

% Built-in Predicate: reverse
% The reverse built-in predicate takes two arguments. If the first is a list and the second
% is an unbound variable (or vice versa), the variable will be bound to the value of the
% list with the elements written in reverse orde.

% Built-in Predicate: append
% The term concatenating two lists means creating a new list, the elements of which
% are those of the first list followed by those of the second list. Thus concatenating
% [a,b,c] with [p,q,r,s] gives the list [a,b,c,p,q,r,s]. Concatenating [] with [x,y] gives [x,y].
% The append built-in predicate takes three arguments. If the first two arguments
% are lists and the third argument is an unbound variable, the third argument is bound
% to a list comprising the first two lists concatenated.

% Using findall/3 to Create a List
% It would often be desirable to find all the values that would satisfy a goal, not just
% one of them. The findall/3 predicate provides a powerful facility for creating lists
% of all such values. It is particularly useful when used in conjunction with the Prolog
% database.

% Interessante uso:

% findall(S,person(_,S,_,_),L).
% L = [smith,jones,wilson,smith,roberts]

% findall([Forename,Surname],person(Forename,Surname,_,_),L).
% L = [[john,smith],[mary,jones],[michael,wilson],[mark,smith],[henry,roberts]]

% findall([londoner,A,B],person(A,B,_,london),L).
% L = [[londoner,john,smith],[londoner,henry,roberts]]

% find_under_30s(L):-findall(Name,(age(Name,A),A<30),L).
% IF find_under_30s(L): L = [mary,henry,bill].

% Chapter Summary
% This chapter describes a flexible type of data object called a list. It shows how
% to work through a list element by element from left to right using recursion to
% perform the same or a similar operation on each element, how to manipulate lists
% using built-in predicates and how to create a list containing all the possible values
% that would satisfy a specified goal.

getAllTail( [ H | T ], L ) :- L = T.

inc( [ H | T ], L2 ) :- LH is H+1, ( T = [], L2 = [ LH | [] ], !; inc( T, L3 ), L2 = [ LH | L3 ] ).

palindrome( L1 ) :- reverse( L1, L2 ), L2 = L1.

first( L1, EL, L2 ) :- L2 = [ EL | L1 ].

putlast( L1, EL, L2 ) :- addInTail( L1, EL, L2 ).

% like member --> like a repeat
match( [ H | T ], L2 ) :- L2 = H; T \= [], match( T, L2 ).
% ; resetta L2 e lo rende libero.

pred2( L1, O ) :- findall( [X], match( L1, X ), O ).
pred3( L1, O ) :- findall( [pred(X,X)], match( L1, X ), O ).
pred4( L1, O ) :- findall( [pred(element,X)], match( L1, X ), O ).

% il repeat può essere creato con una ricorsione con or.
% ogni atomo di or che proviene dal chiamante,
%      lega solo con il caso attuale di or,
%      oppure lega solo con il padre di or.

% name/2 builtin convert list of integer to string.
% name/2 builtin convert string to list of integer.
% per unire 2 stringhe usare append delle liste ( usare le liste ).

% readline, difficile perchè X non viene salvato in ricorsione, X era separata da `;` :	
listline( L2 ) :- ( get0( X ), not(X is 10), listline( L3 ), L2 = [ X | L3 ], !; L2 = [] ).
striline( S2 ) :- listline( L2 ), name( S2, L2 ).

spalindrome( Stringa ) :- name( Stringa, Obl ), reverse( Obl, Obl2 ), Obl = Obl2.

getAfterX( [ H | T ], E, T2 ) :- ( T \= [], getAfterX( T, E, T3 ), 
                                   T3 \= none, H = E, T2 = T3, !);
                                 ( H = E, T2=T, !; T2=none ).

rLastWord( Stringa, X ) :- name( Stringa, O2 ), reverse( O2, O ),
                           getAfterX( O, 32, T ), 
                           ( T \= none, reverse( T, T2 ), name( X, T2 ), !;
                                        reverse( O, T2 ), name( X, T2 ) ).

% --------------------------------------------------------------------------------
% replace text
%----------------------------------------------------------------------------------

fromXtoAllT( [ H1 | T1 ], X, T ) :- ( T1=[], fail; H1=X, T=T1, !; fromXtoAllT( T1, X, T ) ).

% first after
after( L1, [ HX | TX ], A ) :- fromXtoAllT( L1, HX, A2 ), 
                               ( TX=[], A=A2, !; after( A2, TX, A ), !).

% U = union [ X | A ]
% bug di assegnamento :- B2 = [ H | B ] assegna implicitamente a B.

before( [ H | T ], U, B ) :- ( ( T=[]; T=U ), B=[H|[]], !; before( T, U, B2 ), B=[H|B2] ).

replace( L1, X, Y, O1 ) :- after( L1, X, A ),
                           append( X, A, U ),
                           before( L1, U, B ),
                           append( B, Y, O2 ), append( O2, A, O1 ).

%--------------------
% cheat
%--------------------

% call on file, after op mod, X iss Y :- X is Y.

% op( 700, xfy, iss ).

% Y iss A+B :- Y is A+B.
% Y iss A-B :- Y is A-B.
% Y iss A*B :- Y is A*B.
% Y iss A/B :- Y is A/B.
% Y iss A//B :- Y is A//B.
% Y iss A^B :- Y is A^B.
% Y iss +A :- Y is A.
% Y iss -A :- Y is -A.

% factorial( 1, 1 ) :- !.
% factorial( N, Y ) :- N1 is N-1, factorial( N1, Y1 ), Y is N*Y1.

% Y iss N! :- N1 iss N, factorial( N1, Y ).
% Y iss sqrt(A) :- A1 iss A, Y is sqrt( A1 ).
% Y iss A**B :- A1 iss A, B1 iss B, Y is A1*A1+B1*B1.

% in poche parole is è capace di inventare un suo linguaggio,
% ( azione e conseguenza ) basandosi su simboli normalmente matematici.

% S iss S1++S2 :- join2( S1, S2, S ). ecco creata l'aritmetica delle liste.

% convert( X, X ) :- atom( X ).
% convert( X, X1 ) :- X1 iss X.

% S iss S1++S2:- convert( S1, A ), convert( S2, B ), join2( A, B, S ).
