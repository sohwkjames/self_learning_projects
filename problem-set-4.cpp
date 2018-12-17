#include <iostream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <math.h>

using namespace std;

//--------//
// TASK 1 //
//--------//

char shift_char(char c, int n) {
    // handle cases where n > 26;
    if(n > 26){
        n = n % 26;
    }
    else if (n < -26){
        n = n % 26;
    }

    // handle cases where c is a capital letter. 
    if(c >= 65 && c <= 90){
        if(c + n < 65){
            c = c + (90-65);
        }
        else if (c + n > 90){
            c = c - (90-65);
        }
        else{
            c = c + n;
        }
        return c;
    }


    // handle cases where c is not capital letter.
    if(c >= 97 && c <= 122){
        if(c + n < 97){ // when n is negative
            c = c + n + (26);
        }
        else if (c + n > 122){
      //      cout << "value of c: " << c << "  value of n  " << n << endl;
            c = c + n -  (123-97);
            
        }
        else{
            c = c + n;
        }
        return c;
    }

        //return (c+n);

    return c;
}
    


string &rotate(string &s, int n) {
    // takes a string, and rotates the string by n places.
    // initialise a blank string
    string my_return = "";
    // handle n > s.size()
    if (abs(n) > s.size()){
        n = n % s.size();
    }
    //handle n < 0;
    if (n < 0){
        n = s.size() + n;
         //   cout << "n is :" << n << endl;
    }

    // grab all strings after n, and before wrapping
    for (int i = n; i < s.size(); i++){ 
        my_return.push_back(s[i]); 
    }
    // grab the text after wrapping. grab all characters up to n-1.
    for (int i = 0; i < n; i ++){
        my_return.push_back(s[i]);
    }
    // delete all chars in s
    s = "";
    // push all chars from my_return into s
    for(int i = 0; i < my_return.size(); i++){
        s.push_back(my_return[i]);
    }
    return s;

}



//--------//
// TASK 2 //
//--------//

string &caeser(string &s, int n) {
    // takes a string, and encrypts each letter with n. use shift_char. this function should modify the variable passed into it.
    // define a new string to hold encrpyted string
    string my_return;
    
    for(int i = 0; i < s.size(); i++){
        my_return.push_back(shift_char(s[i], n));
    }
    //replace s with my_return
    s = my_return;
    return s;
}



//--------//
// TASK 3 //
//--------//
int alphabet_indexer(char c){
    // returns what index 0-25 a given alphabet is
    string my_abc = "abcdefghijklmnopqrstuvwxyz"; 
    // force c to be lowercase
    if(c >= 65 && c <= 90){
       
        c = c + (97-65);
        }
    for (int i = 0; i < my_abc.size(); i ++){
        if (c == my_abc[i]){
            return i;
        }
        else{
        }
    }
    return 0;
}

string &substitute(string &s, const string key) {
    
    string my_abc = "abcdefghijklmnopqrstuvwxyz"; 
    int my_uppercase = 0; // boolean value to track if a character needs to be uppercase
    // loop through the input s
    for(int i = 0; i < s.size(); i ++){
        my_uppercase = 0;
        // if character is uppercase, force to be lowercase. If not an alphabet, do nothing.
        if(s[i] >= 65 && s[i] <= 90){
            s[i] = s[i] + (97-65);
            my_uppercase = 1;
            }
        // find the index of the alphabet of current letter (a = 0, b = 1 etc).
        for (int j = 0; j < my_abc.size(); j ++){ 
            if(s[i] == my_abc[j]){
         //       cout << "Mapping " << s[i] << " to " << key[j] << endl;
                s[i] = key[j]; // map a character of s to our key
                s[i] = s[i] -  ( my_uppercase * (97-65) ); // if char no need to be uppercase, multiply by 0. 
                break;

            }
        }
    }
    

    return s;
}


