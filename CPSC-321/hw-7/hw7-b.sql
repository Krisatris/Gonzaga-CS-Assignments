/**********************************************************************
 * NAME: Stella Beemer
 * CLASS: CPSC 321
 * DATE: 11/8/2021
 * HOMEWORK: HW7 Part B
 * DESCRIPTION: This file contains 5 "interesting" queries against the 
                movie rental database.
 **********************************************************************/


-- TODO: add queries with comments below

-- A returns the count of films in English.
SELECT COUNT(language_id)
FROM film
WHERE language_id = 1;

-- B returns the amount of times the movie with an ID of 1 has been rented
SELECT title, COUNT(rental_id)
FROM rental
JOIN inventory
USING (inventory_id)
JOIN film
USING (film_id)
WHERE film_id = 1;

-- C returns the first 10 movies in the 1st category ordered by release year
SELECT title, release_year
FROM film
JOIN film_category
USING (film_id)
JOIN category
USING (category_id)
WHERE category_id = 1
ORDER BY release_year
LIMIT 10;

-- D returns the title, release year, and actor id of all movies starring the actor with ID 1 in the year 2006, sorted alphabetically by title
SELECT title, release_year, actor_id
FROM film
JOIN film_actor
USING (film_id)
WHERE release_year = 2006 AND actor_id = 1
ORDER BY title;

-- E finds the average rental_rate of all movies in store with ID 1.
SELECT AVG(rental_rate)
FROM film
JOIN inventory
USING (film_id)
WHERE store_id = 1;