#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    string s;
    cin >> s;

    std::replace(s.begin(), s.end(), 'T', 'U');

    std::cout << s << std::endl;
    return 0;
}
