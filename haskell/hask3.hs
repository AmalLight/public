
-- Pattern Matching
--         Pattern Matching with Tuples:

addVectors :: (Double, Double) -> (Double, Double) -> (Double, Double)
addVectors a b = (fst a + fst b, snd a + snd b)
-- addVectors ( 1, 2 ) ( 3, 4  ) >> out: ( 4.0, 6.0 )

-- remember _ for pattern with all

head' :: [a] -> a
head' [] = error "Can't call head on an empty list, dummy!"
head' (x:_) = x

firstLetter :: String -> String
firstLetter "" = "Empty string, whoops!"
firstLetter all@(x:xs) = "The first letter of " ++ all ++ " is " ++ [x]

testme all@(x:xs) = x
-- vale per stringhe >> crea lista >> esce testa della lista

-------------------------
-- Guards, Guards!
-------------------------

a = "casa"
b = "base"
c = "letto"

-- fun1 a = print 'A'
-- a non viene considerato "casa", ma una variabile vuota,
-- a viene riempita dall'argomento,

fun1 "casa" = print 'A'
fun1 "base" = print 'B'
fun1 "letto" = print 'C'

-- errore perchè se: d = a, fun1 d = fun1 a

fun1 _ = print 'D'

-- a fun1 _ non ci arriva, il backtrack qui è diverso.

fun2 v
     | v == "casa" = 'A'
     | v == "base" = 'B'
     | v == "letto" = 'C'
     | True = 'D'

-- otherwise == True == else ma non viene eseguiti se c'è un v === ..


----------------------
-- Test2
----------------------

fun3 num
    | num*2 == num+1 = "match *2"
    | num+1 == num*2 = "match +1"

-- il backtrack non funziona neanche quando è sensato
-- il true in prolog era senza senso

fun4 num
    | num*2 == num+1 = "match *2"
    | otherwise = "match +1" --poteva che otherwise era diverso da else, invece no

-- il where può andare sotto l'ultimo |

-- il guards attuale è un xor
-- il backtrack fatto di liste è un vero e proprio foreach == backtrack
-- il problema è che diventa difficile da modellare, in prolog era + ottimizzato

------------------------------------------------------------------------------

cylinder r h =
         let sideArea = 2 * pi * r * h
             topArea = pi * r ^ 2
         in sideArea + 2 * topArea

-- way: dichiara sotto funzioni,
--      e poi le esegue, in esegue funzioni del programma ( funzione ),
--      senza in, sideArea non può essere usato, perchè non è globale.

-- no in in list
-- xs = [ bmi | (w, h) <- xs, let bmi = w / h ^ 2 ]

------------------------------------------------------------------------------

-- case Expressions: non è programmazione funzionale è + object-oriented

describeList :: [a] -> String
describeList ls = "The list is " ++ what ls
                  where what [] = "empty."
                        what [x] = "a singleton list."
                        what xs = "a longer list."
-- logic-oriented
