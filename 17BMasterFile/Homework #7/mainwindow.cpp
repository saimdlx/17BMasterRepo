/*
// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW7 - Personal Contact Book Implementation
// ================================================================
// Program Description:
// Implements the main window logic for the Contact Book.
// Handles UI construction, contact validation, filtering,
// and file I/O operations for JSON data.
// ================================================================

#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QCloseEvent>
#include <QRegularExpression>
#include <QStyle>
#include <QLabel>

// ================================================================
// Constructor: MainWindow
// - Initializes member variables and orchestrates UI setup.
// - Loads existing contact data from storage on startup.
// ================================================================
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), isModified(false), currentContactIndex(-1) {
    setupUI();         // Initialize the user interface components
    createActions();   // Define the logic for menu and toolbar actions
    createMenus();     // Construct the application menu bar
    createToolBars();  // Add the interactive toolbar to the window
    loadContacts();    // Restore contact data from the JSON file
    statusBar()->showMessage("HW7 - Contact Book Loaded", 3000);
}

// Default Destructor
MainWindow::~MainWindow() = default;

// ================================================================
// Function: setupUI
// - Constructs the main layout using layouts and widgets.
// - Sets up the left search/list panel and right entry form.
// - Establishes signal-slot connections for widget interactions.
// ================================================================
void MainWindow::setupUI() {

    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto *mainLayout = new QHBoxLayout(centralWidget);

    // ================================================================
    // Left Panel Construction:
    // - Search bar and contact name list.
    // ================================================================
    auto *leftPanel = new QWidget();
    auto *leftLayout = new QVBoxLayout(leftPanel);
    
    searchField = new QLineEdit();
    searchField->setPlaceholderText("Search contacts...");
    leftLayout->addWidget(new QLabel("Search:"));
    leftLayout->addWidget(searchField);

    contactListWidget = new QListWidget();
    leftLayout->addWidget(contactListWidget);
    mainLayout->addWidget(leftPanel, 1);

    // ================================================================
    // Right Panel Construction:
    // - Detailed contact form for viewing and editing.
    // ================================================================
    auto *rightPanel = new QWidget();
    auto *rightLayout = new QVBoxLayout(rightPanel);
    auto *formLayout = new QFormLayout();

    firstNameField = new QLineEdit();
    lastNameField = new QLineEdit();
    emailField = new QLineEdit();
    phoneField = new QLineEdit();
    categoryBox = new QComboBox();
    categoryBox->addItems({"Friend", "Family", "Work", "Other"});
    notesField = new QTextEdit();

    // Map labels to input fields within the form layout
    formLayout->addRow("First Name:", firstNameField);
    formLayout->addRow("Last Name:", lastNameField);
    formLayout->addRow("Email:", emailField);
    formLayout->addRow("Phone:", phoneField);
    formLayout->addRow("Category:", categoryBox);
    formLayout->addRow("Notes:", notesField);

    rightLayout->addLayout(formLayout);

    // Layout for save and clear buttons
    auto *btnLayout = new QHBoxLayout();
    saveBtn = new QPushButton("Save");
    clearBtn = new QPushButton("Clear");
    btnLayout->addWidget(saveBtn);
    btnLayout->addWidget(clearBtn);
    rightLayout->addLayout(btnLayout);

    mainLayout->addWidget(rightPanel, 2);

    // Connect interactive widgets to their respective slot functions
    connect(saveBtn, &QPushButton::clicked, this, &MainWindow::onSaveContact);
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::onClearForm);
    connect(contactListWidget, &QListWidget::itemClicked, this, &MainWindow::onContactSelected);
    connect(searchField, &QLineEdit::textChanged, this, &MainWindow::onSearchChanged);

}

// ================================================================
// Function: createActions
// - Defines shared QAction objects for use in menus and toolbars.
// - Assigns icons and keyboard shortcuts.
// ================================================================
void MainWindow::createActions() {

    // Configure the New Contact action with a system icon
    newContactAction = new QAction(style()->standardIcon(QStyle::SP_FileIcon), "&New Contact", this);
    connect(newContactAction, &QAction::triggered, this, &MainWindow::onNewContact);

    // Configure the Save All action for data persistence
    saveAllAction = new QAction(style()->standardIcon(QStyle::SP_DialogSaveButton), "&Save All", this);
    connect(saveAllAction, &QAction::triggered, this, &MainWindow::onSaveAll);

    // Configure the Exit action to close the application
    exitAction = new QAction("&Exit", this);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    // Configure the Delete Contact action with a trash icon
    deleteContactAction = new QAction(style()->standardIcon(QStyle::SP_TrashIcon), "&Delete Contact", this);
    connect(deleteContactAction, &QAction::triggered, this, &MainWindow::onDeleteContact);

    // Configure the About action for program information
    aboutAction = new QAction("&About", this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAbout);

}

// ================================================================
// Function: createMenus
// - Populates the main menu bar with File, Edit, and Help menus.
// ================================================================
void MainWindow::createMenus() {

    // Populate the File menu with relevant actions and separators
    auto *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(newContactAction);
    fileMenu->addAction(saveAllAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // Populate the Edit menu for contact manipulation
    auto *editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(deleteContactAction);

    // Populate the Help menu for application metadata
    auto *helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAction);

}

// ================================================================
// Function: createToolBars
// - Adds interactive toolbar buttons for common tasks.
// ================================================================
void MainWindow::createToolBars() {

    auto *toolBar = addToolBar("Main Toolbar");
    toolBar->addAction(newContactAction);
    toolBar->addAction(saveAllAction);
    toolBar->addAction(deleteContactAction);

}

// ================================================================
// Slot: onNewContact
// - Prepares the form for a new contact entry by clearing fields.
// ================================================================
void MainWindow::onNewContact() {

    onClearForm();              // Reset the input fields
    firstNameField->setFocus(); // Place cursor in the first input field
    statusBar()->showMessage("New contact form ready", 2000);

}

// ================================================================
// Slot: onSaveContact
// - Validates form input and creates/updates a contact record.
// - Refreshes the display list and marks data as modified.
// ================================================================
void MainWindow::onSaveContact() {

    // Abort if the input data fails validation checks
    if (!validateInput()) return;

    Contact c;

    // Collect and trim data from form fields
    c.firstName = firstNameField->text().trimmed();
    c.lastName = lastNameField->text().trimmed();
    c.email = emailField->text().trimmed();
    c.phone = phoneField->text().trimmed();
    c.category = categoryBox->currentText();
    c.notes = notesField->toPlainText();

    // Decide between creating a new record or updating an existing one
    if (currentContactIndex == -1) {
        contacts.append(c);
        statusBar()->showMessage("New contact added", 2000);
    } else {
        contacts[currentContactIndex] = c;
        statusBar()->showMessage("Contact updated", 2000);
    }

    isModified = true;      // Flag that the data has unsaved changes
    updateListWidget();     // Refresh the visual list of contacts
    onClearForm();          // Reset the form for the next operation

}

// ================================================================
// Slot: onDeleteContact
// - Prompts for confirmation before removing a contact.
// - Removes the selected record from the data store and list view.
// ================================================================
void MainWindow::onDeleteContact() {

    int row = contactListWidget->currentRow();
    // Ensure a valid item is selected before attempting deletion
    if (row < 0) {
        QMessageBox::warning(this, "Warning", "Please select a contact to delete.");
        return;
    }

    // Confirm deletion with the user to prevent accidental data loss
    auto reply = QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this contact?", QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // Find the actual contact in the list
        QString email = contactListWidget->item(row)->data(Qt::UserRole).toString();
        for (int i = 0; i < contacts.size(); ++i) {
            if (contacts[i].email == email) {
                contacts.removeAt(i);
                break;
            }
        }
        isModified = true;      // Mark as modified after deletion
        updateListWidget();     // Refresh the list view
        onClearForm();          // Clear the form
        statusBar()->showMessage("Contact deleted", 2000);
    }
}

// ================================================================
// Slot: onSaveAll
// - Opens a file dialog to save the entire contact list as JSON.
// ================================================================
void MainWindow::onSaveAll() {

    // Prompt user to select a destination file path
    QString fileName = QFileDialog::getSaveFileName(this, "Save Contacts", "", "JSON Files (*.json)");
    
    // Proceed if a valid file path was provided
    if (!fileName.isEmpty()) {
        if (saveToFile(fileName)) {
            isModified = false; // Reset modification flag on successful save
            statusBar()->showMessage("All contacts saved to " + fileName, 3000);
        }
    }


}

// ================================================================
// Slot: onClearForm
// - Resets all form fields and selection state.
// ================================================================
void MainWindow::onClearForm() {

    firstNameField->clear();
    lastNameField->clear();
    emailField->clear();
    phoneField->clear();
    categoryBox->setCurrentIndex(0);
    notesField->clear();
    
    // Reset state to indicate no contact is being edited
    currentContactIndex = -1;
    contactListWidget->clearSelection();

}

// ================================================================
// Slot: onContactSelected
// - Populates the form with details of the selected contact.
// ================================================================
void MainWindow::onContactSelected(QListWidgetItem *item) {

    if (!item) return;
    
    // Retrieve the identifier stored in the list item
    QString email = item->data(Qt::UserRole).toString();
    
    // Locate the contact in the internal list and map its data to the UI
    for (int i = 0; i < contacts.size(); ++i) {
        if (contacts[i].email == email) {
            currentContactIndex = i;
            firstNameField->setText(contacts[i].firstName);
            lastNameField->setText(contacts[i].lastName);
            emailField->setText(contacts[i].email);
            phoneField->setText(contacts[i].phone);
            categoryBox->setCurrentText(contacts[i].category);
            notesField->setText(contacts[i].notes);
            break;
        }
    }

}

// ================================================================
// Slot: onSearchChanged
// - Triggered when the search box text changes to filter the list.
// ================================================================
void MainWindow::onSearchChanged(const QString &text) {

    Q_UNUSED(text);
    updateListWidget(); // Trigger a list redraw based on new filter text

}

// ================================================================
// Slot: onAbout
// - Displays application information in a dialog.
// ================================================================
void MainWindow::onAbout() {

    QMessageBox::about(this, "About Contact Book", "Personal Contact Book for Homework Assignment 7 developed by Saim Ahmed");

}

// ================================================================
// Function: validateInput
// - Ensures all contact fields meet required criteria.
// - Returns true if valid, else shows an error message and returns false.
// ================================================================
bool MainWindow::validateInput() {

    QString firstName = firstNameField->text().trimmed();
    QString lastName = lastNameField->text().trimmed();
    QString email = emailField->text().trimmed();
    QString phone = phoneField->text().trimmed();

    // Names must only contain alphabetical characters and spaces
    QRegularExpression nameRegex("^[A-Za-z ]+$");
    if (firstName.isEmpty() || !nameRegex.match(firstName).hasMatch()) {
        QMessageBox::critical(this, "Validation Error", "First Name must not be empty and contain only letters/spaces.");
        return false;
    }
    if (lastName.isEmpty() || !nameRegex.match(lastName).hasMatch()) {
        QMessageBox::critical(this, "Validation Error", "Last Name must not be empty and contain only letters/spaces.");
        return false;
    }

    // Emails must follow a standard pattern (something@something.domain)
    QRegularExpression emailRegex("^[^@\\s]+@[^@\\s]+\\.[^@\\s]+$");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::critical(this, "Validation Error", "Email must match pattern: something@something.something");
        return false;
    }

    // Phone numbers must be composed of specific allowed characters
    QRegularExpression phoneRegex("^[\\d\\s\\-\\(\\)]+$");
    if (!phoneRegex.match(phone).hasMatch()) {
        QMessageBox::critical(this, "Validation Error", "Phone must contain only digits, spaces, dashes, and parentheses.");
        return false;
    }

    return true;
}

// ================================================================
// Function: updateListWidget
// - Filters and redraws the contact list widget based on search criteria.
// ================================================================
void MainWindow::updateListWidget() {
    contactListWidget->clear();
    QString filter = searchField->text().toLower();

    // Iterate through all contacts and add those that match the search filter
    for (const auto &c : contacts) {
        if (filter.isEmpty() || 
            c.firstName.toLower().contains(filter) || 
            c.lastName.toLower().contains(filter) || 
            c.email.toLower().contains(filter)) {
            
            auto *item = new QListWidgetItem(c.firstName + " " + c.lastName);
            item->setData(Qt::UserRole, c.email); // Store email for reverse lookup
            contactListWidget->addItem(item);
        }
    }
    statusBar()->showMessage(QString("%1 contacts listed").arg(contactListWidget->count()), 2000);
}

// ================================================================
// Function: loadContacts
// - Loads contact records from the default 'contacts.json' file.
// ================================================================
void MainWindow::loadContacts() {
    QFile file("contacts.json");
    
    // Attempt to open the data file for reading
    if (file.open(QIODevice::ReadOnly)) {
        // Parse the raw JSON data into a document array
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonArray arr = doc.array();
        contacts.clear();
        
        // Deserialize each JSON object back into a Contact struct
        for (const auto &val : arr) {
            contacts.append(Contact::fromJson(val.toObject()));
        }
        updateListWidget(); // Populate the UI list with loaded data
    }
}

// ================================================================
// Function: saveToFile
// - Writes the current in-memory contact list to a JSON file.
// ================================================================
bool MainWindow::saveToFile(const QString &fileName) {

    QFile file(fileName);
    
    // Attempt to open the specified file for writing
    if (file.open(QIODevice::ReadOnly)) {
        QJsonArray arr;
        // Serialize each contact into the JSON array
        for (const auto &c : contacts) {
            arr.append(c.toJson());
        }
        
        // Write the formatted JSON document to files
        QJsonDocument doc(arr);
        file.write(doc.toJson());
        return true;
    }
    
    QMessageBox::critical(this, "Error", "Could not save file.");
    return false;

}

// ================================================================
// Function: closeEvent
// - Intercepts window close request to prompt for unsaved changes.
// ================================================================
void MainWindow::closeEvent(QCloseEvent *event) {

    // If changes are pending, ask user for confirmation before closing
    if (isModified) {
        auto reply = QMessageBox::question(this, "Unsaved Changes", "You have unsaved changes. Save before closing?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        
        if (reply == QMessageBox::Save) {
            onSaveAll();    // Save changes then allow closure
            event->accept();
        } else if (reply == QMessageBox::Discard) {
            event->accept(); // Lose changes and allow closure
        } else {
            event->ignore();  // Cancel the close operation
        }
    } else {
        event->accept(); // Close regardless
    }

}
*/
