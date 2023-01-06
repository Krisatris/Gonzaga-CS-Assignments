# * NAME: Stella Beemer
# * CLASS: CPSC 321
# * DATE: 12/13/2021
# * HOMEWORK: Final Project
# * DESCRIPTION: This file displays user info and prompts the user to update their info

from tkinter import *
from backend import dbService
from frontend import mainPage

def initializePage(con, rs):
    window = Tk()
    window.title("GROOVE")
    window.geometry("300x400")

    def backBtnClicked():
        window.destroy()
        mainPage.initializePage(con, rs)

    backBtn = Button(window, text="Back", command=backBtnClicked)
    backBtn.place(x=0, y=0)

    titleLabel = Label(window, text="User Info", font=("Times New Roman", 15))
    titleLabel.place(x=100, y=10)

    age, gender = dbService.getUserInfo(con, rs)
    username = dbService.getAuthUser()

    infoStr = username + "\n" + age + "\n" + gender

    promptLabel = Label(window, text="Username:\nAge:\nGender:\n", font=("Times New Roman", 12))
    promptLabel.place(x=20, y=60)

    infoLabel = Label(window, text=infoStr, font=("Times New Roman", 12))
    infoLabel.place(x=200, y=60)

    updateTitleLabel = Label(window, text="Update Info", font=("Times New Roman", 15))
    updateTitleLabel.place(x=100, y=150)

    ageLabel = Label(window, text="Enter Age:", font=("Times New Roman", 12))
    ageLabel.place(x=20, y=200)

    genderLabel = Label(window, text="Choose Gender:", font=("Times New Roman", 12))
    genderLabel.place(x=20, y=250)

    ageEntry = Entry(window)
    ageEntry.place(x=100, y=200)

    var = StringVar(window)
    var.set("male")
    genderEntry = OptionMenu(window, var, "male", "female", "non-binary", "genderfluid")
    genderEntry.place(x=150, y=250)

    def submitBtnClicked():
        updateAge = ageEntry.get()
        updateGender = var.get()
        resultTxt = dbService.updateUserInfo(updateAge, updateGender, con, rs)
        result = Label(window, text=resultTxt, font=("Times New Roman", 12))
        result.place(x=10, y=350)

    submitBtn = Button(window, text="Submit", command=submitBtnClicked)
    submitBtn.place(x=180, y=300)
