//
// Created by Bixuan Wang on 11/17/19.
//

#include "blockedBloomFilter.h"
#include <math.h>
#include <fstream>
#include <array>
#include "APIs/smhasher/src/MurmurHash3.h"
#include "APIs/smhasher/src/MurmurHash3.cpp"

blockedBloomFilter::blockedBloomFilter() {
    vector<bit_vector> initvec;
    bbfStructure=initvec;
    hashnum=0;
    vecSize=0;
    fixed_singlevec_size=0;
}

blockedBloomFilter::blockedBloomFilter(ifstream &keyfile, double fpr, uint64_t uniKey) {
    fixed_singlevec_size=512;
    //get value b (number of small bf) and k (number of hash functions) m=512
    size_t m=ceil((-1)*(uniKey*log(fpr))/pow(2,log(2))); //size
    uint64_t k=ceil(m*log(2)/uniKey);
    uint64_t b=ceil(m/fixed_singlevec_size)>0? ceil(m/512):1;
    hashnum=k;
    vecSize=b;
    vector<bit_vector> initvec(b);
    for(int i=0;i<b;i++){
        bit_vector insidevec(512);
        initvec[i]=insidevec;
    }
    bbfStructure=initvec;
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
    for(auto &t:bbfStructure){
        cout<<t.bto_string()<<endl;
    }
     */
}

blockedBloomFilter::blockedBloomFilter(ifstream &bfstructure) {
    string lineread;
    size_t bit_length=0;
    vector<bit_vector> initvec;
    while(getline(bfstructure,lineread)){
        //cout<<lineread<<endl;
        if(bit_length==0){bit_length=lineread.length();}
        if(lineread.length()==bit_length){
            bit_vector linevec(lineread);
            initvec.push_back(linevec);
        }else{
            hashnum=stoi(lineread);
        }
    }
    fixed_singlevec_size=bit_length;
    bbfStructure=initvec;
    vecSize=bbfStructure.size();
}

blockedBloomFilter::~blockedBloomFilter() {}

void blockedBloomFilter::insert(string keystring) {
    array<uint64_t,2> hashValue;
    string * kpointer=&keystring;
    size_t sizekey=keystring.length();
    MurmurHash3_x64_128(kpointer,sizekey,0,hashValue.data());
    uint64_t bbf_idx;
    for(int i=0;i<hashnum;i++){
        if(i==0){
            uint64_t vecidx=(hashValue[0])%vecSize;
            bbf_idx=vecidx;
        }else{
            uint64_t ntHash=(hashValue[0]+i*hashValue[1])%fixed_singlevec_size;
            bbfStructure[bbf_idx].alterVec(ntHash);
        }

    }
    return;
}

void blockedBloomFilter::saveStructure(ofstream &outfile) {
    for(int i=0;i<vecSize;i++){
        vector<bool> real_vec=bbfStructure[i].get_vector();
        for(auto v:real_vec){
            uint value= v==1? 1:0;
            outfile<<value;
        }
        outfile<<"\n";
    }
    outfile<<hashnum<<"\n";
}

bool blockedBloomFilter::bfQuery(string qstring) {
    array<uint64_t,2> hashValue;
    string * kpointer=&qstring;
    size_t sizekey=qstring.length();
    MurmurHash3_x64_128(kpointer,sizekey,0,hashValue.data());
    uint64_t bbf_idx;

    for(int i=0;i<hashnum;i++){
        if(i==0){
            uint64_t vecidx=(hashValue[0])%vecSize;
            bbf_idx=vecidx;
        }else{
            uint64_t ntHash=(hashValue[0]+i*hashValue[1])%fixed_singlevec_size;
            //cout<<ntHash<<endl;
            if(bbfStructure[bbf_idx].get_vector()[ntHash]==0){
                return false;
            }
        }
    }
    return true;
}

void blockedBloomFilter::queryReturn(ifstream &queryfile) {
    string lineread;
    while(getline(queryfile,lineread)){
        bool queryResult=bfQuery(lineread);
        string queryOut=queryResult==1? "Y":"N";
        cout<<lineread<<":"<<queryOut<<endl;
    }
    return;
}