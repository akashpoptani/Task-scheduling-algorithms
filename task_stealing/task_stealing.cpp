#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

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
        //Input
        ifstream myfile;
        myfile.open(filename);
        string myline;
        myfile>>nlayers;
        //cout<<"nlayers"<< nlayers<<endl;
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
        
        /*for(int z=0;z<nlayers;z++)
            cout<<t3pc[z]<<"  ";
        cout<<endl;
        for(int z=0;z<nlayers;z++)
            cout<<commtime[z]<<"  ";
        cout<<endl;
        for(int z=0;z<nlayers;z++)
            cout<<thgc[z]<<"  ";
        cout<<endl;
        cout<<nhgc<<endl;*/
        
        //Array declaration=>
        int time_taken_by_hgc[nhgc]; 	//time taken by hgc to run layers one after another
        int Layers_running_through_hgc[nhgc][nlayers];

        for (int i = 0; i < nhgc; i++)
        {
            for (int j = 0; j < nlayers; j++)
                Layers_running_through_hgc[i][j]=0;
        }

        int mintime=thgc[0];

        //Start running 1,2, 3 , 4 , … nhgc layers on hgcs available initially So
        for(int i=0;i< nhgc;i++)
        {
            Layers_running_through_hgc[i][0]=i;		//storing layer number
            time_taken_by_hgc[i]= thgc[i];		//storing layer time
            if(time_taken_by_hgc[i]<mintime)
                mintime=thgc[i];
        }

        //for(int i=0;i<nhgc;i++)
        //cout<<time_taken_by_hgc[i]<<endl;

        /*for (int i = 0; i < nhgc; i++)
        {
            for (int j = 0; j < nlayers; j++)
            {
                cout<<Layers_running_through_hgc[i][j]<<"  ";
            }
            cout<<endl;
        }*/

        int lnext=nhgc;
        int j[nhgc];
        for (int i = 0; i < nhgc; i++)
            j[i]=1;
        
        int c=0;
        for(int t=mintime+1;lnext!=nlayers;t=mintime+1)  //looping over time
        {
            for(int i=0;i< nhgc;i++)  //checking if any hgc is free to run other layers(subsequent layers)
            {
                //cout<<"running time"<<t<<"  "<<"hgc time"<<time_taken_by_hgc[i]<<endl;
                if (t>time_taken_by_hgc[i])  //hgc is free at this moment and so is not running any layer
                    {
                        //cout<<commtime[lnext-1]<<endl;
                        //cout<<"hgc time"<<time_taken_by_hgc[i]<<"\t"<<"sum 3pc +hgc"<<spc(0,lnext-1,t3pc)+commtime[lnext-1]<<endl;
                        if(spc(0,lnext-1,t3pc)+commtime[lnext-1]>=time_taken_by_hgc[i])
                        time_taken_by_hgc[i]=spc(0,lnext-1,t3pc)+commtime[lnext-1];
                    time_taken_by_hgc[i]+=thgc[lnext];
                    //cout<<time_taken_by_hgc[i]<<"  "<<thgc[lnext]<<endl;
                    Layers_running_through_hgc[i][j[i]]=lnext;
                    //cout<<"printed layer"<<lnext<<endl;
                    lnext++;
                    j[i]++;
                    break;
                    }
            }
            mintime=time_taken_by_hgc[0];
            //cout<<mintime<<"----"<<endl;
            for(int i=0;i< nhgc;i++)  //checking if any hgc is free to run other layers(subsequent layers)
            {
                //cout<<time_taken_by_hgc[i]<<"  ";
                if(time_taken_by_hgc[i]<mintime)
                    mintime=time_taken_by_hgc[i];
            }
            //cout<<endl;
            //cout<<mintime<<"------"<<endl;
        }
        int sum=time_taken_by_hgc[0];
        for(int i=0;i< nhgc;i++)  //checking if any hgc is free to run other layers(subsequent layers)
            {
                //cout<<time_taken_by_hgc[i]<<"\t";
                if(sum<time_taken_by_hgc[i])
                sum=time_taken_by_hgc[i];
            }
            //cout<<endl;
            //cout<<sthgc<<endl;
            cout<<sum<<endl;
            // for (int i = 0; i < nhgc; i++)
            // {
            //     for (int j = 0; j < nlayers; j++)
            //         cout<<Layers_running_through_hgc[i][j]<<"\t";
            //     cout<<endl;
            // }
    }
    }