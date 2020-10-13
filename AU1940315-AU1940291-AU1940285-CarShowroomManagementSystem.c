/*
MADE BY: -  1.SHUBHAM JAIN (AU1940315)
			2.SMIT SHAH (AU1940291)
			3.DHRUVIL PANCHAMIA (AU1940285)
			
PROJECT TITLE: - CAR SHOWROOM MANAGEMENT SYSTEM

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct CarDetails 
{
long onRoadPrice;
char name[30] , brand[30] , maxPower[20] , bodyType[20] , fuelType[10];
int engineDisp , seats , noOfViews; //noOfViews to be 0 at initial stage. Also variant of car not needed.
float mileage , fuelCapacity , bootSpace;
};

/*struct admin 
{
	char userName[20];
	char password[20];
};*/

FILE* fPtr;

char accessedAccount;

void createBox(char title[])
{
	int i;
	printf("\t\t");
	for(i=1;i<=81;i++)
       printf("%c",219);
    printf("\n\t\t%-29c%52c",219,219);
    printf("\n\t\t%-29c%-51s%c",219,title,219);
    printf("\n\t\t%-29c%52c",219,219);
    printf("\n\t\t");
    for(i=1;i<=81;i++)
       printf("%c",219);
}

void updateNoOfViews(struct CarDetails toBeUpdatedCar)
{
	FILE* original = fopen("carDetails.bin","r");
	FILE* temp = fopen("temp.bin","a");
	
	if(original==NULL || temp==NULL)
	{
		printf("File cannot be opened !");
		exit(0);
	}
	
	struct CarDetails car;
	
	while(fread(&car,sizeof(car),1,original))
	{
		if(!strcmpi(car.name,toBeUpdatedCar.name) && !strcmpi(car.brand,toBeUpdatedCar.brand) && !strcmpi(car.fuelType,toBeUpdatedCar.fuelType))
			car.noOfViews++;
		fwrite(&car,sizeof(car),1,temp);
	}
	
	fclose(temp);
	fclose(original);	
	fclose(fPtr);								//reversed the order........................................................................................
	remove("carDetails.bin");
	rename("temp.bin","carDetails.bin");
//	printf("\n%d",x);
	getch();
}

void displayMostViewedCar()
{
	fPtr = fopen("carDetails.bin","a+");
	
	if(fPtr == NULL)
	{
		printf("\n\n\t\t\t\tFile cannot be opened !");
		exit(0);
	}
	
	struct CarDetails car , mostViewedCars[10];
	int i=0 , flag=0;								//made i=0;
	mostViewedCars[0].noOfViews=0;
	
	while(fread(&car,sizeof(car),1,fPtr))
	{
		flag=1;
		if(mostViewedCars[0].noOfViews<car.noOfViews)
		{
			i=1;
			mostViewedCars[0] = car;
		}
		else if(mostViewedCars[0].noOfViews == car.noOfViews)
			mostViewedCars[i++] = car;
	}
	fclose(fPtr);							//added fclose(fPtr);
	if(!flag)
		printf("NO CARS !");
	else
	{
		printf("{%d views}",mostViewedCars[0].noOfViews);
	
		for(i-=1;i>=0;i--)
			printf("\n\t\t\t\t  =>%s %s (%s)",mostViewedCars[i].brand,mostViewedCars[i].name,mostViewedCars[i].fuelType);
	}
}

