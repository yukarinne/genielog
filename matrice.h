struct CaseCreuse
{
	float val;
	int il; 	//indice ligne de la case
	int ic; 	//indice colonne de la case
	CaseCreuse *sl;	//suivant en ligne
	CaseCreuse *sc;	//suivant en colonne
	
	
	
};
class MatCreuse
{
	int nl;		//nombre de lignes 
	int nc;		//nombre de colonnes
	CaseCreuse **Lig;	//vecteur d'acces ligne
	CaseCreuse **Col;	//vecteur d'acces colonne
	
	public:
	MatCreuse();	
	MatCreuse(int L,int C);
	MatCreuse(MatCreuse &A);
	~MatCreuse();
	void Affiche(); 
	void Affiche_b(); 
	CaseCreuse* valeur_pere_ligne(int i,int j);
	void Affect(int i,int j,float v);
	CaseCreuse* valeur_pere_col(int i,int j);
	void operator=(MatCreuse &A);
	void egal(const MatCreuse & obj);
	float valeur(int i,int j);
	CaseCreuse* valeur_bis(int i,int j);
	MatCreuse operator+(const MatCreuse&);
};

