# * NAME: Stella Beemer
# * CLASS: CPSC 321
# * DATE: 12/13/2021
# * HOMEWORK: Final Project
# * DESCRIPTION: This file is the main page of the app. Links the user to 5 other pages.

from tkinter import *
from PIL import ImageTk, Image
from backend import dbService
from frontend import userInfo, websiteInfo, websiteDatabase, userStats, topSites

def initializePage(con, rs):
    window = Tk()
    window.title("GROOVE")
    window.geometry("300x400")

    def userBtnClicked():
        window.destroy()
        userInfo.initializePage(con, rs)

    img = Image.open("images/user_icon.png")
    img = img.resize((35, 35), Image.ANTIALIAS)
    iconImg = ImageTk.PhotoImage(img)
    userBtn = Button(window, image=iconImg, command=userBtnClicked)
    userBtn.place(x=259, y=0)

    welcomeLabel = Label(window, text="Welcome to Groove!", font=("Times New Roman", 25))
    welcomeLabel.place(x=10, y=40)

    infoLabel = Label(window, text="Groove displays sustainability ratings\n"
                                   "for online retailers!",
                                    font=("Times New Roman", 12))
    infoLabel.place(x=30, y=80)

    websiteLabel = Label(window, text="Enter a website below to get started!", font=("Times New Roman", 12))
    websiteLabel.place(x=30, y=130)

    websiteField = Entry(window)
    websiteField.place(x=50, y=180)

    def submitBtnClicked():
        website = websiteField.get()
        if(dbService.getWebsite(website, rs)):
            window.destroy()
            websiteInfo.initializePage(con, rs, website)
        else:
            errorLabel = Label(window, text="That website is not in our database!", font=("Times New Roman", 12))
            errorLabel.place(x=30, y=250)

    submitBtn = Button(window, text="Submit", command=submitBtnClicked)
    submitBtn.place(x=180, y=180)

    def databaseBtnClicked():
        window.destroy()
        websiteDatabase.initializePage(con, rs)

    databaseBtn = Button(window, text="See websites in database here!", command=databaseBtnClicked)
    databaseBtn.place(x=50, y=290)

    def userStatsBtnClicked():
        window.destroy()
        userStats.initializePage(con, rs)

    userStatsBtn = Button(window, text="See Groove user stats here!", command=userStatsBtnClicked)
    userStatsBtn.place(x=50, y=325)

    def topSitesBtnClicked():
        window.destroy()
        topSites.initializePage(con, rs)

    userStatsBtn = Button(window, text="See top rated Groove sites here!", command=topSitesBtnClicked)
    userStatsBtn.place(x=50, y=360)

    window.mainloop()