char displayCarDetails(struct CarDetails car , int signal)	//signal=1 for prompt , signal=0 for only display
{
	system("cls");
	
	createBox("CAR DETAILS");
	
	printf("\n\n-------------------------------------------------------------------");
	printf("\nBRAND:%s",car.brand);
	printf("\n-------------------------------------------------------------------");
	printf("\nName:%s",car.name);
	printf("\n-------------------------------------------------------------------");
	printf("\nOn-Road Price: Rs.%ld",car.onRoadPrice);
	printf("\n-------------------------------------------------------------------");
	printf("\nBody Type:%s",car.bodyType);
	printf("\n-------------------------------------------------------------------");
	printf("\nFuel Type:%s",car.fuelType);
	printf("\n-------------------------------------------------------------------");
	printf("\nFuel Capacity:%0.2f litres",car.fuelCapacity);
	printf("\n-------------------------------------------------------------------");
	printf("\nMileage:%.2f kmpl",car.mileage);
	printf("\n-------------------------------------------------------------------");
	printf("\nNo. of Seats:%d",car.seats);
	printf("\n-------------------------------------------------------------------");
	printf("\nBoot Space:%0.2f litres",car.bootSpace);
	printf("\n-------------------------------------------------------------------");
	printf("\nMaximum Power:%s",car.maxPower);
	printf("\n-------------------------------------------------------------------");
	printf("\nEngine Displacement:%d cc",car.engineDisp);
	printf("\n-------------------------------------------------------------------");
	printf("\nNumber of Views:%d views",car.noOfViews);
		
	if(signal)
	{
		char ans;
		printf("\n\t\t\t\tDo you want to continue(y/n):");
		scanf("%c",&ans);
		return ans;	
	}
	else
	{	/*if(accessedAccount == 'g')
			updateNoOfViews(car);*/
		getch();
		return 0;
	}
}

int addCar()
{
    struct CarDetails car;
    
    while(getchar()!='\n');							//CLEARING INPUT BUFFER
	
	createBox("ADD A CAR");
    
	printf("\n\nENTER CAR DETAILS: - ");
	printf("\n\n-------------------------------------------------------------------");
    printf("\nBrand: ");
    	gets(car.brand);
    	strupr(car.brand);
    printf("-------------------------------------------------------------------");
    printf("\nName: ");
    	gets(car.name);
		strupr(car.name);
	printf("-------------------------------------------------------------------");
	printf("\nFuel Type : ");
    	gets(car.fuelType);
    	strupr(car.fuelType);
    printf("-------------------------------------------------------------------");
    
	//CHECKING FOR DUPLICATE DATA
	FILE* checkFile = fopen("carDetails.bin","r");
	struct CarDetails temp;
	while(fread(&temp,sizeof(temp),1,checkFile))
	{
		if(!strcmpi(car.name,temp.name) && !strcmpi(car.brand,temp.brand) && !strcmpi(car.fuelType,temp.fuelType))
		{
			printf("\n\n\n\t\t\t\tCAR DETAILS ALREADY STORED IN DATABASE ! TRY AGAIN ");
			return 0;
		}
	}
	fclose(checkFile);


    printf("\nMaximum Power: ");
	    gets(car.maxPower);
	    strupr(car.maxPower);
	printf("-------------------------------------------------------------------");
    printf("\nBody Type: ");
    	gets(car.bodyType);
    	strupr(car.bodyType);
    printf("-------------------------------------------------------------------");
    printf("\nFuel Capacity (litres): ");
    	scanf("%f",&car.fuelCapacity);
    printf("-------------------------------------------------------------------");
    printf("\nMileage (kmpl): ");
	    scanf("%f",&car.mileage);
	printf("-------------------------------------------------------------------");
    printf("\nEngine Displacement (cc): "); 
	    scanf("%d",&car.engineDisp);
	printf("-------------------------------------------------------------------");
    printf("\nNumber of Seats: ");
	    scanf("%d",&car.seats);
	printf("-------------------------------------------------------------------");
    printf("\nBoot Space (litres): ");
    	scanf("%f",&car.bootSpace);
    printf("-------------------------------------------------------------------");
	printf("\nOn Road Price: Rs.");
		scanf("%ld",&car.onRoadPrice);
	printf("-------------------------------------------------------------------");
	
	car.noOfViews=0;
	
	displayCarDetails(car,0);
	getch();
	
	fPtr=fopen("carDetails.bin","a+");
    if(fPtr==NULL)
    {
    	printf("File cannot be opened !!");
    	exit(0);
	}
	fwrite(&car,sizeof(car),1,fPtr);
	fclose(fPtr);    
	
	printf("\n\n\t\t\t\t\tCAR DETAILS STORED SUCCESSFULLY !!");
	getch();
	
	return 1;
} 

