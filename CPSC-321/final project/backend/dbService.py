# * NAME: Stella Beemer
# * CLASS: CPSC 321
# * DATE: 12/13/2021
# * HOMEWORK: Final Project
# * DESCRIPTION: This file is a service that executes all queries needed for my database

import mysql.connector
from backend import config
import hashlib
import random


# initializes database for use in app
def initializeDb():
    try:
        user = config.mysql['user']
        password = config.mysql['password']
        host = config.mysql['host']
        dab = 'sbeemer2_DB'
        con = mysql.connector.connect(user=user, password=password, host=host, database=dab)
        rs = con.cursor()
        return con, rs
    except mysql.connector.Error as err:
        print(err)


# authenticates user against passwordfile table
def validateUser(username, password, rs):
    query = '''SELECT salt, password FROM PasswordFile WHERE username = %s'''
    try:
        rs.execute(query, (username,))
    except:
        return False
    else:
        row = rs.fetchone()
        salt = str(row[0])
        saltPassword = password + salt
        hashPassword = hashlib.sha256(saltPassword.encode('utf-8')).hexdigest()
        if (hashPassword == row[1]):
            config.authUser['user'] = username
            return True
        else:
            return False


# adds an entry to the passwordfile table
def createAccount(username, password, con, rs):
    # check username isnt already in DB, return to page if it is
    exist_query = '''SELECT username FROM PasswordFile WHERE username = %s'''
    rs.execute(exist_query, (username,))
    row = rs.fetchone()
    if (row != None):
        return "This username has already been taken."

    # hash the password for inserting
    random.seed(11231)
    salt = random.randint(1, 999)
    saltPassword = password + str(salt)
    hashPassword = hashlib.sha256(saltPassword.encode('utf-8')).hexdigest()

    # insert into the password file
    insert_query = '''INSERT INTO PasswordFile values (%s, %s, %s)'''
    try:
        rs.execute(insert_query, (username, salt, hashPassword))
    except:
        return "An error has occurred."
    else:
        con.commit()
        return "Account successfully created!"


# checks if a certain website is in the websiteinfo table
def getWebsite(website, rs):
    query = '''SELECT website_name FROM WebsiteInfo WHERE website_name = %s'''
    rs.execute(query, (website,))
    row = rs.fetchone()
    if (row != None):
        return True
    else:
        return False


# returns list of all websites in websiteinfo table
def getWebsitesInDB(rs):
    query = '''SELECT website_name FROM WebsiteInfo'''
    rs.execute(query)
    result = []
    for name in rs:
        result.append(str(name[0]))
    return result


# submits a website to the suggestionbox table
def addSuggestion(website, con, rs):
    query = '''INSERT INTO SuggestionBox values (%s)'''
    try:
        rs.execute(query, (website,))
    except:
        return "An error has occurred."
    else:
        con.commit()
        return "Website successfully submitted!"


# gets the co2, waste, and fair trade scores from websiteinfo
def getWebsiteScores(website, rs):
    query = '''SELECT co2, waste, fair_trade FROM WebsiteInfo WHERE website_name = %s'''
    rs.execute(query, (website,))
    row = rs.fetchone()
    co2 = int(row[0])
    waste = int(row[1])
    fairTrade = int(row[2])
    avgScore = (co2 + waste + fairTrade) // 3
    return co2, waste, fairTrade, avgScore


# returns user info when accessing userInfo.py, also adds user
# to UserInfo if they are a new account accessing the page for the first time
def getUserInfo(con, rs):
    username = config.authUser["user"]
    query = '''SELECT age, gender FROM UserInfo WHERE username = %s'''
    rs.execute(query, (username,))
    row = rs.fetchone()
    if (row != None):
        return str(row[0]), str(row[1])
    rs.nextset()
    insert_query = '''INSERT INTO UserInfo values (%s, NULL, NULL)'''
    rs.execute(insert_query, (username,))
    con.commit()
    return "", ""


# returns username of logged in user
def getAuthUser():
    return config.authUser["user"]


