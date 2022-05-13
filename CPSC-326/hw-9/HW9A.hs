{-
   Name: Linden Beemer
   File: HW9A.hs
   Date: Spring 2022
   Desc: implements the following functions w/out pattern matching
-}


module HW9A (
  myReverse,
  myLast,
  myInit,
  myMemb,
  myReplace,
  myReplaceAll,
  myElemSum,
  myRemDups,
  myListMax,
  myMergeSort
) where


-- TODO: Implement the following functions WITHOUT USING pattern
-- matching, and instead using if-then-else. For each function,
-- provide the function type. An example is provided for (1), however,
-- the actual definition is still required. 


-- (1). myReverse
myReverse :: [a] -> [a]
myReverse xs = 
  if (length xs) == 0
    then error "empty list"
  else if (length xs) == 1
    then xs
  else myReverse(tail xs) ++ [head xs]

-- (2). myLast 
myLast :: [a] -> a
myLast xs =
  if (length xs) == 1
    then (head xs)
  else myLast (tail xs)

-- (3). myInit
myInit :: [a] -> [a]
myInit xs = 
  if (length xs) == 1 || (length xs) == 2
    then [head xs]
  else [head xs] ++ myInit(tail xs)

-- (4). myMemb 
myMemb :: Eq a => a -> [a] -> Bool
myMemb x xs = 
  if null xs
    then False
  else (if (head xs) == x 
    then True
  else myMemb x (tail xs))

-- (5). myReplace
myReplace :: Eq a => (a,a) -> [a] -> [a]
myReplace xt xs = 
  if null xs
    then xs
  else (if (fst xt) == (head xs)
    then (snd xt) : (myReplace xt (tail xs))
  else (head xs) : myReplace xt (tail xs))

-- (6). myReplaceAll
myReplaceAll :: Eq a => [(a,a)] -> [a] -> [a]
myReplaceAll xts xs =
  if null xts
    then xs
  else myReplaceAll (tail xts) (myReplace (head xts) xs)

-- (7). myElemSum
myElemSum :: Int -> [Int] -> Int
myElemSum x xs =
  if null xs
    then 0
  else (if (head xs) == x
    then x + myElemSum x (tail xs)
  else 0 + myElemSum x (tail xs))

-- (8). myRemDups
myRemDups :: Eq a => [a] -> [a]
myRemDups xs =
  if null xs
    then xs
  else (if myMemb (head xs) (tail xs)
    then myRemDups (tail xs)
  else (head xs) : myRemDups (tail xs))

-- (9). myListMax (i know length is slow but im not sure how else to do this)
myListMax :: [Int] -> Int
myListMax x = 
  if length x <= 1
    then (head x)
  else
    let m = myListMax (tail x) in
      if m > (head x)
        then m
      else (head x)

-- (10). myMergeSort
myMergeSort :: Ord a => [a] -> [a]
myMergeSort xs =
  if null xs
    then xs
  else if length xs == 1
    then xs
  else
    let mid = (length xs) `div` 2 in
      merge (myMergeSort (take mid xs)) (myMergeSort (drop mid xs))
    where 
      merge xs ys = 
        if null xs && null ys
          then []
        else if null ys
          then [head xs] ++ merge (drop 1 xs) []
        else if null xs
          then [head ys] ++ merge [] (drop 1 ys)
        else if (head xs) <= (head ys)
          then [head xs] ++ merge (drop 1 xs) ys
        else
          [head ys] ++ merge xs (drop 1 ys)