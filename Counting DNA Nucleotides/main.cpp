#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    string s;
    unordered_map<char,int> m;

    cin >> s;
    for(char x: s){
        m[x]++;
    }
    printf("%d %d %d %d", m['A'], m['C'], m['G'], m['T']);
    return 0;
}