# updates user info in UserInfo table
def updateUserInfo(updateAge, updateGender, con, rs):
    query = '''UPDATE UserInfo SET age = %s, gender = %s WHERE username = %s'''
    username = getAuthUser()
    try:
        rs.execute(query, (updateAge, updateGender, username))
    except:
        return "An error has occurred, please try again."
    else:
        con.commit()
        return "Update successful! Please refresh the page to \nsee the change."


# finds the top rated sites by groove and orders them by average score
def findTopSites(rs):
    query = '''SELECT website_name, ((co2 + waste + fair_trade) / 3) AS Average
                FROM WebsiteInfo ORDER BY Average DESC LIMIT 5'''
    rs.execute(query)
    resultStr = ""
    for (wname, waverage) in rs:
        resultStr += str(wname) + ": " + str(int(waverage)) + "\n"
    return resultStr


# returns the list of categories websites in the groove database fall into
def getCategories(rs):
    query = '''SELECT DISTINCT category_name FROM Categories'''
    rs.execute(query)
    result = []
    for (category) in rs:
        result.append(str(category[0]))
    return result


# returns top rated sites filtered by an entered category name
def getFilteredTop(category, rs):
    query = '''SELECT website_name, ((co2 + waste + fair_trade) / 3) AS Average
                    FROM WebsiteInfo JOIN Categories USING (website_name)
                    WHERE category_name = %s
                    ORDER BY Average DESC LIMIT 5'''
    rs.execute(query, (category,))
    resultStr = ""
    for (wname, waverage) in rs:
        resultStr += str(wname) + ": " + str(int(waverage)) + "\n"
    return resultStr


# filters favorited sites of all users by category, age, and gender
def filterByAll(category, age, gender, rs):
    ageLower = age[0:2]
    ageUpper = age[-2:]
    query = '''SELECT website_name, COUNT(UserInfo.username) AS favorite
                FROM FavoritedWebsites JOIN Categories USING (website_name)
                JOIN UserInfo USING (username)
                WHERE category_name = %s AND age >= %s AND age <= %s AND gender = %s
                GROUP BY website_name
                ORDER BY favorite DESC LIMIT 5'''
    rs.execute(query, (category, ageLower, ageUpper, gender,))
    resultStr = ""
    for (wname, waverage) in rs:
        resultStr += str(wname) + ": " + str(int(waverage)) + " Favorites\n"
    return resultStr


# filters all favorited websites by category and age
def filterByCA(category, age, rs):
    ageLower = age[0:2]
    ageUpper = age[-2:]
    query = '''SELECT website_name, COUNT(UserInfo.username) AS favorite
                    FROM FavoritedWebsites JOIN Categories USING (website_name)
                    JOIN UserInfo USING (username)
                    WHERE category_name = %s AND age >= %s AND age <= %s
                    GROUP BY website_name
                    ORDER BY favorite DESC LIMIT 5'''
    rs.execute(query, (category, ageLower, ageUpper,))
    resultStr = ""
    for (wname, waverage) in rs:
        resultStr += str(wname) + ": " + str(int(waverage)) + "\n"
    return resultStr


# filters all favorited websites by category and gender
def filterByCG(category, gender, rs):
    query = '''SELECT website_name, COUNT(UserInfo.username) AS favorite
                    FROM FavoritedWebsites JOIN Categories USING (website_name)
                    JOIN UserInfo USING (username)
                    WHERE category_name = %s AND gender = %s
                    GROUP BY website_name
                    ORDER BY favorite DESC LIMIT 5'''
    rs.execute(query, (category, gender,))
    resultStr = ""
    for (wname, waverage) in rs:
        resultStr += str(wname) + ": " + str(int(waverage)) + "\n"
    return resultStr


# filters all favorited websites by age and gender
def filterByAG(age, gender, rs):
    ageLower = age[0:2]
    ageUpper = age[-2:]
    query = '''SELECT website_name, COUNT(FavoritedWebsites.username) AS favorite
                    FROM FavoritedWebsites JOIN UserInfo USING (username)
                    WHERE age >= %s AND age <= %s AND gender = %s
                    GROUP BY website_name
                    ORDER BY favorite DESC LIMIT 5'''
    rs.execute(query, (ageLower, ageUpper, gender,))
    resultStr = ""
    for (wname, waverage) in rs:
        resultStr += str(wname) + ": " + str(int(waverage)) + "\n"
    return resultStr


