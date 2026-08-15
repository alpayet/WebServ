#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

int main(void)
{
	// TODO enlever
	size_t size = 500 * 1024 * 1024;
	std::vector<char> buffer(size, 'A');

	std::cout << "\n[Main process parent PID: " << getpid() << "]\n";
	std::cout << "-> PRET. Ouvre un autre terminal et lance 'htop' ou 'top' pour voir la RAM.\n";
	std::cout << "-> Appuie sur ENTREE pour faire le fork()...";
	std::cin.get();


	pid_t pid = fork();

	if (pid == 0)
	{
		std::cout << "\n[Enfant PID: " << getpid() << "] Fork reussi !\n";
		char a = buffer[0];

		std::cout << "-> Appuie sur ENTREE pour modifier la memoire (declencher l'ecriture)...";
		std::cin.get();

		std::cout << "[Enfant] Ecriture en cours (Copy-On-Write actif)...\n";

		for (size_t i = 0; i < size; ++i)
		{
			buffer[i] = 'B';
		}

		std::cout << "[Enfant] Ecriture terminee ! Regarde ta RAM : elle a bondi de +500 Mo.\n";
		std::cout << "-> Appuie sur ENTREE pour terminer l'enfant...";
		std::cin.get();

		_exit(1);
	}
	else
	{
		// --- PROCESSUS PARENT ---
		wait(NULL); // Attend la fin de l'enfant
		std::cout << "\n[Parent] Enfant termine. Fin du programme.\n";
	}
}
