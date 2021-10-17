#include <iostream>
#include <string.h>
#include <bitset>
#include <list>
#include <bits/stdc++.h>
#include <iterator>
#include <sstream>

using namespace std;

namespace unsigned_types {
    typedef std::basic_string<unsigned char> string;
}

string toBitString(string message)
{
    string bitString;

    for(size_t i = 0; i < message.size(); i++)
    {
        bitString = bitString + bitset<8>(message.c_str()[i]).to_string();
    }
    return bitString;
}

string doBinaryMath(string num1, string num2, string num3, string num4)
{
    unsigned long num1Num = bitset<32>(num1).to_ulong();
    unsigned long num2Num = bitset<32>(num2).to_ulong();
    unsigned long num3Num= bitset<32>(num3).to_ulong();
    unsigned long num4Num = bitset<32>(num4).to_ulong();

    unsigned long total = num1Num + num2Num + num3Num + num4Num;

    return bitset<32>(total).to_string();
}

string doBinaryMath5(string num1, string num2, string num3, string num4, string num5)
{

    unsigned long num1Num = bitset<32>(num1).to_ulong();
    unsigned long num2Num = bitset<32>(num2).to_ulong();
    unsigned long num3Num= bitset<32>(num3).to_ulong();
    unsigned long num4Num = bitset<32>(num4).to_ulong();
    unsigned long num5Num = bitset<32>(num5).to_ulong();
   
    unsigned long total = num1Num + num2Num + num3Num + num4Num + num5Num;

    return bitset<32>(total).to_string();
}

string doBinaryMath2(string num1, string num2)
{
    unsigned long num1Num = bitset<32>(num1).to_ulong();
    unsigned long num2Num = bitset<32>(num2).to_ulong();

    unsigned long total = num1Num + num2Num;

    return bitset<32>(total).to_string();
}



string padding(string bitStringMessage)
{
    int len = bitStringMessage.size();
    bool loop = true;
    int count = 0;
    string newMessage = bitStringMessage;

    while(loop)
    {
        if((len + 1 + count + 64) % 512 == 0)
        {
            string temp = "1";
            for(int i = 0; i < count; i++)
            {
                temp = temp + "0";
            }

            newMessage = newMessage + temp;
            loop = false;
        }
        else
        {
            count++;
        }

    }
    string lenInBinary = bitset<64>(len).to_string();
    
    newMessage = newMessage + lenInBinary;
    return newMessage;
}

string shiftRight(string message, int num)
{
    string temp;
    for(int i = 0; i < num; i++)
    {
        temp = temp + '0';
    }

    for(int j = 0; j < (message.size() - num); j++)
    {
        temp = temp + message[j];
    }

    return temp;
}

string leftRotate(string message, int num)
{
    reverse(message.begin(), message.begin()+num);
    reverse(message.begin()+num, message.end());
    reverse(message.begin(), message.end());

    return message;
}

string rightRotate(string message, int num)
{
    return leftRotate(message, message.size() - num);
}

string sigma0(string message)
{
    string rotr7 = rightRotate(message, 7);
    string rotr18 = rightRotate(message, 18);

    string temp;
    for(int i = 0; i < 32; i++)
    {
        temp = temp + to_string((rotr7[i] ^ rotr18[i]));
    }

    string shift3 = shiftRight(message, 3);

    string temp2;
    for(int j = 0; j < 32; j++)
    {
        temp2 = temp2 + to_string((temp[j] ^ shift3[j]));
    }

    return temp2;
}

string sigma1(string message)
{
    string rotr17 = rightRotate(message, 17);
    string rotr19 = rightRotate(message, 19);

    string temp;
    for(int i = 0; i < 32; i++)
    {
        temp = temp + to_string((rotr17[i] ^ rotr19[i]));
    }

    string shift10 = shiftRight(message, 10);

    string temp2;
    for(int j = 0; j < 32; j++)
    {
        temp2 = temp2 + to_string((temp[j] ^ shift10[j]));
    }

    return temp2;
}

string uppercaseSigma1(string message)
{
    string rotr6 = rightRotate(message, 6);
    string rotr11 = rightRotate(message, 11);

    string temp;
    for(int i = 0; i < 32; i++)
    {
        temp = temp + to_string((rotr6[i] ^ rotr11[i]));
    }

    string rotr10 = rightRotate(message, 10);

    string temp2;
    for(int j = 0; j < 32; j++)
    {
        temp2 = temp2 + to_string((temp[j] ^ rotr10[j]));
    }

    return temp2;
}

string ch(string x, string y, string z)
{
    bitset<32> bitsX = bitset<32>(x);
    bitset<32> bitsY = bitset<32>(y);
    bitset<32> bitsZ = bitset<32>(z);

    
    bitset<32> andGate = bitsX & bitsY;
    bitset<32> notAndGate = (~bitsX)& bitsZ;
    

    bitset<32> xorGate = andGate ^ notAndGate;

    string temp = xorGate.to_string();

    return temp;

}

