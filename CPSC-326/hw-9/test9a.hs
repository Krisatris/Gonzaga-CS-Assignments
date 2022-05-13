{-
  Name:
  File: test9a.hs
  Date: Spring 2022
  Desc: Basic tests for HW9. To execute from the command line using
        ghci, run: ghci test9a.hs -e main
-}

import HW9A

-- TODO: Add additional tests to for hw9a below
main = do
  -- my reverse tests
  putStrLn (assertTrue (null (myReverse [])) "myReverse 1")    
  putStrLn (assertEqual [1] (myReverse [1]) "myReverse 2")  
  putStrLn (assertEqual [2,1] (myReverse [1,2]) "myReverse 3")
  putStrLn (assertEqual ['a'..'z'] (myReverse ['z','y'..'a']) "myReverse 4")
  -- my last tests
  putStrLn (assertEqual 1 (myLast [1]) "myLast 1")
  putStrLn (assertEqual 2 (myLast [1,2]) "myLast 2")
  putStrLn (assertEqual 'z' (myLast ['a'..'z']) "myLast 3")
  -- my init tests
  putStrLn (assertEqual [1] (myInit [1]) "myInit 1")
  putStrLn (assertEqual [1] (myInit [1,2]) "myInit 2")
  putStrLn (assertEqual ['a'..'y'] (myInit ['a'..'z']) "myInit 3")
  -- my memb tests
  putStrLn (assertEqual False (myMemb 0 [1]) "myMemb 1")
  putStrLn (assertEqual False (myMemb 3 [1, 2, 4, 5]) "myMemb 2")
  putStrLn (assertEqual True (myMemb 's' ['a'..'z']) "myMemb 3")
  -- my replace tests
  putStrLn (assertEqual [1, 8, 3, 8] (myReplace (2,8) [1, 2, 3, 2]) "myReplace 1")
  putStrLn (assertEqual [10, 2, 3, 4, 5] (myReplace (1,10) [1, 2, 3, 4, 5]) "myReplace 2")
  putStrLn (assertEqual ['a','b','c','a'] (myReplace ('z','a') ['a','b','c','z']) "myReplace 3")
  -- my replace all tests
  putStrLn (assertEqual [1, 10, 3, 10] (myReplaceAll [(2,8), (8, 10)] [1, 2, 3, 2]) "myReplaceAll 1")
  putStrLn (assertEqual [10, 2, 3, 4, 5] (myReplaceAll [(1,10)] [1, 2, 3, 4, 5]) "myReplaceAll 2")
  putStrLn (assertEqual ['a','e','c','a'] (myReplaceAll [('z','a'), ('b','e')] ['a','b','c','z']) "myReplaceAll 3")
  -- my elem sum tests
  putStrLn (assertEqual 10 (myElemSum 10 [10, 20, 25]) "myElemSum 1")
  putStrLn (assertEqual 12 (myElemSum 3 [3, 3, 3, 3]) "myElemSum 2")
  putStrLn (assertEqual 4 (myElemSum 2 [1, 1, 2, 2, 3, 3]) "myElemSum 3")
  -- my rem dup tests
  putStrLn (assertEqual [10, 20, 25] (myRemDups [10, 20, 25]) "myRemDups 1")
  putStrLn (assertEqual [3] (myRemDups [3, 3, 3, 3]) "myRemDups 2")
  putStrLn (assertEqual [1, 2, 3] (myRemDups [1, 1, 2, 2, 3, 3]) "myRemDups 3")
  -- my list max tests
  putStrLn (assertEqual 25 (myListMax [10, 20, 25]) "myListMax 1")
  putStrLn (assertEqual 3 (myListMax [3, 3, 3, 3]) "myListMax 2")
  putStrLn (assertEqual 12 (myListMax [7, 1, 9, 12, 10]) "myListMax 3")
  -- my merge sort tests
  putStrLn (assertEqual [1, 2] (myMergeSort [1, 2]) "myMergeSort 1")
  putStrLn (assertEqual [6, 7, 8, 9] (myMergeSort [9, 8, 7, 6]) "myMergeSort 2")
  putStrLn (assertEqual [1..10] (myMergeSort [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]) "myMergeSort 3")
 

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

