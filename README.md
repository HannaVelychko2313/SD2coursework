Beauty Salon Management System

Terminal-based management system designed for beauty salons handling customer management, appointment scheduling, and financial document generation (invoices and receipts).

Features:

    Business Management:
        Update business name, ID, phone, and address.
        Business details are saved to and loaded from 'business_details.txt'.

    Appointment & Billing:
        Scheduling appointments linking customers and services.
        Automatic generation of invoices and receipts in .txt format.

User Roles:
Admin: full access to creating new users, managing customers, services, products, viewing all financial records, and updating business details.

    Staff: full access to appointment management, partial access to customers, services and products records, ability to generate financial documents for appointments

Technical Implementation:

    Object-Oriented Programming: inheritance (Staff and Admin inherite from User, roduct and Service inherit from Item) and polymorphism.

    Data Persistence: automatic file I/O system that saves all data into text files upon shutdown and loads them at startup.

    Input Validation:error handling using Regex for dates/times.

    Memory Management:use of constructors/destructors to prevent memory leaks during object cleanup.

File Structure:

'SalonSystem.h/cpp' - managing data flow and logic

'Appointment.h/cpp' - scheduling and generating receipts/invoices

'User/Staff/Admin.h/cpp' - user hierarchy and role-based permissions

'Item/Product/Service.h/cpp' - product and service management

'\*.txt` files generated automatically

Passwords:
Default Admin User: admin890
Staff User: anita7
