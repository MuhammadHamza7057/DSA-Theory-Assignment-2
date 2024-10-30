#include <iostream>
#include <limits> // For std::numeric_limits
using namespace std;

struct Node {
    int coefficient;
    int exponent;
    Node* next;
};

class Polynomial {
private:
    Node* head;

public:
    Polynomial() : head(nullptr) {}

    // Function to insert a term in the polynomial
    void insertTerm(int coefficient, int exponent) {
        if (coefficient == 0) return;  // Ignore zero coefficients

        Node* newNode = new Node{ coefficient, exponent, nullptr };
        Node* current = head;
        Node* prev = nullptr;

        // Insert in sorted order
        while (current && current->exponent > exponent) {
            prev = current;
            current = current->next;
        }

        // If the exponent already exists, add the coefficients
        if (current && current->exponent == exponent) {
            current->coefficient += coefficient;
            if (current->coefficient == 0) {  // Remove node if coefficient is zero
                if (prev) {
                    prev->next = current->next;
                }
                else {
                    head = current->next;
                }
                delete current;
            }
            return;
        }

        // Insert new term
        newNode->next = current;
        if (prev) {
            prev->next = newNode;
        }
        else {
            head = newNode;
        }
    }

    // Function to display the polynomial
    void display() {
        if (!head) {
            cout << "0" << endl;
            return;
        }

        Node* current = head;
        while (current) {
            cout << (current->coefficient > 0 && current != head ? " + " : "")
                << current->coefficient << "x^" << current->exponent;
            current = current->next;
        }
        cout << endl;
    }

    // Overload + operator for polynomial addition
    Polynomial operator+(const Polynomial& other) {
        Polynomial result;
        Node* current1 = head;
        Node* current2 = other.head;

        while (current1 || current2) {
            if (!current2 || (current1 && current1->exponent > current2->exponent)) {
                result.insertTerm(current1->coefficient, current1->exponent);
                current1 = current1->next;
            }
            else if (!current1 || (current2 && current1->exponent < current2->exponent)) {
                result.insertTerm(current2->coefficient, current2->exponent);
                current2 = current2->next;
            }
            else {
                result.insertTerm(current1->coefficient + current2->coefficient, current1->exponent);
                current1 = current1->next;
                current2 = current2->next;
            }
        }
        return result;
    }

    // Overload - operator for polynomial subtraction
    Polynomial operator-(const Polynomial& other) {
        Polynomial result;
        Node* current1 = head;
        Node* current2 = other.head;

        while (current1 || current2) {
            if (!current2 || (current1 && current1->exponent > current2->exponent)) {
                result.insertTerm(current1->coefficient, current1->exponent);
                current1 = current1->next;
            }
            else if (!current1 || (current2 && current1->exponent < current2->exponent)) {
                result.insertTerm(-current2->coefficient, current2->exponent);
                current2 = current2->next;
            }
            else {
                result.insertTerm(current1->coefficient - current2->coefficient, current1->exponent);
                current1 = current1->next;
                current2 = current2->next;
            }
        }
        return result;
    }

    // Overload * operator for polynomial multiplication
    Polynomial operator*(const Polynomial& other) {
        Polynomial result;
        for (Node* current1 = head; current1; current1 = current1->next) {
            for (Node* current2 = other.head; current2; current2 = current2->next) {
                result.insertTerm(current1->coefficient * current2->coefficient,
                    current1->exponent + current2->exponent);
            }
        }
        return result;
    }

    // Function to evaluate the polynomial at a given x
    double evaluate(double x) {
        double result = 0.0;
        Node* current = head;
        while (current) {
            result += current->coefficient * pow(x, current->exponent);
            current = current->next;
        }
        return result;
    }

    // Function to clear the polynomial
    void clear() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }
};

// Function to get valid integer input
int getValidIntegerInput() {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cout << "Invalid input! Please enter an integer: ";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any remaining input
            return input;
        }
    }
}

// Function to get valid double input
double getValidDoubleInput() {
    double input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cout << "Invalid input! Please enter a valid number: ";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any remaining input
            return input;
        }
    }
}

