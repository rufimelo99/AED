#include <iostream>

using namespace std;


int sudoku_problem[4][4]={
                 1,2,3,4,
                 3,4,1,2,
                 4,1,2,3,
                 2,0,4,1,


                };
int sudoku_solution[4][4];
                
bool verificar (int sudoku_problem[4][4]){
		for (int coluna = 0; coluna < 4; coluna++) {
			for (int linha = 0; linha < 4; linha ++) {	
				if(sudoku_problem[linha][coluna] == 0){
					return false;
					}
					
				for(int linha_a_seguir = linha + 1; linha_a_seguir < 4; linha_a_seguir++) { 
						if (sudoku_problem[linha][coluna] == sudoku_problem[linha_a_seguir][coluna]){
						return false;
						}
				}		
				for (int coluna_a_seguir = coluna + 1; coluna_a_seguir < 4; coluna_a_seguir++) {
					if (sudoku_problem[linha][coluna] == sudoku_problem[linha][coluna_a_seguir]){
						return false;
						}
					int bloco_linha = (linha / 2)*2;
					int bloco_coluna = (coluna / 2)*2;
					int contador_no_bloco = -1;
					for(int i=0; i<2; i++) {
						for(int j=0; j<2; j++) {	
							if ( sudoku_problem[linha][coluna] == sudoku_problem[bloco_linha+i][bloco_coluna+j] ){
								contador_no_bloco ++;
							}						
							if (contador_no_bloco > 0 ){
								std::cout << "Erro no bloco: " << "bloco: ("<<linha / 2<<","<< coluna/2 <<")" << endl<< endl<< endl;	
								return false;
								}
						}
					}
				}
			} 
		}
	return true;
}

bool e_solucao_final(int sudoku_problem[4][4]){
	if(verificar(sudoku_problem)==false){
		return false;
		}
	
	for (int i = 0; i < 4; ++i){
	  for (int j = 0; j < 4; ++j){
		  if(sudoku_problem[i][j]== 0){
			  return false;
			  }
		  }
	}
	
	return true;
}


bool resolver(){
	if(e_solucao_final(sudoku_problem)==true){
		std::cout <<  "é versao final \n";
		return true;
	}
	

	
	
	/*if( verificar(sudoku_solution) == true){
		for (int i = 0; i < 4; ++i){
			for (int j = 0; j < 4; ++j){
				if(sudoku_solution[i][j]==0){ x
					
						for (int e = 1; e < 5; i++){
							sudoku_solution[i][j] = e;
							if(verificar(sudoku_solution)==true){
								resolver();
								}
							else{
								sudoku_solution[i][j] = 0;
								
								}
							}
						
						}
					}
				}
			}	*/
	// consider digits 1 to 9 
    
		
	return false;
}


bool SolveSudoku(int sudoku_problem[4][4]) 
{ 
    
    int row, col; 
  
    if (e_solucao_final(sudoku_problem) == true) {
		std::cout <<  "parabens\n";
       return true; // success! 
  }
		
     
    for (int num = 1; num <= 4; num++) 
    { 
        if (verificar(sudoku_problem) == false) 
        { 
		
            sudoku_problem[row][col] = num; 
			std::cout << sudoku_problem[row][col] ;
			
			
            if (SolveSudoku(sudoku_problem)) 
                return true; 
  
            sudoku_problem[row][col] = 0; 
        } 
    } 
    return false; 
} 


int main(){	
	SolveSudoku(sudoku_solution);
	
	
	//há erros ou nao?
	if(e_solucao_final(sudoku_problem)==true){
			std::cout <<  "é versao final \n";
		}
	else{
			std::cout <<  "nao é versao final \n";
		}
	resolver();
	
	//imprimir solucao
	for (int i = 0; i < 4; ++i)
		{
		  for (int j = 0; j < 4; ++j)
			std::cout << sudoku_solution[i][j] << " ";
		  std::cout << std::endl;
	}
	return 0;
}
