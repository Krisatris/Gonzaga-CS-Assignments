
'''
    command line-based function for testing that my logic is correct
    takes two center points and a radius, prints the points needed for the
    circle in the command line
'''
def midPointCircleCommandLine(xCenter, yCenter, radius):
    x = radius
    y = 0

    # printing the initial point
    print("(", x + xCenter, ", ", y + yCenter, ")", sep="", end="")

    if(radius > 0):
        print("(", x + xCenter, ", ", -y + yCenter, ")", sep="", end="")
        print("(", y + xCenter, ", ", x + yCenter, ")", sep="", end="")
        print("(", -y + xCenter, ", ", x + yCenter, ")", sep="")

    midPoint = 1 - radius

    while(x > y):
        y += 1

        if(midPoint <= 0):
            midPoint = midPoint + 2 * y + 1
        else:
            x -= 1
            midPoint = midPoint + 2 * y - 2 * x + 1

        if(x < y):
            break

        print("(", x + xCenter, ", ", y + yCenter, ")", sep="", end="")
        print("(", -x + xCenter, ", ", y + yCenter, ")", sep="", end="")
        print("(", x + xCenter, ", ", -y + yCenter, ")", sep="", end="")
        print("(", -x + xCenter, ", ", -y + yCenter, ")", sep="")

        if(x != y):
            print("(", y + xCenter, ", ", x + yCenter, ")", sep="", end="")
            print("(", -y + xCenter, ", ", x + yCenter, ")", sep="", end="")
            print("(", y + xCenter, ", ", -x + yCenter, ")", sep="", end="")
            print("(", -y + xCenter, ", ", -x + yCenter, ")", sep="")

# function to pass lists of circle points to animation programs
def midPointCircle(xCenter, yCenter, radius):
    x = radius
    y = 0

    points = []

    # store the first point
    points.append((x + xCenter, y + yCenter))

    if (radius > 0):
        points.append((x + xCenter, -y + yCenter))
        points.append((y + xCenter, x + yCenter))
        points.append((-y + xCenter, x + yCenter))

    midPoint = 1 - radius

    while (x > y):
        y += 1

        if (midPoint <= 0):
            midPoint = midPoint + 2 * y + 1
        else:
            x -= 1
            midPoint = midPoint + 2 * y - 2 * x + 1

        if (x < y):
            break


        points.append((x + xCenter, y + yCenter))
        points.append((-x + xCenter, y + yCenter))
        points.append((x + xCenter, -y + yCenter))
        points.append((-x + xCenter, -y + yCenter))

        if (x != y):
            points.append((y + xCenter, x + yCenter))
            points.append((-y + xCenter, x + yCenter))
            points.append((y + xCenter, -x + yCenter))
            points.append((-y + xCenter, -x + yCenter))

    #return quadOne, quadTwo, quadThree, quadFour
    return points

def main():
    '''
    enter midpointCircleCommandLine() calls here to test that function
    I suggest removing them before running turtleAnimation to avoid having
    your command line spammed
    '''

main()