# filters all favorited websites by category
def filterByCategory(category, rs):
    query = '''SELECT website_name, COUNT(FavoritedWebsites.username) AS favorite
                    FROM FavoritedWebsites JOIN Categories USING (website_name)
                    WHERE category_name = %s
                    GROUP BY website_name
                    ORDER BY favorite DESC LIMIT 5'''
    rs.execute(query, (category,))
    resultStr = ""
    for (wname, waverage) in rs:
        resultStr += str(wname) + ": " + str(int(waverage)) + "\n"
    return resultStr


# filters all favorited websites by age
def filterByAge(age, rs):
    ageLower = age[0:2]
    ageUpper = age[-2:]
    query = '''SELECT website_name, COUNT(UserInfo.username) AS favorite
                    FROM FavoritedWebsites JOIN UserInfo USING (username)
                    WHERE age >= %s AND age <= %s
                    GROUP BY website_name
                    ORDER BY favorite DESC LIMIT 5'''
    rs.execute(query, (ageLower, ageUpper,))
    resultStr = ""
    for (wname, waverage) in rs:
        resultStr += str(wname) + ": " + str(int(waverage)) + "\n"
    return resultStr


# filters all favorited websites by gender
def filterByGender(gender, rs):
    query = '''SELECT website_name, COUNT(UserInfo.username) AS favorite
                    FROM FavoritedWebsites JOIN UserInfo USING (username)
                    WHERE gender = %s
                    GROUP BY website_name
                    ORDER BY favorite DESC LIMIT 5'''
    rs.execute(query, (gender,))
    resultStr = ""
    for (wname, waverage) in rs:
        resultStr += str(wname) + ": " + str(int(waverage)) + "\n"
    return resultStr


# returns websites ordered by most amount of user favorites to least
def mostFavorites(rs):
    query = '''SELECT website_name, COUNT(username)
                FROM FavoritedWebsites GROUP BY website_name'''
    rs.execute(query)
    resultStr = ""
    for (wname, wcount) in rs:
        resultStr += str(wname) + ": " + str(wcount) + "\n"
    return resultStr


# determines which of the above 8 queries will be used
def determineQuery(category, age, gender, rs):
    needCategory = True if (category != "All Categories") else False
    needAge = True if (age != "all ages") else False
    needGender = True if (gender != "all genders") else False

    if (needCategory and needAge and needGender):
        return filterByAll(category, age, gender, rs)
    elif (needCategory and needAge):
        return filterByCA(category, age, rs)
    elif (needCategory and needGender):
        return filterByCG(category, gender, rs)
    elif (needAge and needGender):
        return filterByAG(age, gender, rs)
    elif (needCategory):
        return filterByCategory(category, rs)
    elif (needAge):
        return filterByAge(age, rs)
    elif (needGender):
        return filterByGender(gender, rs)
    else:
        return mostFavorites(rs)


# gets rationale for website rating
def getRationale(website, rs):
    query = '''SELECT co2_reasoning, waste_reasoning, fair_trade_reasoning
                FROM WebsiteInfo WHERE website_name = %s'''
    rs.execute(query, (website,))
    row = rs.fetchone()
    result = []
    for i in range(3):
        result.append(str(row[i]))
    return result


# this function adds the selected website to the user's favorite list
def addToFavorites(website, con, rs):
    exist_query = '''SELECT * FROM FavoritedWebsites WHERE username = %s AND website_name = %s'''
    username = getAuthUser()
    rs.execute(exist_query, (username, website))
    row = rs.fetchone()
    if (row != None):
        return "This website is already in your favorites!"

    insert_query = '''INSERT INTO FavoritedWebsites values (%s, %s)'''
    try:
        rs.execute(insert_query, (username, website))
    except:
        return "An error has occurred."
    else:
        con.commit()
        return "Successfully added to favorites!"
