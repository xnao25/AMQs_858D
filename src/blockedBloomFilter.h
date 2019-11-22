//
// Created by Bixuan Wang on 11/17/19.
//

#ifndef AMQS_BLOCKEDBLOOMFILTER_H
#define AMQS_BLOCKEDBLOOMFILTER_H


#include "bit_vector.h"
#include <iostream>

class blockedBloomFilter {
private:
    vector<bit_vector> bbfStructure;
    uint64_t hashnum;
    uint64_t vecSize;
    uint64_t fixed_singlevec_size;
public:
    blockedBloomFilter();
    blockedBloomFilter(ifstream &keyfile, double fpr, uint64_t uniKey);
    blockedBloomFilter(ifstream &bfstructure);
    ~blockedBloomFilter();
    void insert(string keystring);
    void saveStructure(ofstream &outfile);
    bool bfQuery(string qstring);
    void queryReturn(ifstream &queryfile);
};


#endif //AMQS_BLOCKEDBLOOMFILTER_H
