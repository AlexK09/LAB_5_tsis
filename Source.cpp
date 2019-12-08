#include <iostream>
#include <vector>
#include<string>


struct point {
	double x;
	double y;

	point() {
		x = y = 0;
	}

	point(double x, double y) {
		this->x = x;
		this->y = y;
	}

	void printer() {
		std::cout <<"  "<< x << "        |       " << y;
	}

	double sravnenie(point A) {
		return sqrt((x - A.x) * (x - A.x) + (y - A.y)*(y - A.y));
	}
};

std::vector<std::string> name() {
	std::vector<std::string> names(4);
	names[0] = "Spain";
	names[1] = "Turkey";
	names[2] = "Cuba";
	names[3] = "Indonezia";
	return names;
}

std::vector<std::vector<double>> zapolnenie()
{
	std::vector<std::vector<double>>tablitsa(4, std::vector<double>(4));
	tablitsa[0][0] = 4;
	tablitsa[0][1] = 6;
	tablitsa[0][2] = 5;
	tablitsa[0][3] = 10;
	tablitsa[1][0] = 2;
	tablitsa[1][1] = 8;
	tablitsa[1][2] = 3;
	tablitsa[1][3] = 2;
	tablitsa[2][0] = 7;
	tablitsa[2][1] = 4;
	tablitsa[2][2] = 7;
	tablitsa[2][3] = 6;
	tablitsa[3][0] = 8;
	tablitsa[3][1] = 2;
	tablitsa[3][2] = 9;
	tablitsa[3][3] = 4;


	return tablitsa;
}

std::vector<double> minimummaximum(double k) {
	std::vector<double> minmax(2);
	std::vector<std::vector<double>> tablitsa = zapolnenie();
	minmax[0]=11;
	minmax[1] = 0;
	for (int i = 0; i < 4; i++) {
		
		for (int j = 0; j < 4; j++) {
			if (j != k) continue;
			else {
				if (tablitsa[i][j] < minmax[0])  minmax[0] = tablitsa[i][j];
				if (tablitsa[i][j] > minmax[1]) minmax[1] = tablitsa[i][j];
			}
		}
	}
	
	return minmax;
}

void printertabl(std::vector<std::vector<double>> tablitsa) {
	std::vector<std::string>names = name();
	std::cout << "           |  Trip price  |  Length  | Sea shore  | Attractions  |" << std::endl;
	for (int i = 0; i < 4; i++) {
		if (i == 0)
			std::cout << names[i] << "      |";
		if (i == 1)
			std::cout << names[i] << "     |";
		if (i == 2)
			std::cout << names[i] << "       |";
		if (i == 3)
			std::cout << names[i] << "  |";
		for (int j = 0; j < 4; j++) {
			if (j == 0) {
				std::cout << "     ";
				printf("%.2f", tablitsa[i][j]);
				std::cout << "     |";
			}

			if (j == 1) {
				std::cout << "   ";
				printf("%.2f", tablitsa[i][j]);
				std::cout << "   |";
			}

			if (j == 2) {
				std::cout << "    ";
				printf("%.2f", tablitsa[i][j]);
				std::cout << "    |";
			}

			if (j == 3) {
				if (tablitsa[i][j] < 10) {
					std::cout << "     ";
					printf("%.2f", tablitsa[i][j]);
					std::cout << "     |";
				}
				else {
					std::cout << "     ";
					printf("%.2f", tablitsa[i][j]);
					std::cout << "    |";
				}
			}
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}

double OS(std::vector<std::vector<double>> massiv) {
	double os = 0;
	double Amax = 0;
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			Amax += massiv[i][j];

		}
		os += Amax * massiv[j][5];
		Amax = 0;
	}
	os = (os - 4) / 3;
	return os;
}

