byte x_inicio = 2;
byte y_inicio = 0;
byte x_fim = 2;
byte y_fim = 4; 

typedef struct cel{
  byte g;
  byte h;
  byte f;
  byte celula; //0 representa o inicio, 1 o caminho e 2 o fim
  byte indice;
  byte analisado;
  byte objeto;
  byte pai;
}CELULA;

CELULA matriz[5][5];

CELULA lista_aberta[25];
byte it_aberta=0;
CELULA lista_fechada[25];
byte it_fechada=0;
byte primeiro=0;
short ultimo=-1;
byte x_atual;
byte y_atual;
byte primeira_passada=1;
char movimento_robo[15]; //'b'=baixo, 'c'=cima, 'd'=direita, 'e'=esquerda
byte contador_movimento=0;
byte flag=0;

//calculando os custos_ função dentro de função vai acima
void h(byte linha, byte coluna){
  short h_x, h_y;
  
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

void g(byte linha, byte coluna){
  byte g_x, g_y;
  
  matriz[linha][coluna].g = (matriz[x_atual][y_atual].g + 1); 
}

void f(byte linha, byte coluna){
  matriz[linha][coluna].f = matriz[linha][coluna].h + matriz[linha][coluna].g;
}

void melhor_caminho(byte x, byte y){
  byte i, j;

  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      if(matriz[x][y].pai==matriz[i][j].indice){ //se o nome da celula for igual ao pai da celula atual
        if((x-1)==i && y==j){
          //back
          movimento_robo[contador_movimento++]='b'; //***celula de cima, porém o robô irá fazer o caminho contrário(do início ao fim) por isso celula de baixo
          x=i;
          y=j;
          Serial.println("Cima");
          if(x==x_inicio && y==y_inicio){
            Serial.println("Mover");
            
            mover();
            Serial.println("Fim 1");
            delay(25000);
          }
          melhor_caminho(x, y);
        }
        else{
          if((x+1)==i && y==j){
            //back
            movimento_robo[contador_movimento++]='c';
            x=i;
            y=j;
            Serial.println("Baixo");
            if(x==x_inicio && y==y_inicio){
              Serial.println("Mover");
              
              mover();
              Serial.println("Fim 2");
              delay(25000);
            }
            melhor_caminho(x, y);
          }
          else{
            if(x==i && (y-1)==j){
              //back
              movimento_robo[contador_movimento++]='d'; //celula da esquerda, porém armazena direita
              x=i;
              y=j;
              Serial.println("Esquerda");
              if(x==x_inicio && y==y_inicio){
                Serial.println("Mover");             
                mover();
                Serial.println("Fim 3");
                delay(25000);

              }
              melhor_caminho(x, y);
            }
            else{
              //back
              movimento_robo[contador_movimento++]='e';
              x=i;
              y=j;
              Serial.println("Direita");
              if(x==x_inicio && y==y_inicio){
                Serial.println("Mover");
                mover();
                Serial.println("Fim 4");
                delay(25000);
              }
              melhor_caminho(x, y);    
            }
          }
        }       
      }
    }
  }
}


void mover(){
  short m;
   for(m=(contador_movimento-1);m>=0;m--){
    if(movimento_robo[m] == 'b'){
      Serial.println("robô se move pra baixo");
    }
    else{
      if(movimento_robo[m] == 'c'){
        Serial.println("robô se move pra cima");
      }
      else{
        if(movimento_robo[m] == 'd'){
          Serial.println("robô se move pra direita");
        }
        else{
          Serial.println("robô se move pra esquerda");
        }          
      }
    }
  }  
}

//defini a cecula inicial=matriz[2][0] e final=matriz[2][4]
void iniciar_matriz(){
  byte i, j, cont;
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
        matriz[i][j].pai=0;
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
          matriz[i][j].pai=0;
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
            matriz[i][j].pai=0;            
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
              matriz[i][j].pai=0; 
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
                matriz[i][j].pai=0;
              }
              else{
                matriz[i][j].g=0;
                matriz[i][j].h=0;
                matriz[i][j].f=0;
                matriz[i][j].celula=1;
                matriz[i][j].indice=cont++;
                matriz[i][j].analisado=0;
                matriz[i][j].objeto=0;
                matriz[i][j].pai=0;
              }
            }
          }
        }       
      }
    }
  }
}

