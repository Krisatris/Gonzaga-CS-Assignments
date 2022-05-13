# * NAME: Stella Beemer
# * CLASS: CPSC 321
# * DATE: 12/1/2021
# * HOMEWORK: HW 9 Part A
# * DESCRIPTION: This file is a CLI against the world factbook database

import mysql.connector
import config

def main():
    rs, con = initialize_db()

    input_num = 0
    while(input_num != 5):
        # prompt for user input
        print("1. List countries")
        print("2. Add country")
        print("3. Find countries based on gdp and inflation")
        print("4. Update country's gdp and inflation")
        print("5. Exit")
        input_num = input("Enter your choice (1-5): ")
        print("")

        # go to correct function
        if input_num == 1:
            list_countries(rs, con)
        elif input_num == 2:
            add_country(rs, con)
        elif input_num == 3:
            find_gdp_inflation(rs, con)
        elif input_num == 4:
            update_gdp_inflation(rs, con)

    # end the program and close connections if user enters 5    
    print("halting program.")
    rs.close()
    con.close()
    quit()

def initialize_db():
    try: 
        # connection info
        usr = config.mysql['user']
        pwd = config.mysql['password']
        hst = config.mysql['host']
        dab = 'sbeemer2_DB'
        # create a connection
        con = mysql.connector.connect(user=usr,password=pwd, host=hst,
                                      database=dab)
        # create a result set
        rs = con.cursor()
        return rs, con
    except mysql.connector.Error as err:
        print err

def list_countries(rs, con):
    # query the database and print the results
    query = 'SELECT country_name, country_code from Country'
    # execute the query
    rs.execute(query)
    # print the results
    for (cname, ccode) in rs:
        print '{} ({})'.format(cname, ccode)
    print("")

def add_country(rs, con):
    # prompt for country input
    country_code = raw_input("Country code................: ")
    country_name = raw_input("Country name................: ")
    gdp = raw_input("Country per capita gdp (USD): ")
    inflation = raw_input("Country inflation (pct).....: ")

    # query the database for the inputted country code
    exist_query = '''SELECT country_code FROM Country WHERE country_code = %s'''
    rs.execute(exist_query, (country_code,))
    row = rs.fetchone()
    if(row != None):
        print("\nThis country is already in the database.\n")
        return

    # insert the inputted country
    input_query = '''INSERT INTO Country values (%s, %s, %s, %s)'''
    rs.execute(input_query, (country_code, country_name, gdp, inflation))
    con.commit()
    print("\nCountry added!\n")

def find_gdp_inflation(rs, con):
    # prompt for search info
    limit = int(raw_input("Number of countries to display: "))
    min_gdp = int(raw_input("Minimum per capita gdp (USD)..: "))
    max_inflation = float(raw_input("Maximum inflation (pct).......: "))
    print("")

    # search the database and print
    search_query = '''SELECT country_name, country_code, gdp, inflation 
                      FROM Country 
                      WHERE gdp >= %s AND inflation <= %s 
                      LIMIT %s'''
    rs.execute(search_query, (min_gdp, max_inflation, limit))
    for (cname, ccode, cgdp, cinflation) in rs:
        print '{} ({}), {}, {}'.format(cname, ccode, cgdp, cinflation)
    print("")

def update_gdp_inflation(rs, con):
    # prompt for update info
    country_code = raw_input("Country code................: ")
    gdp = raw_input("Country per capita gdp (USD): ")
    inflation = raw_input("Country inflation (pct).....: ")

    # query the database for the inputted country code
    exist_query = '''SELECT country_code FROM Country WHERE country_code = %s'''
    rs.execute(exist_query, (country_code,))
    row = rs.fetchone()
    if(row == None):
        print("\nThis country is not in the database.\n")
        return

    # update the row
    update_query = '''UPDATE Country SET gdp = %s, inflation = %s WHERE country_code = %s'''
    rs.execute(update_query, (gdp, inflation, country_code))
    con.commit()
    print("\nUpdate added!\n")

if __name__ == '__main__':
    main()
    
