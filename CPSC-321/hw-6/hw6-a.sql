/**********************************************************************
 * NAME: Stella Beemer
 * CLASS: CPSC 321
 * DATE: 10/25
 * HOMEWORK: HW 6 (SQL 2)
 * DESCRIPTION: This file runs queries against the world factbook database
                from last assignment.
 **********************************************************************/


-- TODO: add drop table statements
DROP TABLE IF EXISTS City;
DROP TABLE IF EXISTS Border;
DROP TABLE IF EXISTS Province;
DROP TABLE IF EXISTS Country;

-- TODO: add create table statements

-- Country stores identifying info about countries
CREATE TABLE Country (
    country_code CHAR(2),
    country_name TINYTEXT,
    gdp INT,
    inflation FLOAT,
    PRIMARY KEY(country_code)
);

-- A province is a territory within a country
CREATE TABLE Province (
    province_name VARCHAR(255),
    country_code CHAR(2),
    area INT,
    PRIMARY KEY(province_name, country_code),
    FOREIGN KEY(country_code) REFERENCES Country(country_code)
);

-- Stores info about cities within certain provinces, countries
CREATE TABLE City (
    city_name VARCHAR(255),
    province_name VARCHAR(255),
    country_code CHAR(2),
    population INT,
    PRIMARY KEY(city_name, province_name, country_code),
    FOREIGN KEY(province_name) REFERENCES Province(province_name),
    FOREIGN KEY(country_code) REFERENCES Country(country_code)
);

-- Stores info about borders between countries
CREATE TABLE Border (
    country_code_1 CHAR(2),
    country_code_2 CHAR(2),
    border_length INT,
    PRIMARY KEY(country_code_1, country_code_2),
    FOREIGN KEY(country_code_1) REFERENCES Country(country_code),
    FOREIGN KEY(country_code_2) REFERENCES Country(country_code)
);


-- TODO: add insert statements
INSERT INTO Country (country_code, country_name, gdp, inflation) 
    values ('US', 'United States of America', 1000000, 2.5),
    ('CA', 'Canada', 750000, 3.0),
    ('MX', 'Mexico', 750000, 3.2);

INSERT INTO Province (province_name, country_code, area)
    values ('Washington', 'US', 50000),
    ('Oregon', 'US', 50000),
    ('California', 'US', 100000),
    ('British Columbia', 'CA', 100000),
    ('Alberta', 'CA', 75000),
    ('Quebec', 'CA', 80000),
    ('Baja California', 'MX', 71450),
    ('Mexico City', 'MX', 1494),
    ('Veracruz', 'MX', 71823);

INSERT INTO City (city_name, province_name, country_code, population)
    values ('Seattle', 'Washington', 'US', 750000),
    ('Spokane', 'Washington', 'US', 300000),
    ('Walla Walla', 'Washington', 'US', 50000),
    ('Portland', 'Oregon', 'US', 500000),
    ('Eugene', 'Oregon', 'US', 100000),
    ('Bend', 'Oregon', 'US', 50000),
    ('Los Angeles', 'California', 'US', 15000000),
    ('San Francisco', 'California', 'US', 2000000),
    ('Sacremento', 'California', 'US', 1000000),
    ('Vancouver', 'British Columbia', 'CA', 630000),
    ('Victoria', 'British Columbia', 'CA', 80000),
    ('Kelowna', 'British Columbia', 'CA', 140000),
    ('Calgary', 'Alberta', 'CA', 1200000),
    ('Edmonton', 'Alberta', 'CA', 970000),
    ('Red Deer', 'Alberta', 'CA', 83000),
    ('Montreal', 'Quebec', 'CA', 2000000),
    ('Quebec City', 'Quebec', 'CA', 520000),
    ('Gatineau', 'Quebec', 'CA', 280000),
    ('Mexicali', 'Baja California', 'MX', 1000000),
    ('Tijuana', 'Baja California', 'MX', 1600000),
    ('Ensenada', 'Baja California', 'MX', 690000),
    ('Narvarte Poniente', 'Mexico City', 'MX', 300000),
    ('Xochimilco', 'Mexico City', 'MX', 150000),
    ('Mixcoac', 'Mexico City', 'MX', 150000),
    ('Veracruz', 'Veracruz', 'MX', 550000),
    ('Coatzacoalcos', 'Veracruz', 'MX', 305260),
    ('Cordoba', 'Veracruz', 'MX', 218000);

