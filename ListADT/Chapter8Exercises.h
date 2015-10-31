/** Exercises for Chapter 8 **/
/** Question 1:
Consider an ADT list of integers.Write a pseudocode function that computes the sum of the integers in the list
aList.The defi nition of your function should be independent of the list’s implementation. 

Answer: 

sumIntegers(List aList) : integer
{
int addr = 0
for (0 < i < aList.getLength())
	addr += aList.getEntry(i)
return addr
}
*/

/** Question 2: Implement the function swap , as described in Checkpoint Question 3, but remove the assumption that the ith and
jth items on the list exist. Return a value that indicates whether the swap was successful.

Answer:
bool swap(const int& i, const int& j)
{
int listLength = getLength();
if (i > listLength || j > listLength)
	{
	return false; // if i or j is not in the list
	}
else {
	//copy j 
	ItemType copyJ = getEntry(j);
	// replace j with i
	setEntry(j, getEntry(i));
	// replace i with copyJ
	setEntry(i, copyJ);
	}
	return true;
}  
*/

/* Question 3: Use the function swap that you wrote in Exercise 2 to write a function that reverses the order of the items in a 
list aList.

Answer:

bool reverse() {
int listLength = getLength();
if (isEmpty() || listLength < 2) // empty list and single item list are reversed
{
return true;
}
int mid = listLength/2; // get midpoint of the list 
if (listLength % 2 == 0); // if the list if even, we will have even halves
{
  int loopVar = 1;
  while (loopVar <= mid) // this control statement will change for odd
  { 
  swap(loopVar, listLength - loopVar);
  loopVar++;
  }
  return true;
}
else // list is odd, so midpoint remains the same 
{
while (loopVar < mid)
{
swap (loopVar, listLength - loopVar);
loopVar++;
}
return true;
}	
*/

/* Question 12: Repeat Exercise 20 in chapter 2 using a list ADT

Chapter 2 Exercise 20:  Had to write a function f(n) both recursively and iteratively.  Solution was as follows:
/*
recursively & interatively compute function f(n) = f(n-1) + 3*f(n-5) forall n > 5
f(1) = f(2) = f(3) 1;
f(4) = 3;
f(5) = 4;

int computeRecursiveFunction(int n)
{
	// base case 1: n <= 3;
	switch (n)
	{
	case(1) :
	case(2) :
	case(3) :
			return 1;
		break;
	case(4) :
		return 3;
		break;
	case(5) :
		return 5;
		break;
	default:
		return computeRecursiveFunction(n - 1) + 3 * computeRecursiveFunction(n - 5);
	}
}
int computeIterativeFunction(int n)
{
switch (n) {
case(1) :
case(2) :
case(3) :
return 1;
break;
case(4) :
return 3;
break;
case(5) :
return 4;
break;
default:
int valOne, valTwo, valThree, valFour, valFive;
// sets initial values
valOne = valTwo = valThree = 1;
valFour = 3;
valFive = 5;
int current = 0;
for (int loopVar = 6; loopVar <= n; loopVar++)
{
// current is previous + 3 * the fifth previous
current = valFive + 3 * valOne;
// get ready for next iterative cycle
valOne = valTwo;
valTwo = valThree;
valThree = valFour;
valFour = valFive;
valFive = current;
}
return current;
}
}

simple wayto implement this function with the list:
list contains 5 integers initialized to the above values
same for loop;
same current variable;
for each loop cycle, replace valOne with valTwo, valThee with valFour, valFour with valFive, and finally valFive with current
// at the end you would return valFive.  
*/


