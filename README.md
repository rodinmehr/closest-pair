# closest-pair
The closest pair of points problem - Using Brute-Force and Divide &amp; Conquer Strategies

The closest pair of points problem or closest pair problem is a problem of computational geometry: given n points in metric space, find a pair of points with the smallest distance between them.

In this program I used two different method to solve this problem in Euclidean space of 2 dimension:
1. Brute-Force
2. Divide and Conquer

The first one is a naive approach toward solving this problem which we measure every possible distance between all the points. It has O(n^2) Time Complexity.

The Second one is a better solution and it will dived the input points to two sub problems and recursively search for the solution. In this program I used "Merge Sort" and Since I sort points based on their x-coordinates and passed it to function "closestPair()" and another time in this function sort some points based on their y-coordinates, it has O(n*log^2 n) Time complexity.

Another better approach is to sort points by their x and y coordinates at the same time. which I didn't implement in my program. In this case we would have O(n*log n) Time Complexity and It's proved to be the lower bound as well.

## Code Review:
`struct Point
{
	double x, y;
};
`
All the program works with this structure and define our points.

`double randomNumber(double min, double max)`
This is for generating random numbers.

`void autoGenerateRandNum()`
is used for generating n points with x and y coordinates automatically into a file input.txt

`void manuallyGenerateRandNum()`
is just like upper function but it will work manually and it will ask the user to enter:
1. how many numbers
2. minimum/maximum x
3. minimum/maximum x

`double calDist(Point p1, Point p2)`
calculating distance between points p1 and p2

`vector<Point> merge(vector<Point> left, vector<Point> right, string coord)'
is used for combining part for merg sort

'vector<Point> mergeSort(vector<Point> vect, string coord)'
sort vect by deviding it to two different sub problem. Variable 'coord' is either 'x' or 'y' based on our needs, so it will sort the vect which is our points by their x or y coordinates.

`vector<Point> bruteForce(vector<Point> p)`
Naive approach to solve the problem. It will test all the points with each other to find minimum pair.

`vector<Point> closestPair(vector<Point> points)`
This is where the magic goes :)
It will divide points (which are sorted by their x-coord) into half. So we will have:
Left and Right points
it will recursively call the function till find the minimum pair of left and right
The most tricky part is in combining these two. In this case we will make a hypothetical strip around the middle point and search for the potential points that might be our real pair. So another sort base on their y-coord and we will search. *The important thing is that we don't need to check all of them and it suffice to check only a constant points (believed to be less than 6 points).