struct CarDetails newCarDetails()
{
	system("cls");
	
	struct CarDetails car;
	
	while(getchar()!='\n');					//CLEARING INPUT BUFFER
	
	printf("\n\nEnter new Details:");
	printf("\n\n-------------------------------------------------------------------");
    printf("\nBrand: ");
   		gets(car.brand);
   		strupr(car.brand);
   	printf("-------------------------------------------------------------------");
   	printf("\nName: ");
    	gets(car.name);
    	strupr(car.name);
    printf("-------------------------------------------------------------------");
    printf("\nFuel Type : ");
    	gets(car.fuelType);
    	strupr(car.fuelType);
    printf("-------------------------------------------------------------------");
    	
    //CHECKING FOR DUPLICATE DATA	
   	FILE* checkFile = fopen("carDetails.bin","r");
	struct CarDetails temp;
	while(fread(&temp,sizeof(temp),1,checkFile))
	{
		if(!strcmpi(car.name,temp.name) && !strcmpi(car.brand,temp.brand) && !strcmpi(car.fuelType,temp.fuelType))
		{
			printf("\n\n\n\t\t\t\t\tCar Detail already stored in database ! TRY AGAIN ");
			car.seats=0;
			return car;
		}
	}
	fclose(checkFile);
    
   	printf("\nMaximum Power: ");
    	gets(car.maxPower);
    	strupr(car.maxPower);
    printf("-------------------------------------------------------------------");
   	printf("\nBody Type: ");
	   	gets(car.bodyType);
	   	strupr(car.bodyType);
	printf("-------------------------------------------------------------------");
    printf("\nFuel Capacity (litres): ");
    	scanf("%f",&car.fuelCapacity);
    printf("-------------------------------------------------------------------");
   	printf("\nMileage (kmpl): ");
    	scanf("%f",&car.mileage);
    printf("-------------------------------------------------------------------");
   	printf("\nEngine Displacement (cc): "); 
	 	scanf("%d",&car.engineDisp);
	printf("-------------------------------------------------------------------");
    printf("\nNumber of Seats: ");
	   	scanf("%d",&car.seats);
	printf("-------------------------------------------------------------------");
    printf("\nBoot Space (litres): ");
    	scanf("%f",&car.bootSpace);
    printf("-------------------------------------------------------------------");
	printf("\nOn Road Price: Rs.");
		scanf("%ld",&car.onRoadPrice);
	printf("-------------------------------------------------------------------");
			
	car.noOfViews=0;
	
	return car;
}

void updateCar() 										
{	
	fPtr=fopen("carDetails.bin","r");
	FILE* fTemp=fopen("temp.bin","a");			//Temporary File Pointer
	if(fPtr==NULL || fTemp==NULL)
	{
		printf("File cannot be opened !!");
		exit(0);
	}
	while(getchar()!='\n');						//CLEARING INPUT BUFFER
	
	createBox("UPDATE A CAR");
    
    struct CarDetails car;
    char enteredName[30] , enteredBrand[30] , enteredFuelType[10];
	int flag=0;
	
	printf("\n\nENTER CAR DETAILS:\n\n");
	printf("\n\n-------------------------------------------------------------------");
	printf("\nBrand:");
		gets(enteredBrand);
	printf("-------------------------------------------------------------------");
	printf("\nName:");
		gets(enteredName);
	printf("-------------------------------------------------------------------");
	printf("\nFuel Type:");
		gets(enteredFuelType);
	printf("-------------------------------------------------------------------");
	
	while(fread(&car,sizeof(car),1,fPtr))
	{
		if(!strcmpi(car.name,enteredName) && !strcmpi(car.brand,enteredBrand) && !strcmpi(car.fuelType,enteredFuelType))
		{		
			int ans=displayCarDetails(car,1);
			if(ans=='y' || ans=='Y')
			{
				struct CarDetails newCar = newCarDetails();	
				while(newCar.seats==0)
					newCar = newCarDetails();
				fwrite(&newCar,sizeof(newCar),1,fTemp);
				printf("\n\n\n\t\t\t\tCar Updated Successfully !");
			}
			else if(ans=='n')
				fwrite(&car,sizeof(car),1,fTemp);
			
			flag=1;
		}
		else
			fwrite(&car,sizeof(car),1,fTemp);
	}
	fclose(fTemp);
	fclose(fPtr);
	remove("carDetails.bin");
	rename("temp.bin","carDetails.bin");
	if(!flag)
	{
		printf("\n\n\t\tCAR NOT FOUND IN DATABASE !!");
		getch();	
	}
}

