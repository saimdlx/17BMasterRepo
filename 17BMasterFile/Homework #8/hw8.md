# \*\*HW #8

(Qt Model/View Architecture)\*\*

**Homework Assignment 1: Student Roster Application**

**Due Date: 6/12/2026**

**Submission: Submit (upload in Canvas) all .h and .cpp files in PDF.**

**Objective**

Build a Student Roster application that uses Qt's Model/View architecture. You will practice using QStandardItemModel, connecting it to multiple views, and working with data roles.

**Requirements**

**Part A: Basic Model Setup**

- Create a QStandardItemModel with the following columns: Student ID, First Name, Last Name, Major, GPA (5 columns total).
- Populate the model with at least 8 students with realistic sample data.
- Set appropriate column headers using setHorizontalHeaderLabels().

**Part B: Multiple Views**

- Display the model in a QTableView as the main view.
- Display the same model in a QListView showing only the first column (student names). Hint: use QListView::setModelColumn(1) to show the First Name column.
- Both views must be visible at the same time, side by side, in a QHBoxLayout.
- Verify that editing a student's name in one view updates the other view automatically.

**Part C: Data Roles and Formatting**

- Set the BackgroundRole for any student with a GPA below 2.0 to light red (QColor(255, 200, 200)).
- Set the BackgroundRole for any student with a GPA of 3.5 or above to light green (QColor(200, 255, 200)).
- Set the FontRole to bold for students on the Dean's List (GPA >= 3.7).
- Add a tooltip (ToolTipRole) to each student that shows their full information.

**Part D: Interactive Features**

- Add an "Add Student" button that inserts a new row with default values.
- Add a "Remove Student" button that removes the currently selected student.
- Enable sorting by clicking column headers (setSortingEnabled(true)).
- Enable alternating row colors for better readability.

**Hints**

- Use model->item(row, col)->setData(value, role) to set roles on existing items.
- GPA should be stored as a string in DisplayRole but compared as a double for color logic.
- To apply formatting after data is loaded, loop through all rows with a for loop.

**Homework Assignment 2: Custom Book Inventory Model**

**Due Date: 6/12/2026**

**Submission: Submit (upload in Canvas) all .h and .cpp files in PDF.**

**Objective**

Create a complete custom model by subclassing QAbstractTableModel. This homework requires you to write a model from scratch that wraps a QVector of Book structs, supports editing, and uses begin/end insert/remove row methods.

**Requirements**

**Part A: Data Structure**

Define a Book struct with the following fields: title (QString), author (QString), isbn (QString), year (int), price (double), inStock (bool).

**Part B: Custom Model Class**

- Create a BookModel class that inherits from QAbstractTableModel.
- Implement all required methods: rowCount(), columnCount(), data(), headerData(), flags().
- Support Qt::DisplayRole, Qt::EditRole, and Qt::CheckStateRole (for the inStock column-display a checkbox).
- Use an enum for column indices (similar to the ContactModel example).
- Implement setData() to allow editing of all fields.
- Implement addBook() and removeBook() methods using beginInsertRows/endInsertRows and beginRemoveRows/endRemoveRows.

**Part C: Main Window**

- Display the BookModel in a QTableView with alternating row colors and row selection.
- Add "Add Book" and "Remove Book" buttons.
- Pre-populate the model with at least 6 books.
- Enable column sorting.

**Part D: Extra Formatting**

- Display the Price column right-aligned with a dollar sign (e.g., "\$29.99") using the data() method.
- Display books priced above \$50 with a bold font (FontRole).
- Set a ToolTipRole for each book that shows: "Title by Author (Year) - ISBN: xxx".
- Display the Year column center-aligned using TextAlignmentRole.

**Starter Code**

Use this skeleton to get started with the BookModel header:

// bookmodel.h - Starter skeleton

# ifndef BOOKMODEL_H

# define BOOKMODEL_H

# include &lt;QAbstractTableModel&gt;

# include &lt;QVector&gt;

struct Book {

QString title;

QString author;

QString isbn;

int year;

double price;

bool inStock;

};

class BookModel : public QAbstractTableModel

{

Q_OBJECT

public:

enum Column { Title = 0, Author, ISBN, Year, Price, InStock, ColumnCount };

explicit BookModel(QObject \*parent = nullptr);

// TODO: Implement these required methods

int rowCount(const QModelIndex &parent = QModelIndex()) const override;

int columnCount(const QModelIndex &parent = QModelIndex()) const override;

QVariant data(const QModelIndex &index, int role) const override;

QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

Qt::ItemFlags flags(const QModelIndex &index) const override;

bool setData(const QModelIndex &index, const QVariant &value, int role) override;

void addBook(const Book &book);

void removeBook(int row);

private:

QVector&lt;Book&gt; m_books;

};

# endif