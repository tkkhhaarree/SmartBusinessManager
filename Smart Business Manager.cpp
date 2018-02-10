
#include <iostream>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
using namespace std;

COORD coord={0,0};

struct employee{
char empid[30];
char emppass[30];
}E[10];


int e_size=1;

void delay(unsigned int msec){
clock_t goal = msec+clock();
while(goal>clock())
{
}
}

void loading()
{
    coord.X=60;
    coord.Y=20;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    cout<<"-LOADING-";
    for(int i=50;i<=80;i++)
    {coord.X=i;
    coord.Y=22;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    cout<<"|";
    delay(100);
    }
}



void frame(){
    system("cls");
for(int i=10;i<=140;i++){
    coord.X=i;
    coord.Y=5;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    cout<<"-";
}

for(int i=6;i<=45;i++){
    coord.X=140;
    coord.Y=i;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    cout<<"|";
}


for(int i=140;i>=10;i--){
    coord.X=i;
    coord.Y=45;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    cout<<"-";
}

for(int i=44;i>=6;i--){
    coord.X=10;
    coord.Y=i;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    cout<<"|";
}
}



void welcome(int turn){
    frame();
    char id[30],pass[30];
    coord.X=55;
    coord.Y=12;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    cout<<"- WELCOME EMPLOYEE -";
    delay(1000);
    cout<<"\n\n\n\n\t\t\t\t\t LOGIN TO SYSTEM : ";
    cout<<"\n\n\t\t\t\t\t Enter id : ";
    gets(id);
    cout<<"\n\t\t\t\t\t Enter password : ";
    gets(pass);
    int flag=0;
    for(int i=0;i<e_size;i++)
        if(strcmpi(E[i].empid,id)==0 && strcmpi(E[i].emppass,pass)==0)
            flag=1;
    if(flag==1)
        {cout<<" \n\n\t\t USER FOUND.";
        delay(1000);
        }
    else
    {   if(turn<3)
        {cout<<" \n\n\t\t Invalid id password.\n\n\t\t Try again.";
        delay(1000);
        welcome(++turn);
        }
        else
        {
            cout<<" \n\n\t\t Too many tries. System will stop.";
            exit(0);
        }
    }

}

void drive(int,int,int);
void start();
void delivery()

{   frame();
    int arr[10][10],n,i,j,x[10][10];
    coord.X=20;
    coord.Y=12;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    printf("Enter the number of godowns the driver need to pick items from :  ");
    scanf("%d",&n);
    printf("\n\n\n");
    for(i=0;i<n;i++)
        for(j=0;j<n;j++){
                if(i==j)
                    arr[i][j]=0;
           if(i<j)
           {
            cout<<"\t\t\t\t\t Enter distance between Godown "<<(char)(i+65)<<" & "<<(char)(j+65)<<" : ";
            scanf("%d",&arr[i][j]);
            arr[j][i]=arr[i][j];
           }
        }

    for(i=0;i<n;i++)
    {   printf("\n");
        for(j=0;j<n;j++)
     {
         x[i][j]=arr[i][j];
     }
    }

    for(i=0;i<n;i++)
        for(j=1;j<n;j++)
        {
            if(i==0)
                x[i][j]+=x[i][j-1];
            else if(j==0)
                x[i][j]+=x[i-1][j];
            else
            {   int min;
                if(x[i][j-1]<x[i-1][j])
                    min=x[i][j-1];
                else
                    min=x[i-1][j];
                x[i][j]+=min;
            }
        }

    double dist=(double)x[n-1][n-1];
    cout<<"\n\n\n\t\t\t Minimum cost path for route is : "<<dist<<" km";
    cout<<"\n\t\t\t Costing a petrol of Rs. "<<(dist/11)*68.26;
    cout<<"\n\t\t\t Amount transferred to drivers paytm.";
    getch();
    drive(0,n,0);
}



