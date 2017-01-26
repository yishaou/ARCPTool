// test1.cpp 
//

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include "stdafx.h"


//#include<iostream>
//#include<string>

//#include <math.h>
//#include <conio.h>


#include "engine.h"

//#pragma comment(lib, "libeng.lib")
//#pragma comment(lib, "libmx.lib")
//#pragma comment(lib, "libmat.lib")

#define GET_ARRAY_LEN(arrays,len){len = (sizeof(arrays) / sizeof(arrays[0]));}

struct Result{
 float coordation;
 Result *next;
};

Result *p=NULL;
Result *node=NULL;
//Result *head=NULL;

//int iSearchNum = 0;//the number of half search

struct Node{
	float value;
	float coordation;
};

void search(Node* nodemin, Node* nodemax, float gap, float step)
{
	if(nodemin->coordation + step == nodemax->coordation)
		return;
	float difference = nodemax->value - nodemin->value;
	if(difference > gap)
	{
		Node *mid = new Node;

		float fbisection = (nodemax->coordation + nodemin->coordation)/2;
		int i=1;

		while(true)
		{
			if(nodemin->coordation + step * i >= fbisection)
			{
				mid->coordation = nodemin->coordation + step * i;
				break;
			}
			i++;
		}

		

		printf("%1f input new value: \n", mid->coordation);
		float dValue;
		scanf("%f", &dValue);
		mid->value = dValue;

		Result *node=new Result;
		node->coordation = mid->coordation; 
		node->next = NULL;
		
		p->next = node;
		p= node;

		/*if(mid->value >= nodemin->value)
		{*/
		search(nodemin, mid, gap, step);
		search(mid, nodemax, gap, step);
		//}
	}
	else
	{
		return;
	}
}



///value
float searchTOP(float startmin, float value, float step)
{
	float fResult = 0.0;
	int n=1;
	while(true)
	{
		if(startmin + step*n>=value)
		{
			fResult = startmin + step*n;
			break;
		}
		n++;
	}
	
	return fResult;
}

int searchArrayIndex(float a[], float value, int length)
{
	int index = -1;
	for(int i=0; i<length; i++)
	{
		if(a[i] == value)
		{
			index = i;
			break;
		}
	}
	return index;
}

float MEM[13] = {2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8};
float MEMmin = 2;//
float MEMmax = 8;//
//int MEMnum = 0;//
Result *MEMhead=NULL;//
int MEMArraymin = 0;///
int MEMArraymax = 12;//
int MEMnum = 0;///

float CPU[7] = {2, 3, 4, 5, 6, 7, 8};
float CPUmin = 2;
float CPUmax = 8;
//int CPUnum = 0;//
Result *CPUhead = NULL;
int CPUArraymin = 0;
int CPUArraymax = 6;
int CPUnum = 0;


float NET[17] = {20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100};
float NETmin = 20;
float NETmax = 100;
//int NETnum = 0;//
Result *NEThead = NULL;
int NETArraymin = 0;
int NETArraymax = 16;
int NETnum = 0;

float WRITE[21] = {20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120};
float WRITEmin = 20;
float WRITEmax = 120;
//int WRITEnum = 0;//
Result *WRITEhead = NULL;
int WRITEArraymin = 0;
int WRITEArraymax = 20;
int WRITEnum = 0;

float READ[24] = {20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135};
float READmin = 20;
float READmax = 135;
//int READnum = 0;//
Result *READhead = NULL;
int READArraymin = 0;
int READArraymax = 23;
int READnum = 0;

Engine *ep;

