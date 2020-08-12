
rl7 :- consult( 'dogs7.pl' ).

% force to stop backtraking with !.

larger(A,B,A) :- A>B, !.
larger(A,B,B).

% cure repeat loop:

get_answer(Ans):- write('Enter answer to question'), nl,
                  repeat, write('answer yes or no: '), read(Ans),
                  valid(Ans),write('Answer is '), write(Ans), nl, !.

valid(yes). valid(no).

% è incerto se il repeat si interrompe normalmente e quindi questo era un errore,
% oppure anche normalmente il repeat non si interrompe: vedremo.

% cut = cure with Failure = fail.

bird(sparrow).
bird(eagle).
bird(duck).
bird(crow).
bird(ostrich).
bird(puffin).
bird(swan).
bird(albatross).
bird(starling).
bird(owl).
bird(kingfisher).
bird(thrush).

can_fly( ostrich ) :- !, fail.
can_fly(X) :- bird( X ).

% saggia decisione, `!` si attiva solo in caso di backtracking.
% è come un segnalino che avverte del backtraking, e risponde negativamente.

% As before, the can_fly(ostrich) goal is matched with the head of the first can_fly
% clause. Attempting to satisfy the goal in the body of that clause (i.e. fail) fails, but
% the cut prevents the system from backtracking and so the can_fly(ostrich) goal fails.
% The combination of goals !,fail is known as cut with failure.

% fail poi ! è scorretto perchè il bactraking equivale a un or.
% pure fail, !, fail è scorretto. perchè il fail dice semplicemente di interrompere quel match.
%
% ne deduco quindi che in ogni posiz. sia il `!`, dice semplicemente che finito quel match,
% si dovrà interrompere il backtraking.

% interessante:
factorial(1,R) :- R is 1, !.
factorial(N,X) :- N1 is N-1,
                  factorial( N1,R ),
                  X is N*R.
% to cut:
go :- write( 'go::' ), nl, repeat, read_and_check( N,Type ),
      write( N ), write(' have Type: ' ), write( Type ), nl, 
      Type>0, N is 100, !.

read_and_check( N, Type ) :- write( 'please enter N ' ), read( N ), nl,
                             ( ( integer( N ), Type is 1 ); Type is 0 ), !.

% ! non può fermare repeat fuori dalla sua funzione chiamante.
% ! this symbol make erase of variables, for every time that this function is called.

% in questo caso + probabilmente il ! ha la funzione di break,
% mi viene da pensare che interrompa bene lo stdin,
% e che quindi c'era o invio o un altro char in input ( in buffer ).

% quindi dentro un loop forzato da un repeat, dove le varibili,
% non sono riallocabili dalla ricorsione, è meglio usare il !, per forzare il loro erase.

% rendere un predicato dinamico == aggiornabile in live: dynamic( predicate/x ).
% aggiornare il predicato e aggiungere se non esiste ( come dinamico ):
%     assertz( fact ), assertz( rule );
%     assertz( Clause ) ; Quindi:
%          assertz( ( predicate:- ... ) ).
%
% elliminare:
%             retract( fact ) or retract( fact/0 ) --> non possibile,
%             retract( rule ) or retract( predicate ) --> non possibile,
%                    se ci si riferisce alla regola in se,
%             rectract( clauses ) --> possibile sse non ci si riferisce alla regola in se.
% è possibile usare le variabili per elliminare diverse clause.
% non è possibile elliminare con predicate/.., però si può usare il simbolo `_` come 'Tutti'.

% è importante l'uso di listing( predicate ).
% in listing è allow: predicate/..

exist( W, Z ) :- W == 'dog', dog( X ), X==Z.

insert( W, Z ) :- W == 'dog', assertz( dog(Z) ), write( Z ), write( ' is inserted' ).

add_data :- write( 'load_menu...' ), dynamic( dog/1 ), nl, nl, menu.

menu :- write( 'insert predicate/1: ' ), read( W ), nl, ( W=='end', !, fail; true ),
        write( 'atom for predicate: ' ), read( Z ), nl, ( Z=='end', !, fail; true ),
        ( exist( W, Z ); insert( W, Z ) ),
        write( 'show listing dog:' ), listing( dog ), menu.

display( W ) :- W == 'dog', nl, nl, dog( X ),
                write( 'exist animal ' ), write( W ),
                write( 'on database, with name: '), write( X ).

remove_dog( Name ) :- nl, exist( 'dog', Name ),
                      write( Name ), write( ' is delated' ), retract( dog( Name ) ), !;
                      write( Name ), write( ' not exist' ), nl, fail.

% preferisco la ricorsione al repeat.
% il repeat è in se machinnoso e buggato.
% il fail ferma la funzione, il true no, quindi si deve usare il `!` per creare l'xor.
