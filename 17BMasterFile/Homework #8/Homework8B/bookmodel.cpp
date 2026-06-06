// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW8B - Book Model Class Implementation
// ================================================================
#include "bookmodel.h"
#include <QFont>

// ================================================================
// Constructor:
// Initializes the base QAbstractTableModel.
// ================================================================
BookModel::BookModel(QObject *parent) : QAbstractTableModel(parent) {}

// ================================================================
// Function: rowCount
// Returns the number of items in the internal book vector.
// ================================================================
int BookModel::rowCount(const QModelIndex &parent) const {
    // return the number of books.
    return m_books.size();
}

// ================================================================
// Function: columnCount
// Uses the ColumnCount member of the enum to define the
// width of the table.
// ================================================================
int BookModel::columnCount(const QModelIndex &parent) const {
    // returns the total number of columns defined in the emunerator.
    return ColumnCount;
}

// ================================================================
// Function: data
//   Check if the index is within valid bounds for our vector.
//   Retrieve the Book object at the specified row.
//   Handle multiple roles which define different aspects of the cell.
// ================================================================
QVariant BookModel::data(const QModelIndex &index, int role) const {
    // Access the book in our vector for the current row.
    const Book &book = m_books[index.row()];

    // DisplayRole and EditRole:
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case Title:  return book.title;
            case Author: return book.author;
            case ISBN:   return book.isbn;
            case Year:   return book.year;
            case Price:
                // For display, add a '$' and fix to 2 decimal places.
                // For editing, return the raw double value so the editor works correctly.
                if (role == Qt::DisplayRole) return QString("$%1").arg(book.price, 0, 'f', 2);
                return book.price;
            case InStock:
                // Return an empty variant for DisplayRole because the checkbox (CheckStateRole) will handle the visual state in this column.
                if (role == Qt::DisplayRole) return QVariant();
                return book.inStock;
        }
    }

    // CheckState Role:
    // Specifically for the 'In Stock' column, this renders a checkbox.
    if (role == Qt::CheckStateRole && index.column() == InStock) {
        // Map boolean to Qt's states.
        return book.inStock ? Qt::Checked : Qt::Unchecked;
    }

    // TextAlignment Role:
    if (role == Qt::TextAlignmentRole) {
        // Years are centered
        if (index.column() == Year) return Qt::AlignCenter;

        // Prices are right-aligned to keep decimal points in line
        if (index.column() == Price) return Qt::AlignRight;
    }

    // Font Role:
    if (role == Qt::FontRole && book.price > 50.0) {
        QFont font;
        font.setBold(true);
        return font;
    }

    // ToolTip Role:
    // Returns a string that appears when the user hovers over cell.
    if (role == Qt::ToolTipRole) {
        return QString("%1 by %2 (%3) - ISBN: %4")
            .arg(book.title, book.author).arg(book.year).arg(book.isbn);
    }

    // Defaults if roles aren't handled
    return QVariant();
}

// ================================================================
// Function: headerData
// Provides the labels for the horizontal headers of the table.
// ================================================================
QVariant BookModel::headerData(int section, Qt::Orientation orientation, int role) const {
    // Map column indices.
    switch (section) {
        case Title:   return tr("Title");
        case Author:  return tr("Author");
        case ISBN:    return tr("ISBN");
        case Year:    return tr("Year");
        case Price:   return tr("Price");
        case InStock: return tr("In Stock");
        default:      return QVariant();
    }
}

// ================================================================
// Function: flags
// Tells the view which cells are selectable, enabled, or editable.
// ================================================================
Qt::ItemFlags BookModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::NoItemFlags;

    // Default flags for all cells: enabled, selectable, and editable via text.
    Qt::ItemFlags f = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;

    // Special flag for columns containing a checkbox.
    if (index.column() == InStock) {
        f.setFlag(Qt::ItemIsUserCheckable);
    }

    return f;
}

// ================================================================
// Function: setData
// Updates the internal data structure when a user finishes editing.
// Identify which role and column is being updated.
// Update the Book field in the vector.
// Invoke dataChanged() to force the view to repaint the updated cell.
// ================================================================
bool BookModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || index.row() >= m_books.size()) return false;

    // Get a mutable reference to the book being edited.
    Book &book = m_books[index.row()];

    // Handle standard edits
    if (role == Qt::EditRole) {
        switch (index.column()) {
            case Title:   book.title = value.toString();   break;
            case Author:  book.author = value.toString();  break;
            case ISBN:    book.isbn = value.toString();    break;
            case Year:    book.year = value.toInt();       break;
            case Price:   book.price = value.toDouble();   break;
            case InStock: book.inStock = value.toBool();   break;
        }
    }
    // Handle Checkbox state changes.
    else if (role == Qt::CheckStateRole && index.column() == InStock) {
        book.inStock = (value.toInt() == Qt::Checked);
    }
    return false;
}

// ================================================================
// Function: addBook
// Appends a new book to the end of the list.
// Call beginInsertRows before modifying the container, and
// endInsertRows after. Program is slow without it
// ================================================================
void BookModel::addBook(const Book &book) {
    // Notify the framework that we are adding 1 row at the end of the current list.
    beginInsertRows(QModelIndex(), m_books.size(), m_books.size());

    // Add the actual data.
    m_books.append(book);

    // Finish the insertion transaction.
    endInsertRows();
}

// ================================================================
// Function: removeBook
// Logic: Deletes a specific row from the list.
// Like insertion, this must be wrapped in begin/end signals.
// ================================================================
void BookModel::removeBook(int row) {
    // Range check to avoid crashes.
    if (row < 0 || row >= m_books.size()) return;

    // Notify the framework that the specified row is about to be removed.
    beginRemoveRows(QModelIndex(), row, row);

    // Remove the data from the vector.
    m_books.removeAt(row);

    // Finish the removal transaction.
    endRemoveRows();
}
