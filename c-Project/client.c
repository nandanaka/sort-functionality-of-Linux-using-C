
/*Name - Nandana K A
SRN   - PES1UG19CS290
SEM  -  ll
SEC  -  G
Roll No. - 44
C-Project ID - 16
*/

//Note - In Linux  "-f" gives the option to ignore the cases whereas in the question it is given as "-i". So i have used "-f" instead of "-i"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"server.h"

int main(int argc, char *argv[])                                  //command line argument
{

    int k=0,no_user_file=0,no_output_files=0,number_fr=0,number_f=0,number_r=0,tot_line=0;       //program variables
    char user_files[200][200],output_files[200][200];             //array to store the names of files
    char s1[200][200];                     //array to copy each line of the files

    if(argc<3)
    {
        printf("command not found\n");                   //exit if too few arguments are supplied
        exit(1);
    }

    if((strcmp(argv[1],"sort")))
     {
        printf("command not found\n");          //exit if the first word is not "sort"
        exit(1);
    }

    for(k=2; k<argc; k++)
    {
        if(strcmp(argv[k],"-f") &&  strcmp(argv[k],"-r") && strcmp(argv[k],"-o") )
        {
            strcpy(user_files[no_user_file],argv[k]);                                  //copying the file name to user_files excluding "-f" , "-r" and "-o"
            no_user_file++;                                                                           // "no_user_files" counts number of files supplied
        }

        else if(!strcmp(argv[k],"-o"))                           //checking for output file
        {

            if(k+1==argc)
            {
                printf("sort: option requires an argument -- \'o\'\n ");
                exit(1);                                                                                                        //exit if no output file is given
            }
            if(no_user_file==0)
            {
              printf("command not found\n");                          //exit if no input file is given
              exit(1);
            }
            strcpy(output_files[no_output_files],argv[k+1]);                         //copying the output file
            k=k+1;
            no_output_files++;                                    //counting the number of output files
        }

        else                                                  //counting the number of "-f" and "-r" since in Linux position or number of "-f" and "-r" doesn't matter as long as they are written after the word "sort"
        {
            if(!strcmp(argv[k],"-f"))
                number_f++;
            else
                number_r++;
            number_fr++;                     // counts the total number of "-f" and "-r"
        }
    }


    if(number_fr==argc-2)
    {
        printf("command not found\n");
        exit(1);                                                                 //exit if no file name is supplied
    }

    FILE *fp[argc];

    for(k=0; k<no_user_file; k++)
    {
        fp[k]=fopen(user_files[k],"r");                        //opening "no_user_files" number of files which were copied to user_files
    }

    for(k=0; k<no_user_file; k++)
    {
        if(fp[k]==NULL )
        {
            printf("sort: cannot read : %s :no such files or directories\n",user_files[k]);                   //exit if the files doesn't exist
            exit(1);
        }
    }

    for(k=0; k<no_user_file; k++)
    {
        while(fgets(s1[tot_line],100,fp[k]))                         //copying each line from "no_user_files" number of files
        {

            if(s1[tot_line][strlen(s1[tot_line])-1]!='\n')                  //checking whether , at the end , there  is a new line character or not
                s1[tot_line][strlen(s1[tot_line])]='\n';                     //giving a new line character if it's not present
            tot_line++;                                                                     //counting the total number of lines
        }
    }



    if(no_output_files==0)                            //if output file is not given then print the result onto the terminal
    {
        if(number_fr==0)                                               // normal sort if total number of "-f" and "-r" is zero
            sort_normal(s1,tot_line);
        else if(number_f>0 && number_r==0)       // ignore the cases and sort if the number of "-f" is definite and number of "-r" is zero
            sort_icase(s1,tot_line);
        else if(number_f==0 && number_r>0)       // reverse the sort if number of "-f" is zero and umber of "-r" is definite
            sort_reverse(s1,tot_line);
        else
            sort_icase_reverse(s1,tot_line);               //ignore the cases and reverse sort

        for(k = 0; k<= tot_line; k++)
        {
            printf(" %s", s1[k]);                //printing the sorted lines
        }
    }

    else if(no_output_files>0)                   //     if output file is given
    {


        FILE *fp1[no_output_files];

        if(number_fr==0)                                         // normal sort if total number of "-f" and "-r" is zero
            sort_normal(s1,tot_line);
        else if(number_f>0 && number_r==0)      // ignore the cases and sort if the number of "-f" is definite and number of "-r" is zero
            sort_icase(s1,tot_line);
        else if(number_f==0 && number_r>0)     // reverse the sort if number of "-f" is zero and umber of "-r" is definite
            sort_reverse(s1,tot_line);
        else
            sort_icase_reverse(s1,tot_line);               //ignore the cases and reverse sort

        for(k=0; k<no_output_files; k++)
        {
            fp1[k]=fopen(output_files[k],"w");              //open the output files

            if(fp1[k]==NULL)
            {
                printf("couldn't open file %s", output_files[k]);      //exit if couldn't open the output files
                exit(1);

            }

            output_file(s1,fp1[k],tot_line);           //function which prints the lines onto the output file

            fclose(fp1[k]);
        }
    }
    getchar();
    return 0;
}



