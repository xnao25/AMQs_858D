//
// Created by Bixuan Wang on 11/16/19.
//

#ifndef AMQS_BLOOMFILTER_H
#define AMQS_BLOOMFILTER_H

#include "bit_vector.h"
#include <iostream>

using namespace std;

class bloomFilter {
private:
bit_vector bfStructure;
size_t bfsize;
uint64_t hashnum;
public:
    bloomFilter();
    bloomFilter(ifstream &keyfile, double fpr, uint64_t uniKey);
    bloomFilter(ifstream &bfstructure);
    ~bloomFilter();
    void insert(string keystring);
    void saveStructure(ofstream &outfile);
    bool bfQuery(string qstring);
    void queryReturn(ifstream &queryfile);
    //vector<bool> bfQFile(ifstream &queryfile);
};


#endif //AMQS_BLOOMFILTER_H
