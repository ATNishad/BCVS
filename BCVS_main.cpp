#include<iostream>
#include<string>
using namespace std;

class Block{
private:
string data;
string timestamp;
string previous_hash;
string current_hash;

public:
Block(string A,string B,string C) : data(A), timestamp(B), previous_hash(C) {
    hash_generator();
}

void hash_generator(){
    current_hash=data+timestamp+previous_hash;
    cout<<current_hash;
}

};
