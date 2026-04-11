#include <iostream>
using namespace std;

enum Category{
    ELECTRONICS = 1,
    GROCERY = 2,
    CLOTHING = 3,
    OFFICE = 4
};

struct Product{
    int productID;
    string productName;
    Category productCategory;
    double productPrice;
    int productQuantity;
};

typedef Product *ProductPtr;

void displayMenu();
ProductPtr createProduct();
void addProduct(vector<ProductPtr>&);
void displayProduct(const vector<ProductPtr>&);
void deleteAll(vector<ProductPtr>&);


//Program Execution Begins Here
int main() {
    
    return 0;
}

void displayMenu(){

    cout << "===== Inventory System =====" << '\n';
    cout << "1. Add Product" << '\n';
    cout << "2. Display Products" << '\n';
    cout << "3. Exit" << '\n';
    cout << "Enter choice: ";

}

ProductPtr createProduct(){
   
    int inputID = 0;
    string inputName = "";
    int categoryMarker = 0;
    Category c;
    double inputPrice = 0;
    int inputQuantity = 0;

    cout << "Enter Product ID: ";
    cin >> inputID;

    cout << "Enter Product Name: ";
    cin >> inputName;

    cout << "Enter Category (1-4): ";
    cin >> categoryMarker;
    c = static_cast<Category>(categoryMarker);
    
    cout << "Enter Price: ";
    cin >> inputPrice;

    cout << "Enter Quantity: ";
    cin >> inputQuantity;


    ProductPtr freshProd = new Product;
    freshProd->productID = inputID;
    freshProd->productName = inputName;
    freshProd->productCategory = c;
    freshProd->productPrice = inputPrice;
    freshProd->productQuantity = inputQuantity;
    
    return freshProd;
}

void addProduct(vector<ProductPtr>& products){
    cout << endl;
    ProductPtr p = createProduct();
    products.push_back(p);
    cout << "Product added successfully!" << "\n";
    cout << endl;
}

void displayProduct(const vector<ProductPtr>& products){

    for (int i = 0 ; i < products.size(); i++){
        
    }



}