#include <iostream>
#include <cstdlib> // For rand()
#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>
#include <ctime> // For using srand(time(0))

using namespace std;

int counterBruteForce=0, counterDevide = 0;

struct Point
{
	double x, y;
};

int pNum;
vector<Point> p;

double randomNumber(double min, double max)
{
	return ((double)rand() / (double)RAND_MAX) * (max - min) + min;
}

/* Automatically Generate 10000 random numbers between -10000 to +10000 and write them into input.txt */
void autoGenerateRandNum() {
	srand(time(0));
	ofstream outPairFile;
	outPairFile.open("input.txt");
	if (outPairFile.is_open()) {
		int pairNumber = 100;
		pNum = pairNumber;
		//double xMin=-10000, xMax=10000, yMin=-10000, yMax=10000;
		double xMin = -10, xMax = 10, yMin = -10, yMax = 10;
		outPairFile << pairNumber << endl;
		for (int i = 0; i < pairNumber; i++)
			outPairFile << randomNumber(xMin, xMax) << " " << randomNumber(yMin, yMax) << endl;
		outPairFile.close();
	}
	else
		cout << "There was a problem generating or opening pair file" << endl;
}

/* Manually Generate random numbers between your desired x/y-coordinate and write them into input.txt */
void manuallyGenerateRandNum() {
	srand(time(0));
	ofstream outPairFile;
	outPairFile.open("input.txt");
	if (outPairFile.is_open()) {
		cout << "Enter number of pairs you want to generate: ";
		int pairNumber = 0;
		cin >> pairNumber;
		double xMin, xMax, yMin, yMax;
		cout << "Enter -x,+x coordinates" << endl;
		cin >> xMin >> xMax;
		cout << "Enter -y,+y coordinates" << endl;
		cin >> yMin >> yMax;

		outPairFile << pairNumber << endl;
		for (int i = 0; i < pairNumber; i++)
			outPairFile << randomNumber(xMin, xMax) << " " << randomNumber(yMin, yMax) << endl;
		outPairFile.close();
	}
	else
		cout << "There was a problem generating or opening pair file" << endl;
}

