#include <iostream>

#ifndef PERSONA_H
#define PERSONA_H

class Persona {
	private:
		std::string nome;
		std::string cognome;
		int eta = 0;
		std::string email;
		int *temperatura;
	public:
		Persona() {
			temperatura = new int[100];
		}
		Persona(std::string s, std::string c, int e, std::string em) : 
			nome(s), cognome(c), eta(e), email(em) {
			temperatura = new int[100];
		}
		
		Persona(const Persona& p) {
			nome = p.nome;
			cognome = p.cognome;
			eta = p.eta;
			email = p.email;
			temperatura = new int[100];
		}
		
		void print();
		
		~Persona() {
			delete [] temperatura;
		}
		
		
/*		void print() {
			std::cout << "Mi chiamo " << nome << " " << cognome << ", ho " << eta << " anni e la mia email è " << email << std::endl;
		}*/
};

void Persona::print() {
			std::cout << "Mi chiamo " << nome << " " << cognome << ", ho " << eta << " anni e la mia email è " << email << std::endl;
}

#endif
