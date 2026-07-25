#include<iostream>
using namespace std;
int main()
{
    double stress=350;
    double yield=235;

    if(stress>yield)
    { 
        cout<<"材料屈服"<<endl;
    }
    else if(stress>0.8*yield)
    {
        cout<<"材料接近屈服"<<endl;
    }
    else
    {
        cout<<"材料安全"<<endl;
    }
    return 0;
}