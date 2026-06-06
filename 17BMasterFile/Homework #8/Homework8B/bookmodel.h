// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW8B - Book Model Header File
// ================================================================
// Program Description:
// Custom Model implementation for Book data.
// Subclasses QAbstractTableModel to wrap a QVector of Book structs.
// Provides data for Display, Edit, CheckState, Font, and ToolTip roles.
// Editing via setData and flags.
// ================================================================
#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include <QAbstractTableModel>
#include <QVector>

// ================================================================
// Struct: Book
// Represents a single book entry in the system.
// Contains fields for title, author, ISBN, year, price, and stock status.
// ================================================================
struct Book {
    QString title;
    QString author;
    QString isbn;
    int year;
    double price;
    bool inStock;
};

// ================================================================
// Class: BookModel
// Custom table model that manages a collection of Book objects.
// Maps Book fields to table columns using an enumeration.
// ================================================================
class BookModel : public QAbstractTableModel {
    Q_OBJECT
public:
    // ================================================================
    // Enum: Column
    // Defines the index for each property of a Book in the table view.
    // ================================================================
    enum Column { Title = 0, Author, ISBN, Year, Price, InStock, ColumnCount };
    explicit BookModel(QObject *parent = nullptr);

    // ================================================================
    // Overridden methods from QAbstractTableModel
    // ================================================================
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    // ================================================================
    // addBook: Appends a new book to the model.
    // removeBook: Deletes a book at the specified row.
    // ================================================================
    void addBook(const Book &book);
    void removeBook(int row);

private:
    QVector<Book> m_books;
};

#endif // BOOKMODEL_H
