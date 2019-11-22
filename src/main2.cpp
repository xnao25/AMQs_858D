#include <iostream>
#include <string>
//#include "bloomFilter.h"
#include "blockedBloomFilter.h"
#include "APIs/smhasher/src/MurmurHash3.h"
#include <array>
#include <fstream>
#include <map>

using namespace std;

int main(int argc, char* argv[]) {

    //bloom filter
    if(argc<2){
        cout<<"---Blocked Bloom Filter Usage---"<<endl;
        cout<<"Build structure:"<<endl;
        cout<<"\t/path/to/bf build -k <key file> -f <fpr> -n <num. distinct keys> -o <output file>"<<endl;
        cout<<"Query:"<<endl;
        cout<<"\t/path/to/bf query -i <input file> -q <queries>"<<endl;
        return 1;
    }

    string command(argv[1]);
    if(command!="build" && command!="query"){
        cout<<"---Blocked Bloom Filter Usage---"<<endl;
        cout<<"Build structure:"<<endl;
        cout<<"\t/path/to/bf build -k <key file> -f <fpr> -n <num. distinct keys> -o <output file>"<<endl;
        cout<<"Query:"<<endl;
        cout<<"\t/path/to/bf query -i <input file> -q <queries>"<<endl;
        return 1;
    }
    map<string,string> input_arguments;
    string mkey;
    for(int i=0;i<argc;i++){
        if(argv[i][0]=='-'){
            mkey=argv[i];
        }else{
            if(mkey==""){continue;}
            if(input_arguments.find(argv[i])==input_arguments.end()){
                input_arguments[mkey]=argv[i];
            }
        }
    }
    if(command=="build"){
        vector<string> required_arguments={"-k","-f","-n","-o"};
        for(auto &ra:required_arguments){
            if(input_arguments.find(ra)==input_arguments.end()){
                cout<<"**Error: not enough input to build structure"<<endl;
                cout<<"---Blocked Bloom Filter Usage---"<<endl;
                cout<<"Build structure:"<<endl;
                cout<<"\t/path/to/bf build -k <key file> -f <fpr> -n <num. distinct keys> -o <output file>"<<endl;
                cout<<"Query:"<<endl;
                cout<<"\t/path/to/bf query -i <input file> -q <queries>"<<endl;
                return 1;
            }
        }
        ifstream keyfile;
        keyfile.open(input_arguments["-k"]);
        double fpr=stod(input_arguments["-f"]);
        uint64_t nkeys=stoi(input_arguments["-n"]);
        ofstream outstructure;
        outstructure.open(input_arguments["-o"]);

        blockedBloomFilter bf1(keyfile,fpr,nkeys);
        bf1.saveStructure(outstructure);
    }
    if(command=="query"){
        vector<string> required_arguments={"-i","-q"};
        for(auto &ra:required_arguments){
            if(input_arguments.find(ra)==input_arguments.end()){
                cout<<"**Error: not enough input to query"<<endl;
                cout<<"---Blocked Bloom Filter Usage---"<<endl;
                cout<<"Build structure:"<<endl;
                cout<<"\t/path/to/bf build -k <key file> -f <fpr> -n <num. distinct keys> -o <output file>"<<endl;
                cout<<"Query:"<<endl;
                cout<<"\t/path/to/bf query -i <input file> -q <queries>"<<endl;
                return 1;
            }
        }
        ifstream structinput;
        structinput.open(input_arguments["-i"]);
        ifstream queryinput;
        queryinput.open(input_arguments["-q"]);

        blockedBloomFilter bf2(structinput);
        bf2.queryReturn(queryinput);
    }


/*
    ifstream testinput;
    testinput.open("testinput.txt");
    ofstream testoutput;
    testoutput.open("testoutput.txt");
    ifstream testinput2;
    testinput2.open("testoutput.txt");
    ifstream testinput3;
    testinput3.open("testqueries.txt");

    blockedBloomFilter bbfTest(testinput,0.01,7);
    bbfTest.saveStructure(testoutput);
    testinput.close();
    testoutput.close();
    blockedBloomFilter bbfTest2(testinput2);
    bbfTest2.queryReturn(testinput3);


*/
    return 0;
}