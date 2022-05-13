/**********************************************************************
 * NAME: Stella Beemer
 * CLASS: CPSC 321
 * DATE: 10/25
 * HOMEWORK: HW 6 (SQL 2)
 * DESCRIPTION: This file runs queries against the lego database from
                the last assignment.
 **********************************************************************/

-- TODO: drop table statements
DROP TABLE IF EXISTS Part_List;
DROP TABLE IF EXISTS Category;
DROP TABLE IF EXISTS Theme;
DROP TABLE IF EXISTS Produced_Range;
DROP TABLE IF EXISTS Identical_Brick;
DROP TABLE IF EXISTS Lego_Set;
DROP TABLE IF EXISTS Brick;

-- TODO: add create table statements

-- Stores info about singular Lego Bricks
CREATE TABLE Brick (
    element_id BIGINT NOT NULL,
    design_id INT NOT NULL,
    brick_name TINYTEXT NOT NULL,
    color TINYTEXT NOT NULL,
    price FLOAT(2, 2) NOT NULL,
    PRIMARY KEY(element_id)
);

-- Stores info about if Bricks are identical to others, and if they are
-- what their corresponding part is
CREATE TABLE Identical_Brick (
    old_brick BIGINT NOT NULL,
    new_brick BIGINT NOT NULL,
    PRIMARY KEY(old_brick, new_brick),
    FOREIGN KEY(old_brick) REFERENCES Brick(element_id),
    FOREIGN KEY(new_brick) REFERENCES Brick(element_id)
);

-- Stores identifying info about Lego Sets
CREATE TABLE Lego_Set (
    item_num BIGINT NOT NULL,
    set_name TINYTEXT NOT NULL,
    age_range TINYTEXT NOT NULL,
    price DOUBLE(6, 2) NOT NULL,
    minifigure_count SMALLINT,
    vip_points INT NOT NULL,
    height SMALLINT,
    width SMALLINT,
    depth SMALLINT,
    PRIMARY KEY(item_num)
);

-- Stores the Part List for each Lego Set
CREATE TABLE Part_List (
    set_id BIGINT NOT NULL,
    brick_id BIGINT NOT NULL,
    amount INT NOT NULL,
    PRIMARY KEY(set_id, brick_id),
    FOREIGN KEY(set_id) REFERENCES Lego_Set(item_num),
    FOREIGN KEY(brick_id) REFERENCES Brick(element_id)
);

-- Stores the singular theme that each Set has
CREATE TABLE Theme (
    set_id BIGINT NOT NULL,
    theme_name VARCHAR(255) NOT NULL,
    theme_description TEXT NOT NULL,
    licensed_from TINYTEXT,
    PRIMARY KEY(set_id, theme_name),
    FOREIGN KEY(set_id) REFERENCES Lego_Set(item_num)
);

-- Stores the categories each set is a part of
CREATE TABLE Category (
    set_id BIGINT NOT NULL,
    category_name VARCHAR(255) NOT NULL,
    PRIMARY KEY(set_id, category_name),
    FOREIGN KEY(set_id) REFERENCES Lego_Set(item_num)
);

-- Stores the dates when each set was produced
CREATE TABLE Produced_Range (
    set_id BIGINT NOT NULL,
    start_year SMALLINT NOT NULL,
    end_year SMALLINT,
    PRIMARY KEY(set_id, start_year),
    FOREIGN KEY(set_id) REFERENCES Lego_Set(item_num)
);


-- TODO: add insert statements
INSERT INTO Brick (element_id, design_id, brick_name, color, price)
    values (6177283, 3004, 'BRICK 1X2', 'Sand Blue', 0.11),
    (6102990, 3068, 'FLAT TILE 2X2', 'Medium Nougat', 0.08),
    (6138571, 22888, '1/2 CIRCLE PLATE 4X8', 'Medium Azur', 0.38),
    (4224253, 4258, 'PARABOLIC REFLECTOR 048', 'Dark Stone Grey', 0.51),
    (4514717, 3029, 'PLATE 4X12', 'Bright Red', 0.70),
    (6177142, 3004, 'BRICK 1X2', 'Sand Blue', 0.11),
    (6152321, 3034, 'PLATE 2X8', 'Dark Red', 0.25), 
    (4228253, 4258, 'PARABOLIC REFLECTOR 048', 'Dark Stone Grey', 0.51),
    (6284573, 35381, 'FLAT TILE 1X1, ROUND', 'Brick Yellow', 0.04),
    (300423, 3004, 'BRICK 1X2', 'Bright Blue', 0.11),
    (302021, 3020, 'PLATE 2X4', 'Bright Red', 0.14);

