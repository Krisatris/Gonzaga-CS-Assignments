# * NAME: Stella Beemer
# * CLASS: CPSC 321
# * DATE: 12/13/2021
# * HOMEWORK: Final Project
# * DESCRIPTION: This file prompts the user for login and links to create an account

from tkinter import *
from PIL import ImageTk, Image
from frontend import createAccount
from frontend import mainPage
from backend import dbService


def initializePage(con, rs):
    window = Tk()
    window.title("GROOVE")
    window.geometry("300x400")

    grooveImg = ImageTk.PhotoImage(Image.open("images/groove-48.png"))
    grooveLogo = Label(window, image=grooveImg)
    grooveLogo.place(x=20, y=10)
    appTitleLabel = Label(window, text="GROOVE", font=("Times New Roman", 30))
    appTitleLabel.place(x=80, y=10)

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
        if (dbService.validateUser(username, password, rs)):
            window.destroy()
            mainPage.initializePage(con, rs)
        else:
            authFailed = Label(window, text="Authentication failed.", font=("Times New Roman", 12))
            authFailed.place(x=50, y=290)

    submitBtn = Button(window, text="Submit", command=submitBtnClicked)
    submitBtn.place(x=50, y=240)

    def createAccClicked():
        window.destroy()
        createAccount.initializePage(con, rs)

    createAccBtn = Button(window, text="Create Account", command=createAccClicked)
    createAccBtn.place(x=100, y=240)

    window.mainloop()