## ATM Management System (in C)

### Overview

This project is an ATM Management System written in C, designed to demonstrate programming logic, data manipulation, and file handling.
The system allows users to register, manage multiple accounts, make transactions, update account information, and more — all through a terminal interface.

The main goal is to enhance and extend an existing codebase by implementing new features, optimizing performance, and ensuring data persistence through file management.

### Features
#### User Authentication
- Login / Register users
- Prevent duplicate usernames

#### Account Management
- Create new accounts
- View list of owned accounts
- Check details of a specific account
- Update account information (country, phone number)

#### Transactions
- Deposit and withdraw funds (except for fixed accounts)
- Balance updates are persisted in files

#### Account Operations
- Delete existing accounts
- Transfer ownership to another user

### File Structure
```
.
├── data
│   ├── users.txt          # Stores user information (id, name, password)
│   └── records.txt        # Stores account records
├── src
│   ├── auth.c             # Handles user login
│   ├── file.c             # Handles file reading and writing
│   ├── input.c            # Handles user input of different types
│   ├── register.c         # Handles user registration
│   ├── system.c           # Core system functions (accounts, transactions, etc.)
│   ├── main.c             # Entry point of the program
│   └── header.h           # Header file with structures and function prototypes
├── Makefile               # For building the project
└── README.md              # Project documentation

```

### Installation & Usage
#### Build the Project
Use the Makefile to compile the source code:
```
make
```
This will generate an executable named atm in your project directory.

#### Run the Program
Once compiled, run the application using:
```
./atm
```
                ======= ATM =======


                [1]- login

                [2]- register

                [3]- exit

                Select option: 
```

```


                                   Bank Management System
                                         User Login:
```

```
                ======= ATM =======


                [1]- Create a new account

                [2]- Update account information

                [3]- Check accounts

                [4]- Check list of owned account

                [5]- Make Transaction

                [6]- Remove existing account

                [7]- Transfer ownership

                [8]- Exit

                Select option: 
```
