/*
	Name: Fahad Ur Rehman
	SOLS: fur866
	ID: 4651960
	Assignment 2 for CSCI212
	Purpose: This program takes a file and outputs the libraries that file depends on along with their absolute paths
*/

#include <iostream>
#include <libfschecker.h>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libelf.h>
#include <gelf.h>

using namespace std;

int find_next(char*,int); // finds the next string until ":"
void copy(char[],char*,int,int); //copies part of one string to other
bool find_and_put(char[],char[],char*); //resolves libraries with their addresses

int main(int argc, char **argv)
{
	Elf *elf;
	Elf_Scn *scn = NULL;
	GElf_Shdr shdr;
	Elf_Data *data;
	int fd, ii, count;
	GElf_Dyn sym;
	char* name = NULL;
	char library[1000];
	int lib_count = 0;
	int z = 0;

	// do arguement checking

	if (argc != 2)
	{
		cerr << "Usage is: elf filename " << endl;
		exit(1);
	}

	// open the file in argv[1] and produce the elf descriptor
	elf_version(EV_CURRENT);

	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		cerr << "Could not open file: " << argv[1] << endl;
		exit(1);
	}

	elf = elf_begin(fd, ELF_C_READ, NULL);
	
	// scan through the sections in the file

	while ((scn = elf_nextscn(elf, scn)) != NULL) 
	{
		// get the section header and check to see if the it the
		// .dynamic section
		gelf_getshdr(scn, &shdr);
        if (shdr.sh_type == SHT_DYNAMIC) 
		{
			data = elf_getdata(scn, NULL);
			ii=0;
			do
			{	
				gelf_getdyn(data, ii++, &sym);
				if (sym.d_tag == DT_NEEDED)
				{
					// if we find a element in the section
					// that is a library we pull it out
					name = elf_strptr(elf,shdr.sh_link,sym.d_un.d_ptr);
					if (name != NULL)
					{
						strcat(library,name); //library names are added separated by ":"
						strcat(library,":");
						lib_count++; //count the number of libraries read
					} 
				}

				if (sym.d_tag == DT_RPATH)
				{
					name = elf_strptr(elf,shdr.sh_link,sym.d_un.d_ptr);
					if (name != NULL)
					{
						char complete_list[5000];
						char lib[100];
						int count = 0;
						for(int i = 0; i < lib_count; i++) //for each library, resolve its address
						{
							int counter = 0;
							while(library[count] != ':')
							{
								lib[counter++] = library[count++];
							}
							lib[counter] = '\0';
							count++;
							if(find_and_put(complete_list,lib,name) == false) //if by any chance a library cannot be found, exit program
							{
								cerr<<"Error some of the libraries not found!"<<endl;
								exit(1);
							}
						}
						cout<<endl<<complete_list<<endl; //output all the libraries with their absolute paths
					} 

				}
         	} while (sym.d_tag != DT_NULL);
		}
	}
	elf_end(elf);
	return 0;
}

int find_next(char* array,int start) // finds the next string until ":"
{
	int i = start;
	for(; i < strlen(array); i++)
	{
		if(array[i] == ':')
		{
			break;
		}
	}

	return i;
}

void copy(char array1[],char* array2,int start,int end) //copies part of one string to other
{
	int i = start;
	int count = 0;
	for(; i < end; i++)
	{
		array1[count++] = array2[i];
	}
	array1[count] = '\0';
}

bool find_and_put(char complete_list[], char library[],char* name) //resolves libraries with their addresses
{
	int i = 0;
	char path[5000];
	int start = 0;
	int end = 0;
	bool check = false;
	
	while(name[i] != '\0') //first we check a library against all the paths
	{
		end = find_next(name,start);
		if(name[end] != '0')
		{
			copy(path,name,start,end);
			start = end + 1;
			strcat(path,"/");
			strcat(path,library);
			if(checkfile(path) == 0) //as soon as a library is resolved, it is copied to the complete_list array and the loop is broken
			{
				strcat(complete_list,library);
				strcat(complete_list," =>  ");
				strcat(path,"\n");
				strcat(complete_list,path);
				check = true;
				break;
			}
			strcpy(path,"");
		}
		i = end;
	}
	if(check == false) //if library not resolved yet
	{
		if(getenv("LD_LIBRARY_PATH") != NULL) //we look into "LD_LIBRARY_PATH"
		{
			strcpy(path,getenv("LD_LIBRARY_PATH"));
			strcat(path,"/");
			strcat(path,library);
			if(checkfile(path) == 0) //if library is resolved, it is copied to the complete_list array
			{
				strcat(complete_list,library);
				strcat(complete_list," =>  ");
				strcat(path,"\n");
				strcat(complete_list,path);
				check = true;
			}
		}
	}
		
	if(check == false) //if library not resolved yet
	{
		strcpy(path,"");
		strcat(path,"/");
		strcat(path,"usr/lib/"); //we look into /usr/lib
		strcat(path,library);
		if(checkfile(path) == 0) //if library is resolved in /usr/lib, it is copied to the complete_list array
		{
			strcat(complete_list,library);
			strcat(complete_list," =>  ");
			strcat(path,"\n");
			strcat(complete_list,path);
			check = true;
		}
	}

	return check; //if not resolved any where, false is returned. Else true is returned
}