/* Calculate Distance between two points */
double calDist(Point p1, Point p2)
{
	return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

vector<Point> merge(vector<Point> left, vector<Point> right, string coord) {
	int i = 0, j = 0, k = 0; //i:return vect j:left k:right
	int lsize = left.size();
	int rsize = right.size();
	int size = lsize + rsize;
	vector<Point> sortedVect(size);
	for (i = 0; i < size; i++) {
		counterDevide++;
		if (j < lsize && k < rsize) {
			// if coord="x" or coord="y"
			if (coord == "x") { // Sort By X-coordinate
				if (left[j].x <= right[k].x) {
					sortedVect[i] = left[j];
					j++;
				}
				else {
					sortedVect[i] = right[k];
					k++;
				}
			}
			else { // Sort By Y-coordinate
				if (left[j].y <= right[k].y) {
					sortedVect[i] = left[j];
					j++;
				}
				else {
					sortedVect[i] = right[k];
					k++;
				}
			}

		}
		else if (j < lsize) {
			sortedVect[i] = left[j];
			j++;
		}
		else if (k < rsize) {
			sortedVect[i] = right[k];
			k++;
		}
	}
	return sortedVect;
}

vector<Point> mergeSort(vector<Point> vect, string coord) {
	int size = vect.size();
	int mid = size / 2;
	vector<Point> left;
	vector<Point> right;
	if (size <= 1)//base case
		return vect;
	for (int i = 0; i < mid; i++)
	{
		left.push_back(vect[i]);
		right.push_back(vect[i + mid]);
	}
	if (size % 2 != 0)
		right.push_back(vect.back());//Push last element of vector to the right vector in case size of vect is odd

	left = mergeSort(left, coord);
	right = mergeSort(right, coord);

	return merge(left, right, coord);
}

// Brute Force Approch goes here
vector<Point> bruteForce(vector<Point> p) {
	int psize = p.size();
	if (psize < 2)
		return p;
	else
	{
		double min = calDist(p[0], p[1]);
		Point p1 = p[0], p2 = p[1];
		for (int i = 0; i < psize; i++)
			for (int j = i + 1; j < psize; j++)
			{
				double distpp = calDist(p[i], p[j]);
				counterBruteForce++;
				if (distpp < min) {
					min = distpp;
					//Two min distance pair:
					p1 = p[i];
					p2 = p[j];					
				}
			}
		vector<Point> minPoints;
		minPoints.push_back(p1);
		minPoints.push_back(p2);
		return minPoints;
	}
}

// return a pair with minimum distance
vector<Point> closestPair(vector<Point> points) {
	if (points.size() <= 3) {
		// return min distance between these using brute-force
		return bruteForce(points);
	}
	int pointsSize = points.size();
	int half = pointsSize / 2;
	vector<Point> leftPairs;
	vector<Point> rightPairs;
	vector<Point> leftResult, rightResult;

	if (pointsSize % 2 == 0) {
		for (int i = 0; i < half; i++)
		{
			leftPairs.push_back(points[i]);
			rightPairs.push_back(points[i + half]);
		}
	}
	else
	{
		for (int i = 0; i <= half; i++)
		{
			leftPairs.push_back(points[i]);
		}
		for (int i = half + 1; i < pointsSize; i++)
		{
			rightPairs.push_back(points[i]);
		}
	}

	leftResult = closestPair(leftPairs);
	rightResult = closestPair(rightPairs);
	double minLeft = calDist(leftResult[0], leftResult[1]);
	double minRight = calDist(rightResult[0], rightResult[1]);
	double minLR = min(minLeft, minRight);
	vector<Point> stripPoints;
	// Since we have a sorted points based on their x,
	// It suffices to check only points around px
	for (int i = half-1; i > 0; i--)
	{
		if (points[half].x - points[i].x < minLR)
			stripPoints.push_back(points[i]);
		else
			break; // In case px>min
	}
	for (int i = half + 1; i < pointsSize; i++)
	{
		if (points[i].x- points[half].x < minLR)
			stripPoints.push_back(points[i]);
		else
			break; // In case px>min
	}
	stripPoints.push_back(points[half]);
	vector<Point> sortedStripPointsy;
	vector<Point> stripClosestPair;
	if (stripPoints.size() > 1) // At least one 2 points be in the strip area
	{
		// If there is a point in Strip Area
		// sort stripPoint by their y-coordinates
		double min = minLR;
		sortedStripPointsy = mergeSort(stripPoints, "y");
		int sizePointStrip = sortedStripPointsy.size();
		for (int i = 0; i < sizePointStrip - 1; i++)
			for (int j = i + 1; j < sizePointStrip && (sortedStripPointsy[j].y - sortedStripPointsy[i].y < min); j++)
			{
				counterDevide++;
				double pairDistance = calDist(sortedStripPointsy[i], sortedStripPointsy[j]);
				if (pairDistance < min)
				{
					min = pairDistance;
					stripClosestPair.clear();
					stripClosestPair.push_back(sortedStripPointsy[i]);
					stripClosestPair.push_back(sortedStripPointsy[j]);
				}
			}

		if (stripClosestPair.size()>0) // If closest pair is in the strip line
			return stripClosestPair;
		else
			return (minLeft < minRight) ? leftResult : rightResult;
	}
	else
		return (minLeft < minRight) ? leftResult : rightResult;
}

int main()
{
	system("cls");
	cout << "\t\t*******************************************" << endl;
	cout << "\t\t\t   Finding Closest Pair" << endl;
	cout << "\t\t\tWritten By: Mahsa Radinmehr" << endl;
	cout << "\t\t*******************************************" << endl << endl;

	// Uncomment one of these two if you want to generate new Numbers
	autoGenerateRandNum();
	//manuallyGenerateRandNum();

	string line;
	ifstream pointFile("input.txt");
	if (pointFile.is_open())
	{
		getline(pointFile, line);
		pNum = stoi(line);
		int i = 0;

		while (getline(pointFile, line))
		{
			double x = stod(line.substr(0, line.find(" ")));
			double y = stod(line.substr(line.find(" ")));
			Point pTemp;
			pTemp.x = x;
			pTemp.y = y;
			p.push_back(pTemp);
			i++;
		}
		pointFile.close();
	}
	else
		cout << "There was a problem opening or reading pair file" << endl;

	// Broute-Force Strategy
	vector<Point> minPointsBruteForce;
	clock_t beginBruteForce = clock();
	minPointsBruteForce = bruteForce(p);
	clock_t endBruteForce = clock();
	double elapsedSecsBruteForce = double(endBruteForce - beginBruteForce) / CLOCKS_PER_SEC;
	double distMin = calDist(minPointsBruteForce[0], minPointsBruteForce[1]);
	cout << "Brute-Force:" << endl;
	cout << "Min Dist: " << distMin << endl;
	cout << "Pairs are: (" << minPointsBruteForce[0].x << "," << minPointsBruteForce[0].y << ") (" << minPointsBruteForce[1].x << "," << minPointsBruteForce[1].y << ")" << endl;
	cout << "Total Running Time of Brute-Force: " << elapsedSecsBruteForce<< endl;
	cout << "Brute-Force Counter: " << counterBruteForce << endl;
	cout << "***********************************\n" << endl;
	// End of Brute-Force

	// Devide & Conquer Strategy
	clock_t beginDevide = clock();
	cout << "Devide & Conquer:" << endl;
	if (p.size() < 2) { // In case we have only two points
						// return two points and their distance
		cout << "p1: " << p[0].x << " " << p[0].y << " , p2: " << p[1].x << " " << p[1].y << calDist(p[0], p[1]) << endl;
	}
	else {
		vector<Point> sortedPx;
		sortedPx = mergeSort(p, "x");
		vector<Point> closestP = closestPair(sortedPx);
		clock_t endDevide = clock();
		double elapsedSecsDevide = double(endDevide - beginDevide) / CLOCKS_PER_SEC;
		cout << "Min Dist: " << calDist(closestP[0], closestP[1]) << endl;
		cout << "Closest Pair: (" << closestP[0].x << "," << closestP[0].y << ") (" << closestP[1].x << "," << closestP[1].y << ")" << endl;
		cout << "Total Running Time of Devide & Conquer: " << elapsedSecsDevide << endl;
		cout << "Devide & Conquer Counter: " << counterDevide << endl;
	}
	// End of Devide & Conquer Strategy

	char ch;
	cin >> ch;
	return 0;
}