INSERT INTO Border (country_code_1, country_code_2, border_length)
    values ('US', 'CA', 8891),
    ('US', 'MX', 3145);


-- TODO: add select statements (to print tables)
SELECT * FROM Country;
SELECT * FROM Province;
SELECT * FROM City;
SELECT * FROM Border;


-- TODO: add queries

-- (a), all countries with high gdp and low inflation
SELECT * 
FROM Country
WHERE gdp > 800000 AND inflation < 3.0;

-- (b), provinces with low area in high inflation countries (comma join) 
SELECT C.country_code, C.country_name, C.inflation, P.province_name, P.area 
FROM Country C, Province P
WHERE C.country_code = P.country_code AND inflation > 2.9 AND area < 20000;

-- (c), provinces with low area in high inflation countries (join keyword)
SELECT C.country_code, C.country_name, C.inflation, P.province_name, P.area 
FROM Country C
JOIN Province P
USING (country_code)
WHERE inflation > 2.9 AND area < 20000;

-- (d), provinces with at least one city with a population over 1000 (comma join)
SELECT DISTINCT C.country_code, C.country_name, P.province_name, P.area
FROM Country C, Province P, City C1
WHERE (C.country_code = P.country_code AND P.province_name = C1.province_name) AND C1.population > 1000;

-- (e), provinces with at least one city with a population over 1000 (join keyword)
SELECT DISTINCT C.country_code, C.country_name, P.province_name, P.area
FROM Country C
JOIN Province P
USING (country_code)
JOIN City C1 
USING (province_name)
WHERE C1.population > 1000;

-- (f) provinces with at least two cities with a population over 1000 (comma join)
SELECT DISTINCT C.country_code, C.country_name, P.province_name, P.area
FROM Country C, Province P, City C1, City C2
WHERE (C.country_code = P.country_code AND P.province_name = C1.province_name AND P.province_name = C2.province_name) AND C1.population > 1000
    AND C2.population > 1000 AND C1.city_name != C2.city_name;

-- (g) provinces with at least two cities with a population over 1000 (join keyword)
SELECT DISTINCT C.country_code, C.country_name, P.province_name, P.area
FROM Country C
JOIN Province P
USING (country_code)
JOIN City C1 
USING (province_name)
JOIN City C2
USING (province_name)
WHERE C1.population > 1000 AND C2.population > 1000 and C1.city_name != C2.city_name;

-- (h) finds pairs of different cities with the same populations (comma join)
SELECT C1.city_name, C1.province_name, C1.country_code, C2.city_name, C2.province_name, C2.country_code, C1.population
FROM City C1, City C2
WHERE C1.province_name = C2.province_name AND C1.population = C2.population 
    AND (C1.city_name != C2.city_name OR C1.province_name != C2.province_name OR C1.country_code != C2.country_code);

-- (i) finds all countries with a high GDP and low inflation that border a country 
--      with a low GDP and high inflation (comma join)
SELECT DISTINCT C1.country_code, C1.country_name
FROM Country C1, Border, Country C2
WHERE (C1.country_code = country_code_1 AND C2.country_code = country_code_2)
    AND (C1.gdp > 800000 AND C1.inflation < 3.0)
    AND (C2.gdp < 800000 AND C2.inflation > 2.9);

-- (j) finds pairs of different cities with the same populations (join keyword)
SELECT C1.city_name, C1.province_name, C1.country_code, C2.city_name, C2.province_name, C2.country_code, C1.population
FROM City C1 
JOIN City C2 
USING (province_name)
WHERE C1.population = C2.population AND (C1.city_name != C2.city_name OR C1.province_name != C2.province_name OR C1.country_code != C2.country_code);

-- (j) finds all countries with a high GDP and low inflation that border a country 
--      with a low GDP and high inflation (join keyword)
SELECT DISTINCT C1.country_code, C1.country_name
FROM Country C1 
JOIN Border 
ON C1.country_code = Border.country_code_1 
JOIN Country C2 
ON C2.country_code = Border.country_code_2
WHERE ((C1.country_code = country_code_1 AND C2.country_code = country_code_2) OR (C1.country_code = country_code_2 AND C2.country_code = country_code_2))
    AND (C1.gdp > 800000 AND C1.inflation < 3.0)
    AND (C2.gdp < 800000 AND C2.inflation > 2.9);