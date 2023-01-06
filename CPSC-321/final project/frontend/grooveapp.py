# * NAME: Stella Beemer
# * CLASS: CPSC 321
# * DATE: 12/13/2021
# * HOMEWORK: Final Project
# * DESCRIPTION: This file starts the app. Originally was the file called to start but command line didn't like that

from frontend import loginPage
from backend import dbService

def start():
    con, rs = dbService.initializeDb()
    loginPage.initializePage(con, rs)