void deleteCar()
{	
	fPtr = fopen("carDetails.bin","r");
	FILE* fTemp = fopen("temp.bin","a");
	
	if(fPtr==NULL || fTemp==NULL)
	{
		printf("\n\n\t\t\t\tFILE CANNOT BE OPENED !");
		exit(0);
	}
	
	while(getchar()!='\n');									//CLEARING INPUT BUFFER
	
	createBox("DELETE A CAR");
	
	struct CarDetails car;
	char enteredName[30] , enteredBrand[30] , enteredFuelType[10];
	int flag=0;
	
	printf("\n\nENTER CAR DETAILS:\n\n");
	printf("\n\n-------------------------------------------------------------------");
	printf("\nBrand:");
		gets(enteredBrand);
	printf("-------------------------------------------------------------------");
	printf("\nName:");
		gets(enteredName);
	printf("-------------------------------------------------------------------");
	printf("\nFuel Type:");
		gets(enteredFuelType);
	printf("-------------------------------------------------------------------");
	
	while(fread(&car,sizeof(car),1,fPtr))
	{
			if(!strcmpi(car.name,enteredName) && !strcmpi(car.brand,enteredBrand) && !strcmpi(car.fuelType,enteredFuelType))
			{
				flag=1;
				char ans=displayCarDetails(car,1);
				if(ans!='y' && ans!='Y')
					fwrite(&car,sizeof(car),1,fTemp);
				else
				{
					printf("\n\n\n\t\t\t\tRECORD DELETED SUCCESSFULLY FROM DATABASE !");
					getch();
				}
			}
			else
				fwrite(&car,sizeof(car),1,fTemp);
	}
	
	fclose(fTemp);
	fclose(fPtr);
	remove("carDetails.bin");
	rename("temp.bin","carDetails.bin");
	
	if(!flag)
	{
		printf("\n\n\n\t\t\t\tNO SUCH RECORD FOUND IN DATABASE !");
		getch();
	}
}

void showMatchedCars(struct CarDetails matchedCars[30],int i)
{
	int choice;
	do
	{	
	
		system("cls");
					
		createBox("MATCHED CARS");
			
		int k;
		printf("\n\n0.EXIT");	
		for(k=0;k<i;k++)					
			printf("\n%d.%s %s (%s)",k+1,matchedCars[k].brand,matchedCars[k].name,matchedCars[k].fuelType);	
		printf("\n\nENTER YOUR CHOICE:");
		scanf("%d",&choice);
		if(choice!=0)
		{		
			displayCarDetails(matchedCars[choice-1],0);
		}
	}while(choice!=0);
}

