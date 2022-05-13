/**********************************************************************
 * NAME: Stella Beemer
 * CLASS: CPSC 321
 * DATE: 11/21
 * HOMEWORK: Assignment 8
 * DESCRIPTION: This file completes queries against the movies database
 **********************************************************************/


-- TODO: add queries with comments below

/*
-- a: find total number of films by category ordered from most to least
SELECT name, COUNT(film_id)
FROM film_category JOIN category USING (category_id)
GROUP BY name
ORDER BY COUNT(film_id) DESC;


-- b: first and last names of customers who rented at least 4 PG, 2.99 movies
SELECT first_name, last_name, COUNT(rental_id)
FROM rental JOIN customer USING (customer_id)
JOIN payment USING (rental_id)
JOIN inventory USING (inventory_id)
JOIN film USING (film_id)
WHERE rating = 'PG' AND amount = 2.99
GROUP BY first_name, last_name
HAVING COUNT(rental_id) > 3
ORDER BY COUNT(rental_id) DESC;

-- c: find all G rated movies 
SELECT title, amount
FROM rental JOIN payment USING (rental_id) JOIN inventory USING (inventory_id) JOIN film USING (film_id),
    (SELECT MAX(amount) AS max_amount FROM payment) AS f2
WHERE rating = 'G' AND amount = max_amount;

-- d: find the category(s) with the most num of PG films
SELECT name, COUNT(name)
FROM film JOIN film_category USING (film_id) JOIN category USING (category_id)
WHERE rating = 'PG'
GROUP BY name
HAVING COUNT(*) >= ALL (SELECT COUNT(*)
                        FROM film JOIN film_category USING (film_id) JOIN category USING (category_id)
                        WHERE rating = 'PG'
                        GROUP BY name);


-- e: find the G rated film(s) that are rented more than average
SELECT title, COUNT(rental_id)
FROM rental JOIN inventory USING (inventory_id) JOIN film USING (film_id)
WHERE rating = 'G'
GROUP BY title
HAVING COUNT(*) >= (SELECT AVG(rental_count)
                        FROM (SELECT COUNT(rental_id) as rental_count
                        FROM rental JOIN inventory USING (inventory_id) JOIN film USING (film_id)
                        WHERE rating = 'G'
                        GROUP BY title) AS F)
ORDER BY COUNT(rental_id) DESC;

-- f: actors/actresses not in a 'G' film
SELECT DISTINCT first_name, last_name
FROM actor
WHERE actor_id NOT IN (SELECT actor_id
                        FROM film JOIN film_actor USING (film_id) JOIN actor USING (actor_id)
                        WHERE rating = 'G');


-- g: find film titles that all stores carry
SELECT title
FROM film
WHERE title NOT IN (SELECT title
                    FROM film CROSS JOIN store LEFT OUTER JOIN inventory ON film.film_id = inventory.film_id AND store.store_id = inventory.store_id
                    WHERE inventory.inventory_id IS NULL);


-- h: percentage of G rated movies each actor/actress has acted in
SELECT actor_id, first_name, last_name, (COUNT(actor_id) / 
                    (SELECT COUNT(*) FROM film JOIN film_actor USING (film_id) GROUP BY actor_id)) AS F
FROM film JOIN film_actor USING (film_id) JOIN actor USING(actor_id)
WHERE rating = 'G'
GROUP BY actor_id;


-- i: outer join to find films with no actors
SELECT title
FROM film LEFT OUTER JOIN film_actor ON film.film_id = film_actor.film_id
WHERE actor_id IS NULL;


-- j: outer join to find films that are in a store's inventory but haven't been rented
SELECT title
FROM film JOIN inventory USING (film_id) LEFT OUTER JOIN rental ON inventory.inventory_id = rental.inventory_id
WHERE rental_id IS NULL;
*/

-- k: number of actors who acted in each film
SELECT film.film_id, COUNT(*)
FROM film LEFT OUTER JOIN film_actor ON film.film_id = film_actor.film_id
GROUP BY film.film_id;