INSERT INTO Identical_Brick (old_brick, new_brick)
    values (4228253, 4224253),
    (6177142, 6177283);

INSERT INTO Lego_Set (item_num, set_name, age_range, price, minifigure_count, vip_points, height, width, depth)
    values (10276, 'Colosseum', '18+', 549.99, null, 3575, 27, 52, 59),
    (10278, 'Police Station', '18+', 199.99, 5, 1300, 37, 25, 25),
    (10295, 'Porsche 911', '18+', 149.99, null, 975, 10, 16, 35),
    (71043, 'Hogwarts Castle', '16+', 399.99, null, 2600, null, null, null),
    (71741, 'NINJAGO City Gardens', '14+', 299.99, 19, 1950, 73, 33, 44),
    (40378, 'Goofy & Pluto', '10+', 14.99, null, 97, null, null, null);

INSERT INTO Part_List (set_id, brick_id, amount)
    values(71741, 6152321, 15),
    (71741, 4514717, 50),
    (71043, 6284573, 25),
    (10295, 6138571, 95),
    (10278, 6102990, 73),
    (10278, 6177283, 32),
    (10276, 6152321, 321),
    (10276, 4514717, 431),
    (10276, 4224253, 10),
    (40378, 300423, 3),
    (40378, 302021, 12);

INSERT INTO Theme (set_id, theme_name, theme_description, licensed_from)
    values(10276, 'Creator Expert', 'Are you ready for the ultimate LEGO® building challenge? Our advanced LEGO Creator Expert series includes collectable Modular Houses, Cars, World Buildings, Fairgrounds and Seasonal Sets - and guarantee hours of building enjoyment with every set.', null),
    (10278, 'Creator Expert', 'Are you ready for the ultimate LEGO® building challenge? Our advanced LEGO Creator Expert series includes collectable Modular Houses, Cars, World Buildings, Fairgrounds and Seasonal Sets - and guarantee hours of building enjoyment with every set.', null),
    (10295, 'Creator Expert', 'Are you ready for the ultimate LEGO® building challenge? Our advanced LEGO Creator Expert series includes collectable Modular Houses, Cars, World Buildings, Fairgrounds and Seasonal Sets - and guarantee hours of building enjoyment with every set.', null),
    (71043, 'Harry Potter', 'Relive your favorite Harry Potter™ moments with these magical sets.', 'J.K. Rowling'),
    (71741, 'NINJAGO', 'LEGO® NINJAGO® is an exciting world of ninjas battling against evil. Your child will love role playing their exciting and varied adventures.', null),
    (40378, 'Disney™', 'LEGO® Disney allows your child to build and play stories from their favorite fairytales. Disney characters will come to life as your child recreates romance, adventure, and heroism!', 'Disney');

INSERT INTO Category (set_id, category_name)
    values(10276, 'Creator Expert'),
    (10276, 'Adults Welcome'),
    (10276, 'Buildings'),
    (10278, 'Real Life Heroes'),
    (10278, 'Creator Expert'),
    (10278, 'Adults Welcome'),
    (10278, 'Buildings'),
    (10295, 'Cars'),
    (10295, 'Creator Expert'),
    (10295, 'Adults Welcome'),
    (10295, 'Vehicles'),
    (10295, 'Sports'),
    (10295, 'Buildings'),
    (71043, 'Dragons'),
    (71043, 'Adults Welcome'),
    (71043, 'Harry Potter'),
    (71043, 'Buildings'),
    (71043, 'Fantasy'),
    (71741, 'Fantasy'),
    (71741, 'Ninjas'),
    (71741, 'NINJAGO'),
    (71741, 'Buildings'),
    (40378, 'Disney'),
    (40378, 'Buildings'),
    (40378, 'BrickHeadz');

