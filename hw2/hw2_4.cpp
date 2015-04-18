#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <assert.h>
#include <string>
#include <ctime>
#define UMAX 23907635
#define LMAX 149639105

using namespace std;
struct ad_property
{
    unsigned long long int DisplayURL;
    int AdvertiseID;
    int KeywordID;
    int TitleID;
    int DescriptionID;
    int Click;
    int Impression;
    double CIratio;
};
typedef struct ad_property Ad_Property;
struct data
{
    int AdID;
    int Position;
    int Depth;
    int QueryID;
    Ad_Property Property;
};
typedef struct data Data;
struct border
{
    int left;
    int right;
};
typedef struct border Border;
struct command
{
    string s;
    int array[5];
    double d;
};
typedef struct command Command;
typedef vector<Data> D;
vector<D> *Dvptr = new vector<D> (UMAX); //the data structure

bool compare( const Data d1, const Data d2)
{
    if( d1.AdID == d2.AdID )
    {
        if( d1.QueryID == d2.QueryID)
        {
            if( d1.Position == d2.Position )
            {
                if( d1.Depth == d2.Depth )
                {
                    if(d1.Property.Click == d2.Property.Click)
                    {
                        if(d1.Property.Impression == d2.Property.Impression)
                        {
                            return d1.Property.CIratio < d2.Property.CIratio;
                        }
                        else
                        return d1.Property.Impression < d2.Property.Impression;
                    }
                    else
                    return d1.Property.Click < d2.Property.Click;
                }
                else
                return d1.Depth < d2.Depth;
            }
            else
            return d1.Position < d2.Position;
        }
        else
          return d1.QueryID < d2.QueryID;
    }
    else
    return d1.AdID < d2.AdID;
}
bool compare2( const Data d1, const Data d2)
{
    if( d1.AdID == d2.AdID)
    {
        if(d1.Property.AdvertiseID == d2.Property.AdvertiseID)
     {
        if( d1.Property.KeywordID == d2.Property.KeywordID )
        {
            if( d1.Property.TitleID == d2.Property.TitleID )
            {
                if( d1.Property.DescriptionID == d2.Property.DescriptionID )
                {
                    return d1.Property.DisplayURL < d2.Property.DisplayURL;
                }
                else return d1.Property.DescriptionID < d2.Property.DescriptionID;
            }
            else
              return d1.Property.TitleID < d2.Property.TitleID;
        }
        else
          return d1.Property.KeywordID < d2.Property.KeywordID;
    }
    else
       return d1.Property.AdvertiseID < d2.Property.AdvertiseID;
    }
    else
       return d1.AdID < d2.AdID;
}
Border find_border(int left,int right,int mid,D *d, char var,int key)
{
    int left_mid,right_mid;
    int flag = 1;
    int temp_mid;
    temp_mid = mid;
    Border B;
    B.left = left;
    B.right = right;
    //printf("debug find border %d %d %d %c\n",left,mid,right,var); //dubeg
    while( flag == 1 && ( mid > left ) ) //flag is use to jump out the while loop and mid > left for efficiency besides mid-1 may lead to error
    {
        left_mid = (left+mid)/2;
        switch(var)
        {
            case 'a':
            {
                if( (*d)[mid-1].AdID != key ) // mid-1 isn't key implying mid is the border
                {
                    B.left = mid;             // so left border = mid
                    flag = 0;                 // jump out the while loop
                }
                else if( (*d)[left].AdID == key ) //the leftest side is key implying left is the border
                {
                    B.left = left;           // so left border = left
                    flag = 0;                // jump out the while loop
                }
                else
                {
                    if( (*d)[left_mid].AdID == key) //use binary serach!
                      mid = left_mid;
                    else
                    {
                        mid--;
                        left = left_mid+1;
                    }
                }
            }
            break;
            case 'q':
            {
               if( (*d)[mid-1].QueryID != key )
               {
                   B.left = mid;
                   flag = 0;
               }
               else if( (*d)[left].QueryID == key )
               {
                   B.left = left;
                   flag = 0;
               }
               else
               {
                   if( (*d)[left_mid].QueryID == key )
                    mid = left_mid;
                   else
                   {
                       mid--;
                       left = left_mid+1;
                   }
               }
            }
            break;
            case 'p':
            {
              if( (*d)[mid-1].Position != key )
              {
                  B.left = mid;
                  flag = 0;
              }
              else if( (*d)[left].Position == key )
              {
                  B.left =left;
                  flag = 0;
              }
              else
              {
                  if( (*d)[left_mid].Position == key )
                    mid = left_mid;
                  else
                  {
                      mid--;
                      left = left_mid+1;
                  }
              }
            }
            break;
            case 'd':
            {
              if( (*d)[mid-1].Depth != key )
              {
                  B.left = mid;
                  flag = 0;
              }
              else if( (*d)[left].Depth == key )
              {
                  B.left = left;
                  flag = 0;
              }
              else
              {
                  if( (*d)[left_mid].Depth == key )
                    mid = left_mid;
                  else
                  {
                      mid--;
                      left = left_mid+1;
                  }
              }
            }
            break;
        }
    }
    flag = 1;
    mid = temp_mid;
    while( flag == 1 && ( mid < right ) )//for right side
    {
        right_mid = (right+mid)/2;
        switch(var)
        {
        case 'a':
            {
                if( (*d)[mid+1].AdID != key )
                {
                    B.right = mid;
                    flag = 0;
                }
                else if( (*d)[right].AdID == key )
                {
                    B.right = right;
                    flag = 0;
                }
                else
                {
                    if( (*d)[right_mid].AdID == key )
                        mid = right_mid;
                    else
                    {
                        mid++;
                        right = right_mid-1;
                    }
                }
            }
            break;
        case 'q':
            {
                if( (*d)[mid+1].QueryID != key )
                {
                    B.right = mid;
                    flag = 0;
                }
                else if( (*d)[right].QueryID == key )
                {
                    B.right = right;
                    flag = 0;
                }
                else
                {
                    if( (*d)[right_mid].QueryID == key )
                        mid  = right_mid;
                    else
                    {
                        mid++;
                        right = right_mid-1;
                    }
                }
            }
            break;
        case 'p':
            {
                if( (*d)[mid+1].Position != key )
                {
                    B.right = mid;
                    flag = 0;
                }
                else if( (*d)[right].Position == key )
                {
                    B.right = right;
                    flag = 0;
                }
                else
                {
                    if( (*d)[right_mid].Position == key )
                      mid = right_mid;
                    else
                     {
                         mid++;
                         right = right_mid-1;
                     }
                }
            }
            break;
        case 'd':
            {
                if( (*d)[mid+1].Depth != key )
                {
                    B.right = mid;
                    flag = 0;
                }
                else if( (*d)[right].Depth == key )
                {
                    B.right = right;
                    flag = 0;
                }
                else
                {
                    if( (*d)[right_mid].Depth == key )
                        mid = right_mid;
                    else
                        {
                            mid++;
                            right = right_mid-1;
                        }
                }
            }
            break;
        }
    }
    return B;
}
Border bs(Border B,D *d,char var,int key) //*d = pointer to (*Dvptr)[u] , var = the parameter: a,q,p,d , key = the desire value
{
    int high = B.right;
    int low = B.left;
    int mid;
    int flag = 1;
    while( low < high && flag == 1)
    {
        mid = (low+high)/2;
      switch(var)
      {
        case 'a':
        {
           if( (*d)[mid].AdID < key )
           low = mid+1;
           else if( (*d)[mid].AdID > key )
           high = mid-1;
           else
           {
               B = find_border(low,high,mid,d,var,key);
               flag = 0; //since border is found, we don't need while loop anymore
           }
        }
        break;
        case 'q':
        {
          if( (*d)[mid].QueryID < key )
            low = mid+1;
          else if( (*d)[mid].QueryID > key )
            high = mid-1;
          else
          {
              B = find_border(low,high,mid,d,var,key);
              flag = 0;
          }
        }
        break;
        case 'p':
        {
           if( (*d)[mid].Position < key )
            low = mid+1;
           else if( (*d)[mid].Position > key )
            high = mid-1;
           else
           {
               B = find_border(low,high,mid,d,var,key);
               flag = 0;
           }
        }
        break;
        case 'd':
        {
           if( (*d)[mid].Depth < key )
            low = mid+1;
           else if( (*d)[mid].Depth > key )
            high = mid-1;
           else
           {
               B = find_border(low,high,mid,d,var,key);
               flag = 0;
           }
        }
        break;
      }
    }
    if( low == high )
        B.left = B.right = low;
 //   printf("debug bs border = %d %d\n",B.left,B.right); //debug
    return B;
}
void get(int u,int a,int q,int p,int d) //use binary_search , sort by a q p d
{
    printf("********************\n");
    Border B;
    int low,high,mid;
    int click_sum,impression_sum;

     D *vd = &(*Dvptr)[u];               //initiallize , D = vector<Data>
    click_sum = impression_sum = 0; //initiallize
    B.right = high = ((*Dvptr)[u]).size() -1 ; //initiallize
    B.left = low = 0;               //initiallize
  //  printf("debug get size = %d %d %d",(*Dvptr)[u].size(), B.left,B.right );//debug
    B = bs(B,vd,'a',a);
    B = bs(B,vd,'q',q);
    B = bs(B,vd,'p',p);
    B = bs(B,vd,'d',d);
    for( int i = B.left ; i <= B.right ; i++ )
    {
        click_sum += (*Dvptr)[u][i].Property.Click;
        impression_sum += (*Dvptr)[u][i].Property.Impression;
    }
    printf("%d %d\n",click_sum,impression_sum);
    printf("********************\n");
  return;
}
void clicked(int u)
{
    printf("********************\n");
    int size = (*Dvptr)[u].size();
    int last_a,last_q; //to avoid repeat value
    last_a = -1;
    last_q = -1;
    for( int i = 0 ; i < size ; i++ )
    {
        if( (*Dvptr)[u][i].Property.Click  > 0 ) //satisfy the request --> need to process
        {
            if( (*Dvptr)[u][i].AdID == last_a && (*Dvptr)[u][i].QueryID == last_q ) //repeat!
               continue;
            else
               printf("%d %llu\n", (*Dvptr)[u][i].AdID, (*Dvptr)[u][i].QueryID );
            last_a = (*Dvptr)[u][i].AdID;
            last_q = (*Dvptr)[u][i].QueryID;
        }
    }
    printf("********************\n");
    return;
}
void impressed(int u1,int u2)
{
    printf("********************\n");
   int i,j;
   i = j = 0;
   int u1size,u2size;
   int flag = 0 ;  //flag denotes whether there is an AdID impression > 1 from both user
   int can = 1;//the number of continuous AdID
   int last_AdID =-1 ;
   vector<Data> temp(0);
   u1size = (*Dvptr)[u1].size();
   u2size = (*Dvptr)[u2].size();
   std::sort( (*Dvptr)[u1].begin(), (*Dvptr)[u1].end(), compare2 );
   std::sort( (*Dvptr)[u2].begin(), (*Dvptr)[u2].end(), compare2 );
   int A,K,T,D,last_A = -1,last_K = -1,last_T = -1,last_D = -1;
   int llast_A = -1,llast_K = -1,llast_T = -1,llast_D = -1;
   unsigned long long DURL,last_DURL = -1,llast_DURL = -1;
   while( i < u1size && j < u2size )
   {
       if( (*Dvptr)[u1][i].AdID == (*Dvptr)[u2][j].AdID )
       {
           if( (*Dvptr)[u1][i].AdID == last_AdID )
           {
               temp.push_back( (*Dvptr)[u1][i] );
               temp.push_back( (*Dvptr)[u2][j] );
           }
          else if( (*Dvptr)[u1][i].AdID != last_AdID ) //output
          {
              if( !temp.empty() && flag == 1 )
              {
                  printf("%d\n", temp[0].AdID);
                  for( int t = 0 ; t < temp.size() ; t++ )
                  {
                      can = 1;
                      A = temp[t].Property.AdvertiseID;
                      K = temp[t].Property.KeywordID;
                      T = temp[t].Property.TitleID;
                      D = temp[t].Property.DescriptionID;
                      DURL = temp[t].Property.DisplayURL;
                      for( int k = 0 ; k < t ; k++ )
                      {
                          if(  (A == temp[k].Property.AdvertiseID) && (K == temp[k].Property.KeywordID) && (T == temp[k].Property.TitleID) && (D == temp[k].Property.DescriptionID) && (DURL == temp[k].Property.DisplayURL)  )
                           {
                               can = 0;
                               break;
                           }
                      }
                      if( can == 1 )
                      printf("\t%llu %d %d %d %d\n",DURL,A,K,T,D);
                  }
              }
                  //output
                 flag = 0;
                 temp.clear();
                 temp.push_back( (*Dvptr)[u1][i] );
                 temp.push_back( (*Dvptr)[u2][j] );
                 //last_AdID = temp[0].AdID;

          }
          if( (*Dvptr)[u1][i].Property.Impression > 0 && (*Dvptr)[u2][i].Property.Impression > 0 )
              flag = 1;
          last_AdID = (*Dvptr)[u1][i].AdID;
          i++;
          j++;
       }
       else
       {
           if( !temp.empty() && flag ==1 )
           {
                printf("%d\n", temp[0].AdID);
                  for( int t = 0 ; t < temp.size() ; t++ )
                  {
                      can = 1;
                      A = temp[t].Property.AdvertiseID;
                      K = temp[t].Property.KeywordID;
                      T = temp[t].Property.TitleID;
                      D = temp[t].Property.DescriptionID;
                      DURL = temp[t].Property.DisplayURL;
                      for( int k = 0 ; k < t ; k++ )
                      {
                          if(  (A == temp[k].Property.AdvertiseID) && (K == temp[k].Property.KeywordID) && (T == temp[k].Property.TitleID) && (D == temp[k].Property.DescriptionID) && (DURL == temp[k].Property.DisplayURL)  )
                           {
                               can = 0;
                               break;
                           }
                      }
                      if( can == 1 )
                      printf("\t%llu %d %d %d %d\n",DURL,A,K,T,D);
                  }
           }
           flag = 0;
           temp.clear();

           if( (*Dvptr)[u1][i].AdID < (*Dvptr)[u2][j].AdID )
            i++;
           else if( (*Dvptr)[u1][i].AdID > (*Dvptr)[u2][j].AdID)
            j++;
       }
   }
   if( flag ==1 && !temp.empty())
   {
        printf("%d\n", temp[0].AdID);
                  for( int t = 0 ; t < temp.size() ; t++ )
                  {
                      can = 1;
                      A = temp[t].Property.AdvertiseID;
                      K = temp[t].Property.KeywordID;
                      T = temp[t].Property.TitleID;
                      D = temp[t].Property.DescriptionID;
                      DURL = temp[t].Property.DisplayURL;
                      for( int k = 0 ; k < t ; k++ )
                      {
                          if(  (A == temp[k].Property.AdvertiseID) && (K == temp[k].Property.KeywordID) && (T == temp[k].Property.TitleID) && (D == temp[k].Property.DescriptionID) && (DURL == temp[k].Property.DisplayURL)  )
                           {
                               can = 0;
                               break;
                           }
                      }
                      if( can == 1 )
                      printf("\t%llu %d %d %d %d\n",DURL,A,K,T,D);
                  }
   }
   printf("********************\n");
   return;
}
void profit(int a,double theta)
{
    printf("********************\n");
    Border B;
    D *d;
    int impress_sum,click_sum;
    double ratio;
    for( int i = 0 ; i < UMAX ; i++ )
    {
        B.left = 0;
        B.right = (*Dvptr)[i].size()-1;
        d = &(*Dvptr)[i];
        B = bs(B,d,'a',a);
        impress_sum = 0;
        click_sum = 0;
        for( int j = B.left ; j <=B.right ; j++)
        {
            impress_sum += (*Dvptr)[i][j].Property.Impression;
            click_sum += (*Dvptr)[i][j].Property.Click;
        }
        if( click_sum == 0 && impress_sum == 0 )
          ratio = 0;
        else
          ratio = (double)click_sum/impress_sum;
        if( ratio >= theta )
          printf("%d\n",i);
    }
    printf("********************\n");
    return;
}
int main(int argc, char** argv)
{
    Data D;                // to temply save value scanf from file and put into vector
    int Uid ;               // Uid is not member of Data
    FILE *fp;
   // puts(argv[1]);//debug
    fp = fopen(argv[1],"r"); //read from command line
    //fp = fopen("test.txt","r"); //local test
    int i,maxU =-1 ;
    assert( fp != NULL );
    vector<Command> C(0);  // to read commnad from command ine
    Command temp;          // to temply save value from command line and put into vector
    int sizeofC;           // to know how many command should I deal with
    clock_t t1,t2,t3;      //local test test time
    t1 = clock();

  //  printf("initialize done\n"); //debug
    while( ( fscanf(fp,"%d %d %llu %d %d %d %d %d %d %d %d %d",&D.Property.Click ,&D.Property.Impression ,&D.Property.DisplayURL ,&D.AdID ,&D.Property.AdvertiseID,
         &D.Depth, &D.Position,&D.QueryID, &D.Property.KeywordID, &D.Property.TitleID, &D.Property.DescriptionID, &Uid) ) != EOF ) //get data from file
    {
	  //  printf("debug uid = %d\n",Uid); //debug
        if( Uid > maxU )
          maxU = Uid;
      	//printf("debig push\n"); //debug
        ((*Dvptr)[Uid]).push_back(D);
    }
    t2 = clock();
   // printf("time = %lf\n", ( (double)t2-t1 )/CLOCKS_PER_SEC ); //test of time
   // printf("get data done\n"); //debug
    //printf("%d\n",maxU);  //debug
    for( i = 0 ; i < maxU; i++ )//sort
    {
        if( (*Dvptr)[i].empty() )
           continue;
        std::sort((*Dvptr)[i].begin(), (*Dvptr)[i].end(), compare);  //sort in increasing order
    }
    t3 = clock();
   // printf("time = %lf\n", ( (double)t3-t1)/CLOCKS_PER_SEC );
   // printf("sort done\n");  //debug
    while( 1 )             //read command from command line
    {
      //  printf("in while\n"); //debug
        cin >> temp.s;
        if( temp.s == "quit"  )
            break;
        else
        {
            if( temp.s == "get" )
            {
                cin >> temp.array[0];
                cin >> temp.array[1];
                cin >> temp.array[2];
                cin >> temp.array[3];
                cin >> temp.array[4];
            }
            else if( temp.s == "clicked" )
                cin >> temp.array[0];
            else if( temp.s == "impressed" )
            {
                cin >> temp.array[0];
                cin >> temp.array[1];
            }
            else if( temp.s == "profit" )
            {
                cin >> temp.array[0];
                cin >> temp.d;
            }
            else //local test
            {
                cout << "wrong";
                break;
            }
            C.push_back(temp);
        }
       // cout << "success read\n" ; //debug
    }
    sizeofC = C.size();
    //printf("get command  done\n");  //debug
    for( i = 0 ; i < sizeofC ; i++ ) //after reading, now process those command
    {
        if( C[i].s == "get"  )
            get(C[i].array[0],C[i].array[1],C[i].array[2],C[i].array[3],C[i].array[4]);
        else if( C[i].s == "clicked"  )
            clicked(C[i].array[0]);
        else if( C[i].s == "impressed" )
            impressed(C[i].array[0],C[i].array[1]);
        else if( C[i].s == "profit" )
            profit(C[i].array[0],C[i].d);
    }
    delete Dvptr;
    return 0;
}
//impressed has problem
