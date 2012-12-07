#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>

using namespace std;

void test_map() {
  string str;
  map<string, int> dat;


  while(cin >> str) {
    dat[str] ++;
  }

  for(map<string, int>::iterator it = dat.begin();
      it != dat.end(); ++it) {
    cout << (*it).first << " -> " << (*it).second << endl;
    cout << it->first << " -> " << it->second << endl;
  }
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cout << "usage: freq_dict flnm" << endl;
    return 1;
  }

  stringstream done;
  ifstream source(argv[1]);
  source >> noskipws;

  if(!source) {
    cout << "problem with file open" << endl;
    return 1;
  }

  string perms("4563897012 \t\r\n.");

  set<char> permset(perms.begin(), perms.end());

  char c;
  int ind = 0;
  bool fail = false;

  while(source >> c) {
    done << c;
    ++ind;

    if(permset.find(c) == permset.end()) {
      fail = true;
      cout << "bad character " << c << " found at index " << ind << " with code " << int((unsigned char)c) << endl;
      
      cout << done.str() << endl;

      return 1;
    }
  }

  cout << "OK" << endl;
  
  return 0;
}
