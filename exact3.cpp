/*Nom: Jordi Ricart Garcia
S'ha d'optimitzar aquest codi tot el que pugueu. Fer un document PDF on s'explica detalladament com estava el codi i quina millora heu fet.Podeu modificar el codi tot el que vulgueu, però ha de mantenir les mateixes funcionalitats, no pot tenir noves ni tenir menys, el programa ha de fer el mateix.*/
#include <iostream>
#include <cstdlib> //for rand and srand
#include <cstdio>
#include <string>
#include <ctime> // time function for seed value
#include <chrono>
#include <thread>
using namespace std;
struct carta
{
  int numero;
  string palo;
};
int sum_carta(int i, int puntos, struct carta mano[])
{
  switch (mano[i].numero)
  {
  case 1:
    cout << "\033[1;33m A de " << mano[i].palo << "\033[0m" << endl;
    if (puntos + 11 > 21)
    {
      puntos = puntos + 1;
    }
    else
    {
      puntos = puntos + 11;
    }
    break;
  case 11:
    cout << "\033[1;33m Sota de " << mano[i].palo << "\033[0m" << endl;
    puntos = puntos + 10;
    break;
  case 12:
    cout << "\033[1;33m Caballo de " << mano[i].palo << "\033[0m" << endl;
    puntos = puntos + 10;
    break;
  case 13:
    cout << "\033[1;33m Rey de " << mano[i].palo << "\033[0m" << endl;
    puntos = puntos + 10;
    break;
  default:
    cout << "\033[1;33m " << mano[i].numero << " de " << mano[i].palo << "\033[0m" << endl;
    puntos = puntos + mano[i].numero;
    break;
  }
  return puntos;
}
bool calcul_puntos(int puntos)
{
  if (puntos > 21)
  {
    cout << "\033[1;31mTe has pasado... puntos: " << puntos << "\033[0m" << endl;
    cout << "\033[1;31mHas perdido\033[0m" << endl;
    return false;
  }
  else if (puntos == 21)
  {
    cout << "\033[1;33mFELICIDADES tienes " << puntos << " puntos!(Blackjack)\033[0m" << endl;
    return false;
  }
  else
  {
    cout << "\033[1;32mTienes " << puntos << " puntos \033[0m" << endl;
    return true;
  }
};
int main()
{
  struct carta baraja[52];
  time_t t;
  srand((unsigned)time(&t));
  int i, numeros[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  const string palos[4] = {"Corazones", "Diamantes", "Picas", "Treboles"};
  int contador = 0;
  for (i = 0; i < 13; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      baraja[contador].numero = numeros[i];
      baraja[contador].palo = palos[j];
      contador++;
    }
  }
  int opcion;
  bool repetir = true, principi = true;
  struct carta mano[52], manoMaquina[52];
  int num_cartas_mano = 2, puntos = 0, contadorAs = 0, puntosMaquina;

  // Repartir cartas
  for (int contadorBaraja = 0; contadorBaraja < 2; contadorBaraja++)
  {
    mano[contadorBaraja] = baraja[rand() % 52];
  }
  do
  {
    cout << "\033[1;31m \n\nMenu de Opciones \033[0m" << endl;
    cout << "\033[1;32m 1. Robar carta \033[0m" << endl;
    cout << "\033[1;32m 2. Mostrar mano \033[0m" << endl;
    cout << "\033[1;32m 3. Plantarse \033[0m" << endl;
    cout << "\033[1;32m 4. Ver baraja \033[0m" << endl;
    cout << "\033[1;32m 0. SALIR \033[0m" << endl;
    if (principi)
    {
      cout << "\033[1;31m \nTus cartas son: \033[0m" << endl;
      for (i = 0; mano[i].palo != ""; i++)
      {
        puntos = sum_carta(i, puntos, mano);
      }
      if (calcul_puntos(puntos) == false)
      {
        repetir = false;
        break;
      }
      principi = false;
    }
    cout << "\nIngrese una opcion: ";
    cin >> opcion;

    switch (opcion)
    {
    case 1:
      system("clear");
      mano[num_cartas_mano] = baraja[rand() % 52];
      cout << "\033[1;32mTu carta es: \033[0m" << endl;
      puntos = sum_carta(num_cartas_mano, puntos, mano);
      num_cartas_mano++;
      if (calcul_puntos(puntos) == false)
      {
        repetir = false;
      }
      break;
    case 2:
      system("clear");
      cout << "\033[1;31m \nTus cartas son: \033[0m" << endl;
      puntos = 0;
      for (i = 0; mano[i].palo != ""; i++)
      {
        puntos = sum_carta(i, puntos, mano);
      }
      cout << "\033[1;32mTienes " << puntos << " puntos \033[0m" << endl;
      break;
    case 3:
      system("clear");
      cout << "\033[1;32mHas conseguido " << puntos << " puntos \033[0m" << endl;
      cout << "\033[1;36mAhora juega la máquina\033[0m" << endl;
      while (puntosMaquina < puntos)
      {
        cout << "\033[1;36mLa maquina roba carta\033[0m" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        manoMaquina[i] = baraja[rand() % 52];
        puntosMaquina = sum_carta(i, puntosMaquina, manoMaquina);
        puntosMaquina = puntosMaquina + manoMaquina[i].numero;
        cout << "\033[1;37m Puntos maquina: " << puntosMaquina << endl;
        i++;
      }
      if (puntosMaquina > 21)
      {
        cout << "\033[1;31mLa máquina se ha pasado\033[0m" << endl;
        cout << "\033[1;33mFELICIDADES, HAS GANADO!\033[0m" << endl;
      }
      else if (puntosMaquina == puntos)
      {
        cout << "\033[1;33mLa máquina se planta\033[0m" << endl;
        cout << "\033[1;33mEmpate\033[0m" << endl;
      }
      else
      {
        cout << "\033[1;33mLa máquina se planta\033[0m" << endl;
        cout << "\033[1;31mHas perdido...\033[0m" << endl;
      }
      cout << "\033[1;35mTu has conseguido " << puntos << " puntos y la máquina " << puntosMaquina << " puntos\033[0m" << endl;
      repetir = false;
      break;
    case 4:
      for (int contadorBaraja = 0; contadorBaraja < 52; contadorBaraja++)
      {
        switch (baraja[contadorBaraja].numero)
        {
        case 1:
          cout << "A de " << baraja[contadorBaraja].palo << endl;         
          break;
        case 11:
          cout << "Sota de " << baraja[contadorBaraja].palo << endl;
          break;
        case 12:
          cout << "Caballo de " << baraja[contadorBaraja].palo << endl;
          break;
        case 13:
          cout << "Rey de " << baraja[contadorBaraja].palo << endl;
          break;
        default:
          cout << baraja[contadorBaraja].numero << " de " << baraja[contadorBaraja].palo << endl;
          break;
        }
      }
      break;
    case 0:
      repetir = false;
      break;
    }
  } while (repetir);
}