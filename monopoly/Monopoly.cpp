#include<Windows.h>
#include<stdlib.h>
#include<string>
#include<tchar.h>
#include<vector>
#include<iostream>
#include<cstdio>
#include<list>
#include<time.h>
#include <io.h>
#pragma comment(lib,"Winmm.lib")
using namespace std;
static TCHAR WindowsClass[] = "win32app";
static TCHAR Title[] = "MyWindow";
HINSTANCE hinst;

#define ID_BUTTON1 1001
#define ID_BUTTON2 1002
#define ID_BUTTON3 1003
#define ID_BUTTON4 1004
#define ID_BUTTON5 1005
#define ID_EDIT1 100
#define ID_EDIT2 101
#define ID_EDIT3 102
#define ID_EDIT4 103
#define ID_EDIT5 104
#define ID_CHECK 7001
#define ID_EDIT1 10001
	




LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);				// для дочернего окна
HWND btnBRAS,editRez,btnPlay1,btnPlay2,editMany1,editMany2,editNews1,editNews2,checkbox,btnKup1,btnKup2;
HMENU hMenubar, hMenu;
int window_y_pos;



int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpcmdLine, int nCmdShow) {	// описание окна
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;		// стиль для отлавливания даблклика
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION)); // стандартная иконка виндовс
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//wcex.hbrBackground = CreateSolidBrush(RGB(100, 70, 150));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WindowsClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex)) {	// если не удалось создать окно
		MessageBox(NULL, "CAll failed!", "MyWindow", NULL);
		return 1;
	}

	hinst = hinstance;
	HWND hwnd = CreateWindow(
		WindowsClass,
		Title,
		WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,
		125, 10, 1100, 700,		// х у ширина высота
		NULL, NULL,
		hinst, NULL);

	if (!hwnd) {
		MessageBox(NULL, "CAll failed!", "MyWindow", NULL);
		return 1;
	}

	ShowWindow(hwnd, nCmdShow);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}



	return (int)msg.wParam;
}
bool xod=true,sound=false;
int z=0,c=0,h=0,d=0;//тек положение игрока
int Many1=100;//деньги игроков
int Many2=100;
int q=0;
int zagr=0;
int masCen[]={0,60,100,60,120,0,80,150,0,220,120,100,80,0,160,200};//массив цен используется для заполнения массива firma
int masShtr[]={0,10,20,10,20,0,10,25,0,50,20,15,10,0,30,35};//массив штрафов
struct Citat{
	char lin[300];
	};
struct News{
	char news[256];
	int many;
	};
struct Brend{            //структура котороя содержит все дание игрового поля
	int stoim;              // стоимость предприятия
	int shtraf;             // Штраф
	HWND edit;               // хендлер edit для передачи в игровое поле имени владельца 
	char name[15];          // И название предприятия, на всякий случай может пригодится))))
    char player[15];          // имя владельца
	};

Brend firma[16];//******** Массив всех полей игравого поля

struct Pos{
	int x;
	int y;
};

//class Cell {
//	string name;
//	string owner;
//	int cost;
//	int penalty;
//
//public:
//
//	Cell() {
//		name = "";
//		owner = "";
//		cost = 0;
//		penalty = 0;
//	}
//
//	void SetName(string s) {
//		name = s;
//	}
//
//	void SetOwner(string s) {
//		owner = s;
//	}
//
//	void SetCost(int n) {
//		cost = n;
//	}
//
//	void SetPenalty(int n) {
//		penalty = n;
//	}
//
//	int GetCost() {
//		return cost;
//	}
//
//	int GetPenalty() {
//		return penalty;
//	}
//
//	string GetName() {
//		return name;
//	}
//
//	string GetOwner() {
//		return owner;
//	}
//
//};

//class Person {
//	string name;
//	int money;
//public:
//	Person() {
//		name = "";
//		money = 1000;
//	}
//
//	void SetName(string s) {
//		name = s;
//	}
//
//	void SetMoney(int n) {
//		money = n;
//	}
//
//	string GetName() {
//		return name;
//	}
//
//	int GetMoney() {
//		return money;
//	}
//};

//list<Cell>listbox_arr;
//int size = 20;
//
//void SetArr() {
//	int id = 500;
//	for (int i = 0; i < size; i++, id++) {
//		listbox_arr.push_back(new Cell());
//	}
//}



LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hDC, hCompatibleDC;
    PAINTSTRUCT PaintStruct;
    HANDLE hBitmap, hOldBitmap,hBitmapP1,hBitmapP2,hBitShtrP1,hBitShtrP2/*,hBitPropP1,hBitPropP2*/,hBitKupP1,hBitKupP2;
    RECT Rect;
    BITMAP Bitmap;
	srand(time(NULL));
		
		
    static Citat linux[4];                         // Массив цитат для  Линуса 
	
	strcpy(linux[0].lin,"Моё имя Линус, и я ваш Бог");
	strcpy(linux[1].lin,"Microsoft — не есть зло, просто у них по-настоящему паршивые операционные системы.");
	strcpy(linux[2].lin,"Интеллект — это способность избегать выполнения работы, но так, чтобы она при этом была сделана");
	strcpy(linux[3].lin,"Философия Линукса: \"Смейся в лицо опасности\". Ой. Не то. \"Сделай сам\". Да, правильно.");
	
    static News masNews[6];                               // массив для событий в поле шанс
	
	strcpy(masNews[0].news," Ваш старый умирающий Macbook, оставил Вам наследство! Получи 50$");
	strcpy(masNews[1].news," Вы получили грант на разработку ПО под расческу для усов! Получи 20$");
	strcpy(masNews[2].news," Ваш IBM 3  на 27% состоит из золота! Получи 30$");
	strcpy(masNews[3].news," Вы получили нобелевскую премию за вклад в развитие игры МОНОПОЛИЯ! Получи 25$");
	strcpy(masNews[4].news," Вы никогда не платили за лицензионное ПО. За наглость получи 15$");
	strcpy(masNews[5].news," Вы написали приложение без единого бага!!! За хорошую фантазию 40$");
	masNews[0].many=50;
	masNews[1].many=20;
	masNews[2].many=30;
	masNews[3].many=25;
	masNews[4].many=15;
	masNews[5].many=40;
	
	static News masBad[6];                       // массив для событий в поле БАГ
	
	strcpy(masBad[0].news," Вы наконец решили заменить шариковую мышку! Новая мышь -10$");
	strcpy(masBad[1].news," Работая со сложным кодом, Вы вывихнули  кисть руки! Лечение -20$");
	strcpy(masBad[2].news," Вы пили пиво и меняли пароли! Восстановление системы -25$");
	strcpy(masBad[3].news," Вы написали крутую хакерскую программу! Решение суда: штраф -30$");
	strcpy(masBad[4].news," Никогда, никогда не пейте кофе над ноутбуком! Новый ноут -40$");
	strcpy(masBad[5].news," В казино вы всегда ставили на 0 или 1! Плохая система -50$");
	masBad[0].many=-10;
	masBad[1].many=-20;
	masBad[2].many=-25;
	masBad[3].many=-30;
	masBad[4].many=-40;
	masBad[5].many=-50;
	

	hBitmapP1 = LoadImage(NULL, "pic1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);    //Присвоение хендлиров рисунков фишек
	hBitmapP2 = LoadImage(NULL, "pic_2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	        //***************************************эти хэндлеры часть не удачного эксперимента (потуги анимации фишек)  Оставил что б если что ты могла тож побаловаться, в итоге можно удалить
	//hBitShtrP1 = LoadImage(NULL, "picShtr1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); //рисунок фишки при попадании игрока на купленое поле
	//hBitShtrP2 = LoadImage(NULL, "picShtr2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//hBitPropP1 = LoadImage(NULL, "picProp1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//Вид фишки при пропуске хода
	//hBitPropP2 = LoadImage(NULL, "picProp2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//hBitKupP1 = LoadImage(NULL, "picKup1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); //вид фишуи при  возможности купить
	//hBitKupP2 = LoadImage(NULL, "picKup2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	
	
	
	// создаем массив с координатами для перемещения игровых фишек
static  Pos mas[16];

mas[14].x=mas[15].x=mas[13].x=mas[0].x=980;
mas[5].y=mas[4].y=mas[3].y=mas[2].y=mas[1].y=mas[0].y=600;
mas[12].x=mas[1].x=800;
mas[11].x=mas[2].x=600;
mas[10].x=mas[3].x=420;
mas[9].x=mas[4].x=220;
mas[5].x=mas[6].x=mas[7].x=mas[8].x=55;
mas[15].y=mas[6].y=440;
mas[14].y=mas[7].y=250;
mas[8].y=mas[9].y=mas[10].y=mas[11].y=mas[12].y=mas[13].y=10;

//*********конец масива координат*************

static  Pos masEd[16];                           //Массив для координат edit для записи имени владельцев 

masEd[0].x=masEd[5].x=masEd[8].x=masEd[13].x=-40;// в игровом поле
masEd[0].y=masEd[5].y=masEd[8].y=masEd[13].y=-40;
masEd[1].x=830;
masEd[4].y=masEd[1].y=555;
masEd[2].x=645;
masEd[2].y=550;
masEd[3].x=455;
masEd[3].y=559;
masEd[4].x=255;
masEd[6].y=373;
masEd[7].x=masEd[6].x=75;
masEd[7].y=196;
masEd[11].y=masEd[10].y=masEd[9].y=87;
masEd[9].x=275;
masEd[10].x=455;
masEd[11].x=635;
masEd[12].x=835;
masEd[12].y=85;
masEd[15].x=masEd[14].x=1008;
masEd[14].y=214;
masEd[15].y=374;

//***********конец массива координат******************


	switch (message) {
	case WM_COMMAND:

		if(strcmp(firma[z].player,"нет")==0){                     // Отслежует возможность покупки для 1 игрока
			EnableWindow(btnKup1, 1);
			}else{
				EnableWindow(btnKup1, 0);
			}
		if(strcmp(firma[c].player,"нет")==0){                  // Отслежует возможность покупки для 1 игрока
			EnableWindow(btnKup2, 1);
			}else{
				EnableWindow(btnKup2, 0);
			}

		if (LOWORD(wParam) == ID_BUTTON4){                     // типа покупка  1го игрока
		
			strcpy(firma[z].player,"1 Игрок");
			SendMessage(firma[z].edit, WM_SETTEXT, 0, (LPARAM)firma[z].player);
			return 0;
		}

		if (LOWORD(wParam) == ID_BUTTON5){                       // типа покупка  2го игрока
		
			strcpy(firma[c].player,"2 Игрок");
			SendMessage(firma[c].edit, WM_SETTEXT, 0, (LPARAM)firma[c].player);
			return 0;
		}
		if (LOWORD(wParam) == ID_BUTTON3){                      // Генератор цитат))))))
			if(q>=4)q=0;
		MessageBox(btnPlay2,linux[q].lin , "Цитаты", FALSE);
		q++;
		}

		if (LOWORD(wParam) == ID_CHECK){                          //Включение звука
			auto res = SendMessage(checkbox, BM_GETCHECK, 0, 0);
			if (res == BST_CHECKED){
				sound=true;}
			if (res == BST_UNCHECKED){
				sound=false;}
		}

		if (LOWORD(wParam) == ID_BUTTON2) {
			if(d==0){                                                       // А это прикольный сикрет
				PlaySound( "start.wav", NULL, SND_ASYNC | SND_FILENAME );
				d++;
			}else { 
				PlaySound( NULL, NULL, SND_FILENAME );
				d=0;
			}
		}
		//*****************начало хода************************************
		if (LOWORD(wParam) ==ID_BUTTON1){ //Здесь примитивный алгоритм ходов , выполнение пропуска хода и отработка карточек в поле Шанс и Баг
			                           // Приметивный потому что, повторяется для каждого игрока
				                          //Это я сделал для наглядности, при желании меняй
			
        if(sound==true){PlaySound( "kosti.wav", NULL, SND_ASYNC | SND_FILENAME );}
		//int B=rand()%11+2;                // !для лучшего баланса игры  поменял диапазон кубика
        int B=rand()%6+1;                   // с 2-12 на 1-6 но это не столь важно!
		char s[10];                        
		itoa(B, s, 10);                 
		SendMessage(editRez, WM_SETTEXT, 0, (LPARAM)s);          // Вывод на экран очков за бросок кубика

		// ********************ход первого игрока
		if(xod==true){//булевая переменая xod нужна для чередования хода между игроками
			z+=B;
			if(z>=16){
				z-=16;
				Many1+=50; //получение денег за пойденный круг
			}
			if(strcmp(firma[z].player,"нет")==0){
			EnableWindow(btnKup1, 1);
			}else{
				EnableWindow(btnKup1, 0);
			}
		 MoveWindow(btnPlay1,  mas[z].x-35, mas[z].y, 60, 60, TRUE);
		 if(z==8){
		  if(sound==true){PlaySound( "Prop.wav", NULL, SND_ASYNC | SND_FILENAME );}  
          SendMessage(editNews1, WM_SETTEXT, 0, (LPARAM)" Посиди , подумай");
		 }
		 if(c==8&&h==0){// пропуск хода игрок 1
			   //звуковой эфект
				h++;
			//	DeleteObject(hBitmapP2);
			// SendMessage (btnPlay2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitPropP2);     //смена изображения  фишки при пропуске хода(к сожалению работает не очень стабильно)
				break;                                                                      //можешь проверить у себя. Баг появвляется после 15-20 бросков.  этот баг--- утечка памяти. около 8 часов пытался исправить не получилось
		 }
		 else{
			// DeleteObject(hBitPropP1);
			//SendMessage (btnPlay2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmapP2);        //возврат обычного изображения
			 h=0;
		 }
		 if(z==5){
			 if(sound==true){PlaySound( "good.wav", NULL, SND_ASYNC | SND_FILENAME );} //звуковой эфект
			 int a=rand()%6;
			
		     SendMessage(editNews1, WM_SETTEXT, 0, (LPARAM)masNews[a].news);
			 Many1+=masNews[a].many;
		 }
		 if(z==13){
			 if(sound==true){PlaySound( "bad.wav", NULL, SND_ASYNC | SND_FILENAME );}//звуковой эфект
		 int a=rand()%6;
		
		 SendMessage(editNews1, WM_SETTEXT, 0, (LPARAM)masBad[a].news);
		 Many1+=masBad[a].many;
		
		 }
		 xod=false;
		}
		// ********************ход Второго игрока
		else if(xod==false){
			c+=B;
			if(c>=16){
				c-=16;
				Many2+=50;//получение денег за пойденный круг
			}
			
			MoveWindow(btnPlay2,  mas[c].x+35, mas[c].y, 60, 60, TRUE);
			if(c==8){
				if(sound==true){PlaySound( "Prop.wav", NULL, SND_ASYNC | SND_FILENAME );}//звуковой эфект
                SendMessage(editNews2, WM_SETTEXT, 0, (LPARAM)" Посиди , подумай");
			}
			if(z==8&&h==0){//пропуск хода для второго игрока
				 
				h++;
				//DeleteObject(hBitmapP2);
				//SendMessage (btnPlay1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitPropP1);
				break;
			}
			else{
				//DeleteObject(hBitPropP1);
				//SendMessage (btnPlay1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmapP1);
				h=0;
			}
			 if(c==5){
				  if(sound==true){PlaySound( "good.wav", NULL, SND_ASYNC | SND_FILENAME );} //звуковой эфект
			 int y=rand()%6;
			
		     SendMessage(editNews2, WM_SETTEXT, 0, (LPARAM)masNews[y].news);
			 Many2+=masNews[y].many;
		 }
		 if(c==13){
            if(sound==true){PlaySound( "bad.wav", NULL, SND_ASYNC | SND_FILENAME );}      //звуковой эфект
		 int y=rand()%6;
	
		 SendMessage(editNews2, WM_SETTEXT, 0, (LPARAM)masBad[y].news);
		 Many2+=masBad[y].many;
		 }
			xod=true;
		}
		          char M[10];                                 //Вывод на  экран состояния счета игроков
                 itoa(Many1,M,10);
                 SendMessage(editMany1, WM_SETTEXT, 0, (LPARAM)M);
                 itoa(Many2,M,10);
                 SendMessage(editMany2, WM_SETTEXT, 0, (LPARAM)M);	
				/* for(int i=0;i<16;i++){
				 if(i!=0||i!=5||i!=8||i!=13){
				 SendMessage(firma[i].edit, WM_SETTEXT, 0, (LPARAM)firma[i].player);
				 }
				 }  */


        
		}
		//*******конец обработки хода*****************

		break;
	case BN_CLICKED:
		
		break;

	case WM_CREATE:
		btnKup1=CreateWindowEx(NULL, "button", "Купить?", WS_CHILD | WS_VISIBLE, 300,255, 60, 20, hwnd, (HMENU)ID_BUTTON4, hinst, NULL);
		btnKup2=CreateWindowEx(NULL, "button", "Купить?", WS_CHILD | WS_VISIBLE, 732,255, 60, 20, hwnd, (HMENU)ID_BUTTON5, hinst, NULL);
		btnPlay1=CreateWindowEx(NULL, "button", "Игрок1", WS_CHILD | WS_VISIBLE|BS_BITMAP, mas[0].x-35,mas[0].y, 60, 60, hwnd, (HMENU)ID_BUTTON2, hinst, NULL);
	    btnPlay2=CreateWindowEx(NULL, "button", "Игрок2", WS_CHILD | WS_VISIBLE|BS_BITMAP, mas[0].x+35,mas[0].y, 60, 60, hwnd, (HMENU)ID_BUTTON3, hinst, NULL);
		btnBRAS = CreateWindowEx(NULL, "button", "Бросок", WS_CHILD | WS_VISIBLE, 510, 215, 60, 20, hwnd, (HMENU)ID_BUTTON1, hinst, NULL);	
		editRez = CreateWindowEx(NULL, "edit", "0", WS_CHILD | WS_VISIBLE, 580, 215, 15, 20, hwnd, (HMENU)ID_EDIT1, hinst, NULL);
		editMany1= CreateWindowEx(NULL, "edit", "100", WS_CHILD | WS_VISIBLE, 240, 430, 60, 20, hwnd, (HMENU)ID_EDIT2, hinst, NULL);//для отображения счета игроков
		editMany2= CreateWindowEx(NULL, "edit", "100", WS_CHILD | WS_VISIBLE, 825, 420, 60, 20, hwnd, (HMENU)ID_EDIT3, hinst, NULL);//для отображения счета игроков
		editNews2=CreateWindowEx(NULL, "edit", "Давай начнем!", WS_CHILD | WS_VISIBLE|ES_MULTILINE|ES_READONLY, 733, 290, 178, 80, hwnd, (HMENU)ID_EDIT3, hinst, NULL);
		editNews1=CreateWindowEx(NULL, "edit", "Давай начнем!", WS_CHILD | WS_VISIBLE|ES_MULTILINE|ES_READONLY, 180, 290, 180, 80, hwnd, (HMENU)ID_EDIT3, hinst, NULL);
		checkbox = CreateWindow("button", "Звук", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 800,470, 55, 14, hwnd, (HMENU)ID_CHECK, hinst, NULL);
		for(int i=0;i<16;i++){          // создание 16 edit и хорошая возможность заполнить массив firma
			firma[i].stoim=masCen[i];
			firma[i].shtraf=masShtr[i];
			
			if(i==0||i==5||i==8||i==13){
			continue;
			}
			strcpy(firma[i].player,"нет");
			firma[i].edit=CreateWindowEx(NULL, "edit", "нет", WS_CHILD | WS_VISIBLE,masEd[i].x,masEd[i].y, 60, 20, hwnd, (HMENU)i, hinst, NULL);
		} 
	    SendMessage (btnPlay1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmapP1);
		SendMessage (btnPlay2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmapP2);
	
		break;
    case WM_PAINT :
		//*************ничего интересного, прорисовка фона*****************
        hDC = BeginPaint(hwnd, &PaintStruct);
        hBitmap = LoadImage(NULL, "picture.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
        hCompatibleDC = CreateCompatibleDC(hDC);
        hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
        GetClientRect(hwnd, &Rect);
        StretchBlt(hDC, 0, 0, Rect.right, Rect.bottom, hCompatibleDC, 0, 0, Bitmap.bmWidth, 
            Bitmap.bmHeight, SRCCOPY);
        SelectObject(hCompatibleDC, hOldBitmap);
        DeleteObject(hBitmap);                          // а это попытка перекрыть утечку памяти
		DeleteObject(hBitmapP1);
		DeleteObject(hBitmapP2);
	    DeleteObject(editNews1);
        DeleteObject(editNews2);
		DeleteObject(btnPlay1);
		DeleteObject(btnPlay2);
		DeleteObject(editMany1);
		DeleteObject(editMany2);
		DeleteObject(btnBRAS);
		DeleteObject(editRez);
		DeleteObject( masEd);
		DeleteObject( mas);
		DeleteObject(firma);
		DeleteObject(masBad);
		DeleteObject(masNews);
	    DeleteObject(linux);
		//DeleteObject(hBitPropP1);
		//DeleteObject(hBitPropP2);
		for(int i=0;i<16;i++){
		DeleteObject(firma[i].edit);
		}
        DeleteDC(hCompatibleDC);
        EndPaint(hwnd, &PaintStruct);
        return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	
	return 0;

}


