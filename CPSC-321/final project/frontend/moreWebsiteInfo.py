# * NAME: Stella Beemer
# * CLASS: CPSC 321
# * DATE: 12/13/2021
# * HOMEWORK: Final Project
# * DESCRIPTION: This file creates displays the rationales for Groove ratings of websites

from tkinter import *
from backend import dbService


def initializePage(website, con, rs):
    window = Tk()
    window.title("GROOVE")
    window.geometry("600x400")

    websiteLabel = Label(window, text=website, font=("Times New Roman", 15))
    websiteLabel.place(x=115, y=10)

    co2TextLabel = Label(window, text="carbon emissions rationale:", font=("Times New Roman bold", 12))
    co2TextLabel.place(x=10, y=50)
    wasteTextLabel = Label(window, text="waste impact rationale:", font=("Times New Roman bold", 12))
    wasteTextLabel.place(x=10, y=150)
    tradeTextLabel = Label(window, text="fair trade rationale:", font=("Times New Roman bold", 12))
    tradeTextLabel.place(x=10, y=250)

    result = dbService.getRationale(website, rs)
    co2Rationale = Label(window, text=result[0], font=("Times New Roman", 10))
    co2Rationale.place(x=10, y=100)
    wasteRationale = Label(window, text=result[1], font=("Times New Roman", 10))
    wasteRationale.place(x=10, y=200)
    tradeRationale = Label(window, text=result[0], font=("Times New Roman", 10))
    tradeRationale.place(x=10, y=300)
