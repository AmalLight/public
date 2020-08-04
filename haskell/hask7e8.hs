
-- MAKING OUR OWN TYPES AND TYPE CLASSES

-- tools for create atom, ajective and ecc

data Atom1 = True | False
data Atom2 = Atom1 | Num

-- IN PUT AND OUTPUT

-- like c++ cout << putSrtln

cout x = putStrLn x
main = cout "hello World" -- main for compiler in c

x = "casa"

cin = do
    x <- getLine
    return x
-- x is not global

-- Using let Inside I/O Actions
-- main = do
--     putStrLn "What's your first name?"
--     firstName <- getLine
--     putStrLn "What's your last name?"
--     lastName <- getLine

--     let bigFirstName = map toUpper firstName
--         bigLastName = map toUpper lastName
--     putStrLn $ "hey " ++ bigFirstName ++ " "
--                       ++ bigLastName
--                       ++ ", how are you?"
-- in do let doesn't have need to in,
-- comunque può usare funzioni esterne

-- Other Out: putStrLn, putStr, putChar
--            putStr ".."
--            putChar '.'
--            print( { [List], string, char, tuple, .. })

-- without do:
fun_wd = print "casa"
fun_d = do print "casa"

-- do è un lambda particolare,
-- visto che main non lo necessita,
-- ne deduco che do sia una lambda particolare da evitare.
-- lo scopo è di evitare di diventare schiavi della sintassi.

-- when ( import Control.Monad ), da ignorare.
-- sequence da ignorare
-- altre funzioni da Monad sono da ignorare.
