/*
// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW7 - Personal Contact Book Header File
// ================================================================
// Program Description:
// Declares contacts data structure and the MainWindow class.
// Includes UI component declarations, event handler slots,
// and private utility methods for the contact book application.
// ================================================================
#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QAction>
#include <QList>
#include <QJsonObject>

// ================================================================
// Struct: Contact
// - Represents a single personal contact record.
// - Provides serialization methods to/from QJsonObject for 
//   JSON file persistence.
// ================================================================
struct Contact {
    QString firstName;
    QString lastName;
    QString email;
    QString phone;
    QString category;
    QString notes;

    // Convert contact object to JSON representation
    QJsonObject toJson() const {
        QJsonObject obj;
        obj["firstName"] = firstName;
        obj["lastName"] = lastName;
        obj["email"] = email;
        obj["phone"] = phone;
        obj["category"] = category;
        obj["notes"] = notes;
        return obj;
    }

    // Create contact object from JSON data
    static Contact fromJson(const QJsonObject &obj) {
        Contact c;
        c.firstName = obj["firstName"].toString();
        c.lastName = obj["lastName"].toString();
        c.email = obj["email"].toString();
        c.phone = obj["phone"].toString();
        c.category = obj["category"].toString();
        c.notes = obj["notes"].toString();
        return c;
    }
};

// ================================================================
// Class: MainWindow
// - Provide the main application UI.
// - Manages the collection of Contact objects and coordinates
//   between UI events and data persistence.
// ================================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    // Overridden close event to prompt for unsaved changes
    void closeEvent(QCloseEvent *event) override;

private slots:
    // ================================================================
    // Event Handler Slots:
    // - Handles user interactions with menus, buttons, and lists.
    // ================================================================
    void onNewContact();
    void onSaveContact();
    void onDeleteContact();
    void onSaveAll();
    void onClearForm();
    void onContactSelected(QListWidgetItem *item);
    void onSearchChanged(const QString &text);
    void onAbout();

private:
    // ================================================================
    // Private Utility Methods:
    // - Encapsulates UI construction.
    // ================================================================
    void setupUI();
    void createActions();
    void createMenus();
    void createToolBars();
    void loadContacts();
    bool saveToFile(const QString &fileName);
    bool validateInput();
    void updateListWidget();
    void clearInputs();

    // UI Components
    QListWidget *contactListWidget;
    QLineEdit *searchField;
    QLineEdit *firstNameField;
    QLineEdit *lastNameField;
    QLineEdit *emailField;
    QLineEdit *phoneField;
    QComboBox *categoryBox;
    QTextEdit *notesField;
    QPushButton *saveBtn;
    QPushButton *clearBtn;

    // Actions
    QAction *newContactAction;
    QAction *saveAllAction;
    QAction *exitAction;
    QAction *deleteContactAction;
    QAction *aboutAction;

    // Data Management
    QList<Contact> contacts;      // In-memory storage for contacts
    bool isModified;              // Tracking unsaved changes to save or manipulate (.json)
    int currentContactIndex;
};

#endif
*/