// ================================================================
// Programmer: Saim Ahmed
// Class: CIS-17B
// Instructor: Med Mogasemi
// ================================================================
// Program:  Inventory Management System
// ================================================================
// Program Description:
// Inventory Management System
// - Demonstrates usage of structs, enums, and dynamic memory.
// - Allows users to add products to an inventory and display them.
// - Uses a vector of pointers to manage dynamically allocated products.
// ================================================================
#include <iostream>
#include <vector>
using namespace std;

// ================================================================
// Enum: Category
// - Defines the various categories for products:
// - ELECTRONICS (1): Electronic items
// - GROCERY (2): Food and household items
// - CLOTHING (3): Apparel and clothing
// - OFFICE (4): Office supplies and furniture
// ================================================================
enum Category
{
    ELECTRONICS = 1,
    GROCERY = 2,
    CLOTHING = 3,
    OFFICE = 4
};

// ================================================================
// Struct: Product
// - Represents a product in the inventory with the following:
// - productID: Unique identifier for the product.
// - productName: Name of the product.
// - productCategory: The category the product belongs to (Enum).
// - productPrice: Unit price of the product.
// - productQuantity: Number of items available in stock.
// ================================================================
struct Product
{
    int productID = 0;
    string productName = "";
    Category productCategory;
    double productPrice = 0.0;
    int productQuantity = 0;
};

// ================================================================
// Typedef: ProductPtr
// - Defines a pointer type for the Product struct.
// - Facilitates cleaner syntax when working with dynamic allocation.
// ================================================================
typedef Product *ProductPtr;

// ================================================================
// Function Prototypes:
// - displayMenu(): Displays the user interface options.
// - createProduct(): Handles user input to create a new Product.
// - addProduct(vector<ProductPtr> &): Adds a product to the list.
// - displayProduct(const vector<ProductPtr> &): Shows all products.
// - categoryToString(Category): Converts enum to human-readable string.
// - deleteAll(vector<ProductPtr> &): Cleans up dynamic memory.
// ================================================================
void displayMenu();
ProductPtr createProduct();
void addProduct(vector<ProductPtr> &);
void displayProduct(const vector<ProductPtr> &);
string categoryToString(Category c);
void deleteAll(vector<ProductPtr> &);

// ================================================================
// Main Function:
// - Orchestrates the inventory system lifecycle.
// - Manages the primary control loop and menu selection.
// - Ensures proper memory cleanup upon exit.
// ================================================================
int main()
{
    // ================================================================
    // Data Structures:
    // - products: Vector storing pointers to all inventory items.
    // - input: Stores the user's menu choice.
    // ================================================================
    vector<ProductPtr> products;
    int input = 0;

    // ================================================================
    // Main Control Loop:
    // - Continues to prompt the user until "Exit" is chosen.
    // - Routes actions to specific functions based on input.
    // ================================================================
    while (input < 3)
    {
        displayMenu();
        cin >> input;

        switch (input)
        {
        case 1:
            addProduct(products);
            break;
        case 2:
            displayProduct(products);
            break;
        case 3:
            cout << "Goodbye!" << endl;
            deleteAll(products); // Free memory before closing
            return 0;
        }
    }

    return 0;
}

// ================================================================
// Function: displayMenu
// - Outputs the main menu selection to the console.
// ================================================================
void displayMenu()
{
    cout << "===== Inventory System =====" << '\n';
    cout << "1. Add Product" << '\n';
    cout << "2. Display Products" << '\n';
    cout << "3. Exit" << '\n';
    cout << "Enter choice: ";
}

