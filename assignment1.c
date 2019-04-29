#include <stdio.h>
#include <string.h>
#include<stdlib.h>

struct Entry {
	char fname[60];
	char lname[60];
	char number[20];
	char index[4];
};


int c=0;
char arr[200][60];
struct Entry Directory[10000];
struct Entry merger[100];

int create_Directory()
{

	char f_name[50];
	char l_name[50];
	char no[50];
	char i_index[5];
   	FILE * fp;

	fp = fopen ("test.txt", "r");
  	if(fp != NULL)
	{
		while(1)
		{
   		int eof = fscanf(fp, "%s %s %s %s", i_index, f_name, l_name, no);
		if(eof==EOF)
		break;
		strcpy( Directory[c].index, i_index);
		strcpy( Directory[c].fname, f_name);
		strcpy( Directory[c].lname, l_name);
		strcpy( Directory[c].number, no);
		printf("%s %s %s\n",Directory[c].fname,Directory[c].lname,Directory[c].number);
   		char form_name[400]="";
		strcat(form_name, l_name);
		strcat(form_name, "_");
		strcat(form_name, f_name);
		strcat(form_name, "_");
		strcat(form_name, no);
		strcpy(arr[c],form_name);
		c++;

		}
 	}

   printf("***************************************************************\n");

	fclose(fp);

	return 0;

}

void merge(struct Entry arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

 
    struct Entry L[n1];
    struct Entry R[n1];

   
    for (i = 0; i < n1; i++)
    {
    	strcpy(L[i].fname,arr[l + i].fname);
    	strcpy(L[i].lname,arr[l + i].lname);
    	strcpy(L[i].number,arr[l + i].number);
    	strcpy(L[i].index,arr[l + i].index);

    }
    for (j = 0; j < n2; j++)
    {
    	strcpy(R[j].index,arr[m + 1+ j].index);
    	strcpy(R[j].fname,arr[m + 1+ j].fname);
    	strcpy(R[j].lname,arr[m + 1+ j].lname);
    	strcpy(R[j].number,arr[m + 1+ j].number);

    }
    
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2)
    {
    	int result= strcmp(L[i].lname,R[j].lname);

        if (result < 0)
        {
        	strcpy(Directory[k].index,L[i].index);
        	strcpy(Directory[k].fname,L[i].fname);
        	strcpy(Directory[k].lname,L[i].lname);
        	strcpy(Directory[k].number,L[i].number);

            i++;
        }
	else if (result==0)
	{
	   int res1=strcmp(L[i].fname,R[j].fname);
		if(res1<=0)
		{
			strcpy(Directory[k].index,L[i].index);
        		strcpy(Directory[k].fname,L[i].fname);
        		strcpy(Directory[k].lname,L[i].lname);
        		strcpy(Directory[k].number,L[i].number);
  		i++;
		}
		else
		{
			strcpy(Directory[k].index,R[j].index);
			strcpy(Directory[k].fname,R[j].fname);
			strcpy(Directory[k].lname,R[j].lname);
			strcpy(Directory[k].number,R[j].number);
		j++;
		}	
	

	}
        else
        {
        	strcpy(Directory[k].index,R[j].index);
			strcpy(Directory[k].fname,R[j].fname);
			strcpy(Directory[k].lname,R[j].lname);
			strcpy(Directory[k].number,R[j].number);

            j++;
        }
        k++;
    }

    
    while (i < n1)
    {
    	  strcpy(Directory[k].index,L[i].index);
    	  strcpy(Directory[k].fname,L[i].fname);
    	  strcpy(Directory[k].lname,L[i].lname);
    	  strcpy(Directory[k].number,L[i].number);
        i++;
        k++;
    }

   
    while (j < n2)
    {
    	strcpy(Directory[k].index,R[j].index);
		strcpy(Directory[k].fname,R[j].fname);
		strcpy(Directory[k].lname,R[j].lname);
		strcpy(Directory[k].number,R[j].number);
        j++;
        k++;
    }

}


void sortDirectory(struct Entry arr[], int l, int r)
{
    if (l < r)
    {
        
        int m = l+(r-l)/2;
	sortDirectory(arr, l, m);
        sortDirectory(arr, m+1, r);

        merge(arr, l, m, r);
    }
}


void insertEntry(struct Entry s_contact2)
{

	int cmp;
	int exist=0;
	for(int p=0;p<c;p++)
	{
		cmp=strcmp(s_contact2.index,Directory[p].index);
		{
			if(cmp==0)
			{
				printf("please choose the correct index as %d\n",c);
				 exist++;
				 c--;
				break;
			}
		}

		 cmp=strcmp(s_contact2.lname,Directory[p].lname);
		 if(cmp==0)
		 {
			 cmp=strcmp(s_contact2.fname,Directory[p].fname);
			 if(cmp==0)
			 {
				cmp=strcmp(s_contact2.number,Directory[p].number);
					 if(cmp==0)
					 {
						 printf("Entry already exists in the directory\n");
						 exist++;
						 c--;
						 break;

					 }
			 }
		 }


	}
	if(exist==0)
	{
		strcpy(Directory[c].index,s_contact2.index);
		strcpy(Directory[c].fname,s_contact2.fname);
		strcpy(Directory[c].lname,s_contact2.lname);
		strcpy(Directory[c].number,s_contact2.number);
		printf("Entry inserted successfully\n");
		sortDirectory(Directory,0,c);
	}
	

}



