/**********************************************************************
 * NAME: Stella Beemer
 * CLASS: CPSC 321
 * DATE: 11/6/2021
 * HOMEWORK: HW 7 Part A
 * DESCRIPTION: This file does queries against the worldfactbook database
 **********************************************************************/


-- TODO: add queries with comments below

-- query A, average gdp and inflation
SELECT AVG(gdp), AVG(inflation)
FROM Country;

-- query B, total & average area of provinces in Mexico
SELECT SUM(area), AVG(area)
FROM Country
JOIN Province
USING (country_code)
WHERE country_code = 'MX';

-- C, average population of cities in countries with high gdp and low inflation
SELECT DISTINCT AVG(population) 
FROM Country
JOIN Province
USING (country_code)
JOIN City
USING (province_name)
WHERE gdp > 800000 AND inflation < 3.0;

-- D average pop of cities within large area provinces and low inflation countries
SELECT DISTINCT AVG(population) 
FROM Country
JOIN Province
USING (country_code)
JOIN City
USING (province_name)
WHERE area > 70000 AND inflation < 3.0;

-- E averege pop of cities in the same province as Seattle
SELECT DISTINCT AVG(population) 
FROM Country
JOIN Province
USING (country_code)
JOIN City
USING (province_name)
WHERE province_name = 'Washington' AND city_name != 'Seattle';

-- F number of countries that border the US and average border length
SELECT COUNT(border_length), AVG(border_length)
FROM Border
WHERE country_code_1 = 'US';

-- G SymmetricBorder view
DROP VIEW IF EXISTS SymmetricBorder;

CREATE VIEW SymmetricBorder
AS
SELECT country_code_1, country_code_2, border_length
FROM Border;

-- H number of countries with high inflation
SELECT COUNT(country_code_1)
FROM SymmetricBorder C
JOIN Country CO1
ON C.country_code_1 = CO1.country_code
JOIN Country CO2
ON C.country_code_2 = CO2.country_code
WHERE CO1.country_code != CO2.country_code AND CO1.inflation > CO2.inflation AND CO1.gdp < CO2.gdp;

-- I 10% smaller inflation and 20% larger gdp
SELECT country_code_1, country_code_1
FROM SymmetricBorder C
JOIN Country CO1
ON C.country_code_1 = CO1.country_code
JOIN Country CO2
ON C.country_code_2 = CO2.country_code
WHERE (0.9(C1.inflation) < C2.inflation) AND (1.2(C1.gdp) > C2.gdp)
ORDER BY country_code_1, C2.inflation, C2.inflation DESC, country_code_2;

-- J aplhabetically ordered
SELECT city_name, population, province_name, country_name
FROM City
JOIN Province
USING (province_name)
ORDER BY country_name, province_name, population, city_name;