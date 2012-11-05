#include<stdio.h> 

void why_here(void)
{ 
	printf("I am a hacker here!\n"); 
	//_exit(0); 
} 

int my() 
{ 
	int buff[1]; 
	buff[2] = (int)why_here; 
	return 0;
}

int main(int argc,char * argv[]) 
{ 
	int buff[1]; 
	my();
//	buff[2] = (int)why_here; 
	printf( "main\n" );
	return 0;
} 

