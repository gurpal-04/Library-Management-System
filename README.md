
# Library Management System in C

The Library Management System in C is a command-line based application that facilitates the management of books in a library. The system is designed to provide a user-friendly interface for both regular users and administrators. Users can sign in to their accounts, search for books using various criteria, and view available books, while administrators have additional privileges such as adding new books to the library.

## Goals

The primary goal of this project is to create an efficient and user-friendly library management system that allows users to access and search for books easily. The project aims to achieve the following objectives:

1. **User Authentication:** Implement a secure login system that differentiates between regular users and administrators.

2. **Book Management:** Enable users to view a list of all the books, search for books by ID, title, and author's name.

3. **Administrator Privileges:** Allow administrators to access an admin dashboard and provide them with the ability to add new books to the library.

## Specifications

The Library Management System is built in C and incorporates the following key features:

- **User Login:** Users are required to sign in using their credentials (username and password) to access the system.

- **Admin Login:** Administrators can log in using special admin credentials to access the admin dashboard.

- **User Dashboard:** After successful login, regular users can view the list of books and search for books using different criteria.

- **Admin Dashboard:** Administrators can perform tasks such as adding new books to the library. They can provide details like book ID, title, author's name.

- **Search Functionality:** Users can search for books by providing the book ID, book title, or author's name. The system will display matching results.

- **Book Listing:** Both users and administrators can view a list of all available books in the library.

## Design

The project is structured with modular programming principles to enhance readability, maintainability, and scalability. The following components and modules are incorporated:

- **User Authentication:** A secure login mechanism is implemented using username and password validation. User credentials are stored in a secure manner.

- **File Handling:** Data related to books and user credentials is stored in separate text files. This ensures data persistence between sessions.

- **User Interface:** The command-line interface provides a user-friendly way for users to interact with the system. Clear prompts and messages guide users through the different functionalities.

- **Search Algorithm:** The search feature utilizes algorithms to efficiently find and display matching books based on user input.

- **Admin Privileges:** Administrators can access the admin dashboard by providing appropriate credentials. Admins can then add new books to the library.

## Usage

1. Clone the repository to your local machine.
2. Compile the source code using a C compiler.
3. Run the executable.
4. Choose between user and admin login.
5. Follow the prompts to navigate the user or admin dashboard.
6. Search for books, view the list of books, and manage the library as needed.

## Conclusion

The Library Management System in C provides an organized and efficient way to manage books within a library. With features such as user authentication, search functionality, and admin privileges, this system offers a comprehensive solution for both users and administrators to interact with the library's book inventory.
