# **HW #7 (Introduction to Qt & GUI Fundamentals)**

**Homework Assignment 1: Personal Contact Book**

Build a Qt application that allows users to manage a list of personal contacts. Your main window must be a QMainWindow subclass with a menu bar, toolbar, and status bar. This assignment tests your understanding of widgets, layouts, signals/slots, QMainWindow, and basic event handling.

**Requirements**

**Part 1: Main Window and UI Design:**

**QMainWindow Structure:**

- **Menu Bar** - File menu with: New Contact, Save All, Exit. Edit menu with: Delete Contact. Help menu with: About.
- **Toolbar** - Icon buttons for New Contact, Save All, and Delete Contact (use QAction objects shared with the menu).
- **Status Bar** - Display context messages (e.g., "Contact saved", "3 contacts loaded").

**Central Widget Layout:**

The central widget should use a horizontal split:

**Left Panel:**

- A QListWidget displaying contact names
- A QLineEdit above the list for searching/filtering

**Right Panel (Contact Details Form):**

- QLineEdit fields for: First Name, Last Name, Email, and Phone Number
- A QComboBox for Contact Category (Friend, Family, Work, Other)
- A QTextEdit for Notes
- "Save" and "Clear" buttons

**Part 2: Functionality:**

**Add Contact** - Triggering the New Contact action clears the form. Filling in details and clicking "Save" creates a new contact and adds it to the list.

**View/Edit Contact** - Clicking a name in the list loads that contact's details into the form. Editing and clicking "Save" updates the contact.

**Delete Contact** - Triggering the Delete action shows a QMessageBox confirmation dialog. If confirmed, the contact is removed from the list.

**Search/Filter** - Typing in the search field filters the contact list in real time. Search should match against first name, last name, or email.

**Data Persistence** - Save all contacts to a JSON file. Use QFileDialog::getSaveFileName() for "Save As". Override closeEvent to prompt "Save before closing?" if there are unsaved changes. Load contacts from file on startup.

**Part 3: Input Validation**

- First Name and Last Name must not be empty and should contain only letters and spaces
- Email must match a basic pattern: <something@something.something>
- Phone must contain only digits, spaces, dashes, and parentheses
- Display clear error messages using QMessageBox when validation fails

**Deliverables**

- Print all source files in PDF and upload them to Canvas (h, .cpp, CMakeLists.txt or .pro)

**Homework Assignment 2: Student Grade Tracker**

Build a Qt application that helps a student track their grades across multiple courses. Your main window must be a QMainWindow subclass. This assignment focuses on more advanced widget usage, QMainWindow features, dynamic UI updates, and data management.

**Requirements**

**Part 1: Main Window and UI Design**

**QMainWindow Structure:**

- **Menu Bar** - File menu: Save Grades, Load Grades, Exit. Course menu: Add Course, Remove Course. Help menu: About.
- **Toolbar** - Buttons for Add Course, Add Grade, and Save (share QAction objects with menu).
- **Status Bar** - Show current course name and number of grades, updated dynamically.

**Central Widget Layout:**

**Top Section - Course Selection:**

- A QComboBox to select the current course
- A QLabel showing the overall GPA across all courses

**Middle Section - Grade Entry:**

- QLineEdit for assignment name
- QSpinBox for points earned (0-100)
- QSpinBox for total possible points (1-100)
- QComboBox for category (Homework, Quiz, Exam, Project)
- "Add Grade" button

**Bottom Section - Grade Display:**

- A QTableWidget showing all grades for the selected course with columns: Assignment, Category, Score, Percentage, Letter Grade
- "Delete Selected" button to remove a grade entry
- A QProgressBar showing the current course average

**Part 2: Functionality**

**Course Management**- Add courses via QInputDialog::getText(). Remove courses with confirmation dialog (modal). Switching courses in the combo box updates the grade table and statistics.

**Grade Entry**- Add grade entries to the selected course. Calculate and display the percentage and letter grade automatically. Validate that an assignment name is provided and a course is selected.

**Grade Display**- Display grades in a QTableWidget with proper column headers. Allow selecting rows for deletion. Alternate row colors for readability.

**Statistics**- Calculate and display the course average (weighted by total possible points) in the progress bar. Calculate and display the overall GPA in the top label. Update both automatically when grades change.

**Data Persistence**- Use the File menu's Save/Load actions with QFileDialog to save and load all courses and grades as JSON.

**Part 3: Polish and Error Handling**

- Use QSS stylesheets to color-code letter grades in the table: A = green, B = blue, C = orange, D/F = red
- Disable the "Add Grade" toolbar action and button when no course is selected
- Show a modal "Are you sure?" dialog when removing a course that has grades
- Handle edge cases: empty course list, no grades entered, zero total points

**Letter Grade Scale**

| **Percentage** | **Letter** |
| -------------- | ---------- |
| 90-100%        | A          |
| 80-89%         | B          |
| 70-79%         | C          |
| 60-69%         | D          |
| Below 60%      | F          |