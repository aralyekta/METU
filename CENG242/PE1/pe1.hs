module PE1 where

import Text.Printf


-- This function takes a Double and rounds it to 2 decimal places as requested in the PE --
getRounded :: Double -> Double
getRounded x = read s :: Double
               where s = printf "%.2f" x

-------------------------------------------------------------------------------------------
----------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
-------------------------------------------------------------------------------------------

convertTL :: Double -> String -> Double
convertTL money "USD" = getRounded (money / 8.18)
convertTL money "EUR" = getRounded (money / 9.62)
convertTL money "BTC" = getRounded (money / 473497.31)

-------------------------------------------------------------------------------------------

countOnWatch :: [String] -> String -> Int -> Int
countOnWatch _ _ 0 = 0
countOnWatch [] _ _ = 0
countOnWatch (x:xs) employee days | (x == employee) = 1 + countOnWatch xs employee (days-1)
                                  | otherwise = countOnWatch xs employee (days-1)


-------------------------------------------------------------------------------------------

encryptDigit :: Int -> Int
encryptDigit x | (x `mod` 3 == 0) = x-1
               | (x `mod` 4 == 0) = (x * 2) `mod` 10
               | (x `mod` 5 == 0) = (x + 3) `mod` 10
               | otherwise = (x + 4) `mod` 10


encrypt :: Int -> Int
encrypt x = let firstDigit = x `div` 1000 `mod` 10
                secondDigit = x `div` 100 `mod` 10
                thirdDigit = x `div` 10 `mod` 10
                fourthDigit = x `div` 1 `mod` 10
            in read (show (encryptDigit firstDigit) ++ show (encryptDigit secondDigit)
             ++ show (encryptDigit thirdDigit) ++ show (encryptDigit fourthDigit))

-------------------------------------------------------------------------------------------

compoundInterest :: (Double, Int) -> Double
compoundInterest (money, year) | (money >= 10000 && year >= 2) = getRounded (money * (1 + 11.5/1200)^(12 * year))
                               | (money < 10000 && year >= 2) = getRounded (money * (1 + 9.5/1200)^(12 * year))
                               | (money >= 10000 && year < 2) = getRounded (money * (1 + 10.5/1200)^(12 * year))
                               | otherwise = getRounded (money * (1 + 9.0/1200)^(12 * year))

compoundInterests :: [(Double, Int)] -> [Double]
compoundInterests investments = [compoundInterest x | x <- investments]
