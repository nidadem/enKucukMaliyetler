#include<iostream>
#include<iomanip>
using namespace std;

class Dizi {
public:
	int* talep;
	int* geciciTalep;
	int* geciciArz;
	int* arz;
	int** dizi;
	int** geciciDizi;
	int enKucukEleman, enKucukSutun, enKucukSatir, z_toplam=0;
	bool degisim;


	void diziOlustur(int satir, int sutun) {
		dizi = new int* [satir];
		for (int i = 0; i < satir; i++) {
			dizi[i] = new int[sutun];
		}
		cout << "dizi elemanlarýný giriniz: " << endl;
		for (int i = 0; i < satir; i++) {
			for (int j = 0; j < sutun; j++) {
				cout << i + 1 << ". satýr " << j + 1 << ". sütun" << ". eleman: ";
				cin >> dizi[i][j];
			}
		}
	}
	void talepOlustur(int sutun) {
		talep = new int[sutun];
		for (int i = 0; i < sutun; i++) {
			cout << i + 1 << ". Sütun talebi: ";
			cin >> talep[i];
		}
	}
	void arzOlustur(int satir) {
		arz = new int[satir];
		for (int i = 0; i < satir; i++) {
			cout << i + 1 << ". Satýr arzý: ";
			cin >> arz[i];
		}
	}
	void diziYazdir(int satir, int sutun) {
		for (int i = 0; i < satir; i++) {
			for (int j = 0; j < sutun+1; j++) {
				if (i == 0 && j == sutun) {
					cout << setw((j+2)*5) << "ARZ" << endl;
				}
			}
		}
		for (int i = 0; i < satir; i++) {
			for (int j = 0; j < sutun; j++) {
				if (j == 0) {
					cout << setw(10) << dizi[i][j] << setw(5);
				}
				else {
					cout << setw(5) << dizi[i][j] << setw(5);
				}
			}
			cout << setw(5) << arz[i] << setw(5) << endl;
			if (i == satir - 1) {
				cout << "TALEP";
				for (int k = 0; k < sutun; k++) {
					cout << setw(5) << talep[k] << setw(5);
				}
			}
		}
		cout << endl << endl;
	}
	void enKucukElemanBul(int satir, int sutun) {
		for (int i = 0; i < satir; i++) {
			for (int j = 0; j < sutun; j++) {
				if (i == 0 && j == 0) {
					enKucukEleman = dizi[i][j];
				}
				if (enKucukEleman > dizi[i][j]) {
					enKucukEleman = dizi[i][j];
					enKucukSatir = i;
					enKucukSutun = j;
				}
			}
		}
	}
	void diziSutunSil(int satir, int sutun, int hangiSutun) {
		int** tmp = new int* [satir];

		for (int i = 0; i < satir; i++){
			tmp[i] = new int[sutun - 1];
		}

		for (int i = 0; i < satir; i++) {
			for (int j = 0, k = 0; j < sutun; j++){
				if (j != hangiSutun) tmp[i][k++] = dizi[i][j];
			}
		}

		for (int i = 0; i < satir; i++){
			delete[] dizi[i];
		}
		delete[] dizi;
		dizi = tmp;
	}
	void diziSatirSil(int satir, int sutun, int hangiSatir) {
		delete[] dizi[hangiSatir];

		int** tmp = new int* [satir - 1];
		int tmpI = 0;

		for (int i = 0; i < satir; i++)
			if (i != hangiSatir) {
				tmp[tmpI++] = dizi[i];
			}
		delete[] dizi;
		dizi = tmp;
	}

