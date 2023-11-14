#include <iostream>
#include <string>
#include <stack>

using namespace std;

class StringDecoder{
	private:
		string data_;
	// Implement your class here
	bool decode(const string &str) {
		data_.clear();
		size_t idx = 0; //현재위치
		stack<int> s;
		stack<string> stackString;
		string temp; // 현재 해독중인 문자열을 저장하는 임시변수

		if (str.empty()) {  //문자열이 비어있는경우
			data_ = "ERROR: Invalid input";
			return false;
		}

		while (idx < str.length()) {
			if (str[idx] == '{') { //문자열 돌다가 { 를 만날때
				if (idx == 0 || !hexDigit(str[idx - 1])) { //이전문자가 16진수가 아닌경우
					data_ = "ERROR: Invalid input";
					return false;
				}
				//이전문자가 16진수라면
				s.push(hexToInt(str[idx - 1])); //{ 문자가 나왔을때 그 문자를 16진수로 변환하여 스택 s에 저장
				temp.pop_back(); // 중복을 피하기위해 pop
				stackString.push(temp); // 현재까지의 문자열 조각을 stackstring stack에 저장
				temp.clear(); // 새로운 문자열 조각을 만들 준비
			}
			else if (str[idx] == '}') { //}를 만나는 경우
				if (s.empty()) { 
					data_ = "ERROR: Invalid input";
					return false;
				}
				
				string result = stackString.top();
				stackString.pop();

				for (int i = 0; i < s.top(); ++i) { //현재 stack s의 맨 위에는 반복 횟수가 적혀있음
						result += temp;
				}
				s.pop();
				temp = result;
			}
			
			else {
				if (!isValid(str[idx])) {
					data_ = "ERROR: Invalid input";
          return false;
				}
				temp += str[idx];
			}
			idx++;
		}
		data_ = temp;
		return true;
	}

bool hexDigit(const char &ch) {
	return ('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'F');
}
int hexToInt(const char &ch) {
	if ('0' <= ch && ch <= '9') 
		return ch - '0';
	else
		return ch - 'A' + 10;
}

bool isValid(const char &c) {
		string validChars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,!?@#$%^&*";
		return validChars.find(c) != string::npos; //npos는 find 함수를 통해 해당 문자(열)을 찾지 못햇을때 반환되는 상수 (즉, ,find하지 못햇으면 npos가 반환됨) >> isValid 함수에서는 일치하면1 아니면 0아 리턴
}

public:
StringDecoder(){}

friend istream &operator>>(istream &is, StringDecoder &sd) {
		string encodedString;
		is >> encodedString;
		if (!sd.decode(encodedString)) {
				sd.data_ = "ERROR: Invalid input";
		}
		return is;
}

friend ostream &operator<<(ostream &os, const StringDecoder &sd) {
		os << sd.data_;
		return os;
}
};

int main(){
	StringDecoder sd;
	
	// Note:
	// encoded input strings are read from an input file using operator>>
	// your class may store a decoded string in data_ to print it using operator<<
	while(cin >> sd){
		cout << sd << endl;
	}
	
	return 0;
}