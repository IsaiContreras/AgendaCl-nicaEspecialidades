#include <Windows.h>
#include <commctrl.h>
#include <fstream>
#include <string>
#include <time.h>
#include "resource.h"
#include "ListHeader.h"
#include "ListNodeHeader.h"
using namespace std;

#pragma region VARIABLES GLOBALES
fstream treeFile;
fstream countersFile;
int gUserID;
char username[40];
char globalDir[MAX_PATH];
int r = GetCurrentDirectory(MAX_PATH, globalDir);
char espFile[MAX_PATH] = "";
char* a = strcpy(espFile, globalDir);
char* b = strcat(espFile, "\\SavedData\\especialidades.dat");
char medFile[MAX_PATH] = "";
char* c = strcpy(medFile, globalDir);
char* d = strcat(medFile, "\\SavedData\\medicos.dat");
char pacFile[MAX_PATH] = "";
char* e = strcpy(pacFile, globalDir);
char* f = strcat(pacFile, "\\SavedData\\pacientes.dat");
char dateFile[MAX_PATH] = "";
char* g = strcpy(dateFile, globalDir);
char* h = strcat(dateFile, "\\SavedData\\citas.dat");
char counters[MAX_PATH] = "";
char* i = strcpy(counters, globalDir);
char* j = strcat(counters, "\\counters.dat");
char tempImage[MAX_PATH] = "";
bool exitAll;
int countP = 1;
int countD = 1;
time_t globalTime;
HINSTANCE hInstanciaGlobal;
HWND hLogin;
HWND hMenu;
HWND hAddMed;
HWND hAddPat;
HWND hNewDate;
HWND hPcFoto;
HWND hStUser;
HWND hLbDat;
HWND hLbPac;
HWND hLbEsp;
HWND hLbMedic;
HBITMAP hBmpFoto;
#pragma endregion

