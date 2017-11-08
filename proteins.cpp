#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

struct protein
{
    int item_id;
    string gi_id;
    string ref_id;
    string name;
    vector<char> sequence;
};

void store(vector<protein> *database, ifstream *file);
void count(vector<protein> database, int h);
int menu2(int h, vector<protein> database);
int menu1(vector<protein> database);


int main()
{
    int x = 0, s = 0;
    string amino;
    cout << "Welcome to the Protein Database" << endl;
    string a = "protein_a.fa";
    string b = "protein_c.fa";
    ifstream file_abridged;
    ifstream file_complete;
    vector<protein> database;
    
    cout << "Select an option from the menu below" << endl << "1) Load abridged protein data" << endl << "2) Load complete protein data" << endl;
    cin >> x;
    while ((x != 1)&&(x != 2))
    {
        cout << "That's not an option" << endl;
        cout << "Please select a valid option:"<< endl << "abridged -> 1" << endl << "complete -> 2" << endl;
        cin >> x;
    }
    if(x == 1)
    {
        cout << "Loading database..." << endl;
        file_abridged.open("protein_a.fa", ios_base::in);
        store(&database, &file_abridged);
        cout << "Database loaded." << endl;
    }
    else
    {
        cout << "Loading database..." << endl;
        file_complete.open("protein_c.fa", ios_base::in);
        store(&database, &file_complete);
        cout << "Database loaded." << endl;
    }

    while(s == 0) //repeats menu 1 until option 6 (quit database) returns s=1 and the program finishes
    {
        s = menu1(database);
    }
    
    
    return 0;
}

//function to store my data from the file into a vector called database
void store(vector<protein> *database, ifstream *file)
{
    protein Pr;
    string useless;
    string amino;
    Pr.item_id = 0;
    while(! file->eof())
    {
        Pr.item_id++;
        getline(*file, useless, '|');
        getline(*file, Pr.gi_id, '|');
        getline(*file, useless, '|');
        getline(*file, Pr.ref_id, '|');
        getline(*file, Pr.name, '\n');
        Pr.sequence.clear();
        getline(*file, amino, '>');
        for(int i = 0; i<amino.size(); i++)
        {
            Pr.sequence.push_back(amino[i]);
        }
        database->push_back(Pr);
    }
}

//function to count number of times an amino acid appears in a protein sequence
void count(vector<protein> database, int h)
{
	int counter=0;
	for(char letter = 'A'; letter <= 'W'; letter ++)
	{
		for (int i = 0; i < database[h].sequence.size(); i++)
		{
			if (database[h].sequence[i] == letter)
			{
				counter++;
			}
		}
		cout << letter << " " << counter << endl;
		counter=0;
	}
	for(char letter = 'Y'; letter <= 'Z'; letter ++)
	{
		for (int i = 0; i < database[h].sequence.size(); i++)
		{
			if (database[h].sequence[i] == letter)
			{
				counter++;
			}
		}
		cout << letter << " " << counter << endl;
		counter=0;
	}
	for (int i = 0; i < database[h].sequence.size(); i++)
	{
		if (database[h].sequence[i] == 'X')
		{
			counter++;
		}
	}
	cout << "X " << counter << endl;
	counter=0;
	for (int i = 0; i < database[h].sequence.size(); i++)
	{
		if (database[h].sequence[i] == '*')
		{
			counter++;
		}
	}
	cout << "* " << counter << endl;
	counter=0;	
	for (int i = 0; i < database[h].sequence.size(); i++)
	{
		if (database[h].sequence[i] == '-')
		{
			counter++;
		}
	}
	cout << "- " << counter << endl;
	counter=0;		
}

//function that implements the second menu of the program
int menu2(int h, vector<protein> database) //h is the protein number selected in menu 1
{
    int p, m = 0, q = 0;
	cout << endl;
    
    cout << "Select an option from the menu below" << endl;
    cout << "1) Description of the protein" << endl;
    cout << "2) Protein sequence" << endl;
    cout << "3) Protein statistics" << endl;
    cout << "4) Record protein to file" << endl;
    cout << "5) Return to main menu" << endl;
    cin >> p;
    
    switch(p)
    {
        case 1:
            cout << "Description of the protein:" << endl;
            cout << "item id: " << database[h].item_id << endl;
            cout << "gi id: " << database[h].gi_id << endl;
            cout << "ref id: " << database[h].ref_id << endl;
            cout << "name: " << database[h].name << endl;
			m = 0;
			return m;
            break;
            
        case 2:
            cout << "Protein sequence: " << endl;
            for (int i = 0; i < database[h].sequence.size(); i++)
                cout << database[h].sequence[i];
            cout << endl;
			m = 0;
			return m;
            break;
            
        case 3:
            cout << "Report on the protein statistics: " << endl;
			for (int i = 0; i < database[h].sequence.size(); i++)
			{
                if(database[h].sequence[i] == '\n') // counts number of empty spaces at the end of each line of the protein sequence so then it is sustracted from the sequence size to get the right number
				{
					q++;
				}
			}
            cout << "Total number of amino acids: " << database[h].sequence.size() - q <<endl;
            count(database, h); //implements the function that counts number of times that a character is repeated
			m = 0;
			return m;
            break;
            
        case 4:
		{
            ofstream selected_proteins; // the new file selected_proteins is created
			selected_proteins.open("selected_proteins.txt"); //the file created is opened
            //the selected protein is saved into the file
			selected_proteins << ">gi|";
            selected_proteins << database[h].gi_id;
			selected_proteins << "|ref|";
			selected_proteins << database[h].ref_id;
			selected_proteins << "|";
			selected_proteins << database[h].name;
			selected_proteins << endl;
			for (int i = 0; i < database[h].sequence.size(); i++)
                selected_proteins << database[h].sequence[i];
			selected_proteins << endl;
			selected_proteins.close();
			cout << "The protein was written to file" << endl;
			m = 0;
			return m;
            break;
		}
            
        case 5:
			m = 1;
			return m;
            break;
    }
	return m;
}

