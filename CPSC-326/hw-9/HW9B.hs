{-
   Name: Linden Beemer
   File: HW9B.hs
   Date: Spring 2022
   Desc: implements the following functions w/pattern matching
-}


module HW9B (
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


-- TODO: Implement the following functions USING PATTERN MATCHING. You
-- CANNOT use any if-then-else expressions in your
-- implementations. Again, provide the function types for each
-- function (see HW9A.hs for an example). 

-- (1). myReverse
myReverse :: [a] -> [a]
myReverse [] = []
myReverse (x:xs) = (myReverse xs) ++ [x]

-- (2). myLast 
myLast :: [a] -> a
myLast [] = error "Empty List"
myLast xs 
  | (length xs) == 1 = head xs
myLast (_:xs) = myLast xs

-- (3). myInit
myInit :: [a] -> [a]
myInit [] = error "Empty List"
myInit xs 
  | (length xs) == 1 = [head xs]
  | (length xs) == 2 = [head xs]
myInit (x:xs) = [x] ++ myInit xs

-- (4). myMemb 
myMemb :: Eq a => a -> [a] -> Bool
myMemb n [] = False
myMemb n xs 
  | (head xs) == n = True
myMemb n (_:xs) = myMemb n xs

-- (5). myReplace
myReplace :: Eq a => (a,a) -> [a] -> [a]
myReplace (_,_) [] = []
myReplace (a,b) (x:xs) 
  | a == x = b : myReplace (a,b) xs
  | otherwise = x : myReplace (a,b) xs

-- (6). myReplaceAll
myReplaceAll :: Eq a => [(a,a)] -> [a] -> [a]
myReplaceAll [] xs = xs
myReplaceAll (x:ys) xs = myReplaceAll ys (myReplace x xs)

-- (7). myElemSum
myElemSum :: Int -> [Int] -> Int
myElemSum _ [] = 0
myElemSum n (x:xs)
  | n == x = n + myElemSum n xs
  | otherwise = 0 + myElemSum n xs

-- (8). myRemDups
myRemDups :: Eq a => [a] -> [a]
myRemDups [] = []
myRemDups (x:xs)
  | myMemb x xs = myRemDups xs
  | otherwise = x : myRemDups xs

-- (9). myListMax (i know length is slow but im not sure how else to do this)
myListMax :: [Int] -> Int
myListMax [] = error("Empty List")
myListMax xs | length xs <= 1 = head xs
myListMax (x:xs) 
  | m > x = m
  | otherwise = x
  where m = myListMax xs

-- (10). myMergeSort
myMergeSort :: Ord a => [a] -> [a]
myMergeSort [] = []
myMergeSort xs 
  | length xs == 1 = xs
  | otherwise = merge (myMergeSort (take mid xs)) (myMergeSort (drop mid xs))
        where 
          mid = (length xs) `div` 2
          merge [] [] = []
          merge xs ys
            | null ys = [head xs] ++ merge (drop 1 xs) []
            | null xs = [head ys] ++ merge [] (drop 1 ys)
            | (head xs) <= (head ys) = [head xs] ++ merge (drop 1 xs) ys
            | otherwise = [head ys] ++ merge xs (drop 1 ys)