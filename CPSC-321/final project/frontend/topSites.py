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

    titleLabel = Label(window, text="Top Rated Sites on Groove!", font=("Times New Roman", 15))
    titleLabel.place(x=40, y=10)

    result = dbService.findTopSites(rs)
    topSitesLabel = Label(window, text=result, font=("Times New Roman", 12))
    topSitesLabel.place(x=100, y=50)

    filterLabel = Label(window, text="Filter by category:")
    filterLabel.place(x=10, y=180)

    options = dbService.getCategories(rs)
    var = StringVar(window)
    var.set(options[0])
    categoryOptions = OptionMenu(window, var, *options)
    categoryOptions.place(x=110, y=180)

    textVar = StringVar()
    filteredTopLabel = Label(window, textvariable=textVar, font=("Times New Roman", 12))
    filteredTopLabel.place(x=100, y=220)

    def submitBtnClicked():
        category = var.get()
        filteredResult = dbService.getFilteredTop(category, rs)
        textVar.set(filteredResult)
        filteredTopLabel.place(x=100, y=220)

    submitBtn = Button(window, text="Submit", command=submitBtnClicked)
    submitBtn.place(x=250, y=180)