void metod1() {

	std::cout << "Metod zameny kriteriev" << std::endl;
	std::vector<std::string> names=name();

	std::vector<double> kritmin(4);
	kritmin[0] = 0.25;
	kritmin[1] = 0.3;
	kritmin[3] = 0.45;

	std::vector<std::vector<double>> tablitsa = zapolnenie();

	printertabl(tablitsa);

	int mainkrit = 2;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {	
			if (j == mainkrit) {
				continue;
			}
			else {
				std::vector<double>minmax = minimummaximum(j);
				tablitsa[i][j] = (tablitsa[i][j] - minmax[0]) / (minmax[1] - minmax[0]);
							
			}
			
		}
		
	}
	printertabl(tablitsa);

	std::cout << "minimal points:" <<std::endl<<"main point - Sea shore"<<std::endl << "Trip price - 25% (0.25)" << std::endl << "Length - 30% (0.3)" << std::endl << "Attractions - 45% (0.45)" << std::endl;

	for (int i=0; i<4; i++) 
	for (int i = 0; i < 4; i++) {
		std::vector<int> kriterialnyi(4);
		for (int j = 0; j < 4; j++) {
			if (tablitsa[i][j] == mainkrit) kriterialnyi[j] = 1;
			else {
				if (tablitsa[i][j] > kritmin[j]) kriterialnyi[j] = 1;
				else kriterialnyi[j] = 0;
				
			}
		}
		int sum = 0;
		for (int u = 0; u < 4; u++) sum+= kriterialnyi[u];
		if (sum != 4) tablitsa[i][mainkrit] = 0;
		else continue;
	}

	int max = 0;
	for (int i = 0; i < 4; i++) {
		if (tablitsa[i][mainkrit] > max) max = i;
	}

	std::cout<<std::endl << "Optimalnyi variant - " << names[max] << std::endl<<"------------------------------------";

}

void metod2() {
	std::cout << "Metod formirovaniya i suzheniya Pareto" << std::endl;
	std::vector<std::string> names = name();
	std::vector<std::vector<double>> tablitsa = zapolnenie();
	std::cout << std::endl;
	printertabl(tablitsa);
	std::cout << "          Trip Price   |    Length    " << std::endl;
	point Spain(tablitsa[0][0], tablitsa[0][1]);
	std::cout << "Spain -     "; Spain.printer(); std::cout << std::endl;
	point Turkey(tablitsa[1][0], tablitsa[1][1]);
	std::cout << "Turkey -    "; Turkey.printer();  std::cout << std::endl;
	point Cuba(tablitsa[2][0], tablitsa[2][1]);
	std::cout << "Cuba -      "; Cuba.printer(); std::cout << std::endl;
	point Indonesia(tablitsa[3][0], tablitsa[3][1]);
	std::cout << "Indonesia - "; Indonesia.printer(); std::cout << std::endl;
	std::cout << std::endl;
	

	std::vector<double> minmax = minimummaximum(0);
	std::vector<double> minmax1 = minimummaximum(1);
	point utopia(10, 10);
	std::cout << "             Trip Price   |    Length    " << std::endl;
	std::cout << "utopia point - "; utopia.printer();
	std::cout << std::endl<<std::endl;

	std::vector<double>rasstoyanie(4);

	
	rasstoyanie[0] = utopia.sravnenie(Spain);
	rasstoyanie[1] = utopia.sravnenie(Turkey);
	rasstoyanie[2] = utopia.sravnenie(Cuba);
	rasstoyanie[3] = utopia.sravnenie(Indonesia);

	std::cout << "Rasstoyanie do utopii:" << std::endl;
	for (int i = 0; i < 4; i++) {
		std::cout << names[i] << " - ";
		printf("%.2f", rasstoyanie[i]);
		std::cout << "   "<<std::endl;
	}

	double min=11;
	int minimum = 0;
	for (int i = 0; i < 4; i++) {
		if (rasstoyanie[i] < min) {
			min = rasstoyanie[i];
			minimum = i;

		}
	}

	std::cout << std::endl << "Optimalnyi variant - " << names[minimum] << std::endl<< "------------------------------------";
	
}

