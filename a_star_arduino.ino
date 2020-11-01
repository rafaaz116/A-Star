int x_inicio = 2;
int y_inicio = 0;
int x_fim = 2;
int y_fim = 4; 

typedef struct cel{
  int g;
  int h;
  int f;
  int celula; //0 representa o inicio, 1 o caminho e 2 o fim
  int indice;
  int analisado;
  int objeto;
  int prox;
}CELULA;

CELULA matriz[5][5];

CELULA lista_aberta[25];
int it_aberta=0;
CELULA lista_fechada[25];
int it_fechada=0;
int primeiro=0;
int ultimo=-1;
int x_atual;
int y_atual;
int primeira_passada=1;


//calculando os custos_ função dentro de função vai acima
void h(int linha, int coluna){
  int h_x, h_y;
  
  h_x=(x_fim - linha);
  if(h_x<0){
    h_x=h_x*(-1);
  }
  h_y=(y_fim - coluna);
  if(h_y<0){
    h_y=h_y*(-1);
  }
  matriz[linha][coluna].h = h_x + h_y;
}

void g(int linha, int coluna){
  int g_x, g_y;

  g_x = (linha - x_inicio);
  if(g_x<0){
    g_x=g_x*(-1);
  }
  g_y = (coluna - y_inicio);
  if(g_y<0){
    g_y=g_y*(-1);
  }
  matriz[linha][coluna].g = g_x + g_y;
}

void f(int linha, int coluna){
matriz[linha][coluna].f = matriz[linha][coluna].h + matriz[linha][coluna].g;
}

//defini a cecula inicial=matriz[2][0] e final=matriz[2][4]
void iniciar_matriz(){
  int i, j, cont;
  cont=1;
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      if(i==x_inicio && j==y_inicio){
        matriz[i][j].g=0;
        matriz[i][j].h=0;
        matriz[i][j].f=0;
        matriz[i][j].celula=0;
        matriz[i][j].indice=cont++;
        matriz[i][j].analisado=0;
        matriz[i][j].objeto=0;
      }
      else{
        if(i==x_fim && j==y_fim){
          matriz[i][j].g=0;
          matriz[i][j].h=0;
          matriz[i][j].f=0;
          matriz[i][j].celula=2;
          matriz[i][j].indice=cont++;
          matriz[i][j].analisado=0;
          matriz[i][j].objeto=0;
        }
        else{
          if(i==1 && j==2){
            matriz[i][j].g=0;
            matriz[i][j].h=0;
            matriz[i][j].f=0;
            matriz[i][j].celula=2;
            matriz[i][j].indice=cont++;
            matriz[i][j].analisado=0;
            matriz[i][j].objeto=1;            
          }
          else{
            if(i==2 && j==2){
              matriz[i][j].g=0;
              matriz[i][j].h=0;
              matriz[i][j].f=0;
              matriz[i][j].celula=2;
              matriz[i][j].indice=cont++;
              matriz[i][j].analisado=0;
              matriz[i][j].objeto=1; 
            }
            else{
              if(i==3 && j==2){
                matriz[i][j].g=0;
                matriz[i][j].h=0;
                matriz[i][j].f=0;
                matriz[i][j].celula=2;
                matriz[i][j].indice=cont++;
                matriz[i][j].analisado=0;
                matriz[i][j].objeto=1;
              }
              else{
                matriz[i][j].g=0;
                matriz[i][j].h=0;
                matriz[i][j].f=0;
                matriz[i][j].celula=1;
                matriz[i][j].indice=cont++;
                matriz[i][j].analisado=0;
                matriz[i][j].objeto=0;
              }
            }
          }
        }       
      }
    }
  }
}

void iniciar_lista_aberta(){
  int i;
  for(i=0;i<25;i++){
    lista_aberta[i].g=0;
    lista_aberta[i].h=0;
    lista_aberta[i].f=0;
    lista_aberta[i].celula=0;
    lista_aberta[i].indice=0;
    lista_aberta[i].analisado=0;
    lista_aberta[i].objeto=0;
  }
}

void iniciar_lista_fechada(){
  int i;
  for(i=0;i<25;i++){
    lista_fechada[i].g=0;
    lista_fechada[i].h=0;
    lista_fechada[i].f=0;
    lista_fechada[i].celula=0;
    lista_fechada[i].indice=0;
    lista_fechada[i].analisado=0;
    lista_fechada[i].objeto=0;
  }
}  

