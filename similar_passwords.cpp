/*
Algorithm:
    Accesses the common passwords file and adds each password into a vector
    Calls the check_incorrect_char function to determine the number of incorrect characters between the input password and common password
    For each common password, determine the lowest number of incorrect characters
    Iterate through the common passwords vector and adds each common password with the lowest number of incorrect characters to a vector
    Sorts the similar passwords vector and prints out the output
*/
#include<iostream>
using std::cout; using std::endl; using std::cin;
#include<vector>
using std::vector;
#include<fstream>
using std::ifstream;
#include<string>
using std::string;
#include<algorithm>
using std::copy;
#include<iterator>
using std::ostream_iterator;

int check_incorrect_char(string &user_pass, string &test_pass) {
    /*
    This function finds the number of incorrect characters 
    Algorithm:
    Gets the length of both passwords
    Iterates through the smaller password and finds the extra characters if the length is different
    Finds the number of incorrect characters by comparing the positions of the characters within each password
    Returns: An integer of the total number of incorrect characters
    */
    int incorrect_char = 0;
    int extra_char;
    int total_incorrect_char;
    //Gets the length of user password and given test password
    int user_pass_size = static_cast<int>(user_pass.size());
    int test_pass_size = static_cast<int>(test_pass.size());
    //Iterates through the smaller password 
    if (user_pass_size <= test_pass_size) {
        //Counts the number of incorrect characters
        for(int i = 0; i <= user_pass_size - 1; i++) {
            if (user_pass[i] != test_pass[i]) {
                incorrect_char++;
            }
        }
        //Finds the length of the extra characters
        extra_char = test_pass_size - user_pass_size;
    }
    else {
         for(int i = 0; i <= test_pass_size - 1; i++) {
            //Counts the number of incorrect characters
            if (user_pass[i] != test_pass[i]) {
                incorrect_char++;
            }
        }
        //Finds the length of the extra characters 
        extra_char = user_pass_size - test_pass_size;
    }
    //Finds the total incorrect characters
    total_incorrect_char = incorrect_char + extra_char;
    return total_incorrect_char;
}

int main() {
    //Prompts for password input
    cout << "Give me a password: ";
    vector<string> similar_passwords;
    string user_password; 
    cin >> user_password;
    cout << "You provided a password of " << user_password << endl;
    cout << "The most similar passwords to " << user_password << " are:" << endl;
    string test_password;
    vector<int> incorrect_v;
    //Accesses the common_passwords file
    ifstream common_passwords("common_passwords.txt");
    string password;
    vector<string> common_pass_v;
    //Inserts all the passwords into a vector
    while(common_passwords >> password) {
        common_pass_v.push_back(password);
    }
    //Iterates through the common_passwords vector 
    for (auto test_password : common_pass_v) {
        //Adds the number of incorrect characters into a vector
        incorrect_v.push_back(check_incorrect_char(user_password, test_password));
    }
    //Retrieves the lowest number of incorrect characters
    int lowest_error = *min_element(incorrect_v.begin(), incorrect_v.end());
    //Retrieves all the common passwords and checks if they match the lowest number of incorrect characters
    for (auto test_password : common_pass_v) {
        if (check_incorrect_char(user_password, test_password) == lowest_error) {
            //Adds the common password with the lowest incorrect character to a vector
            similar_passwords.push_back(test_password);
        }
    }
    //Sort the vector of similar passwords
    sort(similar_passwords.begin(), similar_passwords.end());
    //Prints out all the similar passwords with commas
    for(auto i : similar_passwords) {
        cout << i << ", ";
    }
    cout << endl;
    cout << "All of which are " << lowest_error << " character(s) different." << endl;
    return 0;
}