void metod3() {
	std::vector<std::string>names = name();
	std::cout << "metod vzveshivaniya i ob'edineniya kriteriev" << std::endl;
	std::vector<std::vector<double>> tablitsa = zapolnenie();
	printertabl(tablitsa);
	std::vector<double> sum(4);
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j<4; j++) {
			sum[i] += tablitsa[i][j];
		}
	}

	

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tablitsa[i][j] = tablitsa[i][j] / sum[i];
			
		}
	}

	printertabl(tablitsa);
	std::vector<std::vector<double>>gamma(4, std::vector<double>(4));
	gamma[0][0] = 0;
	gamma[0][1] = 0.5;
	gamma[0][2] = 0;
	gamma[0][3] = 0;
	gamma[1][0] = 0.5;
	gamma[1][1] = 0;
	gamma[1][2] = 0;
	gamma[1][3] = 0;
	gamma[2][0] = 1;
	gamma[2][1] = 1;
	gamma[2][2] = 0;
	gamma[2][3] = 0;
	gamma[3][0] = 1;
	gamma[3][1] = 1;
	gamma[3][2] = 1;
	gamma[3][3] = 0;

	std::vector<double> alpha(4);

	std::cout << "alpha  =  ";
	for (int i = 0; i < 4; i++) alpha[i] = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			alpha[i] += gamma[i][j];
			
		}
		printf("%.2f", alpha[i]);
		std::cout << "  ";
	}
	std::cout << std::endl;

	std::cout << "alphan =  ";
	for (int i = 0; i < 4; i++) {
		
			alpha[i] = alpha[i]/6;

		
			printf("%.2f", alpha[i]);
			std::cout << "  ";
	}
	std::cout << std::endl;

	std::vector<double> res(4);
	for (int i = 0; i < 4; i++) res[i] = 0;


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res[i] += tablitsa[i][j] * alpha[j];	
		}
	}
	std::cout << std::endl;
	std::cout << "result: " << std::endl;
	
	for (int i = 0; i < 4; i++) {
		std::cout<<names[i]<<" - ";
		printf("%.2f", res[i]);
		std::cout << std::endl;
	}

	double max = 0;
	int maximum = 0;
	for (int i = 0; i < 4; i++) if (res[i] > max) {
		max = res[i];
		maximum = i;
	}

	std::cout << std::endl<<std::endl << "Optimalnyi variant - " << names[maximum] << std::endl << "------------------------------------";

}