//function that implements the main menu of the program
int menu1(vector<protein> database)
{
    int w, h, s = 0, m = 0, j = 0, k = 0, b, n = 0;
    string g;
    vector<string> matches;
	string search;
	cout << endl;
    
    cout << "Select an option from the menu below" << endl;
    cout << "1) Overview of the database" << endl;
    cout << "2) Search by protein #" << endl;
    cout << "3) Search by gi #" << endl;
    cout << "4) Search by ref #" << endl;
    cout << "5) Search by keyword" << endl;
    cout << "6) Quit database" << endl;
    cin >> w;
    cout << endl;
    
    switch (w)
    {
        case 1:
            cout << "The proteins in the database are from GenBank(R)" << endl;
            cout << "Total number of proteins in the database: " << database.size() << endl;
            cout << "A  alanine               P  proline" << endl;
            cout << "B  aspartate/asparagine  Q  glutamine" << endl;
            cout << "C  cystine               R  arginine" << endl;
            cout << "D  aspartate             S  serine" << endl;
            cout << "E  glutamate             T  threonine" << endl;
            cout << "F  phenylalanine         U  selenocysteine" << endl;
            cout << "G  glycine               V  valine" << endl;
            cout <<	"H  histidine             W  tryptophan" << endl;
            cout << "I  isoleucine            Y  tyrosine" << endl;
            cout << "K  lysine                Z  glutamate/glutamine" << endl;
            cout << "L  leucine               X  any" << endl;
            cout << "M  methionine            *  translation stop" << endl;
            cout << "N  asparagine            -  gap of indeterminate length" << endl;
            s=0;
            return s;
            break;
            
        case 2:
            cout << "Enter item id: " << endl;
            cin >> h;
            h = h - 1;
			while(m == 0) //repeats menu 2 until option 5 (return to main menu) returns m=1 and it comes back to menu
            {
				m = menu2(h, database);
			}
            s=0;
            return s;
            break;
            
        case 3:
            cout << "Enter gi id: " << endl;
            cin >> g;
            for(int i = 0; i <= database.size(); i++)
            {
                if ((database[i].gi_id) == g)
                {
                    while(m == 0)//repeats menu 2 until option 5 (return to main menu) returns m=1 and it comes back to menu
                    {
						m = menu2(i, database);
					}
                }
            }
            s=0;
            return s;
            break;
            
        case 4:
            cout << "Enter ref number: " << endl;
            cin >> g;
            for(int i = 0; i <= database.size(); i++)
            {
                if ((database[i].ref_id) == g)
                {
					while(m == 0)//repeats menu 2 until option 5 (return to main menu) returns m=1 and it comes back to menu
                    {
						m = menu2(i, database);
					}
				}
            }
            s=0;
            return s;
            break;
            
        case 5:
            while(n == 0)
            {
                cout << "Enter keyword: " << endl;
                cin >> g;
                for(int i = 0; i < database.size(); i++) //runs through all the proteins of the dsatabse to find a match on the name of the protein with the word enetered
                {
                    if((database[i].name).find(g) != string::npos)
                    {
                        search =database[i].gi_id;
                        matches.push_back(search);
                    }
                }
                cout << endl;
                cout << "Number of matches found: " << matches.size() << endl;
                if(matches.size() == 0)
                {
                    cout << "No matches found. Try another word" << endl;
                    n = 0;
                }
                else
                {
                    n = 1;
                }
            }
            while((j < matches.size()) && (k < database.size())) // displays all the matches found
            {
                if (matches[j] == (database[k].gi_id))
                {
                    cout << j+1 << ") ";
                    cout << "item id: " << k+1;
                    cout << ", gi id: " << database[k].gi_id;
                    cout << ", ref id: " << database[k].ref_id << endl;
                    cout << "    " << database[k].name << endl;
                    j++;
                    k++;
                }
                else
                {
                    k++;
                }
            }
            cout << endl;
            cout << "Select one of the matches" << endl;
            cin >> b; // b is the match selected
            j = 0;
            k = 0;
            while((j < matches.size()) && (k < database.size()))
            {
                if ((b-1) == j) // b-1 is used because the list of matches starts in zero
                {
                    if(matches[j] == (database[k].gi_id))
                    {
                        while(m == 0)//repeats menu 2 until option 5 (return to main menu) returns m=1 and it comes back to menu
                        {
                            m = menu2(k, database);
                        }
                        break;
                    }
                    else
                    {
                        k++;
                    }
                }
                else
                {
                    j++;
                }
            }
            s=0;
            return s;
            break;
            
        case 6:
			cout << "Thank you for using the protein database" << endl;
            s=1;
            return s;
            break;
    }
    return s;
}





