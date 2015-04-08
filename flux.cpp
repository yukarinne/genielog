#include "matrice.h"
#include "flux.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

//faut modifier affect car la fonction ne créé pas des cases inexistantes.
// ou alors il faut récup la taille de la matrice dans le txt et le donner au constructeur


// qu'une matcreuse appel la lecture pour créer une autre matcreuse n'a pas de sens
MatCreuse MatCreuse::lecture()
{	
	int lig, col, val, nbe_col, nbe_lig;
	ifstream fichier("matrice.txt", ios::in);
	fichier >> nbe_lig >> nbe_col;
	MatCreuse matrice(nbe_lig, nbe_col);

	while(fichier)
	{
		fichier >> lig >> col >> val;
		matrice.Affect(lig, col, val); // j'envoie à la fonction affect la ligne, colonne et valeur à entrer dans la matrice
	}

	return MatCreuse;
}

void MatCreuse::ecriture()
{
	
}


