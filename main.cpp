#include <iostream>
#include <string>

using namespace std;

const int MAX_USERS = 100;           // Maximum number of biometric entries
string storedHashes[MAX_USERS];      // Array to store hashed biometric entries
int userCount = 0;                   // To track the number of enrolled users
string adminPassword = "securepass"; // Password for enrollment access

// Function to hash a "biometric" pattern (simple simulation)
string hashData(const string &data)
{
    unsigned long hash = 5381;
    for (char c : data)
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return to_string(hash);
}

// Function to shift each character by 4 places in the alphabet
string generateUniqueString(const string &data)
{
    string result;
    for (char c : data)
    {
        if (isalpha(c))
        {
            if (islower(c))
            {
                result += 'a' + (c - 'a' + 4) % 26;
            }
            else
            {
                result += 'A' + (c - 'A' + 4) % 26;
            }
        }
        else
        {
            result += c; // Non-alphabetic characters remain unchanged
        }
    }
    return result;
}

// Function to create a user-friendly unique string
string generateUserFriendlyString(const string &name, const string &birthMonth, const string &favoritePerson, const string &favoriteThing)
{
    // Use the first letters of key responses
    string acronym = string(1, toupper(name[0])) + string(1, toupper(birthMonth[0])) +
                     string(1, toupper(favoritePerson[0])) + string(1, toupper(favoriteThing[0]));

    // Add a mnemonic number based on string lengths
    int numberPart = name.length() + birthMonth.length() + favoritePerson.length() + favoriteThing.length();

    // Add a meaningful suffix
    string suffix = generateUniqueString(favoriteThing).substr(0, 3); // First 3 shifted chars

    // Combine all parts with dashes
    return acronym + "-" + to_string(numberPart) + "-" + suffix;
}

// Function to authenticate against stored hashes
bool authenticate(const string &inputHash)
{
    for (int i = 0; i < userCount; i++)
    {
        if (storedHashes[i] == inputHash)
        {
            return true; // Match found
        }
    }
    return false; // No match found
}

// Function to check the admin password
bool checkPassword()
{
    string enteredPassword;
    int attempts = 0;

    while (attempts < 5)
    {
        cout << "Enter admin password to access enrollment: ";
        cin >> enteredPassword;

        if (enteredPassword == adminPassword)
        {
            return true; // Password is correct
        }
        else
        {
            attempts++;
            cout << "Incorrect password." << endl;
        }
    }

    cout << "Too many failed attempts. Returning to the main menu." << endl;
    return false; // Failed after 5 attempts
}

int main()
{
    string inputData; // To hold user input for enrollment or authentication
    int option;       // Menu option

    cout << "=== Biometric Authentication System ===" << endl;

    while (true)
    {
        // Display menu
        cout << "\n1. Enroll Biometric Data" << endl;
        cout << "2. Authenticate Biometric Data" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        // Handle menu options
        if (option == 1)
        {
            if (checkPassword())
            { // Only proceed if the correct password is provided
                if (userCount >= MAX_USERS)
                {
                    cout << "Enrollment limit reached. Cannot enroll more users." << endl;
                }
                else
                {
                    string name, birthMonth, favoritePerson, favoriteThing;

                    cout << "Answer the following questions to create your unique biometric:\n";
                    cout << "1. What is your full name? ";
                    cin.ignore();
                    getline(cin, name);

                    cout << "2. What is your birth month? ";
                    getline(cin, birthMonth);

                    cout << "3. Who is your favorite person? ";
                    getline(cin, favoritePerson);

                    cout << "4. What do you like about them? ";
                    getline(cin, favoriteThing);

                    // Generate a user-friendly unique string for the user
                    string uniqueString = generateUserFriendlyString(name, birthMonth, favoritePerson, favoriteThing);

                    // Hash the unique string
                    string hashedData = hashData(uniqueString);
                    storedHashes[userCount++] = hashedData; // Store the hashed biometric

                    cout << "Your unique biometric string is: " << uniqueString << endl;
                    cout << "Please save this string. You will use it for authentication." << endl;
                }
            }
        }
        else if (option == 2)
        {
            if (userCount == 0)
            {
                cout << "No biometric data found. Please enroll first!" << endl;
            }
            else
            {
                cout << "Enter your unique biometric string for authentication: ";
                cin.ignore();
                getline(cin, inputData);
                string inputHash = hashData(inputData);

                if (authenticate(inputHash))
                {
                    cout << "Authentication successful!" << endl;
                }
                else
                {
                    cout << "Authentication failed. Biometric data does not match." << endl;
                }
            }
        }
        else if (option == 3)
        {
            cout << "Exiting the system. Goodbye!" << endl;
            break; // Exit the loop and program
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