// ================================================================
// Function: createProduct
// - Collects item details from the user.
// - Dynamically allocates a new Product struct on the heap.
// - Returns: ProductPtr to the newly created product.
// ================================================================
ProductPtr createProduct()
{
    int inputID = 0;
    string inputName = "";
    int categoryMarker = 0;
    Category inputCategory;
    double inputPrice = 0;
    int inputQuantity = 0;

    cout << "Enter Product ID: ";
    cin >> inputID;
    cout << "Enter Product Name: ";
    cin >> inputName;
    cout << "Select Category (1-4): " << '\n';
    cout << "1. ELECTRONICS" << '\n';
    cout << "2. GROCERY" << '\n';
    cout << "3. CLOTHING" << '\n';
    cout << "4. OFFICE" << '\n';
    cout << "Enter choice: ";
    cin >> categoryMarker;
    inputCategory = static_cast<Category>(categoryMarker);
    cout << "Enter Price: ";
    cin >> inputPrice;
    cout << "Enter Quantity: ";
    cin >> inputQuantity;

    // Dynamic Allocation
    ProductPtr cProd = new Product;
    cProd->productID = inputID;
    cProd->productName = inputName;
    cProd->productCategory = inputCategory;
    cProd->productPrice = inputPrice;
    cProd->productQuantity = inputQuantity;

    return cProd;
}

// ================================================================
// Function: addProduct
// - Calls createProduct to get a new item.
// - Pushes the returned pointer into the tracking vector.
// - Parameters:
//   - products (vector<ProductPtr> &): Reference to the product list.
// ================================================================
void addProduct(vector<ProductPtr> &products)
{
    cout << endl;
    ProductPtr nProd = createProduct();
    products.push_back(nProd);
    cout << "Product added successfully!" << "\n";
    cout << endl;
}

// ================================================================
// Function: displayProduct
// - Iterates through the vector and prints details of each product.
// - Uses categoryToString to display the enum value as text.
// - Parameters:
//   - products (const vector<ProductPtr> &): The product list to show.
// ================================================================
void displayProduct(const vector<ProductPtr> &products)
{
    for (int i = 0; i < products.size(); i++)
    {
        cout << endl;
        cout << "Product ID: " << products[i]->productID << '\n';
        cout << "Product Name: " << products[i]->productName << '\n';
        cout << "Product Category: " << categoryToString(products[i]->productCategory) << '\n';
        cout << "Product Price: " << products[i]->productPrice << '\n';
        cout << "Product Quantity: " << products[i]->productQuantity << '\n';
        cout << endl;
    }
}

// ================================================================
// Function: categoryToString
// - Maps Category enum values to their string representations.
// - Parameters:
//   - c (Category): The category enum to convert.
// - Returns: string label of the category.
// ================================================================
string categoryToString(Category c)
{
    string result;
    switch (c)
    {
    case ELECTRONICS:
        result = "Electronics";
        break;
    case GROCERY:
        result = "Grocery";
        break;
    case CLOTHING:
        result = "Clothing";
        break;
    case OFFICE:
        result = "Office";
        break;
    }
    return result;
}

// ================================================================
// Function: deleteAll
// - Iterates through the vector to delete dynamically allocated memory.
// - Clears the vector to prevent dangling pointers.
// - Parameters:
//   - products (vector<ProductPtr> &): The list to be cleaned.
// ================================================================
void deleteAll(vector<ProductPtr> &products)
{
    for (ProductPtr prod : products)
    {
        delete prod;
    }
    products.clear();
}
/* Program Output Using Assignment Input
===== Inventory System =====
1. Add Product
2. Display Products
3. Exit
Enter choice: 1

Enter Product ID: 500
Enter Product Name: Laptop
Select Category (1-4):
1. ELECTRONICS
2. GROCERY
3. CLOTHING
4. OFFICE
Enter choice: 1
Enter Price: 899.99
Enter Quantity: 10
Product added successfully!

===== Inventory System =====
1. Add Product
2. Display Products
3. Exit
Enter choice: 2

Product ID: 500
Product Name: Laptop
Product Category: Electronics
Product Price: 899.99
Product Quantity: 10

===== Inventory System =====
1. Add Product
2. Display Products
3. Exit
Enter choice: 3
Goodbye!
*/