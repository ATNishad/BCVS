#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<chrono>
using namespace std;

const string timer() {
        const auto now=chrono::system_clock::now();
        time_t t=chrono::system_clock::to_time_t(now);
        string timestamp=std::ctime(&t);
        timestamp.pop_back();
        return timestamp;
}

class Block{
private:
string data;
string timestamp;
string previous_hash;
string current_hash;

public:
//constructor
Block(string A,string B,string C) : data(A), timestamp(B), previous_hash(C) {
    hash_generator();
}

//hash_gen function
void hash_generator(){
    current_hash=data+"|"+timestamp+"|"+previous_hash;
    cout<<"current hash:"<<current_hash<<"\n";
}

//getter function
string get_current_hash(){
    return current_hash;   
}

};

class Blockchain{
private:
vector<Block> chain;

public:
//constructor
Blockchain(){
    Block gen_blockobj("GENESIS_BLOCK",timer(),"GENESIS_HASH");
    chain.push_back(gen_blockobj);
}

//add block function
void add_block(string data){
    string prev_hash = chain.back().get_current_hash();
    Block new_block_obj(data,timer(),prev_hash);
    chain.push_back(new_block_obj);
}

};

