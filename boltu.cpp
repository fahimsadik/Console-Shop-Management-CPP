#include<bits/stdc++.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include<windows.h>
using namespace std;

string customerId,customerPass,lname;
int lquantity;
double lprice;

class Time
{
public:
    Time()
    {
        // Get current time
        current_time_ = time(nullptr);

        // Convert to local time
        local_time_ = localtime(&current_time_);
    }

    string getTimeString() const
    {
        // Define the output format
        const char output_format[] = "%I:%M:%S %p, %A, %B %d, %Y";

        // Print the time in the desired format
        char time_string[100];
        strftime(time_string, sizeof(time_string), output_format, local_time_);

        return string(time_string);
    }

private:
    time_t current_time_;
    tm* local_time_;
};

// Function to check if a given user name exists in the file
bool check_username_exists(string username, string userfilename)
{
    ifstream file(userfilename);
    string line;
    while (getline(file, line))
    {
        if (line.substr(0, line.find(":")) == username)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// Function to sign up a new user and store their user name and password in a file
void usersignup(string userfilename)
{
    string username, password;
    system("CLS");
    cout << "Enter a username: ";
    cin >> username;
    if (check_username_exists(username, userfilename))
    {
        system("CLS");
        cout << "That username already exists. Please choose another one.\n";
        return;
    }
    system("CLS");
    cout << "Enter a password: ";
    cin >> password;
    ofstream file(userfilename, ios::app);
    file << username << ":" << password << endl;
    file.close();
    system("CLS");
    cout << "User created successfully!\n"<<endl;
    cout<<"please login now....."<<endl;
}

// Function to login a user and check if their username and password are correct
void userlogin(string userfilename)
{
    string username, password;
again:
    cout << "Enter your username: ";
    cin >> username;
    if (!check_username_exists(username, userfilename))
    {
        cout << "That username does not exist. Please try again or sign up.\n";
        goto again;
    }
    customerId=username;
againpass:
    cout << "Enter your password: ";
    cin >> password;
    ifstream file(userfilename);
    string line;
    while (getline(file, line))
    {
        if (line.substr(0, line.find(":")) == username && line.substr(line.find(":")+1) == password)
        {
            customerPass=password;
            file.close();
           system("CLS");
            cout << "Hello, " << username << "!\n";

            return;
        }
    }
    file.close();
    cout << "Incorrect password. Please try again.\n";
    goto againpass;
}

// Define a Product class to store information about each product
class Product
{
public:
    string name;
    double price;
    int quantity;

    Product(string name, double price, int quantity)
    {
        this->name = name;
        this->price = price;
        this->quantity = quantity;
    }

    void display()
    {
        cout << name << " - TK" << price << " - " << quantity << " in stock\n";
    }

    void sell(int quantity)
    {
        if (quantity <= this->quantity)
        {
            this->quantity -= quantity;
        }
    }
};

// Define a Sale class to store information about each sale
class Sale
{
public:
    Time t;
    string current_time = t.getTimeString();
    string username;
    string product_name;
    double price;
    int quantity;
    double total;
    time_t time;
    Sale() : username(""), product_name(""), price(0.0), quantity(0), time(0) {}
    Sale(string username,string product_name, double price, int quantity, double total,string current_time)
    {
        this->current_time=current_time;
        this->username=username;
        this->product_name = product_name;
        this->price = price;
        this->quantity = quantity;
        this->total = total;

    }

    bool operator==(const Sale& other) const
    {
        return product_name == other.product_name;
    }


};

// Read product information from a file and return a vector of Product objects
vector<Product> read_products(string filename)
{
    vector<Product> products;
    ifstream infile(filename);
    if (!infile)
    {
        cerr << "Error: could not open file " << filename << endl;
        exit(1);
    }
    string name;
    double price;
    int quantity;
    while (infile >> name >> price >> quantity)
    {
        Product p(name, price, quantity);
        products.push_back(p);
    }
    infile.close();
    return products;
}

// Write updated product information to a file
void write_products(string filename, const vector<Product>& products)
{
    ofstream outfile(filename);
    if (!outfile)
    {
        cerr << "Error: could not open file " << filename << endl;
        exit(1);
    }
    for (int i = 0; i < products.size(); i++)
    {
        outfile << products[i].name << " " << products[i].price << " " << products[i].quantity << endl;
    }
    outfile.close();
}

class ProductManager
{

public:
    ProductManager()
    {
        // Load products from file
        ifstream infile("products.txt");
        string line;
        while (getline(infile, line))
        {
            stringstream ss(line);
            string name;
            double price;
            int quantity;
            ss >> name >> price >> quantity;
            Product p(name, price, quantity);
            products.push_back(p);
        }
        infile.close();
    }

    void addProduct()
    {
        string name;
        double price;
        int quantity;
        system("CLS");
        cout << "Enter product name: ";
        cin >> name;
        cout << "Enter product price: ";
        cin >> price;
        cout << "Enter product quantity: ";
        cin >> quantity;

        // Check if product already exists
        for (auto& prod : products)
        {
            if (prod.name == name)
            {
                system("CLS");
                cout << "Product already exists. Updating price and quantity." << endl;
                prod.price = price;
                prod.quantity += quantity;
                saveProductsToFile();
                return;
            }
        }
        Product p(name, price, quantity);
        products.push_back(p);
        saveProductsToFile();
    }

    void modifyProduct()
    {
        string product_name;
        cout << "Enter the name of the product to modify: ";
        cin >> product_name;

        for (auto& prod : products)
        {
            if (prod.name == product_name)
            {
                int choice;
                system("CLS");
                cout << "What do you want to modify?" << endl;
                cout << "1. Price" << endl;
                cout << "2. Quantity" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                if (choice == 1)
                {
                    system("CLS");
                    cout << "Enter new price: ";
                    cin >> prod.price;
                }
                else if (choice == 2)
                {
                    system("CLS");
                    cout << "Enter quantity to add or subtract: ";
                    int quantity;
                    cin >> quantity;
                    prod.quantity += quantity;
                }
                else
                {
                    system("CLS");
                    cout << "Invalid choice. Please try again." << endl;
                }

                saveProductsToFile();
                return;
            }
        }
system("CLS");
        cout << "Product not found." << endl;
    }

    void viewProducts()
    {
        //system("CLS");
        cout << "Products:" << endl;
        for (auto& prod : products)
        {
            cout << prod.name << " " << prod.price << " " << prod.quantity << endl;
        }
        system("pause");
        //int getch(void);
    }

private:
    vector<Product> products;

    void saveProductsToFile()
    {
        ofstream outfile("products.txt");
        for (auto& prod : products)
        {
            outfile << prod.name << " " << prod.price << " " << prod.quantity << endl;
        }
        outfile.close();
    }
};


class UserList
{
private:
    string filename;

public:
    UserList(string file)
    {
        filename = file;
    }

    void read_users()
    {
        ifstream infile(filename);
        string line;

        while (getline(infile, line))
        {
            string delimiter = ":";
            size_t pos = 0;
            string username, password;

            pos = line.find(delimiter);
            username = line.substr(0, pos);
            password = line.substr(pos + 1, line.length() - pos - 1);

            cout << "Username: " << username << "  Password: " << password << endl;
        }

        infile.close();
    }
};

class UserSales {
    private:
        string user_file;
        string sales_file;

    public:
        UserSales(string user, string sales) {
            user_file = user;
            sales_file = sales;
        }

        void delete_user(string username) {
            // Delete user from users.txt
            ifstream user_infile(user_file);
            ofstream user_outfile("temp.txt");
            string user_line;
            bool found = false;

            while (getline(user_infile, user_line)) {
                if (user_line.find(username) == string::npos) {
                    user_outfile << user_line << endl;
                } else {
                    found = true;
                }
            }

            user_infile.close();
            user_outfile.close();
            remove(user_file.c_str());
            rename("temp.txt", user_file.c_str());

            // Delete user from sales.txt
            ifstream sales_infile(sales_file);
            ofstream sales_outfile("temp.txt");
            string sales_line;

            while (getline(sales_infile, sales_line)) {
                if (sales_line.find(username) == string::npos) {
                    sales_outfile << sales_line << endl;
                }
            }

            sales_infile.close();
            sales_outfile.close();
            remove(sales_file.c_str());
            rename("temp.txt", sales_file.c_str());

            if (found) {
                    system("CLS");
                cout << "Deleted user " << username << " from user_file and sales_file" << endl;
            } else {
                system("CLS");
                cout << "User " << username << " not found in user_file" << endl;
            }
        }
};

class ProductRemover {
    private:
        string product_file;

    public:
        ProductRemover(string product) {
            product_file = product;
        }

        void remove_product(string product_name) {
            // Remove product from products.txt
            ifstream product_infile(product_file);
            ofstream product_outfile("temp.txt");
            string product_line;
            bool found = false;

            while (getline(product_infile, product_line)) {
                if (product_line.find(product_name) == string::npos) {
                    product_outfile << product_line << endl;
                } else {
                    found = true;
                }
            }

            product_infile.close();
            product_outfile.close();
            remove(product_file.c_str());
            rename("temp.txt", product_file.c_str());

            if (found) {
                    system("CLS");
                cout << "Removed product " << product_name << " from " << product_file << endl;
            } else {
                system("CLS");
                cout << "Product " << product_name << " not found in " << product_file << endl;
            }
        }
};

void title()
{
    cout << "\t\t\t\t*****************************************" << endl;
    cout << "\t\t\t\t*                                       *" << endl;
    cout << "\t\t\t\t*             Welcome to boltu          *" << endl;
    cout << "\t\t\t\t*                                       *" << endl;
    cout << "\t\t\t\t*****************************************" << endl << endl << endl;
    cout << "Enter as a Customer  : Enter 1" << endl;
    cout << "Enter as a Seller    : Enter 2" << endl;
    cout << "Enter as an Admin    : Enter 3" << endl;
    cout << "To exit the application : Enter 0" << endl;
    cout << "---------------------------------" << endl << endl;
    cout << "Enter your choice : ";
}

int main ()
{
    // Read product information from a file
    string salefilename="sales.txt";
    Time t;
    string current_time = t.getTimeString();
    string userfilename = "users.txt";
    int appp,customerValue,sellerValue,adminValue,customerchoosed,selleradding,sellerchoosed;
    string sellerId,sellerPass,adminId,adminPass;
mainmenu:
    cout<<endl;
    system("CLS");
    title();
    cin>>appp;
    while(appp!=0 && appp!=1 && appp!=2 && appp!=3)
    {
        cout << "ERROR!!! You have entered invalid key." << endl << endl;
        cout << "Enter your choice carefully again!! : ";
        cin >> appp;
    }

    if(appp==0)
    {
        cout << endl << "Exit Successfully!!!" << endl;
        return -1;
    }
    else if(appp==1)
    {
        string filename = "products.txt";
        vector<Product> products = read_products(filename);
customermenu:
    system("CLS");
        cout << "\t\t\t\t*****************************************" << endl;
        cout << "\t\t\t\t*      Thank you for choosing us        *" << endl;
        cout << "\t\t\t\t*****************************************" << endl << endl << endl;
        cout<<"for login [1]"<<endl;
        cout<<"for sign up [2]"<<endl;
        cout<<"for goto main menu [0]"<<endl;
        cout<<"Please choose an option: ";
        cin>>customerValue;
        while(customerValue!=0 && customerValue!=1 && customerValue!=2)
        {
            cout << "ERROR!!! You have entered invalid key." << endl << endl;
            cout << "Enter your choice carefully again!! : ";
            cin >> customerValue;
        }
        if(customerValue==0)
        {
            cout<<"going back to main menu....";
            goto mainmenu;
        }
        else if(customerValue==1)
        {
            system("CLS");
            userlogin(userfilename);
customerhello:
            cout<<"buy products [1]"<<endl;
            cout<<"for goto customer menu menu [0]"<<endl;
            cout<<"Please choose an option: ";
            cin>>customerchoosed;
            while(customerchoosed!=0 && customerchoosed!=1)
            {
                cout << "ERROR!!! You have entered invalid key." << endl << endl;
                cout << "Enter your choice carefully again!! : ";
                cin >> customerchoosed;
            }
            if(customerchoosed==0)
            {
                system("CLS");
                cout<<"going back to customer menu";
                goto customermenu;

            }
            else if(customerchoosed==1)
            {
                int countproduct=0;
buyuser:

                // Display all the products in the shop
                system("CLS");
                cout << "Welcome to the shop!\n";
                cout << "Here are the products we have available:\n";
                double total_amount=0;
                vector<Sale> sales;
                string username=customerId;
                Sale sale;
                sale.current_time=current_time;
                sale.username=username;
                ofstream outfile("sales.txt", ios::app);

                if (!outfile)
                {
                    cerr << "Error: could not open file sales.txt" << endl;
                    exit(1);
                }
                outfile<<endl;
                outfile<<current_time<<" "<<customerId<<" ";
                outfile.close();
productmenu:
                for (int i = 0; i < products.size(); i++)
                {
                    products[i].display();
                }
                // Allow the user to buy products
                bool buy_more = true;
                while (buy_more)
                {
                    string product_name;
namerama:
                system("CLS");
                for (int i = 0; i < products.size(); i++)
                    {
                        products[i].display();
                    }
                    cout << "Enter the name of the product you want to buy: ";
                    cin >> product_name;
                    for (int i = 0; i < products.size(); i++)
                    {
                        if (products[i].name == product_name)
                        {
                            int quantity;

                            cout << "Enter the quantity you want to buy: ";
                            cin >> quantity;
                            for(int i=0; i< sales.size(); i++)
                            {
                                if(sales[i].product_name==product_name)
                                {
                                    //cout<<"LULU"<<endl;
                                    sales[i].quantity+=quantity;

                                    //break;
                                    goto namerama;
                                }
                            }

                            products[i].sell(quantity);
                            write_products(filename, products);
                            double total_price = quantity * products[i].price;
                            system("CLS");
                            cout << " You bought " << quantity << " " << products[i].name << " for $" << total_price << ". Thank you for your purchase!\n";
                            countproduct++;
                            // Store sale information in the sales vector
                            Sale sale;
                            sale.product_name = product_name;
                            sale.quantity = quantity;
                            sale.price = products[i].price;
                            sale.total = total_price;
                            sales.push_back(sale);
                            total_amount+=quantity* products[i].price ;
writesale:
                            //countproduct++;

                            // Ask the user if they want to buy more products
                            char buy_more_input;

                            cout << "Do you want to buy more products? (y/n): ";
                            cin >> buy_more_input;
                            if (buy_more_input == 'n')
                            {

                                buy_more = false;
willdrop:
                                system("CLS");
                                cout<<"if you want to drop any product press [1] or press [0] to customer menu...";
                                cout<<endl<<"after that you wont be able to drop any products";
                                cout<<"enter your choice";
                                int dropProductValue;
                                cin>>dropProductValue;
                                if(dropProductValue==1)
                                {
                                    //drop products begin here

                                    void dropProductQuantity(vector<Sale>& sales);
                                    {
                                        string product_name;
                                        int dropped_quantity;
                                        bool found = false;

                                        // Get product name and quantity to drop from user
again:
                                        cout << "Enter product name: ";
                                        cin>> product_name;
                                        cout << "Enter quantity to drop: ";
                                        cin >> dropped_quantity;
                                        if(countproduct<1)
                                        {
                                            system("CLS");
                                            cout<<"you hadnot bought anything"<<endl;
                                            goto customerhello;

                                        }
                                        else

                                            // Search for the product in the vector of sales
                                            for (int i = 0; i < sales.size(); i++)
                                            {
                                                if (sales[i].product_name == product_name)
                                                {
                                                    found = true;

                                                    // If the dropped quantity is greater than or equal to the quantity of the product in the sale
                                                    if(dropped_quantity > sales[i].quantity)
                                                    {
                                                        cout<<"error"<<endl;
                                                        goto again;
                                                    }
                                                    else if (dropped_quantity == sales[i].quantity)
                                                    {
                                                        total_amount-=dropped_quantity*sales[i].price;
                                                        sales.erase(sales.begin() + i); // Remove the entire sale
                                                        cout << "Product removed from sales." << endl;
                                                        countproduct--;
                                                    }
                                                    else if(dropped_quantity<sales[i].quantity) // Reduce the quantity of the product in the sale
                                                    {
                                                        //double price_per_item = sales[i].price / sales[i].quantity;
                                                        sales[i].quantity -= dropped_quantity;
                                                        total_amount-=dropped_quantity*sales[i].price;
                                                        //sales[i].price = sales[i].quantity * price_per_item;
                                                        sales[i].total = sales[i].quantity * sales[i].price;
                                                        cout << "Product quantity dropped." << endl;

                                                    }
                                                    lname=product_name;
                                                    lquantity=dropped_quantity;
                                                    lprice=sales[i].price;
                                                    //break; // Exit the loop once the product is found
                                                }
                                            }

                                        if (!found) // Product not found in sales
                                        {
                                            system("CLS");
                                            cout << "Product not found in sales." << endl;
                                            goto again;
                                        }
                                    }
                                }
                                else if(dropProductValue==0)
                                {
                                    goto billhere;
                                }
                            }


                        }


                    }
                }

                // Update the quantity in the products.txt file

                void producthehe();
                {
                    ifstream infile("products.txt");
                    ofstream outfile("temp.txt");
                    string line;
                    bool updated = false;
                    while (getline(infile, line))
                    {
                        stringstream ss(line);
                        string name;
                        double price;
                        int quantity;
                        ss >> name >> price >> quantity;
                        if (name == lname)
                        {
                            quantity += lquantity;
                            outfile << name << " " << price << " " << quantity << endl;
                            updated = true;
                        }
                        else
                        {
                            outfile << line << endl;
                        }
                    }
                    if (!updated)
                    {
                        outfile << lname << " " << lprice << " " << lquantity << endl;
                    }
                    infile.close();
                    outfile.close();
                    remove("products.txt");
                    rename("temp.txt", "products.txt");
                }

billhere:
    system("CLS");
                cout<<"printing bill"<<endl;
                getchar;
                cout << "-----------------------------" << endl;
                cout << "     WELCOME TO MY STORE" << endl;
                cout << "-----------------------------" << endl;
                cout << "Username: " << sale.username << endl;
                cout << "Date: " << sale.current_time << endl;
                cout << "-----------------------------" << endl;
                cout << "Product Name | Quantity | Price | Total" << endl;
                cout << "-----------------------------" << endl;
                for (Sale sale : sales)
                {
                    cout << setw(12) << left << sale.product_name
                         << setw(10) << left << sale.quantity
                         << setw(8) << right << fixed << setprecision(2) << sale.price
                         << setw(8) << right << fixed << setprecision(2) << sale.total
                         << endl;
                }
                cout << "-----------------------------" << endl;
                cout << "Total amount: $" << fixed << setprecision(2) << total_amount << endl;
                cout << "-----------------------------" << endl;

                void write();
                {
                    ofstream outfile("sales.txt", ios::app);

                    if (!outfile)
                    {
                        cerr << "Error: could not open file sales.txt" << endl;
                        exit(1);
                    }
                    for (int i = 0; i < sales.size(); i++)
                    {
                        outfile<<" "<< sales[i].product_name << " " << sales[i].price << " " << sales[i].quantity << " " << sales[i].total << " ";
                    }
                    outfile.close();
                }
                return 0;

                //buying products ends here
            }
            else
            {
                system("CLS");
                cout<<"showing cart";
            }
            //customer ends here
        }
        else
        {
            usersignup(userfilename);
            goto customermenu;
        }

    }

    else if(appp==2)
    {
        system("CLS");
        cout<<"login [1]"<<endl;
        cout<<"for goto main menu [0]"<<endl;
        cout<<"Please choose an option: ";
        cin>>sellerValue;
sellerloginmenu:
        while(sellerValue!=0 && sellerValue!=1)
        {
            cout << "ERROR!!! You have entered invalid key." << endl << endl;
            cout << "Enter your choice carefully again!! : ";
            cin >> sellerValue;
        }
        if(sellerValue==0)
        {
            system("CLS");
            cout<<"going back to main menu....";
            goto mainmenu;
        }
        else
        {
            system("CLS");
            cout<<"Enter user name: ";
            cin>>sellerId;
            cout<<"enter pass: ";
            cin>>sellerPass;

            if(sellerId=="deloar"&&sellerPass=="seller")
            {
                ProductManager manager;

                while (true)
                {
                    system("CLS");
                    int choice;
                    cout << "What do you want to do?" << endl;
                    cout << "1. Add product" << endl;
                    cout << "2. Modify product" << endl;
                    cout << "3. View products" << endl;
                    cout << "4. Goto Main menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice)
                    {
                    case 1:
                        system("CLS");
                        manager.addProduct();
                        break;
                    case 2:
                        system("CLS");
                        manager.modifyProduct();
                        break;
                    case 3:
                        system("CLS");
                        manager.viewProducts();
                        system("pause");
                        break;
                    case 4:
                        system("CLS");
                        goto mainmenu;
                    default:
                        system("CLS");
                        cout << "Invalid choice. Please try again";
                    }
                }
            }
            else
            {
                system("CLS");
                cout<<"wrong!!"<<endl;
                goto sellerloginmenu;
            }
        }
    }

    else
    {
adminloginmenu:
    system("CLS");
        cout<<"login [1]"<<endl;
        cout<<"for goto main menu [0]"<<endl;
        cout<<"Please choose an option: ";
        cin>>adminValue;
        while(adminValue!=0 && adminValue!=1 && adminValue!=2)
        {
            cout << "ERROR!!! You have entered invalid key." << endl << endl;
            cout << "Enter your choice carefully again!! : ";
            cin >> sellerValue;
        }
        if(adminValue==0)
        {
            system("CLS");
            cout<<"going back to main menu....";
            goto mainmenu;
        }
        else if (adminValue==1)
        {
            wrongadmin:
                system("CLS");
            cout<<"Enter user name: ";
            cin>>adminId;
            cout<<"enter pass: ";
            cin>>adminPass;

            if(adminId=="ADMIN"&&adminPass=="admin@123")
            {
                system("CLS");
                cout<<"hello admin!!"<<endl;
wheretochoose:
                cout<<"1. Show users"<<endl<<"2. Show Products"<<endl<<"0. Main Menu"<<endl<<"Enter you choice :";
                int adminchoose;
                cin>>adminchoose;
                if(adminchoose==1)
                {
                    system("CLS");
                    int keepchoice;
                    //see user details
                    UserList user_list("users.txt");
                    user_list.read_users();
                    hehe:
                    cout<<"want to delete any user"<<endl;

                    cout<<"1. Yes 2. No"<<endl;
                    cout<<"enter your choice: ";
                    cin>>keepchoice;
                    if(keepchoice==1)
                    {
                        UserSales user_sales("users.txt", "sales.txt");
    string username;

    while (true) {
        cout << "Enter username to delete (or 'q' to quit): ";
        cin >> username;

        if (username == "q") {
            goto wheretochoose;
        }

        user_sales.delete_user(username);
    }
                    }
                    else if(keepchoice==2){
                            system("CLS");
                        goto wheretochoose;
                    }
                    else
                        system("CLS");
                        goto hehe;

                }

                //ok
                else if(adminchoose==2){
                        int keepchoice;
                        string filename = "products.txt";
                        vector<Product> products = read_products(filename);
                        system("CLS");
                    for (int i = 0; i < products.size(); i++)
                {
                    products[i].display();
                }
                hoho:

                cout<<"want to remove any product"<<endl;

                    cout<<"1. Yes 2. No"<<endl;
                    cout<<"enter your choice: ";
                    cin>>keepchoice;
                    if(keepchoice==1){
                         ProductRemover product_remover("products.txt");
    string product_name;

    while (true) {
        cout << "Enter product name to remove (or 'q' to quit): ";
        cin >> product_name;

        if (product_name == "q") {
                system("CLS");
          break;
        }

        product_remover.remove_product(product_name);

    }
    goto wheretochoose;
                    }
                    else if(keepchoice==2){
                            system("CLS");
                        goto wheretochoose;
                    }

                else{
                    goto hoho;
                }

                }

                else if(adminchoose==0){
                        system("CLS");
                    goto mainmenu;
                }
            }
            else
                goto wrongadmin;

        }
        else
        {
            system("CLS");
            cout<<"wrong!!"<<endl;
            goto adminloginmenu;
        }

    }

}
