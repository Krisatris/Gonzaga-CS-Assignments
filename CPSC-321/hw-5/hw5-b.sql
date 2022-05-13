/**********************************************************************
 * NAME: Stella Beemer
 * CLASS: CPSC 321
 * DATE: 10-18
 * HOMEWORK: HW 5 - SQL 1
 * DESCRIPTION: This program creates the tables for the 2nd part of the assignment
 **********************************************************************/


-- TODO: add drop table statements
DROP TABLE Brick;
DROP TABLE Identical_Brick;
DROP TABLE Set;
DROP TABLE Part_List;
DROP TABLE Theme;
DROP TABLE Category;
DROP TABLE Produced_Range;


-- TODO: add create table statements
CREATE TABLE Brick (
    element_id BIGINT,
    design_id INT,
    brick_name TINYTEXT,
    color TINYTEXT,
    price FLOAT(2, 2),
    PRIMARY KEY(element_id)
);

CREATE TABLE Identical_Brick (
    old_brick BIGINT,
    new_brick BIGINT,
    PRIMARY KEY(old_brick, new_brick),
    FOREIGN KEY(old_brick) REFERENCES Brick(element_id),
    FOREIGN KEY(new_brick) REFERENCES Brick(element_id)
);

CREATE TABLE Set (
    item_num BIGINT,
    set_name TINYTEXT,
    age_range TINYTEXT,
    price DOUBLE(6, 2),
    minifigure_count SMALLINT,
    vip_points INT,
    height SMALLINT,
    width SMALLINT,
    depth SMALLINT,
    PRIMARY KEY(item_num)
);

CREATE TABLE Part_List (
    set_id BIGINT,
    brick_id BIGINT,
    amount INT,
    PRIMARY KEY(set_id, brick_id),
    FOREIGN KEY(set_id) REFERENCES Set(item_num),
    FOREIGN KEY(brick_id) REFERENCES Brick(element_id)
);

CREATE TABLE Theme (
    set_id BIGINT,
    theme_name TINYTEXT,
    theme_description TEXT,
    licensed_from TINYTEXT,
    PRIMARY KEY(set_id, theme_name),
    FOREIGN KEY(set_id) REFERENCES Set(item_num)
);

CREATE TABLE Category (
    set_id BIGINT,
    category_name TINYTEXT
    PRIMARY KEY(set_id, category_name),
    FOREIGN KEY(set_id) REFERENCES Set(item_num)
);

CREATE TABLE Produced_Range (
    set_id BIGINT,
    produce_range TEXT
    PRIMARY KEY(set_id, produce_range),
    FOREIGN KEY(set_id) REFERENCES Set(item_num)
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
    (6284573, 35381, 'FLAT TILE 1X1, ROUND', 'Brick Yellow', 0.04);

INSERT INTO Identical_Brick (old_brick, new_brick)
    values (4228253, 4224253),
    (6177142, 6177283);

INSERT INTO Set (item_num, set_name, age_range, price, minifigure_count, vip_points, height, width, depth)
    values (10276, 'Colosseum', '18+', 549.99, null, 3575, 27, 52, 59),
    (10278, 'Police Station', '18+', 199.99, 5, 1300, 37, 25, 25),
    (10295, 'Porsche 911', '18+', 149.99, null, 975, 10, 16, 35),
    (71043, 'Hogwarts Castle', '16+', 399.99, null, 2600, null, null, null),
    (71741, 'NINJAGO City Gardens', '14+', 299.99, 19, 1950, 73, 33, 44);

INSERT INTO Part_List (set_id, brick_id, amount)
    values(71741, 6152321, 15),
    (71741, 4514714, 50),
    (71043, 6284573, 25)
    (10295, 6138571, 95)
    (10278, 6102990, 73),
    (10278, 6177283, 32),
    (10276, 6152321, 321),
    (10276, 4514714, 431),
    (10276, 4224253, 10);

INSERT INTO Theme (set_id, theme_name, theme_description, licensed_from)
    values(10276, 'Creator Expert', 'Are you ready for the ultimate LEGO® building challenge? Our advanced LEGO Creator Expert series includes collectable Modular Houses, Cars, World Buildings, Fairgrounds and Seasonal Sets - and guarantee hours of building enjoyment with every set.', null),
    (10278, 'Creator Expert', 'Are you ready for the ultimate LEGO® building challenge? Our advanced LEGO Creator Expert series includes collectable Modular Houses, Cars, World Buildings, Fairgrounds and Seasonal Sets - and guarantee hours of building enjoyment with every set.', null),
    (10295, 'Creator Expert', 'Are you ready for the ultimate LEGO® building challenge? Our advanced LEGO Creator Expert series includes collectable Modular Houses, Cars, World Buildings, Fairgrounds and Seasonal Sets - and guarantee hours of building enjoyment with every set.', null),
    (71043, 'Harry Potter', 'Relive your favorite Harry Potter™ moments with these magical sets.', 'J.K. Rowling'),
    (71741, 'NINJAGO', 'LEGO® NINJAGO® is an exciting world of ninjas battling against evil. Your child will love role playing their exciting and varied adventures.', null);

INSERT INTO Category (set_id, category_name)
    values(10276, 'Creator Expert'),
    (10276, 'Adults Welcome')
    (10276, 'Buildings'),
    (10278, 'Real Life Heroes')
    (10278, 'Creator Expert'),
    (10278, 'Adults Welcome'),
    (10278, 'Buildings'),
    (10295, 'Cars'),
    (10295, 'Creator Expert'),
    (10295, 'Adults Welcome'),
    (10295, 'Vehicles'),
    (71043, 'Dragons'),
    (71043, 'Adults Welcome'),
    (71043, 'Harry Potter'),
    (71043, 'Buildings'),
    (71043, 'Fantasy'),
    (71741, 'Fantasy'),
    (71741, 'Ninjas'),
    (71741, 'NINJAGO'),
    (71741, 'Buildings');

INSERT INTO Produced_Range(set_id, produce_range)
    values(10276, '2015-Present'),
    (10278, '2000-2008'),
    (10278, '2020-Present'),
    (10295, '2010-Present'),
    (71043, '2012-2015'),
    (71043, '2018-2021'),
    (71741, '2016-2021');


-- TODO: add select statements (to print tables)
SELECT * FROM Brick;
SELECT * FROM Identical_Brick;
SELECT * FROM Set;
SELECT * FROM Part_List;
SELECT * FROM Theme;
SELECT * FROM Category;
SELECT * FROM Produced_Range;