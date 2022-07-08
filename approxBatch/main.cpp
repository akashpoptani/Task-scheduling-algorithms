#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

int shgc(int s_index,int e_index,int thgc[])
{
    int sum=0;
    for(int i=s_index;i<=e_index;i++)
            sum+=thgc[i];
    return sum;
}
int spc(int s_index,int e_index,int t3pc[])
{
    int sum=0;
    for(int i=s_index;i<=e_index;i++)
            sum+=t3pc[i];
    return sum;
}

int main() 
{
    ifstream nameread;
    nameread.open("Result.txt");
        int nlayers,temp,nhgc;

        //cout<<"Number of HGCs:"<<endl;
        //cin>>nhgc;
        nhgc=8;
        
        string filename;
    while(nameread.eof()==0)
    {
        nameread>>filename;
        //cout<<filename<<endl;

        ifstream myfile;
        myfile.open(filename);
        string myline;
        myfile>>nlayers;
        //cout<< nlayers<<endl;
        int st3pc=0,sthgc=0;

        int t3pc[nlayers];
        int commtime[nlayers];
        int thgc[nlayers];

        for(int z=0;z<nlayers;z++)
        {
            myfile>>temp;
            t3pc[z]=temp;
            st3pc+=t3pc[z];
        }
        //cout<<st3pc<<endl;

        for(int z=0;z<nlayers;z++)
        {
            myfile>>temp;
            commtime[z]=temp;
        }

        for(int z=0;z<nlayers;z++)
        {
            myfile>>temp;
            thgc[z]=temp;
            sthgc+=thgc[z];
        }
        /*  
        for(int z=0;z<nlayers;z++)
            cout<<t3pc[z]<<endl;
        for(int z=0;z<nlayers;z++)
            cout<<commtime[z]<<endl;
        for(int z=0;z<nlayers;z++)
            cout<<thgc[z]<<endl;
        cout<<nhgc<<endl;
        */

        float T,x,tbatch_ideal;
        /*cout<<st3pc<<endl;
        cout<<sthgc<<endl;*/

        x= (float)st3pc/(float)sthgc;
        //cout<<x<<endl;
    
        T=st3pc/(1- pow((1-x),nhgc));
        //cout<<T<<endl;
    
        int c=nhgc-1;
        //cout<<c<<endl;
        int sum=0,time_taken_by_hgc[nhgc];
        int array_storing_first_layer_index[nhgc];
        int tout;
    
        for(int i=nlayers-1;i>0;i--)    //i>0 because we wont cross first layer
        {
            tbatch_ideal=T*pow((1-x),c);
            //cout<<tbatch_ideal<<endl;
            sum+=thgc[i];
            if(sum>tbatch_ideal)
            {
                array_storing_first_layer_index[c]=i;
                time_taken_by_hgc[c]=sum;
                //cout<<tbatch_ideal<<"\t"<<i<<"\t"<<sum<<endl;
                c--;
                sum=0;
            }
        }

        time_taken_by_hgc[0]=shgc(0,array_storing_first_layer_index[1]-1,thgc);
        //cout<<time_taken_by_hgc[0]<<endl;
        
        
        for (int i = 1; i < nhgc; i++)
        {
            time_taken_by_hgc[i]+= spc(0,array_storing_first_layer_index[i]-1,t3pc);
            time_taken_by_hgc[i]+=commtime[array_storing_first_layer_index[i]-1];
            //cout<<i<<"\t"<<time_taken_by_hgc[i]<<endl;
        }
    
        sort(time_taken_by_hgc,time_taken_by_hgc+nhgc);
        tout=time_taken_by_hgc[nhgc-1];
        cout<<tout<<endl;
        //for(int i= 1;i<nhgc;i++)
            //cout<<array_storing_first_layer_index[i]<<"\n";
    }
}