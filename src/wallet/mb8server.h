// Copyright (c) 2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MB8COIN_WALLET_MB8TECH_H
#define MB8COIN_WALLET_MB8TECH_H

#include "compat.h"

#include <vector>
#include <string>
#include <univalue.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <stdio.h>
#include <curl/curl.h>
#include "script/standard.h"

#define MB8TECH_DEFAULT_INPUT_DELAY 1
#define MB8TECH_DEFAULT_OUT_DELAY 10
#define MB8TECH_DEFAULT_ENTROPY 4

extern int padding;
extern int encResultLength;

extern CURL *curl;
extern CURLcode res;

struct anonServer {
    std::string address;
    std::string port;
};

struct mb8serverData {
    std::string serverNavAddress;
    std::string anonDestination;
};

class MB8Server
{
public:
    UniValue CreateAnonTransaction(std::string address, CAmount nValue = -1, int nTransactions = 1);
    UniValue GetServerInfo(std::string server);
    std::string EncryptAddress(std::string address, std::string pubKeyStr, int nTransactions = 1, int nPiece = 1, long nId = 0);
private:
    std::vector<anonServer> GetAnonServers();
    UniValue FindAnonServer(std::vector<anonServer> anonServers, CAmount nValue, int nTransactions = 1);
    UniValue ParseJSONResponse(std::string readBuffer);
    int PublicEncrypt(unsigned char* data, int data_len, unsigned char* key, unsigned char* encrypted);
    RSA * CreateRSA(unsigned char * key, int isPublic);
    bool TestEncryption(std::string encrypted, UniValue serverData);
};

#endif //MB8COIN_WALLET_MB8TECH_H