void searchByParameter(char parameter[])
{
	char title[] = "SEARCH BY ";
	strcat(title,parameter);
	createBox(title);
	
	fPtr = fopen("carDetails.bin","r");
	if(fPtr==NULL)
	{
		printf("\n\n\t\t\t\tFILE CANNOT BE OPENED !");
		exit(0);
	}
	
	while(getchar()!='\n');							//CLEARING INPUT BUFFER
	
	int i=0;
	struct CarDetails car ;
	struct CarDetails matchedCars[10];
	
	if(!strcmpi(parameter,"BRAND & NAME"))
	{
		char enteredBrand[30] , enteredName[30];
		printf("\n\n\nEnter Brand:");
			gets(enteredBrand);
		printf("\n\nEnter Name:");
			gets(enteredName);	
		while(fread(&car,sizeof(car),1,fPtr))
		{
			if(!strcmpi(car.brand,enteredBrand) && !strcmpi(car.name,enteredName))
				matchedCars[i++]=car;
		}
	}
	else
	{
		char enteredParameter[30];
		printf("\n\n\nEnter %s:",parameter);
			gets(enteredParameter);
		
		while(fread(&car,sizeof(car),1,fPtr))
		{
			if(!strcmpi(car.brand,enteredParameter) && !strcmpi(parameter,"BRAND"))
				matchedCars[i++]=car;
			else if(!strcmpi(car.name,enteredParameter) && !strcmpi(parameter,"NAME"))
				matchedCars[i++]=car;
		}
	}
	
	fclose(fPtr);
	
	if(i==0)
	{
		printf("\n\n\n\t\t\t\tNO SUCH CARS IN THE DATABASE!");
		getch();
	}
	else
		showMatchedCars(matchedCars,i);
}

void searchCar()
{
	
	int choice;
	
	do
	{
		system("cls");
		
		createBox("SEARCH A CAR");
		
		printf("\n\nSEARCH CAR BY: - ");
		printf("\n\n0.Exit");
		printf("\n1. Only Brand");
		printf("\n2. Only Name ");
		printf("\n3. Brand and Name");
		printf("\n\nEnter your choice: ");
		scanf("%d",&choice);
		system("cls");
		switch(choice){
			case 0:
				break;
			case 1:searchByParameter("BRAND");
				break;
			case 2:searchByParameter("NAME");
				break;
			case 3:searchByParameter("BRAND & NAME");
				break;	
			default:
				printf("Wrong choice. Try again ");
		}	
	}while(choice!=0);
}

int displayListOfCars()
{
	system("cls");
	
	createBox("LIST OF CARS");
	
	struct CarDetails car;
	int flag=0,i=1;
		
	while(fread(&car,sizeof(car),1,fPtr))
	{
		if(flag!=1)
		{
			flag=1;
			printf("\n\n\n0.EXIT");
		}
		printf("\n%d.%s %s (%s)",i++,car.brand,car.name,car.fuelType);		
	}	
	if(!flag)
	{
		printf("\n\n\n\n\t\t\t\tNO CARS IN THE DATABASE !");
		return 0;
	}
	else
		return i-1;
}

void displayCars()
{	
	fPtr = fopen("carDetails.bin","r");
	if(fPtr==NULL)
	{
		printf("\n\n\n\t\t\t\tFILE CANNOT BE OPENED !");
		exit(0);
	}	
	
	int choice;
	
	do
	{
		struct CarDetails car;
		int totalCars = displayListOfCars();
		if(totalCars)
		{
			printf("\n\nENTER YOUR CHOICE:");
			scanf("%d",&choice);
			if(choice==0)
				break;
			else if(choice>0 && choice<=totalCars)
			{
				fseek(fPtr,(choice-1)*sizeof(car),SEEK_SET);
				fread(&car,sizeof(car),1,fPtr);
				displayCarDetails(car,0);
			}
			else
			{			
				printf("Invalid Input !");
				getch();
			}
			//fclose(fPtr);					//commented fclose(fPtr);
			fseek(fPtr,0,SEEK_SET); 	//assigned fPtr to fopen()	Initially no fPtr was there in the statement
		}
		else
			break;
	}while(choice!=0);
	fclose(fPtr);
}

