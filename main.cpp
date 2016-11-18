#include "HashDictionary.cpp"
using namespace std;


string randomStrGen(int length) {
    static string charset = "abcdefghijklmnopqrstuvwxyz";
    string result;
    result.resize(length);

    for (int i = 0; i < length; i++) {
        result[i] = charset[rand() % charset.length()];
    }
    return result;
}

int main() {
    Dictionary *hashDictionary = new Dictionary();
    for (int i = 0; i < 20; i++){
        string x = randomStrGen(rand() % 12 + 1);
        hashDictionary->AddEntry(x);
    }
    return 0;
}

