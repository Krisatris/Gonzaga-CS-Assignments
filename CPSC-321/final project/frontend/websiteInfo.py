# * NAME: Stella Beemer
# * CLASS: CPSC 321
# * DATE: 12/13/2021
# * HOMEWORK: Final Project
# * DESCRIPTION: This file creates the page that displays Groove ratings of entered websites

from tkinter import *
from PIL import ImageTk, Image
from frontend import mainPage, moreWebsiteInfo
from backend import dbService

def initializePage(con, rs, website):
    window = Tk()
    window.title("GROOVE")
    window.geometry("300x400")

    def backBtnClicked():
        window.destroy()
        mainPage.initializePage(con, rs)

    backBtn = Button(window, text="Back", command=backBtnClicked)
    backBtn.place(x=0, y=0)

    websiteLabel = Label(window, text=website, font=("Times New Roman", 15))
    websiteLabel.place(x=115, y=10)

    co2, waste, fairTrade, avgScore = dbService.getWebsiteScores(website, rs)

    avgTextLabel = Label(window, text="Average Rating", font=("Times New Roman", 12))
    avgTextLabel.place(x=100, y=130)

    img = Image.open("images/score-" + str(avgScore) + ".png")
    img = img.resize((75, 75), Image.ANTIALIAS)
    avgImg = ImageTk.PhotoImage(img)
    avgLabel = Label(window, image=avgImg)
    avgLabel.image = avgImg
    avgLabel.place(x=112, y=50)

    co2TextLabel = Label(window, text="carbon emissions", font=("Times New Roman", 12))
    co2TextLabel.place(x=10, y=180)
    wasteTextLabel = Label(window, text="waste impact", font=("Times New Roman", 12))
    wasteTextLabel.place(x=10, y=230)
    tradeTextLabel = Label(window, text="fair trade certification", font=("Times New Roman", 12))
    tradeTextLabel.place(x=10, y=280)

    img = Image.open("images/score-" + str(co2) + ".png")
    img = img.resize((40, 40), Image.ANTIALIAS)
    co2Img = ImageTk.PhotoImage(img)
    co2Label = Label(window, image=co2Img)
    co2Label.image = co2Img
    co2Label.place(x=200, y=170)

    img = Image.open("images/score-" + str(waste) + ".png")
    img = img.resize((40, 40), Image.ANTIALIAS)
    wasteImg = ImageTk.PhotoImage(img)
    wasteLabel = Label(window, image=wasteImg)
    wasteLabel.image = wasteImg
    wasteLabel.place(x=200, y=220)

    img = Image.open("images/score-" + str(fairTrade) + ".png")
    img = img.resize((40, 40), Image.ANTIALIAS)
    tradeImg = ImageTk.PhotoImage(img)
    tradeLabel = Label(window, image=tradeImg)
    tradeLabel.image = tradeImg
    tradeLabel.place(x=200, y=270)

    def moreInfoBtnClicked():
        moreWebsiteInfo.initializePage(website, con, rs)

    moreInfoBtn = Button(window, text="More info on ratings here!", command=moreInfoBtnClicked)
    moreInfoBtn.place(x=0, y=320)

    def favoritesClicked():
        result = dbService.addToFavorites(website, con, rs)
        resultLabel = Label(window, text=result, font=("Times New Roman", 12))
        resultLabel.place(x=20, y=360)

    favoriteBtn = Button(window, text="Favorite this website!", command=favoritesClicked)
    favoriteBtn.place(x=150, y=320)