void compareCar()
{
	fPtr = fopen("carDetails.bin","r");
	if(fPtr==NULL)
	{
		printf("\n\n\n\n\t\t\t\tFile cannot be opened !");
		exit(0);
	}
	
	int choice1 , choice2 ;
	
	do
	{
		fseek(fPtr , 0 , SEEK_SET);
		int flag = displayListOfCars();
		if(flag)
		{
			struct CarDetails car1;
			struct CarDetails car2;
			
			printf("\n\nENTER YOUR CHOICE 1:");
			scanf("%d",&choice1);
			if(choice1==0)
				break;
			
			printf("\nENTER YOUR CHOICE 2:");
			scanf("%d",&choice2);
			if(choice2==0)
				break;
			if(choice2==choice1)
				continue;
				
			fseek(fPtr,(choice1-1)*sizeof(car1),SEEK_SET);
			fread(&car1,sizeof(car1),1,fPtr);
			fseek(fPtr,(choice2-1)*sizeof(car2),SEEK_SET);
			fread(&car2,sizeof(car2),1,fPtr);
			
			system("cls");
			
			createBox("CAR-1 VS CAR-2");
			
			printf("\n\n\nBRAND :%-41s||\tBRAND : %s",car1.brand,car2.brand);
			printf("\n------------------------------------------------------------------------------------------------------");
			printf("\nCar :%-43s||\tCar : %s",car1.name,car2.name);
			printf("\n------------------------------------------------------------------------------------------------------");
			printf("\nOn Road Price :%-33ld||\tOn Road Price : %ld",car1.onRoadPrice,car2.onRoadPrice);
			printf("\n------------------------------------------------------------------------------------------------------");
			printf("\nBody Type :%-37s||\tBody Type : %s",car1.bodyType,car2.bodyType);
			printf("\n------------------------------------------------------------------------------------------------------");
			printf("\nFuel Type :%-37s||\tFuel Type : %s",car1.fuelType,car2.fuelType);
			printf("\n------------------------------------------------------------------------------------------------------");
			printf("\nFuel Capacity :%-33.2f||\tFuel Capacity : %0.2f",car1.fuelCapacity,car2.fuelCapacity);
			printf("\n------------------------------------------------------------------------------------------------------");
			printf("\nMileage :%-39.2f||\tMileage : %0.2f",car1.mileage,car2.mileage);
			printf("\n------------------------------------------------------------------------------------------------------");
			printf("\nNo. of seats :%-34d||\tNo. of seats : %d",car1.seats,car2.seats);
			printf("\n------------------------------------------------------------------------------------------------------");
			printf("\nBoot Space :%-36.2f||\tBoot Space : %0.2f",car1.bootSpace,car2.bootSpace);
			printf("\n------------------------------------------------------------------------------------------------------");
			printf("\nMaximum Power :%-33s||\tMaximum Power : %s",car1.maxPower,car2.maxPower);
			printf("\n------------------------------------------------------------------------------------------------------");
			printf("\nEngine Displacement :%-27d||\tEngine Displacement : %d",car1.engineDisp,car2.engineDisp);
			printf("\n------------------------------------------------------------------------------------------------------");
			getch();
		}
		else
			break;
	}while(choice1!=0 || choice2!=0);
	
	fclose(fPtr);
}

void adminMenu() 
{
	int choice;
	accessedAccount = 'a';
	do
	{
		system("cls");
		
		createBox("CAR SHOWROOM MANAGEMENT SYSTEM");
		
		printf("\n\n\t\t\t\t\tADMIN MENU"); 
		//printf("\n\n\t\tMOST VIEWED CAR : ");
		//displayMostViewedCar();					//******************************************
		printf("\n\n\n0.Exit");    	
    	printf("\n1.Add car");
    	printf("\n2.Update/Edit car");
    	printf("\n3.Delete car");
    	printf("\n4.Search car");
    	printf("\n5.Display whole car list");
    	printf("\n\n\nEnter YOUR CHOICE : ");
    	scanf("%d",&choice);
		system("cls");	   
    	switch(choice)
		{
	   
	    	case 0:
		    	break;   
			case 1:
				{					
					int flag=addCar();
					while(flag==0)
					{				
						system("cls");	
						flag=addCar();
					}
				}	
				break;
			case 2:
				updateCar();
				break;
			case 3:
				deleteCar();
				break;
			case 4:
				searchCar();
				break;
			case 5:
		   		displayCars();
				break;
			default:
		       printf("Wrong choice. Try Again!!!");       
		}
	}while(choice!=0);
}