#pragma region WINDOW PROCEDURES PROTOTYPES
BOOL CALLBACK inicioSesion(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK menuPrincipal(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK agregarMedico(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK editarMedico(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK agregarPaciente(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK editarPaciente(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK agregarCita(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK editarCita(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK confirmarCita(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK consultaMedMes(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK consultaSem(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK consultaEspSem(HWND, UINT, WPARAM, LPARAM);
#pragma endregion

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int cShow) {
	hInstanciaGlobal = hInstance;
	hLogin = CreateDialog(hInstanciaGlobal, MAKEINTRESOURCE(IDD_LOGIN), NULL, inicioSesion);
	ShowWindow(hLogin, SW_SHOW);
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

#pragma region CLASES
struct USER {
	int id;
	char user[30];
	char pass[8];
	USER *next;
}*origin, *aux;

class Especialidad {
	int id;
	char name[30];
	char desc[MAX_PATH];
	int user;
public:
	Especialidad() {};
	void setID(int id) { this->id = id; }
	void setName(char* name) { strcpy(this->name, name); }
	void setDesc(char* desc) { strcpy(this->desc, desc); }
	void setUserID(int user) { this->user = user; }
	int getID() { return this->id; }
	char* getName() { return this->name; }
	char* getDesc() { return this->desc; }
	int getUserID() { return this->user; }
	char* print() {
		char buff[40];
		_itoa(id, buff, 10); strcat(buff, " | "); strcat(buff, name);
		return buff;
	}
	//OPERATORS OVERLOAD
	bool operator >(const Especialidad& esp) {

	}
	bool operator >=(const Especialidad& esp) {

	}
	bool operator <(const Especialidad& esp) {

	}
	bool operator <=(const Especialidad& esp) {

	}
	bool operator ==(const Especialidad& esp) {

	}
	bool operator ==(const int& ref) {
		if (this->id = ref)
			return true;
		else
			return false;
	}
	bool operator !=(const char*) {
		return false;
	}
	void operator =(Especialidad& esp) {
		this->setID(esp.id);
		this->setName(esp.name);
		this->setDesc(esp.desc);
		this->setUserID(esp.user);
	}
};
Node<Especialidad>* auxE;

class Paciente {
	char name[30];
	char lastNameP[30];
	char lastNameM[30];
	char compName[90];
	char contact[12];
	char med[90];
	char birthday[15];
	char genre;
	char reference[MAX_PATH];
	int id;
	int medId;
	int age;
	int user;
public:
	void setName(char* name) { strcpy(this->name, name); };
	void setLastNameP(char* lastP) { strcpy(this->lastNameP, lastP); }
	void setLastNameM(char* lastM) { strcpy(this->lastNameM, lastM); }
	void setCompName(char* compName) { strcpy(this->compName, compName); }
	void setContact(char* contact) { strcpy(this->contact, contact); }
	void setMed(char* med) { strcpy(this->med, med); }
	void setBirthDate(char* birthday) { strcpy(this->birthday, birthday); }
	void setGenre(char genre) { this->genre = genre; };
	void setRef(char* reference) { strcpy(this->reference, reference); }
	void setID(int id) { this->id = id; }
	void setMedID(int medId) { this->medId = medId; }
	void setAge(int age) { this->age = age; }
	void setUserID(int user) { this->user = user; }
	char* getName() { return this->name; };
	char* getLastNameP() { return this->lastNameP; }
	char* getLastNameM() { return this->lastNameM; }
	char* getCompName() { return this->compName; }
	char* getContact() { return this->contact; }
	char* getMed() { return this->med; }
	char* getBirthDate() { return this->birthday; }
	char getGenre() { return this->genre; }
	char* getRef() { return this->reference; }
	int getID() { return this->id; }
	int getMedID() { return this->medId; }
	int getAge() { return this->age; }
	int getUserID() { return this->user; }
	char* print() {
		char buff[70];
		_itoa(this->id, buff, 10); strcat(buff, " | "); strcat(buff, compName);
		return buff;
	}
	//Operators Overload
	bool operator >(const Paciente& pac) {
		char* l = this->lastNameP;
		const char* r = pac.lastNameP;
		while (*l != NULL && *r != NULL) {
			if (*l < *r)
				return false;
			else if (*l > *r)
				return true;
			else {
				l++;
				r++;
			}
			if (*l == NULL & *r == NULL)
				return false;
			else if (*l == NULL)
				return true;
			else if (*r == NULL)
				return false;
		}
	}
	bool operator >=(const Paciente& pac) {

	}
	bool operator <(const Paciente& pac) {
		char* l = this->lastNameP;
		const char* r = pac.lastNameP;
		while (*l != NULL && *r != NULL) {
			if (*l < *r)
				return true;
			else if (*l > *r)
				return false;
			else {
				l++;
				r++;
			}
			if (*l == NULL & *r == NULL)
				return false;
			else if (*l == NULL)
				return false;
			else if (*r == NULL)
				return true;
		}
	}
	bool operator <=(const Paciente& pac) {

	}
	bool operator ==(const Paciente& pac) {
		char* l = lastNameP;
		const char* r = pac.lastNameP;
		while (*l != NULL && *r != NULL) {
			if (*l < *r)
				return true;
			else if (*l > *r)
				return false;
			else {
				l++;
				r++;
			}
			if (*l == NULL & *r == NULL)
				return false;
			else if (*l == NULL)
				return false;
			else if (*r == NULL)
				return true;
		}
	}
	bool operator != (const char* comp) {
		char* p = this->compName;
		while (*comp != NULL) {
			if (*p + 32 == *comp | *p - 32 == *comp | *p == *comp) {
				p++;
				comp++;
			}
			else return true;
		}
		return false;
	}
	void operator =(Paciente pac) {
		this->setName(pac.name);
		this->setLastNameP(pac.lastNameP);
		this->setLastNameM(pac.lastNameM);
		this->setCompName(pac.compName);
		this->setContact(pac.contact);
		this->setMed(pac.med);
		this->setBirthDate(pac.birthday);
		this->setGenre(pac.genre);
		this->setRef(pac.reference);
		this->setID(pac.id);
		this->setMedID(pac.medId);
		this->setAge(pac.age);
		this->setUserID(pac.user);
	}
	friend ostream& operator <<(ostream &out, const Paciente& pac) {
		out << "ID: " << pac.id << " | Nom: " << pac.lastNameP << " " << pac.lastNameM << " " << pac.name << " | Gen: " << pac.genre << " | Ed: " << pac.age << " | F.Nac: " << pac.birthday << " | Tel: " << pac.contact << " | Med: " << pac.med << endl;
		return out;
	}
};
Node<Paciente>* auxP;

class Cita {
	int id;
	char pac[90];
	char med[90];
	char esp[30];
	char contact[12];
	char dirImage[MAX_PATH];
	char motive[MAX_PATH] = "";
	int pacId;
	int medId;
	int cons;
	int medsched;
	int espId;
	int time1 = -1;
	int time2 = -1;
	int state = 0;
	tm date;
	int user;
public:
	void setID(int id) { this->id = id; }
	void setPac(char* pac) { strcpy(this->pac, pac); }
	void setMed(char* med) { strcpy(this->med, med); }
	void setEsp(char* esp) { strcpy(this->esp, esp); }
	void setContact(char* contact) { strcpy(this->contact, contact); }
	void setDirImage(char* dirImage) { strcpy(this->dirImage, dirImage); }
	void setMotive(char* motive) { strcpy(this->motive, motive); }
	void setPacID(int pacId) { this->pacId = pacId; }
	void setMedID(int medId) { this->medId = medId; }
	void setCons(int noCons) { this->cons = noCons; }
	void setMedSch(int medsched) { this->medsched = medsched; }
	void setEspID(int espId) { this->espId = espId; }
	void setTime1(int time) { this->time1 = time; }
	void setTime2(int time) { this->time2 = time; }
	void setState(int state) { this->state = state; }
	void setDate(tm date) { this->date = date; }
	void setUserID(int user) { this->user = user; }
	int getID() { return this->id; }
	char* getPac() { return this->pac; }
	char* getMed() { return this->med; }
	char* getEsp() { return this->esp; }
	char* getContact() { return this->contact; }
	char* getDirImage() { return this->dirImage; }
	char* getMotive() { return this->motive; }
	int getPacID() { return this->pacId; }
	int getMedID() { return this->medId; }
	int getCons() { return this->cons; }
	int getMedSch() { return this->medsched; }
	int getEspID() { return this->espId; }
	int getTime1() { return this->time1; }
	int getTime2() { return this->time2; }
	int getState() { return this->state; }
	tm getDate() { return this->date; }
	int getUserID() { return this->user; }
	char* print() {
		char buff[70];
		char num[10];
		_itoa(this->id, buff, 10); strcat(buff, " | "); strcat(buff, this->pac); strcat(buff, " | ");
		_itoa(this->date.tm_mday, num, 10); strcat(buff, num); strcat(buff, "/");
		_itoa(this->date.tm_mon, num, 10); strcat(buff, num); strcat(buff, "/");
		_itoa(this->date.tm_year, num, 10); strcat(buff, num);
		return buff;
	}
	//OPERATORS OVERLOAD
	bool operator >(const Cita& dat) {
		if (this->cons > dat.cons) return true;
		else return false;
	}
	bool operator <(const Cita& dat) {
		if (this->cons < dat.cons) return true;
		else return false;
	}
	bool operator != (const char* comp) {
		return false;
	}
	bool operator !=(const Cita& dat) {
		if (this->id != dat.id)
			return true;
		else
			return false;
	}
	void operator =(Cita dat) {
		this->id = dat.id;
		strcpy(this->pac, dat.pac);
		strcpy(this->med, dat.med);
		strcpy(this->esp, dat.esp);
		strcpy(this->contact, dat.contact);
		strcpy(this->dirImage, dat.dirImage);
		strcpy(this->motive, dat.motive);
		this->pacId = dat.pacId;
		this->medId = dat.medId;
		this->cons = dat.cons;
		this->medsched = dat.medsched;
		this->espId = dat.espId;
		this->time1 = dat.time1;
		this->time2 = dat.time2;
		this->state = dat.state;
		this->date = dat.date;
		this->user = dat.user;
	}
	friend ostream& operator <<(ostream &out, const Cita& dat) {
		char time[60];
		if (dat.time1 != -1) {
			switch (dat.medsched) {
			case 0: {
				char times[15][25] = { "0 - 07:00 AM a 07:20 AM", "1 - 07:20 AM a 07:40 AM", "2 - 07:40 AM a 08:00 AM", "3 - 08:00 AM a 08:20 AM", "4 - 08:20 AM a 08:40 AM",
									   "5 - 08:40 AM a 09:00 AM", "6 - 09:00 AM a 09:20 AM", "7 - 09:20 AM a 09:40 AM", "8 - 09:40 AM a 10:00 AM", "9 - 10:00 AM a 10:20 AM",
									   "10 - 10:20 AM a 10:40 AM", "11 - 10:40 AM a 11:00 AM", "12 - 11:00 AM a 11:20 AM", "13 - 11:20 AM a 11:40 AM", "14 - 11:40 AM a 12:00 PM" };
				strcpy(time, times[dat.time1]);
				if (dat.time2 != -1) {
					strcat(time, " | H2: "); strcat(time, times[dat.time2]);
				}
			}
				break;
			case 1: {
				char times[15][25] = { "0 - 01:00 PM a 01:20 PM", "1 - 01:20 PM a 01:40 PM", "2 - 01:40 PM a 02:00 PM", "3 - 02:00 PM a 02:20 PM", "4 - 02:20 PM a 02:40 PM",
									   "5 - 02:40 PM a 03:00 PM", "6 - 03:00 PM a 03:20 PM", "7 - 03:20 PM a 03:40 PM", "8 - 03:40 PM a 04:00 PM", "9 - 04:00 PM a 04:20 PM",
									   "10 - 04:20 PM a 04:40 PM", "11 - 04:40 PM a 05:00 PM", "12 - 05:00 PM a 05:20 PM", "13 - 05:20 PM a 05:40 PM", "14 - 05:40 PM a 06:00 PM" };
				strcpy(time, times[dat.time1]);
				if (dat.time2 != -1) {
					strcat(time, " | H2: "); strcat(time, times[dat.time2]);
				}
			}
				break;
			case 2: {
				char times[15][25] = { "0 - 07:00 PM a 07:20 PM", "1 - 07:20 PM a 07:40 PM", "2 - 07:40 PM a 08:00 PM", "3 - 08:00 PM a 08:20 PM", "4 - 08:20 PM a 08:40 PM",
									   "5 - 08:40 PM a 09:00 PM", "6 - 09:00 PM a 09:20 PM", "7 - 09:20 PM a 09:40 PM", "8 - 09:40 PM a 10:00 PM", "9 - 10:00 PM a 10:20 PM",
									   "10 - 10:20 PM a 10:40 PM", "11 - 10:40 PM a 11:00 PM", "12 - 11:00 PM a 11:20 PM", "13 - 11:20 PM a 11:40 PM", "14 - 11:40 PM a 12:00 AM" };
				strcpy(time, times[dat.time1]);
				if (dat.time2 != -1) {
					strcat(time, " | H2: "); strcat(time, times[dat.time2]);
				}
			}
				break;
			}
		}
		out << "Cita: " << dat.id << " | Fech: " << dat.date.tm_mday << "/" << dat.date.tm_mon << "/" << dat.date.tm_year << " | H: " << time << " | Cons: " << dat.cons << " | Esp: " << dat.esp << " | Med: " << dat.med << " | Pac: " << dat.pac << " | Tel: " << dat.contact << endl;
		return out;
	}
};
Node<Cita>* auxD;

struct Medico {
	Medico *father;
	char name[30];
	char lastNameP[30];
	char lastNameM[30];
	char compName[90];
	char contact[12];
	char ateDay[6] = "";
	char esp[30];
	char dirImage[MAX_PATH] = "";
	int ced;
	int cons;
	int espId;
	int time;
	int user;
	Medico *left;
	Medico *right;
public:
	bool operator >(const Medico& med) {
		if (this->ced > med.ced)
			return true;
		else
			return false;
	}
	bool operator >=(const Medico& med) {
		if (this->ced >= med.ced)
			return true;
		else
			return false;
	}
	bool operator <(const Medico& med) {
		if (this->ced < med.ced)
			return true;
		else
			return false;
	}
	bool operator <=(const Medico& med) {
		if (this->ced <= med.ced)
			return true;
		else
			return false;
	}
	bool operator ==(const Medico& med) {
		if (this->ced == med.ced)
			return true;
		else
			return false;
	}
	bool operator !=(const Medico& med) {
		if (this->ced == med.ced)
			return false;
		else
			return true;
	}
	void operator =(const Medico& med) {
		strcpy(this->name, med.name);
		strcpy(this->lastNameP, med.lastNameP);
		strcpy(this->lastNameM, med.lastNameM);
		strcpy(this->compName, med.compName);
		strcpy(this->contact, med.contact);
		strcpy(this->ateDay, med.ateDay);
		strcpy(this->esp, med.esp);
		strcpy(this->dirImage, med.dirImage);
		this->ced = med.ced;
		this->cons = med.cons;
		this->espId = med.espId;
		this->time = med.time;
		this->user = med.user;
	}
	friend ostream& operator <<(ostream &out, const Medico& med) {
		char schedule[65];
		strcpy(schedule, "");
		for (int i = 0; i < 5; i++) {
			if (med.ateDay[i] == 'L')
				strcat(schedule, "Lunes ");
			if (med.ateDay[i] == 'M')
				strcat(schedule, "Martes ");
			if (med.ateDay[i] == 'N')
				strcat(schedule, "Miercoles ");
			if (med.ateDay[i] == 'J')
				strcat(schedule, "Jueves ");
			if (med.ateDay[i] == 'V')
				strcat(schedule, "Viernes ");
		}
		if(med.time == 0)
			strcat(schedule, "De 8:00 AM a 12:00 PM.");
		if (med.time == 1)
			strcat(schedule, "De 1:00 PM a 6:00 PM.");
		if (med.time == 2)
			strcat(schedule, "De 7:00 PM a 11:00 PM.");
		out << "Ced: " << med.ced << " | Nom: " << med.compName << " | Esp: " << med.esp << " | Cons: " << med.cons << " | Tel: " << med.contact << " | Hor: " << schedule <<" | Registrer: " << med.user << endl;
		return out;
	}
}*auxM = NULL, auxMC;

class TreeList {
	Medico *root;
	char *file;
public:
	TreeList(char *file) {
		this->file = file;
		Medico aux;
		treeFile.open(this->file, ios::in | ios::binary | ios::ate);
		if (treeFile.is_open()) {
			int size = treeFile.tellg();
			treeFile.seekg(0, ios::beg);
			if (size > 0) {
				treeFile.read((char*)&aux, sizeof(Medico));
				while (!treeFile.eof()) {
					AddNode(aux);
					treeFile.read((char*)&aux, sizeof(Medico));
				}
			}
		}
		treeFile.close();
	}
	void CopyNode(Medico *node, Medico data) {
		strcpy(node->name, data.name);
		strcpy(node->lastNameP, data.lastNameP);
		strcpy(node->lastNameM, data.lastNameM);
		strcpy(node->compName, data.compName);
		strcpy(node->contact, data.contact);
		strcpy(node->ateDay, data.ateDay);
		strcpy(node->esp, data.esp);
		strcpy(node->dirImage, data.dirImage);
		node->ced = data.ced;
		node->cons = data.cons;
		node->espId = data.espId;
		node->time = data.time;
		node->user = data.user;
		node->left = NULL;
		node->right = NULL;
	}
	void CopyNodeNS(Medico *node, Medico data) {
		strcpy(node->name, data.name);
		strcpy(node->lastNameP, data.lastNameP);
		strcpy(node->lastNameM, data.lastNameM);
		strcpy(node->compName, data.compName);
		strcpy(node->contact, data.contact);
		strcpy(node->ateDay, data.ateDay);
		strcpy(node->esp, data.esp);
		strcpy(node->dirImage, data.dirImage);
		node->ced = data.ced;
		node->cons = data.cons;
		node->espId = data.espId;
		node->time = data.time;
		node->user = data.user;
	}
	void Add(Medico **node, Medico *nuevo, Medico *prev) {
		Medico *aux = *node;
		if (aux == NULL) {
			nuevo->father = prev;
			*node = nuevo;
		}
		else {
			if (nuevo->ced > aux->ced)
				Add(&(aux->right), nuevo, aux);
			if (nuevo->ced < aux->ced)
				Add(&(aux->left), nuevo, aux);
		}
	}
	void AddNode(Medico data) {
		Medico **node = &root;
		Medico *nuevo = new Medico;
		CopyNode(nuevo, data);
		if (*node == NULL) {
			nuevo->father = NULL;
			nuevo->left = NULL;
			nuevo->right = NULL;
			*node = nuevo;
		}
		else
			Add(node, nuevo, NULL);
	}
	Medico *MostLeft(Medico *tree) {
		if (tree == NULL)
			return NULL;
		if (tree->left)
			return MostLeft(tree->left);
		else
			return tree;
	}
	void Replace(Medico *tree, Medico *nuevo) {
		if (tree->father) {
			if (tree->father->left != NULL) {
				if (tree->ced == tree->father->left->ced)
					tree->father->left = nuevo;
			}
			if (tree->father->right != NULL) {
				if (tree->ced == tree->father->right->ced)
					tree->father->right = nuevo;
			}
		}
		else
			root = nuevo;
		if (nuevo)
			nuevo->father = tree->father;
	}
	void DeleteNode(Medico *node) {
		if (node->left != NULL & node->right != NULL) {
			Medico *min = MostLeft(node->right);
			CopyNodeNS(node, *min);
			DeleteNode(min);
		}
		else if (node->left != NULL) {
			Replace(node, node->left);
			delete node;
		}
		else if (node->right != NULL) {
			Replace(node, node->right);
			delete node;
		}
		else {
			Replace(node, NULL);
			delete node;
		}
	}
	void DeleteAllNodes(Medico* node) {
		if (node != NULL) {
			DeleteAllNodes(node->left);
			DeleteAllNodes(node->right);
			delete node;
		}
	}
	Medico *Search(Medico *node, int ref, int change, int type) {
		switch (type) {
		case 0:
			if (node != NULL) {
				if (node->ced == ref)
					return node;
				else {
					if (ref > node->ced)
						return Search(node->right, ref, 0, 0);
					if (ref < node->ced)
						return Search(node->left, ref, 0, 0);
				}
			}
			else
				return NULL;
			break;
		case 1:
			if (node != NULL) {
				Search(node->left, ref, change, 1);
				if (node->espId == ref)
					node->espId = change;
				Search(node->right, ref, change, 1);
			}
			return NULL;
			break;
		}
	}
	void countList(int &count, Medico *tree) {
		if (tree != NULL) {
			countList(count, tree->left);
			count++;
			countList(count, tree->right);
		}
	}
	void printInOrderLb(HWND hWindow, Medico *node) {
		if (node != NULL) {
			printInOrderLb(hWindow, node->left);
			char buff[80];
			_itoa(node->ced, buff, 10);
			strcat(buff, " | "); strcat(buff, node->compName);
			SendMessage(hWindow, LB_ADDSTRING, 0, (LPARAM)buff);
			printInOrderLb(hWindow, node->right);
		}
	}
	void printInOrderCb(HWND hWindow, Medico *node) {
		if (node != NULL) {
			printInOrderCb(hWindow, node->left);
			char buff[80];
			_itoa(node->ced, buff, 10);
			strcat(buff, " | "); strcat(buff, node->compName);
			SendMessage(hWindow, CB_ADDSTRING, 0, (LPARAM)buff);
			printInOrderCb(hWindow, node->right);
		}
	}
	void printInOrderCbEsp(HWND hWindow, Medico *node, int ref) {
		if (node != NULL) {
			printInOrderCbEsp(hWindow, node->left, ref);
			if (node->espId == ref) {
				char buff[80];
				_itoa(node->ced, buff, 10);
				strcat(buff, " | "); strcat(buff, node->compName);
				SendMessage(hWindow, CB_ADDSTRING, 0, (LPARAM)buff);
			}
			printInOrderCbEsp(hWindow, node->right, ref);
		}
	}
	void printInOrderFile(Medico *node) {
		if (node != NULL) {
			treeFile.write((char*)node, sizeof(Medico));
			printInOrderFile(node->left);
			printInOrderFile(node->right);
		}
	}
	Medico *getRoot() {
		return this->root;
	}
	~TreeList() {
		treeFile.open(this->file, ios::out | ios::binary | ios::trunc);
		if (treeFile.is_open()) {
			printInOrderFile(root);
		}
		treeFile.close();
		DeleteAllNodes(root);
	}
};
#pragma endregion

#pragma region LISTAS
LinkedList<Especialidad> listaEspecialidades(espFile);
TreeList listaMedicos(medFile);
LinkedList<Paciente> listaPacientes(pacFile);
LinkedList<Cita> listaCitas(dateFile);
#pragma endregion

#pragma region FUNCIONES
void writeCounters() {
	countersFile.open(counters, ios::out);
	if (countersFile.is_open()) {
		countersFile.write((char*)&countP, sizeof(int));
		countersFile.write((char*)&countD, sizeof(int));
	}
	countersFile.close();
}
void readCounters() {
	countersFile.open(counters, ios::in | ios::binary | ios::ate);
	if (countersFile.is_open()) {
		int size = countersFile.tellg();
		countersFile.seekg(0, ios::beg);
		if (size > 0) {
			countersFile.read((char*)&countP, sizeof(int));
			countersFile.read((char*)&countD, sizeof(int));
		}
	}
	countersFile.close();
}
bool validAlpha(char* s) {
	while (*s != 0) {
		if ((*s < 65 | *s > 90 & *s < 97 | *s > 122) & *s != 32)
			return false;
		s++;
	}
	return true;
}
int week_number(const std::tm& tm) {
	constexpr int DAYS_PER_WEEK = 7;
	const int wday = tm.tm_wday;
	const int delta = wday ? wday - 1 : DAYS_PER_WEEK - 1;
	return (tm.tm_yday + DAYS_PER_WEEK - delta) / DAYS_PER_WEEK;
}
bool is_UsingEsp(Medico *node, int ref) {
	if (node != NULL) {
		if (node->espId == ref)
			return true;
		if (is_UsingEsp(node->left, ref))
			return true;
		if (is_UsingEsp(node->right, ref))
			return true;
	}
	return false;
}
bool is_SameSched(Medico *node, Medico ref) {
	if (node != NULL) {
		if (*node != ref) {
			if (node->espId == ref.espId) {
				if (node->cons == ref.cons) {
					char *sched1 = node->ateDay;
					char *sched2 = ref.ateDay;
					while (*sched1 != '\0') {
						int c = 0;
						while (*sched2 != '\0') {
							if (*sched2 == *sched1) {
								if (node->time == ref.time)
									return true;
							}
							sched2++;
							c++;
						}
						sched2 -= c;
						sched1++;
					}
				}
			}
		}
		if (is_SameSched(node->left, ref))
			return true;
		if (is_SameSched(node->right, ref))
			return true;
	}
	return false;
}
bool is_SameCed(Medico *node, int ref) {
	if (node != NULL) {
		if (node->ced == ref)
			return true;
		if (is_SameCed(node->left, ref))
			return true;
		if (is_SameCed(node->right, ref))
			return true;
	}
	return false;
}
bool is_PendingDateMedic(int ref) {
	Node<Cita>* aux = listaCitas.getFirst();
	while (aux != NULL) {
		if (aux->getData().getMedID() == ref & aux->getData().getState() == 0)
			return true;
		aux = aux->getNext();
	}
	return false;
}
bool is_dateOnThisTime(int t, int medID, tm tmDate) {
	Node<Cita> *aux = listaCitas.getFirst();
	while (aux != NULL) {
		Cita temp = aux->getData();
		if (temp.getMedID() == medID & temp.getDate().tm_year == tmDate.tm_year & temp.getDate().tm_mon == tmDate.tm_mon & temp.getDate().tm_mday == tmDate.tm_mday) {
			if (temp.getTime1() == t) return true;
			else if (temp.getTime2() == t) return true;
		}
		aux = aux->getNext();
	}
	return false;
}
bool is_SameDateTime(Cita currDate) {
	Node<Cita>* aux = listaCitas.getFirst();
	while (aux != NULL) {
		Cita dt = aux->getData();
		if (dt != currDate) {
			if (dt.getTime1() == currDate.getTime1() & dt.getMedID() == currDate.getMedID() & dt.getDate().tm_year == currDate.getDate().tm_year & dt.getDate().tm_mon == currDate.getDate().tm_mon & dt.getDate().tm_mday == currDate.getDate().tm_mday)
				return true;
		}
		aux = aux->getNext();
	}
	return false;
}
bool is_PassedDate(tm dt, tm actual) {
	if (dt.tm_year < actual.tm_year)
		return true;
	else if (dt.tm_year == actual.tm_year & dt.tm_mon < actual.tm_mon)
		return true;
	else if (dt.tm_year == actual.tm_year & dt.tm_mon == actual.tm_mon & dt.tm_mday < actual.tm_mday)
		return true;
	else
		return false;
}
int binarySearchMed(Medico arr[], int l, int r, int x) {
	if (r >= l) {
		int mid = l + (r - l) / 2;
		if (arr[mid].ced == x) return mid;
		if (arr[mid].ced > x) return binarySearchMed(arr, l, mid - 1, x);
		return binarySearchMed(arr, mid + 1, r, x);
	}
	return -1;
}
void buildMedicArray(Medico arr[], int& i, Medico* node) {
	if (node != NULL) {
		buildMedicArray(arr, i, node->left);
		arr[i] = *node;
		i++;
		buildMedicArray(arr, i, node->right);
	}
}
void printTimes(HWND hCalendar, HWND hCb, Medico *med, int time1, int time2) {
	SendMessage(hCb, CB_RESETCONTENT, 0, 0);
	SYSTEMTIME dateSelect;
	SendMessage(hCalendar, MCM_GETCURSEL, 0, (LPARAM)&dateSelect);
	time_t rawTime;
	tm tmDate;
	time(&rawTime);
	tmDate = *localtime(&rawTime);
	tmDate.tm_year = dateSelect.wYear - 1900;
	tmDate.tm_mon = dateSelect.wMonth - 1;
	tmDate.tm_mday = dateSelect.wDay;
	mktime(&tmDate);
	tmDate.tm_year += 1900;
	tmDate.tm_mon += 1;
	char wDay;
	switch (dateSelect.wDayOfWeek) {
	case 1:
		wDay = 'L';
		break;
	case 2:
		wDay = 'M';
		break;
	case 3:
		wDay = 'N';
		break;
	case 4:
		wDay = 'J';
		break;
	case 5:
		wDay = 'V';
		break;
	default:
		return;
	}
	for (int i = 0; i < 5; i++) {
		if (wDay == med->ateDay[i]) {
			switch (med->time) {
			case 0: {
				char times[15][25] = { "0 | 07:00 AM a 07:20 AM", "1 | 07:20 AM a 07:40 AM", "2 | 07:40 AM a 08:00 AM", "3 | 08:00 AM a 08:20 AM", "4 | 08:20 AM a 08:40 AM",
									   "5 | 08:40 AM a 09:00 AM", "6 | 09:00 AM a 09:20 AM", "7 | 09:20 AM a 09:40 AM", "8 | 09:40 AM a 10:00 AM", "9 | 10:00 AM a 10:20 AM",
									   "10 | 10:20 AM a 10:40 AM", "11 | 10:40 AM a 11:00 AM", "12 | 11:00 AM a 11:20 AM", "13 | 11:20 AM a 11:40 AM", "14 | 11:40 AM a 12:00 PM" };
				for (int i = 0; i < 15; i++) {
					if (i == time1)
						SendMessage(hCb, CB_ADDSTRING, 0, (LPARAM)times[i]);
					if (i == time2)
						SendMessage(hCb, CB_ADDSTRING, 0, (LPARAM)times[i]);
					if (!is_dateOnThisTime(i, med->ced, tmDate))
						SendMessage(hCb, CB_ADDSTRING, 0, (LPARAM)times[i]);
				}
			}
					break;
			case 1: {
				char times[15][25] = { "0 | 01:00 PM a 01:20 PM", "1 | 01:20 PM a 01:40 PM", "2 | 01:40 PM a 02:00 PM", "3 | 02:00 PM a 02:20 PM", "4 | 02:20 PM a 02:40 PM",
									   "5 | 02:40 PM a 03:00 PM", "6 | 03:00 PM a 03:20 PM", "7 | 03:20 PM a 03:40 PM", "8 | 03:40 PM a 04:00 PM", "9 | 04:00 PM a 04:20 PM",
									   "10 | 04:20 PM a 04:40 PM", "11 | 04:40 PM a 05:00 PM", "12 | 05:00 PM a 05:20 PM", "13 | 05:20 PM a 05:40 PM", "14 | 05:40 PM a 06:00 PM" };
				for (int i = 0; i < 15; i++) {
					if (i == time1)
						SendMessage(hCb, CB_ADDSTRING, 0, (LPARAM)times[i]);
					if (i == time2)
						SendMessage(hCb, CB_ADDSTRING, 0, (LPARAM)times[i]);
					if (!is_dateOnThisTime(i, med->ced, tmDate))
						SendMessage(hCb, CB_ADDSTRING, 0, (LPARAM)times[i]);
				}
			}
					break;
			case 2: {
				char times[15][25] = { "0 | 07:00 PM a 07:20 PM", "1 | 07:20 PM a 07:40 PM", "2 | 07:40 PM a 08:00 PM", "3 | 08:00 PM a 08:20 PM", "4 | 08:20 PM a 08:40 PM",
									   "5 | 08:40 PM a 09:00 PM", "6 | 09:00 PM a 09:20 PM", "7 | 09:20 PM a 09:40 PM", "8 | 09:40 PM a 10:00 PM", "9 | 10:00 PM a 10:20 PM",
									   "10 | 10:20 PM a 10:40 PM", "11 | 10:40 PM a 11:00 PM", "12 | 11:00 PM a 11:20 PM", "13 | 11:20 PM a 11:40 PM", "14 | 11:40 PM a 12:00 AM" };
				for (int i = 0; i < 15; i++) {
					if (i == time1)
						SendMessage(hCb, CB_ADDSTRING, 0, (LPARAM)times[i]);
					if (i == time2)
						SendMessage(hCb, CB_ADDSTRING, 0, (LPARAM)times[i]);
					if (!is_dateOnThisTime(i, med->ced, tmDate))
						SendMessage(hCb, CB_ADDSTRING, 0, (LPARAM)times[i]);
				}
			}
					break;
			}
			break;
		}
	}
}
template <typename T> void Swap(T &data01, T &data02) {
	T temp = data02;
	data02 = data01;
	data01 = temp;
}
//DATES ON QUICK SORT
int countDates(int week) {
	int r = 0;
	Node<Cita>* aux = listaCitas.getFirst();
	while (aux != NULL) {
		Cita comp = aux->getData();
		if (week_number(comp.getDate()) == week & comp.getState() == 0)
			r++;
		aux = aux->getNext();
	}
	return r;
}
void buildDatesArray(Cita arr[], int week) {
	Node<Cita>* aux = listaCitas.getFirst();
	int i = 0;
	while (aux != NULL) {
		Cita comp = aux->getData();
		if (week_number(comp.getDate()) == week & comp.getState() == 0) {
			arr[i] = comp;
			i++;
		}
		aux = aux->getNext();
	}
}
void QuickSortD(Cita arr[], int left, int right) {
	int i = left, j = right;
	Cita pivot = arr[(left + right) / 2];
	//partition
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			Swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}
	//recursion
	if (left < j)
		QuickSortD(arr, left, j);
	if (i < right)
		QuickSortD(arr, i, right);
}
//GENERATE MEDIC REPORT
void BuildHeap(Medico arr[], int& n, Medico *tree) {
	if (tree != NULL) {
		arr[n] = *tree;
		n++;
		BuildHeap(arr, n, tree->left);
		BuildHeap(arr, n, tree->right);
	}
	
}
void heapify(Medico arr[], int n, int i) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && arr[l] < arr[largest])
		largest = l;
	if (r < n && arr[l] < arr[largest])
		largest = r;
	if (largest != i) {
		Swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}
void HeapSort(char* file, int n) {
	Medico *arr = new Medico[n];
	int i = 0;
	BuildHeap(arr, i, listaMedicos.getRoot());
	for (i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);
	ofstream report;
	report.open(file, ios::out);
	if (report.is_open()) {
		for (int i = n - 1; i >= 0; i--) {
			report << arr[0];
			Swap(arr[0], arr[i]);
			heapify(arr, i, 0);
		}
	}
	report.close();
}
void generateMedicReport() {
	int n = 0; listaMedicos.countList(n, listaMedicos.getRoot());
	if (n == 0) {
		MessageBox(NULL, "No se puede generar reporte porque la lista de médicos está vacía.", "Lista Vacía", MB_ICONINFORMATION);
		return;
	}
	char buff[MAX_PATH] = "";
	OPENFILENAME ofnFile;
	ZeroMemory(&ofnFile, sizeof(ofnFile));
	ofnFile.hwndOwner = hMenu;
	ofnFile.lStructSize = sizeof(ofnFile);
	ofnFile.lpstrFile = buff;
	ofnFile.nMaxFile = MAX_PATH;
	ofnFile.lpstrDefExt = "txt";
	ofnFile.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
	ofnFile.lpstrFilter = "Text File\0*.txt\0";
	if (GetSaveFileName(&ofnFile)) {
		HeapSort(buff, n);
	}
}
//GENERATE PATIENT REPORT
void BuildArray(Paciente arr[], int n) {
	Node<Paciente>* aux = listaPacientes.getFirst();
	for (int i = 0; i < n; i++) {
		arr[i] = aux->getData();
		aux = aux->getNext();
	}
}
void QuickSort(Paciente arr[], int left, int right) {
	int i = left, j = right;
	Paciente pivot = arr[(left + right) / 2];
	//partition
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			Swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}
	//recursion
	if (left < j)
		QuickSort(arr, left, j);
	if (i < right)
		QuickSort(arr, i, right);
}
void generatePatientReport() {
	int n = listaPacientes.CountList();
	if (n == 0) {
		MessageBox(NULL, "No se puede generar reporte porque la lista de pacientes está vacía", "Lista Vacía", MB_ICONINFORMATION);
		return;
	}
	char buff[MAX_PATH] = "";
	OPENFILENAME ofnFile;
	ZeroMemory(&ofnFile, sizeof(ofnFile));
	ofnFile.hwndOwner = hMenu;
	ofnFile.lStructSize = sizeof(ofnFile);
	ofnFile.lpstrFile = buff;
	ofnFile.nMaxFile = MAX_PATH;
	ofnFile.lpstrDefExt = "txt";
	ofnFile.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
	ofnFile.lpstrFilter = "Text File\0*.txt\0";
	if (GetSaveFileName(&ofnFile)) {
		Paciente *arr = new Paciente[n];
		BuildArray(arr, n);
		QuickSort(arr, 0, n - 1);
		ofstream report;
		report.open(buff, ios::out);
		if (report.is_open()) {
			for (int j = 0; j < n; j++) {
				report << arr[j];
			}
		}
		report.close();
	}
}
#pragma endregion

#pragma region WINDOW PROCEDURES
BOOL CALLBACK inicioSesion(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HWND hCbUser = GetDlgItem(hwnd, CB_USER);
	switch (msg) {
	case WM_INITDIALOG:{
		origin = aux = NULL;
		ifstream login;
		char userDir[MAX_PATH] = "";
		strcpy(userDir, globalDir); strcat(userDir, "\\users.txt");
		login.open(userDir, ios::in);
		if (login.is_open()) {
			while (!login.eof()) {
				string buff;
				if (origin == NULL) {
					origin = new USER;
					getline(login, buff);
					origin->id = atoi(buff.c_str());
					getline(login, buff);
					strcpy(origin->user, buff.c_str());
					getline(login, buff);
					strcpy(origin->pass, buff.c_str());
					origin->next = NULL;
					aux = origin;
				}
				else {
					aux->next = new USER;
					aux = aux->next;
					getline(login, buff);
					aux->id = atoi(buff.c_str());
					getline(login, buff);
					strcpy(aux->user, buff.c_str());
					getline(login, buff);
					strcpy(aux->pass, buff.c_str());
					aux->next = NULL;
				}
				char buffC[40];
				_itoa(aux->id, buffC, 10); strcat(buffC, " | "); strcat(buffC, aux->user);
				SendMessage(hCbUser, CB_ADDSTRING, 0, (LPARAM)buffC);
			}
			aux = NULL;
			login.close();
		}
		else {
			MessageBox(hwnd, "Error al leer el archivo de usuarios.", "ERROR", MB_ICONERROR);
		}
	}
	break;
	case WM_COMMAND:{
		char buff[30];
		if (LOWORD(wParam) == CB_USER && HIWORD(wParam) == CBN_SELCHANGE) {
			aux = origin;
			int index = SendMessage(hCbUser, CB_GETCURSEL, 0, 0);
			if (index > -1) {
				for (int i = 0; i < index; i++)
					aux = aux->next;
			}
		}
		if (LOWORD(wParam) == IDOK && HIWORD(wParam) == BN_CLICKED) {
			if (aux != NULL) {
				HWND hEdtPassword = GetDlgItem(hwnd, EDT_PASS);
				GetWindowText(hEdtPassword, buff, 9);
				string compare(buff);
				string password(aux->pass);
				if (password.compare(compare) == 0) {
					gUserID = aux->id;
					strcpy(username, aux->user);
					hMenu = CreateDialog(hInstanciaGlobal, MAKEINTRESOURCE(IDD_MENU), NULL, menuPrincipal);
					ShowWindow(hMenu, SW_SHOW);
					DestroyWindow(hwnd);
				}
				else {
					MessageBox(hwnd, "Contraseña incorrecta.", "AVISO", MB_ICONEXCLAMATION);
				}
			}
			else
				MessageBox(hwnd, "Escoja un usuario para iniciar sesión.", "AVISO", MB_ICONINFORMATION);
		}
	}
	break;
	case WM_CLOSE:
		exitAll = true;
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		while (origin != NULL) {
			aux = origin;
			origin = aux->next;
			delete aux;
		}
		if (exitAll)
			PostQuitMessage(0);
		break;
	}
	return FALSE;
}

BOOL CALLBACK menuPrincipal(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	//MEDIC WINDOWS
	HWND hStMedName = GetDlgItem(hwnd, ST_MED_NAME);
	HWND hStMedCed = GetDlgItem(hwnd, ST_MED_CED);
	HWND hStMedEsp = GetDlgItem(hwnd, ST_MED_ESP);
	HWND hStMedCons = GetDlgItem(hwnd, ST_MED_NOCONS);
	HWND hStMedContact = GetDlgItem(hwnd, ST_MED_PHONE);
	HWND hStMedHora = GetDlgItem(hwnd, EDT_MED_ATTIME);
	HWND hBtnMedMod = GetDlgItem(hwnd, BTN_MED_MODIFY);
	HWND hBtnMedDel = GetDlgItem(hwnd, BTN_MED_DELETE);
	//ESPEC WINDOWS
	HWND hEdtEspName = GetDlgItem(hwnd, EDT_ESP_NAME);
	HWND hEdtEspKey = GetDlgItem(hwnd, EDT_ESP_KEY);
	HWND hEdtEspDesc = GetDlgItem(hwnd, EDT_ESP_DESC);
	HWND hBtnEspMod = GetDlgItem(hwnd, BTN_ESP_MODIFY);
	HWND hBtnEspDel = GetDlgItem(hwnd, BTN_ESP_DELETE);
	//PATIENT WINDOWS
	HWND hStPacName = GetDlgItem(hwnd, ST_PAC_NAME);
	HWND hStPacAge = GetDlgItem(hwnd, ST_PAC_AGE);
	HWND hStPacGenre = GetDlgItem(hwnd, ST_PAC_GENRE);
	HWND hStPacContact = GetDlgItem(hwnd, ST_PAC_PHONE);
	HWND hStPacBirthday = GetDlgItem(hwnd, ST_PAC_BIRTHDATE);
	HWND hStPacFirstMed = GetDlgItem(hwnd, ST_PAC_FIRSTMED);
	HWND hStPacRef = GetDlgItem(hwnd, EDT_PAC_REFER);
	HWND hBtnPacMod = GetDlgItem(hwnd, BTN_PAC_MODIFY);
	HWND hBtnPacDel = GetDlgItem(hwnd, BTN_PAC_DELETE);
	//DATE WINDOWS
	HWND hStDtNoDate = GetDlgItem(hwnd, ST_DT_NODATE);
	HWND hStDtDate = GetDlgItem(hwnd, ST_DT_DATETIME);
	HWND hStDtTime = GetDlgItem(hwnd, ST_DT_TIME);
	HWND hStDtMed = GetDlgItem(hwnd, ST_DT_MEDNAME);
	HWND hStDtEsp = GetDlgItem(hwnd, ST_DT_ESP);
	HWND hStDtCons = GetDlgItem(hwnd, ST_DT_NOCONS);
	HWND hStDtPac = GetDlgItem(hwnd, ST_DT_PACNAME);
	HWND hStDtState = GetDlgItem(hwnd, ST_DT_STATE);
	HWND hStDtMot = GetDlgItem(hwnd, ST_DT_MOTIVE);
	HWND hBtnDtMod = GetDlgItem(hwnd, BTN_DT_MODIFY);
	HWND hBtnDtDel = GetDlgItem(hwnd, BTN_DT_DELETE);
	switch (msg) {
	case WM_INITDIALOG:{
		//SetMedicWindows
		EnableWindow(hBtnMedMod, false);
		EnableWindow(hBtnMedDel, false);
		//SetEspButtons
		EnableWindow(hBtnEspMod, false);
		EnableWindow(hBtnEspDel, false);
		//SetPacButtons
		EnableWindow(hBtnPacMod, false);
		EnableWindow(hBtnPacDel, false);
		//SetDtButtons
		EnableWindow(hBtnDtMod, false);
		EnableWindow(hBtnDtDel, false);
		//SetUsername
		hStUser = GetDlgItem(hwnd, ST_USERNAME);
		SetWindowText(hStUser, username);
		//PrintListBox
		hLbMedic = GetDlgItem(hwnd, LB_MED);
		hLbEsp = GetDlgItem(hwnd, LB_ESP);
		hLbPac = GetDlgItem(hwnd, LB_PAC);
		hLbDat = GetDlgItem(hwnd, LB_DT);
		listaMedicos.printInOrderLb(hLbMedic, listaMedicos.getRoot());
		listaEspecialidades.PrintOnWindow(hLbEsp, 0, NULL);
		listaPacientes.PrintOnWindow(hLbPac, 0, NULL);
		listaCitas.PrintOnWindow(hLbDat, 0, NULL);
		//ReadCounters
		readCounters();
	}
	break;
	case WM_COMMAND:
		//GestiónCitas
		if (LOWORD(wParam) == LB_DT && HIWORD(wParam) == LBN_SELCHANGE) {
			//GetNode
			int index = SendMessage(hLbDat, LB_GETCURSEL, 0, 0);
			char buff[80];
			SendMessage(hLbDat, LB_GETTEXT, index, (LPARAM)buff);
			index = atoi(buff);
			auxD = listaCitas.SearchNode(index);
			Cita date = auxD->getData();
			//SetStatics
			_itoa(date.getID(), buff, 10);
			SetWindowText(hStDtNoDate, buff);
			_itoa(date.getDate().tm_mday, buff, 10); strcat(buff, " de ");
			switch (date.getDate().tm_mon) {
			case 1:
				strcat(buff, "Enero del ");
				break;
			case 2:
				strcat(buff, "Febrero del ");
				break;
			case 3:
				strcat(buff, "Marzo del ");
				break;
			case 4:
				strcat(buff, "Abril del ");
				break;
			case 5:
				strcat(buff, "Mayo del ");
				break;
			case 6:
				strcat(buff, "Junio del ");
				break;
			case 7:
				strcat(buff, "Julio del ");
				break;
			case 8:
				strcat(buff, "Agosto del ");
				break;
			case 9:
				strcat(buff, "Septiembre del ");
				break;
			case 10:
				strcat(buff, "Octubre del ");
				break;
			case 11:
				strcat(buff, "Noviembre del ");
				break;
			case 12:
				strcat(buff, "Diciembre del ");
				break;
			}
			char num[5];
			_itoa(date.getDate().tm_year, num, 10); strcat(buff, num);
			SetWindowText(hStDtDate, buff);
			switch (date.getMedSch()) {
			case 0: {
				char times[15][25] = { "0 | 07:00 AM a 07:20 AM", "1 | 07:20 AM a 07:40 AM", "2 | 07:40 AM a 08:00 AM", "3 | 08:00 AM a 08:20 AM", "4 | 08:20 AM a 08:40 AM",
									   "5 | 08:40 AM a 09:00 AM", "6 | 09:00 AM a 09:20 AM", "7 | 09:20 AM a 09:40 AM", "8 | 09:40 AM a 10:00 AM", "9 | 10:00 AM a 10:20 AM",
									   "10 | 10:20 AM a 10:40 AM", "11 | 10:40 AM a 11:00 AM", "12 | 11:00 AM a 11:20 AM", "13 | 11:20 AM a 11:40 AM", "14 | 11:40 AM a 12:00 PM" };
				strcpy(buff, times[date.getTime1()]);
				if (date.getTime2() != -1) {
					strcat(buff, " y "); strcat(buff, times[auxD->getData().getTime2()]);
				}
				SetWindowText(hStDtTime, buff);
			}
					break;
			case 1: {
					char times[15][25] = { "0 | 01:00 PM a 01:20 PM", "1 | 01:20 PM a 01:40 PM", "2 | 01:40 PM a 02:00 PM", "3 | 02:00 PM a 02:20 PM", "4 | 02:20 PM a 02:40 PM",
										   "5 | 02:40 PM a 03:00 PM", "6 | 03:00 PM a 03:20 PM", "7 | 03:20 PM a 03:40 PM", "8 | 03:40 PM a 04:00 PM", "9 | 04:00 PM a 04:20 PM",
										   "10 | 04:20 PM a 04:40 PM", "11 | 04:40 PM a 05:00 PM", "12 | 05:00 PM a 05:20 PM", "13 | 05:20 PM a 05:40 PM", "14 | 05:40 PM a 06:00 PM" };
					strcpy(buff, times[date.getTime1()]);
					if (date.getTime2() != -1) {
						strcat(buff, " y "); strcat(buff, times[date.getTime2()]);
					}
					SetWindowText(hStDtTime, buff);
			}
					break;
			case 2: {
				char times[15][25] = { "0 | 07:00 PM a 07:20 PM", "1 | 07:20 PM a 07:40 PM", "2 | 07:40 PM a 08:00 PM", "3 | 08:00 PM a 08:20 PM", "4 | 08:20 PM a 08:40 PM",
									   "5 | 08:40 PM a 09:00 PM", "6 | 09:00 PM a 09:20 PM", "7 | 09:20 PM a 09:40 PM", "8 | 09:40 PM a 10:00 PM", "9 | 10:00 PM a 10:20 PM",
									   "10 | 10:20 PM a 10:40 PM", "11 | 10:40 PM a 11:00 PM", "12 | 11:00 PM a 11:20 PM", "13 | 11:20 PM a 11:40 PM", "14 | 11:40 PM a 12:00 AM" };
				strcpy(buff, times[date.getTime1()]);
				if (date.getTime2() != -1) {
					strcat(buff, " y "); strcat(buff, times[date.getTime2()]);
				}
				SetWindowText(hStDtTime, buff);
			}
					break;
			}
			SetWindowText(hStDtMed, date.getMed());
			SetWindowText(hStDtEsp, date.getEsp());
			_itoa(date.getCons(), buff, 10);
			SetWindowText(hStDtCons, buff);
			SetWindowText(hStDtPac, date.getPac());
			switch (date.getState()) {
			case 0:
				SetWindowText(hStDtState, "Activa");
				break;
			case 1:
				SetWindowText(hStDtState, "Atendida");
				break;
			case 2:
				SetWindowText(hStDtState, "Cancelada");
				SetWindowText(hStDtMot, date.getMotive());
				break;
			}
			//SetImage
			hPcFoto = GetDlgItem(hwnd, BMP_DT);
			hBmpFoto = (HBITMAP)LoadImage(NULL, date.getDirImage(), IMAGE_BITMAP, 85, 105, LR_LOADFROMFILE);
			SendMessage(hPcFoto, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmpFoto);
			//SetButtons
			if (date.getState() == 0) {
				EnableWindow(hBtnDtMod, true);
				EnableWindow(hBtnDtDel, true);
			}
		}
		if (LOWORD(wParam) == BTN_DT_SEARCH && HIWORD(wParam) == BN_CLICKED) {
			HWND hEdtSearch = GetDlgItem(hwnd, EDT_DT_SEARCH);
			int inlen = GetWindowTextLength(hEdtSearch);
			char buff[100];
			if (inlen == 0) {
				MessageBox(hwnd, "Introduce un número de cita en la barra de búsqueda para buscar la cita.", "Campo Vacío", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 20) {
				MessageBox(hwnd, "Demasiados caracteres en la barra de búsqueda.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtSearch, buff, inlen + 1);
			inlen = atoi(buff);
			auxD = listaCitas.SearchNode(inlen);
			if (auxD == NULL) {
				MessageBox(hwnd, "No se encontró cita con ese número.", "No Encontrado", MB_ICONINFORMATION);
				break;
			}
			Cita date = auxD->getData();
			_itoa(date.getID(), buff, 10);
			SetWindowText(hStDtNoDate, buff);
			_itoa(date.getDate().tm_mday, buff, 10); strcat(buff, " de ");
			switch (date.getDate().tm_mon) {
			case 1:
				strcat(buff, "Enero del ");
				break;
			case 2:
				strcat(buff, "Febrero del ");
				break;
			case 3:
				strcat(buff, "Marzo del ");
				break;
			case 4:
				strcat(buff, "Abril del ");
				break;
			case 5:
				strcat(buff, "Mayo del ");
				break;
			case 6:
				strcat(buff, "Junio del ");
				break;
			case 7:
				strcat(buff, "Julio del ");
				break;
			case 8:
				strcat(buff, "Agosto del ");
				break;
			case 9:
				strcat(buff, "Septiembre del ");
				break;
			case 10:
				strcat(buff, "Octubre del ");
				break;
			case 11:
				strcat(buff, "Noviembre del ");
				break;
			case 12:
				strcat(buff, "Diciembre del ");
				break;
			}
			char num[5];
			_itoa(date.getDate().tm_year, num, 10); strcat(buff, num);
			SetWindowText(hStDtDate, buff);
			switch (date.getMedSch()) {
			case 0: {
				char times[15][25] = { "0 | 07:00 AM a 07:20 AM", "1 | 07:20 AM a 07:40 AM", "2 | 07:40 AM a 08:00 AM", "3 | 08:00 AM a 08:20 AM", "4 | 08:20 AM a 08:40 AM",
									   "5 | 08:40 AM a 09:00 AM", "6 | 09:00 AM a 09:20 AM", "7 | 09:20 AM a 09:40 AM", "8 | 09:40 AM a 10:00 AM", "9 | 10:00 AM a 10:20 AM",
									   "10 | 10:20 AM a 10:40 AM", "11 | 10:40 AM a 11:00 AM", "12 | 11:00 AM a 11:20 AM", "13 | 11:20 AM a 11:40 AM", "14 | 11:40 AM a 12:00 PM" };
				strcpy(buff, times[date.getTime1()]);
				if (date.getTime2() != -1) {
					strcat(buff, " y "); strcat(buff, times[auxD->getData().getTime2()]);
				}
				SetWindowText(hStDtTime, buff);
			}
					break;
			case 1: {
				char times[15][25] = { "0 | 01:00 PM a 01:20 PM", "1 | 01:20 PM a 01:40 PM", "2 | 01:40 PM a 02:00 PM", "3 | 02:00 PM a 02:20 PM", "4 | 02:20 PM a 02:40 PM",
									   "5 | 02:40 PM a 03:00 PM", "6 | 03:00 PM a 03:20 PM", "7 | 03:20 PM a 03:40 PM", "8 | 03:40 PM a 04:00 PM", "9 | 04:00 PM a 04:20 PM",
									   "10 | 04:20 PM a 04:40 PM", "11 | 04:40 PM a 05:00 PM", "12 | 05:00 PM a 05:20 PM", "13 | 05:20 PM a 05:40 PM", "14 | 05:40 PM a 06:00 PM" };
				strcpy(buff, times[date.getTime1()]);
				if (date.getTime2() != -1) {
					strcat(buff, " y "); strcat(buff, times[date.getTime2()]);
				}
				SetWindowText(hStDtTime, buff);
			}
					break;
			case 2: {
				char times[15][25] = { "0 | 07:00 PM a 07:20 PM", "1 | 07:20 PM a 07:40 PM", "2 | 07:40 PM a 08:00 PM", "3 | 08:00 PM a 08:20 PM", "4 | 08:20 PM a 08:40 PM",
									   "5 | 08:40 PM a 09:00 PM", "6 | 09:00 PM a 09:20 PM", "7 | 09:20 PM a 09:40 PM", "8 | 09:40 PM a 10:00 PM", "9 | 10:00 PM a 10:20 PM",
									   "10 | 10:20 PM a 10:40 PM", "11 | 10:40 PM a 11:00 PM", "12 | 11:00 PM a 11:20 PM", "13 | 11:20 PM a 11:40 PM", "14 | 11:40 PM a 12:00 AM" };
				strcpy(buff, times[date.getTime1()]);
				if (date.getTime2() != -1) {
					strcat(buff, " y "); strcat(buff, times[date.getTime2()]);
				}
				SetWindowText(hStDtTime, buff);
			}
					break;
			}
			SetWindowText(hStDtMed, date.getMed());
			SetWindowText(hStDtEsp, date.getEsp());
			_itoa(date.getCons(), buff, 10);
			SetWindowText(hStDtCons, buff);
			SetWindowText(hStDtPac, date.getPac());
			switch (date.getState()) {
			case 0:
				SetWindowText(hStDtState, "Activa");
				break;
			case 1:
				SetWindowText(hStDtState, "Atendida");
				break;
			case 2:
				SetWindowText(hStDtState, "Cancelada");
				SetWindowText(hStDtMot, date.getMotive());
				break;
			}
			//SetImage
			hPcFoto = GetDlgItem(hwnd, BMP_DT);
			hBmpFoto = (HBITMAP)LoadImage(NULL, date.getDirImage(), IMAGE_BITMAP, 85, 105, LR_LOADFROMFILE);
			SendMessage(hPcFoto, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmpFoto);
			//SetButtons
			if (date.getState() == 0) {
				EnableWindow(hBtnDtMod, true);
				EnableWindow(hBtnDtDel, true);
			}
		}
		if (LOWORD(wParam) == BTN_DT_MEDMON && HIWORD(wParam) == BN_CLICKED) {
			int result = DialogBox(hInstanciaGlobal, MAKEINTRESOURCE(IDD_MEDMON), hwnd, consultaMedMes);
		}
		if (LOWORD(wParam) == BTN_DT_WEEK && HIWORD(wParam) == BN_CLICKED) {
			int result = DialogBox(hInstanciaGlobal, MAKEINTRESOURCE(IDD_SEM), hwnd, consultaSem);
		}
		if (LOWORD(wParam) == BTN_DT_ESPWEEK && HIWORD(wParam) == BN_CLICKED) {
			int result = DialogBox(hInstanciaGlobal, MAKEINTRESOURCE(IDD_ESPSEM), hwnd, consultaEspSem);
		}
		if (LOWORD(wParam) == BTN_DT_ADD && HIWORD(wParam) == BN_CLICKED) {
			int result = DialogBox(hInstanciaGlobal, MAKEINTRESOURCE(IDD_CITA), hwnd, agregarCita);
			if (result == 1) {
				listaCitas.PrintOnWindow(hLbDat, 0, NULL);
				//CleanStatics
				SetWindowText(hStDtNoDate, "");
				SetWindowText(hStDtDate, "");
				SetWindowText(hStDtTime, "");
				SetWindowText(hStDtMed, "");
				SetWindowText(hStDtEsp, "");
				SetWindowText(hStDtCons, "");
				SetWindowText(hStDtPac, "");
				SetWindowText(hStDtState, "");
				SetWindowText(hStDtMot, "");
				//SetImage
				hPcFoto = GetDlgItem(hwnd, BMP_DT);
				hBmpFoto = (HBITMAP)LoadImage(NULL, "", IMAGE_BITMAP, 90, 120, LR_LOADFROMFILE);
				SendMessage(hPcFoto, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmpFoto);
				//SetButtons
				EnableWindow(hBtnDtMod, false);
				EnableWindow(hBtnDtDel, false);
			}
		}
		if (LOWORD(wParam) == BTN_DT_MODIFY && HIWORD(wParam) == BN_CLICKED) {
			int result = DialogBox(hInstanciaGlobal, MAKEINTRESOURCE(IDD_CITA), hwnd, editarCita);
			if (result == 1) {
				listaCitas.PrintOnWindow(hLbDat, 0, NULL);
				//CleanStatics
				SetWindowText(hStDtNoDate, "");
				SetWindowText(hStDtDate, "");
				SetWindowText(hStDtTime, "");
				SetWindowText(hStDtMed, "");
				SetWindowText(hStDtEsp, "");
				SetWindowText(hStDtCons, "");
				SetWindowText(hStDtPac, "");
				SetWindowText(hStDtState, "");
				SetWindowText(hStDtMot, "");
				//SetImage
				hPcFoto = GetDlgItem(hwnd, BMP_DT);
				hBmpFoto = (HBITMAP)LoadImage(NULL, "", IMAGE_BITMAP, 90, 120, LR_LOADFROMFILE);
				SendMessage(hPcFoto, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmpFoto);
				//SetButtons
				EnableWindow(hBtnDtMod, false);
				EnableWindow(hBtnDtDel, false);
			}
		}
		if (LOWORD(wParam) == BTN_DT_DELETE && HIWORD(wParam) == BN_CLICKED) {
			int result = DialogBox(hInstanciaGlobal, MAKEINTRESOURCE(IDD_CONFIRM), hwnd, confirmarCita);
			if (result == 1) {
				//CleanStatics
				SetWindowText(hStDtNoDate, "");
				SetWindowText(hStDtDate, "");
				SetWindowText(hStDtTime, "");
				SetWindowText(hStDtMed, "");
				SetWindowText(hStDtEsp, "");
				SetWindowText(hStDtCons, "");
				SetWindowText(hStDtPac, "");
				SetWindowText(hStDtState, "");
				SetWindowText(hStDtMot, "");
				//SetImage
				hPcFoto = GetDlgItem(hwnd, BMP_DT);
				hBmpFoto = (HBITMAP)LoadImage(NULL, "", IMAGE_BITMAP, 90, 120, LR_LOADFROMFILE);
				SendMessage(hPcFoto, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmpFoto);
				//SetButtons
				EnableWindow(hBtnDtMod, false);
				EnableWindow(hBtnDtDel, false);
			}
		}
		//GestiónMedicos
		if (LOWORD(wParam) == LB_MED && HIWORD(wParam) == LBN_SELCHANGE) {
			//GetNode
			int index = SendMessage(hLbMedic, LB_GETCURSEL, 0, 0);
			char buff[80];
			SendMessage(hLbMedic, LB_GETTEXT, index, (LPARAM)buff);
			index = atoi(buff);
			auxM = listaMedicos.Search(listaMedicos.getRoot(), index, 0, 0);
			//SetStatics
			SetWindowText(hStMedName, auxM->compName);
			_itoa(auxM->ced, buff, 10);
			SetWindowText(hStMedCed, buff);
			SetWindowText(hStMedEsp, auxM->esp);
			_itoa(auxM->cons, buff, 10);
			SetWindowText(hStMedCons, buff);
			SetWindowText(hStMedContact, auxM->contact);
			strcpy(buff, "");
			for (int i = 0; i < 5; i++) {
				if (auxM->ateDay[i] == 'L')
					strcat(buff, "Lunes, ");
				if (auxM->ateDay[i] == 'M')
					strcat(buff, "Martes, ");
				if (auxM->ateDay[i] == 'N')
					strcat(buff, "Miércoles, ");
				if (auxM->ateDay[i] == 'J')
					strcat(buff, "Jueves, ");
				if (auxM->ateDay[i] == 'V')
					strcat(buff, "Viernes, ");
			}
			if (auxM->time == 0)
				strcat(buff, "De 7:00 AM a 12:00 PM.");
			if (auxM->time == 1)
				strcat(buff, "De 1:00 PM a 6:00 PM.");
			if (auxM->time == 2)
				strcat(buff, "De 7:00 PM a 12:00 AM.");
			SetWindowText(hStMedHora, buff);
			//SetImage
			hPcFoto = GetDlgItem(hwnd, BMP_MED);
			hBmpFoto = (HBITMAP)LoadImage(NULL, auxM->dirImage, IMAGE_BITMAP, 85, 105, LR_LOADFROMFILE);
			SendMessage(hPcFoto, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmpFoto);
			//SetButtons
			EnableWindow(hBtnMedMod, true);
			EnableWindow(hBtnMedDel, true);
		}
		if (LOWORD(wParam) == BTN_MED_ADD && HIWORD(wParam) == BN_CLICKED) {
			int result = DialogBox(hInstanciaGlobal, MAKEINTRESOURCE(IDD_REGISMEDIC), hwnd, agregarMedico);
			if (result == 1) {
				SendMessage(hLbMedic, LB_RESETCONTENT, 0, 0);
				listaMedicos.printInOrderLb(hLbMedic, listaMedicos.getRoot());
				//CleanStatics
				SetWindowText(hStMedName, "");
				SetWindowText(hStMedCed, "");
				SetWindowText(hStMedEsp, "");
				SetWindowText(hStMedCons, "");
				SetWindowText(hStMedContact, "");
				SetWindowText(hStMedHora, "");
				//SetImage
				hPcFoto = GetDlgItem(hwnd, BMP_MED);
				hBmpFoto = (HBITMAP)LoadImage(NULL, "", IMAGE_BITMAP, 90, 120, LR_LOADFROMFILE);
				SendMessage(hPcFoto, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmpFoto);
				//SetButtons
				EnableWindow(hBtnMedMod, false);
				EnableWindow(hBtnMedDel, false);
			}
		}
		if (LOWORD(wParam) == BTN_MED_MODIFY && HIWORD(wParam) == BN_CLICKED) {
			int index = SendMessage(hLbMedic, LB_GETCURSEL, 0, 0);
			char buff[80];
			SendMessage(hLbMedic, LB_GETTEXT, index, (LPARAM)buff);
			index = atoi(buff);
			auxM = listaMedicos.Search(listaMedicos.getRoot(), index, 0, 0);
			int result = DialogBox(hInstanciaGlobal, MAKEINTRESOURCE(IDD_REGISMEDIC), hwnd, editarMedico);
			if (result == 1) {
				//ResetLbContent
				SendMessage(hLbMedic, LB_RESETCONTENT, 0, 0);
				listaMedicos.printInOrderLb(hLbMedic, listaMedicos.getRoot());
				//CleanStatics
				SetWindowText(hStMedName, "");
				SetWindowText(hStMedCed, "");
				SetWindowText(hStMedEsp, "");
				SetWindowText(hStMedCons, "");
				SetWindowText(hStMedContact, "");
				SetWindowText(hStMedHora, "");
				//SetImage
				hPcFoto = GetDlgItem(hwnd, BMP_MED);
				hBmpFoto = (HBITMAP)LoadImage(NULL, "", IMAGE_BITMAP, 90, 120, LR_LOADFROMFILE);
				SendMessage(hPcFoto, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmpFoto);
				//SetButtons
				EnableWindow(hBtnMedMod, false);
				EnableWindow(hBtnMedDel, false);
			}
		}
		if (LOWORD(wParam) == BTN_MED_DELETE && HIWORD(wParam) == BN_CLICKED) {
			if (!is_PendingDateMedic(auxM->ced)) {
				if (MessageBox(hwnd, "¿Seguro que quiere dar de baja este médico?", "AVISO", MB_YESNO) == IDYES) {
					//DeleteNode
					listaMedicos.DeleteNode(auxM);
					//ResetLbContent
					SendMessage(hLbMedic, LB_RESETCONTENT, 0, 0);
					listaMedicos.printInOrderLb(hLbMedic, listaMedicos.getRoot());
					//CleanStatics
					SetWindowText(hStMedName, "");
					SetWindowText(hStMedCed, "");
					SetWindowText(hStMedEsp, "");
					SetWindowText(hStMedCons, "");
					SetWindowText(hStMedContact, "");
					SetWindowText(hStMedHora, "");
					//SetImage
					hPcFoto = GetDlgItem(hwnd, BMP_MED);
					hBmpFoto = (HBITMAP)LoadImage(NULL, "", IMAGE_BITMAP, 90, 120, LR_LOADFROMFILE);
					SendMessage(hPcFoto, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmpFoto);
					//SetButtons
					EnableWindow(hBtnMedMod, false);
					EnableWindow(hBtnMedDel, false);
				}
			}
			else
				MessageBox(hwnd, "Éste médico tiene citas pendientes, no es posible darlo de baja.", "Citas Pendientes", MB_ICONINFORMATION);
		}
		if (LOWORD(wParam) == BTN_MED_REPORT && HIWORD(wParam) == BN_CLICKED) {
			generateMedicReport();
		}
		//GestiónEspecialidades
		if (LOWORD(wParam) == LB_ESP && HIWORD(wParam) == LBN_SELCHANGE) {
			//GetNode
			int index = SendMessage(hLbEsp, LB_GETCURSEL, 0, 0);
			char buff[80];
			SendMessage(hLbEsp, LB_GETTEXT, index, (LPARAM)buff);
			index = atoi(buff);
			auxE = listaEspecialidades.SearchNode(index);
			Especialidad esp = auxE->getData();
			//SetStatics
			SetWindowText(hEdtEspName, esp.getName());
			_itoa(esp.getID(), buff, 10);
			SetWindowText(hEdtEspKey, buff);
			SetWindowText(hEdtEspDesc, esp.getDesc());
			//SetButtons
			EnableWindow(hBtnEspMod, true);
			EnableWindow(hBtnEspDel, true);
		}
		if (LOWORD(wParam) == BTN_ESP_CLEAN && HIWORD(wParam) == BN_CLICKED) {
			SetWindowText(hEdtEspName, "");
			SetWindowText(hEdtEspKey, "");
			SetWindowText(hEdtEspDesc, "");
		}
		if (LOWORD(wParam) == BTN_ESP_ADD && HIWORD(wParam) == BN_CLICKED) {
			Especialidad temp;
			char buff[MAX_PATH];
			//GetName
			int length = GetWindowTextLength(hEdtEspName);
			if (length == 0) {
				MessageBox(hwnd, "Falta llenar el campo Nombre de especialidad.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (length > 30) {
				MessageBox(hwnd, "El Nombre de especialidad es muy largo, debe de tener menos de 30 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtEspName, buff, length + 1);
			temp.setName(buff);
			//GetKey
			length = GetWindowTextLength(hEdtEspKey);
			if (length == 0) {
				MessageBox(hwnd, "Falta llenar el campo Clave de especialidad.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (length > 10) {
				MessageBox(hwnd, "La clave de especialidad es muy larga, debe de tener menos de 10 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtEspKey, buff, length + 1);
			temp.setID(atoi(buff));
			if (listaEspecialidades.SearchNode(temp.getID()) != NULL) {
				MessageBox(hwnd, "Ya existe una especialidad con ésta clave.", "AVISO", MB_ICONINFORMATION);
				break;
			}
			//GetDesc
			length = GetWindowTextLength(hEdtEspDesc);
			if (length == 0) {
				MessageBox(hwnd, "Falta llenar el campo Descripción de especialidad.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (length > MAX_PATH) {
				MessageBox(hwnd, "La descripción de especialidad es muy larga, debe de tener menos de 260 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtEspDesc, buff, length + 1);
			temp.setDesc(buff);
			//GetUserID
			temp.setUserID(gUserID);
			//AddNode
			listaEspecialidades.AddNode(temp);
			//ResetWindows
			listaEspecialidades.PrintOnWindow(hLbEsp, 0, NULL);
			SetWindowText(hEdtEspName, "");
			SetWindowText(hEdtEspKey, "");
			SetWindowText(hEdtEspDesc, "");
		}
		if (LOWORD(wParam) == BTN_ESP_MODIFY && HIWORD(wParam) == BN_CLICKED) {
			Especialidad temp;
			char buff[MAX_PATH];
			int id = auxE->getData().getID();
			//GetName
			int length = GetWindowTextLength(hEdtEspName);
			if (length == 0) {
				MessageBox(hwnd, "Falta llenar el campo Nombre de especialidad.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (length > 30) {
				MessageBox(hwnd, "El Nombre de especialidad es muy largo, debe de tener menos de 30 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtEspName, buff, length + 1);
			temp.setName(buff);
			//GetKey
			length = GetWindowTextLength(hEdtEspKey);
			if (length == 0) {
				MessageBox(hwnd, "Falta llenar el campo Clave de especialidad.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (length > 10) {
				MessageBox(hwnd, "La Clave de especialidad es muy larga, debe de tener menos de 10 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtEspKey, buff, length + 1);
			length = atoi(buff);
			if (length != id) {
				if (listaEspecialidades.SearchNode(length) != NULL) {
					MessageBox(hwnd, "Ya existe una especialidad con ésta clave.", "AVISO", MB_ICONINFORMATION);
					break;
				}
				listaMedicos.Search(listaMedicos.getRoot(), id, length, 1);
				temp.setID(length);
			}
			else
				temp.setID(id);
			//GetDesc
			length = GetWindowTextLength(hEdtEspDesc);
			if (length == 0) {
				MessageBox(hwnd, "Falta llenar el campo Descripción de especialidad.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (length > MAX_PATH) {
				MessageBox(hwnd, "La Descripción de especialidad es muy larga, debe de tener menos de 260 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtEspDesc, buff, length + 1);
			temp.setDesc(buff);
			//GetUserID
			temp.setUserID(auxE->getData().getUserID());
			//ChangeNodeData
			auxE->setData(temp);
			//ResetContent
			listaEspecialidades.PrintOnWindow(hLbEsp, 0, NULL);
			//CleanStatics
			SetWindowText(hEdtEspName, "");
			SetWindowText(hEdtEspKey, "");
			SetWindowText(hEdtEspDesc, "");
			//SetButtons
			EnableWindow(hBtnEspMod, false);
			EnableWindow(hBtnEspDel, false);
		}
		if (LOWORD(wParam) == BTN_ESP_DELETE && HIWORD(wParam) == BN_CLICKED) {
			//ConfirmNoMedics and Delete
			int id = auxE->getData().getID();
			if (is_UsingEsp(listaMedicos.getRoot(), id))
				MessageBox(hwnd, "Existe al menos un médico registrado en esta especialidad, dé de baja a los médicos de esta especialidad antes de eliminarla.", "AVISO", MB_ICONINFORMATION);
			else {
				if(MessageBox(hwnd, "¿Seguro que quiere dar de baja esta especialidad?", "Confirmar", MB_YESNO) == IDYES)
					listaEspecialidades.DeleteNode(auxE);
				else break;
			}
			//ResetContent
			listaEspecialidades.PrintOnWindow(hLbEsp, 0, NULL);
			//CleanStatics
			SetWindowText(hEdtEspName, "");
			SetWindowText(hEdtEspKey, "");
			SetWindowText(hEdtEspDesc, "");
			//SetButtons
			EnableWindow(hBtnEspMod, false);
			EnableWindow(hBtnEspDel, false);
		}
		//GestiónPacientes
		if (LOWORD(wParam) == LB_PAC && HIWORD(wParam) == LBN_SELCHANGE) {
			//GetNode
			int index = SendMessage(hLbPac, LB_GETCURSEL, 0, 0);
			char buff[80];
			SendMessage(hLbPac, LB_GETTEXT, index, (LPARAM)buff);
			index = atoi(buff);
			auxP = listaPacientes.SearchNode(index);
			Paciente pat = auxP->getData();
			//SetStatics
			SetWindowText(hStPacName, pat.getCompName());
			_itoa(pat.getAge(), buff, 10);
			SetWindowText(hStPacAge, buff);
			if (pat.getGenre() == 'M')
				SetWindowText(hStPacGenre, "Mujer");
			else
				SetWindowText(hStPacGenre, "Hombre");
			SetWindowText(hStPacBirthday, pat.getBirthDate());
			SetWindowText(hStPacContact, pat.getContact());
			SetWindowText(hStPacFirstMed, pat.getMed());
			SetWindowText(hStPacRef, pat.getRef());
			//SetButtons
			EnableWindow(hBtnPacMod, true);
			EnableWindow(hBtnPacDel, true);
		}
		if (LOWORD(wParam) == BTN_PAC_ADD && HIWORD(wParam) == BN_CLICKED) {
			int result = DialogBox(hInstanciaGlobal, MAKEINTRESOURCE(IDD_REGISPAC), hwnd, agregarPaciente);
			if (result == 1) {
				listaPacientes.PrintOnWindow(hLbPac, 0, NULL);
				SetWindowText(hStPacName, "");
				SetWindowText(hStPacAge, "");
				SetWindowText(hStPacGenre, "");
				SetWindowText(hStPacBirthday, "");
				SetWindowText(hStPacContact, "");
				SetWindowText(hStPacFirstMed, "");
				SetWindowText(hStPacRef, "");
				EnableWindow(hBtnPacMod, false);
				EnableWindow(hBtnPacDel, false);
			}
		}
		if (LOWORD(wParam) == BTN_PAC_MODIFY && HIWORD(wParam) == BN_CLICKED) {
			int result = DialogBox(hInstanciaGlobal, MAKEINTRESOURCE(IDD_REGISPAC), hwnd, editarPaciente);
			if (result == 1) {
				//ResetLbContent
				listaPacientes.PrintOnWindow(hLbPac, 0, NULL);
				//CleanStatics
				SetWindowText(hStPacName, "");
				SetWindowText(hStPacAge, "");
				SetWindowText(hStPacGenre, "");
				SetWindowText(hStPacBirthday, "");
				SetWindowText(hStPacContact, "");
				SetWindowText(hStPacFirstMed, "");
				SetWindowText(hStPacRef, "");
				//SetButtons
				EnableWindow(hBtnPacMod, false);
				EnableWindow(hBtnPacDel, false);
			}
		}
		if (LOWORD(wParam) == BTN_PAC_DELETE && HIWORD(wParam) == BN_CLICKED) {
			if (MessageBox(hwnd, "¿Seguro que quiere dar de baja esta especialidad?", "Confirmar", MB_YESNO) == IDYES) {
				listaPacientes.DeleteNode(auxP);
				//ResetContent
				listaPacientes.PrintOnWindow(hLbPac, 0, NULL);
				//CleanStatics
				SetWindowText(hStPacName, "");
				SetWindowText(hStPacAge, "");
				SetWindowText(hStPacGenre, "");
				SetWindowText(hStPacBirthday, "");
				SetWindowText(hStPacContact, "");
				SetWindowText(hStPacFirstMed, "");
				SetWindowText(hStPacRef, "");
				//SetButtons
				EnableWindow(hBtnPacMod, false);
				EnableWindow(hBtnPacDel, false);
			}
		}
		if (LOWORD(wParam) == BTN_PAC_REPORT && HIWORD(wParam) == BN_CLICKED) {
			generatePatientReport();
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		writeCounters();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return FALSE;
}

BOOL CALLBACK agregarMedico(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HWND hCbEsp = GetDlgItem(hwnd, CB_ESP);
	switch (msg) {
	case WM_INITDIALOG: {
		hStUser = GetDlgItem(hwnd, ST_USERNAME);
		SetWindowText(hStUser, username);
		listaEspecialidades.PrintOnWindow(hCbEsp, 1, NULL);
		CheckDlgButton(hwnd, RD_TIME1, BST_CHECKED);
	}
	break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL && HIWORD(wParam) == BN_CLICKED)
			EndDialog(hwnd, 0);
		if (LOWORD(wParam) == IDOK && HIWORD(wParam) == BN_CLICKED) {
			HWND hEdtName = GetDlgItem(hwnd, EDT_NAME);
			HWND hEdtLastNameP = GetDlgItem(hwnd, EDT_LASTNAMEPAT);
			HWND hEdtLastNameM = GetDlgItem(hwnd, EDT_LASTNAMEMAT);
			HWND hEdtCed = GetDlgItem(hwnd, EDT_CED);
			HWND hEdtContact = GetDlgItem(hwnd, EDT_PHONE);
			HWND hEdtCons = GetDlgItem(hwnd, EDT_NOCONS);
			Medico temp;
			int inlen;
			char buff[90];
			//GetName
			inlen = GetWindowTextLength(hEdtName);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Nombre.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 30) {
				MessageBox(hwnd, "El Nombre es muy largo, debe tener menos de 30 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtName, buff, inlen + 1);
			if (!validAlpha(buff)) {
				MessageBox(hwnd, "El Nombre no debe contener caracteres numéricos.", "Información Incorrecta", MB_ICONINFORMATION);
				break;
			}
			strcpy(temp.name, buff);
			//GetLastNameP
			inlen = GetWindowTextLength(hEdtLastNameP);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Apellido Paterno.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 30) {
				MessageBox(hwnd, "El Apellido Paterno es muy largo, debe tener menos de 30 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtLastNameP, buff, inlen + 1);
			if (!validAlpha(buff)) {
				MessageBox(hwnd, "El Apellido Paterno no debe contener caracteres numéricos.", "Información Incorrecta", MB_ICONINFORMATION);
				break;
			}
			strcpy(temp.lastNameP, buff);
			//GetLastNameM
			inlen = GetWindowTextLength(hEdtLastNameM);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Apellido Materno.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 30) {
				MessageBox(hwnd, "El Apellido Materno es muy largo, debe tener menos de 30 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtLastNameM, buff, inlen + 1);
			if (!validAlpha(buff)) {
				MessageBox(hwnd, "El Apellido Materno no debe contener caracteres numéricos.", "Información Incorrecta", MB_ICONINFORMATION);
				break;
			}
			strcpy(temp.lastNameM, buff);
			//GetCompName
			strcpy(buff, temp.name); strcat(buff, " "); strcat(buff, temp.lastNameP); strcat(buff, " "); strcat(buff, temp.lastNameM);
			strcpy(temp.compName, buff);
			//GetCed
			inlen = GetWindowTextLength(hEdtCed);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Cédula.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 10) {
				MessageBox(hwnd, "La Cedula es muy larga, debe tener menos de 10 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtCed, buff, inlen + 1);
			temp.ced = atoi(buff);
			if (is_SameCed(listaMedicos.getRoot(), temp.ced)) {
				MessageBox(hwnd, "Ya existe un médico con esta cédula.", "Cédula Existente.", MB_ICONINFORMATION);
				break;
			}
			//GetContact
			inlen = GetWindowTextLength(hEdtContact);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Teléfono de contacto.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen == 8 || inlen == 10) {
				GetWindowText(hEdtContact, buff, 13);
				strcpy(temp.contact, buff);
			}
			else {
				MessageBox(hwnd, "Número telefónico invalido. La cantidad de caracteres debe ser de 8 o 10.", "Teléfono inválido", MB_ICONINFORMATION);
				break;
			}
			//GetCons
			inlen = GetWindowTextLength(hEdtCons);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Consultorio.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 10) {
				MessageBox(hwnd, "El Número de consultorio es muy largo, debe tener menos de 10 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtCons, buff, inlen + 1);
			temp.cons = atoi(buff);
			//GetEsp
			inlen = SendMessage(hCbEsp, CB_GETCURSEL, 0, 0);
			if (inlen == -1) {
				MessageBox(hwnd, "Falta llenar el campo Especialidad.", "Campos incompletos", MB_ICONINFORMATION);
				break;
			}
			inlen = GetWindowTextLength(hCbEsp);
			GetWindowText(hCbEsp, buff, inlen + 1);
			Especialidad espIn = listaEspecialidades.SearchNode(atoi(buff))->getData();
			temp.espId = espIn.getID();
			strcpy(temp.esp, espIn.getName());
			//GetAteDay
			strcpy(buff, "");
			if (IsDlgButtonChecked(hwnd, CH_MON) == BST_CHECKED)
				strcat(buff, "L");
			if (IsDlgButtonChecked(hwnd, CH_TUE) == BST_CHECKED)
				strcat(buff, "M");
			if (IsDlgButtonChecked(hwnd, CH_WED) == BST_CHECKED)
				strcat(buff, "N");
			if (IsDlgButtonChecked(hwnd, CH_THU) == BST_CHECKED)
				strcat(buff, "J");
			if (IsDlgButtonChecked(hwnd, CH_FRI) == BST_CHECKED)
				strcat(buff, "V");
			strcat(buff, "\0");
			if (strcmp(buff, "\0") == 0) {
				MessageBox(hwnd, "Falta llenar días de atención.", "Campos incompletos", MB_ICONINFORMATION);
				break;
			}
			strcpy(temp.ateDay, buff);
			//GetTime
			if (IsDlgButtonChecked(hwnd, RD_TIME1) == BST_CHECKED)
				temp.time = 0;
			else if (IsDlgButtonChecked(hwnd, RD_TIME2) == BST_CHECKED)
				temp.time = 1;
			else if (IsDlgButtonChecked(hwnd, RD_TIME3) == BST_CHECKED)
				temp.time = 2;
			//CompareSchedules
			if (is_SameSched(listaMedicos.getRoot(), temp)) {
				MessageBox(hwnd, "El horario de éste médico solapa el horario de otro médico.", "Horario Ocupado", MB_ICONINFORMATION);
				break;
			}
			//GetImage
			strcpy(temp.dirImage, tempImage);
			//GetUserID
			temp.user = gUserID;
			listaMedicos.AddNode(temp);
			strcpy(tempImage, "");
			EndDialog(hwnd, 1);
		}
		if (LOWORD(wParam) == BTN_EX && HIWORD(wParam) == BN_CLICKED) {
			OPENFILENAME ofnFoto;
			ZeroMemory(&ofnFoto, sizeof(ofnFoto));
			ofnFoto.hwndOwner = hwnd;
			ofnFoto.lStructSize = sizeof(ofnFoto);
			ofnFoto.lpstrFile = tempImage;
			ofnFoto.nMaxFile = MAX_PATH;
			ofnFoto.lpstrDefExt = "bmp";
			ofnFoto.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
			ofnFoto.lpstrFilter = "BMP Images\0*.bmp\0All Files\0*.*\0";
			if (GetOpenFileName(&ofnFoto)) {
				hPcFoto = GetDlgItem(hwnd, BMP_MED);
				hBmpFoto = (HBITMAP)LoadImage(NULL, tempImage, IMAGE_BITMAP, 85, 105, LR_LOADFROMFILE);
				SendMessage(hPcFoto, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmpFoto);
			}
		}
		if (LOWORD(wParam) == BTN_UNDO && HIWORD(wParam) == BN_CLICKED) {
			strcpy(tempImage, "");
			hPcFoto = GetDlgItem(hwnd, BMP_MED);
			hBmpFoto = (HBITMAP)LoadImage(NULL, tempImage, IMAGE_BITMAP, 90, 120, LR_LOADFROMFILE);
			SendMessage(hPcFoto, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmpFoto);
		}
		break;
	}
	return FALSE;
}

BOOL CALLBACK editarMedico(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HWND hEdtName = GetDlgItem(hwnd, EDT_NAME);
	HWND hEdtLastNameP = GetDlgItem(hwnd, EDT_LASTNAMEPAT);
	HWND hEdtLastNameM = GetDlgItem(hwnd, EDT_LASTNAMEMAT);
	HWND hEdtCed = GetDlgItem(hwnd, EDT_CED);
	HWND hEdtContact = GetDlgItem(hwnd, EDT_PHONE);
	HWND hEdtCons = GetDlgItem(hwnd, EDT_NOCONS);
	HWND hCbEsp = GetDlgItem(hwnd, CB_ESP);
	switch (msg) {
	case WM_INITDIALOG: {
		hStUser = GetDlgItem(hwnd, ST_USERNAME);
		SetWindowText(hStUser, username);
		char buff[50];
		//SetEdits
		SetWindowText(hEdtName, auxM->name);
		SetWindowText(hEdtLastNameP, auxM->lastNameP);
		SetWindowText(hEdtLastNameM, auxM->lastNameM);
		//SetCed
		_itoa(auxM->ced, buff, 10);
		SetWindowText(hEdtCed, buff);
		EnableWindow(hEdtCed, false);
		//SetContact
		SetWindowText(hEdtContact, auxM->contact);
		//SetCons
		_itoa(auxM->cons, buff, 10);
		SetWindowText(hEdtCons, buff);
		//SetEsp
		listaEspecialidades.PrintOnWindow(hCbEsp, 1, NULL);
		_itoa(auxM->espId, buff, 10);
		SendMessage(hCbEsp, CB_SELECTSTRING, -1, (LPARAM)buff);
		//SetDays
		char *days = auxM->ateDay;
		while (*days != '\0') {
			if (*days == 'L')
				CheckDlgButton(hwnd, CH_MON, BST_CHECKED);
			if (*days == 'M')
				CheckDlgButton(hwnd, CH_TUE, BST_CHECKED);
			if (*days == 'N')
				CheckDlgButton(hwnd, CH_WED, BST_CHECKED);
			if (*days == 'J')
				CheckDlgButton(hwnd, CH_THU, BST_CHECKED);
			if (*days == 'V')
				CheckDlgButton(hwnd, CH_FRI, BST_CHECKED);
			days++;
		}
		//SetTime
		if (auxM->time == 0)
			CheckDlgButton(hwnd, RD_TIME1, BST_CHECKED);
		else if (auxM->time == 1)
			CheckDlgButton(hwnd, RD_TIME2, BST_CHECKED);
		else if (auxM->time == 2)
			CheckDlgButton(hwnd, RD_TIME3, BST_CHECKED);
		//SetImage
		hPcFoto = GetDlgItem(hwnd, BMP_MED);
		hBmpFoto = (HBITMAP)LoadImage(NULL, auxM->dirImage, IMAGE_BITMAP, 85, 105, LR_LOADFROMFILE);
		SendMessage(hPcFoto, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmpFoto);
		strcpy(tempImage, auxM->dirImage);
		break;
	}
	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL && HIWORD(wParam) == BN_CLICKED) {
			EndDialog(hwnd, 0);
		}
		if (LOWORD(wParam) == IDOK && HIWORD(wParam) == BN_CLICKED) {
			Medico temp;
			char buff[60];
			int inlen;
			//GetName
			inlen = GetWindowTextLength(hEdtName);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Nombre.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 60) {
				MessageBox(hwnd, "El Nombre es muy largo, debe tener menos de 60 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtName, buff, inlen + 1);
			if (!validAlpha(buff)) {
				MessageBox(hwnd, "El Nombre no debe contener caracteres numéricos.", "Información Incorrecta", MB_ICONINFORMATION);
				break;
			}
			strcpy(temp.name, buff);
			//GetLastNameP
			inlen = GetWindowTextLength(hEdtLastNameP);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Apellido Paterno.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 30) {
				MessageBox(hwnd, "El Apellido Paterno es muy largo, debe tener menos de 30 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtLastNameP, buff, inlen + 1);
			if (!validAlpha(buff)) {
				MessageBox(hwnd, "El Apellido Paterno no debe contener caracteres numéricos.", "Información Incorrecta", MB_ICONINFORMATION);
				break;
			}
			strcpy(temp.lastNameP, buff);
			//GetLastNameM
			inlen = GetWindowTextLength(hEdtLastNameM);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Apellido Materno.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 30) {
				MessageBox(hwnd, "El Apellido Materno es muy largo, debe tener menos de 30 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtLastNameM, buff, inlen + 1);
			if (!validAlpha(buff)) {
				MessageBox(hwnd, "El Apellido Materno no debe contener caracteres numéricos.", "Información Incorrecta", MB_ICONINFORMATION);
				break;
			}
			strcpy(temp.lastNameM, buff);
			//GetCompName
			strcpy(buff, temp.name); strcat(buff, " "); strcat(buff, temp.lastNameP); strcat(buff, " "); strcat(buff, temp.lastNameM);
			strcpy(temp.compName, buff);
			//PassCed
			temp.ced = auxM->ced;
			//GetContact
			inlen = GetWindowTextLength(hEdtContact);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Cédula.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen == 8 || inlen == 10) {
				GetWindowText(hEdtContact, temp.contact, inlen + 1);
			}
			else {
				MessageBox(hwnd, "Número telefónico invalido. La cantidad de caracteres debe ser de 8 o 10.", "Teléfono inválido", MB_ICONINFORMATION);
				break;
			}
			//GetCons
			inlen = GetWindowTextLength(hEdtCons);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Consultorio.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 10) {
				MessageBox(hwnd, "El Número de consultorio es muy largo, debe tener menos de 10 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtCons, buff, inlen + 1);
			temp.cons = atoi(buff);
			//GetEsp
			inlen = SendMessage(hCbEsp, CB_GETCURSEL, 0, 0);
			if (inlen == -1) {
				MessageBox(hwnd, "Falta llenar el campo Especialidad.", "Campos incompletos", MB_ICONINFORMATION);
				break;
			}
			inlen = GetWindowTextLength(hCbEsp);
			GetWindowText(hCbEsp, buff, inlen + 1);
			Especialidad espIn = listaEspecialidades.SearchNode(atoi(buff))->getData();
			temp.espId = espIn.getID();
			strcpy(temp.esp, espIn.getName());
			//GetAte
			strcpy(buff, "");
			if (IsDlgButtonChecked(hwnd, CH_MON) == BST_CHECKED)
				strcat(buff, "L");
			if (IsDlgButtonChecked(hwnd, CH_TUE) == BST_CHECKED)
				strcat(buff, "M");
			if (IsDlgButtonChecked(hwnd, CH_WED) == BST_CHECKED)
				strcat(buff, "N");
			if (IsDlgButtonChecked(hwnd, CH_THU) == BST_CHECKED)
				strcat(buff, "J");
			if (IsDlgButtonChecked(hwnd, CH_FRI) == BST_CHECKED)
				strcat(buff, "V");
			strcat(buff, "\0");
			if (strcmp(buff, "\0") == 0) {
				MessageBox(hwnd, "Falta llenar días de atención.", "Campos incompletos", MB_ICONINFORMATION);
				break;
			}
			strcpy(temp.ateDay, buff);
			//GetTime
			if (IsDlgButtonChecked(hwnd, RD_TIME1) == BST_CHECKED)
				temp.time = 0;
			else if (IsDlgButtonChecked(hwnd, RD_TIME2) == BST_CHECKED)
				temp.time = 1;
			else if (IsDlgButtonChecked(hwnd, RD_TIME3) == BST_CHECKED)
				temp.time = 2;
			//CompareSchedules
			if (is_SameSched(listaMedicos.getRoot(), temp)) {
				MessageBox(hwnd, "El horario de éste médico solapa el horario de otro médico.", "Horario Ocupado", MB_ICONINFORMATION);
				break;
			}
			//GetImage
			strcpy(temp.dirImage, tempImage);
			//PassUserID
			temp.user = auxM->user;
			*auxM = temp;
			EndDialog(hwnd, 1);
		}
		if (LOWORD(wParam) == BTN_EX && HIWORD(wParam) == BN_CLICKED) {
			OPENFILENAME ofnFoto;
			ZeroMemory(&ofnFoto, sizeof(ofnFoto));
			ofnFoto.hwndOwner = hwnd;
			ofnFoto.lStructSize = sizeof(ofnFoto);
			ofnFoto.lpstrFile = tempImage;
			ofnFoto.nMaxFile = MAX_PATH;
			ofnFoto.lpstrDefExt = "bmp";
			ofnFoto.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
			ofnFoto.lpstrFilter = "BMP Images\0*.bmp\0All Files\0*.*\0";
			if (GetOpenFileName(&ofnFoto)) {
				hPcFoto = GetDlgItem(hwnd, BMP_MED);
				hBmpFoto = (HBITMAP)LoadImage(NULL, tempImage, IMAGE_BITMAP, 85, 105, LR_LOADFROMFILE);
				SendMessage(hPcFoto, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmpFoto);
			}
		}
		if (LOWORD(wParam) == BTN_UNDO && HIWORD(wParam) == BN_CLICKED) {
			strcpy(tempImage, "");
			hPcFoto = GetDlgItem(hwnd, BMP_MED);
			hBmpFoto = (HBITMAP)LoadImage(NULL, tempImage, IMAGE_BITMAP, 90, 120, LR_LOADFROMFILE);
			SendMessage(hPcFoto, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmpFoto);
		}
		break;
	}
	return FALSE;
}

BOOL CALLBACK agregarPaciente(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HWND hCbDay = GetDlgItem(hwnd, CB_DAY);
	HWND hCbMonth = GetDlgItem(hwnd, CB_MONTH);
	HWND hCbMed = GetDlgItem(hwnd, CB_MED);
	switch (msg) {
	case WM_INITDIALOG: {
		hStUser = GetDlgItem(hwnd, ST_USERNAME);
		SetWindowText(hStUser, username);
		CheckDlgButton(hwnd, RD_FEMALE, BST_CHECKED);
		//Días
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"01");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"02");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"03");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"04");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"05");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"06");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"07");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"08");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"09");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"10");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"11");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"12");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"13");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"14");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"15");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"16");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"17");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"18");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"19");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"20");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"21");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"22");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"23");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"24");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"25");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"26");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"27");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"28");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"29");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"30");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"31");
		//Meses
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"01");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"02");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"03");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"04");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"05");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"06");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"07");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"08");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"09");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"10");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"11");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"12");
		listaMedicos.printInOrderCb(hCbMed, listaMedicos.getRoot());
		break;
	}
	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL && HIWORD(wParam) == BN_CLICKED)
			EndDialog(hwnd, 0);
		if (LOWORD(wParam) == IDOK && HIWORD(wParam) == BN_CLICKED) {
			HWND hEdtName = GetDlgItem(hwnd, EDT_NAME);
			HWND hEdtLastP = GetDlgItem(hwnd, EDT_LASTNAMEPAT);
			HWND hEdtLastM = GetDlgItem(hwnd, EDT_LASTNAMEMAT);
			HWND hEdtYear = GetDlgItem(hwnd, EDT_YEAR);
			HWND hEdtAge = GetDlgItem(hwnd, EDT_AGE);
			HWND hEdtContact = GetDlgItem(hwnd, EDT_PHONE);
			HWND hEdtRef = GetDlgItem(hwnd, EDT_REFERENCE);
			Paciente temp;
			char buff[MAX_PATH];
			int inlen;
			//GetName
			inlen = GetWindowTextLength(hEdtName);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Nombre.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 30) {
				MessageBox(hwnd, "El Nombre es muy largo, debe tener menos de 30 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtName, buff, inlen + 1);
			if (!validAlpha(buff)) {
				MessageBox(hwnd, "El Nombre no debe contener caracteres numéricos.", "Información Incorrecta", MB_ICONINFORMATION);
				break;
			}
			temp.setName(buff);
			//GetLastNameP
			inlen = GetWindowTextLength(hEdtLastP);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Apellido Paterno.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 30) {
				MessageBox(hwnd, "El Apellido Paterno es muy largo, debe tener menos de 30 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtLastP, buff, inlen + 1);
			if (!validAlpha(buff)) {
				MessageBox(hwnd, "El Apellido Paterno no debe contener caracteres numéricos.", "Información Incorrecta", MB_ICONINFORMATION);
				break;
			}
			temp.setLastNameP(buff);
			//GetLastNameM
			inlen = GetWindowTextLength(hEdtLastM);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Apellido Materno.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 30) {
				MessageBox(hwnd, "El Apellido Materno es muy largo, debe tener menos de 30 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtLastM, buff, inlen + 1);
			if (!validAlpha(buff)) {
				MessageBox(hwnd, "El Apellido Materno no debe contener caracteres numéricos.", "Información Incorrecta", MB_ICONINFORMATION);
				break;
			}
			temp.setLastNameM(buff);
			//SetCompleteName
			strcpy(buff, temp.getName()); strcat(buff, " "); strcat(buff, temp.getLastNameP()); strcat(buff, " "); strcat(buff, temp.getLastNameM());
			temp.setCompName(buff);
			//GetAge
			inlen = GetWindowTextLength(hEdtAge);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Edad.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 6) {
				MessageBox(hwnd, "La Edad es muy larga, debe tener menos de 6 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtAge, buff, inlen + 1);
			temp.setAge(atoi(buff));
			//GetBirthday
			time_t rawTime;
			tm validTime;
			time(&rawTime);
			validTime = *localtime(&rawTime);
			inlen = SendMessage(hCbDay, CB_GETCURSEL, 0, 0);
			if (inlen == -1) {
				MessageBox(hwnd, "Falta llenar el campo Día de nacimiento.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hCbDay, buff, 3);
			validTime.tm_mday = atoi(buff);
			inlen = SendMessage(hCbMonth, CB_GETCURSEL, 0, 0);
			if (inlen == -1) {
				MessageBox(hwnd, "Falta llenar el campo Mes de nacimiento.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hCbMonth, buff, 3);
			validTime.tm_mon = atoi(buff);
			inlen = GetWindowTextLength(hEdtYear);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Año de nacimiento.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 10) {
				MessageBox(hwnd, "El dato es muy largo, debe tener menos de 10 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtYear, buff, 5);
			validTime.tm_year = atoi(buff);
			validTime.tm_mon -= 1;
			validTime.tm_year -= 1900;
			mktime(&validTime);
			char num[6];
			char zero[3];
			strcpy(buff, "");
			if (validTime.tm_mday < 10) {
				strcpy(zero, "0");
				_itoa(validTime.tm_mday, num, 10); strcat(zero, num); strcat(buff, zero); strcat(buff, "/");
			}
			else {
				_itoa(validTime.tm_mday, num, 10); strcat(buff, num); strcat(buff, "/");
			}
			validTime.tm_mon += 1;
			if (validTime.tm_mon < 10) {
				strcpy(zero, "0");
				_itoa(validTime.tm_mon, num, 10);  strcat(zero, num); strcat(buff, zero); strcat(buff, "/");
			}
			else{
				_itoa(validTime.tm_mon, num, 10);  strcat(buff, num); strcat(buff, "/");
			}
			validTime.tm_year += 1900;
			_itoa(validTime.tm_year, num, 10); strcat(buff, num);
			temp.setBirthDate(buff);
			//GetGenre
			if (IsDlgButtonChecked(hwnd, RD_FEMALE) == BST_CHECKED) {
				temp.setGenre('M');
			}
			else {
				temp.setGenre('H');
			}
			//GetContact
			inlen = GetWindowTextLength(hEdtContact);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Teléfono de contacto.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen == 8 || inlen == 10)
				GetWindowText(hEdtContact, temp.getContact(), inlen + 1);
			else {
				MessageBox(hwnd, "Número telefónico invalido. La cantidad de caracteres debe ser de 8 o 10.", "Teléfono inválido", MB_ICONINFORMATION);
				break;
			}
			//GetMedic
			inlen = SendMessage(hCbMed, CB_GETCURSEL, 0, 0);
			if (inlen == -1) {
				MessageBox(hwnd, "Falta llenar el campo Primer médico.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			inlen = GetWindowTextLength(hCbMed);
			GetWindowText(hCbMed, buff, inlen + 1);
			inlen = atoi(buff);
			Medico *med = listaMedicos.Search(listaMedicos.getRoot(), inlen, 0, 0);
			temp.setMed(med->compName);
			temp.setMedID(med->ced);
			//GetRef
			inlen = GetWindowTextLength(hEdtRef);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Referencia.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > MAX_PATH) {
				MessageBox(hwnd, "La Referencia es muy larga, debe tener menos de 260 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtRef, buff, inlen + 1);
			temp.setRef(buff);
			//GetID
			temp.setID(countP);
			countP++;
			//GetUserID
			temp.setUserID(gUserID);
			listaPacientes.AddNode(temp);
			EndDialog(hwnd, 1);
		}
		break;						
	}
	return FALSE;
}

BOOL CALLBACK editarPaciente(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HWND hEdtName = GetDlgItem(hwnd, EDT_NAME);
	HWND hEdtLastNameP = GetDlgItem(hwnd, EDT_LASTNAMEPAT);
	HWND hEdtLastNameM = GetDlgItem(hwnd, EDT_LASTNAMEMAT);
	HWND hEdtAge = GetDlgItem(hwnd, EDT_AGE);
	HWND hEdtContact = GetDlgItem(hwnd, EDT_PHONE);
	HWND hCbDay = GetDlgItem(hwnd, CB_DAY);
	HWND hCbMonth = GetDlgItem(hwnd, CB_MONTH);
	HWND hEdtYear = GetDlgItem(hwnd, EDT_YEAR);
	HWND hCbMed = GetDlgItem(hwnd, CB_MED);
	HWND hEdtRef = GetDlgItem(hwnd, EDT_REFERENCE);
	switch (msg) {
	case WM_INITDIALOG: {
		hStUser = GetDlgItem(hwnd, ST_USERNAME);
		SetWindowText(hStUser, username);
		//Días
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"01");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"02");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"03");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"04");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"05");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"06");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"07");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"08");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"09");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"10");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"11");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"12");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"13");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"14");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"15");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"16");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"17");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"18");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"19");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"20");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"21");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"22");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"23");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"24");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"25");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"26");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"27");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"28");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"29");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"30");
		SendMessage(hCbDay, CB_ADDSTRING, 0, (LPARAM)"31");
		//Meses
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"01");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"02");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"03");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"04");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"05");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"06");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"07");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"08");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"09");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"10");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"11");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"12");
		listaMedicos.printInOrderCb(hCbMed, listaMedicos.getRoot());
		char buff[MAX_PATH];
		Paciente pat = auxP->getData();
		//SetName
		SetWindowText(hEdtName, pat.getName());
		//SetLastName
		SetWindowText(hEdtLastNameP, pat.getLastNameP());
		SetWindowText(hEdtLastNameM, pat.getLastNameM());
		//SetAge
		_itoa(pat.getAge(), buff, 10);
		SetWindowText(hEdtAge, buff);
		//SetContact
		SetWindowText(hEdtContact, pat.getContact());
		//SetFirstMed
		_itoa(pat.getMedID(), buff, 10);
		SendMessage(hCbMed, CB_SELECTSTRING, -1, (LPARAM)buff);
		//SetRef
		SetWindowText(hEdtRef, pat.getRef());
		//SetBirthday
		string fecha(pat.getBirthDate());
		string day = fecha.substr(0, 2);
		string month = fecha.substr(3, 2);
		string year = fecha.substr(6, 4);
		char dayC[3]; strcpy(dayC, day.c_str());
		char monthC[3]; strcpy(monthC, month.c_str());
		char yearC[5]; strcpy(yearC, year.c_str());
		int dayI = atoi(dayC);
		int monthI = atoi(monthC);
		SendMessage(hCbDay, CB_SETCURSEL, dayI - 1, (LPARAM)dayC);
		SendMessage(hCbMonth, CB_SETCURSEL, monthI - 1, (LPARAM)monthC);
		SetWindowText(hEdtYear, yearC);
		//SetGenre
		if (pat.getGenre() == 'M')
			CheckDlgButton(hwnd, RD_FEMALE, BST_CHECKED);
		else
			CheckDlgButton(hwnd, RD_MALE, BST_CHECKED);
		break;
	}
	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL && HIWORD(wParam) == BN_CLICKED)
			EndDialog(hwnd, 0);
		if (LOWORD(wParam) == IDOK && HIWORD(wParam) == BN_CLICKED) {
			Paciente temp;
			char buff[MAX_PATH];
			int inlen;
			//GetName
			inlen = GetWindowTextLength(hEdtName);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Nombre.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 30) {
				MessageBox(hwnd, "El Nombre es muy largo, debe tener menos de 30 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtName, buff, inlen + 1);
			if (!validAlpha(buff)) {
				MessageBox(hwnd, "El Nombre no debe contener caracteres numéricos.", "Información incorrecta", MB_ICONINFORMATION);
				break;
			}
			temp.setName(buff);
			//GetLastNameP
			inlen = GetWindowTextLength(hEdtLastNameP);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Apellido Paternos.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 30) {
				MessageBox(hwnd, "El Apellido Paterno es muy largo, debe tener menos de 30 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtLastNameP, buff, inlen + 1);
			if (!validAlpha(buff)) {
				MessageBox(hwnd, "El Apellido Paterno no deben contener caracteres numéricos.", "Información Incorrecta", MB_ICONINFORMATION);
				break;
			}
			temp.setLastNameP(buff);
			//GetLastNameM
			inlen = GetWindowTextLength(hEdtLastNameM);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Apellido Maternos.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 30) {
				MessageBox(hwnd, "El Apellido Materno es muy largo, debe tener menos de 30 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtLastNameM, buff, inlen + 1);
			if (!validAlpha(buff)) {
				MessageBox(hwnd, "El Apellido Materno no deben contener caracteres numéricos.", "Información Incorrecta", MB_ICONINFORMATION);
				break;
			}
			temp.setLastNameM(buff);
			//SetCompleteName
			strcpy(buff, temp.getName()); strcat(buff, " "); strcat(buff, temp.getLastNameP());  strcat(buff, " "); strcat(buff, temp.getLastNameM());
			temp.setCompName(buff);
			//GetAge
			inlen = GetWindowTextLength(hEdtAge);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Edad.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 6) {
				MessageBox(hwnd, "La Edad es muy larga, debe tener menos de 6 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtAge, buff, inlen + 1);
			temp.setAge(atoi(buff));
			//GetBirthday
			time_t rawTime;
			tm validTime;
			time(&rawTime);
			validTime = *localtime(&rawTime);
			inlen = SendMessage(hCbDay, CB_GETCURSEL, 0, 0);
			if (inlen == -1) {
				MessageBox(hwnd, "Falta llenar el campo Día de nacimiento.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hCbDay, buff, 3);
			validTime.tm_mday = atoi(buff);
			inlen = SendMessage(hCbMonth, CB_GETCURSEL, 0, 0);
			if (inlen == -1) {
				MessageBox(hwnd, "Falta llenar el campo Mes de nacimiento.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hCbMonth, buff, 3);
			validTime.tm_mon = atoi(buff);
			inlen = GetWindowTextLength(hEdtYear);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Año de nacimiento.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 10) {
				MessageBox(hwnd, "El dato es muy largo, debe tener menos de 10 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtYear, buff, 5);
			validTime.tm_year = atoi(buff);
			validTime.tm_mon -= 1;
			validTime.tm_year -= 1900;
			mktime(&validTime);
			char num[6];
			char zero[3];
			strcpy(buff, "");
			if (validTime.tm_mday < 10) {
				strcpy(zero, "0");
				_itoa(validTime.tm_mday, num, 10); strcat(zero, num); strcat(buff, zero); strcat(buff, "/");
			}
			else {
				_itoa(validTime.tm_mday, num, 10); strcat(buff, num); strcat(buff, "/");
			}
			validTime.tm_mon += 1;
			if (validTime.tm_mon < 10) {
				strcpy(zero, "0");
				_itoa(validTime.tm_mon, num, 10);  strcat(zero, num); strcat(buff, zero); strcat(buff, "/");
			}
			else {
				_itoa(validTime.tm_mon, num, 10);  strcat(buff, num); strcat(buff, "/");
			}
			validTime.tm_year += 1900;
			_itoa(validTime.tm_year, num, 10); strcat(buff, num);
			temp.setBirthDate(buff);
			//GetGenre
			if (IsDlgButtonChecked(hwnd, RD_FEMALE) == BST_CHECKED) {
				temp.setGenre('M');
			}
			else {
				temp.setGenre('H');
			}
			//GetContact
			inlen = GetWindowTextLength(hEdtContact);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Teléfono de contacto.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen == 8 || inlen == 10)
				GetWindowText(hEdtContact, temp.getContact(), inlen + 1);
			else {
				MessageBox(hwnd, "Número telefónico invalido. La cantidad de caracteres debe ser de 8 o 10.", "Teléfono inválido", MB_ICONINFORMATION);
				break;
			}
			//GetFirstMedic
			inlen = SendMessage(hCbMed, CB_GETCURSEL, 0, 0);
			if (inlen == -1) {
				MessageBox(hwnd, "Falta llenar el campo Primer médico.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			inlen = GetWindowTextLength(hCbMed);
			GetWindowText(hCbMed, buff, inlen + 1);
			inlen = atoi(buff);
			Medico *med = listaMedicos.Search(listaMedicos.getRoot(), inlen, 0, 0);
			temp.setMed(med->compName);
			temp.setMedID(med->ced);
			//GetRef
			inlen = GetWindowTextLength(hEdtRef);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta llenar el campo Referencia.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > MAX_PATH) {
				MessageBox(hwnd, "La referencia es muy larga, debe tener menos de 260 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hEdtRef, temp.getRef(), inlen + 1);
			//PassID
			temp.setID(auxP->getData().getID());
			//PassUserID
			temp.setUserID(auxP->getData().getUserID());
			auxP->setData(temp);
			EndDialog(hwnd, 1);
		}
		break;
	}
	return FALSE;
}

BOOL CALLBACK agregarCita(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HWND hMcDate = GetDlgItem(hwnd, MC_DATEPANEL);
	HWND hLbPac = GetDlgItem(hwnd, LB_PAC);
	HWND hCbEsp = GetDlgItem(hwnd, CB_ESP);
	HWND hCbMed = GetDlgItem(hwnd, CB_MED);
	HWND hCbTime = GetDlgItem(hwnd, CB_TIME);
	switch (msg) {
	case WM_INITDIALOG: {
		hStUser = GetDlgItem(hwnd, ST_USERNAME);
		SetWindowText(hStUser, username);
		char id[10];
		_itoa(countD, id, 10);
		HWND hStId = GetDlgItem(hwnd, ST_DT_NODATE);
		SetWindowText(hStId, id);
		listaPacientes.PrintOnWindow(hLbPac, 0, NULL);
		listaEspecialidades.PrintOnWindow(hCbEsp, 1, NULL);
		SendMessage(hCbEsp, CB_INSERTSTRING, 0, (LPARAM)"Todas");
		EnableWindow(hCbMed, false);
		EnableWindow(hCbTime, false);
	}
	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL && HIWORD(wParam) == BN_CLICKED)
			EndDialog(hwnd, 0);
		if (LOWORD(wParam) == IDOK && HIWORD(wParam) == BN_CLICKED) {
			Cita temp;
			temp.setID(countD);
			//GetPatContactAndID
			int inlen = SendMessage(hLbPac, LB_GETCURSEL, 0, 0);
			if (inlen == -1) {
				MessageBox(hwnd, "Falta seleccionar el paciente.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			char buff[100];
			SendMessage(hLbPac, LB_GETTEXT, inlen, (LPARAM)buff);
			Paciente pat = listaPacientes.SearchNode(atoi(buff))->getData();
			temp.setPacID(pat.getID());
			temp.setPac(pat.getCompName());
			temp.setContact(pat.getContact());
			//GetMedicConsEspAndTime
			inlen = SendMessage(hCbMed, CB_GETCURSEL, 0, 0);
			if (inlen == -1) {
				MessageBox(hwnd, "Falta seleccionar el médico.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			inlen = GetWindowTextLength(hCbMed);
			GetWindowText(hCbMed, buff, inlen + 1);
			Medico med = *listaMedicos.Search(listaMedicos.getRoot(), atoi(buff), 0, 0);
			temp.setMedID(med.ced);
			temp.setMed(med.compName);
			temp.setEspID(med.espId);
			temp.setEsp(med.esp);
			temp.setCons(med.cons);
			temp.setMedSch(med.time);
			temp.setDirImage(med.dirImage);
			//GetDate
			SYSTEMTIME dateSel;
			SendMessage(hMcDate, MCM_GETCURSEL, 0, (LPARAM)&dateSel);
			time_t rawTime;
			tm dateTime;
			tm actualT;
			time(&rawTime);
			dateTime = *localtime(&rawTime);
			actualT = *localtime(&rawTime);
			dateTime.tm_year = dateSel.wYear - 1900;
			dateTime.tm_mon = dateSel.wMonth - 1;
			dateTime.tm_mday = dateSel.wDay;
			mktime(&dateTime);
			if (is_PassedDate(dateTime, actualT)) {
				MessageBox(hwnd, "La fecha que introdujo es antigua, coloque una fecha próxima.", "Fecha Invalida", MB_ICONINFORMATION);
				break;
			}
			dateTime.tm_year += 1900;
			dateTime.tm_mon += 1;
			temp.setDate(dateTime);
			//GetTime
			inlen = SendMessage(hCbTime, CB_GETCURSEL, 0, 0);
			if (inlen == -1) {
				MessageBox(hwnd, "Falta seleccionar la hora de la cita.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			GetWindowText(hCbTime, buff, inlen + 1);
			temp.setTime1(atoi(buff));
			if (IsDlgButtonChecked(hwnd, CH_SECONDTIME) == BST_CHECKED) {
				temp.setTime2(atoi(buff) + 1);
				if (temp.getTime2() == 15) {
					MessageBox(hwnd, "Seleccionaste la última hora, no hay espacio para la segunda hora.", "Sin espacio para segunda hora", MB_ICONINFORMATION);
					break;
				}
				if (is_SameDateTime(temp)) {
					MessageBox(hwnd, "El segundo tiempo solapa la hora de otra cita.", "Tiempo solapado", MB_ICONEXCLAMATION);
					break;
				}
			}
			countD++;
			//GetUserID
			temp.setUserID(gUserID);
			listaCitas.AddNode(temp);
			EndDialog(hwnd, 1);
		}
		if (LOWORD(wParam) == EDT_SEARCH && HIWORD(wParam) == EN_CHANGE) {
			HWND hEdtS = GetDlgItem(hwnd, EDT_SEARCH);
			int length = GetWindowTextLength(hEdtS);
			char buff[90];
			GetWindowText(hEdtS, buff, length + 1);
			listaPacientes.PrintOnWindow(hLbPac, 0, buff);
		}
		if (LOWORD(wParam) == CB_ESP && HIWORD(wParam) == CBN_SELCHANGE) {
			int index = SendMessage(hCbEsp, CB_GETCURSEL, 0, 0);
			if (index == 0) {
				EnableWindow(hCbMed, true);
				SendMessage(hCbMed, CB_RESETCONTENT, 0, 0);
				listaMedicos.printInOrderCb(hCbMed, listaMedicos.getRoot());
				break;
			}
			int length = GetWindowTextLength(hCbEsp);
			char buff[40];
			GetWindowText(hCbEsp, buff, length + 1);
			length = atoi(buff);
			EnableWindow(hCbMed, true);
			SendMessage(hCbMed, CB_RESETCONTENT, 0, 0);
			listaMedicos.printInOrderCbEsp(hCbMed, listaMedicos.getRoot(), length);
			SendMessage(hCbTime, CB_RESETCONTENT, 0, 0);
			EnableWindow(hCbTime, false);
		}
		if (LOWORD(wParam) == CB_MED && HIWORD(wParam) == CBN_SELCHANGE) {
			int length = GetWindowTextLength(hCbMed);
			char buff[100];
			GetWindowText(hCbMed, buff, length + 1);
			length = atoi(buff);
			Medico *aux = listaMedicos.Search(listaMedicos.getRoot(), length, 0, 0);
			hPcFoto = GetDlgItem(hwnd, BMP_MED);
			hBmpFoto = (HBITMAP)LoadImage(NULL, aux->dirImage, IMAGE_BITMAP, 85, 105, LR_LOADFROMFILE);
			SendMessage(hPcFoto, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmpFoto);
			EnableWindow(hCbTime, true);
			printTimes(hMcDate, hCbTime, aux, -1, -1);
		}
		break;
	case WM_NOTIFY:
		LPNMHDR lpNmHdr = (LPNMHDR)lParam;
		if (lpNmHdr->idFrom == MC_DATEPANEL && lpNmHdr->code == MCN_SELCHANGE) {
			int length = GetWindowTextLength(hCbMed);
			if (length > 0) {
				char buff[100];
				GetWindowText(hCbMed, buff, length + 1);
				length = atoi(buff);
				Medico *aux = listaMedicos.Search(listaMedicos.getRoot(), length, 0, 0);
				printTimes(hMcDate, hCbTime, aux, -1, -1);
			}
		}
		break;
	}
	return FALSE;
}

BOOL CALLBACK editarCita(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HWND hMcDate = GetDlgItem(hwnd, MC_DATEPANEL);
	HWND hLbPac = GetDlgItem(hwnd, LB_PAC);
	HWND hCbEsp = GetDlgItem(hwnd, CB_ESP);
	HWND hCbMed = GetDlgItem(hwnd, CB_MED);
	HWND hCbTime = GetDlgItem(hwnd, CB_TIME);
	switch (msg) {
	case WM_INITDIALOG: {
		hStUser = GetDlgItem(hwnd, ST_USERNAME);
		SetWindowText(hStUser, username);
		char buff[60];
		int index;
		Cita date = auxD->getData();
		_itoa(date.getID(), buff, 10);
		HWND hStId = GetDlgItem(hwnd, ST_DT_NODATE);
		SetWindowText(hStId, buff);
		listaPacientes.PrintOnWindow(hLbPac, 0, NULL);
		_itoa(date.getPacID(), buff, 10);
		index = SendMessage(hLbPac, LB_FINDSTRING, -1, (LPARAM)buff);
		SendMessage(hLbPac, LB_SETCURSEL, index, 0);
		listaEspecialidades.PrintOnWindow(hCbEsp, 1, NULL);
		_itoa(date.getEspID(), buff, 10);
		index = SendMessage(hCbEsp, CB_FINDSTRING, -1, (LPARAM)buff);
		SendMessage(hCbEsp, CB_SETCURSEL, index, 0);
		listaMedicos.printInOrderCbEsp(hCbMed, listaMedicos.getRoot(), date.getEspID());
		_itoa(date.getMedID(), buff, 10);
		index = SendMessage(hCbMed, CB_FINDSTRING, -1, (LPARAM)buff);
		SendMessage(hCbMed, CB_SETCURSEL, index, 0);
		SYSTEMTIME setDate;
		tm currDate = date.getDate();
		setDate.wYear = (WORD)currDate.tm_year;
		setDate.wMonth = (WORD)currDate.tm_mon;
		setDate.wDay = (WORD)currDate.tm_mday;
		setDate.wDayOfWeek = (WORD)currDate.tm_wday;
		setDate.wHour = 0;
		setDate.wMinute = 0;
		setDate.wSecond = 0;
		setDate.wMilliseconds = 0;
		index = SendMessage(hMcDate, MCM_SETCURSEL, 0, (LPARAM)&setDate);
		Medico *med = listaMedicos.Search(listaMedicos.getRoot(), date.getMedID(), 0, 0);
		printTimes(hMcDate, hCbTime, med, date.getTime1(), date.getTime2());
		_itoa(date.getTime1(), buff, 10);
		index = SendMessage(hCbTime, CB_FINDSTRING, 0, (LPARAM)buff);
		SendMessage(hCbTime, CB_SETCURSEL, index, 0);
		if (date.getTime2() != -1)
			CheckDlgButton(hwnd, CH_SECONDTIME, BST_CHECKED);
		hPcFoto = GetDlgItem(hwnd, BMP_MED);
		hBmpFoto = (HBITMAP)LoadImage(NULL, date.getDirImage(), IMAGE_BITMAP, 85, 105, LR_LOADFROMFILE);
		SendMessage(hPcFoto, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmpFoto);
	}
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL && HIWORD(wParam) == BN_CLICKED)
			EndDialog(hwnd, 0);
		if (LOWORD(wParam) == IDOK && HIWORD(wParam) == BN_CLICKED) {
			Cita temp;
			temp.setID(auxD->getData().getID());
			//GetPatContactAndID
			int inlen = SendMessage(hLbPac, LB_GETCURSEL, 0, 0);
			if (inlen == -1) {
				MessageBox(hwnd, "Falta seleccionar el paciente.", "Campos Incompletos", MB_ICONEXCLAMATION);
				break;
			}
			char buff[50];
			SendMessage(hLbPac, LB_GETTEXT, inlen, (LPARAM)buff);
			Paciente pat = listaPacientes.SearchNode(atoi(buff))->getData();
			temp.setPacID(pat.getID());
			temp.setPac(pat.getCompName());
			temp.setContact(pat.getContact());
			//GetMedicConsEspAndTime
			inlen = GetWindowTextLength(hCbMed);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta seleccionar el médico.", "Campos Incompletos", MB_ICONEXCLAMATION);
				break;
			}
			GetWindowText(hCbMed, buff, inlen + 1);
			Medico med = *listaMedicos.Search(listaMedicos.getRoot(), atoi(buff), 0, 0);
			temp.setMedID(med.ced);
			temp.setMed(med.compName);
			temp.setEspID(med.espId);
			temp.setEsp(med.esp);
			temp.setCons(med.cons);
			temp.setMedSch(med.time);
			temp.setDirImage(med.dirImage);
			//GetDate
			SYSTEMTIME dateSel;
			SendMessage(hMcDate, MCM_GETCURSEL, 0, (LPARAM)&dateSel);
			time_t rawTime;
			tm dateTime;
			tm actualT;
			time(&rawTime);
			dateTime = *localtime(&rawTime);
			actualT = *localtime(&rawTime);
			dateTime.tm_year = dateSel.wYear - 1900;
			dateTime.tm_mon = dateSel.wMonth - 1;
			dateTime.tm_mday = dateSel.wDay;
			mktime(&dateTime);
			if (is_PassedDate(dateTime, actualT)) {
				MessageBox(hwnd, "La fecha que introdujo es antigua, coloque una fecha próxima.", "Fecha Invalida", MB_ICONINFORMATION);
				break;
			}
			dateTime.tm_year += 1900;
			dateTime.tm_mon += 1;
			temp.setDate(dateTime);
			//GetTime
			inlen = GetWindowTextLength(hCbTime);
			if (inlen == 0) {
				MessageBox(hwnd, "Falta seleccionar la hora de la cita.", "Campos Incompletos", MB_ICONEXCLAMATION);
				break;
			}
			GetWindowText(hCbTime, buff, inlen + 1);
			temp.setTime1(atoi(buff));
			if (IsDlgButtonChecked(hwnd, CH_SECONDTIME) == BST_CHECKED) {
				temp.setTime2(atoi(buff) + 1);
				if (temp.getTime2() == 15) {
					MessageBox(hwnd, "Seleccionaste la última hora, no hay espacio para la segunda hora.", "Sin espacio para segunda hora", MB_ICONINFORMATION);
					break;
				}
				if (is_SameDateTime(temp)) {
					MessageBox(hwnd, "El segundo tiempo solapa la hora de otra cita.", "Tiempo solapado", MB_ICONEXCLAMATION);
					break;
				}
			}
			//PassUserID
			temp.setUserID(auxD->getData().getUserID());
			auxD->setData(temp);
			EndDialog(hwnd, 1);
		}
		if (LOWORD(wParam) == EDT_SEARCH && HIWORD(wParam) == EN_CHANGE) {
			HWND hEdtS = GetDlgItem(hwnd, EDT_SEARCH);
			int length = GetWindowTextLength(hEdtS);
			char buff[60];
			GetWindowText(hEdtS, buff, length + 1);
			listaPacientes.PrintOnWindow(hLbPac, 0, buff);
		}
		if (LOWORD(wParam) == CB_ESP && HIWORD(wParam) == CBN_SELCHANGE) {
			int index = SendMessage(hCbEsp, CB_GETCURSEL, 0, 0);
			if (index == 0) {
				EnableWindow(hCbMed, true);
				SendMessage(hCbMed, CB_RESETCONTENT, 0, 0);
				listaMedicos.printInOrderCb(hCbMed, listaMedicos.getRoot());
				break;
			}
			int length = GetWindowTextLength(hCbEsp);
			char buff[30];
			GetWindowText(hCbEsp, buff, length + 1);
			length = atoi(buff);
			EnableWindow(hCbMed, true);
			SendMessage(hCbMed, CB_RESETCONTENT, 0, 0);
			listaMedicos.printInOrderCbEsp(hCbMed, listaMedicos.getRoot(), length);
			SendMessage(hCbTime, CB_RESETCONTENT, 0, 0);
			EnableWindow(hCbTime, false);
		}
		if (LOWORD(wParam) == CB_MED && HIWORD(wParam) == CBN_SELCHANGE) {
			int length = GetWindowTextLength(hCbMed);
			char buff[30];
			GetWindowText(hCbMed, buff, length + 1);
			length = atoi(buff);
			Medico *aux = listaMedicos.Search(listaMedicos.getRoot(), length, 0, 0);
			hPcFoto = GetDlgItem(hwnd, BMP_MED);
			hBmpFoto = (HBITMAP)LoadImage(NULL, aux->dirImage, IMAGE_BITMAP, 85, 105, LR_LOADFROMFILE);
			SendMessage(hPcFoto, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmpFoto);
			EnableWindow(hCbTime, true);
			printTimes(hMcDate, hCbTime, aux, -1, -1);
		}
		break;
	case WM_NOTIFY:
		LPNMHDR lpNmHdr = (LPNMHDR)lParam;
		if (lpNmHdr->idFrom == MC_DATEPANEL && lpNmHdr->code == MCN_SELCHANGE) {
			int length = GetWindowTextLength(hCbMed);
			if (length > 0) {
				char buff[30];
				GetWindowText(hCbMed, buff, length + 1);
				length = atoi(buff);
				Medico *aux = listaMedicos.Search(listaMedicos.getRoot(), length, 0, 0);
				printTimes(hMcDate, hCbTime, aux, -1, -1);
			}
		}
		break;
	}
	return FALSE;
}

BOOL CALLBACK confirmarCita(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG: {
		CheckDlgButton(hwnd, RD_CONFIRM, BST_CHECKED);
	}
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL && HIWORD(wParam) == BN_CLICKED)
			EndDialog(hwnd, 0);
		if (LOWORD(wParam) == IDOK && HIWORD(wParam) == BN_CLICKED) {
			if (IsDlgButtonChecked(hwnd, RD_CONFIRM) == BST_CHECKED) {
				Cita temp = auxD->getData();
				temp.setState(1);
				auxD->setData(temp);
			}
			else {
				Cita temp = auxD->getData();
				HWND hEdtMotive = GetDlgItem(hwnd, EDT_MOTIVE);
				int length = GetWindowTextLength(hEdtMotive);
				if (length == 0) {
					MessageBox(hwnd, "Escriba el motivo de cancelación.", "Campos Incompletos", MB_ICONINFORMATION);
					break;
				}
				if (length > MAX_PATH) {
					MessageBox(hwnd, "Límite de caracteres alcanzado.", "Exceso de Caracteres", MB_ICONINFORMATION);
					break;
				}
				char buff[MAX_PATH];
				GetWindowText(hEdtMotive, buff, length + 1);
				temp.setState(2);
				temp.setMotive(buff);
				auxD->setData(temp);
			}
			EndDialog(hwnd, 1);
		}
		break;
	}
	return FALSE;
}

BOOL CALLBACK consultaMedMes(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HWND hCbMonth = GetDlgItem(hwnd, CB_MONTH);
	switch (msg) {
	case WM_INITDIALOG: {
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"01");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"02");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"03");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"04");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"05");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"06");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"07");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"08");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"09");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"10");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"11");
		SendMessage(hCbMonth, CB_ADDSTRING, 0, (LPARAM)"12");
	}
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL && HIWORD(wParam) == BN_CLICKED) {
			EndDialog(hwnd, 0);
		}
		if (LOWORD(wParam) == IDOK && HIWORD(wParam) == BN_CLICKED) {
			HWND hStMed = GetDlgItem(hwnd, ST_MEDNAME);
			int inlen = GetWindowTextLength(hStMed);
			if (inlen == 0) {
				MessageBox(hwnd, "Aún no se ha seleccionado el médico para realizar la búsqueda.", "Médico no seleccionado", MB_ICONINFORMATION);
				break;
			}
			HWND hCbMonth = GetDlgItem(hwnd, CB_MONTH);
			inlen = SendMessage(hCbMonth, CB_GETCURSEL, 0, 0);
			if (inlen == -1) {
				MessageBox(hwnd, "Seleccione un mes para realizar la búsqueda.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			inlen = GetWindowTextLength(hCbMonth);
			char buff[MAX_PATH];
			GetWindowText(hCbMonth, buff, inlen + 1);
			inlen = atoi(buff);
			strcpy(buff, "");
			OPENFILENAME ofnFile;
			ZeroMemory(&ofnFile, sizeof(ofnFile));
			ofnFile.hwndOwner = hwnd;
			ofnFile.lStructSize = sizeof(ofnFile);
			ofnFile.lpstrFile = buff;
			ofnFile.nMaxFile = MAX_PATH;
			ofnFile.lpstrDefExt = "txt";
			ofnFile.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
			ofnFile.lpstrFilter = "Text File\0*.txt\0";
			if (GetSaveFileName(&ofnFile)) {
				ofstream dateCons; dateCons.open(buff, ios::out);
				if (dateCons.is_open()) {
					Node<Cita>* date = listaCitas.getFirst();
					while (date != NULL) {
						Cita comp = date->getData();
						if (comp.getMedID() == auxMC.ced & comp.getDate().tm_mon == inlen & comp.getState() == 0) {
							dateCons << comp;
						}
						date = date->getNext();
					}
				}
				dateCons.close();
			}
			EndDialog(hwnd, 1);
		}
		if (LOWORD(wParam) == BTN_SEARCH && HIWORD(wParam) == BN_CLICKED) {
			int n = 0; listaMedicos.countList(n, listaMedicos.getRoot());
			Medico *arr = new Medico[n];
			int i = 0;
			buildMedicArray(arr, i, listaMedicos.getRoot());
			HWND hEdtMed = GetDlgItem(hwnd, EDT_MED);
			int inlen = GetWindowTextLength(hEdtMed);
			if (inlen == 0) {
				MessageBox(hwnd, "Introduzca una cédula para buscar al médico.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			if (inlen > 20) {
				MessageBox(hwnd, "La cédula introducida es muy larga, debe tener menos de 20 caracteres.", "Exceso de Caracteres", MB_ICONINFORMATION);
				break;
			}
			char buff[90];
			GetWindowText(hEdtMed, buff, inlen + 1);
			inlen = atoi(buff);
			int res = binarySearchMed(arr, 0, n, inlen);
			if (res == -1) {
				MessageBox(hwnd, "No existe médico registrado con esta cédula.", "Médico no encontrado", MB_ICONINFORMATION);
				break;
			}
			auxMC = arr[res];
			HWND hStMed = GetDlgItem(hwnd, ST_MEDNAME);
			HWND hStEsp = GetDlgItem(hwnd, ST_ESP);
			SetWindowText(hStMed, auxMC.compName);
			SetWindowText(hStEsp, auxMC.esp);
		}
		break;
	}
	return FALSE;
}

BOOL CALLBACK consultaSem(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG: {

	}
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL && HIWORD(wParam) == BN_CLICKED) {
			EndDialog(hwnd, 0);
		}
		if (LOWORD(wParam) == IDOK && HIWORD(wParam) == BN_CLICKED) {
			HWND hMcWeek = GetDlgItem(hwnd, MCM_WEEKSELECTOR);
			SYSTEMTIME dateW;
			SendMessage(hMcWeek, MCM_GETCURSEL, 0, (LPARAM)&dateW);
			time_t rawTime;
			tm weekD;
			time(&rawTime);
			weekD = *localtime(&rawTime);
			weekD.tm_mday = dateW.wDay;
			weekD.tm_mon = dateW.wMonth;
			weekD.tm_year = dateW.wYear;
			weekD.tm_mon -= 1;
			weekD.tm_year -= 1900;
			mktime(&weekD);
			char buff[MAX_PATH] = "";
			OPENFILENAME ofnFile;
			ZeroMemory(&ofnFile, sizeof(ofnFile));
			ofnFile.hwndOwner = hwnd;
			ofnFile.lStructSize = sizeof(ofnFile);
			ofnFile.lpstrFile = buff;
			ofnFile.nMaxFile = MAX_PATH;
			ofnFile.lpstrDefExt = "txt";
			ofnFile.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
			ofnFile.lpstrFilter = "Text File\0*.txt\0";
			if (GetSaveFileName(&ofnFile)) {
				ofstream dateCons; dateCons.open(buff, ios::out);
				if (dateCons.is_open()) {
					int n = countDates(week_number(weekD));
					Cita *arr = new Cita[n];
					buildDatesArray(arr, week_number(weekD));
					QuickSortD(arr, 0, n - 1);
					for (int i = 0; i < n; i++) {
						dateCons << arr[i];
					}
				}
				dateCons.close();
			}
			EndDialog(hwnd, 1);
		}
		break;
	}
	return FALSE;
}

