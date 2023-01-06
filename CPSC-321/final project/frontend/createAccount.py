# * NAME: Stella Beemer
# * CLASS: CPSC 321
# * DATE: 12/13/2021
# * HOMEWORK: Final Project
# * DESCRIPTION: This file prompts the user to create an account

from tkinter import *
from backend import dbService
from frontend import loginPage

def initializePage(con, rs):
    window = Tk()
    window.title("GROOVE")
    window.geometry("300x400")

    createAccLabel = Label(window, text="Create an account for Groove", font=("Times New Roman", 16))
    createAccLabel.place(x=10, y=10)

    usernameLabel = Label(window, text="Username:", font=("Times New Roman", 12))
    usernameLabel.place(x=50, y=80)
    usernameField = Entry(window)
    usernameField.place(x=50, y=110)

    passwordLabel = Label(window, text="Password:", font=("Times New Roman", 12))
    passwordLabel.place(x=50, y=160)
    passwordField = Entry(window, show="*")
    passwordField.place(x=50, y=190)

    def submitBtnClicked():
        username = usernameField.get()
        password = passwordField.get()
        resultTxt = dbService.createAccount(username, password, con, rs)
        result = Label(window, text=resultTxt, font=("Times New Roman", 12))
        result.place(x=50, y=290)

    submitBtn = Button(window, text="Submit", command=submitBtnClicked)
    submitBtn.place(x=50, y=240)

    def returnClicked():
        window.destroy()
        loginPage.initializePage(con, rs)

    returnBtn = Button(window, text="Return to Login", command=returnClicked)
    returnBtn.place(x=100, y=240)