void adminLogin()
{
    system("cls");
	
	while(getchar()!='\n');						//CLEARING INPUT BUFFER
	
    char userName[20],password[30];
    
    createBox("ADMIN LOGIN");
    
    printf("\n\n\nUser Name : ");
	gets(userName);
	int i;
    char ch;
    printf("Password  : ");
    for(i=0; i<30;)							//FOR PRINTING * INSTEAD OF INPUT CHARACTER
    {
	    ch=getch();            
       	if(ch!=13){
        	if(ch==8 && i!=0){
	        	printf("\b \b");
	            i--;
	        }
	        if(ch!=8){
	        	printf("*");
	            password[i++]=ch;
    	    }
    	}
    	else{
            break;
        }
    }
    password[i]='\0';
	
	if(!strcmp(userName,"guest") && !strcmp(password,"guest"))
		{
        	printf("\nLogin successful !");
        	Sleep(100);
        	printf("\n\n\t\t\t\t\tWELCOME ADMIN");
        	getch();
        	adminMenu();        	
    	}
	else			
	{
		printf("\n\n\n\n\t\t\t\tWrong Username or Password !");
		getch();
	}
}

void guestMenu()
{
	int choice;
	accessedAccount = 'g';
	do
	{
		system("cls");
		createBox("CAR SHOWROOM MANAGEMENT SYSTEM");
		printf("\n\n\t\t\t\t\t\tGUEST MENU"); 
		//printf("\n\n\t\tMOST VIEWED CAR : ");
		//displayMostViewedCar();
		printf("\n\n\n0.EXIT");
    	printf("\n1.Search Car");
    	printf("\n2.Display Car");
    	printf("\n3.Compare Car");
    	printf("\n\nENTER YOUR CHOICE:");
    	scanf("%d",&choice);
    	switch(choice) {
	    	case(0):
	    		break;
	    	case(1):
	    		searchCar();
	    		break;
	    	case(2):
	    		displayCars();
	    		break;
	    	case(3):
	    		compareCar();
	    		break;
    		default:
    			printf("Wrong choice. Try Again!!!");
		}
	}while(choice!=0);
}

void login() 
{
	int choice;
	do
	{
		system("cls");
	
		createBox("LOGIN");
		
	    printf("\n\n\n\n0.EXIT");
	    printf("\n1.Login as Admin");
	    printf("\n2.Login as Guest");
	    printf("\n\n\nEnter your choice : ");
	    scanf("%d",&choice);
	    switch(choice) 
		{
    		case 0:{
				break;
			}   
			case 1:
				adminLogin();
				break;
			case 2:
				guestMenu();
				break;
			default:{
		       printf("Wrong choice. Try Again!!!");
		       getch();
			}
		}
	}while(choice!=0);
}

void wlcmPage()
{
	int k;
	printf("\n\n\n\n\n\n\n\t\t\t Welcome to Car Showroom Management System\n\n");
	printf("\t\t\t\t\tLOADING");
	for (k=0;k<20;k++) 
	{
		printf(".");
		Sleep(100);
		if(k%3==0 && k!=0)
			printf("\b \b\b \b\b \b");
		
	}
	printf("\n\n\n\t\t\t Press any key to continue...");
	getch();
	login();
}


void main()
{
    wlcmPage();		
}
