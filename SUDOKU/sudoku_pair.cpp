#include <iostream>
#include <utility> 


using namespace std;


int sudoku_problem[9][9]={
					  3, 0, 6, 5, 0, 8, 4, 0, 0, 
                      5, 2, 0, 0, 0, 0, 0, 0, 0, 
                      0, 8, 7, 0, 0, 0, 0, 3, 1, 
                      0, 0, 3, 0, 1, 0, 0, 8, 0, 
                      9, 0, 0, 8, 6, 3, 0, 0, 5, 
                      0, 5, 0, 0, 9, 0, 6, 0, 0, 
                      1, 3, 0, 0, 0, 0, 2, 5, 0, 
                      0, 0, 0, 0, 0, 0, 0, 7, 4, 
                      0, 0, 5, 2, 0, 6, 3, 0, 0,

                };
                
bool verificar (int sudoku_problem[9][9]){
		for (int coluna = 0; coluna < 9; coluna++) {
			for (int linha = 0; linha < 9; linha ++) {	
					
				for(int linha_a_seguir = linha + 1; linha_a_seguir < 9; linha_a_seguir++) { 
						if (sudoku_problem[linha][coluna] == sudoku_problem[linha_a_seguir][coluna] && sudoku_problem[linha][coluna] != 0){
						return false;
						}
				}		
				for (int coluna_a_seguir = coluna + 1; coluna_a_seguir < 9; coluna_a_seguir++) {
					if (sudoku_problem[linha][coluna] == sudoku_problem[linha][coluna_a_seguir] && sudoku_problem[linha][coluna] != 0){
						return false;
						}
					int bloco_linha = (linha / 3)*3;
					int bloco_coluna = (coluna / 3)*3;
					int contador_no_bloco = -1;
					for(int i=0; i<2; i++) {
						for(int j=0; j<2; j++) {	
							if ( sudoku_problem[linha][coluna] == sudoku_problem[bloco_linha+i][bloco_coluna+j]  && sudoku_problem[linha][coluna] != 0){
								contador_no_bloco ++;
							}						
							if (contador_no_bloco > 0 ){
								//std::cout << "Erro no bloco: " << "bloco: ("<<linha / 3<<","<< coluna/3 <<")" << endl<< endl<< endl;	
								return false;
								}
						}
					}
				}
			} 
		}
	return true;
}

bool e_solucao_final(int sudoku_problem[9][9]){
	if(verificar(sudoku_problem)==false){
		return false;
		}
	
	for (int i = 0; i < 9; ++i){
	  for (int j = 0; j < 9; ++j){
		  if(sudoku_problem[i][j]== 0){
			  return false;
			  }
		  }
	}
	
	return true;
}


pair<int, int> localizacao_0(int sudoku_problem[9][9])
{
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			if (sudoku_problem[row][col] == 0)
			{
				return make_pair(row, col);
			}
	return make_pair(9, 9);
}

bool Resolver(int sudoku_problem[9][9]) 
{ 
  
    if (e_solucao_final(sudoku_problem)) {
		std::cout <<  "sucesso\n";
       return true; 
  }
  
	pair<int, int> row_and_col = localizacao_0(sudoku_problem);
	int row = row_and_col.first;
	int col = row_and_col.second;
     
    for (int num = 1; num <= 9; num++) 
    { 
        if (verificar(sudoku_problem) == true) 
        { 
			
            sudoku_problem[row][col] = num; 
			//std::cout << sudoku_problem[row][col] ;
			
			
            if (Resolver(sudoku_problem)) 
                return true; 
  
            sudoku_problem[row][col] = 0; 
        } 
    } 
    return false; 
} 
void imprimir(int sudoku_problem[][9]){
	std::cout << endl;
	
	for (int i = 0; i < 9; ++i)
		{
		  for (int j = 0; j < 9; ++j){
			std::cout << sudoku_problem[i][j] << " ";
			if(j == 2  ||j == 5 || j == 8){
			std::cout << " ";
				}
		  
	}std::cout << std::endl;
	if(i == 2  ||i == 5 ||i == 8){
			std::cout << endl;
				}
	}
}



int main(){
	

	Resolver(sudoku_problem);

	
	imprimir(sudoku_problem);
	
}
