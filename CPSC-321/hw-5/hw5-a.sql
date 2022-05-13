/**********************************************************************
 * NAME: Stella Beemer
 * CLASS: CPSC 321
 * DATE: 10/18/2021
 * HOMEWORK: HW 5 - SQL 1
 * DESCRIPTION: This file builds the databases for part 1 of the assignment
 **********************************************************************/


-- TODO: add drop table statements
DROP TABLE Country;
DROP TABLE Province;
DROP TABLE City;
DROP TABLE Border;

-- TODO: add create table statements
CREATE TABLE Country (
    country_code CHAR(2),
    country_name TINYTEXT,
    gdp INT,
    inflation, FLOAT,
    PRIMARY KEY(country_code)
);

CREATE TABLE Province (
    province_name TINYTEXT,
    country_code CHAR(2),
    area INT,
    PRIMARY KEY(province_name, country_code),
    FOREIGN KEY(country_code) REFERENCES Country(country_code)
);

CREATE TABLE City (
    city_name TINYTEXT,
    province_name TINYTEXT,
    country_code CHAR(2),
    population INT,
    PRIMARY KEY(city_name, province_name, country_code),
    FOREIGN KEY(province_name) REFERENCES Province(province_name),
    FOREIGN KEY(country_code) REFERENCES Country(country_code)
);

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
    ('San Francisco', 'Califronia', 'US', 2000000),
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