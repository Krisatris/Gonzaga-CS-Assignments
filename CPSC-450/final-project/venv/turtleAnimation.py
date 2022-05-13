import turtle
import algorithm

def drawCircle(color, xCenter, yCenter, radius):

    points = algorithm.midPointCircle(xCenter, yCenter, radius)

    s = turtle.Screen()
    t = turtle.Turtle()
    t.penup()
    t.hideturtle()
    padding = 10

    t.color(color)

    if(radius >= 100):
        t.speed(10)
    else:
        t.speed(radius // 10)

    # writing the 4 initial points
    t.goto(xCenter, yCenter + radius + padding)
    t.write((xCenter, yCenter + radius), align='center')
    t.goto(xCenter + radius + padding, yCenter)
    t.write((xCenter + radius, yCenter))
    t.goto(xCenter, yCenter - radius - (2 * padding))
    t.write((xCenter, yCenter - radius), align='center')
    t.goto(xCenter - radius - (4 * padding), yCenter)
    t.write((xCenter - radius, yCenter), align='left')

    # drawing the circle
    for i in range(len(points)):
        x, y = points[i]
        t.goto(x, y)
        t.pendown()
        t.forward(1)
        t.penup()

    s.exitonclick()

def main():

    colors = ["red", "orange", "yellow", "green", "blue", "purple", "pink", "black", "brown"]

    # prompt users for info
    xCenter = int(input("Enter a x-center point: "))
    yCenter = int(input("Enter a y-center point: "))
    while True:
        radius = int(input("Enter a radius (non-negative): "))
        if radius > -1:
            break
    while True:
        color = str(input("Enter a color (enter \'options\' for possible choices): "))
        if(color == "options"):
            print(colors)
        elif(color in colors):
            break
    if(radius < 10):
        print("WARNING: circle and animation will be very small")

    drawCircle(color, xCenter, yCenter, radius)

main()