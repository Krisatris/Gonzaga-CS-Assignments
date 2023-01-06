/**********************************************************************
 * NAME: Stella Beemer
 * CLASS: CPSC 321
 * DATE: 10/25
 * HOMEWORK: Final Project
 * DESCRIPTION: This file creates and populates the tables needed to
                run Groove. If you need to reset the database while running
                my app, please use this file.
 **********************************************************************/


-- TODO: add drop table statements
DROP TABLE IF EXISTS SuggestionBox;
DROP TABLE IF EXISTS FavoritedWebsites;
DROP TABLE IF EXISTS Categories;
DROP TABLE IF EXISTS PasswordFile;
DROP TABLE IF EXISTS UserInfo;
DROP TABLE IF EXISTS WebsiteInfo;

-- TODO: add create table statements

-- stores the user log in info (this is going to be the first table
-- I drop if I need to simplify things).
CREATE TABLE PasswordFile (
    username VARCHAR(255) NOT NULL,
    salt SMALLINT NOT NULL,
    password TEXT NOT NULL,
    PRIMARY KEY(username)
);

-- Stores the explicit rankings for each website not determined by users
CREATE TABLE WebsiteInfo (
    website_name VARCHAR(255) NOT NULL,
    site_description TEXT,
    co2 TINYINT NOT NULL,
    co2_reasoning TEXT,
    waste TINYINT NOT NULL,
    waste_reasoning TEXT,
    fair_trade TINYINT NOT NULL,
    fair_trade_reasoning TEXT,
    PRIMARY KEY(website_name)
);

-- stores demographic info about the user (will add more fields as I
-- think of good ones)
CREATE TABLE UserInfo (
    username VARCHAR(255) NOT NULL,
    age TINYINT UNSIGNED,
    gender ENUM('male', 'female', 'non-binary', 'genderfluid'),
    PRIMARY KEY(username)
);

-- stores categories for the websites (similar to categories in lego table)
CREATE TABLE Categories (
    website_name VARCHAR(255) NOT NULL,
    category_name VARCHAR(255) NOT NULL,
    PRIMARY KEY(website_name, category_name),
    FOREIGN KEY(website_name) REFERENCES WebsiteInfo(website_name)
);

-- Create basic table to store suggest websites Groove covers
CREATE TABLE SuggestionBox (
    website_name VARCHAR(255) NOT NULL
);

-- stores websites the user decides to favorite
CREATE TABLE FavoritedWebsites (
    username VARCHAR(255) NOT NULL,
    website_name VARCHAR(255) NOT NULL,
    PRIMARY KEY(website_name, username),
    FOREIGN KEY(website_name) REFERENCES WebsiteInfo(website_name),
    FOREIGN KEY(username) REFERENCES UserInfo(username)
);

-- TODO: add insert statements
INSERT INTO PasswordFile 
    values ('user1', 53, 'a60f6d009343ab015ee59fa2ff29e5aa12dd69aa7a7285f15e1fdec6ce7407d7'),
    ('user2', 429, 'd5fb8fad4184ab1d64e11c23241c2c95e3296235a22ad6e2d7afb28bc827a087'),
    ('user3', 130, 'fdaf316691c0233b44908b805a61d61682233bcd8c3430cbc3a16d200ab908cd');

