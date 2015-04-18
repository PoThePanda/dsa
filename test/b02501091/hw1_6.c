#include <stdio.h>
int min(int a, int b)
{
    return a < b ?  a : b ;
}
int max(int a, int b)
{
    return a > b ? a : b;
}
void GCD_By_Reverse_Search(int a, int b)
{
    int i;
    int count = 0;
    for( i = min(a,b) ; i >=0 ; i-- )
    {
        count++;
        if( a%i == 0 && b%i == 0 )
        {
          printf("Case (%d, %d): GCD-By-Reverse-Search = %d, taking %d iterations\n",a,b,i,count);
          break;
        }
    }
    return;
}
void GCD_By_Filter(int a, int b)
{
    int i;
    int tmpa = a;
    int tmpb = b; // save the value for future
    int gcd = 1;
    int count = 0;
    for( i = 2 ; i <= min(a,b) ; i++ )
    {
        count++;
        if( a%i == 0 && b%i == 0 )
        {
            gcd *= i;
            a /= i;
            b /= i;
            i = 1;
        }
    }
     printf("Case (%d, %d): GCD-By-Filter = %d, taking %d iterations\n",tmpa,tmpb,gcd,count);
     return ;
}
void GCD_By_Filter_Faster(int a,int b)
{
    int i;
    int tmpa = a;
    int tmpb = b;
    int gcd = 1;
    int count = 0;
    for( i = 2 ; i <= min(a,b) ; i++ )
    {
        count++;
        if( a%i == 0 && b%i == 0 )
        {
            gcd *= i;
            a /= i;
            b /= i;
            i--;
        }
    }
     printf("Case (%d, %d): GCD-By-Filter-Faster = %d, taking %d iterations\n",tmpa,tmpb,gcd,count);
    return;
}
void GCD_By_Binary(int a,int b)
{
    int m = max(a,b);
    int n = min(a,b);
    int count = 0;
    int ans = 1;
    int temp;
    while( m != 0 && n != 0 )
    {
        count++;
        if( m%2 == 0 && n %2 == 0 )
        {
            ans *= 2;
            m /= 2;
            n /= 2;
        }
        else if( m%2 == 0 )
            m /= 2;
        else if( n%2 == 0 )
            n /= 2;
        if( n > m )
        {
            temp = n;
            n = m;
            m = temp;
        }
        m -= n;
    }
     printf("Case (%d, %d): GCD-By-Binary = %d, taking %d iterations\n",a,b,n*ans,count);
     return;
}
void GCD_By_Euclid(int a,int b)
{
    int m = max(a,b);
    int n = min(a,b);
    int count = 0;
    int tmp;
    while( m % n != 0 )
    {
        count++;
        tmp = n;
        n = m % n;
        m = tmp;
    }
     printf("Case (%d, %d): GCD-By-Euclid = %d, taking %d iterations\n",a,b,n,count);
}
int main(void)
{
    int a,b;
    while(1)
    {
        scanf("%d",&a);
        if( a == 0 )
          break;
        scanf("%d",&b);
        GCD_By_Reverse_Search(a,b);
        GCD_By_Filter(a,b);
        GCD_By_Filter_Faster(a,b);
        GCD_By_Binary(a,b);
        GCD_By_Euclid(a,b);
    }
    return 0;
}
