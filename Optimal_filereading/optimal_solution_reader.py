import math
with open("glpsol_solutions.txt","r") as file:
    data = file.readlines()
file.close()
i=0
while (i<288):
        data_l= data[i].split(':')
        print (data_l)
        if(i%16==0 or i%16==1 or i%16==4 or i%16==5 or i%16==6 or i%16==8 or i%16==9 or i%16==10 or i%16==11):
            i=i+4
            continue
        if(i%16==12):
            i=i-11
            continue
        if(i%16==13):
            i=i-7
            continue
        if(i%16==14):
            i=i-3
            continue
        if(i%16==15):
            i=i+1
            continue