INSERT INTO Produced_Range(set_id, start_year, end_year)
    values(10276, 2015, NULL),
    (10278, 2000, 2008),
    (10278, 2020, NULL),
    (10295, 2010, NULL),
    (71043, 2012, 2015),
    (71043, 2018, 2021),
    (71741, 2016, 2021),
    (40378, 2019, null);

-- TODO: add select statements (to print tables)
SELECT * FROM Brick;
SELECT * FROM Identical_Brick;
SELECT * FROM Lego_Set;
SELECT * FROM Part_List;
SELECT * FROM Theme;
SELECT * FROM Category;
SELECT * FROM Produced_Range;

-- TODO: add quereies

-- (a) return sets with at least 10 of some brick and costing less than $25.00
SELECT DISTINCT item_num, set_name
FROM Lego_Set
JOIN Part_List
ON Lego_Set.item_num = Part_List.set_id
WHERE amount > 10 AND price < 25.00;

-- (b) returns all sets that have either a bright blue or bright red brick
SELECT DISTINCT item_num, set_name
FROM Lego_Set
JOIN Part_List
ON Lego_Set.item_num = Part_List.set_id
JOIN Brick
ON Part_List.brick_id = Brick.element_id
WHERE (brick_name = 'BRICK 1X2' AND color = 'Bright Blue')
    OR (brick_name = 'PLATE 2X4' AND color = 'Bright Red');

-- (c) finds all sets that are in both the disney theme and buildings category
SELECT DISTINCT item_num, set_name
FROM Lego_Set
JOIN Theme
ON Lego_Set.item_num = Theme.set_id
JOIN Category
ON Lego_Set.item_num = Category.set_id
WHERE theme_name = 'Disney™' AND category_name = 'Buildings';

-- (d) finds all sets that are in both the building and sports categories
SELECT DISTINCT item_num, set_name
FROM Lego_Set
JOIN Category C1
ON Lego_Set.item_num = C1.set_id
JOIN Category C2
ON Lego_Set.item_num = C2.set_id
WHERE (C1.category_name = 'Buildings' AND C2.category_name = 'Sports');

-- (e) finds all sets produced under two different year ranges
SELECT DISTINCT item_num, set_name
FROM Lego_Set
JOIN Produced_Range PR1
ON Lego_Set.item_num = PR1.set_id
JOIN Produced_Range PR2
ON Lego_Set.item_num = PR2.set_id
WHERE (PR1.start_year != PR2.start_year);

-- (f) find all sets that have a low price, large num of minifigures,
--      and a large num of vip points
SELECT DISTINCT item_num, set_name
FROM Lego_Set
WHERE price < 250.00 AND minifigure_count > 4 AND vip_points > 1000;

-- (g) find all sets produced within a given year (2012-2014)
--      **I am assuming with this question that if a set has an edge case where it was
--          produced in two successive ranges (ie. 2010-2012 and 2012-2014) that it does
--          not fulfill this query.
SELECT DISTINCT item_num, set_name
FROM Lego_Set
JOIN Produced_Range
ON Lego_Set.item_num = Produced_Range.set_id
WHERE start_year <= 2012 AND (end_year >= 2014 OR end_year IS NULL);

-- (h) find average set price of 'Creator Expert' themed sets
SELECT DISTINCT theme_name, AVG(price)
FROM Lego_Set
JOIN Theme
ON Lego_Set.item_num = Theme.set_id
WHERE theme_name = 'Creator Expert';

-- (h) find sets that have at least two different categories
SELECT DISTINCT item_num, set_name
FROM Lego_Set
JOIN Category C1
ON Lego_Set.item_num = C1.set_id
JOIN Category C2
ON Lego_Set.item_num = C2.set_id
WHERE C1.category_name != C2.category_name;

-- (h) find sets that have at least 100 parts
SELECT DISTINCT item_num, set_name
FROM Lego_Set
JOIN Part_List PL1
ON Lego_Set.item_num = PL1.set_id
JOIN Part_List PL2
ON Lego_Set.item_num = PL2.set_id
WHERE (PL1.brick_id != PL2.brick_id) AND (PL1.amount + PL2.amount > 100);