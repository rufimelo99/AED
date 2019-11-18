#include <iostream>

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
  
 /*
bool Numero_valido(int tentativa, int sudoku_problem[][9], int coluna, int linha){
    int Elemento_do_BlocoLinha = 3*(linha/3);
    int Elemento_do_BlocoColuna = 3*(coluna/3);
    int Bloco_linha1 = (linha%3)+1;
    int Bloco_linha2 = (linha%3)+2;
    int Bloco_coluna1 = (coluna%3)+1;
    int Bloco_coluna2 = (coluna%3)+2;
 
    for (int i=0; i<9; i++) {
        if (sudoku_problem[i][coluna] == tentativa) return false;
        if (sudoku_problem[linha][i] == tentativa) return false;
    }
 
    if(sudoku_problem[Bloco_linha1 + Elemento_do_BlocoLinha][Bloco_coluna1+Elemento_do_BlocoColuna] == tentativa  && sudoku_problem[Bloco_linha1 + Elemento_do_BlocoLinha][Bloco_coluna1+Elemento_do_BlocoColuna] != 0){return false;}
    if(sudoku_problem[Bloco_linha2 + Elemento_do_BlocoLinha][Bloco_coluna1+Elemento_do_BlocoColuna] == tentativa  && sudoku_problem[Bloco_linha2 + Elemento_do_BlocoLinha][Bloco_coluna1+Elemento_do_BlocoColuna] != 0){return false;}
    if(sudoku_problem[Bloco_linha1 + Elemento_do_BlocoLinha][Bloco_coluna2+Elemento_do_BlocoColuna] == tentativa  && sudoku_problem[Bloco_linha1 + Elemento_do_BlocoLinha][Bloco_coluna2+Elemento_do_BlocoColuna] != 0){return false;}
    if(sudoku_problem[Bloco_linha2 + Elemento_do_BlocoLinha][Bloco_coluna2+Elemento_do_BlocoColuna] == tentativa  && sudoku_problem[Bloco_linha2 + Elemento_do_BlocoLinha][Bloco_coluna2+Elemento_do_BlocoColuna] != 0){return false	;}
    return true;
}
*/
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


int localizacao_0(int sudoku_problem[9][9])
{
	int row, col;
	for (row = 0; row < 9; row++)
		for (col = 0; col < 9; col++)
			if (sudoku_problem[row][col] == 0)
			{
				return row, col;
			}
	return row = 9, col = 9;
}

bool Resolver(int sudoku_problem[][9]) {
	
	if (e_solucao_final(sudoku_problem)) {
		std::cout <<  "Parabens\n";
       return true; 
  }
	
	int col, row = localizacao_0(sudoku_problem);
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
	
	
	/* for (int val=1; val<10; val++) {
		std::cout << val << endl;
		if (Numero_valido(val, sudoku_problem, linha, coluna) == true) {
			std::cout << "este valor corresponde" <<val << endl;
			sudoku_problem[linha][coluna] = val;
			if (linha == 8 && coluna == 8) {
				std::cout << "acabou";
				return true;
			}
			int proxima_linha = linha+1;
			//int proxima_coluna = coluna+1;
			int proxima_coluna = coluna;
			if (proxima_linha >= 9) {	
				proxima_linha = 0;
				proxima_coluna++;
			}
			
			if (Resolver(sudoku_problem, proxima_linha, proxima_coluna)) {
			  return true;
			}
			std::cout << sudoku_problem[linha][coluna];
			sudoku_problem[linha][coluna] = 0;
			
		}
  }*/
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
/*
	int col, row = localizacao_0(sudoku_problem);
	std::cout << row <<endl;
	std::cout << col <<endl;
	
	*/
	
	Resolver(sudoku_problem);
	
	imprimir(sudoku_problem);
	return 0;
}
