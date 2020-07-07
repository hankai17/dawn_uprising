#include <iostream>
using namespace std;

/*
int Grial(int x,int k) //求x!中k因数的个数。
{
    int Ret = 0;
    while (x)
    {
        Ret += x / k;
        x /= k;
    }
    return Ret;
}
int main()
{
    cout << Grial(10, 2) << endl;
    return 0;
}
*/


/*
//如果要求一个n!中k的因子个数，那么必定满足如下的规则。
//即x=n/k+n/k^2+n/k^3...(直到n/k^x小于0);
#include <iostream>
using namespace std;
int Grial(int x, int k)
{
    int count = 0;
    int n = x;
    while (n)
    {
        n &= (n - 1);
        count++;
    }
    return x - count;
}
int main()
{
    cout << Grial(3, 2) << endl;
    return 0;
}
*/

//找出数组中出现次数超过数组一半的数字。
#include <iostream>
using namespace std;
int Grial(int a[], int n) {
    int count=0;
    int key;
    for (int i = 0; i < n; i++) {
        if (count == 0) {
            key = a[i];
            count = 1;
        } else {
            if (key == a[i]) {
                count++;
            } else {
                count--;
            }
        }
    }
    return key;
}

int main()
{
    //int a[] = {1,2,3,4,5,6,3,3,3,3,3};
    int a[] = {3,3,3,4,3,6,3,9,3,0,2};
    cout<<Grial(a, sizeof(a) / sizeof(int))<<endl;
    return 0;
}

#include <iostream>
//上一题的扩展，有3个数字出现次数超过1/4。
using namespace std;
void Grial(int a[], int n)
{
    if (n <= 3)return;
    int count1=0, key1=0;
    int count2=0, key2=0;
    int count3=0, key3=0;
    for (int i = 0; i < n; i++)
    {
        if (!count1 && key2 != a[i] && key3 != a[i])
        {
            count1++;
            key1 = a[i];
        }
        else if (key1 == a[i])
        {
            count1++;
        }
        else  if (key2!=a[i] && key3!=a[i])
        {
            count1--;
        }


        if (!count2 &&key3 != a[i] && key1!=a[i])
        {
            count2++;
            key2 = a[i];
        }
        else if (key2 == a[i])
        {
            count2++;
        }
        else if (key1!=a[i] && key3!=a[i])
        {
            count2--;
        }


        if (!count3 && key1!=a[i] && key2!=a[i])
        {
            count3++;
            key3 = a[i];
        }
        else if (key3 == a[i])
        {
            count3++;
        }
        else if (key1!=a[i] && key2!=a[i])
        {
            count3--;
        }


    }
    cout << key1 << endl;
    cout << key2 << endl;
    cout << key3 << endl;
}

int main()
{
    int a[] = {1,5,5,5,5,2,3,1,2,2,1,1,1,2};
    Grial(a, sizeof(a) / sizeof(int));
    return 0;
}
