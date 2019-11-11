#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/*Create a public class (Although I could create a struct too which will have the same features)*/
class DNA_DB{
	public:
	//Type atributes
	vector<char> mysequence;
	string file_name;
	string dna_seq_name;
	string dna_seq_gid;
	string dna_seq_ref;

};

//Provide name of the uploaded sequence
string seq_name(string mystring){
	string seq;
	char delim = '|';
	char delim2 = 'N';
	string name;
	ifstream myfile(mystring);
	if (myfile.is_open())
	{
		getline(myfile, name, delim);
		getline(myfile, name, delim);
		getline(myfile, name, delim);
		getline(myfile, name, delim);
		getline(myfile, name, delim2);
		seq = name;
		myfile.close();
	}
	return seq;
}

//Provide the GID
string seq_gid(string mystring){
	string gid;
	char delim = '|';
	string name;
	ifstream myfile(mystring);
	if (myfile.is_open())
	{
		getline(myfile, name, delim);
		getline(myfile, name, delim);
		gid = name;
		myfile.close();
	}
	return gid;
}

//Provide the REF
string seq_ref(string mystring){
	string ref;
	char delim = '|';
	string name;
	ifstream myfile(mystring);
	if (myfile.is_open())
	{
		getline(myfile, name, delim);
		getline(myfile, name, delim);
		getline(myfile, name, delim);
		getline(myfile, name, delim);
		ref = name;
		myfile.close();
	}
	return ref;
}

 
 
 
//Provide a vector of characters from file's sequence
vector<char> new_file_char(string myfilename)
{
	vector<char> file_char;
	string first_line;
	char h;
	ifstream myfile(myfilename);
	getline (myfile,first_line);
	while (!myfile.eof()){
		myfile.get(h);
		if (int(h) != 10)
		{
			file_char.push_back(h);
		}
	}
	myfile.close();
	return file_char;
}

//Menu2
void Menu2()
{
	cout << "\n Select one of the following o[tions\n";
	cout << "(H) Help\n";
	cout << "(S) Summary statistics of the DNA sequence\n";
	cout << "(1) Analyse gap region\n";
	cout << "(2) Analyse coded region\n";
	cout << "(3) Analyse base pair range\n";
	cout << "(4) Find DNA sequence by manual input\n";
	cout << "(5) Find DNA sequence by file input\n";
	cout << "(R) Return to the previous menu\n";
	cout << "(Q) Quit\n";
}

//Help Menu
void HelpMenu()
{
	cout << "\n Code Base Description \n";
	cout << "G Guanine \n";
	cout << "A Adenine \n";
	cout << "T Thymine (Uracil in RNA) \n";
	cout << "C Cytosine \n";
	cout << "R Purine (A or G) \n";
	cout << "Y Pyrimidine (C or G) \n";
	cout << "M Amino (A or C) \n";
	cout << "K Ketone (G or T) \n";
	cout << "S Strong interaction (C or G) \n";
	cout << "W Weak interaction (A or T) \n";
	cout << "H Not-G (A or C or T) H follows G in the alphabet \n";
	cout << "B Not-A (C or G or T) B follows A in the alphabet \n";
	cout << "V Not-T (not-U) (A or C or G) V follows U in the alphabet \n";
	cout << "D Not-C (A or G or T) D follows C in the alphabet \n";
	cout << "N Any (A or C or G or T) \n\n";
}

