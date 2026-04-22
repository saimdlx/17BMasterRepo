# **HW #4**

**Feet and Inches Class - Operator Overloading**

In this assignment, you will design and implement a class named FeetInches that represents a distance measured in **feet and inches**.

You will overload several operators so that objects of this class behave like built-in numeric types.

- **Class Design**

Create a class named FeetInches with the following private data members:

int feet;

int inches;

**Important Rule:**

The number of inches must always be kept in **standard form**:

- 12 inches = 1 foot
- Inches must be between 0 and 11
- Negative values must be simplified correctly

For example:

| **Input**        | **Should Become** |
| ---------------- | ----------------- |
| 3 feet 14 inches | 4 feet 2 inches   |
| 5 feet -2 inches | 4 feet 10 inches  |

You must write a private member function:

**void simplify();**

This function ensures that the object is always stored in valid form.

- **Constructor**

Provide a constructor with default values:

FeetInches(int f = 0, int i = 0);

The constructor must call simplify().

- **Overload the Following Operators**

You must overload:

**Arithmetic Operators**

- \+ (Addition)
- \- (Subtraction)

**Increment Operators**

- Prefix ++
- Postfix ++

**Comparison Operators**

- >
- <
- ==

**Stream Operators**

- << (Output operator)
- >> (Input operator)

The << operator must display objects in this format:

X feet, Y inches

The >> operator must prompt the user for feet and inches.

- **Main Program Requirements**

Your main() function must:

- Create two FeetInches objects.
- Ask the user to enter distances for both objects.
- Display:
  - The two distances entered
  - Their sum
  - Their difference
  - Results of comparison operators
  - Results of prefix and postfix increment

**//---------Sample Output #1-----**

Enter a distance in feet and inches.

Feet: 5

Inches: 8

Enter another distance in feet and inches.

Feet: 3

Inches: 11

The values you entered are:

5 feet, 8 inches and 3 feet, 11 inches

Sum:

9 feet, 7 inches

Difference:

1 feet, 9 inches

Comparison Results:

First > Second : true

First < Second : false

First == Second : false

Prefix ++ First:

5 feet, 9 inches

Postfix ++ Second:

Before increment: 3 feet, 11 inches

After increment : 4 feet, 0 inches

**Sample Output #2 (Automatic Simplification)**

Enter a distance in feet and inches.

Feet: 2

Inches: 15

Enter another distance in feet and inches.

Feet: 1

Inches: -5

The values you entered are:

3 feet, 3 inches and 0 feet, 7 inches

(Notice how the program automatically simplified the input.)

**Sample Output #3 (Equal Values)**

Enter a distance in feet and inches.

Feet: 4

Inches: 6

Enter another distance in feet and inches.

Feet: 4

Inches: 6

The values you entered are:

4 feet, 6 inches and 4 feet, 6 inches

Comparison Results:

First > Second : false

First < Second : false

First == Second : true

**Submission Requirements**

- Submit:
  - FeetInches.h
  - FeetInches.cpp **Upload one or three PDFs**
  - main.cpp
- Code must:
  - Be properly formatted
  - Include meaningful comments
  - Use descriptive variable names
  - Follow good coding style

**Common Mistakes to Avoid**

- Forgetting to call simplify() after operations
- Incorrect postfix increment return value
- Not handling negative inches correctly
- Comparing only feet and ignoring inches
- Forgetting to make &lt;< and &gt;> friend functions