
// HGC

#include <bits/stdc++.h>
using namespace std;
int main()
{

	ifstream ip;
	ip.open("Result.txt");
	ofstream fout;
	fout.open("check.txt");
	while (ip.eof() == 0)
	{
		string filename;
		ip >> filename;
		unordered_map<int, int> threepc_time;
		vector<pair<int, int>> Hgc_time;
		unordered_map<int, int> Comm_time;
		long long int No_hgc;

		unordered_map<string, string> Input;
		ifstream in;
		in.open(filename);
		string name, array;
		int num;
		in >> num;
		int n = num;
		int count_input = 1;
		int count1 = 0;

		// taking input
		// input file formate
		// no of layers Three pc time
		// no of layers Hgc time
		// no of layers comm time
		// 1 no of hgc
		while (in.eof() == 0)
		{
			in >> num;
			if (n > 0)
			{
				n--;

				if (count_input == 1)
				{
					threepc_time[count1] = num;
				}
				else if (count_input == 2)
				{
					Hgc_time.push_back({num, count1});
				}
				else if (count_input == 3)
				{
					Comm_time[count1] = num;
				}
				else
					No_hgc = num;
				count1++;
			}
			else
				n = num, count1 = 0, count_input++;
		}
		No_hgc = 4;
		long long int threepctime = 0, Time = 0;

		// calculating Ready time for i th layer

		unordered_map<long long int, long long int> Threepc_timei;
		for (int i = 0; i < threepc_time.size(); i++)
		{
			Threepc_timei[i] = threepctime;
			threepctime += threepc_time[i];
		}
		// fout << "Ready times : ";
		// for (auto it : Threepc_timei)
		// 	fout << it.first << " " << it.second << endl;
		// fout << endl;
		// fout << "comm time :";
		// for (auto it : Comm_time)
		// 	fout << it.first << " " << it.second << endl;

		sort(Hgc_time.begin(), Hgc_time.end());
		reverse(Hgc_time.begin(), Hgc_time.end());

		// fout << "Hgc times : ";
		// for (auto it : Hgc_time)
		// 	fout << it.second << " " << it.first << endl;
		// fout << endl;

		int hgc_index = 0, end_time[No_hgc];
		vector<pair<long long int, long long int>> Ttime[No_hgc]; // starting time ,ending time [hgc_no]
		int p = 0;
		int eachhgc_get_Layers = 0;
		for (auto it : Hgc_time)
		{
			if (eachhgc_get_Layers == 0)
			{ 
				// assigning first No_hgc index layers to Hgc's

				Time = 0;
				if (it.second != 0)
					Time = Threepc_timei[it.second] + Comm_time[it.second - 1];
				//fout << "Ready time is " << it.second << " " << Comm_time[it.second] << endl;
				if (Time != 0)
					Ttime[hgc_index].push_back({0, Time - 1});
				end_time[hgc_index] = it.first + Time;
				hgc_index++;
				if (hgc_index >= No_hgc)
					eachhgc_get_Layers = 1;
			}
			else
			{
				hgc_index = 0;
				Time = 0;
				if (it.second != 0)
					Time += Threepc_timei[it.second] + Comm_time[it.second - 1];
				// fout << "Ready time is " << it.second << " " << Comm_time[it.second] << endl;
				for (hgc_index = 0; hgc_index < No_hgc; hgc_index++)
					sort(Ttime[hgc_index].begin(), Ttime[hgc_index].end());

				long long int freetime = 0;
				bool get_hgc = false;
				// fout << endl;
				// fout << endl;
				// fout << "for layers " << it.second << "will work from " << Time << " to " << Time + it.first << endl;
				// fout << "Hgc free times  : ";
				// for (hgc_index = 0; hgc_index < No_hgc; hgc_index++)
				// {
				// 	fout << "for hgc " << hgc_index << endl;
				// 	for (auto ik : Ttime[hgc_index])
				// 		fout << ik.first << " " << ik.second << "     ";
				// 	fout << endl;
				// }
				// fout << endl;
				// fout << "there end time of every hss are: ";
				// for (hgc_index = 0; hgc_index < No_hgc; hgc_index++)
				// 	fout << "hss no " << hgc_index << "And time is " << end_time[hgc_index] << endl;

				// checking if there is any time interval so that this layers can run in that time interval

				for (hgc_index = 0; hgc_index < No_hgc; hgc_index++)
				{
					int count = 0;
					for (auto ip : Ttime[hgc_index])
					{
						if (ip.first <= Time && ip.second >= it.first + Time)
						{
							//fout << "reserved on hss" << hgc_index << endl;
							if (ip.first != Time)
								Ttime[hgc_index].push_back({ip.first, Time});
							if (ip.second != it.first + Time)
								Ttime[hgc_index].push_back({it.first + Time + 1, ip.second});
							Ttime[hgc_index].erase(Ttime[hgc_index].begin() + count);
							get_hgc = true;
							break;
						}
						count++;
					}
					if (get_hgc)
						break;
				}

				// if not then assign this at last
				long long int waiting_time = INT_MAX, gap_time = INT_MAX;
				int wait_index = -1, gap_index = -1;

				if (!get_hgc)
				{
					// now if any hgc is free then assign the layer if not then we will calculate the minimum waiting time for that layer
					for (hgc_index = 0; hgc_index < No_hgc; hgc_index++)
					{
						if (end_time[hgc_index] <= Time)
						{
							if (Time - end_time[hgc_index] < gap_time)
								gap_index = hgc_index;
							gap_time = min(gap_time, Time - end_time[hgc_index]);
						}
						else
						{
							if (abs(Time - end_time[hgc_index]) < waiting_time)
								wait_index = hgc_index;
							waiting_time = min(waiting_time, abs(Time - end_time[hgc_index]));
						}
					}
					if (gap_index != -1)
					{
						 fout << "ther will be a gap when we assign ,gap is" << gap_time << " with hss " << gap_index << endl;
						hgc_index = gap_index;
						if (gap_time != 0)
							Ttime[hgc_index].push_back({end_time[hgc_index], Time});
						end_time[hgc_index] += it.first;
					}
					else
					{
						fout << "there will be a wait time when we assign ,wait is " << waiting_time << " with hss " << wait_index << endl;
						hgc_index = wait_index;
						end_time[hgc_index] += it.first;
					}
				}
			}
		}

		sort(end_time, end_time + No_hgc);
		fout << end_time[No_hgc - 1] << endl;
		;
	}
	fout.close();
}
