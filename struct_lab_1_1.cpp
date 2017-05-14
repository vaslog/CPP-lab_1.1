
#include <cstdlib>
#include <iostream>
#include <fstream>

#include <string>
#include <cmath>
#include <ctime>
using namespace std;

const int marks_count = 50;
const int obj_count = 3;
//student//

class Student {
public:
    int id;
    Student *Next, *Prev; //Указатели на адреса следующего и предыдущего элементов списка
    string firstname, lastname;
    int marks_c[obj_count];
    int marks[obj_count][marks_count];
    float avg;

public:
    Student(string, string);
    //    ~Student();
    int Add_mark(int, int);
    int* Get_marks(int);
    float Get_avgball(void);
    string Objname_byid(int);
};

Student::Student(string firstname, string lastname) {

    this->firstname = firstname;
    this->lastname = lastname;

    for (int i = 0; i < obj_count; i++) {
        for (int j = 0; j < marks_count; j++)
            marks[i][j] = 0;
    }
    for (int i = 0; i < obj_count; i++)
        marks_c[i] = 0;
    std::cout << "Конструктор Student по умолчанию отработал(" << firstname << lastname << ")" << std::endl;
}

int Student::Add_mark(int obj_num, int mark) {
    //    cout<<"OBJ_NUM="<<obj_num<<" MARK="<<mark<<endl;
    if (obj_num >= 0 && obj_num < obj_count && mark >= 1 && mark <= 5 && marks_c[obj_num] < marks_count) {
        marks[obj_num][marks_c[obj_num]++] = mark;
        
        avg = Get_avgball();
        return 1;
        
    } else
        return 0;
}

int * Student::Get_marks(int obj_num = 0) {

    int* send_marks;
    send_marks = this->marks[obj_num];
    return send_marks;
}

float Student::Get_avgball() {
    float avg = 0;

    for (int j = 0; j < obj_count; j++)
        for (int i = 0; i < marks_c[j]; i++)
            avg += marks[j][i];
    if (marks_c[0] + marks_c[1] + marks_c[2])
        avg = avg / (marks_c[0] + marks_c[1] + marks_c[2]);
    else avg = 0;
    cout<<"ср балл "<<avg<<endl;
    return avg;
}

string Student::Objname_byid(int id) {
    switch (id) {
        case 0:
            return "Физика";
            break;
        case 1:
            return "Математика";
            break;
        case 2:
            return "Информатика";
            break;
        default:
            return "Unknown obj_id";
            break;
    }
}
//*student//

class Students {
    Student *Head, *Tail; //Указатели на адреса начала списка и его конца
public:

    Students()
    : Head(NULL)
    , Tail(NULL) {
    }; //Инициализируем адреса как пустые
    ~Students(); //Деструктор
    void Show(int, int, int); //Функция отображения студентов на экране

    int Count(void);
    void Add( Student* ); //Функция добавления студента в список
    Student * Add(string,string);
    
    int Delete(string, string); // 1 == success ; 0 == failed
    Student* Search(string, string);
    void Sync(string);
    int Mark_Count(int, int); //предмет, оценка = количество
    void Bad_Students(void);
    //    Student * Get_byid();
};

Students::~Students() { //Деструктоp
    while (Head) //Пока по адресу на начало списка что-то есть
    {
        Tail = Head->Next; //Резервная копия адреса следующего звена списка
        delete Head; //Очистка памяти от первого звена
        Head = Tail; //Смена адреса начала на адрес следующего элемента
    }
}

void Students::Add(Student * stud) {
     Student * place;
     place=Head;
     while(place)
     {
         if(!(place->avg<stud->avg))
         {
             place=place->Next;
             continue;
         }
         if(place==Head)
         {
             Head=stud;
             place->Prev=stud;
             stud->Next=place;
             return;
         }else
         {
             Student * temp;
             temp=place->Prev;
             place->Prev=stud;
             stud->Prev=temp;
             stud->Prev->Next=stud;
             return;
         }
                 
          
     }

    }
Student* Students::Add(string firstname,string lastname)
{
    Student * temp= new Student(firstname,lastname);
    temp->Next=NULL;
    if(Head!=NULL)
    {
        temp->Prev=Tail;
        Tail->Next=temp;
        Tail=temp;
        
    }else { temp->Prev=NULL; Head=Tail=temp;}
    return temp;
    
    
    
}
int Students::Delete(string firstname, string lastname) {
    
    Student* temp = Search(firstname, lastname);
    if (temp == NULL)
        return 0;
    Student *Prev = temp->Prev, *Next = temp->Next;
    if (Prev != NULL)
        Prev->Next = temp->Next;
    else
        Head = temp->Next;
    if (Next != NULL)
        Next->Prev = temp->Prev;
    else
        Tail = temp->Prev;
    delete temp;

    return 1;
}