void iniciar_lista_aberta(){
  byte i;
  for(i=0;i<25;i++){
    lista_aberta[i].g=0;
    lista_aberta[i].h=0;
    lista_aberta[i].f=0;
    lista_aberta[i].celula=0;
    lista_aberta[i].indice=0;
    lista_aberta[i].analisado=0;
    lista_aberta[i].objeto=0;
    lista_aberta[i].pai=0;
  }
}

void iniciar_lista_fechada(){
  byte i;
  for(i=0;i<25;i++){
    lista_fechada[i].g=0;
    lista_fechada[i].h=0;
    lista_fechada[i].f=0;
    lista_fechada[i].celula=0;
    lista_fechada[i].indice=0;
    lista_fechada[i].analisado=0;
    lista_fechada[i].objeto=0;
    lista_fechada[i].pai=0;
  }
}  

void detectar_vizinhos(byte x_atual, byte y_atual){
  byte i, j, n;
  //nao pode considerar objeto e quem esta na lista aberta e fechada
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      if(i==(x_atual-1) && j==y_atual && matriz[i][j].analisado==0 && matriz[i][j].objeto==0){ //se for um vizinho
        if(i==x_fim && j==y_fim){ //se esse vizinho for a celula objetivo
          matriz[i][j].pai = matriz[x_atual][y_atual].indice;
          melhor_caminho(i, j);
        }else{
          //verifica_custo();
          //antes de verificar o custo e adicionar na lista aberta, deve-se verificar se a celula analisada não está na lista aberta e nem na fechada.
          //H
          h(i, j); //linha corrente e coluna corrente
          //G
          g(i, j); 
          //F
          f(i, j);
          matriz[i][j].pai = matriz[x_atual][y_atual].indice;
          lista_aberta[it_aberta]=matriz[i][j];
          it_aberta++;
          ultimo++;
          matriz[i][j].analisado=1;        
        }
      }
      if(i==x_atual && j==(y_atual+1) && matriz[i][j].analisado==0 && matriz[i][j].objeto==0){
        if(i==x_fim && j==y_fim){ //se esse vizinho for a celula objetivo
          matriz[i][j].pai = matriz[x_atual][y_atual].indice;
          melhor_caminho(i, j);

        }
        else{
          //calcular f, g, h
          h(i, j);
          g(i, j);
          f(i, j);
          matriz[i][j].pai = matriz[x_atual][y_atual].indice;
          lista_aberta[it_aberta]=matriz[i][j];
          it_aberta++;
          ultimo++;
          matriz[i][j].analisado=1;
        }
      }
      if(i==(x_atual+1) && j==y_atual && matriz[i][j].analisado==0 && matriz[i][j].objeto==0){
        if(i==x_fim && j==y_fim){ //se esse vizinho for a celula objetivo
          matriz[i][j].pai = matriz[x_atual][y_atual].indice;
          melhor_caminho(i, j);
          //mover();

        }
        else{
          h(i, j);
          g(i, j);
          f(i, j);
          matriz[i][j].pai = matriz[x_atual][y_atual].indice;
          lista_aberta[it_aberta]=matriz[i][j];
          it_aberta++; 
          ultimo++; 
          matriz[i][j].analisado=1;   
        }  
      }
      if(i==x_atual && j==(y_atual-1) && matriz[i][j].analisado==0 && matriz[i][j].objeto==0){
        if(i==x_fim && j==y_fim){ //se esse vizinho for a celula objetivo
          matriz[i][j].pai = matriz[x_atual][y_atual].indice;
          melhor_caminho(i, j);

        }
        else{
          h(i, j);
          g(i, j);
          f(i, j);
          matriz[i][j].pai = matriz[x_atual][y_atual].indice;
          lista_aberta[it_aberta]=matriz[i][j];
          it_aberta++;
          ultimo++;
          matriz[i][j].analisado=1;   
        }
      
      }
    }
  }
  //reordenar a lista aberta
}