int bin_pack(int wt[],int num,int cap)
{
    int no_of_bins=0,i,j;
    int bin_remaining[num];
    for(i=0;i<num;i++)
        bin_remaining[i]=cap;
    for(i=0;i<num;i++)
    {
        int pos=0,smal=999;
        for(j=0;j<no_of_bins;j++)
        {
            if(bin_remaining[j]>=wt[i] && (bin_remaining[j]-wt[i])<smal)
            {
                pos=j;
                smal=bin_remaining[j]-wt[i];
            }

        }
        if(smal==999)
        {
            bin_remaining[no_of_bins]=cap-wt[i];
            no_of_bins++;
        }
        else
            bin_remaining[pos]-=wt[i];
    }


    return no_of_bins;
}



void drive(int godown,int n,int bins){

    frame();
    coord.X=55;
    coord.Y=12;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    if(godown==0)
        cout<<"TRAVELING FROM SHOP TO A";
    else if(godown==n)
        cout<<"TRAVELLING FROM E TO DESTINATION";
    else
        cout<<"TRAVELLING FROM "<<(char)(godown+64)<<" to "<<(char)(godown+65);
     for(int i=50;i<=80;i++)
    {coord.X=i;
    coord.Y=15;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    cout<<"|";
    delay(100);
    }
   if(godown==n)
    {
        cout<<"\n\n\n\n\t\t\t ALL ITEMS SAFELY DELIVERED TO THE DESTINATION.";
        getch();
        start();
    }
    else{
    cout<<"\n\n\n\n\t\t\t Max capacity of each container in delivery van is 10 units.";
    cout<<"\n\n\t\t\t Enter no of items to be loaded : ";
    int items[10],n_items;
    cin>>n_items;
    cout<<"\n\n\t\t\t Enter quantity of each item : ";
    for(int i=0;i<n_items;i++)
        cin>>items[i];
    int n_container;
    n_container=bin_pack(items,n_items,10);
    cout<<"\n\n\t\t\t No of bins required : "<<n_container;
    if(n_container+bins>20)
        {
            cout<<"\n\n\t\t\t QUANTITY EXCEEDING. HENCE WONT TAKE ITEMS FROM HERE.";
            getch();
            drive(++godown,n,bins);
        }
    else
    {   bins+=n_container;
        cout<<"\n\n\t\t\t ITEMS PICKED UP. TOTAL BINS : "<<bins;
        getch();
        drive(++godown,n,bins);
    }
    }
}

int coins[9]={2000,500,100,50,20,10,5,2,1};
void coin_change(int amount){
    int sum=0;
    while(sum!=amount)
    {
        for(int i=0;i<9;i++)
        {
            if(coins[i]+sum<=amount)
            {
                sum+=coins[i];
                cout<<coins[i]<<" ";
                break;
            }
        }
    }
}


void cashing(){
    frame();
    coord.X=55;
    coord.Y=12;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    cout<<"Enter the amount paid by customer : ";
    int paid,cost,amt;
    cin>>paid;
    cout<<"\n\n\t\t\t\t\t\t Enter cost of items purchased : ";
    cin>>cost;
    amt=paid-cost;
    cout<<"\n\n\t\t\t\t\t\t Amount to be given back to customer : "<<amt;
    cout<<"\n\n\n\t\t\t\t\t\t Give bills of : ";
    coin_change(amt);
    getch();
    start();
}



void start(){
    frame();
    int ch;
    coord.X=55;
    coord.Y=12;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    cout<<"- CASHING & DELIVERY -";
    cout<<"\n\n\n\n\n\n\n\t\t\t\t\t 1. Perform cashing on articles.";
    cout<<"\n\n\n\n\n\t\t\t\t\t 2. Plan the article delivery pattern.";
    cout<<"\n\n\n\n\n\t\t\t\t\t Enter choice : ";
    cin>>ch;
    if(ch==1)
        cashing();
    else if(ch==2)
        delivery();
    else
    {
        cout<<"\n\n\n\n\n\t\t\t\t INVALID CHOICE. RETRY.";
        delay(1000);
        start();

    }
}





int main()
{
    strcpy(E[0].empid,"shubham");
    strcpy(E[0].emppass,"251197");
    loading();
    welcome(1);
    start();
    return 0;
}
