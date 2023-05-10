#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct client
{
	int id;
	char name[20];
	char phoneno[11];
	char city[30];
}c;

struct laptop
{
	char brand[20];
	char model[20];
	int id;
	char problem[200];
	int price;	
}lap;

void expert(char s[],int x)
{
	int i,flag[4]={0};
	char z1[]="display";
	char z2[]="heating";
	char z3[]="battery";
	char z4[]="speaker";
	
	for(i=0;i<(sizeof(z1)-1);i++)
	{
	
		if(s[i]!=z1[i])
			flag[0]=1;
		else if(s[i]!=z2[i])
			flag[1]=1;
		else if(s[i]!=z3[i])
			flag[2]=1;
		else if(s[i]!=z4[i])
			flag[3]=1;
	}
	if(flag[0]==0)
		printf("Expert : 1.Ajay Mathur\n\n");
	else if(flag[1]==0)
		printf("Expert : 2.Vikas Kumar\n\n");
	else if(flag[2]==0)
		printf("Expert : 3.Vishal Shrivastav\n\n");
	else if(flag[3]==0)
		printf("Expert : 4.Sai Kanhaiya\n\n");
	else
	printf("No expert Found!\n\n");
	
}

int avlid(int x)
{
	FILE *fp;
	int flag=0;
	fp=fopen("client.dat","rb");
	while(fread(&c,sizeof(c),1,fp))
	{
		if(x==c.id)
		{
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;
}

int avlst(int x)
{
	FILE *fp;
	fp=fopen("laptop.dat","rb");
	while(!feof(fp))
	{
		fread(&lap,sizeof(lap),1,fp);
		if(x==lap.id)
		{
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;
}

void addclient()
{
	system("cls");
	int n,i;
	int x=c.id;
	FILE *fp;
	printf("Enter number of client, You want to add in record:");
	scanf("%d",&n);
	struct client c[n];
	for(i=0;i<n;i++)
	{
//		printf("enter id:");
//		fflush(stdin);
//		scanf("%d",&c[i].id);
		c[i].id=++x;
		printf("Enter Name:");
		fflush(stdin);
		gets(c[i].name);
		printf("Enter phone-no:");
		fflush(stdin);
		gets(c[i].phoneno);
		printf("enter city name:");
		fflush(stdin);
		gets(c[i].city);
	}
	
	fp=fopen("client.dat","ab");
	fwrite(&c,sizeof(c),1,fp);
	fclose(fp);
	
	printf("\n\n\tRecord Added\n\n");
}

void addlaptop()
{
	system("cls");
	int n,i;

	FILE *fp;
	printf("Enter no of details,You want to enter:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Enter customer id:");
		fflush(stdin);
		scanf("%d",&lap.id);
		if(avlid(lap.id)==0)
		{
			printf("\n\tCustomer not available with this id,Try again...\n");
			i--;
		}
		else
		{
		printf("Enter brand name:");
		fflush(stdin);
		gets(lap.brand);
		printf("Enter Model:");
		fflush(stdin);
		gets(lap.model);
		printf("write the laptop's problematic component(in lowercase):");
		fflush(stdin);
		gets(lap.problem);
		printf("Enter Price when You Bought:");
		fflush(stdin);
		scanf("%d",&lap.price);
		fp=fopen("laptop.dat","ab");
		fwrite(&lap,sizeof(lap),1,fp);
		fclose(fp);
		}
//		If we open file here wb then It will overwrite again and again
//		if we dont want to append then after closing of Loop we need to fwrite showed in comment and 
//		we have to take lap[n] like c[n] in addclient()
	}
//	fp=fopen("laptop.dat","wb");
//	fwrite(&lap,sizeof(lap),1,fp);
//	fclose(fp);
	
	printf("\n\n\tRecord Added!\n\n");	
}

void viewlaptop()
{
	system("cls");
	char c;
	FILE *fp;
	fp=fopen("laptop.dat","r");
  
	while(fread(&lap,sizeof(lap),1,fp))
	{
		printf("customer-id:%d\tBrand:%s\tmodel:%s\t\tProblem:%s\tInitial Price:%d\t",lap.id,lap.brand,lap.model,lap.problem,lap.price);
		expert(lap.problem,sizeof(lap.problem));
	}
	
	fclose(fp);
  
}

void viewclient()
{
	system("cls");
	FILE *fp;
	fp=fopen("client.dat","r");
	while(fread(&c,sizeof(c),1,fp))
	{
		printf("customer-id:%d\t\tname:%s\t\tphone-no:%s\t\tcity:%s\n\n",c.id,c.name,c.phoneno,c.city);
		
	}
	fclose(fp);
}

void deleteclient()
{
	system("cls");
	FILE *pf,*tf;
	int no;
	printf("enter cid to delete:");
	fflush(stdin);
	scanf("%d",&no);
	pf=fopen("client.dat","rb");
	tf=fopen("tmp.dat","wb");
	if(avlid(no)==0)
		printf("\n\tid not available in record\n");
	else
	{
	while(fread(&c,sizeof(c),1,pf))
	{
		if(no!=c.id)
			fwrite(&c,sizeof(c),1,tf);
	}
	fclose(pf);
	fclose(tf);
	pf=fopen("client.dat","wb");
	tf=fopen("tmp.dat","rb");
	while(fread(&c,sizeof(c),1,tf))
	{
		fwrite(&c,sizeof(c),1,pf);
	}
	fclose(pf);
	fclose(tf);
	printf("\n\n\tDeleted Successfully\n\n");
	}
}

void deletelaptop()
{
	system("cls");
	FILE *pf,*tf;
	pf=fopen("laptop.dat","rb");
	tf=fopen("tmp.dat","wb");
	int m;
	printf("Enter the customer-id to delete laptop details:");
	scanf("%d",&m);
	if(avlst(m)==0)
		printf("\n\tcustomer-id doesn't exist in record\n");
  else
  {
  
	while(fread(&lap,sizeof(lap),1,pf))
	{
		if(m!=lap.id)
			fwrite(&lap,sizeof(lap),1,tf);
	}
	fclose(pf);
	fclose(tf);
	fopen("laptop.dat","wb");
	fopen("tmp.dat","rb");
	while(fread(&lap,sizeof(lap),1,tf))
	{
		fwrite(&lap,sizeof(lap),1,pf);
	}
	fclose(pf);
	fclose(tf);
	printf("\n\n\tDeleted Successfully\n\n");
  }
}

void updateclient()
{
	system("cls");
	FILE *pf,*tf;
	pf=fopen("client.dat","rb");
	tf=fopen("temper.dat","wb");
	int x;
	printf("Enter the id of the element whichnyou want to update: ");
	scanf("%d",&x);
	if(avlid(x)==0)
		printf("\n\tId Doesn't exist in record!\n");
 else
  {
	
	while(fread(&c,sizeof(c),1,pf))
	{
		if(c.id!=x)
		{
			fwrite(&c,sizeof(c),1,tf);
		}
		else
		{
			printf("\tPress 1 to update name:\n\tPress 2 to update Phone-no\n\tPress 3 to update city\n\n");
			int z;
			scanf("%d",&z);
			switch(z)
			{
				case 1:
				fflush(stdin);
				gets(c.name);
				break;
				
				case 2:
				fflush(stdin);
				gets(c.phoneno);
				break;
				
				case 3:
				fflush(stdin);
				gets(c.city);
				break;	
			}
			fwrite(&c,sizeof(c),1,tf);
			
		}	
	}
	fclose(pf);
	fclose(tf);
	pf=fopen("client.dat","wb");
	tf=fopen("temper.dat","rb");
	while(fread(&c,sizeof(c),1,tf))
	{
		fwrite(&c,sizeof(c),1,pf);
	}
	
	fclose(pf);
	fclose(tf);
	printf("\n\tUpdated Successfully!\n");
  }
	
}

void updatelaptop()
{
	system("cls");
	FILE *pf,*tf;
	int m;
	pf=fopen("laptop.dat","rb");
	tf=fopen("temper.dat","wb");
	printf("enter the customer-id to update:");
	scanf("%d",&m);
	if(avlst(m)==0)
		printf("\n\tcustomer-id doesn't Exist in record!\n");
 else
 {
 
	while(fread(&lap,sizeof(lap),1,pf))
	{
		if(lap.id!=m)
			fwrite(&lap,sizeof(lap),1,tf);
		else
		{
			
			printf("\n\tPress 1 to update brand name:\n\tPress 2 to update price:\n\tPress 3 to update problem\n\tPress 4 to update model :\n");
			int z;
			scanf("%d",&z);
			switch(z)
			{
				case 1:
				printf("New Brand name:");
				fflush(stdin);
				gets(lap.brand);
				break;
				
				case 2:
				printf("New Price:");
				fflush(stdin);
				scanf("%d",&lap.price);
				break;
				
				case 3:
				printf("Problem:");
				fflush(stdin);
				gets(lap.problem);
				break;
				
				case 4:
				printf("Model:");
				fflush(stdin);
				gets(lap.model);
				break;
			}
			fwrite(&lap,sizeof(lap),1,tf);
		}
	}
	fclose(pf);
	fclose(tf);
	pf=fopen("laptop.dat","wb");
	tf=fopen("temper.dat","rb");
	while(fread(&lap,sizeof(lap),1,tf))
	{
		fwrite(&lap,sizeof(lap),1,pf);
	}
	fclose(pf);
	fclose(tf);
	printf("\n\n\tUpdated Successfully!\n\n");
	
  } 
}

void search()
{
	system("cls");
	int x;
	FILE *fp,*ft;
	fp=fopen("client.dat","r");
	ft=fopen("laptop.dat","r");
	printf("Enter customer-id to get details:");
	scanf("%d",&x);
	if(avlid(x)==0)
		printf("\n\tCustomer-id not Found!\t\t");
	else
	{
		while(fread(&c,sizeof(c),1,fp))
		{
			if(x==c.id)
			{
				printf("\nclient-details:-\n\tcustomer-id:%d\n\tName:%s,\n\tPhone-no:%s\n\tCity:%s\n\n",c.id,c.name,c.phoneno,c.city);
			}
		}
		fclose(fp);
		while(fread(&lap,sizeof(lap),1,ft))
		{
			if(x==lap.id)
			{
				printf("\nLaptop-details:-\n\tBrand-name:%s\n\tModel:%s\n\tInitial-price:%d\n\tProblem:%s\n\t",lap.brand,lap.model,lap.price,lap.problem);
				expert(lap.problem,sizeof(lap.problem));
			}
		}
		fclose(ft);
	}
}

void idfinder()
{
	system("cls");
	FILE *fp;
	char s[18];
	int i,x=0;
	fp=fopen("client.dat","r");
	printf("enter Phone no to get customer-id:");
	fflush(stdin);
	gets(s);
	while(fread(&c,sizeof(c),1,fp))
	{
		int flag=0;
		for(i=0;i<(sizeof(c.phoneno)-1);i++)
		{
			if(c.phoneno[i]!=s[i])
				flag=1;
		}
		if(flag!=1)
		{
			printf("\n\tid:%d\tname:%s\n",c.id,c.name);
			x=1;
			break;
		}
	}
	if(x==0)
		printf("\n\tNot Found any customer associated with this phone-no!\n\n");
	fclose(fp);
}

int main()
{
	int x,t;
	do
	{
		printf("\n---------------------------------------------------------------------------------------------------\n");
		printf("\nPress 1 to add record of client in the file:\n");
		printf("Press 2 to add details of laptop in the file:\n");
		printf("press 3 to view details of client:\n");
		printf("Press 4 to view record of Laptop:\n");
		printf("Press 5 to delete record:\n");
		printf("Press 6 to Update Record:\n");
		printf("Press 7 to see client details with associated laptop by customer-id:\n");
		printf("Press 8 to find custome-id by mobileno:\n");
		printf("press 9 to exit:\n\n");
		printf("Please select your choice:");
		scanf("%d",&x);
		printf("\n");
		printf("-----------------------------------------------------------------------------------------------------------\n");
		switch(x)
		{
			case 1:
				addclient();
				break;
			
			case 2:
				addlaptop();
				break;
			
			case 3:
				viewclient();
				break;
			
			case 4:
				viewlaptop();
				break;
				
			case 5:
				
				printf("\t1 to delete client details:\n\t2 to delete laptop details:\n\n");
				printf("Enter Your choice: ");
				fflush(stdin);
				scanf("%d",&t);
				switch(t)
				{
					case 1:
						deleteclient();
						break;
					case 2:
						deletelaptop();
						break;
				}
				break;
				
			case 6:
				printf("\t1 to Update client details:\n\t2 to Update laptop details:\n\n");
				printf("Enter Your choice: ");
				fflush(stdin);
				scanf("%d",&t);
				switch(t)
				{
					case 1:
						updateclient();
						break;
					case 2:
						updatelaptop();
						break;
				}
				break;
				
			case 7:
				search();
				break;
				
			case 8:
				idfinder();
				break;
				
			case 9:
				exit(0);
				break;
				
			default:
				system("cls");
				printf("\nYour choice is wrong\nPlease try again...\n");
				break;
		}
	}while(x!=9);
}
