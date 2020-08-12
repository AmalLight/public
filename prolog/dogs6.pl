
% ho imparato che non è possibile passare una funfione in un'altra funzione,
%                 non è possibile passare una espressione matematica in una funzione,
%                 non è possibile assegnare variabili, l'unica opportunità è assegnare col match,
%                                                      l'unica opportunità è usare X is,
%                                                      is funziona sse la variabile è vuota.
%
%                 IL RITORNO DI UNA FUNZIONE È DATA SOLO:
%                 DALLA VARIABILE CHE È POSSIBILE LEGGERE DOPO IL MATCH.
%
%                 non è possibile eludere il matching!

% il LOOP:
% il loop avviene tramite un assegnamento iniziale e:
% un secondo assegnamento per far abbassare la variabile a -1.

loop(0).
loop(N) :- N>0, write('The value is: '), write(N), nl,
           M is N-1,loop(M).

% Altro esempio di loop.
% output_values(Last,Last) :- #FINISH!
% output_values(First,Last):- #...., N is First+1, output_values(N,Last).

% cosa fa ?
sumto(1,1).
sumto(N,S):-N>1,N1 is N-1,sumto(N1,S1),S is S1+N.

% mettiamo sum(N,X):
% sum( 3, X ) --> sum( 2, X ), X+N = X+3. 3+3 = 6.
% sum( 2, X ) --> sum( 1, X ), X+N = X+2 = 2. 1+2 = 3.
% sum( 1, 1 ) --> ritorna X = 1 poichè N <= 1.
%Quindi sum(N,X) | N=3, torna 6.

rl6 :- consult( 'dogs6.pl' ).

% Esercizio, scrivere uno square:
square( N, X ) :- X is N*N.

% esempio fatto dal libro:
% read_six(Infile):-seeing(S),see(Infile), process_terms(6),seen,see(S).
%
% process_terms(0).
% process_terms(N) :- N>0,read(X),write(X),nl,N1 is N-1,
%                     process_terms(N1).

% esempio basato su loop derministico:
% go:-loop(start).
%
% loop(end).
% loop(X) :- X\=end, write('Type end to end: '), read(Word),
%            write('Input was '), write(Word), nl, loop(Word).

% esempio loop 2:
% loop :- write('Type end to end: '), read(Word),
%         write('Input was '), write(Word),nl,
%         (Word=end;loop).
%
% interessante l'uso di parentesi per limitare l'or.
% la potenza e l'utilità delle parentesi sono pari solo al loro utilizzo.

%------------------------------------------------------
% repeat == +- continue della programmazione a oggetti
%------------------------------------------------------
% il repeat entra in azione sse Esiste almeno una,
% delle Variabili dichiarate successivamente che non matchano successivamente.
% `will always fail on backtracking`

% scoperta dal libro:
readterms(Infile) :- seeing(S),see(Infile),
                     repeat,read(X),write(X),nl,X=end,
                     seen,see(S).
% un fail si verifica se non si riesce ad arrivare al .
% ne deduco quindi che non esiste true o false in prolog,
%    ma il fails o il success che è +- simile ma non del tutto analogo.
%    Allora in fine il reapeat si aziona al fails.
%    ( il non matchin di una Variabile, genera un fails ).

% se una variabile ha tipo: riconosco_x_come(_).
% allora tutte le X mechano, e non si avrà fails, in questo caso.

% di base Prolog forza il Bactraking ad essere sempre attivo,
% e non si ferma al primo matching, bisogna stare attenti!!.

% Un mio test:
dog( martin ).
dog( fido ) :- write( 'fido is a special dog. ' ).
dog( seven ).
dog( pippo ) :- fail.
dog( freedom ) :- write( 'freedom is a special dog. ' ), fail.

% non segue un ordine alfabetico, ma segue l'ordine di stesura.
% con dog( X ). ho imparato che il Bactracking è forzato per tutti.
% Ora provo a escludere pippo dal matching:

% dog( X ) è sbagliato perchè le variabili non vengono salvate alla chiamata.
dogs( X ) :- ( X=pippo, write( X ), true ); ( dog( X ), write( X ) ).

% aggiungendo un altro cane 'freedom' con fail cosa succede ?
% il true di pippo potrà comunque mantenere coerenza,
% senza entrare in loop.

% è sbagliato perchè va contro il backtracking,
% ( non esiste un solo output ), tuttavia fa quello che desidero.
testme :- ( dogs( X ), write( ' is ok ' ) ); ( write( 'not ok ' ), fail ).

% ( X, write( ' is ok ' ); write( ' not ok ' ) ). 
% fa risultare freedom come true, anche se è palesemente fail.
% quindi è una sintassi sbagliata. ci vuole fail dopo not ok.
% ( per mantenere coerenza e avere il giusto ritorno ).

% Chapter Summary
% This chapter describes how a set of goals can be evaluated repeatedly in Prolog,
% either a fixed number of times or until a specified condition is met, and how
% multiple solutions can be arrived at using the technique of 'backtracking with
% failure'.

start_square( N1, N2 ) :- ( N1 > 6, N2 < 12, square2( 6, 12 ) );
                          ( N1 > 6, N2 > 11, square2( 6, N2 ) );
                          ( N1 < 7, N2 < 12, square2( N1, 12 ) );
                          ( N1 < N2+1, N1 < 7, N2 > 11, square2( N1, N2 ) );
                          N1 < N2.

square2( N1, N2 ) :- square( N1, X ),
                     write( N1 ), write( '^2 = ' ), write( X ), nl,
                     N3 is N1+1, N1 < N2,
                     square2( N3, N2 ).

% backtracking == or ( l'ho reso xor con > e < ).
% ; == or o xor ?

isOr( N ) :- ( N > 4, write( 1 ) );
             ( N > 6, write( 2 ) );
             ( N > 5, write( 3 ) ).

% ne deduco che ; == or.
% l'xor è artificiale.
% l'unica differenza con i linguaggi like c++ e java:
%
% il bactraking forza l'or a essere verboso:
% X < 6 && isOk( X ) in java a x < 6 ritorna true, senza valutare isOk,
% questo perchè le variabili non sono da cercare.
% in Prolog ogni predicato in or viene valutato.
% Solo l'end si comporta come si comporterebbe con il c++ o il java o il python ...

esercizio2 :- get0( X ), nl, write( 'Lettore:' ), nl, nl, next( X ), nl.

next(X):- ( not( ( X=42; X=39; X=46; X=10; X=63 ) ),
            put( X ), get0( Y ), next( Y ) );
           
          ( X=42; X=39; X=46; X=10; X=63 ), write( ' end. ' ).

% difference between get and get0:
%     get not read special_char,
%     get     read special_char.
%
% not possible to allor char on buffer with read.
% get or get0 not readb char from read( X ).