BOOL CALLBACK consultaEspSem(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HWND hCbEsp = GetDlgItem(hwnd, CB_ESP);
	switch (msg) {
	case WM_INITDIALOG: {
		listaEspecialidades.PrintOnWindow(hCbEsp, 1, NULL);
	}
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL && HIWORD(wParam) == BN_CLICKED) {
			EndDialog(hwnd, 0);
		}
		if (LOWORD(wParam) == IDOK && HIWORD(wParam) == BN_CLICKED) {
			int inlen = SendMessage(hCbEsp, CB_GETCURSEL, 0, 0);
			if (inlen == -1) {
				MessageBox(hwnd, "No se ha seleccionado una especialidad para iniciar la búsqueda.", "Campos Incompletos", MB_ICONINFORMATION);
				break;
			}
			inlen = GetWindowTextLength(hCbEsp);
			char buff[MAX_PATH];
			GetWindowText(hCbEsp, buff, inlen + 1);
			inlen = atoi(buff);
			HWND hMcWeek = GetDlgItem(hwnd, MCM_WEEKSELECTOR);
			SYSTEMTIME dateW;
			SendMessage(hMcWeek, MCM_GETCURSEL, 0, (LPARAM)&dateW);
			time_t rawTime;
			tm weekD;
			time(&rawTime);
			weekD = *localtime(&rawTime);
			weekD.tm_mday = dateW.wDay;
			weekD.tm_mon = dateW.wMonth;
			weekD.tm_year = dateW.wYear;
			weekD.tm_mon -= 1;
			weekD.tm_year -= 1900;
			mktime(&weekD);
			strcpy(buff, "");
			OPENFILENAME ofnFile;
			ZeroMemory(&ofnFile, sizeof(ofnFile));
			ofnFile.hwndOwner = hwnd;
			ofnFile.lStructSize = sizeof(ofnFile);
			ofnFile.lpstrFile = buff;
			ofnFile.nMaxFile = MAX_PATH;
			ofnFile.lpstrDefExt = "txt";
			ofnFile.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
			ofnFile.lpstrFilter = "Text File\0*.txt\0";
			if (GetSaveFileName(&ofnFile)) {
				ofstream dateCons; dateCons.open(buff, ios::out);
				if (dateCons.is_open()) {
					Node<Cita>* date = listaCitas.getFirst();
					while (date != NULL) {
						Cita comp = date->getData();
						if (week_number(comp.getDate()) == week_number(weekD) & comp.getEspID() == inlen & comp.getState() == 0) {
							dateCons << comp;
						}
						date = date->getNext();
					}
				}
				dateCons.close();
			}
			EndDialog(hwnd, 1);
		}
		break;
	}
	return FALSE;
}
#pragma endregion