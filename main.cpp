#include <iostream>
#include <bitset>
#include <cmath>
class Binario{
  public:
  static const int bits{8};
  std::bitset <bits> arr;
  void Invertir(){
    int temp;
    for(int i=0,j=bits-1;i<j;i++,j--){
      temp=arr[i];
      arr[i]=arr[j];
      arr[j]=temp;
    }
  }
  void Decimal_Binario(int num){
    bool compro{false};
    if(num<0){
      compro=true;
      num*=-1;
    }
    int resul{0};
    for (int i=0; i<bits;i++){
      resul=num-(std::pow(2,bits-1-i));
      if(resul>=0){
        arr[i]=1;
        num=resul;
      }else{
        arr[i]=0;
      }
    }
    Invertir();
    if(compro){
      Complemento_2();
    }
  }
  void Complemento_2(){
    Binario z;
    for(int i=0; i<bits;i++){
      z.arr[i]=1;
    }
    z.Invertir();
    Binario m;
    for(int i=0; i<bits;i++){
      m.arr[i]=arr[i]^z.arr[i];
    }
    Binario k;
    k.Decimal_Binario(1);
    m.Suma(m,k);
    for(int i=0; i<bits;i++){
      arr[i]=m.arr[i];
    }
  }
  void Suma(Binario b, Binario c){
    std::cout << "SE VA A SUMAR " << b.arr << " + " << c.arr << std::endl;
    bool acarreo{0};
    bool resul{0};
    for(int i=0; i<bits;i++){
      resul=(c.arr[i]^acarreo)^b.arr[i]; 
      acarreo=(((b.arr[i] & c.arr[i]) | (c.arr[i] & acarreo))| (b.arr[i] & acarreo));
      arr[i]=resul;
    }
  }
  void Resta(Binario b, Binario c){
    c.Complemento_2(); 
    Suma(b, c);
  }
  void Mover(Binario& A, Binario& Q, std::bitset<1>& QQ) {
      bool guar = A.arr[bits-1];
      bool guar2 = A.arr[0];
      for (int i = 0; i < bits - 1; i++) {
          A.arr[i] = A.arr[i + 1];
      }
      A.arr[bits - 1] = guar;
      std::cout << "Estado actual de A " << A.arr << std::endl;
      
      guar=Q.arr[0];
      for (int i = 0; i < bits - 1; i++) {
          Q.arr[i] = Q.arr[i + 1];
      }
      Q.arr[bits - 1]=guar2;
      std::cout << "Estado actual de Q " << Q.arr << std::endl;
      QQ[0] = guar;
  }
  std::bitset<bits*2>Algoritmo_Booth(Binario M,Binario Q){
    int Contador{bits};
    std::bitset<bits*2> resul;
    Binario A;
    std::bitset <1> Q_minus_1;
    for(int i=0; i<bits;i++){
      A.arr[i]=0;
    }
    Q_minus_1[0]=0;
    std::cout << "TABLA ESTADOS " << std::endl;
    std::cout << "A" << "               " << "Q" << "                       " << "Q-1" << "                 " << "M" << std::endl;
    std::cout << A.arr << "              " << Q.arr << "              " << Q_minus_1[0] << "              " << M.arr << std::endl;
    do{
      if(Q.arr[0]==1 && Q_minus_1[0]==0){
        std::cout << "ENTRO CASO 1 RESTA" << std::endl;
        A.Resta(A,M);
        Mover(A,Q,Q_minus_1);
        Contador--;
      }else if(Q.arr[0]==0 && Q_minus_1[0]==1){
        std::cout << "ENTRO CASO 2 SUMA" << std::endl;
        A.Suma(A,M);
        Mover(A,Q,Q_minus_1);
        Contador--;
      }else{
        std::cout << "ENTRO CASO 3 MOVERSE" << std::endl;
        Mover(A,Q,Q_minus_1);
        Contador--;
      }
      std::cout << "TABLA ESTADOS " << std::endl;
      std::cout << "A" << "                 " << "Q" << "                 " << "Q-1" << "                 " << "M" << std::endl;
      std::cout << A.arr << "           " << Q.arr << "           " << Q_minus_1[0] << "           " << M.arr << std::endl;
    }while(Contador!=0);
    for(int i=0; i<bits;i++){
      resul[i+bits]=A.arr[i];
    }
    for(int i=0;i < bits;i++){
      resul[i]=Q.arr[i];
    }
    return resul;
  }
};
int main() {
  int num;
  int num2;
  std::cout << "Hello World!\n";
  std::cout << "Bienvenido dame el numero que quieres convertir a binario\n";
  std::cin >> num;
  Binario a;
  a.Decimal_Binario(num);
  std::cout << "Representación binaria de " << num << ": " << a.arr << std::endl;
  Binario d;
  std::cout << "Dame el numero que quieres convertir a binario\n";
  std::cin >> num2;
  d.Decimal_Binario(num2);
  std::cout << "Representación binaria de " << num2 << ": " << d.arr << std::endl;
  std::cout << a.Algoritmo_Booth(a, d);
}