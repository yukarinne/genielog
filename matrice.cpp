#include <iostream>
#include <stdlib.h>
#include "matrice.h"
using namespace std;
	
MatCreuse::MatCreuse()
{
	nc=0;
	nl=0;
	Lig=NULL;
	Col=NULL;	
}

MatCreuse::MatCreuse(int L,int C)
{
	nc=C;
	nl=L;
	Lig=new CaseCreuse *[nl];
	for(int i=0;i<nl;i++)Lig[i]=NULL;
	Col=new CaseCreuse *[nc];
	for(int j=0;j<nc;j++)Col[j]=NULL;
}
MatCreuse::~MatCreuse()
{
	CaseCreuse *a;
	CaseCreuse *b;
	if(Col == NULL)
	{
		return;
	}
	for (int i = 0; i < nl; i++)
	{
		a = Lig[i];
		while(a != NULL)
		{
			b = a;
			a = a->sc;
			delete b;
		}
	}
	delete[] Lig;
	delete[] Col;
}
MatCreuse::MatCreuse(MatCreuse &A)
{
	nc=A.nc;
	nl=A.nl;
	float v;

	Lig=new CaseCreuse *[nl];
	for(int i=0;i<nl;i++)Lig[i]=NULL;
	Col=new CaseCreuse *[nc];
	for(int j=0;j<nc;j++)Col[j]=NULL;

	for(int i=0;i<nl;i++)
	{
		for(int j=0;j<nc;j++)
		{
			if((v=A.valeur(i,j))!=0)
			{
				Affect(i,j,v);
			}
		}
	}
}

float MatCreuse::valeur(int i,int j)
{
	CaseCreuse *A;
	if(i>nl||j>nc)
	{	
		cout<<"ces coordonnées dépassent les coordonnées de la matrice"<<endl;		
		exit(EXIT_FAILURE);
	}
	A=Col[j];	
	while(A!=NULL)
	{
		if(A->il==i)
		{
			return (A->val);
		}
		A=A->sl;
	}
	return 0;
		
				
}


CaseCreuse* MatCreuse::valeur_bis(int i,int j)
{
	CaseCreuse *A;
	if(i>nl||j>nc)
	{	
		cout<<"ces cordonnées dépassent les cordonnées de la matrice"<<endl;		
		return NULL;
	}
	A=Col[j];	
	while(A!=NULL)
	{
		if(A->il==i)
		{
		return A;
		}
		A=A->sl;
	}
	return NULL;
					
}
CaseCreuse* MatCreuse::valeur_pere_col(int i,int j)
{
	
	CaseCreuse *A;
	if(i>nl||j>nc)
	{	
		cout<<"ces coordonnées dépassent les coordonnées de la matrice"<<endl;		
		return NULL;
	}
	A=Col[j];
	if(!A) return NULL;
	if(A->il==i) return NULL;	
	while(A)
	{		
		if(A->sl ==NULL) break;	
		if(A->sl->il==i)
		{
			return (A); 	
		}
		A=A->sl;
		
	}
	return(A);
				
}

CaseCreuse* MatCreuse::valeur_pere_ligne(int i,int j)
{	
	CaseCreuse *A;
	if(i>nl||j>nc)
	{	
		cout<<"ces coordonnées dépassent les coordonnées de la matrice"<<endl;		
		return NULL;
	}
	A=Lig[i];
	if(!A) return NULL;
	if(A->ic==j) return NULL;
		
	while(A )
	{
		
		if(A->sc ==NULL) break;			
		if(A->sc->ic==j)
		{
			return (A); 	
		}		
		A=A->sc;
		
	}
	cout<<endl;
	
	return(A);
				
}
void MatCreuse::Affect(int i,int j,float v)
{
	if(v!=0)
	{	
		
		CaseCreuse *B;

		if(B=valeur_bis(i,j))
		{
			B->val=v;
			return;
		}
		CaseCreuse *N=new CaseCreuse();	
		N->sl=NULL; N->sc=NULL;
		N->val=v;
		N->il=i; N->ic=j;
		CaseCreuse *Al=valeur_pere_ligne(i,j);
		
		if(Al==NULL)
		{
			
			if(Lig[i]==NULL) Lig[i]=N;
			else
			{
				
				N->sc=Lig[i];
				Lig[i]=N;
			}
		}
		else
		{
			N->sc=Al->sc;
			Al->sc=N;
		}
		CaseCreuse *Ac=valeur_pere_col(i,j);
		if(Ac==NULL)
		{
			
			if(Col[j]==NULL) Col[j]=N;
			else
			{
				N->sl=Col[j];
				Col[j]=N;
			}
		}
		else
		{
			
			
			N->sl=Ac->sl;
			Ac->sl=N;
		}
		
	}
	if(v==0)
	{
		  CaseCreuse *N=new CaseCreuse();	
				
		if(N=valeur_bis(i,j))
		{
			CaseCreuse *Al=valeur_pere_ligne(i,j);
			if(!Al)
			{	
				if(Lig[i]!=NULL)
				{
					Lig[i]=N->sc;
					
				}
			}		
			if(Al)
			{	
				Al->sc=N->sc;
				
			}
			CaseCreuse *Ac=valeur_pere_col(i,j);
			if(!Al)
			{	
				if(Col[j]!=NULL)
				{
					Col[j]=N->sl;
					
				}
			}		
			if(Al)
			{	
				Ac->sl=N->sl;
				
			}
			delete[] N;
						
		}	
		
}

}

MatCreuse MatCreuse::operator+(const MatCreuse &B)
{
	MatCreuse C(nl,nc);			//Matrice résultat
	if(nl != B.nl || nc != B.nc)
	{	
		cout<<"Les matrices n'ont pas les même dimensions"<<endl;
		return C;
	}
	CaseCreuse *tmp,*tmpB;			//Creation de deux pointeurs temporaire pour parcourir les deux matrices
	for(int i=0;i<nl;i++)
	{
		tmp=Lig[i];
		tmpB=B.Lig[i];
		while(tmp != NULL || tmpB != NULL)
		{
			if(tmp != NULL && tmpB != NULL)
			{
				if(tmp->ic == tmpB->ic)C.Affect(tmp->il,tmp->ic,tmp->val+tmpB->val);
				else if(tmp->ic < tmpB->ic)C.Affect(tmp->il,tmp->ic,tmp->val);
				else C.Affect(tmpB->il,tmpB->ic,tmpB->val);
			}
			else if(tmp != NULL)C.Affect(tmp->il,tmp->ic,tmp->val);
			else C.Affect(tmpB->il,tmpB->ic,tmpB->val);
			tmp=tmp->sc;
			tmpB=tmpB->sc;
		}
	}

}


void MatCreuse::Affiche_b() 
{

for(int i=0;i<nl;i++)
{
	for(int j=0;j<nc;j++) cout<<valeur(i,j)<<" ";
	cout<<endl;

}
}
void MatCreuse::operator=(MatCreuse &A)
{
    CaseCreuse *tmp;
    nl=A.nl;
    nc=A.nc;
    Lig=new CaseCreuse* [nl];
    Col=new CaseCreuse* [nc];
    for(int i=0; i<nl; i++)
    {
        tmp=A.Lig[i];
        while(tmp!=NULL)
            {
                Affect(tmp->il, tmp->ic, tmp->val);
                tmp=tmp->sc;
        }
    }
}

