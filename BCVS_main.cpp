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
string voter_id;
string candidate;
string timestamp;
string previous_hash;
string current_hash;

public:
//constructor
Block(string A,string B,string C,string D) : voter_id(A), candidate(B),timestamp(C), previous_hash(D) {
    hash_generator();
}

//hash_gen function
void hash_generator(){
    string pre_hash_combine=voter_id+"|"+candidate+"|"+timestamp+"|"+previous_hash;
    std::hash<string> hasher;
    current_hash=to_string(hasher(pre_hash_combine));
    std::cout<<"current hash:"<<current_hash<<"\n";
}

//getter functions
string get_voterid(){
    return voter_id;
}

string get_candidate(){
    return candidate;
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
    Block gen_blockobj("GENESIS_BLOCK","GENESIS_BLOCK",timer(),"GENESIS_HASH");
    chain.push_back(gen_blockobj);
}

//add block function
void add_block(string voter_id,string candidate){
    string prev_hash = chain.back().get_current_hash();
    Block new_block_obj(voter_id,candidate,timer(),prev_hash);
    chain.push_back(new_block_obj);
}

void display_chain(){
    for(int i=0 ; i<chain.size() ; i++){
        cout<<"\n";
        cout<<"Block index:"<<i<<"\n";
        cout<<"Data:"<<chain[i].get_voterid()<<"\n";
        cout<<"Previous block\'s hash:"<<chain[i].get_previous_hash()<<"\n";
        cout<<"Current block\'s hash:"<<chain[i].get_current_hash()<<"\n";
    }
}

void block_verification(){
    for(auto itr = chain.begin()+1; itr!= chain.end() ; ++itr){
        auto p_block = prev(itr);
        if(itr->get_previous_hash() != p_block->get_current_hash() ){
            std::cout<<"Block verification failed, mismatched at block index "<<distance(chain.begin(),itr)<<"\n";
            return;
            }

        string recomputed_hash = std::to_string(std::hash<string>{}(
            itr->get_voterid() + "|" + itr->get_candidate() + "|" + itr->get_timestamp() + "|" + itr->get_previous_hash()));

        if(itr->get_current_hash() != recomputed_hash){
            std::cout<<"Block verification failed, mismatched at block index "<<distance(chain.begin(),itr)<<"\n";
            return;
        }
        }
        std::cout<<"All blocks are verified and valid \n";  
    }

};

int main(){
    string voter_id;
    string candidate;
    Blockchain BC_main;
    
    do{
    std::cout<<"Enter /q to quit \n";
    std::cout<<"enter voter_id:";
    getline(cin,voter_id);
    std::cout<<"Enter candidate to vote:";
    getline(cin,candidate);

    if(voter_id == "/q" || candidate == "/q"){
        break;
    }
    BC_main.add_block(voter_id,candidate);
    }while(voter_id != "/q" || candidate != "/q");
    
    BC_main.display_chain();
    std::cout<<"\n";
    BC_main.block_verification();
}
