#include"tm4c123gh6pm.h"
#include"UART.h"
#include<string.h>
#include<stdlib.h>
#include"GPS.h"
#include "GPIO.h"

// Define the variables declared as extern in GPS.h
char *token; // Used to tokenize the GPS input array
char GPS_input_array[50]; // Array to store GPS input data
char GPS_LOGNAME[] = "$GPRMC,"; // Log name for GPS data
char GPS_2D[12][20]; // 2D array to store parsed GPS data
extern float latitude, longitude; // Latitude and longitude values
bool first_read_successful=false;

// there is problem happened in video cause of memory but i do not change code untill it gives error
// when you run need to define main()****
// I use UART1 to recieve data from Gps 
//the function might be different from video & I will show you what the difference i will used keywoed *difference* to show you big difference
void GPS_READ()
{
	char flag;//will be used in logname check
	char counter=0;// used in filling gps array
	char recieved_char;//for readability
	char i;// i define it twice because program give me error =>used as counter
	// check log name
	do
	{ flag=1;
			for(i=0 ; i<7 ; i++) 
			{
					if(UART1_getChar()!=GPS_LOGNAME[i])
					{
						flag=0;
						break;
	
					}

			}
	}while(flag==0);


	//make sure that array do not contain rubbish
	strcpy(GPS_input_array,"");
	
	do{
			
			recieved_char=UART1_getChar();
			GPS_input_array[counter]=recieved_char;
			counter ++;

			if(recieved_char=='V')// check if the end of the string is reached
			{
				break;
			}

	}while(recieved_char!='E'); // I try to take only needed information from Gps to save storage *difference* 

}



// here no difference bet video 
// note: Egypt coordinates are North and East
// we can remove some code by this note but i do not make that

void GPS_format(){
	char counter_of_token_strings=0;
	token=strtok(GPS_input_array,",");
	
  
	do{
	   	strcpy(GPS_2D[counter_of_token_strings],token);
		token=strtok(NULL,",");
		counter_of_token_strings++;
		 
	
	}while(token!=NULL);

	if (strcmp(GPS_2D[1],"A")==0)
		{
			first_read_successful = true;
			if (strcmp(GPS_2D[3],"N")==0)
			{
				latitude=atof(GPS_2D[2]);
			}
			else
				latitude=-atof(GPS_2D[2]);
			if (strcmp(GPS_2D[5],"W")==0)
			{
				longitude=atof(GPS_2D[4]);
			}
			else
				longitude=-atof(GPS_2D[4]);
	
	}



}




