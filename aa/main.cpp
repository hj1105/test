#include <iostream>

using namespace std;

int main()
{
    int&& reff = 5;
    reff=3;
    printf("%d",reff);
    return 0;
}