int main() {
    Polynomial poly1, poly2;
    int choice;

    do {
        cout << "===============================\n";
        cout << "    Polynomial Operations Menu\n";
        cout << "===============================\n";
        cout << "1. Insert Term(s)\n";
        cout << "2. Display Polynomial\n";
        cout << "3. Add Polynomials\n";
        cout << "4. Subtract Polynomials\n";
        cout << "5. Multiply Polynomials\n";
        cout << "6. Evaluate Polynomial\n";
        cout << "0. Exit\n";
        cout << "===============================\n";
        cout << "Choose an option: ";
        choice = getValidIntegerInput(); // Get validated integer input

        switch (choice) {
        case 1: {
            int numTerms;
            cout << "How many terms do you want to insert for the first polynomial? ";
            numTerms = getValidIntegerInput(); // Get validated integer input

            for (int i = 0; i < numTerms; i++) {
                int coefficient, exponent;
                cout << "Insert term " << (i + 1) << " - Enter coefficient: ";
                coefficient = getValidIntegerInput(); // Get validated integer input
                cout << "Insert term " << (i + 1) << " - Enter exponent: ";
                exponent = getValidIntegerInput(); // Get validated integer input
                poly1.insertTerm(coefficient, exponent);
                cout << "\n---------------------------------\n";
                cout << "   Term " << (i + 1) << " inserted successfully!\n";
                cout << "---------------------------------\n";
            }
            break;
        }
        case 2: {
            cout << "\n---------------------------------\n";
            cout << "      Displaying Polynomial:\n";
            cout << "---------------------------------\n";
            poly1.display();
            break;
        }
        case 3: {
            cout << "\nAdding Polynomials\n---------------------------------\n";
            int numTerms;
            cout << "How many terms do you want to insert for the second polynomial? ";
            numTerms = getValidIntegerInput(); // Get validated integer input

            for (int i = 0; i < numTerms; i++) {
                int coefficient, exponent;
                cout << "Insert term " << (i + 1) << " - Enter coefficient: ";
                coefficient = getValidIntegerInput(); // Get validated integer input
                cout << "Insert term " << (i + 1) << " - Enter exponent: ";
                exponent = getValidIntegerInput(); // Get validated integer input
                poly2.insertTerm(coefficient, exponent);
                cout << "\n---------------------------------\n";
                cout << "   Term " << (i + 1) << " inserted successfully!\n";
                cout << "---------------------------------\n";
            }

            Polynomial sum = poly1 + poly2;
            cout << "\n---------------------------------\n";
            cout << "   Sum of Polynomials: \n";
            cout << "---------------------------------\n";
            sum.display();

            // Ask if the user wants to insert another polynomial
            char insertMore;
            cout << "Do you want to insert another polynomial? (y/n): ";
            cin >> insertMore;
            if (insertMore == 'y' || insertMore == 'Y') {
                poly2.clear(); // Clear second polynomial for next use
                continue; // Restart the loop
            }

            poly2.clear(); // Clear second polynomial for next use
            break;
        }
        case 4: {
            cout << "\nSubtracting Polynomials\n---------------------------------\n";
            int numTerms;
            cout << "How many terms do you want to insert for the second polynomial? ";
            numTerms = getValidIntegerInput(); // Get validated integer input

            for (int i = 0; i < numTerms; i++) {
                int coefficient, exponent;
                cout << "Insert term " << (i + 1) << " - Enter coefficient: ";
                coefficient = getValidIntegerInput(); // Get validated integer input
                cout << "Insert term " << (i + 1) << " - Enter exponent: ";
                exponent = getValidIntegerInput(); // Get validated integer input
                poly2.insertTerm(coefficient, exponent);
                cout << "\n---------------------------------\n";
                cout << "   Term " << (i + 1) << " inserted successfully!\n";
                cout << "---------------------------------\n";
            }

            Polynomial difference = poly1 - poly2;
            cout << "\n---------------------------------\n";
            cout << "   Difference of Polynomials: \n";
            cout << "---------------------------------\n";
            difference.display();

            // Ask if the user wants to insert another polynomial
            char insertMore;
            cout << "Do you want to insert another polynomial? (y/n): ";
            cin >> insertMore;
            if (insertMore == 'y' || insertMore == 'Y') {
                poly2.clear(); // Clear second polynomial for next use
                continue; // Restart the loop
            }

            poly2.clear(); // Clear second polynomial for next use
            break;
        }
        case 5: {
            cout << "\nMultiplying Polynomials\n---------------------------------\n";
            int numTerms;
            cout << "How many terms do you want to insert for the second polynomial? ";
            numTerms = getValidIntegerInput(); // Get validated integer input

            for (int i = 0; i < numTerms; i++) {
                int coefficient, exponent;
                cout << "Insert term " << (i + 1) << " - Enter coefficient: ";
                coefficient = getValidIntegerInput(); // Get validated integer input
                cout << "Insert term " << (i + 1) << " - Enter exponent: ";
                exponent = getValidIntegerInput(); // Get validated integer input
                poly2.insertTerm(coefficient, exponent);
                cout << "\n---------------------------------\n";
                cout << "   Term " << (i + 1) << " inserted successfully!\n";
                cout << "---------------------------------\n";
            }

            Polynomial product = poly1 * poly2;
            cout << "\n---------------------------------\n";
            cout << "   Product of Polynomials: \n";
            cout << "---------------------------------\n";
            product.display();

            // Ask if the user wants to insert another polynomial
            char insertMore;
            cout << "Do you want to insert another polynomial? (y/n): ";
            cin >> insertMore;
            if (insertMore == 'y' || insertMore == 'Y') {
                poly2.clear(); // Clear second polynomial for next use
                continue; // Restart the loop
            }

            poly2.clear(); // Clear second polynomial for next use
            break;
        }
        case 6: {
            double x;
            cout << "Enter the value of x to evaluate the polynomial: ";
            x = getValidDoubleInput(); // Get validated double input
            double result = poly1.evaluate(x);
            cout << "\n---------------------------------\n";
            cout << "   Polynomial evaluated at x = " << x << ": " << result << "\n";
            cout << "---------------------------------\n";
            break;
        }
        case 0: {
            cout << "Exiting the program.\n";
            break;
        }
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 0);

    poly1.clear(); // Clear the first polynomial before exiting
    poly2.clear(); // Clear the second polynomial before exiting

    return 0;
}
