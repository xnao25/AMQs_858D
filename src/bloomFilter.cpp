//
// Created by Bixuan Wang on 11/16/19.
//

#include "bloomFilter.h"
#include <fstream>
#include <math.h>
#include <array>
#include "APIs/smhasher/src/MurmurHash3.h"
//#include "APIs/smhasher/src/MurmurHash3.cpp"


bloomFilter::bloomFilter() {
    bit_vector bfstruct;
    bfStructure=bfstruct;
    bfsize=0;
    hashnum=0;
}

bloomFilter::bloomFilter(ifstream &keyfile, double fpr, uint64_t uniKey) {
    //Calculate the size m and hash function number k by fpr
    size_t m=ceil((-1)*(uniKey*log(fpr))/pow(2,log(2))); //size
    bfsize=m;
    uint64_t k=ceil(m*log(2)/uniKey); //hash count
    hashnum=k;

    //cout<<"m:"<<m<<endl;
    //cout<<"k:"<<k<<endl;

    //get data from input
    bit_vector initvec(m);
    bfStructure=initvec;
    //generate hash value and bfstructure
    string lineread;
    //vector<string> keys;
    while(getline(keyfile,lineread)){
        /*
        if(find(keys.begin(),keys.end(),lineread)==keys.end()){
            keys.push_back(lineread);
        }
         */
        insert(lineread);
    }
    /*
    for(auto &key_input:keys){
        insert(key_input);
    }
     */
}

bloomFilter::bloomFilter(ifstream &bfstructure) {
    string lineread;
    string bitstring;
    uint64_t hcount;
    uint count=0;
    while(getline(bfstructure,lineread)){
        if(count==0){
            bitstring=lineread;
        }else{
            hcount=stoi(lineread);
        }
        count++;
    }
    bit_vector initvec(bitstring);
    bfStructure=initvec;
    hashnum=hcount;
    bfsize=bitstring.length();
}

bloomFilter::~bloomFilter() {

}

void bloomFilter::insert(string keystring) {
    //generate hash value

    array<uint64_t,2> hashValue;
    string * kpointer=&keystring;
    size_t sizekey=keystring.length();
    MurmurHash3_x64_128(kpointer,sizekey,0,hashValue.data());
    for(int i=0;i<hashnum;i++){
        uint64_t ntHash=(hashValue[0]+i*hashValue[1])%bfsize;
        bfStructure.alterVec(ntHash);
    }
    return;
}

void bloomFilter::saveStructure(ofstream &outfile) {
    vector<bool> real_vec=bfStructure.get_vector();
    for(auto v:real_vec){
        uint value= v==1? 1:0;
        outfile<<value;
    }
    outfile<<"\n";
    outfile<<hashnum<<"\n";
}

bool bloomFilter::bfQuery(string qstring) {
    vector<bool> real_vec=bfStructure.get_vector();
    array<uint64_t,2> hashValue;
    string * kpointer=&qstring;
    size_t sizekey=qstring.length();
    MurmurHash3_x64_128(kpointer,sizekey,0,hashValue.data());
    //cout<<qstring<<endl;
    //cout<<hashValue[0]<<endl;
    //cout<<hashValue[1]<<endl;
    for(int i=0;i<hashnum;i++){
        uint64_t ntHash=(hashValue[0]+i*hashValue[1])%bfsize;
        //cout<<ntHash<<endl;
        if(real_vec[ntHash]==0){
            return false;
        }
    }
    return true;
}

void bloomFilter::queryReturn(ifstream &queryfile) {
    string lineread;
    while(getline(queryfile,lineread)){
        bool queryResult=bfQuery(lineread);
        string queryOut=queryResult==1? "Y":"N";
        cout<<lineread<<":"<<queryOut<<endl;
    }
    return;
}