#include <bits/stdc++.h>
using namespace std;

class Product
{
public:
    string name;
    string category;
    double price;

    Product(string name, string category, double price)
        : name(name), category(category), price(price) {}
};

class User
{
public:
    string username;
    string password;

    User(string username, string password)
        : username(username), password(password) {}
};

class Order
{
public:
    string username;
    string password;
    vector<Product> products;

    double calculateTotal() const
    {
        return accumulate(products.begin(), products.end(), 0.0, [](double total, const Product &product) { 
            return total + product.price; });
    }
};

class ECommerceSystem
{
private:
    vector<User> users;
    vector<Order> orders;
    map<string, double> categorySales;
    map<string, map<string, double>> listing;

public:
    ECommerceSystem() : categorySales()
    {
        // Predefined product listing
        listing = {
           {"ELECTRONICS", {
            {"Ipad", 1200.00},
            {"Iphone", 2500.00}
        }},
        {"APPAREL", {
            {"T-shirt", 20.00},
            {"Pants", 30.00},
            {"Shoes", 35.00}
        }},
            {"BOOKS AND STATIONERY", {
            {"Fiction", 15.00},
            {"Non fiction", 10.00},
            {"Notebooks", 5.00}
        }},
        {"GAMING ACCESSORIES", {
            {"XBOX", 250.00},
            {"Headset", 30.00},
            {"Oculus", 300.00}
        }},
        {"HOME AND HOUSEHOLD", {
            {"Clock", 50.00},
            {"Lamps", 25.00},
            {"Room Decor", 10.00}
        }}
        };
    }

    // Function to register a new user
    void registerUser(const User &user)
    {
        users.push_back(user);
    }

    // Function for user login authentication
    bool authenticateUser(const string &username, const string &password) const
    {
        for (const auto &user : users)
        {
            if (user.username == username && user.password == password)
            {
                return true;
            }
        }
        return false;
    }

    // Function to list available products
    void listAvailableProducts() const
    {   
        cout << "-------------------\n";
        cout << "Available Products:\n";
        cout << "-------------------\n";

        for (const auto &categoryEntry : listing)
        {
            const string &category = categoryEntry.first;
            const map<string, double> &productsInCategory = categoryEntry.second;

            cout << "Category: " << category << "\n";
            for (const auto &productEntry : productsInCategory)
            {
                cout << "- " << productEntry.first << " (Price: $" << productEntry.second << ")\n";
            }
            cout << "\n";
        }
    }

    // Function to get the price and category of a product
    pair<string, double> getProductInfo(const string &productName) const
    {
        for (const auto &categoryEntry : listing)
        {
            const string &category = categoryEntry.first;
            const map<string, double> &productsInCategory = categoryEntry.second;

            auto productIt = productsInCategory.find(productName);
            if (productIt != productsInCategory.end())
            {
                return make_pair(category, productIt->second);
            }
        }
        return make_pair("", -1.0); // Return empty pair if the product is not found
    }

    // Function to process an order
    void processOrder(const Order &order)
    {
        orders.push_back(order);

        // Update category sales
        for (const auto &product : order.products)
        {
            categorySales[product.category] += product.price;
        }
    }

    // Function to generate an invoice for an order
    void generateInvoice(const Order &order) const
    {
        cout << "------------------------------\n";
        cout << "Invoice for user: " << order.username << "\n";
        cout << "------------------------------\n";

        for (const auto &product : order.products)
        {
            cout << "- " << product.name << " (" << product.category << "): $" << product.price << "\n";
        }
        cout << "Total: $" << order.calculateTotal() << "\n";
    }

    // Function to report total sales by category
    void reportTotalSales() const
    {
        cout << "Total Sales by Category:\n";
        for (const auto &entry : categorySales)
        {
            cout << entry.first << ": $" << entry.second << "\n";
        }
    }
};

int main()
{
    ECommerceSystem ecommerce;

    // Register users
    ecommerce.registerUser(User("Karan", "Karan"));
    ecommerce.registerUser(User("siddharth", "siddharth"));
    ecommerce.registerUser(User("Afrah", "Afrah"));

    cout << "Are you an existing user? {Y/N} : ";
    char s;
    cin >> s;
    if (s == 'N')
    {
        string username, password;
        cout << "--------Create your account--------" << endl;
        cout << "Enter your username: ";
        cin >> username;

        cout << "Enter your password: ";
        cin >> password;
        ecommerce.registerUser(User(username, password));
    }
    cout << "---------Log in-----------" << endl;
    Order order;
    cout << "Enter your username: ";
    cin >> order.username;

    cout << "Enter your password: ";
    cin >> order.password;

    if (ecommerce.authenticateUser(order.username, order.password))
    {  
         //List available products
        ecommerce.listAvailableProducts();

        int numProducts;
        cout << "Enter the number of products in your order: ";
        cin >> numProducts;

        for (int i = 0; i < numProducts; ++i)
        {
            string productName;
            cout << "Enter product name: ";
            cin >> productName;

            auto productInfo = ecommerce.getProductInfo(productName);

            if (productInfo.second != -1.0)
            {
                order.products.push_back(Product(productName, productInfo.first, productInfo.second));
            }
            else
            {
                cout << "Product not found.\n"; //edited
                i--; //edited
            }
        }

        // Process the order
        ecommerce.processOrder(order);
        cout << "Your order has been processed successfully.\n";
        ecommerce.generateInvoice(order);
        // Report total sales by category
        ecommerce.reportTotalSales();
    }
    else
    {
        cout << "Authentication failed. Order processing aborted.\n";
    }

    return 0;
}
