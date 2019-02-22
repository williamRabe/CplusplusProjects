//Wm. Rabe
// Project 6

#include <iostream>


using namespace std;

int prompt_for_input(void);
string int_to_string(int);
string output(int);


int main(){

  int input;
	string out;

  input = prompt_for_input();

  while(input >= 0){
		if(input == 0){
			cout << "Zero"<< endl;
			input = prompt_for_input();
		}
		out = output(input);
    cout << out << endl;
    input = prompt_for_input();
    if(input == -1){ // "exit" value
      return 0;
    }
  }

  return 0;
}

int prompt_for_input(void){
  int num;
  cout << "Please enter a Number between 0 and 2 Billion:" << endl;
  cout << "Enter \"-1\" to stop." << endl;
  cin >> num;

  // screens for bad input, lets user know it was bad, asks for good input;
  while(num < -1 || num > 2000000000){
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
    case 30: return "thirty"; break;
    case 40: return "fourty"; break;
    case 50: return "fifty"; break;
    case 60: return "sixty"; break;
    case 70: return "seventy"; break;
    case 80: return "eighty"; break;
    case 90: return "ninety"; break;

    default: return "not";

  }

}

string output(int userNum){
  bool tens_, mils, thous;

  string longhandOut;
  string buf;
  int number[10];

  number[9] = userNum % 10; // ones
  number[8] = userNum % 100; // tens
  if(number[8] > 20){
    number[8] = number[8] - (number[8] % 10); // makes tens value a multiple of 10.
  } else {
    number[9] = 0;
  }
  userNum /= 100;
  number[7] = userNum % 10; // hundreds
  userNum /= 10;
  number[6] = userNum % 10; // thousands
  number[5] = userNum % 100; // ten thousands
  if(number[5] > 20){
    number[5] = number[5] - (number[5] % 10); // makes ten-thou value a multiple of 10.
  } else {
    number[6] = 0;
  }
  userNum /= 100;
  number[4] = userNum % 10; // hundred thousands
  userNum /= 10;
  number[3] = userNum % 10; // millions
  number[2] = userNum % 100; // ten millions
  if(number[2] > 20){
    number[2] = number[2] - (number[2] % 10); // makes ten-mil value a multiple of 10.
  } else {
    number[3] = 0;
  }
  userNum /= 100;
  number[1] = userNum % 10; // hundred millions
  userNum /= 10;
  number[0] = userNum % 10; // billions

  (number[3] > 0 || number[2] > 0 || number[1] > 0) ? mils = true : mils = false;
  (number[6] > 0 || number[5] > 0 || number[4] > 0) ? thous = true : thous = false;

  for(int i = 0; i < 10; i++){
    buf = int_to_string(number[i]);

    if(buf != "not"){

      longhandOut += buf;

      if(i == 0){
        longhandOut += " billion ";
      }

      if(i == 1 || i == 4 || i == 7){
        longhandOut +=" hundred ";
      }

    }

    if(i == 3){
      if(mils){
        longhandOut += " million ";
      }
    }

    if(i == 6){
      if(thous){
        longhandOut += " thousand ";
      }
    }

  }



  return longhandOut;

}