	void talepSil(int sutun, int hangiSutun) {
		geciciTalep = new int[sutun];
		for (int i = 0; i < sutun; i++) {
			if (i>=hangiSutun) {
				geciciTalep[i] = talep[i+1];
			}
			else {
				geciciTalep[i] = talep[i];
			}			
		}
		for (int i = 0; i < sutun; i++) {
			talep[i] = geciciTalep[i];
		}
		delete[]geciciTalep;
		geciciTalep = NULL;
	}
	void arzSil(int satir, int hangiSatir) {
		geciciArz = new int[satir];
		for (int i = 0; i < satir; i++) {
			if (i >= hangiSatir) {
				geciciArz[i] = arz[i + 1];
			}
			else {
				geciciArz[i] = arz[i];
			}
		}
		for (int i = 0; i < satir; i++) {
			arz[i] = geciciArz[i];
		}
		delete[]geciciArz;
		geciciArz = NULL;
	}
	void iterasyon(int satir, int sutun) {
		degisim = false;
		for (int i = 0; i < satir; i++) {
			for (int j = 0; j < sutun; j++) {
				if (i == enKucukSatir && j == enKucukSutun) {
					if (arz[i] > talep[j]) {						
						z_toplam = z_toplam + (talep[j] * dizi[i][j]);
						cout << "En küçük eleman = " << dizi[i][j] << endl;
						cout << setw(5) <<"iþlem= " << talep[j] << " x " << dizi[i][j] << "=" << talep[j] * dizi[i][j] << "\n" << "z_toplam= " << z_toplam << endl;
						arz[i] -= talep[j];
						talep[j] = 0;						
						diziSutunSil(satir, sutun, j);
						talepSil(sutun, j);
						degisim = true;
						
					}
					else if (arz[i] < talep[j]) {
						z_toplam = z_toplam + (arz[i] * dizi[i][j]);
						cout << "En küçük eleman = " << dizi[i][j] << endl;
						cout << setw(5) << "iþlem= " << talep[j] << " x " << dizi[i][j] << "=" << talep[j] * dizi[i][j] << "\n" << "z_toplam= " << z_toplam << endl;
						talep[j] -= arz[i];
						arz[i] = 0;						
						diziSatirSil(satir, sutun, i);
						arzSil(satir, i);
						degisim = false;
						
					}
					else { // arz = talep
						z_toplam = z_toplam + (talep[j] * dizi[i][j]);
						cout << "En küçük eleman = " << dizi[i][j] << endl;
						cout << setw(5) << "iþlem= " << talep[j] << " x " << dizi[i][j] << "=" << talep[j] * dizi[i][j] << "\n" << "z_toplam= " << z_toplam << endl;
						arz[i] = 0;
						talep[j] = 0;						
						diziSutunSil(satir, sutun, j);
						//diziSatirSil(satir, sutun, i);
						talepSil(sutun, j);
						degisim = true;
						
					}
				}
			}
		}
	}
	int talepToplam(int sutun) {
		int totaltalep = 0;
		for (int i = 0; i < sutun; i++) {
			totaltalep += talep[i];
		}
		return totaltalep;
	}
	int arzToplam(int satir) {
		int totalarz = 0;
		for (int i = 0; i < satir; i++) {
			totalarz += arz[i];
		}
		return totalarz;
	}
};
int main() {
	setlocale(LC_ALL, "turkish");
	int satirSayisi, sutunSayisi,satir,sutun;
	int toplamArz, toplamTalep;
	cout << "Dizinin satýr sayýsýný giriniz: ";
	cin >> satirSayisi;
	cout << "Dizinin satýr sayýsýný giriniz: ";
	cin >> sutunSayisi;
	Dizi dizim;
	dizim.diziOlustur(satirSayisi, sutunSayisi);
	dizim.arzOlustur(satirSayisi);
	dizim.talepOlustur(sutunSayisi);
	dizim.diziYazdir(satirSayisi, sutunSayisi);

	do {
		dizim.enKucukElemanBul(satirSayisi, sutunSayisi);
		dizim.iterasyon(satirSayisi, sutunSayisi);
		if (dizim.degisim == false) {
			satirSayisi--;
		}
		else {
			sutunSayisi--;
		}
		toplamArz = dizim.arzToplam(satirSayisi);
		toplamTalep = dizim.talepToplam(sutunSayisi);
		cout << "--------------------------" << endl << endl;
		dizim.diziYazdir(satirSayisi, sutunSayisi);
		

	} while (toplamArz != 0 || toplamTalep != 0);


	system("pause");
	return 0;
}