//cpu
void runTestPrograme(float mem, float cpu, float net, float write, float read)
{
	//double time[10] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };

	//mxArray *T = NULL;
	//if (!(ep = engOpen(""))) {
	//	fprintf(stderr, "\nCan't start MATLAB engine\n");
	//	return;
	//}
	//T = mxCreateDoubleMatrix(1, 10, mxREAL);
	//memcpy((void *)mxGetPr(T), (void *)time, sizeof(time));
	///*
	// * Place the variable T into the MATLAB workspace
	// */
	//engPutVariable(ep, "T", T);

	//engClose(ep);


	if(mem <= MEMmin)
	{
		MEMmax = MEMmin;
		MEMArraymax = MEMArraymin;
	}
	else
	{
		MEMmax = searchTOP(MEMmin, mem, 0.5);
		MEMArraymax = searchArrayIndex(MEM, MEMmax, 13);
	}


	if(cpu <= 2)
	{
		CPUmax = CPUmin;
		CPUArraymax = CPUArraymin;
	}
	else if(cpu >= 8)
	{
		CPUmax = 8;
		CPUArraymax = 6;
	}
        else 
        {
                CPUmax = searchTOP(CPUmin, cpu, 1)+1;
                CPUArraymax = searchArrayIndex(CPU, CPUmax, 7);

        }

	if(net <= NETmin)
	{
		NETmax = NETmin;
		NETArraymax = NETArraymin;
	}
	else
	{
		NETmax = searchTOP(NETmin, net, 5);
		NETArraymax = searchArrayIndex(NET, NETmax, 17);
	}

	if(write <= WRITEmin)
	{
		WRITEmax = WRITEmin;
		WRITEArraymax = WRITEArraymin;
	}
	else
	{
		WRITEmax = searchTOP(WRITEmin, write, 5);
		WRITEArraymax = searchArrayIndex(WRITE, WRITEmax, 21);
	}

	if(read <= READmin)
	{
		READmax = READmin;
		READArraymax = READArraymin;
	}
	else
	{
		READmax = searchTOP(READmin, read, 5);
		READArraymax = searchArrayIndex(READ, READmax, 24);
	}



	///get the ceiling point
	if(MEMmax != MEMmin)
	{
		printf("input mem %1f value:\n", MEMmin);
		float dValue;
		scanf("%f", &dValue);
		Node *nodemin = new Node;
	    nodemin->value = dValue;
	    nodemin->coordation = MEMmin;


		printf("input mem %1f value: \n", MEMmax);
		scanf("%f", &dValue);
		Node *nodemax = new Node;
	    nodemax->value = dValue;
	    nodemax->coordation = MEMmax;


		printf("input the threashold of memory: \n");
		scanf("%f", &dValue);

		
		node = new Result;
	    node->coordation = MEMmin;
		MEMhead = node;
		p=node;

		search(nodemin, nodemax, dValue, 0.5);


		node = new Result;
	    node->coordation = nodemax->coordation;
	    node->next = NULL;
	    p->next = node;

	}
	else
	{
		MEMhead = new Result;
		MEMhead->coordation = MEMmax;
		MEMhead->next = NULL;
	}
	Result* r = MEMhead;

    printf("the memory value are: \n");

    while(r !=NULL)
	{
	    printf("%f\n", r->coordation);
        r=r->next;
		MEMnum++;
	}


	////cpu ceiling point
	if(CPUmax != CPUmin)
	{
		printf("input CPU%1f value: \n", CPUmin);
		float dValue;
		scanf("%f", &dValue);
		Node *nodemin = new Node;
	    nodemin->value = dValue;
	    nodemin->coordation = CPUmin;


		printf("input cpu %1f value\n", CPUmax);
		scanf("%f", &dValue);
		Node *nodemax = new Node;
	    nodemax->value = dValue;
	    nodemax->coordation = CPUmax;


		printf("input cpu threashold: \n");
		scanf("%f", &dValue);

		
		node = new Result;
	    node->coordation = CPUmin;
		CPUhead = node;
		p=node;

		search(nodemin, nodemax, dValue, 1);


		node = new Result;
	    node->coordation = nodemax->coordation;
	    node->next = NULL;
	    p->next = node;

		
	}
	else
	{
		CPUhead = new Result;
		CPUhead->coordation = CPUmax;
		CPUhead->next = NULL;
	}
	printf("the cpu values are: \n");

	r = CPUhead;
    while(r !=NULL)
	{
	    printf("%f\n", r->coordation);
        r=r->next;
		CPUnum++;
	}


	/////network 
	if(NETmax != NETmin)
	{
		printf("input network %1f value\n", NETmin);
		float dValue;
		scanf("%f", &dValue);
		Node *nodemin = new Node;
	    nodemin->value = dValue;
	    nodemin->coordation = NETmin;


		printf("input newtork %1f value \n", NETmax);
		scanf("%f", &dValue);
		Node *nodemax = new Node;
	    nodemax->value = dValue;
	    nodemax->coordation = NETmax;


		printf("input the network threshold\n");
		scanf("%f", &dValue);

		
		node = new Result;
	    node->coordation = NETmin;
		NEThead = node;
		p=node;

		search(nodemin, nodemax, dValue, 5);

		

		node = new Result;
	    node->coordation = nodemax->coordation;
	    node->next = NULL;
	    p->next = node;

		
	}
	else
	{
		NEThead = new Result;
		NEThead->coordation = NETmax;
		NEThead->next = NULL;
	}
	printf("the network values are \n");

	r = NEThead;
    while(r !=NULL)
	{
	    printf("%f\n", r->coordation);
        r=r->next;
		NETnum++;
	}


	////disk write
	if(WRITEmax != WRITEmin)
	{
		printf("input disk write %1f value\n", WRITEmin);
		float dValue;
		scanf("%f", &dValue);
		Node *nodemin = new Node;
	    nodemin->value = dValue;
	    nodemin->coordation = WRITEmin;


		printf("input disk write %1f value\n", WRITEmax);
		scanf("%f", &dValue);
		Node *nodemax = new Node;
	    nodemax->value = dValue;
	    nodemax->coordation = WRITEmax;


		printf("input disk write threshold\n");
		scanf("%f", &dValue);

		
		node = new Result;
	    node->coordation = WRITEmin;
		WRITEhead = node;
		p=node;

		search(nodemin, nodemax, dValue, 5);

		

		node = new Result;
	    node->coordation = nodemax->coordation;
	    node->next = NULL;
	    p->next = node;

		
	}
	else
	{
		WRITEhead = new Result;
		WRITEhead->coordation = WRITEmax;
		WRITEhead->next = NULL;
	}
	printf("the disk write value are\n");

	r = WRITEhead;
    while(r !=NULL)
	{
	    printf("%f\n", r->coordation);
        r=r->next;
		WRITEnum++;
	}

	////disk read
	if(READmax != READmin)
	{
		printf("input the disk read %1f value\n", READmin);
		float dValue;
		scanf("%f", &dValue);
		Node *nodemin = new Node;
	    nodemin->value = dValue;
	    nodemin->coordation = READmin;


		printf("input the disk read %1f value\n", READmax);
		scanf("%f", &dValue);
		Node *nodemax = new Node;
	    nodemax->value = dValue;
	    nodemax->coordation = READmax;


		printf("input the write read threshod\n");
		scanf("%f", &dValue);

		
		node = new Result;
	    node->coordation = READmin;
		READhead = node;
		p=node;

		search(nodemin, nodemax, dValue, 5);

		

		node = new Result;
	    node->coordation = nodemax->coordation;
	    node->next = NULL;
	    p->next = node;

		
	}
	else
	{
		READhead = new Result;
		READhead->coordation = READmax;
		READhead->next = NULL;
	}
	printf("the disk read values are \n");

	r = READhead;
    while(r !=NULL)
	{
	    printf("%f\n", r->coordation);
        r=r->next;
		READnum++;
	}


	float (*Interpolation)[7][17][21][24] = new float[13][7][17][21][24];
	for(int i=0; i<24; i++)
	{
		for(int j=0; j<21; j++)
		{
			for(int l=0; l<17; l++)
			{
				for(int m=0; m<13; m++)
				{
					for(int n=0; n<7;n++)
					{
						Interpolation[m][n][l][j][i] = -1;
					}
				}
			}
		}
	}
	
	
	
	
	

	                                        Result* AMEM = MEMhead;
                                        while(AMEM != NULL){
        Result* AREAD = READhead;

        while(AREAD != NULL)
	{
		Result* AWRITE = WRITEhead;
		while(AWRITE != NULL)
		{
			Result* ANET = NEThead;
			while(ANET != NULL)
			{
				Result* ACPU = CPUhead;
				while(ACPU != NULL)
				{
						float fr = AREAD->coordation;
						float fw = AWRITE->coordation;						
						float fn = ANET->coordation;
						float fc = ACPU->coordation;
						float fm = AMEM->coordation;

						int ir = searchArrayIndex(READ, fr, 24);
						int iw = searchArrayIndex(WRITE, fw, 21);						
						int in = searchArrayIndex(NET, fn, 17);
						int ic = searchArrayIndex(CPU, fc, 7);
						int im = searchArrayIndex(MEM, fm, 13);

						printf("input the sensitivity of memory%1f;CPU %1f;network %1f;disk write %1f;disk read %1f\n", fm, fc, fn, fw, fr);
		                float dValue;
		                scanf("%f", &dValue);
						Interpolation[im][ic][in][iw][ir] = dValue;
					
					ACPU = ACPU->next;
				}
				ANET = ANET->next;
			}
			AWRITE = AWRITE->next;
		}
		AREAD = AREAD->next;
	}
                                              AMEM = AMEM->next;}

clock_t start,end;
start=clock();

                                                if (!(ep = engOpen("")))
                                                {
                                                        printf("\nCan't start MATLAB engine\n");
                                                        return;
                                                }

	if(CPUArraymax != CPUArraymin && CPUArraymax + 1 - CPUnum > 0)
	{
		for(int i = READArraymin; i <= READArraymax; i++)
		{
			for(int j = WRITEArraymin; j <= WRITEArraymax; j++)
			{
				for(int l = NETArraymin; l <= NETArraymax; l++)
				{
					for(int m = MEMArraymin; m <= MEMArraymax; m++)
					{
						double *knowcoordation = new double[CPUnum];
						double *knowdata = new double[CPUnum];
						double *unknowcoordation = new double[CPUArraymax + 1 - CPUnum];
						//double *unknowdata = new double[CPUArraymax + 1- CPUnum];

						int p = 0;
						int q = 0;
						for(int n = CPUArraymin; n <= CPUArraymax; n++)
						{
							if(Interpolation[m][n][l][j][i] != -1)
							{
								knowcoordation[p] = CPU[n];
								knowdata[p] = Interpolation[m][n][l][j][i];
								p++;
							}
							else
							{
                                                                if (q== CPUArraymax + 1 - CPUnum)
                                                                break;
								unknowcoordation[q] = CPU[n];
								q++;
							}
						}

                                                if (p==0)
                                                {
                                                   delete knowcoordation;
                                                   delete knowdata;
                                                   delete unknowcoordation;
                                                   continue;
                                                }

						mxArray *C = NULL;////knowcoordation
						mxArray *D = NULL;////knowdata
						mxArray *UC = NULL;////unknowcoordation
			//			mxArray *UD = NULL;////unknowdata

	//					if (!(ep = engOpen(""))) 
	//					{
	//						printf("\nCan't start MATLAB engine\n");
	//						return;
	//					}

						C = mxCreateDoubleMatrix(1, CPUnum, mxREAL);
						D = mxCreateDoubleMatrix(1, CPUnum, mxREAL);
						UC = mxCreateDoubleMatrix(1, CPUArraymax + 1 - CPUnum, mxREAL);
			//			UD = mxCreateDoubleMatrix(1, CPUArraymax + 1 - CPUnum, mxREAL);


						memcpy((void *)mxGetPr(C), (void *)knowcoordation, sizeof(knowcoordation) * CPUnum);
						memcpy((void *)mxGetPr(D), (void *)knowdata, sizeof(knowdata)  * CPUnum);
						memcpy((void *)mxGetPr(UC), (void *)unknowcoordation, sizeof(unknowcoordation) * (CPUArraymax + 1 - CPUnum));

						engPutVariable(ep, "C", C);
						engPutVariable(ep, "D", D);
						engPutVariable(ep, "UC", UC);

						engEvalString(ep, "UD = interp1(C, D, UC, 'pchip');");

						mxArray *mxUD= engGetVariable(ep, "UD");
						double *unknowdata = mxGetPr(mxUD);

	//					if(ep)
	//						engClose(ep);

                                                mxDestroyArray(C);
						mxDestroyArray(D);
						mxDestroyArray(UC);
			//			mxDestroyArray(UD);



						for(int w = 0; w < CPUArraymax + 1- CPUnum; w++)
						{
							int x = searchArrayIndex(CPU, unknowcoordation[w], 7);
							Interpolation[m][x][l][j][i] = unknowdata[w];
						}
				
                                                delete knowcoordation;
                                                delete knowdata;
                                                delete unknowcoordation;
     
//                                                delete unknowdata;
                                	}
				}
			}
		}
	}

	if(MEMArraymax != MEMArraymin && MEMArraymax + 1 - MEMnum > 0)
	{
		for(int i = READArraymin; i <= READArraymax; i++)
		{
			for(int j = WRITEArraymin; j <= WRITEArraymax; j++)
			{
				for(int l = NETArraymin; l <= NETArraymax; l++)
				{
					for(int n = CPUArraymin; n <= CPUArraymax; n++)
					{
						double *knowcoordation = new double[MEMnum];
						double *knowdata = new double[MEMnum];
						double *unknowcoordation = new double[MEMArraymax + 1 - MEMnum];
						//double *unknowdata = new double[MEMArraymax + 1 - MEMnum];

						int p = 0;
						int q = 0;
						for(int m = MEMArraymin; m <= MEMArraymax; m++)
						{
							if(Interpolation[m][n][l][j][i] != -1)
							{
								knowcoordation[p] = MEM[m];
								knowdata[p] = Interpolation[m][n][l][j][i];
								p++;
							}
							else
							{
                                                                if (q==MEMArraymax + 1 - MEMnum)
                                                                break;
								unknowcoordation[q] = MEM[m];
								q++;
							}
						}

                                                if (p==0)
                                                {
                                                   delete knowcoordation;
                                                   delete knowdata;
                                                   delete unknowcoordation;
                                                   continue;
                                                }

						mxArray *C = NULL;////对应knowcoordation
						mxArray *D = NULL;////对应knowdata
						mxArray *UC = NULL;////对应unknowcoordation
	//					mxArray *UD = NULL;////对应unknowdata

	//					if (!(ep = engOpen(""))) 
	//					{
	//						printf("\nCan't start MATLAB engine\n");
	//						return;
	//					}

						C = mxCreateDoubleMatrix(1, MEMnum, mxREAL);
						D = mxCreateDoubleMatrix(1, MEMnum, mxREAL);
						UC = mxCreateDoubleMatrix(1, MEMArraymax + 1 - MEMnum, mxREAL);
	//					UD = mxCreateDoubleMatrix(1, MEMArraymax + 1 - MEMnum, mxREAL);


						memcpy((void *)mxGetPr(C), (void *)knowcoordation, sizeof(knowcoordation) * MEMnum);
						memcpy((void *)mxGetPr(D), (void *)knowdata, sizeof(knowdata) * MEMnum);
						memcpy((void *)mxGetPr(UC), (void *)unknowcoordation, sizeof(unknowcoordation) * (MEMArraymax + 1 - MEMnum));

						engPutVariable(ep, "C", C);
						engPutVariable(ep, "D", D);
						engPutVariable(ep, "UC", UC);

						engEvalString(ep, "UD = interp1(C, D, UC, 'pchip');");

						mxArray *mxUD= engGetVariable(ep, "UD");
						double *unknowdata = mxGetPr(mxUD);

	//					if(ep)
	//						engClose(ep);

                                                  mxDestroyArray(C);
                                                  mxDestroyArray(D);
                                                  mxDestroyArray(UC);
          //                                        mxDestroyArray(UD);
                                                  



						for(int w = 0; w < MEMArraymax + 1 - MEMnum; w++)
						{
							int x = searchArrayIndex(MEM, unknowcoordation[w], 13);
							Interpolation[x][n][l][j][i] = unknowdata[w];
						}
                                                delete knowcoordation;
                                                delete knowdata;
                                                delete unknowcoordation;
  //                                              delete unknowdata;
	 				}
				}
			}
		}
	}
	if(NETArraymax != NETArraymin && NETArraymax + 1 - MEMnum > 0)
	{
		for(int i = READArraymin; i <= READArraymax; i++)
		{
			for(int j = WRITEArraymin; j <= WRITEArraymax; j++)
			{
				for(int n = CPUArraymin; n <= CPUArraymax; n++)
				{
					for(int m = MEMArraymin; m <= MEMArraymax; m++)
					{
						double *knowcoordation = new double[NETnum];
						double *knowdata = new double[NETnum];
						double *unknowcoordation = new double[NETArraymax + 1 - NETnum];

						int p = 0;
						int q = 0;
						for(int l = NETArraymin; l <= NETArraymax; l++)
						{
							if(Interpolation[m][n][l][j][i] != -1)
							{
								knowcoordation[p] = NET[l];
								knowdata[p] = Interpolation[m][n][l][j][i];
								p++;
							}
							else
							{
                                                                if (q==NETArraymax + 1 - NETnum) break;
     								unknowcoordation[q] = NET[l];
								q++;
							}
						}

                                               if (p==0)
                                                {
                                                   delete knowcoordation;
                                                   delete knowdata;
                                                   delete unknowcoordation;
                                                   continue;
                                                }

						mxArray *C = NULL;////knowcoordation
						mxArray *D = NULL;////knowdata
						mxArray *UC = NULL;////unknowcoordation
	//					mxArray *UD = NULL;////unknowdata

	//					if (!(ep = engOpen(""))) 
	//					{
	//						printf("\nCan't start MATLAB engine\n");
	//						return;
	//					}

						C = mxCreateDoubleMatrix(1, NETnum, mxREAL);
						D = mxCreateDoubleMatrix(1, NETnum, mxREAL);
						UC = mxCreateDoubleMatrix(1, NETArraymax + 1 - NETnum, mxREAL);
	//					UD = mxCreateDoubleMatrix(1, NETArraymax + 1 - NETnum, mxREAL);


						memcpy((void *)mxGetPr(C), (void *)knowcoordation, sizeof(knowcoordation) * NETnum);
						memcpy((void *)mxGetPr(D), (void *)knowdata, sizeof(knowdata) * NETnum);
						memcpy((void *)mxGetPr(UC), (void *)unknowcoordation, sizeof(unknowcoordation) * (NETArraymax + 1 - NETnum));

						engPutVariable(ep, "C", C);
						engPutVariable(ep, "D", D);
						engPutVariable(ep, "UC", UC);

						engEvalString(ep, "UD = interp1(C, D, UC, 'pchip');");

						mxArray *mxUD= engGetVariable(ep, "UD");
						double *unknowdata = mxGetPr(mxUD);

	//					if(ep)
	//						engClose(ep);

                                                mxDestroyArray(C);
                                                mxDestroyArray(D);
                                                mxDestroyArray(UC);
          //                                      mxDestroyArray(UD);


						for(int w = 0; w < NETArraymax + 1 - NETnum; w++)
						{
							int x = searchArrayIndex(NET, unknowcoordation[w], 17);
							Interpolation[m][n][x][j][i] = unknowdata[w];
						}

                                                delete knowcoordation;
                                                delete knowdata;
                                                delete unknowcoordation;
//	                                        delete unknowdata;    
          				}
				}
			}
		}
	}


	///
	if(WRITEArraymax != WRITEArraymin && WRITEArraymax + 1 - WRITEnum > 0)
	{
		for(int i = READArraymin; i <= READArraymax; i++)
		{
			for(int n = CPUArraymin; n <= CPUArraymax; n++)
			{
				for(int m = MEMArraymin; m <= MEMArraymax; m++)
				{
					for(int l = NETArraymin; l <= NETArraymax; l++)
					{
						double *knowcoordation = new double[WRITEnum];
						double *knowdata = new double[WRITEnum];
						double *unknowcoordation = new double[WRITEArraymax + 1 - WRITEnum];

						int p = 0;
						int q = 0;
						for(int j = WRITEArraymin; j <= WRITEArraymax; j++)
						{
							if(Interpolation[m][n][l][j][i] != -1)
							{
								knowcoordation[p] = WRITE[j];
								knowdata[p] = Interpolation[m][n][l][j][i];
								p++;
							}
							else
							{
								unknowcoordation[q] = WRITE[j];
								q++;
							}
						}
                                                if (p==0)
                                                {
                                                   delete knowcoordation;
                                                   delete knowdata;
                                                   delete unknowcoordation;
                                                   continue;
                                                }

						mxArray *C = NULL;////knowcoordation
						mxArray *D = NULL;////knowdata
						mxArray *UC = NULL;///unknowcoordation
	//					mxArray *UD = NULL;///unknowdata

	//					if (!(ep = engOpen(""))) 
	//					{
	//						printf("\nCan't start MATLAB engine\n");
	//						return;
	//					}

						C = mxCreateDoubleMatrix(1, WRITEnum, mxREAL);
						D = mxCreateDoubleMatrix(1, WRITEnum, mxREAL);
						UC = mxCreateDoubleMatrix(1, WRITEArraymax + 1 - WRITEnum, mxREAL);
	//					UD = mxCreateDoubleMatrix(1, WRITEArraymax + 1 - WRITEnum, mxREAL);


						memcpy((void *)mxGetPr(C), (void *)knowcoordation, sizeof(knowcoordation) * WRITEnum);
						memcpy((void *)mxGetPr(D), (void *)knowdata, sizeof(knowdata) * WRITEnum);
						memcpy((void *)mxGetPr(UC), (void *)unknowcoordation, sizeof(unknowcoordation) * (WRITEArraymax + 1 - WRITEnum));

						engPutVariable(ep, "C", C);
						engPutVariable(ep, "D", D);
						engPutVariable(ep, "UC", UC);

						engEvalString(ep, "UD = interp1(C, D, UC, 'pchip');");

						mxArray *mxUD= engGetVariable(ep, "UD");
						double *unknowdata = mxGetPr(mxUD);

	//					if(ep)
	//						engClose(ep);
                                                mxDestroyArray(C);
                                                mxDestroyArray(D);
                                                mxDestroyArray(UC);
          //                                      mxDestroyArray(UD);


						for(int w = 0; w < WRITEArraymax + 1 - WRITEnum; w++)
						{
							int x = searchArrayIndex(WRITE, unknowcoordation[w], 21);
							Interpolation[m][n][l][x][i] = unknowdata[w];
						}

                                                delete knowcoordation;
                                                delete knowdata;
                                                delete unknowcoordation;
//	                                        delete unknowdata;
        				}
				}
			}
		}
	}

	///
	if(READArraymax != READArraymin && READArraymax + 1 - READnum > 0)
	{
		for(int n = CPUArraymin; n <= CPUArraymax; n++)
		{
			for(int m = MEMArraymin; m <= MEMArraymax; m++)
			{
				for(int l = NETArraymin; l <= NETArraymax; l++)
				{
					for(int j = WRITEArraymin; j <= WRITEArraymax; j++)
					{
						double *knowcoordation = new double[READnum];
						double *knowdata = new double[READnum];
						double *unknowcoordation = new double[READArraymax + 1 - READnum];

						int p = 0;
						int q = 0;
						for(int i = READArraymin; i <= READArraymax; i++)
						{
							if(Interpolation[m][n][l][j][i] != -1)
							{
								knowcoordation[p] = READ[i];
								knowdata[p] = Interpolation[m][n][l][j][i];
								p++;
							}
							else
							{
								unknowcoordation[q] = READ[i];
								q++;
							}
						}

                                                if (p==0)
                                                {
                                                   delete knowcoordation;
                                                   delete knowdata;
                                                   delete unknowcoordation;
                                                   continue;
                                                }
						mxArray *C = NULL;////knowcoordation
						mxArray *D = NULL;////knowdata
						mxArray *UC = NULL;///unknowcoordation
	//					mxArray *UD = NULL;///unknowdata

	//					if (!(ep = engOpen(""))) 
	//					{
	//						printf("\nCan't start MATLAB engine\n");
	//						return;
	//					}

						C = mxCreateDoubleMatrix(1, READnum, mxREAL);
						D = mxCreateDoubleMatrix(1, READnum, mxREAL);
						UC = mxCreateDoubleMatrix(1, READArraymax + 1 - READnum, mxREAL);
	//					UD = mxCreateDoubleMatrix(1, READArraymax + 1 - READnum, mxREAL);


						memcpy((void *)mxGetPr(C), (void *)knowcoordation, sizeof(knowcoordation) * READnum);
						memcpy((void *)mxGetPr(D), (void *)knowdata, sizeof(knowdata) * READnum);
						memcpy((void *)mxGetPr(UC), (void *)unknowcoordation, sizeof(unknowcoordation) * (READArraymax + 1 - READnum));

						engPutVariable(ep, "C", C);
						engPutVariable(ep, "D", D);
						engPutVariable(ep, "UC", UC);

						engEvalString(ep, "UD = interp1(C, D, UC, 'pchip');");

						mxArray *mxUD= engGetVariable(ep, "UD");
						double *unknowdata = mxGetPr(mxUD);

	//					if(ep)
	//						engClose(ep);

                                                mxDestroyArray(C);
                                                mxDestroyArray(D);
                                                mxDestroyArray(UC);
          //                                      mxDestroyArray(UD);



						for(int w = 0; w < READArraymax + 1 - READnum; w++)
						{
							int x = searchArrayIndex(READ, unknowcoordation[w], 21);
							Interpolation[m][n][l][j][x] = unknowdata[w];
						}

                                                delete knowcoordation;
                                                delete knowdata;
                                                delete unknowcoordation;
  //                                              delete unknowdata;
					}
				}
			}
		}
	}

                                              if(ep)
                                                      engClose(ep);



end=clock();
double dtime=(double)(end - start)/CLOCKS_PER_SEC;
printf("the runtime is %1f \n", dtime);

	//////输出所有
	for(int i=READArraymin; i<=READArraymax; i++)
	{
		for(int j=WRITEArraymin; j<=WRITEArraymax; j++)
		{
			for(int l=NETArraymin; l<=NETArraymax; l++)
			{
				for(int m=MEMArraymin; m<=MEMArraymax; m++)
				{
					for(int n=CPUArraymin; n<=CPUArraymax;n++)
					{
						printf("memory:%1f; CPU:%1f; network:%1f; disk write:%1f; disk read:%1f; result %1f\n", MEM[m], CPU[n], NET[l], WRITE[j], READ[i], Interpolation[m][n][l][j][i]);
			                }
				}
			}
		}
	}
	

}

int main()
{
	printf("input the resource usage: \n");

	printf("input memory usage\n");
	float dmem;
	scanf("%f", &dmem);


	printf("input cpu usage\n");
	float dcpu;
	scanf("%f", &dcpu);


	printf("input net usage\n");
	float dnet;
	scanf("%f", &dnet);

	printf("input disk write usage\n");
	float dwrite;
	scanf("%f", &dwrite);

	printf("input disk read usage\n");
	float dread;
	scanf("%f", &dread);

	//runTestPrograme(8, 0.4, 0, 0, 0);
	runTestPrograme(dmem, dcpu, dnet, dwrite, dread);


	printf("exit with any key......\n");
//	getch();
	
	return 0;
}