void Students::Show(int ot, int otdo, int naprav = 1) {
    Student* temp = Tail;
    if (naprav) {

        temp = Head; //Временно указываем на адрес первого элемента
        int c = 1;
        while (temp != NULL) //Пока не встретим пустое значение
        {
            if (c >= ot && c <= otdo)
                std::cout << "(" << temp->Get_avgball() << ") " << temp->firstname << " " << temp->lastname << std::endl; //Выводим каждое считанное значение на экран

            c++;
            temp = temp->Next; //Смена адреса на адрес следующего элемента
        }
    } else {

        temp = Tail; //Временно указываем на адрес первого элемента
        int c = 1;
        while (temp != NULL) //Пока не встретим пустое значение
        {
            if (c >= ot && c <= otdo)
                std::cout << "(" << temp->Get_avgball() << ") " << temp->firstname << " " << temp->lastname << std::endl; //Выводим каждое считанное значение на экран
            c++;
            temp = temp->Prev; //Смена адреса на адрес следующего элемента
        }

    }


}

int Students::Count() {

    Student* temp = Tail;
    temp = Head; //Временно указываем на адрес первого элемента
    int c = 0;
    while (temp != NULL) //Пока не встретим пустое значение
    {
        c++;
        temp = temp->Next; //Смена адреса на адрес следующего элемента

    }
    return c + 1;

}

Student* Students::Search(string firstname = 0, string lastname = 0) {

    Student* temp = Tail;
    temp = Head; //Временно указываем на адрес первого элемента
    while (temp != NULL) //Пока не встретим пустое значение
    {
        if (temp->firstname == firstname && temp->lastname == lastname)
            return temp;
        temp = temp->Next; //Смена адреса на адрес следующего элемента
    }
    return NULL;
}

int Students::Mark_Count(int obj_id, int mark = 2) {
    int count = 0;

    Student* temp = Tail;

    temp = Head; //Временно указываем на адрес первого элемента
    while (temp != NULL) //Пока не встретим пустое значение
    {
        for (int i = 0; i < marks_count; i++) {
            if (temp->Get_marks(obj_id)[i] == mark)
                count++;
            else if (temp->Get_marks(obj_id)[i] == 0) break;

        }
        temp = temp->Next; //Смена адреса на адрес следующего элемента
    }


    return count;
}

void Students::Bad_Students() {

    Student* temp = Tail;
    int * Marks;
    temp = Head; //Временно указываем на адрес первого элемента
    while (temp != NULL) //Пока не встретим пустое значение
    {

        for (int i = 0; i < obj_count; i++) {
            Marks = temp->Get_marks(i);

            for (int j = 0; j < marks_count; j++) {
                if (Marks[j] == 2) {
                    cout << temp->firstname << " " << temp->lastname << endl;
                    j = marks_count;
                    i = obj_count;
                }

                //       
            }


        }
        temp = temp->Next; //Смена адреса на адрес следующего элемента
    }



}

