C++ Loan Manager and Log Analysis Tools

This repository contains two small C++ console programs.
They are completely separate tools and live in two folders:

ex1 — A simple loan manager program for storing users and their recent borrowed items

ex2 — A log analysis tool that reads event logs and prints a bar chart of tag frequencies

Both programs are written in standard C++ and do not require external libraries.

How to Compile and Run

These instructions assume you are using a standard terminal with g++.

Running ex1 (Loan Manager)

Open a terminal inside the ex1 folder:

cd ex1


Compile the program:

g++ main.cpp Patron.cpp -o test_ex1


Run it:

./test_ex1


The program will show a menu:

Register a new user

Log in

Record a new loan

Exit

User data is stored in patrons.txt inside the folder.

Running ex2 (Log Analysis Tool)

Open a terminal inside the ex2 folder:

cd ex2


Compile the program:

g++ Main.cpp LogReader.cpp -o test_ex2


Run it:

./test_ex2


The program will ask for:

The log file name

The tag list file name

The output file name

It then prints a bar chart to the screen and writes the same chart into the output file you choose.

What Each Program Does
ex1 — Loan Manager

This program lets you:

Register new users

Log in using an ID and pin

View their details

Add loan items (keeps only the three most recent)

All information is saved in plain text format.

ex2 — Log Analysis

This program reads a log text file and finds lines containing tags (words immediately after #tag:).
It counts how many times each tag appears and prints a chart.
The output is shown on the screen and also written to an output file.