int main(){
	string filenames;
	string small_string;
	string range;
	string gen_ex;
	string chosen_seq;
	vector<string> mystrings;
	vector<char> Ngap;
	vector<char> Cgap;
	vector<string> int_range;
	vector<int> search;
	vector<int> n_similar;
	int t = 0;
	int q;
	int k;
	int l;
	int s;
	int u;
	int answer3;
	int answer4;
	char delim = ',';
	char answer1;
	char answer2;
	char f;
	bool p = true;
	bool o = true;
	long double b_pair = 0;
	long double N_region = 0;
	long double C_region = 0;
	long double G = 0;
	long double A = 0;
	long double T = 0;
	long double C = 0;
	long double R = 0;
	long double Y = 0;
	long double M = 0;
	long double K = 0;
	long double S = 0;
	long double W = 0;
	long double H = 0;
	long double B = 0;
	long double V = 0;
	long double D = 0;
	long double N = 0;
	long double Unknown = 0;
	long double i;
	long double j;
	long double x;
	long double v;
	
	// Printing intro
	cout << "DNA Sequence Database Software\n";
	cout << "Specify the name of DNA  sequence file names you would like to load. For multiple files, add a ',' between each file name.\n";
	cin >> filenames;
	
	//Get the multiple files and put them inside vector
	stringstream ss(filenames);
	while(getline(ss, small_string, delim)){
		mystrings.push_back(small_string);
	}
	//Creating as many classes as files user wants
	DNA_DB *dna_db=new DNA_DB[mystrings.size()];
	
	//LOAD file into attributes
	for (t = 0; t < mystrings.size(); t++)
	{
		cout << "\nLoading " << mystrings[t] << " ... \n";
		dna_db[t].file_name = mystrings[t];
		dna_db[t].dna_seq_name = seq_name(mystrings.at(t));
		dna_db[t].dna_seq_gid = seq_gid(mystrings.at(t));
		dna_db[t].dna_seq_ref = seq_ref(mystrings.at(t));
		dna_db[t].mysequence = new_file_char(mystrings.at(t));
		cout << "Successful loading of " << mystrings[t] << "\n\n";
	}
	
	while (p==true){
		o = true;
		//Printing first menu
		cout << "Select one of the following options\n";
		cout << "(S) Summary statistics of the DNA database\n";


		for (int k = 0; k < t; k++)
		{
			cout << "(" << k+1<< ") Analyse " << dna_db[k].file_name << "\n";
		}
		cout << "(Q) Quit\n";
		cin >> answer1;
		
		//For answer s: display the number of sequences loaded, their name, reference number, GID and base pair number
		if (answer1 == 's'){
			cout << "\n The DNA Sequence Database holds the following sequences.\n";
			for(t = 0; t < mystrings.size(); t++)
			{
				cout << "Name:	" << dna_db[t].dna_seq_name;
				cout << "GID:	" << dna_db[t].dna_seq_gid << "\n";
				cout << "REF:	" << dna_db[t].dna_seq_ref << "\n";
				b_pair = dna_db[t].mysequence.size();
				cout.precision(0);
				cout << fixed << "# base pairs: " << b_pair << "\n\n";
			}
		}
	
		//Answer q: quit program
		else if (answer1 == 'q'){
			return 0;
		}
		
		else 
		{	
			//Depending of the number input we access a different file
			u = (int)answer1 - 49;
			while (o==true){
				//Printing of second menu
				Menu2();
				cin >> answer2;

				//FOr anwer h: specify information for the understanding of the file 
				if (answer2=='h')
				{
					HelpMenu();
				}
				
				//For answer s: display name and identifier of selected sequence, number of gap and code regions
				//and the number each appears
				else if (answer2=='s')
				{
					cout << "\n Sequence identifiers: \n";
					cout << "Name:	" << dna_db[u].dna_seq_name << "\n";
					cout << "GID:	" << dna_db[u].dna_seq_gid << "\n";
					cout << "REF:	" << dna_db[u].dna_seq_ref << "\n\n";
					cout << "Region characteristics: \n";
					for (int m = 0; m < dna_db[u].mysequence.size(); m++)
					{
						if ((dna_db[u].mysequence[m] == 'N') && (dna_db[u].mysequence[m-1] != 'N'))
						{
							N_region++;
						}
					}
					C_region = N_region - 1;
					cout << "# regions:		" << N_region+C_region << "\n";
					cout << "# N regions:	" << N_region << "\n";
					cout << "# C regions:	" << C_region << "\n";
					cout.precision(0);
					cout << fixed << "# base pairs: " << dna_db[u].mysequence.size() << "\n";
					for (long double t = 0; t < dna_db[u].mysequence.size(); t++)
					{
						if (dna_db[u].mysequence[t] == 'G')
						{
							G++;
						}
						else if (dna_db[u].mysequence[t] == 'A')
						{
							A++;
						}
						else if (dna_db[u].mysequence[t] == 'T')
						{
							T++;
						}
						else if (dna_db[u].mysequence[t] == 'C')
						{
							C++;
						}
						else if (dna_db[u].mysequence[t] == 'R')
						{
							R++;
						}
						else if (dna_db[u].mysequence[t] == 'Y')
						{
							Y++;
						}
						else if (dna_db[u].mysequence[t] == 'M')
						{
							M++;
						}
						else if (dna_db[u].mysequence[t] == 'K')
						{
							K++;
						}
						else if (dna_db[u].mysequence[t] == 'S')
						{
							S++;
						}
						else if (dna_db[u].mysequence[t] == 'W')
						{
							W++;
						}
						else if (dna_db[u].mysequence[t] == 'H')
						{
							H++;
						}
						else if (dna_db[u].mysequence[t] == 'B')
						{
							B++;
						}
						else if (dna_db[u].mysequence[t] == 'V')
						{
							V++;
						}
						else if (dna_db[u].mysequence[t] == 'D')
						{
							D++;
						}
						else if (dna_db[u].mysequence[t] == 'N')
						{
							N++;
						}
						else 
						{
							Unknown++;
						}
					}
					
					cout << fixed << "G:		" << G << "\n";
					cout << fixed << "A:		" << A << "\n";
					cout << fixed << "T:		" << T << "\n";
					cout << fixed << "C:		" << C << "\n";
					cout << fixed << "R:		" << R << "\n";
					cout << fixed << "Y:		" << Y << "\n";
					cout << fixed << "M:		" << M << "\n";
					cout << fixed << "K:		" << K << "\n";
					cout << fixed << "S:		" << S << "\n";
					cout << fixed << "W:		" << W << "\n";
					cout << fixed << "H:		" << H << "\n";
					cout << fixed << "B:		" << B << "\n";
					cout << fixed << "V:		" << V << "\n";
					cout << fixed << "D:		" << D << "\n";
					cout << fixed << "N:		" << N << "\n";
					cout << fixed << "Unknown:	" << Unknown << "\n";
				}
				
				//For answer r: return to first menu
				else if (answer2 == 'r')
				{
					o = false;
					answer1=0;
				}
				
				//Answer = 1: user is asked for a number which would represent the gap region it will be display
				else if (answer2 == 49) 
				{
					cout << "Enter gap region number: \n";
					cin >> answer3;
					for ( i = 0; i< dna_db[u].mysequence.size(); i++)
					{
						if ((dna_db[u].mysequence[i] == 'N') && (dna_db[u].mysequence[i-1] != 'N'))
						{
							N_region++;
							if (N_region== answer3)
							{
								for (j = i; j<dna_db[u].mysequence.size();j++)
								{
									if (dna_db[u].mysequence[j]=='N')
									{
										Ngap.push_back(dna_db[u].mysequence[j]);
									}
									else
									{
										break;
									}
								}
							}
						}
					}
					cout << "Selected sequence: \n";
					cout.precision(0);
					cout << "Base pair range: (" << fixed << j-Ngap.size() << "," << fixed << j << ")\n";
					cout << "Gap region number: " << answer3 << "\n\n";
					cout << "Sequence: \n";
					for (int p = 0; p<Ngap.size(); p++)
					{
						cout << Ngap[p];
					}
					cout << "\n";
					
				}
				
				//Answer = 2: user is asked for a numer which represents the coded region theat will be display
				else if (answer2 == 50) 
				{
					cout << "Enter coded region number: \n";
					cin >> answer4;
					for ( x = 0; x< dna_db[u].mysequence.size(); x++)
					{
						if ((dna_db[u].mysequence[x] != 'N') && (dna_db[u].mysequence[x-1] != 'N'))
						{
							C_region++;
							if (C_region == answer4)
							{
								for (v = x; v<dna_db[u].mysequence.size();v++)
								{
									if (dna_db[u].mysequence[v]!='N')
									{
										Cgap.push_back(dna_db[u].mysequence[v]);
									}
									else
									{
										break;
									}
								}
							}
						}
					}
					cout << "Selected sequence: \n";
					cout.precision(0);
					cout << "Base pair range: (" << fixed << v-Cgap.size() << "," << fixed << v << ")\n";
					cout << "Coded region number: " << answer4 << "\n\n";
					cout << "Sequence: \n";
					for (int p = 0; p<Cgap.size(); p++)
					{
						cout << Cgap[p];
					}
					cout << "\n";
				}
				
				//Answer = 3: user is asked for a two numbers and the base pairs in that range will be displayed
				else if (answer2 == 51) 
				{
					int h = 10;
					string get_range;
					cout << "Enter a coma ',' separated base pair range: \n";
					cin >> range;
					stringstream detect (range);
					getline(detect, get_range,delim);
					int_range.push_back(get_range);
					getline(detect, get_range,(char)h);
					int_range.push_back(get_range);
					cout << "Selected sequence: \n";
					cout << "Base pair range: (" << int_range[0] << "," << int_range[1] << ")\n\n";
					cout << "Sequence: \n";
					//Convert string from vectot int_range into int
					int m = stoi(int_range.at(0));
					int y = stoi(int_range.at(1));
					for (int n = m; n < y; n++)
					{
						cout << dna_db[u].mysequence[n];
					}
					cout << "\n\n";
				}
				
				//Answer = 4: user is asked for at least 10 nucleotide bases and check if there are in the file sequence
				// displaying the 20 bases before and after and the location of the asked sequence
				else if (answer2 == 52) 
				{
					cout << "Specify the DNA sequence nucleotide you would like to find: \n";
					cin >> chosen_seq;
					vector<char> manual_seq;
					
					for (int h = 0; h <chosen_seq.length();h++)
					{
						manual_seq.push_back(chosen_seq[h]);
					}
					
					
					for(int i =0; i<dna_db[u].mysequence.size();i++)
					{
						bool match = true;
						for(int j =0; j<manual_seq.size();j++)
						{
							if(dna_db[u].mysequence[i+j]!=manual_seq[j])
							{
								match = false;
								break;
							}
						}
						if(match)
						{
							n_similar.push_back(i);
							// start = i;
							// finish = start + chosen_seq.lenght();
						}
					}
					
					for (int f = 0; f<n_similar.size();f++)
					{
						cout << f << ". Base pair range: (" << n_similar[f] << "," << n_similar[f]+manual_seq.size() << ")\n";
						int d = n_similar[f];
						
						for (int r =20; r>0; r--)
						{
							cout << dna_db[0].mysequence[d-r];
						}
						cout << "\n";
						for (int h = 0; h<manual_seq.size(); h++)
						{
							cout << manual_seq[h];
						}
						cout << "\n";
						for (int r = 1; r<21; r++)
						{
							cout << dna_db[0].mysequence[d+r];
						}
						cout << "\n\n";
					}
					
				}
				
				//Answer = 5:user is asked for a file and it will be checked if it is in the sequence
				else if (answer2 == 53) 
				{
					cout << "Especify the DNA sequence file you would like to find: \n";
					cin >> gen_ex;
					cout << "\nLoading " << gen_ex << " ... \n";
					vector<char> genesequence;
					int start = 0;
					int finish = 0;
					genesequence = new_file_char(gen_ex);
					cout << "Successful loading of " << gen_ex << "\n\n";
					
					for(int i =0; i<dna_db[u].mysequence.size();i++)
					{
						bool match = true;
						for(int j =0; j<genesequence.size();j++)
						{
							if(dna_db[u].mysequence[i+j]!=genesequence[j])
							{
								match = false;
								break;
							}
						}
						if(match)
						{
							start = i;
							finish = start + genesequence.size();
						}
					}
					
					cout << "1 matching sequence(s) found. \n\n";
					cout << "1. Base pair range: (" << start << "," << finish << ")\n";

					for (int r = 21; r>0; r--)
						{
							cout << dna_db[u].mysequence[start-r];
						}
					cout << "\n";
					for (int e = 0; e<genesequence.size(); e++)
					{
						cout << genesequence[e];
					}
					cout << "\n";
					for (int r = 1; r<21; r++)
						{
							cout << dna_db[u].mysequence[finish+r];
						}
					cout << "\n\n";
				
				}
				
				//Answer q: quit program
				else if (answer2 == 'q')
				{
					return 0;
				}
			}
		}
	}
}
