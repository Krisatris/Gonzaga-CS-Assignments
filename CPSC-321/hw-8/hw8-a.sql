/**********************************************************************
 * NAME: Stella Beemer
 * CLASS: CPSC 321
 * DATE: 11/21
 * HOMEWORK: Assignment 8
 * DESCRIPTION: This file runs queries against the world factbook databases
 **********************************************************************/


-- TODO: add queries with comments below

-- a: total area of each country
SELECT country_name, SUM(area)
FROM Country JOIN Province USING (country_code)
GROUP BY country_name;

-- b: find GDP, inflation, total pop of each country
SELECT country_name, gdp, inflation, SUM(population)
FROM Country JOIN Province USING (country_code)
JOIN City USING (province_name)
GROUP BY country_name;

-- c: name, area, pop of provinces over 1,000,000 people
SELECT province_name, area, SUM(population)
FROM Province JOIN City USING (province_name)
GROUP BY province_name
HAVING SUM(population) > 1000000;

-- d: order countries by number of cities
SELECT Country.country_code, country_name, COUNT(city_name)
FROM Country JOIN Province USING (country_code)
JOIN City USING (province_name)
GROUP BY country_name
ORDER BY COUNT(city_name) DESC;

-- e: order countries by num of cities with area smaller than 250,000 and gdp > 700000
SELECT Country.country_code, gdp, SUM(area), COUNT(city_name)
FROM Country JOIN Province USING (country_code)
JOIN City USING (province_name)
GROUP BY country_name
HAVING gdp > 700000 AND SUM(area) > 250000
ORDER BY COUNT(city_name);

-- f: find countries with the most cities
SELECT Country.country_code, COUNT(city_name)
FROM Country JOIN Province USING (country_code)
JOIN City USING (province_name)
GROUP BY Country.country_code
HAVING COUNT(*) >= ALL (SELECT COUNT(*)
                        FROM Country JOIN Province USING (country_code)
                        JOIN City USING (province_name)
                        GROUP BY Country.country_code);