void deleteEntry(struct Entry s_contact1)
{
	sortDirectory(Directory,0,c);
	int cmp;

	for(int p=c;p>0;p--)
	{

		 cmp=strcmp(s_contact1.lname,Directory[p].lname);
		 if(cmp==0)
		 {
			 cmp=strcmp(s_contact1.fname,Directory[p].fname);
			 if(cmp==0)
			 {
				 	 for(int a=p;a<=c;a++)
				 	 {
				 		strcpy(Directory[a].index,Directory[a+1].index);
						strcpy(Directory[a].fname,Directory[a+1].fname);
						strcpy(Directory[a].lname,Directory[a+1].lname);
						strcpy(Directory[a].number,Directory[a+1].number);

				 	 }
				 	 break;
			 }
		 }


	}
	c--;

}



void display()
{	printf("in the display");
	
	for(int j=0; j<=c ;j++)
	{
		printf("%s  ",Directory[j].index);
		printf("%s  ",Directory[j].fname);
		printf("%s  ",Directory[j].lname);
		printf("%s  \n",Directory[j].number);

	}

}
void searchDirectory(struct Entry s_contact, int low, int high)
{
	if(low > high)
	{
		printf("Not Found");
	}
	else
	{	
		int mid = (low + high) / 2;
		if(strcmp(s_contact.lname, Directory[mid].lname) == 0)
		{
			if(strcmp(s_contact.fname, Directory[mid].fname) == 0)
			{
				printf("%s %s %s %s",Directory[mid].index, Directory[mid].fname, Directory[mid].lname, Directory[mid].number);
				int a=1;
				if(strcmp(Directory[mid-a].lname, Directory[mid].lname) == 0)			
				{
				if(strcmp(Directory[mid-a].fname, Directory[mid].fname) == 0)
				{
				printf("\n%s %s %s %s",Directory[mid-a].index, Directory[mid-a].fname, Directory[mid-a].lname, Directory[mid-a].number);			}			
				a++;		
				}
				else if(strcmp(Directory[mid+a].lname, Directory[mid].lname) == 0)
				{
					if(strcmp(Directory[mid+a].fname, Directory[mid].fname) == 0)
					{
					printf("\n%s %s %s %s",Directory[mid+a].index, Directory[mid+a].fname, Directory[mid+a].lname, Directory[mid+a].number);			}		
				a++;
				}
				

				return;
			}
			else if(strcmp(s_contact.fname, Directory[mid].fname) < 0)
			{
				searchDirectory(s_contact, 0, mid - 1);
			}
			else
			{
				searchDirectory(s_contact, mid + 1, high);
			}
		} 
		else if(strcmp(s_contact.lname, Directory[mid].lname) < 0)
		{
			searchDirectory(s_contact, 0, mid - 1);
		}
		else
		{
			searchDirectory(s_contact, mid + 1, high);
		}
	}
}
void quick_sort(struct Entry *s_no,int min,int max)
{
for(int i=min;i<=c;i++)
 {
	for(int z=i;z<=c;z++)
		{
			if(strcmp(s_no[i].lname,Directory[z].lname)==0)
			{
				if(strcmp(s_no[i].fname,Directory[z].fname)==0)
				{
					if(strcmp(s_no[i].number,Directory[z].number)>0)
					{
						swap(&s_no[i], &Directory[z]);
					}
				}
			}
		}
}
}
void swap(struct Entry *e1,struct Entry *e2)
{
 	struct Entry temp;
    	memcpy(&temp, e1, sizeof(struct Entry));;
   	memcpy(e1, e2, sizeof(struct Entry));
    	memcpy(e2, &temp, sizeof(struct Entry));
}
int main(void)
{
	int loop=1;
	create_Directory();
	sortDirectory(Directory,0,c);
	quick_sort(Directory,0,c);
	struct Entry s_contact1;
	struct Entry s_contact2;
	struct Entry s_contact3;
	while(loop>0)
	{
	printf("\nPlease choose option\n:");
	printf("1. Show Directory    	(press 1)\n");
	printf("2. Insert    		(press 2)\n");
	printf("3. Search    		(press 3)\n");
	printf("4. Delete    		(press 4)\n");
	printf("5. Exit    		(press 5)\n");

	int choice;
	scanf("%d", &choice);

	printf("You entered: %d\n", choice);


		if(choice==1 || choice==2 || choice==3 ||choice==4 ||choice==5)
		{

			switch(choice)
			{
				case 1: display();
					break;
				case 2:
					c++;
					printf("Enter index as %d:",c);
					fscanf(stdin, "%s", s_contact2.index);
					printf("Enter first name :");
					fscanf(stdin, "%s", s_contact2.fname);
					printf("Enter last name :");
					fscanf(stdin, "%s", s_contact2.lname);
					printf("Enter the number :");
					fscanf(stdin, "%s", s_contact2.number);
					strcat(s_contact2.lname,",");
					insertEntry(s_contact2);
					
					break;
				case 3:	printf("Enter the name :");
    					fscanf(stdin, "%s %s", s_contact3.fname, s_contact3.lname);
					strcat(s_contact3.lname,",");
    					searchDirectory(s_contact3,0,c-1);
					break;
				case 4:
					printf("Enter first name :");
					fscanf(stdin, "%s", s_contact1.fname);
					printf("Enter last name :");
					fscanf(stdin, "%s", s_contact1.lname);
					strcat(s_contact1.lname,",");
					deleteEntry(s_contact1);
					break;
				case 5: loop = 0;
					break;
			}
		}

		else
		{
			printf("enter the correct choice\n");
		}

	}

    return 0;
}















