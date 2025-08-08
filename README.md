# BOLTU The Shop: A C++ Console Application
## Project Overview
"BOLTU" is a command-line shopping management system developed in C++. It simulates a multi-user e-commerce environment with distinct roles for customers, sellers, and administrators. The application is designed to be interactive and robust, using file I/O to handle data persistence for products, user accounts, and sales records. This project showcases object-oriented programming principles and data management in a practical, real-world scenario.

## Features
Multi-User System: The application supports three types of users, each with a unique set of functionalities:

Customers: Can sign up, log in, browse products, make purchases, and receive a detailed receipt.

Sellers: Can log in with a predefined ID and password (deloar/seller) to add, modify, and view products in the inventory.

Admins: Can log in with a predefined ID and password (ADMIN/admin@123) to view and delete both users and products.

Data Persistence: All crucial information—user credentials, product inventory, and sales history—is stored in plain text files (users.txt, products.txt, and sales.txt). This ensures that data is saved between sessions.

Dynamic Inventory Management: Sellers can add new products or modify existing ones by updating their price and quantity.

Sales Tracking: The system records all transactions with a timestamp, customer ID, product details, and total amount in sales.txt.

Detailed Receipt Generation: The program generates a clean, formatted receipt for customers, including a timestamp and a breakdown of their purchase.

Object-Oriented Design: The code is structured using classes (Product, Sale, Time, ProductManager, etc.) to model real-world entities, demonstrating key C++ concepts.

## Project Structure
boltu.cpp: The core C++ source code file that contains the entire application logic, including user authentication, menu-driven navigation, and data handling functions.

products.txt: A simple text file that acts as the database for the product inventory, storing each item's name, price, and available quantity.

users.txt: A text file that stores customer usernames and passwords.

sales.txt: A log file that records all transactions, including the time, customer, and details of the items purchased.

## How to Compile and Run
Save the files: Ensure all files (boltu.cpp, products.txt, users.txt, sales.txt) are in the same directory.

Compile the code: Use a C++ compiler (like g++) to compile the source code. Open your terminal and run the following command:

g++ boltu.cpp -o boltu.exe

This will create an executable file named boltu.exe.

Run the application: Execute the compiled program from your terminal:

./boltu.exe

The application will launch, and you can start interacting with it.

How to Work With the Application
Upon running, you'll be greeted with a main menu to enter as a Customer, Seller, or Admin.

As a Customer
Choose "Enter as a Customer" (1).

You can Sign Up (2) for a new account or Log In (1) with existing credentials from users.txt.

Once logged in, you can browse the products and make a purchase. The program will guide you through adding items and quantities.

After you're finished shopping, you can drop any products you don't want, and the program will print a final receipt.

As a Seller
Choose "Enter as a Seller" (2).

Log in using the default credentials: username: deloar, password: seller.

You will be able to add new products to products.txt, modify existing product details (price or quantity), or view the current inventory.

As an Admin
Choose "Enter as an Admin" (3).

Log in using the default credentials: username: ADMIN, password: admin@123.

As an admin, you have full control over the system. You can view all user accounts, and delete them if necessary. You can also view the product inventory and remove products from the list.