void Students::Sync(string filename = "db") {
    if (Head == NULL) {//если список пустой, то заполняем его из файла, иначе сохраняем в файл
        string firstname = "", lastname = "", mark;
        ifstream file(filename);
        int lc = 0;
        Student* temp;
        Student * stud;
        int counter = 0;
        char ch, last;
        if (file) // если есть доступ к файлу,
        {
            while ((ch = file.get()) != EOF) {
                switch (ch) {
                    case ' ':
                        counter++;

                        ch = file.get();
                        break;
                    case ':':

                        counter++;
                        if (counter != 5) {
                            ch = file.get();
                            if (ch == ':'){ch = 0;
                            file.unget();}
                        }
                        break;
                }
                last = ch;
                cout << counter << endl;
                if (counter == 2 && firstname != "") {
                    cout << "Имя:" << firstname << " | Фамилия:" << lastname << endl;
                    stud = Add (firstname, lastname);
                     
                    firstname = lastname = "";


                }
                switch (counter) {
                    case 0:
                        firstname += ch;
                        break;
                    case 1:

                        lastname += ch;
                        break;
                    case 2://физика
                        mark += ch;

                        stud->Add_mark(0, ch - 48);
                        //                         cout<<stud->Add_mark(0,ch)<<endl;

                        break;
                    case 3://математика
                        mark += ch;
                        stud->Add_mark(1, ch - 48);
                        break;
                    case 4://информатика
                        mark += ch;
                        stud->Add_mark(2, ch - 48);
                        break;

                }

                //              
                if (counter == 5) {
                    cout << "Оценки:" << mark << endl;
                    mark = "";
                    counter = 0;
                }



            }
            file.close();
        } else {

            std::cout << ">>Нет доступа к файлу" << std::endl;


            ofstream file(filename, ios::out | ios::trunc);

            //   file<<"Артём Воробьев:5555:55555:44444:Василий Логинов:55445444:3535355:5555552:Влада Брысина:4455:435435:45554:Егор Камнев:544453:4444432:555555555:Александра Малыхина:55555333:5:4:Татьяна Гончарова:545435:44444444:555444:Никита Жаров:554444:345543:335554:Иван Захаров:544443:4444435:55555442:Денис Молошников:5555552:22:4444:Александр Когут:5354532:53333:44445:";

            file.close();

        }


    } else {
        //сохранение
        ofstream file(filename, ios::binary | ios::out);
        Student* temp;


        temp = Head; //Временно указываем на адрес первого элемента
        int c = 1;
        int * marks;
        char symbol = 32;
        while (temp != NULL) //Пока не встретим пустое значение
        {

            for (int i = 0; i < temp->firstname.size(); i++)
                file.write(&temp->firstname[i], sizeof (temp->firstname[i]));

            symbol = 32;
            file.write(&symbol, sizeof (symbol));
            for (int i = 0; i < temp->lastname.size(); i++)
                file.write(&temp->lastname[i], sizeof (temp->lastname[i]));
            symbol = ':';
            file.write(&symbol, sizeof (symbol));


            char b;
            for (int i = 0; i < obj_count; i++) {
                for (int j = 0; j < temp->marks_c[i]; j++) {
                    char b = temp->Get_marks(i)[j] + 48;
                    file.write(&b, 1);

                }
                file.write(&symbol, 1);

            }

            //            file.write();
            temp = temp->Next; //Смена адреса на адрес следующего элемента
        }

        file.close();




    }
}

