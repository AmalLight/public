
-- Recursion

-- create list on recursion with `:`
replicate' :: Int -> a -> [a]
replicate' n x
    | n <= 0 = []
    | otherwise = x : replicate' (n-1) x

-- il repeat può essere infinite volte se si pensa al pattern matching
-- :  funziona su elementi di liste x già [x], ci vuole : []
-- ++ funziona su liste già chiuse e aggiunge in coda.

-- create reverse:

reverse' [] = []
reverse' (h:t) = reverse' t ++ [h]

-- [h:t] and h:t doesn't work
-- [x] : y non funziona ed è logico che non funzioni,
-- [x] : [y] non funziona ed è logico che non funzioni,
-- solo >> [x] : [y] : [] funziona.
-- solo >> [x] : [ y : [] ] funziona.

---------------------------------------------------------------------------
-- HIGHER-ORDER FUNCTIONS
---------------------------------------------------------------------------

-- if
multThree x y z = x * y * z
-- and
multTwoWithNine = multThree 9
-- so
-- multTwoWithNine 2 3, produce >> 54

-- Some Higher-Orderism Is in Order

applyTwice :: (a -> a) -> a -> a
applyTwice f x = f (f x)

-- The Functional Programmer’s Toolbox

map' :: (a -> b) -> [a] -> [b]
map' _ [] = []
map' f (x:xs) = f x : map' f xs

-- map like foreach

filter' :: (a -> Bool) -> [a] -> [a]
filter' _ [] = []
filter' p (x:xs)
         | p x = x : filter' p xs
         | otherwise = filter' p xs

-- filter produce a new list sse f el = true
-- even like pari o dispari.

-- More Examples of map and filter

largestDivisible :: Integer
largestDivisible = head (filter p [100000,99999..])
                   where p x = x `mod` 3829 == 0

-- other built-in
-- takewhile f [insieme] : come suggerito prende finchè f vale per l'elemento
-- ogni volta che compare [insieme] si può sostituire anche da [ x | x <- [...] ]

-- creo il takewhile
takeW _ [] = [] 
takeW f (h:t) = if f h then h : takeW f t; else []

-- remember good lambda ( ( \x -> .. ) () )

-- Fold = piegare = collassare = avvolgere = chiudere
-- è una famiglia di funzioni che data una funzione e una lista:
-- esegue la funzione su ogni elemento della lista, tornando però un singolo elemento.
-- collassatore dell'intera lista.
-- il fold permette tipo il sum di una lista.

sum' :: (Num a) => [a] -> a
sum' xs = foldl ( \ acc x -> acc + x ) 0 xs

---------------
-- Fold
---------------

-- ( \x -> x ) [6, 7] work, out: [list]!
-- ( \x -> x+1 ) [6, 7] not work! [list]+1 non ha senso

-- map ( \x -> x+1 ) [6, 7] work, out: [list+1]!

-- foldl ( \x -> x+1 ) [6, 7] not work!
-- foldl ( \ int x -> int + x ) 0 [6, 7] work!

-- fold spacchetta una lista e la rimpacchetta secondo ( .. -- X ), la X.
-- quindi il foldl di prima equivale a una catenza f tra tutti gli elementi [lista]:
foldl' f init [] = init
foldl' f init (h:t) = 
              let r = f init h
              in foldl' f r t
-- per le funzioni ci vuole (..)

-- foldr == foldl, but it fold only true f for a [lista]
map'' f [] = []
map'' f (h:t) =
        let r = if f h then [h]; else []
        in r ++ map'' f t

map''' f l =
       let r x = if f x then [x]; else []
       in foldl ( \prec next -> prec ++ r next ) [] l

-- haskell è capace di memorizzare il return con foldl!

-- foldl1 and foldr1: do not need to provide them with an explicit starting accumulator

-- Like c++
True && x = x
False && _ = False

-- Function Application with $, for remove `(` and `)`
-- fold_sum l = foldl $ \p n -> p+n 0 l
-- error, work only sse $ include (all_body).
-- sum (filter (> 10) (map (*2) [2..10]))
-- sum $ filter (> 10) (map (*2) [2..10])
-- sum $ filter (> 10) $ map (*2) [2..10]
