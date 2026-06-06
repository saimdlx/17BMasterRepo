// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW8B - Book Inventory Main Window Class Implementation File
// ================================================================
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>

// ================================================================
// Constructor:
//   Initializes UI components and connects data models.
//   Initialize the custom BookModel and add sample data.
//   Create a Proxy Model to avoid slow performance / sort() rewrite
//   Configure the QTableView to use alternating colors and stretch headers.
//   Assemble the layout using Box Layouts (VBox for vertical, HBox for horizontal).
//   Establish signal-slot connections for interactive elements.
// ================================================================
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Basic window setup.
    setWindowTitle("Hw8B - Book Inventory Manager");
    resize(800, 600);

    // Create the data source.
    model = new BookModel(this);

    // Pre-populate with sample data and peak manga
    model->addBook({"Jojo's Bizarre Adventure", "Hirohiko Araki", "978-1421578798", 2015, 11.31, true});
    model->addBook({"Demon Slayer", "Koyoharu Gotouge", "978-1974700523", 2018, 6.71, true});
    model->addBook({"Naruto, Vol. 1: Uzumaki Naruto", "Masashi Kishimoto", "978-1569319000", 2003, 7.63, false});
    model->addBook({"The Great Gatsby", "F. Scott Fitzgerald", "978-0743273565", 1925, 15.00, true});
    model->addBook({"1984", "George Orwell", "978-0451524935", 1949, 12.50, true});
    model->addBook({"The Lord of the Rings", "J.R.R. Tolkien", "978-0544003415", 1954, 55.00, true});
    model->addBook({"Brave New World", "Aldous Huxley", "978-0060850524", 1932, 14.99, true});


    // Proxy talks to the source Model, view speaks to proxy,
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);

    // Configure the table.
    tableView = new QTableView(this);
    tableView->setModel(proxyModel); // Use proxy for sorting
    tableView->setAlternatingRowColors(true);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // Select whole lines.
    tableView->setSortingEnabled(true); // Allow clicking headers to sort.

    // Make columns fill the available space evenly.
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Create and arrange UI controls.
    addButton.setText("Add Book");
    removeButton.setText("Remove Book");

    // Horizontal layout for buttons at the bottom.
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(&addButton);
    buttonLayout->addWidget(&removeButton);

    // Main vertical layout containing the table and the button row.
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(tableView);
    mainLayout->addLayout(buttonLayout);

    // Create a central widget to hold the layout.
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Connect buttons to logic handlers.
    connect(&addButton, &QPushButton::clicked, this, &MainWindow::onAddBookClicked);
    connect(&removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveBookClicked);
}

MainWindow::~MainWindow() = default;

// ================================================================
// Function: onAddBookClicked
// Adds a template book entry to the model when clicked.
// ================================================================
void MainWindow::onAddBookClicked() {
    model->addBook({"New Book", "Author", "000-0000000000", 2024, 19.99, true});
}
// ================================================================
// Function: onRemoveBookClicked
//   Deletes the currently selected row(s).
//   The View returns indices from the ProxyModel.
//   mapToSource used to get the actual index in our BookModel.
//   Sort indices in descending order so that removing
//   the first item doesn't shift the indices of the subsequent items waiting for deletion
// ================================================================
void MainWindow::onRemoveBookClicked() {
    // Gather selected rows from the view.
    QModelIndexList selectedProxy = tableView->selectionModel()->selectedRows();

    // Trigger if no book selected
    if (selectedProxy.isEmpty()) {
        QMessageBox::warning(this, "Selection Required", "Please select a row to remove.");
        return;
    }

    // Map Proxy indices to Source Model indices.
    QList<int> sourceRows;
    for (const QModelIndex &proxyIndex : selectedProxy) {
        // Convert the sorted view index back to the storage index
        sourceRows.append(proxyModel->mapToSource(proxyIndex).row());
    }

    // Sort indices in descending order.
    std::sort(sourceRows.begin(), sourceRows.end(), std::greater<int>());

    // Remove from source model.
    for (int row : sourceRows) {
        model->removeBook(row);
    }
}