void detectar_vizinhos(int x_atual, int y_atual){
  int i, j, n;
  //nao pode considerar objeto e quem esta na lista aberta e fechada
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      if(i==(x_atual-1) && j==y_atual && matriz[i][j].analisado==0 && matriz[i][j].objeto==0){
        //verifica_custo();
        //antes de verificar o custo e adicionar na lista aberta, deve-se verificar se a celula analisada não está na lista aberta e nem na fechada.
        //H
        h(i, j); //linha corrente e coluna corrente

        //G
        g(i, j);

        //F
        f(i, j);
       
        lista_aberta[it_aberta]=matriz[i][j];
        it_aberta++;
        ultimo++;
        matriz[i][j].analisado=1;  
      }
      if(i==x_atual && j==(y_atual+1) && matriz[i][j].analisado==0 && matriz[i][j].objeto==0){
        //calcular f, g, h
        h(i, j);
        g(i, j);
        f(i, j);
        lista_aberta[it_aberta]=matriz[i][j];
        it_aberta++;
        ultimo++;
        matriz[i][j].analisado=1;
      }
      if(i==(x_atual+1) && j==y_atual && matriz[i][j].analisado==0 && matriz[i][j].objeto==0){
        h(i, j);
        g(i, j);
        f(i, j);
        lista_aberta[it_aberta]=matriz[i][j];
        it_aberta++; 
        ultimo++; 
        matriz[i][j].analisado=1;      
      }
      if(i==x_atual && j==(y_atual-1) && matriz[i][j].analisado==0 && matriz[i][j].objeto==0){
        h(i, j);
        g(i, j);
        f(i, j);
        lista_aberta[it_aberta]=matriz[i][j];
        it_aberta++;
        ultimo++;
        matriz[i][j].analisado=1;        
      }
    }
  }
  //reordenar a lista aberta
}

void insertion_sort(int primeiro, int ultimo){
  int i, j;
  CELULA key;
  for (i = (primeiro+1); i <= ultimo; i++) {
    key.g = lista_aberta[i].g;
    key.h = lista_aberta[i].h;
    key.f = lista_aberta[i].f;
    key.celula = lista_aberta[i].celula;
    key.indice = lista_aberta[i].indice;
    key.analisado = lista_aberta[i].analisado;
    key.objeto = lista_aberta[i].objeto;
    j = i - 1;
    while (j >= primeiro && lista_aberta[j].f > key.f) {
        lista_aberta[j + 1].g = lista_aberta[j].g;
        lista_aberta[j + 1].h = lista_aberta[j].h;
        lista_aberta[j + 1].f = lista_aberta[j].f;
        lista_aberta[j + 1].celula = lista_aberta[j].celula;
        lista_aberta[j + 1].indice = lista_aberta[j].indice;
        lista_aberta[j + 1].analisado = lista_aberta[j].analisado;
        lista_aberta[j + 1].objeto = lista_aberta[j].objeto;
        j = j - 1;
    }
    lista_aberta[j + 1].g = key.g;
    lista_aberta[j + 1].h = key.h;
    lista_aberta[j + 1].f = key.f;
    lista_aberta[j + 1].celula = key.celula;
    lista_aberta[j + 1].indice = key.indice;
    lista_aberta[j + 1].analisado = key.analisado;
    lista_aberta[j + 1].objeto = key.objeto;
  }
}

void busca_celula_analisar(){
  int i, j, contador;
  contador=0;
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      contador++;
      if(lista_aberta[primeiro].indice == contador){
        x_atual=i;
        y_atual=j;
      }     
    }
  }
}

void imprime_lista_aberta(int primerio){
  int i;
  for(i=primeiro;i<25;i++){
    Serial.print(lista_aberta[i].indice);
    Serial.print(" ");
  }
  Serial.println(" ");
}

void imprime_lista_fechada(){
  int i;
  for(i=0;i<25;i++){
    Serial.print(lista_fechada[i].indice);
    Serial.print(" ");
  }
  Serial.println(" ");
}

