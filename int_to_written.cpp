/*Wm. Rabe
program reads in an int between 1 and 1000 and converts it into a Written number
*/

#include <iostream>

using namespace std;

int prompt_for_input(void);
string int_to_string(int);
void output(int);


int main(){

  int input;

  input = prompt_for_input();

  while(input >= 0){
    cout << endl;
    output(input);
    cout << endl;
    input = prompt_for_input();
    if(input == -1){ // "exit" value
      return 0;
    }
  }

  return 0;
}

int prompt_for_input(void){
  int num;
  cout << "Please enter a Number between 1 and 1000:" << endl;
  cout << "Enter \"-1\" to stop." << endl << endl;
  cin >> num;

  // screens for bad input, lets user know it was bad, asks for good input;
  while(num < -1 || num >= 1000){
    cout << "Invalid Input\n\n";
    num = prompt_for_input();
  }

  return num;
}

string int_to_string(int integer){

  switch (integer) {
    case 1: return "one"; break;
    case 2: return "two"; break;
    case 3: return "three"; break;
    case 4: return "four"; break;
    case 5: return "five"; break;
    case 6: return "six"; break;
    case 7: return "seven"; break;
    case 8: return "eight"; break;
    case 9: return "nine"; break;
    case 10: return "ten"; break;
    case 11: return "eleven"; break;
    case 12: return "twelve"; break;
    case 13: return "thriteen"; break;
    case 14: return "fourteen"; break;
    case 15: return "fifthteen"; break;
    case 16: return "sixteen"; break;
    case 17: return "seventeen"; break;
    case 18: return "eightteen"; break;
    case 19: return "nineteen"; break;
    case 20: return "twenty"; break;
    case 30: return "thrirty"; break;
    case 40: return "fourty"; break;
    case 50: return "fifty"; break;
    case 60: return "sixty"; break;
    case 70: return "seventy"; break;
    case 80: return "eighty"; break;
    case 90: return "ninety"; break;

    default: return "not";

  }

}

void output(int num){

    int ones = 0;
    int tens = 0;
    int hundreds = 0;

    string ones_str;
    string tens_str;
    string hundreds_str;


    ones = num % 10;
    hundreds = ((num - tens) % 1000) / 100;

    ones_str = int_to_string(ones);
    hundreds_str = int_to_string(hundreds);

    /* tens needs to either be between 9 and 20 or a value of ten
    i.e.: 20, 30, 40... or else output will be incorrect*/
    tens = num % 100;
    if(tens > 20){
      tens = tens - (tens % 10); // makes tens value a multiple of 10.
    }
    tens_str = int_to_string(tens);

    if(hundreds_str != "not" ){
      cout << hundreds_str << " hundred ";
    }

    if(tens_str != "not" ){
      cout << tens_str;
      if(tens >= 20){
        if(ones_str != "not"){
          cout<< ones_str;
        }
      }
    }


    if(num == 0){
      cout << "zero";
    }

    cout << endl;

}
