# Homework #5 - Advanced Exception Handling & Input Validation

Exception Handling (Paul Deitel & Harvey Deitel Textbook, Chapter# 12)

## Purpose of This Assignment

This homework is designed for an **advanced C++ class** and focuses on **design-level understanding** of exception handling, not just syntax.

You are expected to demonstrate: - Exception propagation across multiple functions - Proper use of rethrowing - RAII and stack unwinding behavior - Polymorphic exception handling - Correct judgment about when exceptions should and should not be used

## General Instructions

- Use **C++ exceptions** (throw, try, catch) appropriately.
- Catch exceptions **by const reference**.
- Do **not** use exit() or abort().
- Do **not** suppress exceptions silently.
- Programs must compile without warnings.
- Include meaningful comments explaining **why** exceptions are used.
- Each problem is a **separate program**.

## Problem 1 - Exception Propagation and Rethrowing

### Objective

Demonstrate exception propagation across multiple function calls and proper rethrowing.

### Program Description

Write a program with three functions:

- readData() - validates input
- processData() - performs computation
- main() - handles final error reporting

### Step-by-Step Requirements

- In readData():
  - Prompt the user for an integer.
  - If the input is not an integer, throw std::invalid_argument.
- In processData():
  - Call readData() inside a try block.
  - Catch the exception, display a short logging message.
  - **Rethrow** the exception using throw;.
- In main():
  - Catch the rethrown exception.
  - Display the final error message.

### Sample Output

Enter an integer: abc  
\[processData\] Logging error before rethrow  
Error in main: Invalid integer input

## Problem 2 - RAII and Stack Unwinding

### Objective

Show that destructors are automatically called during stack unwinding.

### Program Description

Create a class named ResourceTracker that simulates management of a resource.

### Step-by-Step Requirements

- ResourceTracker must:
  - Print a message in its constructor.
  - Print a message in its destructor.
- Write a function dangerousFunction() that:
  - Creates a local ResourceTracker object.
  - Throws a std::runtime_error.
- Call dangerousFunction() from main() inside a try-catch block.
- Observe destructor execution.

### Sample Output

Resource acquired  
Resource released  
Caught exception: Runtime error occurred

## Problem 3 - Custom Exception Hierarchy

### Objective

Design and use a polymorphic exception hierarchy.

### Program Description

Simulate a file processing system with multiple error types.

### Step-by-Step Requirements

- Create a base exception class FileException derived from std::exception.
- Create two derived exceptions:
  - FileNotFoundException
  - PermissionDeniedException
- Override what() in each derived class.
- Write a function openFile(int code):
  - If code == 1, throw FileNotFoundException.
  - If code == 2, throw PermissionDeniedException.
- In main():
  - Catch derived exceptions first.
  - Catch FileException last.

### Sample Output

Error: File not found

## Problem 4 - Input Validation vs Exception Use

### Objective

Demonstrate correct judgment when validating user input.

### Program Description

Write a program that prompts the user for a positive integer.

### Step-by-Step Requirements

- Use a **loop** (not exceptions) to handle simple user mistakes.
- If the user enters non-numeric input, clear the stream and reprompt.
- If the user enters a value greater than 1,000,000:
  - Throw std::out_of_range.
- Catch the exception in main() and display an error message.
- Add comments explaining why exceptions were used only for extreme cases.

### Sample Output

Enter a positive integer: 2000000  
Error: Value exceeds allowed maximum

## **Submission Requirements**

- Submit **four PDF files** (one per problem).
- Programs must compile and run correctly.
- Code must be clearly commented.
- Output must be included at the end of each program (Comment the output).