void imprimir_matriz_indice(){
  int i, j;
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      Serial.print(matriz[i][j].indice);
      Serial.print(' ');
    }
    Serial.println(" ");
  }
}

void imprimir_matriz_f(){
  int i, j;
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      Serial.print(matriz[i][j].f);
      Serial.print(' ');
    }
    Serial.println(" ");
  }
}

void imprimir_matriz_celula(){
  int i, j;
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      Serial.print(matriz[i][j].celula);
      Serial.print(' ');
    }
    Serial.println(" ");
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // put your main code here, to run repeatedly:
  //preenche a matriz
  
  if (primeira_passada==1){
    iniciar_matriz(); //sair do loop
    Serial.println("MATRIZ INDICE(NOME DA CELULA)");
    imprimir_matriz_indice();
    Serial.println("MATRIZ CELULA(POSIÇÃO INICIAL, CAMINHO, FINAL)");
    imprimir_matriz_celula();
    Serial.println("MATRIZ CUSTO F");    
    imprimir_matriz_f();

    iniciar_lista_aberta();
    Serial.println("IMPRIME LISTA ABERTA INICIALIZADA");
    imprime_lista_aberta(primeiro);
    Serial.println("IMPRIME LISTA FECHADA");
    iniciar_lista_fechada();
    imprime_lista_fechada();

    //adiciona a celula início na lista aberta

    x_atual=x_inicio;
    y_atual=y_inicio;
    //lista_aberta[it_aberta] = matriz[x_atual][y_atual];
    lista_aberta[it_aberta].g = matriz[x_atual][y_atual].g;
    lista_aberta[it_aberta].h = matriz[x_atual][y_atual].h;
    lista_aberta[it_aberta].f = matriz[x_atual][y_atual].f;
    lista_aberta[it_aberta].celula = matriz[x_atual][y_atual].celula;
    lista_aberta[it_aberta].indice = matriz[x_atual][y_atual].indice;
    lista_aberta[it_aberta].analisado = matriz[x_atual][y_atual].analisado;
    lista_aberta[it_aberta].objeto = matriz[x_atual][y_atual].objeto;
    Serial.println("IMPRIME LISTA ABERTA, COM VALOR A SER ANALISADO");
    imprime_lista_aberta(primeiro);
    

    
    it_aberta++;
    ultimo++;
    matriz[x_atual][y_atual].analisado=1;
  }

  primeira_passada = 0;
  
  //verificar quem são os vizinhos e também adicionar na lista aberta
  detectar_vizinhos(x_atual, y_atual);
  Serial.println("IMPRIME MATRIZ COM VIZINHOS DETECTADOS");
  imprimir_matriz_f();
  //Serial.println(lista_aberta[0].celula);
  //Serial.println(lista_aberta[1].celula);
  //Serial.println(lista_aberta[2].celula);
  //Serial.println(lista_aberta[3].celula);
  
  //add pai
  //tirar o K(posição inicial[analisada da lista aberta e colocar na fechada) 

  lista_fechada[it_fechada]=lista_aberta[primeiro];
  Serial.println("IMPRIME LISTA FECHADA");
  imprime_lista_fechada();
  it_fechada++;
  lista_aberta[primeiro].g=0;
  lista_aberta[primeiro].h=0;
  lista_aberta[primeiro].f=0;
  lista_aberta[primeiro].celula=1;
  lista_aberta[primeiro].analisado=0;
  lista_aberta[primeiro].objeto=0;
   
  primeiro++; //novo primeiro
  
  Serial.println("IMPRIME LISTA ABERTA ANTES DO INSERTION SORT");
  imprime_lista_aberta(primeiro);  
  insertion_sort(primeiro, ultimo);
  Serial.println("IMPRIME LISTA ABERTA DEPOIS DO INSERTION SORT");
  imprime_lista_aberta(primeiro);
  //ordenar_lista_aberta(); de acordo com menor valor de f -> crescente
  //pega a celula do topo, no caso a l ; atualiza a celula a ser analisada, novo primeiro, detecta os vizinhos
  busca_celula_analisar();
  Serial.print("X ATUAL: ");
  Serial.println(x_atual);
  Serial.print("Y ATUAL: ");
  Serial.println(y_atual);
  //x_atual
  //y_atual
  
  delay(50000);
}
