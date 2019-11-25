# AMQs_858D
Bloom Filter and Blocked Bloom Filter implementations. (Assignment#2 for CMSC858D-Fall2019)

- [Github Repository: https://github.com/xnao25/AMQs_858D/](https://github.com/xnao25/AMQs_858D/)
----------------------------

## Overview
- This repository contains 2 major programs: Bloom Filter and Blocked Bloom Filter. More information about installation and usage can be found below.
- The hash function used in bloom filter and blocked bloom filter are from [MurmurHash](https://github.com/aappleby/smhasher)
----------------------------

## Install
Prerequisite: C++11
Steps:
 1. Clone this repository to your local directory
 2. `$cd AMQs_858D/src/`
 3. `make` two executable programs will appear: `bf` and `blockedbf`

## Usage
### Bloom Filter
- build: `$./bf build -k <key file> -f <fpr> -n <num. distinct keys> -o <output file>` 
  - This command will build a bloom filter structure and store it into the output file.
  - `-k`: A text file containing all the keys to be inserted into the bloom filter. One key each line.
  - `-f`: The expected false positive rate.
  - `-n`: The expected number of unique keys to be inserted into the bloom filter.
  - `-o`: The path of an output file. The file will be written with the bloom filter structure's bit vector and number of hash functions utilized in construction.
- query: `$./bf query-i <input file> -q <queries>`
  - This command will check if the provided value(s) exist(s) in the structure. Result will be printed as standard output.
  - `-i`: The text file containing bloom filter structure. This usually is the output from the build command containing the bit vector and the number of hash functions utilized in the construction. 
  - `-q`: A text file containing all the queries to be checked.

### Blocked Bloom Filter
- build: `$./blockedbf build -k <key file> -f <fpr> -n <num. distinct keys> -o <output file>` 
  - This command will build a blocked bloom filter structure and store it into the output file.
  - `-k`: A text file containing all the keys to be inserted into the blocked bloom filter. One key each line.
  - `-f`: The expected false positive rate.
  - `-n`: The expected number of unique keys to be inserted into the bloom filter.
  - `-o`: The path of an output file. The file will be written with the blocked bloom filter structure's bit vectors and number of hash functions utilized in construction.
- query: `$./blockedbf query-i <input file> -q <queries>`
  - This command will check if the provided value(s) exist(s) in the structure. Result will be printed as standard output.
  - `-i`: The text file containing blocked bloom filter structure. This usually is the output from the build command containing the bit vector and the number of hash functions utilized in the construction. 
  - `-q`: A text file containing all the queries to be checked.

### Example
- Input file:
```
$cat TestBloomFilter.txt
jdQ6cg2k
g1y9AgEs
sMN
ZZYuMR0
cdJXR
HJ0KF
Hn9v7
LYMpw
Hv9
iCJGuq
```
- Bloom Filter build
```
$./bf build -k TestBloomFilter.txt -f 0.01 -n 10 -o bfStruct.txt
$cat bfStruct.txt
010111000011011000001100111100000001001111100111001000110001011110111111011000100100110110000010
6
```
- Bloom Filter query
```
$cat TestBloomQuery.txt
HJ0KF
kiQlkS
$./bf query -i bfStruct.txt -q TestBloomQuery.txt
HJ0KF:Y
kiQlkS:N
```