string maj(bitset<32> a, bitset<32> b, bitset<32> c)
{
    bitset<32> majority = (a & b) ^ (a & c) ^ ( b & c);

    return majority.to_string();
}


vector<string> parsingPaddedMessage(string paddedBitString)
{
     vector<string> parsedMessage;

     int count = 0; 

     for(int i = 0; i < 16; i++)
     {
        string temp;

        for(int j = count; j < (count + 32); j++)
        {
            temp = temp + paddedBitString[j];
        }

        parsedMessage.push_back(temp);
        count += 32;

     }

     for(int j = 16; j < 64; j++)
     {
         string sigmaFirst = sigma1(parsedMessage[j-2]);
         string w7 = parsedMessage[j-7];
         string sigmaZero = sigma0(parsedMessage[j-15]);
         string w16 = parsedMessage[j -16];

        string totalString = doBinaryMath(sigmaFirst, w7, sigmaZero, w16);
        parsedMessage.push_back(totalString);

     }

     return parsedMessage;

}


string sha256(string message)
{

    unsigned int h0 = 0x6a09e667;
    unsigned int h1 = 0xbb67ae85;
    unsigned int h2 = 0x3c6ef372;
    unsigned int h3 = 0xa54ff53a;
    unsigned int h4 = 0x510e527f;
    unsigned int h5 = 0x9b05688c;
    unsigned int h6 = 0x1f83d9ab;
    unsigned int h7 = 0x5be0cd19;

    vector<unsigned int> k = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
    
    string bitString = toBitString(message);
    string paddedString = padding(bitString);
    bool test = true;
    int count = 0;
    int remainingLen = 0;
    int y = 0;
    while(paddedString[y])
    {
        remainingLen++;
        y++;
    }

    
    while(test)
    {
        remainingLen = remainingLen - 512;
        count++;

        if(remainingLen == 0)
        {
            test = false;
        }
    }

    vector<vector<string>> listOfParsedChunks;

    for(int i = 0; i < count; i++)
    {
        
        string currentString = paddedString.substr((i*512), ((i+1)*512));
        vector<string> parsed = parsingPaddedMessage(currentString);
        listOfParsedChunks.push_back(parsed);

        unsigned int a = 0x6a09e667;
        unsigned int b = 0xbb67ae85;
        unsigned int c = 0x3c6ef372;
        unsigned int d = 0xa54ff53a;
        unsigned int e = 0x510e527f;
        unsigned int f = 0x9b05688c;
        unsigned int g = 0x1f83d9ab;
        unsigned int h = 0x5be0cd19;

        for(int j = 0; j < 63; j++)
        {
            
            string bigSigma1 = uppercaseSigma1(bitset<32>(e).to_string());
            string cH = ch(bitset<32>(e).to_string(), bitset<32>(f).to_string(), bitset<32>(g).to_string());
            string temp1 = doBinaryMath5(bitset<32>(h).to_string(), bigSigma1, cH, bitset<32>(k[j]).to_string(), parsed[j]);

            string sigmaZero = sigma0(bitset<32>(a).to_string());
            string majority = maj(a, b, c);
            string temp2 = doBinaryMath2(sigmaZero, majority);


            h = g;
            g = f;
            e = e;
            e = d + int(bitset<32>(temp1).to_ulong());
            d = c;
            c = b;
            b = a;
            a = int(bitset<32>(temp1).to_ulong()) + int(bitset<32>(temp2).to_ulong());
        }

        h0 = h0 + a;
        h1 = h1 + b;
        h2 = h2 + c;
        h3 = h3 + d;
        h4 = h4 + e;
        h5 = h5 + f;
        h6 = h6 + g;
        h7 = h7 + h;


    }

    std::stringstream h0String;
    h0String << std::hex << h0;

    std::stringstream h1String;
    h1String << std::hex << h1;

    std::stringstream h2String;
    h2String << std::hex << h2;

    std::stringstream h3String;
    h3String << std::hex << h3;

    std::stringstream h4String;
    h4String << std::hex << h4;

    std::stringstream h5String;
    h5String << std::hex << h5;

    std::stringstream h6String;
    h6String << std::hex << h6;

    std::stringstream h7String;
    h7String << std::hex << h7;


    return h0String.str() + h1String.str() + h2String.str() + h3String.str() + h4String.str() + h5String.str() + h6String.str() + h7String.str();
}

string readFile2(const string &fileName)
{
    ifstream ifs(fileName.c_str(), ios::in | ios::binary | ios::ate);

    ifstream::pos_type fileSize = ifs.tellg();
    ifs.seekg(0, ios::beg);

    vector<char> bytes(fileSize);
    ifs.read(bytes.data(), fileSize);

    return string(bytes.data(), fileSize);
}

int main()
{
    string message = readFile2("message.txt");
   cout << message << endl;

   cout << sha256(message) << endl;
   
    return 0;
}