void Menu(Students * temp) {

    string str;
    Student* stud;
    char a = -1, predmet = 0, mark = 2, page = 1;
    int pos, ot, otdo;
    int naprav = -1;
    int pagecount = 1;



    while (a != '0') {
        cout << "==============МЕНЮ==============" << endl;
        cout << "1. Добавить студента\n2. Удалить студента" << endl;
        cout << "3. Список студентов" << endl;
        cout << "4. Количество двоек по предметам\n5. Недобросовестные студенты " << endl;
        cout << "6. Оценки студента " << endl;
        cout << "7. Добавить оценку " << endl;
        cout << "0. Выход" << endl;
        cout << "================================" << endl;
        (cin >> a).get();
        //fflush(stdin);
        page = 1;
        naprav = -1;
        switch (a) {
            case '1':
                while (page != 0) {
                    cout << "=======Добавление студента======" << endl;
                    cout << "Введите имя и фамилию студента (Иван Иванов): " << endl;

                    getline(cin, str);

                    pos = str.find(" "); 
                    stud = new Student(str.substr(0, pos), str.substr(pos + 1, str.size()));
                   temp->Add(stud);
                    


                    for (int j = 0; j < obj_count; j++) {
                        cout << "Введите оценки по предмету " << stud->Objname_byid(j) << endl;
                        getline(cin, str);
                        for (int i = 0; i < str.size(); i++) {
                            mark = str.at(i);
                            if (mark >= '2' && mark <= '5')
                                stud->Add_mark(j, mark - 48);
                        }

                    }
                    temp->Add(stud);

                    cout << "Студент  добавлен" << endl;
                    cout << "Назад - 0" << endl;
                    cout << "================================" << endl;
                    (cin >> page).get();
                    page -= 48;
                }
                break;
            case '2':
                while (page != 0) {
                    cout << "=======Удаление студента======" << endl;
                    cout << "Введите имя и фамилию студента (Иван Иванов): " << endl;

                    getline(cin, str);

                    pos = str.find(" "); //
                    if (temp->Delete(str.substr(0, pos), str.substr(pos + 1, str.size())))
                        cout << "Студент " << str.substr(pos + 1, str.size()) << " удалён" << endl;
                    else cout << "Удаление не удалось, проверить Имя и Фамилию" << endl;
                    cout << "Назад - 0" << endl;
                    (cin >> page).get();
                    page -= 48;
                }
                break;

            case '3':
                pagecount = -1;
                while (page != 0) {
                    cout << "========Список студентов=======" << endl;
                    if (pagecount == -1)
                        for (pagecount = 1; pagecount < ceil(temp->Count() / 3.0); pagecount++);
                    if (page > pagecount) {
                        cout << "Нет такой страницы" << endl;
                    } else {
                        ot = page == 1 ? 1 : page * 3 - 3 + 1;
                        otdo = page == 1 ? 3 : 3 + (page - 1)*3;



                        if (naprav == -1) {
                            cout << "В каком порядке вывести? С конца (0) C начала (1)" << endl;

                            (cin >> naprav).get();
                        }
                        temp->Show(ot, otdo, naprav);
                    }
                    cout << "страницы: ";
                    for (int i = 0; i < ceil(temp->Count() / 3.0); i++) {
                        cout << i + 1 << " ";

                    }
                    cout << "\nНазад - 0" << endl;

                    (cin >> page).get();
                    page -= 48;
                }
                break;

            case '4':
                while (page != 0) {
                    cout << "=Количество двоек по предметам=" << endl;
                    cout << "Двоек по физике: " << temp->Mark_Count(0, 2) << endl;
                    cout << "Двоек по математике: " << temp->Mark_Count(1, 2) << endl;
                    cout << "Двоек по информатике: " << temp->Mark_Count(2, 2) << endl;
                    cout << "Назад - 0" << endl;
                    (cin >> page).get();
                    page -= 48;
                }
                break;
            case '5':
                while (page != 0) {
                    cout << "===Недобросовестные студенты====" << endl;
                    cout << "Студентами с двойками:" << endl;

                    temp->Bad_Students();
                    cout << "Назад - 0" << endl;

                    (cin >> page).get();
                    page -= 48;
                }
                break;
            case '6':
                while (page != 0) {
                    cout << "======Оценки студента=======" << endl;
                    cout << "Введите Имя Фамилию студента:" << endl;



                    getline(cin, str);

                    pos = str.find(" "); //
                    stud = temp->Search(str.substr(0, pos), str.substr(pos + 1, str.size()));
                    if (stud == NULL) cout << "Такой студент не найден" << endl;
                    else {
                        for (int j = 0; j < obj_count; j++) {
                            cout << "Оценки по ";
                            switch (j) {
                                case 0:
                                    cout << "математике" << endl;
                                    break;
                                case 1:
                                    cout << "физике" << endl;
                                    break;
                                case 2:
                                    cout << "информатике" << endl;
                                    break;
                            }
                            for (int i = 0; i < marks_count; i++) {
                                if (stud->Get_marks(j)[i] != 0) cout << stud->Get_marks(j)[i] << " ";
                                else i = marks_count;
                            }
                            cout << endl;
                        }
                    }
                    cout << "Назад - 0" << endl;

                    (cin >> page).get();
                    page -= 48;
                }
                break;

            case '7':

                while (page != 0) {
                    cout << "======Добавление оценки=======" << endl;
                    cout << "Введите Имя Фамилию студента:" << endl;

                    getline(cin, str);

                    pos = str.find(" "); //
                    stud = temp->Search(str.substr(0, pos), str.substr(pos + 1, str.size()));
                    if (stud == NULL) cout << "Такой студент не найден" << endl;
                    else {
                        cout << "Введите номер предмета" << endl;
                        cout << "0 - Физика\n1 - Математика \n2 - Информатика" << endl;
                        (cin >> predmet).get();
                        cout << "Введите оценку" << endl;
                        (cin >> mark).get();
                        predmet -= 48;
                        mark -= 48;
                        if (stud->Add_mark(predmet, mark))
                            cout << "Оценка успешно добавлена" << endl;
                        else cout << "Оценка не добавлена" << predmet << " " << mark << endl;
                    }
                    cout << "Назад - 0" << endl;

                    (cin >> page).get();
                    page -= 48;
                }
                break;

        }
    }


}

int main(int argc, char** argv) {
    string filename = "db";
    if (argc > 1)
        string filename = argv[1];
    else {
        cout << "Введите имя файла" << endl;
        cin>>filename;
    }
    Students stdns;
    stdns.Sync(filename);

    Menu(&stdns);
    stdns.Sync(filename);
    return 0;
}
