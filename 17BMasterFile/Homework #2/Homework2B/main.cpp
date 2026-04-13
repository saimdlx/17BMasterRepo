#include <iostream>
#include <vector>
using namespace std;

enum Category
{
    ELECTRONICS = 1,
    GROCERY = 2,
    CLOTHING = 3,
    OFFICE = 4
};

struct Product
{
    int productID;
    string productName;
    Category productCategory;
    double productPrice;
    int productQuantity;
};

typedef Product *ProductPtr;

void displayMenu();
ProductPtr createProduct();
void addProduct(vector<ProductPtr> &);
void displayProduct(const vector<ProductPtr> &);
string categoryToString(Category c);
void deleteAll(vector<ProductPtr> &);

int main()
{
    vector<ProductPtr> products;
    int input = 0;

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
            deleteAll(products);
            return 0;
        }
    }

    return 0;
}

void displayMenu()
{
    cout << "===== Inventory System =====" << '\n';
    cout << "1. Add Product" << '\n';
    cout << "2. Display Products" << '\n';
    cout << "3. Exit" << '\n';
    cout << "Enter choice: ";
}

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

    ProductPtr freshProd = new Product;
    freshProd->productID = inputID;
    freshProd->productName = inputName;
    freshProd->productCategory = inputCategory;
    freshProd->productPrice = inputPrice;
    freshProd->productQuantity = inputQuantity;

    return freshProd;
}

void addProduct(vector<ProductPtr> &products)
{
    cout << endl;
    ProductPtr nProd = createProduct();
    products.push_back(nProd);
    cout << "Product added successfully!" << "\n";
    cout << endl;
}

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

void deleteAll(vector<ProductPtr> &products)
{
    for (ProductPtr prod : products)
    {
        delete prod;
    }
    products.clear();
}
