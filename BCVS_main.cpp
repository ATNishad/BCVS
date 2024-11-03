#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<algorithm>
#include<chrono>
#include<functional>
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
    string pre_hash_combine=data+"|"+timestamp+"|"+previous_hash;
    std::hash<string> hasher;
    current_hash=to_string(hasher(pre_hash_combine));
    cout<<"current hash:"<<current_hash<<"\n";
}

//getter functions
string get_data(){
    return data;
}

string get_timestamp(){
    return timestamp;
}

string get_previous_hash(){
    return previous_hash;
}

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


void display_chain(){
    for(int i=0 ; i<chain.size() ; i++){
        cout<<"\n";
        cout<<"Block index:"<<i<<"\n";
        cout<<"Data:"<<chain[i].get_data()<<"\n";
        cout<<"Previous block\'s hash:"<<chain[i].get_previous_hash()<<"\n";
        cout<<"Current block\'s hash:"<<chain[i].get_current_hash()<<"\n";
    }
}

void block_verification(){
    for(auto itr = chain.begin()+1; itr!= chain.end() ; ++itr){
        auto p_block = prev(itr);
        if(itr->get_previous_hash() != p_block->get_current_hash() ){
            cout<<"Block verification failed, mismatched at block index "<<distance(chain.begin(),itr)<<"\n";
            return;
            }

        string recomputed_hash = std::to_string(std::hash<string>{}(
            itr->get_data() + "|" + itr->get_timestamp() + "|" + itr->get_previous_hash()));

        if(itr->get_current_hash() != recomputed_hash){
            cout<<"Block verification failed, mismatched at block index "<<distance(chain.begin(),itr)<<"\n";
            return;
        }
        }
        cout<<"All blocks are verified and valid \n";  
    }
};

int main(){
    string data;
    Blockchain BC_main;
    do{
    cout<<"Enter /q to quit \n";
    cout<<"enter data:";
    getline(cin,data);
    if(data == "/q"){
        break;
    }
    BC_main.add_block(data);
    }while(data != "/q");
    BC_main.display_chain();
    cout<<"\n";
    BC_main.block_verification();
}
