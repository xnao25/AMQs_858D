//
// Created by Bixuan Wang on 11/16/19.
//

#include "bit_vector.h"

bit_vector::bit_vector() {
    vector<bool> bvec;
    bitVector=bvec;
}

bit_vector::bit_vector(uint64_t bits) {
    vector<bool> bvec(bits);
    for(size_t i=0;i<bits;i++){
        bvec[i]=0;
    }
    bitVector=bvec;
}

bit_vector::bit_vector(string bstring) {
    vector<bool> bvec(bstring.size());
    for(size_t i=0;i<bstring.size();i++){
        bvec[i]= bstring[i]=='1'? 1:0;
    }
    bitVector=bvec;
}

bit_vector::~bit_vector() {

}

vector<bool> bit_vector::get_vector() {
    return bitVector;
}

void bit_vector::alterVec(uint64_t idx) {
    bitVector[idx]=1;
}

string bit_vector::bto_string() {
    string out="";
    for(auto i:bitVector){
        out+= i==1? "1":"0";
    }
    return out;
}
