#pragma once
#include <cstring>
#include <random>

class BankCheck {
public:
    char verificationCode[4] = " ";
    double sum = 0.0;

    BankCheck() = default;
    BankCheck(const char* code, double sum) {
        strcpy(verificationCode, code);
        this->sum = sum;
    }

    ~BankCheck() = default;

    const char* getVerificationCode() const {
        return verificationCode;
    }

    double getSum() const {
        return sum;
    }

    static void generateVerificationCode(char* code) {
        static const char symbolsToUse[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        for (int i = 0; i < 3; i++) {
            code[i] = symbolsToUse[rand() % (sizeof(symbolsToUse) - 1)];
        }
        code[3] = '\0';
    }

    void setCode() {
        generateVerificationCode(verificationCode);
    }

    void setCode(const char* code) {
        strcpy(verificationCode, code);
    }

    void setSum(double sum) {
        if(sum > 0) {
            this->sum = sum;
        }
    }
};
