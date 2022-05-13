/**********************************************************************
 * NAME: Stella Beemer
 * CLASS: CPSC 321
 * DATE: 11/9/2021
 * HOMEWORK: HW 7
 * DESCRIPTION: Queries I will need to use in my project
 **********************************************************************/


-- TODO: add queries with comments below

-- A return password hash and salt based on given username (in this case user1)
SELECT salt, password
FROM PasswordFile
WHERE username = 'user1';

-- B returns the count of fast fashion websites user3 has favorited
SELECT COUNT(category_name)
FROM UserInfo
JOIN FavoritedWebsites
USING (username)
JOIN Categories
USING (website_name)
WHERE username = 'user1' AND category_name = 'Fast Fashion';

-- C returns the websites with ratings above 5 stars
SELECT DISTINCT website_name
FROM UserReviews
WHERE review_score > 5;

-- D returns all users who are 18 years or older, ordered by age
SELECT username, age
FROM UserInfo
WHERE age > 17
ORDER BY age;

-- E returns all websites that have at least two different categories
SELECT DISTINCT website_name
FROM Categories C1
JOIN Categories C2
USING (website_name)
WHERE C1.category_name != C2.category_name;