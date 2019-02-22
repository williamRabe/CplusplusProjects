#include <iostream>
#include <string>
using namespace std;

int main() {

  string line;
  size_t pos;

  cout << "Enter text: \n";
  getline (cin, line);
  cout << "You entered: " + line << endl;

  pos = line.find("BFF");
  if (pos!=std::string::npos){
    line.replace (pos,3,"best friend forever");
  }

  pos = line.find("IDK");
  if (pos!=std::string::npos){
    line.replace (pos,3,"I don't know");
  }

  pos = line.find("JK");
  if (pos!=std::string::npos){
    line.replace (pos,2,"just kidding");
  }

  pos = line.find("TMI");
  if (pos!=std::string::npos){
    line.replace (pos,3,"too much information");
  }

  pos = line.find("TTYL");
  if (pos!=std::string::npos){
    line.replace (pos,4,"talk to you later");
  }

  cout << "Expanded: " + line << endl;

   return 0;
}
