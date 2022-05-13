{-
  Name:
  File: main.hs
  Date: Spring 2022
  Desc: Basic tests for HW10. To execute from the command line using
        ghci, run: ghci main.hs -e main
-}

import HW10

-- TODO: Add additional set examples as needed here
s1 = Elem 'a' (Elem 'c' (Elem 'd' (Elem 'b' (Elem 'e' EmptySet))))
s2 = add 'f' s1
s3 = remove 'f' s2
s4 = Elem 'a' (Elem 'b' EmptySet)
s5 = Elem 'b' (Elem 'c' EmptySet)
s6 = union s4 s5
s7 = intersect s4 s5
s8 = intersect s4 s6
s9 = difference s1 s4
s10 = Elem 1 (Elem 2 (Elem 3 EmptySet))
s11 = filterSet odd s10
l1 = toList s1


-- TODO: Add additional tests to for hw10 below
main = do
  -- member tests
  putStrLn (assertTrue (member 'a' s1) "member 1")    
  putStrLn (assertTrue (member 'b' s1) "member 2")    
  putStrLn (assertTrue (member 'c' s1) "member 3")    
  putStrLn (assertTrue (member 'd' s1) "member 4")
  putStrLn (assertTrue (member 'e' s1) "member 5")
  putStrLn (assertFalse (member 'f' s1) "member 6")
  -- add tests
  putStrLn (assertTrue (member 'a' s2) "add 1")  
  putStrLn (assertTrue (member 'b' s2) "add 2") 
  putStrLn (assertTrue (member 'c' s2) "add 3") 
  putStrLn (assertTrue (member 'd' s2) "add 4") 
  putStrLn (assertTrue (member 'e' s2) "add 5") 
  putStrLn (assertTrue (member 'f' s2) "add 6") 
  -- remove tests
  putStrLn (assertTrue (member 'a' s3) "remove 1")    
  putStrLn (assertTrue (member 'b' s3) "remove 2")    
  putStrLn (assertTrue (member 'c' s3) "remove 3")    
  putStrLn (assertTrue (member 'd' s3) "remove 4")
  putStrLn (assertTrue (member 'e' s3) "remove 5")
  putStrLn (assertFalse (member 'f' s3) "remove 6")
  -- size tests
  putStrLn (assertEqual 2 (size s4) "size 1")    
  putStrLn (assertEqual 5 (size s1) "size 2")
  putStrLn (assertEqual 6 (size s2) "size 3")
  -- subset tests
  putStrLn (assertTrue (subset s4 s1) "subset 1")    
  putStrLn (assertTrue (subset s1 s2) "subset 1")    
  putStrLn (assertFalse (subset s2 s1) "subset 1")
  -- union tests
  putStrLn (assertTrue (member 'a' s6) "union 1")    
  putStrLn (assertTrue (member 'b' s6) "union 2")    
  putStrLn (assertTrue (member 'c' s6) "union 3")  
  putStrLn (assertEqual 3 (size s6) "union 4") 
  -- intersect tests
  putStrLn (assertFalse (member 'a' s7) "intersect 1")    
  putStrLn (assertTrue (member 'b' s7) "intersect 2")    
  putStrLn (assertFalse (member 'c' s7) "intersect 3")  
  putStrLn (assertEqual 1 (size s7) "intersect 4") 
  -- difference tests
  putStrLn (assertFalse (member 'a' s9) "difference 1")    
  putStrLn (assertFalse (member 'b' s9) "difference 2")    
  putStrLn (assertTrue (member 'c' s9) "difference 3")    
  putStrLn (assertTrue (member 'd' s9) "difference 4")
  putStrLn (assertTrue (member 'e' s9) "difference 5")
  putStrLn (assertEqual 3 (size s9) "difference 6") 
  -- filterSet tests
  putStrLn (assertTrue (member 1 s11) "filterSet 1")    
  putStrLn (assertTrue (member 3 s11) "FilterSet 2") 
  putStrLn (assertEqual 2 (size s11) "filterSet 3") 
  -- toList tests
  putStrLn (assertEqual ['a','c','d','b','e'] (toList s1) "toList 1") 
  putStrLn (assertEqual ['a','b'] (toList s4) "toList 2") 
  putStrLn (assertEqual [1,3] (toList s11) "toList 3") 



  
assertEqual :: (Show a, Eq a) => a -> a -> String -> String
assertEqual x y s =
  if x == y then
    s ++ " [Pass]"
  else
    s ++ " [Fail] ... expecting " ++ (show x) ++ " found " ++ (show y)


assertTrue :: Bool -> String -> String
assertTrue x s = assertEqual True x s


assertFalse :: Bool -> String -> String
assertFalse x s = assertEqual False x s

