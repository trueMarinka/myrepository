#include <iostream>
#include<direct.h> // изменение папок 
#include<io.h> // поиск файлов
#include<Windows.h>
#include<string>
#include<conio.h>
#include<vector>

using namespace std;


void UpdateMenu();
void RedrawDirectory();
void SetConsoleCursorPosition(short x_position, short y_position);
enum VKey { BACKSPACE = 8, ENTER = 13, MVK_UP = 72, MVK_DOWN = 80 };
int pos_x = 0, pos_y = 0;


class File{
public:
	File *parent;
	string name;
	int size, time;
	vector<File> file_arr;
	string path;
	string type;


	File(string _path) {
		path = _path;
		type = "";
		name = "";
		size = time = 0;
	}

	void Print() {
		cout << endl;
		for (int i = 0; i < file_arr.size(); i++) {
			cout << " " << file_arr[i].name<< endl;
		}
	}

	void Scan() {
		_finddata_t *file_info = new _finddata_t;
		string path_mask = path + "*.*";
		int done = _findfirst(path_mask.c_str(), file_info);

		int go = done;
		while (go != -1) {
			AnsiToOem(file_info->name, file_info->name);		// для файлов с русскими именами
			if (file_info->name[0] == '.') {
				go = _findnext(done, file_info);
				continue;
			}

			File f(path);
			f.name = file_info->name;
			f.parent = this;

			if (file_info->attrib == _A_SUBDIR) {
				f.type = "d";
			}
			else {
				f.type = "f";
				f.size = file_info->size;
				f.time = file_info->time_create;
			}

			file_arr.push_back(f);

			go = _findnext(done, file_info);
		}

		_findclose(done);
		delete file_info;
	}

	File * get_file_by_caret_id() {
		if (&file_arr[pos_y - 3] != NULL) {
			return &file_arr[pos_y - 3];
		}
		return NULL;
	}
};

File *active_dir;

void main() {
	int btn = 0;
	string disk;
	string path;

	UpdateMenu();

	for (;;) {
		SetConsoleCursorPosition(pos_x, pos_y);
		if (kbhit) {
			btn = getch();
		}

		if (btn == ENTER) {
			switch (pos_y) {
			case 0:
				cin >> disk;
				path = disk + ":/";
				active_dir = new File(path);
				active_dir->name = disk;
				active_dir->Scan();
				RedrawDirectory();
				break;
			case 1:
				return;
			default:
				File * clicked_file = active_dir->get_file_by_caret_id();
				clicked_file->path = active_dir->path + clicked_file->name + "/";
				if (clicked_file != NULL) {
					active_dir = clicked_file;
					if (clicked_file->type == "d") {
						active_dir->Scan();
						RedrawDirectory();
					}
					if (clicked_file->type == "f") {
						UpdateMenu();
						cout << endl << clicked_file->name << " size: " << clicked_file->size << " time_create: " << clicked_file->time << endl;
					}
				}
			}
			continue;
		}

		if (btn == BACKSPACE) {
			if (active_dir->path != disk + ":/") {
				active_dir = active_dir->parent;
				RedrawDirectory();
				continue;		
			}
			else {
				return;
			}

		} 

		if (btn == 0xe0) {
			btn = getch();
			switch (btn) {
			case MVK_UP:
				pos_y--;
				SetConsoleCursorPosition(pos_x, pos_y);
				break;
			case MVK_DOWN:
				pos_y++;
				SetConsoleCursorPosition(pos_x, pos_y);
				break;
			}
		}
	}
}

void RedrawDirectory() {
	UpdateMenu();
	active_dir->Print();
}

void UpdateMenu() {
	system("cls");
	cout << "  Enter disk" << endl;
	cout << "  Exit" << endl;
}

void SetConsoleCursorPosition(short x_position, short y_position) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD _coordPosition = { x_position, y_position };
	SetConsoleCursorPosition(hConsole, _coordPosition);
}

