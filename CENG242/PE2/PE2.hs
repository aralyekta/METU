module PE2 where

---------------------------------------------------------------------------------------------
------------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
--------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
--------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
---------------------------------------------------------------------------------------------

-- Note: undefined is a value that causes an error when evaluated. Replace it with
-- a viable definition! Name your arguments as you like by changing the holes: _

--------------------------
-- Part I: Time to inf up!

-- naturals: The infinite list of natural numbers. That's it!
naturals :: [Integer]
naturals = [0..]

-- interleave: Interleave two lists, cutting off on the shorter list.
interleave :: [a] -> [a] -> [a]
interleave list1 list2 = interleaveHelper 1 list1 list2 where
                            interleaveHelper 1 [] _ = []
                            interleaveHelper 1 _ [] = []
                            interleaveHelper 2 _ [] = []
                            interleaveHelper 1 (x:xs) list2 = x:(interleaveHelper 2 xs list2)
                            interleaveHelper 2 list1 (y:ys) = y:(interleaveHelper 1 list1 ys)

-- integers: The infinite list of integers. Ordered as [0, -1, 1, -2, 2, -3, 3, -4, 4...].
integers :: [Integer]
integers = 0:(interleave [-1,-2..] [1..])

--------------------------------
-- Part II: SJSON Prettification

-- splitOn: Split string on first occurence of character.
splitOn :: Char -> String -> (String, String)
splitOn _ [] = ("","")
splitOn char (x:xs) | x == char = ("",xs)
                    | otherwise = (([x] ++ first), second)
                    where
                        recursiveResult = splitOn char (xs)
                        first = fst recursiveResult
                        second = snd recursiveResult


-- tokenizeS: Transform an SJSON string into a list of tokens.
tokenizeS :: String -> [String]
tokenizeS [] = []
tokenizeS (x:xs) | (x == '{') || (x == '}') || (x == ':') || (x == ',') = [[x]] ++ (tokenizeS xs) 
                 | (x == ' ') || (x == '\t') || (x == '\n') = (tokenizeS xs)
                 | otherwise = [first] ++ (tokenizeS second)
                 where
                     recursiveResult = splitOn x xs
                     first = fst recursiveResult
                     second = snd recursiveResult


-- prettifyS: Prettify SJSON, better tokenize first!
prettifyS :: String -> String
prettifyS [] = []
prettifyS str = prettifyHelper 0 True tokenList where
                tokenList = tokenizeS str
                prettifyHelper _ _ [] = []
                prettifyHelper indent willIndent (x:xs) | (x == "{" && willIndent) = (take indent $ cycle " ") ++ x ++ "\n" ++ prettifyHelper (indent+4) True xs
                                                        | (x == "{" && not willIndent) = x ++ "\n" ++ prettifyHelper (indent+4) True xs
                                                        | (x == "}") = "\n" ++ (take (indent-4) $ cycle " ") ++ x ++ prettifyHelper (indent-4) True xs
                                                        | (x == ":") = x ++ " " ++ prettifyHelper indent False xs
                                                        | (x == ",") = x ++ "\n" ++ prettifyHelper indent True xs
                                                        | willIndent = (take indent $ cycle " ") ++ "'" ++ x ++ "'" ++ prettifyHelper indent True xs
                                                        | otherwise = "'" ++ x ++ "'" ++ prettifyHelper indent True xs

-- Good luck to you, friend and colleague!

