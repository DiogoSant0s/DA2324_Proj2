#ifndef DA2_MENU_H
#define DA2_MENU_H

#include <iomanip>
#include <bits/stdc++.h>
#include <sys/time.h>
#include "Data.h"

/**
 * @details The Menu class configures the User Interface, dealing with all inputs and outputs, and connects to the project's data through the object data
 */
class Menu {
    /**
     * Object of the class Data that connects the user with the project's data
     */
    Data data;
public:
    /**
     * Menu class constructor
     * @details Calls the Data class constructor and the SelectGraphMenu function
     */
    Menu();
    /**
     * Void method that shows the projects' title
     * @details Time Complexity - O(1)
     */
    static void printTitle();
    /**
     * Void method that ensures the user's input integer is valid
     * @param inputs Integer vector
     * @details Time Complexity - O(1)
     * @return The integer provided by the user, verified to be valid
     */
    static int getUserInput(vector<int> inputs);
    /**
     * Void method that clears the screen
     * @details Time Complexity - O(1)
     */
    static void clearScreen();
    /**
     * Void method that outputs a string in a table block or in a path
     * @param s String to Print
     * @param length Space given to the string in the table
     * @param tableOrPath Bool used to determine if we're printing a Table or a Path
     * @details Time Complexity - O(1)
     */
    static void Print(const string &s, int length, bool tableOrPath);
    /**
     * Double method that calculates the elapsed time between two timevals and prints it
     * @param start Timeval of the start
     * @param end Timeval of the end
     * @details Time Complexity - O(1)
     * @return The elapsed time
     */
    static double printElapsedTime(timeval start, timeval end);
    /**
     * Void method that prints the report values if they are valid or N/A if they are not
     * @details Time Complexity - O(1)
     */
    static void checkReportValues(stringstream &i, int precision, double value);
    /**
     * Void method used to choose which graph to read from the datasets
     * @details Time Complexity - O(1)
     */
    void SelectGraphMenu();
    /**
     * Void method used to start the interaction between the user and this projects' data
     * @details Time Complexity - O(1)
     */
    void MainMenu();
    /**
     * Void method used to continue the interaction between the user and this projects' data
     * @details Time Complexity - O(1)
     */
    void InfoMenu();
};

#endif //DA2_MENU_H