void metod4() {
	std::cout << "Metod analiza ierarhiy"<<std::endl;
	std::vector<std::string> names = name();
	std::vector<std::vector<double>>Ocenka(4, std::vector<double>(6));
	std::vector<std::vector<double>>Itog(4, std::vector<double>(6));
	//deshevisna
	std::cout << "Price" << std::endl;
	
	{Ocenka[0][0] = 1;
	Ocenka[0][1] = 3;
	Ocenka[0][2] = 0.33;
	Ocenka[0][3] = 0.2;
	Ocenka[1][0] = 0.33;
	Ocenka[1][1] = 1;
	Ocenka[1][2] = 0.2;
	Ocenka[1][3] = 0.14;
	Ocenka[2][0] = 3;
	Ocenka[2][1] = 5;
	Ocenka[2][2] = 1;
	Ocenka[2][3] = 0.33;
	Ocenka[3][0] = 5;
	Ocenka[3][1] = 7;
	Ocenka[3][2] = 3;
	Ocenka[3][3] = 1;
	Ocenka[0][4] = 0;
	Ocenka[0][5] = 0;
	Ocenka[1][4] = 0;
	Ocenka[1][5] = 0;
	Ocenka[2][4] = 0;
	Ocenka[2][5] = 0;
	Ocenka[3][4] = 0;
	Ocenka[3][5] = 0;

	for (int i = 0; i < 4; i++) Ocenka[0][4] += Ocenka[0][i];
	for (int i = 0; i < 4; i++) Ocenka[1][4] += Ocenka[1][i];
	for (int i = 0; i < 4; i++) Ocenka[2][4] += Ocenka[2][i];
	for (int i = 0; i < 4; i++) Ocenka[3][4] += Ocenka[3][i];

	double sum = 0;
	for (int i = 0; i < 4; i++) sum += Ocenka[i][4];

	for (int i = 0; i < 4; i++)
		Ocenka[i][5] = Ocenka[i][4] / sum;

	std::cout << "           |  Spain  | Turkey  |  Cuba   |Indonezia|   SUM   |  SUMn   |" << std::endl;
	for (int i = 0; i < 4; i++) {
		if (i == 0)
			std::cout << names[i] << "      ";
		if (i == 1)
			std::cout << names[i] << "     ";
		if (i == 2)
			std::cout << names[i] << "       ";
		if (i == 3)
			std::cout << names[i] << "  ";

		for (int j = 0; j < 6; j++) {
			std::cout << "|  ";
			printf("%.2f", Ocenka[i][j]);
			if (Ocenka[i][j] >= 10)
				std::cout << "  ";
			else std::cout << "   ";
		}
		std::cout << "|" << std::endl;
	}
	for (int i = 0; i < 4; i++) {
		Itog[i][0] = Ocenka[i][5];
	}
	}

	std::cout << std::endl;
	std::cout << "Otnoshenie soglasovannosti =" <<OS(Ocenka);
	std::cout << std::endl << std::endl;
	//dalnost'
	std::cout << "Length" << std::endl;

	{
	Ocenka[0][0] = 1;
	Ocenka[0][1] = 0.33;
	Ocenka[0][2] = 3;
	Ocenka[0][3] = 5;
	Ocenka[1][0] = 3;
	Ocenka[1][1] = 1;
	Ocenka[1][2] = 5;
	Ocenka[1][3] = 7;
	Ocenka[2][0] = 0.33;
	Ocenka[2][1] = 0.2;
	Ocenka[2][2] = 1;
	Ocenka[2][3] = 3;
	Ocenka[3][0] = 0.2;
	Ocenka[3][1] = 0.142;
	Ocenka[3][2] = 0.33;
	Ocenka[3][3] = 1;



	Ocenka[0][4] = 0;
	Ocenka[0][5] = 0;
	Ocenka[1][4] = 0;
	Ocenka[1][5] = 0;
	Ocenka[2][4] = 0;
	Ocenka[2][5] = 0;
	Ocenka[3][4] = 0;
	Ocenka[3][5] = 0;

	for (int i = 0; i < 4; i++) Ocenka[0][4] += Ocenka[0][i];
	for (int i = 0; i < 4; i++) Ocenka[1][4] += Ocenka[1][i];
	for (int i = 0; i < 4; i++) Ocenka[2][4] += Ocenka[2][i];
	for (int i = 0; i < 4; i++) Ocenka[3][4] += Ocenka[3][i];

	double sum = 0;
	for (int i = 0; i < 4; i++) sum += Ocenka[i][4];

	for (int i = 0; i < 4; i++)
		Ocenka[i][5] = Ocenka[i][4] / sum;

	std::cout << "           |  Spain  | Turkey  |  Cuba   |Indonezia|   SUM   |  SUMn   |" << std::endl;
	for (int i = 0; i < 4; i++) {
		if (i == 0)
			std::cout << names[i] << "      ";
		if (i == 1)
			std::cout << names[i] << "     ";
		if (i == 2)
			std::cout << names[i] << "       ";
		if (i == 3)
			std::cout << names[i] << "  ";

		for (int j = 0; j < 6; j++) {
			std::cout << "|  ";
			printf("%.2f", Ocenka[i][j]);
			if (Ocenka[i][j] >= 10)
				std::cout << "  ";
			else std::cout << "   ";
		}
		std::cout << "|" << std::endl;
	}

	for (int i = 0; i < 4; i++) {
		Itog[i][1] = Ocenka[i][5];
	}
	}

	std::cout << std::endl;
	std::cout << "Otnoshenie soglasovannosti =" << OS(Ocenka);
	std::cout << std::endl << std::endl;

	//plyaszh
	std::cout << "Sea Shore" << std::endl;
	std::cout<<std::endl;

	{
		Ocenka[0][0] = 1;
		Ocenka[0][1] = 3;
		Ocenka[0][2] = 0.33;
		Ocenka[0][3] = 0.2;
		Ocenka[1][0] = 0.33;
		Ocenka[1][1] = 1;
		Ocenka[1][2] = 0.25;
		Ocenka[1][3] = 0.125;
		Ocenka[2][0] = 3;
		Ocenka[2][1] = 4;
		Ocenka[2][2] = 1;
		Ocenka[2][3] = 0.5;
		Ocenka[3][0] = 5;
		Ocenka[3][1] = 8;
		Ocenka[3][2] = 2;
		Ocenka[3][3] = 1;



		Ocenka[0][4] = 0;
		Ocenka[0][5] = 0;
		Ocenka[1][4] = 0;
		Ocenka[1][5] = 0;
		Ocenka[2][4] = 0;
		Ocenka[2][5] = 0;
		Ocenka[3][4] = 0;
		Ocenka[3][5] = 0;

		for (int i = 0; i < 4; i++) Ocenka[0][4] += Ocenka[0][i];
		for (int i = 0; i < 4; i++) Ocenka[1][4] += Ocenka[1][i];
		for (int i = 0; i < 4; i++) Ocenka[2][4] += Ocenka[2][i];
		for (int i = 0; i < 4; i++) Ocenka[3][4] += Ocenka[3][i];

		double sum = 0;
		for (int i = 0; i < 4; i++) sum += Ocenka[i][4];

		for (int i = 0; i < 4; i++)
			Ocenka[i][5] = Ocenka[i][4] / sum;

		std::cout << "           |  Spain  | Turkey  |  Cuba   |Indonezia|   SUM   |  SUMn   |" << std::endl;
		for (int i = 0; i < 4; i++) {
			if (i == 0)
				std::cout << names[i] << "      ";
			if (i == 1)
				std::cout << names[i] << "     ";
			if (i == 2)
				std::cout << names[i] << "       ";
			if (i == 3)
				std::cout << names[i] << "  ";

			for (int j = 0; j < 6; j++) {
				std::cout << "|  ";
				printf("%.2f", Ocenka[i][j]);
				if (Ocenka[i][j] >= 10)
					std::cout << "  ";
				else std::cout << "   ";
			}
			std::cout << "|" << std::endl;
		}
	}

	std::cout << std::endl;
	std::cout << "Otnoshenie soglasovannosti =" << OS(Ocenka);
	std::cout << std::endl << std::endl;

	//Attractions

	std::cout << "Attractions" << std::endl;

	{
		Ocenka[0][0] = 1;
		Ocenka[0][1] = 10;
		Ocenka[0][2] = 5;
		Ocenka[0][3] = 7;
		Ocenka[1][0] = 0.1;
		Ocenka[1][1] = 1;
		Ocenka[1][2] = 0.2;
		Ocenka[1][3] = 0.33;
		Ocenka[2][0] = 0.2;
		Ocenka[2][1] = 5;
		Ocenka[2][2] = 1;
		Ocenka[2][3] = 3;
		Ocenka[3][0] = 0.143;
		Ocenka[3][1] = 3;
		Ocenka[3][2] = 0.33;
		Ocenka[3][3] = 1;



		Ocenka[0][4] = 0;
		Ocenka[0][5] = 0;
		Ocenka[1][4] = 0;
		Ocenka[1][5] = 0;
		Ocenka[2][4] = 0;
		Ocenka[2][5] = 0;
		Ocenka[3][4] = 0;
		Ocenka[3][5] = 0;

		for (int i = 0; i < 4; i++) Ocenka[0][4] += Ocenka[0][i];
		for (int i = 0; i < 4; i++) Ocenka[1][4] += Ocenka[1][i];
		for (int i = 0; i < 4; i++) Ocenka[2][4] += Ocenka[2][i];
		for (int i = 0; i < 4; i++) Ocenka[3][4] += Ocenka[3][i];

		double sum = 0;
		for (int i = 0; i < 4; i++) sum += Ocenka[i][4];

		for (int i = 0; i < 4; i++)
			Ocenka[i][5] = Ocenka[i][4] / sum;

		std::cout << "           |  Spain  | Turkey  |  Cuba   |Indonezia|   SUM   |  SUMn   |"<<std::endl;
		for (int i = 0; i < 4; i++) {
			if (i == 0)
				std::cout << names[i] << "      ";
			if (i == 1)
				std::cout << names[i] << "     ";
			if (i == 2)
				std::cout << names[i] << "       ";
			if (i == 3)
				std::cout << names[i] << "  ";

			for (int j = 0; j < 6; j++) {
				std::cout <<"|  ";
				printf("%.2f", Ocenka[i][j]);
				if (Ocenka[i][j] >= 10)
					std::cout << "  ";
				else std::cout << "   ";
			}
			std::cout <<"|"<< std::endl;
		}

		for (int i = 0; i < 4; i++) {
			Itog[i][2] = Ocenka[i][5];
		}
	}

	std::cout << std::endl;
	std::cout << "Otnoshenie soglasovannosti =" << OS(Ocenka);
	std::cout << std::endl << std::endl;

	//kriterii

	std::cout << "kriterii" << std::endl;

	{
		Ocenka[0][0] = 1;
		Ocenka[0][1] = 3;
		Ocenka[0][2] = 0.25;
		Ocenka[0][3] = 0.16;
		Ocenka[1][0] = 0.33;
		Ocenka[1][1] = 1;
		Ocenka[1][2] = 0.143;
		Ocenka[1][3] = 0.1;
		Ocenka[2][0] = 4;
		Ocenka[2][1] = 7;
		Ocenka[2][2] = 1;
		Ocenka[2][3] = 0.5;
		Ocenka[3][0] = 6;
		Ocenka[3][1] = 10;
		Ocenka[3][2] = 2;
		Ocenka[3][3] = 1;



		Ocenka[0][4] = 0;
		Ocenka[0][5] = 0;
		Ocenka[1][4] = 0;
		Ocenka[1][5] = 0;
		Ocenka[2][4] = 0;
		Ocenka[2][5] = 0;
		Ocenka[3][4] = 0;
		Ocenka[3][5] = 0;

		for (int i = 0; i < 4; i++) Ocenka[0][4] += Ocenka[0][i];
		for (int i = 0; i < 4; i++) Ocenka[1][4] += Ocenka[1][i];
		for (int i = 0; i < 4; i++) Ocenka[2][4] += Ocenka[2][i];
		for (int i = 0; i < 4; i++) Ocenka[3][4] += Ocenka[3][i];

		double sum = 0;
		for (int i = 0; i < 4; i++) sum += Ocenka[i][4];

		for (int i = 0; i < 4; i++)
			Ocenka[i][5] = Ocenka[i][4] / sum;

		std::cout << "      |    1    |    2    |    3    |     4   |   SUM   |  SUMn   |" << std::endl;
		for (int i = 0; i < 4; i++) {
			std::cout << i + 1 << "     ";

			for (int j = 0; j < 6; j++) {
				std::cout << "|  ";
				printf("%.2f", Ocenka[i][j]);
				if (Ocenka[i][j] >= 10)
					std::cout << "  ";
				else std::cout << "   ";
			}
			std::cout << "|" << std::endl;
		}
		for (int i = 0; i < 4; i++) {
			Itog[i][3] = Ocenka[i][5];
		}
	}

	std::cout << std::endl;
	std::cout << "Otnoshenie soglasovannosti =" << OS(Ocenka);
	std::cout << std::endl << std::endl;


	std::cout << "matritsa SUMMn"<<std::endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << "|  ";
			printf("%.2f", Itog[i][j]);
			std::cout << "   ";
		}
		std::cout << "|" << std::endl;
	}

	std::cout <<std::endl<< "matritsa vesov" << std::endl;
	for (int i = 0; i < 4; i++) {
		std::cout << "|  ";
		printf("%.2f", Ocenka[i][5]);
		std::cout <<"  |"<< std::endl;
	}

	std::cout << std::endl << "Itog" << std::endl;
	double max=0;
	int maximum;
	for (int i = 0; i < 4; i++) {
		double sum = 0;
		for (int j = 0; j < 4; j++) {
			
			sum+=Itog[i][j] * Ocenka[j][5];
		}
		if (sum > max) {
			max = sum;
				maximum = i;
		}
		std::cout << sum << std::endl;
	}

	std::cout << std::endl << std::endl << "Optimalnyi variant - " << names[maximum] << std::endl << "------------------------------------";;
}


int main() {
	metod1();
	std::cout << std::endl;
	metod2();
	std::cout << std::endl;
	metod3();
	std::cout << std::endl;
	metod4();

	return 0;
}
