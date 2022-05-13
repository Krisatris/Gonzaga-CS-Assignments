import unittest
import algorithm

class TestAlgorithmMethods(unittest.TestCase):

    def test_basic(self):
        points = algorithm.midPointCircle(0, 0, 5)
        self.assertEqual(len(points), 28)

        # check that everything in list is tuples
        for i in range(len(points)):
            self.assertEqual(type(points[i]), tuple)

        # check that the first two and last points are correct and in list
        self.assertEqual(points.count((5, 0)), 2)
        self.assertEqual(points.count((0, 5)), 2)
        self.assertEqual(points.count((5, 1)), 1)
        self.assertEqual(points.count((-5, 1)), 1)
        self.assertEqual(points.count((5, -1)), 1)
        self.assertEqual(points.count((-5, -1)), 1)
        self.assertEqual(points.count((3, 4)), 1)
        self.assertEqual(points.count((-3, 4)), 1)
        self.assertEqual(points.count((4, -3)), 1)
        self.assertEqual(points.count((-4, -3)), 1)

    # test that when a radius of 0 is entered only one point is calculated
    def test_radius_zero(self):
        points = algorithm.midPointCircle(0, 0, 0)
        self.assertEqual(len(points), 1)
        self.assertEqual(points[0], (0, 0))

    '''
    when a negative radius is entered, only one point should be calculated
    note that although a negative radius can be entered here, the animation program
    will not accept it as a valid input
    '''

    def test_negative_radius(self):
        points = algorithm.midPointCircle(0, 0, -1)
        self.assertEqual(len(points), 1)
        self.assertEqual(points[0], (-1, 0))

    def test_nonzero_midpoint(self):
        points = algorithm.midPointCircle(5, 5, 2)
        self.assertEqual(len(points), 12)
        for i in range(len(points)):
            self.assertEqual(type(points[i]), tuple)
        self.assertEqual(points.count((7, 5)), 2)
        self.assertEqual(points.count((5, 7)), 2)
        self.assertEqual(points.count((7, 6)), 1)
        self.assertEqual(points.count((3, 6)), 1)
        self.assertEqual(points.count((7, 4)), 1)
        self.assertEqual(points.count((3, 4)), 1)
        self.assertEqual(points.count((6, 7)), 1)
        self.assertEqual(points.count((4, 7)), 1)
        self.assertEqual(points.count((6, 3)), 1)
        self.assertEqual(points.count((4, 3)), 1)

    '''
    ANIMATION TESTING
        because you cannot unit test a turtle animation, below
        are the test cases i used and the items i had to visually confirm work

    basic animation + color test:
        enter 0, 0, 20, black
            - confirm written points as (0, 20), (20, 0), (0, -20), (-20, 0)
            - confirm the circle is drawn in black
            - confirm screen does not close until user hits the close window button
        enter 0, 0, 20, red
            - confirm same points as above except circle is red instead of black
        enter 0, 0, 20, orange
            - confirm same points as above except circle is orange
        REPEAT FOR ALL COLORS
            - passes all of these tests
            - change made after this test: hiding turtle and center justifying top most and bottom most
                written points

    input sanitization test:
        enter 0, 0, -10, black
            - confirm that program reprompts when a negative radius is entered
                - passes this test
        enter, 0, 0, 10, options
            - confirm that program prints the possible colors you can choose from
                - passes this test
        enter, 0, 0, 10, teal
            - confirm that program reprompts when a non-valid color is entered
                - passes this test

    small circle test:
        enter 0, 0, 5, black:
            - confirm that command line gives a "WARNING: circle shown will be very small" prompt
                when given this radius
                - passes this test

    large circle test:
        enter 10, 10, 100, black:
            - confirm written points are (10, 110), (110, 10), (10, -90), (-90, 10)
            - confirm that the full circle is drawn
                - passes this test (figure in write up of this test)
    '''

if __name__ == '__main__':
    unittest.main()