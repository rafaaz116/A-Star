unsigned long tempo;
#define num_linhas 10
#define num_colunas 10
byte x_inicio = 1;
byte y_inicio = 3;
byte x_fim = 5;
byte y_fim = 9;

typedef struct cel{
  byte g;
  byte h;
  byte f;
  byte nome;
  byte indice; //0 - celula que não foi analisada, 1 - celula analisada e 2 - objeto.
  byte pai;
}CELULA;

CELULA matriz[num_linhas][num_colunas];

CELULA *lista_aberta = (CELULA*)malloc((num_linhas*num_colunas)*sizeof(CELULA));
//CELULA lista_aberta[num_linhas*num_colunas];
byte it_aberta=0;
//CELULA *lista_fechada = (CELULA*)malloc((num_linhas*num_colunas)*sizeof(CELULA));
CELULA lista_fechada[num_linhas*num_colunas];
byte it_fechada=0;
byte primeiro=0;
short ultimo=-1;
byte x_atual;
byte y_atual;
byte primeira_passada=1;
char movimento_robo[num_linhas*num_colunas]; //'b' - baixo, 'c' - cima, 'd' - direita, 'e' - esquerda.
byte contador_movimento=0;
byte flag=0;

void h(byte linha, byte coluna){
  byte manhattan;

  manhattan = (abs(x_fim - linha) + abs(y_fim - coluna));

  matriz[linha][coluna].h = manhattan;
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

  for(i=0;i<num_linhas;i++){
    for(j=0;j<num_colunas;j++){
      if(matriz[x][y].pai==matriz[i][j].nome){ //se o nome da celula for igual ao pai da celula atual
        if((x-1)==i && y==j){
          //back
          movimento_robo[contador_movimento++]='b'; //***celula de cima, porém o robô irá fazer o caminho contrário(do início ao fim) por isso celula de baixo
          x=i;
          y=j;
          //Serial.println("Cima");
          if(x==x_inicio && y==y_inicio){
            //Serial.println("Mover");
            
            mover();
            //Serial.println("Fim 1");
            tempo = millis();
            //Serial.print("Tempo de execução em ms: ");
            Serial.println(tempo);
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
            //Serial.println("Baixo");
            if(x==x_inicio && y==y_inicio){
              //Serial.println("Mover");
              
              mover();
              //Serial.println("Fim 2");
              tempo = millis();
              //Serial.print("Tempo de execução em ms: ");
              Serial.println(tempo);
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
              //Serial.println("Esquerda");
              if(x==x_inicio && y==y_inicio){
                //Serial.println("Mover");             
                mover();
                //Serial.println("Fim 3");
                tempo = millis();
                //Serial.print("Tempo de execução em ms: ");
                Serial.println(tempo);
                delay(25000);

              }
              melhor_caminho(x, y);
            }
            else{
              //back
              movimento_robo[contador_movimento++]='e';
              x=i;
              y=j;
              //Serial.println("Direita");
              if(x==x_inicio && y==y_inicio){
                //Serial.println("Mover");
                mover();
                //Serial.println("Fim 4");
                tempo = millis();
                //Serial.print("Tempo de execução em ms: ");
                Serial.println(tempo);
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
      Serial.println("baixo");
      //frente();
      //parar();
    }
    else{
      if(movimento_robo[m] == 'c'){
        Serial.println("cima");
        //tras();
        //parar();        
      }
      else{
        if(movimento_robo[m] == 'd'){
          Serial.println("direita");
          //direita();
          //parar();
        }
        else{
          Serial.println("esquerda");
          //esquerda();
          //parar();
        }          
      }
    }
  }  
}

void iniciar_matriz(){
  byte i, j, cont;
  cont=1;
  for(i=0;i<num_linhas;i++){
    for(j=0;j<num_colunas;j++){
      if((i==2 || i==3 || i==6 || i==7) && (j>=3 && j<=6)){
        matriz[i][j].g=0;
        matriz[i][j].h=0;
        matriz[i][j].f=0;
        matriz[i][j].nome=cont++;
        matriz[i][j].indice=2;
        matriz[i][j].pai=0;
      }
      else{
        matriz[i][j].g=0;
        matriz[i][j].h=0;
        matriz[i][j].f=0;
        matriz[i][j].nome=cont++;
        matriz[i][j].indice=0;
        matriz[i][j].pai=0;
      }
    }
  }
}

void iniciar_lista_aberta(){
  byte i;
  for(i=0;i<num_linhas*num_colunas;i++){
    lista_aberta[i].g=0;
    lista_aberta[i].h=0;
    lista_aberta[i].f=0;
    lista_aberta[i].nome=0;
    lista_aberta[i].indice=0;
    lista_aberta[i].pai=0;
  }
}

void iniciar_lista_fechada(){
  byte i;
  for(i=0;i<num_linhas*num_colunas;i++){
    lista_fechada[i].g=0;
    lista_fechada[i].h=0;
    lista_fechada[i].f=0;
    lista_fechada[i].nome=0;
    lista_fechada[i].indice=0;
    lista_fechada[i].pai=0;
  }
}  

void detectar_vizinhos(byte x_atual, byte y_atual){
  byte i, j, n;
  //nao pode considerar objeto e quem esta na lista aberta e fechada
  for(i=0;i<num_linhas;i++){
    for(j=0;j<num_colunas;j++){
      if(i==(x_atual-1) && j==y_atual && matriz[i][j].indice==0){ //se for um vizinho
        if(i==x_fim && j==y_fim){ //se esse vizinho for a celula objetivo
          matriz[i][j].pai = matriz[x_atual][y_atual].nome;
          Serial.println("1");
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
          matriz[i][j].pai = matriz[x_atual][y_atual].nome;
          lista_aberta[it_aberta]=matriz[i][j];
          it_aberta++;
          ultimo++;
          matriz[i][j].indice=1;        
        }
      }
      if(i==x_atual && j==(y_atual+1) && matriz[i][j].indice==0){
        if(i==x_fim && j==y_fim){ //se esse vizinho for a celula objetivo
          matriz[i][j].pai = matriz[x_atual][y_atual].nome;
          Serial.println("2");
          melhor_caminho(i, j);

        }
        else{
          //calcular f, g, h
          h(i, j);
          g(i, j);
          f(i, j);
          matriz[i][j].pai = matriz[x_atual][y_atual].nome;
          lista_aberta[it_aberta]=matriz[i][j];
          it_aberta++;
          ultimo++;
          matriz[i][j].indice=1;
        }
      }
      if(i==(x_atual+1) && j==y_atual && matriz[i][j].indice==0){
        if(i==x_fim && j==y_fim){ //se esse vizinho for a celula objetivo
          matriz[i][j].pai = matriz[x_atual][y_atual].nome;
          Serial.println("3");
          melhor_caminho(i, j);
          //mover();

        }
        else{
          h(i, j);
          g(i, j);
          f(i, j);
          matriz[i][j].pai = matriz[x_atual][y_atual].nome;
          lista_aberta[it_aberta]=matriz[i][j];
          it_aberta++; 
          ultimo++; 
          matriz[i][j].indice=1;   
        }  
      }
      if(i==x_atual && j==(y_atual-1) && matriz[i][j].indice==0){
        if(i==x_fim && j==y_fim){ //se esse vizinho for a celula objetivo
          matriz[i][j].pai = matriz[x_atual][y_atual].nome;
          Serial.println("4");
          melhor_caminho(i, j);

        }
        else{
          h(i, j);
          g(i, j);
          f(i, j);
          matriz[i][j].pai = matriz[x_atual][y_atual].nome;
          lista_aberta[it_aberta]=matriz[i][j];
          it_aberta++;
          ultimo++;
          matriz[i][j].indice=1;   
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
    key = lista_aberta[i];
    /*
    key.g = lista_aberta[i].g;
    key.h = lista_aberta[i].h;
    key.f = lista_aberta[i].f;
    key.nome = lista_aberta[i].nome;
    key.indice = lista_aberta[i].indice;
    key.pai = lista_aberta[i].pai;
    */
    j = i - 1;
    while (j >= primeiro && lista_aberta[j].f > key.f) {
        lista_aberta[j + 1] = lista_aberta[j];
        /*
        lista_aberta[j + 1].g = lista_aberta[j].g;
        lista_aberta[j + 1].h = lista_aberta[j].h;
        lista_aberta[j + 1].f = lista_aberta[j].f;
        lista_aberta[j + 1].nome = lista_aberta[j].nome;
        lista_aberta[j + 1].indice = lista_aberta[j].indice;
        lista_aberta[j + 1].pai = lista_aberta[j].pai;
        */
        j = j - 1;
    }
    lista_aberta[j + 1] = key;
    /*
    lista_aberta[j + 1].g = key.g;
    lista_aberta[j + 1].h = key.h;
    lista_aberta[j + 1].f = key.f;
    lista_aberta[j + 1].nome = key.nome;
    lista_aberta[j + 1].indice = key.indice;
    lista_aberta[j + 1].pai = key.pai;
    */
  }
}

void busca_celula_analisar(){
  byte i, j, contador;
  contador=0;
  for(i=0;i<num_linhas;i++){
    for(j=0;j<num_colunas;j++){
      contador++;
      if(lista_aberta[primeiro].nome == contador){
        x_atual=i;
        y_atual=j;
      }     
    }
  }
}

void imprime_lista_aberta(byte primerio){
  byte i;
  for(i=primeiro;i<num_linhas*num_colunas;i++){
    Serial.print(lista_aberta[i].nome);
    Serial.print(" ");
  }
  Serial.println(" ");
}

void imprime_lista_fechada(){
  byte i;
  for(i=0;i<num_linhas*num_colunas;i++){
    Serial.print(lista_fechada[i].nome);
    Serial.print(" ");
  }
  Serial.println(" ");
}

void imprimir_matriz_nome(){
  byte i, j;
  for(i=0;i<num_linhas;i++){
    for(j=0;j<num_colunas;j++){
      Serial.print(matriz[i][j].nome);
      Serial.print(' ');
    }
    Serial.println(" ");
  }
}

void imprimir_matriz_f(){
  byte i, j;
  for(i=0;i<num_linhas;i++){
    for(j=0;j<num_colunas;j++){
      Serial.print(matriz[i][j].f);
      Serial.print(' ');
    }
    Serial.println(" ");
  }
}

void imprimir_matriz_indice(){
  byte i, j;
  for(i=0;i<num_linhas;i++){
    for(j=0;j<num_colunas;j++){
      Serial.print(matriz[i][j].indice);
      Serial.print(' ');
    }
    Serial.println(" ");
  }  
}

void frente(){
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  analogWrite(9, 191);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  analogWrite(10, 191);
  delay(1850);
}

void tras(){
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  analogWrite(9, 191);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  analogWrite(10, 191);
  delay(1850); 
}

void direita(){
  //gira roda esquera
  digitalWrite(3, HIGH); // amarelo positivo
  digitalWrite(4, LOW);
  analogWrite(9, 191);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  analogWrite(10, 191);
  delay(900);
  //reto
  digitalWrite(3, HIGH); //amarelo (+)
  digitalWrite(4, LOW); //preto (-)
  analogWrite(9, 191);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  analogWrite(10, 191);
  delay(800);
  //gira direita
  digitalWrite(3, LOW); //amarelo (+)
  digitalWrite(4, LOW); //preto (-)
  analogWrite(9, 191);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  analogWrite(10, 191);
  delay(900);
}

void esquerda(){
  //gira a roda da esquerda
  digitalWrite(3, LOW); //amarelo (+)
  digitalWrite(4, LOW); //preto (-)
  analogWrite(9, 191);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  analogWrite(10, 191);
  delay(900);
  //reto
  digitalWrite(3, HIGH); //amarelo (+)
  digitalWrite(4, LOW); //preto (-)
  analogWrite(9, 191);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  analogWrite(10, 191);
  delay(800);
  //gira a roda da direita
  digitalWrite(3, HIGH); // amarelo positivo
  digitalWrite(4, LOW);
  analogWrite(9, 191);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  analogWrite(10, 191);
  delay(900);  
}

void parar(){
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  delay(4000);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(3, OUTPUT); //saída do arduino para a entrada do l293d
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
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
    //imprimir_matriz_objeto();
    //Serial.println("MATRIZ COM ANALISADOS");
    //imprimir_matriz_indice();

    iniciar_lista_aberta();
    //Serial.println("IMPRIME LISTA ABERTA INICIALIZADA");
    //imprime_lista_aberta(primeiro);
    //Serial.println("IMPRIME LISTA FECHADA");
    iniciar_lista_fechada();
    //imprime_lista_fechada();

    //adiciona a celula início na lista aberta

    x_atual=x_inicio;
    y_atual=y_inicio;
    
    lista_aberta[it_aberta] = matriz[x_atual][y_atual];
    /*
    lista_aberta[it_aberta].g = matriz[x_atual][y_atual].g;
    lista_aberta[it_aberta].h = matriz[x_atual][y_atual].h;
    lista_aberta[it_aberta].f = matriz[x_atual][y_atual].f;
    lista_aberta[it_aberta].nome = matriz[x_atual][y_atual].nome;
    lista_aberta[it_aberta].indice = matriz[x_atual][y_atual].indice;
    lista_aberta[it_aberta].pai = matriz[x_atual][y_atual].pai;
    */
    //Serial.println("IMPRIME LISTA ABERTA, COM VALOR A SER ANALISADO");
    //imprime_lista_aberta(primeiro);
    

    
    it_aberta++;
    ultimo++;
    matriz[x_atual][y_atual].indice=1;
    //Serial.println("MATRIZ COM ANALISADOS");
    //imprimir_matriz_analisado();
  }

  primeira_passada = 0;
  
  //verificar quem são os vizinhos e também adicionar na lista aberta
  detectar_vizinhos(x_atual, y_atual);
  //Serial.println("IMPRIME MATRIZ COM VIZINHOS DETECTADOS");
  //imprimir_matriz_f();
  //Serial.println("MATRIZ COM ANALISADOS");
  //imprimir_matriz_analisado();

  lista_fechada[it_fechada]=lista_aberta[primeiro];
  //Serial.println("IMPRIME LISTA FECHADA");
  //imprime_lista_fechada();
  it_fechada++;

  primeiro++; //novo primeiro
  
  //Serial.println("IMPRIME LISTA ABERTA ANTES DO INSERTION SORT");
  //imprime_lista_aberta(primeiro);  
  insertion_sort(primeiro, ultimo);
  //Serial.println("IMPRIME LISTA ABERTA DEPOIS DO INSERTION SORT");
  //imprime_lista_aberta(primeiro);
  busca_celula_analisar();
  //Serial.print("X ATUAL: ");
  //Serial.println(x_atual);
  //Serial.print("Y ATUAL: ");
  //Serial.println(y_atual);
  //Serial.println("");
  //delay(1000);
}
