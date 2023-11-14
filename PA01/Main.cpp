#include <iostream>
#include <string>

using namespace std;

// Your class SimpleBuffer
template <class T>
class SimpleBuffer{
	private:
		T data_;
	
	public:	
		// Implement your public members
		SimpleBuffer(T data) : data_(data) {}

   T getData() const {
        return data_;
    }

   void setData(const T& data) {
        data_ = data;
    }


};	// Class implementation ends

// Implement your overloaded functions
template <class T>
istream& operator>>(istream& input, SimpleBuffer<T>& buffer) {
    T tmp;
    input >> tmp;
    buffer.setData(buffer.getData() + tmp);
    return input;
}

template <class T>
ostream& operator<<(ostream& output, const SimpleBuffer<T>& buffer) {
    output << "Current data: " << buffer.getData();
    return output;
}
// main() of your program for test
int main() {
	SimpleBuffer<string> buf_str("");
	
	for(int k = 0; k < 3; k++){
		cin >> buf_str;
		cout << buf_str << endl;
	}
	
	SimpleBuffer<int> buf_int(0);
	
	for(int k = 0; k < 5; k++){
		cin >> buf_int;
		cout << buf_int << endl;
	}
	
	return 0;
}