string &unsubstitute(string &s, const string key) {

    string my_abc = "abcdefghijklmnopqrstuvwxyz"; 
    int my_uppercase = 0; // boolean value to track if a character needs to be uppercase
    // loop through the input s
    for(int i = 0; i < s.size(); i ++){
        my_uppercase = 0;
        // if character is uppercase, force to be lowercase. If not an alphabet, do nothing.
        if(s[i] >= 65 && s[i] <= 90){
            s[i] = s[i] + (97-65);
            my_uppercase = 1;
            }
        // find the index of the alphabet of current letter searching through the key
        for (int j = 0; j < key.size(); j ++){ // j tracks which position we are in the key 
            if(s[i] == key[j]){
            //    cout << "Mapping " << s[i] << " to " << my_abc[j] << endl;
                s[i] = my_abc[j]; // map a character of s to our key
                s[i] = s[i] -  ( my_uppercase * (97-65) ); // if char no need to be uppercase, multiply by 0. 
                break;

            }
        }
    }
    

    return s;

}



//--------//
// TASK 4 //
//--------//

string &vigenere(string &s, vector<int> key) {
    
    string my_return = "";
    string temp_string = s;

    int key_index = 0;
    for(int i = 0; i < temp_string.size(); i++){
    
        my_return.push_back(shift_char(temp_string[i], key[key_index]));

       // cout << key[key_index] << " " ;
        key_index = key_index + 1;
        if (key_index + 1 > key.size()){
            key_index = 0;
        
        }
    }
    s = my_return;
    return s;
}



string &unvigenere(string &s, vector<int> key) {
    // modify key: all negative become positive, all positve become negative.
    for(int i = 0; i < key.size(); i ++){
        key[i] = key[i] * -1;
    }
    
    string my_return = "";
    string temp_string = s;

    int key_index = 0;
    for(int i = 0; i < temp_string.size(); i++){
    
        my_return.push_back(shift_char(temp_string[i], key[key_index]));

       // cout << key[key_index] << " " ;
        key_index = key_index + 1;
        if (key_index + 1 > key.size()){
            key_index = 0;
        
        }
    }
    s = my_return;


    return s;
}


//--------//
// TASK 5 //
//--------//
void freq(string s) {
    vector<int> key = {};
    for(int i = 0; i <= 26; i++){ // create a size 26 vector of 0's
        key.push_back(0);
    }
    
    // make all capital letters in s into lowercase letters
    for(int i = 0; i < s.size(); i ++){
        // if character is uppercase, force to be lowercase. If not an alphabet, do nothing.
        if(s[i] >= 65 && s[i] <= 90){
            s[i] = s[i] + (97-65);
        }
    }
    
//   for (int i = 0; i < s.size(); i++){
//       cout << s[i];
//   }
    
    
    for(int i = 0; i < s.size(); i++){ 
        if(s[i] >=97 && s[i] <= 122){ // if a character in string is a lowercase alphabet, grab demical of the alphabet
            key[s[i] - 97] = key[s[i] - 97] +1;  // if character is "a", +=1  to key[0].
        }
   }
    string my_abc = "abcdefghijklmnopqrstuvwxyz";
    
    for(int i = 0; i <26; i++){
        
        cout << my_abc[i] << ":" << key[i];
        if(i != 25){
            cout << " ";
        }
    }
}




// Main Function
int main(void) {
    string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit!";
  //  string text2 = "abcdefgh";
  //  string key = "phqgiumeaylnofdxjkrcvstzwb";
   vector<int> vkey = {7, 5, -6, 22, -13, 6};  // requires latest Mingw installed to work

    // Uncomment to test the different functions
  //  cout << shift_char('m', -13) << endl;
  //   cout << shift_char('c', -2) << endl;

    // cout << rotate(text2, 2) << endl;
    //  cout << rotate(text2, -2) << endl;

 //    cout << caeser(text, 3) << endl;
    // cout << caeser(text, -3) << endl;
   // string text_james = "hado";
    // cout << substitute(text, key) << endl;
    // cout << unsubstitute(text, key) << endl;

  // cout << vigenere(text, vkey) << endl;
     
   // cout << unvigenere(text, vkey) << endl;

     freq(text);

    return 0;
}
