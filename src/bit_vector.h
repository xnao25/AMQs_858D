//
// Created by Bixuan Wang on 11/16/19.
//

#ifndef AMQS_BIT_VECTOR_H
#define AMQS_BIT_VECTOR_H

#include <string>
#include <vector>

using namespace std;

class bit_vector {
private:
    string bit_string;
    vector<bool> bitVector;
public:
    bit_vector();
    bit_vector(uint64_t bits);
    bit_vector(string bstring);
    ~bit_vector();
    vector<bool> get_vector();
    void alterVec(uint64_t idx);
    string bto_string();
};


#endif //AMQS_BIT_VECTOR_H
