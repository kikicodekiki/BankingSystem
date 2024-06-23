#pragma once
#include <cstring>
#include <random>



struct BankCheck {
    char verificationCode[3] = " ";
    double sum = 0.0;

    BankCheck() = default;

    BankCheck(const char* code, double sum) {
        strcpy(verificationCode, code);
        this->sum = sum;
    }

    ~BankCheck() = default;

    const char* getVerificationCode () const {
        return  verificationCode;
    }

    double getSum () const {
        return sum;
    }

    static const char* generateVerificationCode() {
        static int codeSize = 3;

        static const char symbolsToUse[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
        char code[codeSize + 1];

        for (int i = 0; i < codeSize; i++) {
            code[i] = symbolsToUse[rand() % (sizeof(symbolsToUse) - 1)];
        }

        code [codeSize] = '\0';
        return code;
    }

    void setCode () {
        strcpy(verificationCode, generateVerificationCode());
    }

    void setCode(const char* code) {
        strcpy(verificationCode, code);
    }


    double setSum (double sum) {
        if(sum > 0) {
            this->sum = sum;
        }
    }
};
