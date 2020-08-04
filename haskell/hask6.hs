import Data.List
import Data.Map
import Data.Set

-- you can selectively import just those functions. For example:
-- import Data.List( x, y, .. )

-- Solving Problems with Module Functions
-- group x, sort x, f . g, tails x, x `isPrefixOf` y,
-- any f y, ord x, encode num s, decode num s,
-- digitToInt s, find f y.

-- pag 118: Almost As Good: Association Lists
-- Almost As Good: Association Lists =: Dictionary

phoneBook =
      [  ( "betty",   "555-2938" )
        ,( "bonnie",  "452-2928" )
        ,( "patsy",   "493-2928" )
        ,( "lucille", "205-2928" )
        ,( "wendy",   "939-8282" )
        ,( "penny",   "853-2492" )
      ]

getValue key ([]) = "nothing"
getValue key (h:t) = if fst h == key then snd h
                     else getValue key t

----------------------------------------------------
-- Making Our Own Modules
----------------------------------------------------
-- A Geometry Module like a class in java or c++
----------------------------------------------------
-- import Geometry, see Geometry.hs
----------------------------------------------------

-- used of import qualified:
-- import qualified Geometry.Sphere as Sphere
-- import qualified Geometry.Cuboid as Cuboid
-- import qualified Geometry.Cube as Cube