void insertion_sort(byte primeiro, short ultimo){
  byte i, j;
  CELULA key;
  for (i = (primeiro+1); i <= ultimo; i++) {
    key.g = lista_aberta[i].g;
    key.h = lista_aberta[i].h;
    key.f = lista_aberta[i].f;
    key.celula = lista_aberta[i].celula;
    key.indice = lista_aberta[i].indice;
    key.analisado = lista_aberta[i].analisado;
    key.objeto = lista_aberta[i].objeto;
    key.pai = lista_aberta[i].pai;
    j = i - 1;
    while (j >= primeiro && lista_aberta[j].f > key.f) {
        lista_aberta[j + 1].g = lista_aberta[j].g;
        lista_aberta[j + 1].h = lista_aberta[j].h;
        lista_aberta[j + 1].f = lista_aberta[j].f;
        lista_aberta[j + 1].celula = lista_aberta[j].celula;
        lista_aberta[j + 1].indice = lista_aberta[j].indice;
        lista_aberta[j + 1].analisado = lista_aberta[j].analisado;
        lista_aberta[j + 1].objeto = lista_aberta[j].objeto;
        lista_aberta[j + 1].pai = lista_aberta[j].pai;
        j = j - 1;
    }
    lista_aberta[j + 1].g = key.g;
    lista_aberta[j + 1].h = key.h;
    lista_aberta[j + 1].f = key.f;
    lista_aberta[j + 1].celula = key.celula;
    lista_aberta[j + 1].indice = key.indice;
    lista_aberta[j + 1].analisado = key.analisado;
    lista_aberta[j + 1].objeto = key.objeto;
    lista_aberta[j + 1].pai = key.pai;
  }
}

void busca_celula_analisar(){
  byte i, j, contador;
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

void imprime_lista_aberta(byte primerio){
  byte i;
  for(i=primeiro;i<25;i++){
    Serial.print(lista_aberta[i].indice);
    Serial.print(" ");
  }
  Serial.println(" ");
}

void imprime_lista_fechada(){
  byte i;
  for(i=0;i<25;i++){
    Serial.print(lista_fechada[i].indice);
    Serial.print(" ");
  }
  Serial.println(" ");
}

void imprimir_matriz_indice(){
  byte i, j;
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      Serial.print(matriz[i][j].indice);
      Serial.print(' ');
    }
    Serial.println(" ");
  }
}

void imprimir_matriz_f(){
  byte i, j;
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      Serial.print(matriz[i][j].f);
      Serial.print(' ');
    }
    Serial.println(" ");
  }
}

void imprimir_matriz_celula(){
  byte i, j;
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      Serial.print(matriz[i][j].celula);
      Serial.print(' ');
    }
    Serial.println(" ");
  }
}

void imprimir_matriz_objeto(){
  byte i, j;
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      Serial.print(matriz[i][j].objeto);
      Serial.print(' ');
    }
    Serial.println(" ");
  }  
}

void imprimir_matriz_analisado(){
  byte i, j;
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      Serial.print(matriz[i][j].analisado);
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
    //Serial.println("MATRIZ INDICE(NOME DA CELULA)");
    imprimir_matriz_indice();
    //Serial.println("MATRIZ CELULA(POSIÇÃO INICIAL, CAMINHO, FINAL)");
    //imprimir_matriz_celula();
    //Serial.println("MATRIZ CUSTO F");    
    //imprimir_matriz_f();
    //Serial.println("MATRIZ COM OBJETOS");
    imprimir_matriz_objeto();
    //Serial.println("MATRIZ COM ANALISADOS");
    imprimir_matriz_analisado();

    iniciar_lista_aberta();
    //Serial.println("IMPRIME LISTA ABERTA INICIALIZADA");
    imprime_lista_aberta(primeiro);
    //Serial.println("IMPRIME LISTA FECHADA");
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
    lista_aberta[it_aberta].pai = matriz[x_atual][y_atual].pai;
    //Serial.println("IMPRIME LISTA ABERTA, COM VALOR A SER ANALISADO");
    imprime_lista_aberta(primeiro);
    

    
    it_aberta++;
    ultimo++;
    matriz[x_atual][y_atual].analisado=1;
    //Serial.println("MATRIZ COM ANALISADOS");
    imprimir_matriz_analisado();
  }

  primeira_passada = 0;
  
  //verificar quem são os vizinhos e também adicionar na lista aberta
  detectar_vizinhos(x_atual, y_atual);
  Serial.println("IMPRIME MATRIZ COM VIZINHOS DETECTADOS");
  imprimir_matriz_f();
  Serial.println("MATRIZ COM ANALISADOS");
  imprimir_matriz_analisado();
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
  lista_aberta[primeiro].pai=0;
   
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

  delay(5000);
}
