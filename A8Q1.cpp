/*Elizabeth Shim
November 5th, 2020 */

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

int const SPACES = 50;
int const MAX_CHANGE = 25;

void read (ifstream & current, int status[SPACES], string names[SPACES])
{
	int stat = 0, parking_spot = 0;
	string name = "";
	
	while (current >> stat >> name >> parking_spot)
	{
		status[parking_spot-1] = stat;
		names[parking_spot-1] = name;
	}
}

int readOther (ifstream & fileIn, int status[MAX_CHANGE],
			string names[MAX_CHANGE])
{
	int stat = 0;
	string name = "";
	int count = 0;
	
	while (fileIn >> stat >> name)
	{
		status[count] = stat;
		names[count] = name;
		count++;
	}
	
	return count; //the number of ppl in file to be removed/added
}

void remove (int status[SPACES], string names[SPACES], string name) //d
{
	for (int count = 0; count < SPACES; count++)
	{
		if (names[count] == name)
		{
			names[count] = "";
			status[count] = -1;
		}
	}
}

int availParking (int status[SPACES], int personStat) //e
{
	int startCount = 0;
	
	if (personStat == 0)
		startCount = 25;
		
	for (int count = startCount; count < SPACES; count++)
		if (status[count] == -1)
			return count;
	
	return -2;
}

void add (int status[SPACES], string names[SPACES], int addStat, string addName)
{
	int availSpot = availParking (status, addStat);
	
	if (availSpot != -2)
	{
		names [availSpot] = addName;
		status [availSpot] = addStat;
	}
}

void staff (int status[SPACES], string names[SPACES]) //g
{
	string staffName = "";
	
	for (int count = 25; count < SPACES; count++)
	{
		if (status[count] == 1 && availParking(status, 1) != -2)
		{
			staffName = names[count];
			remove(status, names, staffName);
			add (status, names, 1, staffName);
		}
	}
}

void output (ofstream & fileOut, int status[SPACES], string names[SPACES])
{
	fileOut << setw(8) << "Status" << setw(20) << "Names" << setw(16)
		<< "Parking Spot" << endl;
	
	for (int count = 0; count < SPACES; count++)
	{
		fileOut << setw(8) << status[count] << setw(20) << names[count]
			<< setw(16) << count + 1 << endl;
	}
}

int main()
{
	ifstream current ("parking_current.txt");
	ifstream addFile ("parking_add.txt");
	ifstream removeFile ("parking_remove.txt");
	ofstream update ("parking_update.txt");
	
	if (!current || !addFile || !removeFile || !update)
	{
		cout << "File not found.";
		return EXIT_FAILURE;
	}
		
	int status[SPACES]= {0};
	string names[SPACES];
	
	int removeStatus[SPACES]={0};
	string removeNames[SPACES];
	
	int addStatus[SPACES]={0};
	string addNames[SPACES];
	
	read (current, status, names);
	
		//in case i need to find empty spaces
	for (int count = 0; count < SPACES; count++)
	{
		if (names[count] == "")
			status[count] = -1;
	}
	
	int removeNum = readOther (removeFile, removeStatus, removeNames); 
	int addNum = readOther (addFile, addStatus, addNames);
	
	for (int count = 0; count < removeNum; count++)
		remove (status, names, removeNames[count]);
		
	staff (status, names);
	
	for (int count = 0; count < SPACES; count++)
		add (status, names, addStatus[count], addNames[count]);
		
	output (update, status, names);
	
	current.close();
	removeFile.close();
	addFile.close();
	update.close();
	system ("PAUSE");
	return EXIT_SUCCESS;
}

/*
  Status               Names    Parking Spot
       1        Xie_Wei-Chau               1
       1         Hulls_Carol               2
       1       Pritzker_Mark               3
       1      Manezes_Alfred               4
       1     Fluid_Newtonian               5
       1       Tuncel_Levent               6
       1       Gryguc_Andrew               7
       1      McKinnon_David               8
       1        Jeremy_Pavan               9
       0           Paik_Chad              10
       1         Davison_Dan              11
       1        Bedi_Sanjeev              12
       1      Yodelay_he_who              13
      -1                                  14
      -1                                  15
      -1                                  16
      -1                                  17
      -1                                  18
       0      Malloch_Jeremy              19
      -1                                  20
       1        McKillop_Bob              21
      -1                                  22
      -1                                  23
      -1                                  24
       1     Davidson_George              25
       0            Lung_Ian              26
       0        Hmeidan_Amer              27
       0       Huot_Isabella              28
       0          Lau_Amanda              29
       0            Tan_Mark              30
       0          Mills_Joel              31
       0        Roller_Anika              32
       0    Starratt_Kathryn              33
       0        Belisle_Matt              34
       0    Jasmine_Princess              35
       0        Wang_Willian              36
       0    Samlalsingh_Ryan              37
       0    Barakat_Abdullah              38
       0          Yuan_Jacky              39
       0      Hamza_Muhammad              40
       0           Zheng_Tim              41
       0         Ratiu_Timea              42
       0       Sheng_Stephen              43
       0             Kim_Leo              44
       0    Clifford_Zachary              45
       0        Bhamare_Yash              46
       0    Yousufzay_Namoos              47
       0     Kandathil_Ashar              48
       0          Lau_Darren              49
       0       Keillor_Peter              50

*/
