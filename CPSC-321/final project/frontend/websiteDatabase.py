# * NAME: Stella Beemer
# * CLASS: CPSC 321
# * DATE: 12/13/2021
# * HOMEWORK: Final Project
# * DESCRIPTION: This file displays all websites in Groove's database

from tkinter import *
from backend import dbService
from frontend import mainPage


# this class is from Black Thunder on stackxchange and creates a bulleted list in a tkinter label
# https://stackoverflow.com/questions/52531830/creating-a-bulleted-list-on-a-label-widget-using-python-tkinter
class BLabel(object):
    b = "•"

    def __init__(self, master):
        self.l = Label(master)

    def add_option(self, text):
        if self.l.cget("text") == "":
            self.l.config(text=self.b + " " + text)
        else:
            self.l.config(text=self.l.cget("text") + "\n" + self.b + " " + text)


def initializePage(con, rs):
    window = Tk()
    window.title("GROOVE")
    window.geometry("300x400")

    def backBtnClicked():
        window.destroy()
        mainPage.initializePage(con, rs)

    backBtn = Button(window, text="Back", command=backBtnClicked)
    backBtn.place(x=0, y=0)

    titleLabel = Label(window, text="Websites in our database:", font=("Times New Roman", 15))
    titleLabel.place(x=50, y=10)

    suggestLabel = Label(window, text="Don't see a website listed? Suggest it below!", font=("Times New Roman", 12))
    suggestLabel.place(x=10, y=50)

    websiteField = Entry(window)
    websiteField.place(x=50, y=90)

    def submitBtnClicked():
        website = websiteField.get()
        resultTxt = dbService.addSuggestion(website, con, rs)
        result = Label(window, text=resultTxt, font=("Times New Roman", 12))
        result.place(x=50, y=120)

    submitBtn = Button(window, text="Submit", command=submitBtnClicked)
    submitBtn.place(x=180, y=90)

    websiteList = dbService.getWebsitesInDB(rs)
    bullets = BLabel(master=window)
    for i in websiteList:
        bullets.add_option(i)
    bullets.l.place(x=100, y=180)