INSERT INTO WebsiteInfo 
    values('Boohoo', 'United Kingdom-based online fashion retailer, aimed at 16–30 year olds', 1, 'no evidence it has taken meaningful action to reduce or eliminate hazardous chemicals. The brand does measure and report in greenhouse gas emission', 1, 'does not use eco-friendly materials, uses hazardous chemicals', 1, 'Not FTC. Extreme Human Rights violations'),
    ('Fashion Nova', 'American fast fashion retail company', 2, 'no evidence it has taken meaningful action to reduce or eliminate hazardous chemicals. The brand does measure and report in greenhouse gas emission', 1, 'Fast fashion. Low-quality materials. Products have a short life span.', 1, 'Not FTC. Extreme Human Rights violations, unfair wages, etc. Povery cycle.'),
    ('I.AM.GIA.', 'fAustralian fashion clothing brand', 1, 'no evidence it reduces its carbon and other greenhouse gas emissions', 2, 'Fast fashion. Low-quality materials. Products have a short relatively life span.', 2, 'Not FTC. Unfair wages, infringement, etc.'),
    ('ASOS', 'British online fashion and cosmetic retailer.', 2, 'public commitment and has set an intensity target to reduce its greenhouse gas emissions from its own operations and supply chain by 2020, but there is no evidence it has set an absolute target', 4, 'uses some eco-friendly materials in its clothing, but there is no evidence it minimises textile waste when manufacturing its products', 2, 'Not FTC. 41-50% in the Fashion Transparency Index. Failure to disclose working conditions.'),
    ('Patagonia', 'American clothing company that markets and sells outdoor clothing.', 7, 'Working to reduce emmissions, become carbon neutral. There’s some transparency missing though.', 8, 'All cotton Patagonia uses is organic and 72% of its line is made from recycled materials and all cotton is organic. But the company still uses a percentage of virgin polyester and nylon, which are materials derived from oil.', 10, 'FTC. B Corp.'),
    ('ThredUp', 'Online consignment and thrift store', 9, 'Online thrift is low emissions, but some from shipping.', 9, 'Online Thrift. Wasteful packaging could be improved.', 8, 'NOT FTC, but fair working conditions. Little publications/data.'),
    ('FlyLow', 'Ski Gear company', 8, 'best efforts to keep product at low emitting levels', 9, 'repurposing scrap fabric from our pants to make rad tote bags, and using insulating fabric made from post-consumer recycled materials in our jackets. Quality. ', 9, 'NOT FTC, but great working conditions, contributing to local communities. High wages. Good Lab. donate gear for non-profits, volunteer on traiI-building days, donate to wildland preservation'),
    ('Adidas', 'Athletic clothing company', 4, 'Working to reduce 30% of emissions by 2030, plan not specific.', 6, 'Working with Parley Ocean Plastic to use recycled plastics. Sustainable cotton.', 8, 'Not FTC. Fair pay, longevity with employees, unionization allowed'),
    ('American Eagle', 'American clothing company specializing in clothes for juniors', 6, 'Working to reduce emmissions, become carbon neutral. ', 4, 'Fast fashion. Low-quality materials. Products have a short life span. Greenwashing. No evidence to prove waste reduction goals. ', 2, 'Not FTC. Number of scandals regarding working conditions '),
    ('LuluLemon', 'Athelesiure clothing company', 2, 'No absolute targets, but 100% renewable energy commitment will result in absolute Scope 1 & 2 emissions reductions of > 60% by 2025. ', 8, '', 6, ''),
    ('Urban Outfitters', 'Clothing company specialized in trendy fashion for juniors', 4, '', 3, 'High synthetic fabric use ', 3, 'Not FTC. Unfair wages '),
    ('Kuyichi', 'Brand specializing in sustainable wardrobe basics', 9, 'focused on carbon neutrality. ', 10, 'Uses a high proportion of eco-friendly materials including Global Organic Textile Standard (GOTS) cotton.', 10, 'It is a member of the Fair Wear Foundation. It has a Code of Conduct that covers all of the ILO Four Fundamental Freedoms principles. It monitors health and safety issues by visiting all of its final stage of production suppliers. It ensures payment of a living wage in most of its supply chain and has a project to further improve wages. It traces all of its supply chain.');

INSERT INTO UserInfo
    values ('user1', 18, 'female'),
    ('user2', 25, 'male'),
    ('user3', 21, 'non-binary'),
    ('user4', 35, 'female'),
    ('user5', 24, 'genderfluid'),
    ('user6', 19, 'non-binary'),
    ('user7', 20, 'male'),
    ('user8', 22, 'male'),
    ('user9', 49, 'male'),
    ('user10', 72, 'female'),
    ('user11', 23, 'female'),
    ('user12', 25, 'non-binary'),
    ('user13', 29, 'genderfluid'),
    ('user14', 32, 'female'),
    ('user15', 18, 'female');

INSERT INTO Categories
    values ('Boohoo', 'Fast Fashion'),
    ('Boohoo', 'Juniors'),
    ('Fashion Nova', 'Fast Fashion'),
    ('Fashion Nova', 'Juniors'),
    ('I.AM.GIA.', 'Fast Fashion'),
    ('I.AM.GIA.', 'Juniors'),
    ('ASOS', 'Fast Fashion'),
    ('ASOS', 'Juniors'),
    ('Patagonia', 'Outdoor Clothing'),
    ('Patagonia', 'Menswear'),
    ('ThredUp', 'Thrift Store'),
    ('FlyLow', 'Outdoor Clothing'),
    ('Adidas', 'Athletic'),
    ('Adidas', 'Juniors'),
    ('American Eagle', 'Juniors'),
    ('American Eagle', 'Menswear'),
    ('American Eagle', 'Fast Fashion'),
    ('LuluLemon', 'Athletic'),
    ('Urban Outfitters', 'Juniors'),
    ('Urban Outfitters', 'Fast Fashion'),
    ('Kuyichi', 'Juniors');

INSERT INTO FavoritedWebsites
    values ('user1', 'ThredUp'),
    ('user1', 'I.AM.GIA.'),
    ('user2', 'Patagonia'),
    ('user2', 'ThredUp'),
    ('user3', 'ASOS'),
    ('user4', 'Adidas'),
    ('user4', 'LuluLemon'),
    ('user5', 'Kuyichi'),
    ('user6', 'American Eagle'),
    ('user6', 'ASOS'),
    ('user7', 'Urban Outfitters'),
    ('user7', 'American Eagle'),
    ('user8', 'Adidas'),
    ('user9', 'ThredUp'),
    ('user10', 'FlyLow'),
    ('user10', 'LuluLemon'),
    ('user11', 'FlyLow'),
    ('user12', 'Kuyichi'),
    ('user12', 'ThredUp'),
    ('user13', 'Fashion Nova'),
    ('user14', 'Adidas'),
    ('user14', 'LuluLemon'),
    ('user15', 'Boohoo'),
    ('user15', 'I.AM.GIA.');

-- TODO: add select statements (to print tables)
SELECT * FROM PasswordFile;
SELECT * FROM WebsiteInfo;
SELECT * FROM UserInfo;
SELECT * FROM Categories;
SELECT * FROM FavoritedWebsites;
SELECT * FROM SuggestionBox;