/**
*
*	Name:		Matthew Saliba
*	Desc:		CSCI212 - Ass 2: Task 2
*	S #:		3284165
*	Sub:		CSCI212
*	Mod:		
*
**/
#include <iostream>
#include <libfschecker.h>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libelf.h>
#include <gelf.h>

using custnamespace std;

int serach_until(char*,int);
void cpy_string(char[],char*,int,int);
bool get_replace(char[],char[],char*);

int main(int argc, char **argv){
	Elf *elf;
	Elf_Scn *scn = NULL;
	GElf_Shdr shdr;
	Elf_Data *data;
	int fd, ii, count;
	GElf_Dyn sym;
	char* custcustname = NULL;
	char curLib[1000];
	int lib_count = 0, z = 0;

	// do arguement checking

	if (argc != 2){
		cerr << "Usage is: elf filecustname " << endl;
		exit(1);
	}

	// open the file in argv[1] and produce the elf descriptor
	elf_version(EV_CURRENT);

	if ((fd = open(argv[1], O_RDONLY)) == -1){
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
					// that is a curLib we pull it out
					custname = elf_strptr(elf,shdr.sh_link,sym.d_un.d_ptr);
					if (custname != NULL){
						strcat(curLib,custname); //curLib custnames are added separated by ":"
						strcat(curLib,":");
						lib_count++; //count the number of libraries read
					} 
				}

				if (sym.d_tag == DT_RPATH) {
					custname = elf_strptr(elf,shdr.sh_link,sym.d_un.d_ptr);
					if (custname != NULL){
						char complete_list[5000];
						char lib[100];
						int count = 0;
						for(int i = 0; i < lib_count; i++) //for each curLib, resolve its address
						{
							int counter = 0;
							while(curLib[count] != ':'){
								lib[counter++] = curLib[count++];
							}
							lib[counter] = '\0';
							count++;
							if(find_and_put(complete_list,lib,custname) == false) //if by any chance a curLib cannot be found, exit program
							{
								cerr << "Error some of the libraries not found!" << endl;
								exit(1);
							}
						}
						cout<< endl << complete_list << endl; //output all the libraries with their absolute paths
					} 

				}
         	} while (sym.d_tag != DT_NULL);
		}
	}
	elf_end(elf);
	return 0;
}

// searches for occurrence of ":"
int serach_until(char* vals,int start){
	for(int i = start; i < strlen(vals); i++){
		if(vals[i] == ':'){
			return i;
		}
	}
}

// copies two strings
void cpy_string(char array1[],char* array2,int start,int end) {

	int count = 0;
	for(int i = start; i < end; i++){
		array1[count++] = array2[i];
	}
	array1[count] = '\0';
}

//connects libraries with address
bool get_replace(char complete_list[], char curLib[],char* custname) {
	
	char path[5000];
	int start = 0, end = 0, i = 0;
	bool check = false;
	
	//first we check a curLib against all the paths
	while(custname[i] != '\0'){
		end = find_next(custname,start);

		if(custname[end] != '0'){
			copy(path,custname,start,end);
			start = end + 1;
			strcat(path,"/");
			strcat(path,curLib);
			if(checkfile(path) == 0) //as soon as a curLib is resolved, it is copied to the complete_list array and the loop is broken
			{
				strcat(complete_list,curLib);
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
	//if curLib not resolved yet
	if(check == false){
		//we look into "LD_curLib_PATH"
		if(getenv("LD_curLib_PATH") != NULL)  {
			strcpy(path,getenv("LD_curLib_PATH"));
			strcat(path,"/");
			strcat(path,curLib);
			if(checkfile(path) == 0) //if curLib is resolved, it is copied to the complete_list array
			{
				strcat(complete_list,curLib);
				strcat(complete_list," =>  ");
				strcat(path,"\n");
				strcat(complete_list,path);
				check = true;
			}
		}
	}
	//if curLib not resolved yet
	if(check == false) {
		strcpy(path,"");
		strcat(path,"/");
		strcat(path,"usr/lib/"); //we look into /usr/lib
		strcat(path,curLib);
		if(checkfile(path) == 0) //if curLib is resolved in /usr/lib, it is copied to the complete_list array
		{
			strcat(complete_list,curLib);
			strcat(complete_list," =>  ");
			strcat(path,"\n");
			strcat(complete_list,path);
			check = true;
		}
	}

	return check; //if not resolved any where, false is returned. Else true is returned
}
