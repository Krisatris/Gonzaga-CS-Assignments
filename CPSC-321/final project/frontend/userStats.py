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

    titleLabel = Label(window, text="Groove User Statistics", font=("Times New Roman", 15))
    titleLabel.place(x=70, y=10)

    infoLabel = Label(window, text="See the most popular favorite websites by\n category, age, and gender of users!",
                      font=("Times New Roman", 10))
    infoLabel.place(x=30, y=40)

    categoryOptions = dbService.getCategories(rs)
    categoryOptions.append("All Categories")
    categoryVar = StringVar(window)
    categoryVar.set(categoryOptions[0])

    ageOptions = ['18-24', '25-30', '31-45', '45-99', 'all ages']
    ageVar = StringVar(window)
    ageVar.set(ageOptions[4])

    genderOptions = ['male', 'female', 'non-binary', 'genderfluid', 'all genders']
    genderVar = StringVar(window)
    genderVar.set(genderOptions[4])

    categoryLabel = Label(window, text="Category:", font=("Times New Roman", 10))
    categoryLabel.place(x=10, y=80)

    ageLabel = Label(window, text="Age:", font=("Times New Roman", 10))
    ageLabel.place(x=10, y=120)

    genderLabel = Label(window, text="Gender:", font=("Times New Roman", 10))
    genderLabel.place(x=10, y=160)

    categoryEntry = OptionMenu(window, categoryVar, *categoryOptions)
    categoryEntry.place(x=70, y=80)

    ageEntry = OptionMenu(window, ageVar, *ageOptions)
    ageEntry.place(x=70, y=120)

    genderEntry = OptionMenu(window, genderVar, *genderOptions)
    genderEntry.place(x=70, y=160)

    resultVar = StringVar()
    resultLabel = Label(window, textvariable=resultVar, font=("Times New Roman", 12))
    resultLabel.place(x=70, y=220)

    def submitBtnClicked():
        category = categoryVar.get()
        age = ageVar.get()
        gender = genderVar.get()
        result = dbService.determineQuery(category, age, gender, rs)
        if len(result) == 0:
            result = "There is no user info for this filter."
        resultVar.set(result)

    submitBtn = Button(window, text="Submit", command=submitBtnClicked)
    submitBtn.place(x=200, y=160)
