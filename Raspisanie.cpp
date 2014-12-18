//
//  main.cpp
//  Raspisanie
//
//  Created by Alex Vashurov on 04.12.14.
//  Copyright (c) 2014 Alex Vashurov. All rights reserved.
//

#include "Raspisanie.h"


Raspisanie::Raspisanie()
{
    //raspisanie.resize(1);
}

int inttime(string str)                             //возвращает время в минутах
{
    int flag = 0, i = 0;
    char supp[3];                                   //массив, 3- ноль-символ
    int result = 0, trans = 0;
    string part1, part2;
    while (i < str.size())
    {
        if (str[i] == ':'){
            flag = 1;
            i += 1;
        }
        if (flag == 0)
            part1.push_back(str[i]);
        if (flag == 1)
            part2.push_back(str[i]);
        i += 1;
    }
    for (i = 0; i < part1.size(); i++)
        supp[i] = part1[i];
    trans = atoi(supp);                             //перевод из char в int
    result = trans;
    for (i = 0; i < part2.size(); i++)
        supp[i] = part2[i];
    trans = atoi(supp);
    result *= 60;
    result += trans;
    return result;
}

int probeli(string str)                             //возвращает кол-во пробелов в начале строки
{
    int flag=0;
    for (int i = 0; i < str.size();i++)
        if (str[i] == ' ')
            flag += 1;
        else
            return flag;
    return flag;
}


void clearing(string &str)                         //удаляет пробелы из начала строки
{
    int a = probeli(str);
    str.erase(str.begin(), str.begin() + a);
}



bool Raspisanie::load(string filename)                      //загрузка расписания из файла
{
    ifstream input(filename);
    if (!input.is_open())
        return false;
    string stroka;
    char symbol;
    poezd supp;                                             //переменная типа поезд
    int i = 0;
    int flag = 0,flagstart=0;
    
    while (!input.eof())                                    //работа с файлом
    {
        input.get(symbol);
        if (symbol != '\n')
            stroka.push_back(symbol);
        else{
            if (probeli(stroka) < 2)
            {
                if (flagstart == 1)
                {
                    raspisanie.push_back(supp);
                    supp.name.clear();
                    supp.time.clear();
                    supp.endstation.clear();
                    supp.stations.clear();
                }
                if (flagstart == 0)
                    flagstart = 1;
                while (i<stroka.size())
                {
                    if (i == 0 && stroka[i] == ' ')
                        i += 1;
                    if (stroka[i] == ' '){
                        flag += 1;
                        i += 1;
                    }
                    if (flag == 0)
                        supp.name.push_back(stroka[i]);
                    if (flag == 1)
                        supp.time.push_back(stroka[i]);
                    if (flag == 2)
                        supp.endstation.push_back(stroka[i]);
                    i += 1;
                }
                flag = 0;
            }
            else{
                clearing(stroka);
                supp.stations.push_back(stroka);
            }
            stroka.clear();
            i = 0;
        }
    }
    
    raspisanie.push_back(supp);
    for (int k = 0; k < raspisanie.size(); k++)
        raspisanie[k].tttime = inttime(raspisanie[k].time);
    return true;
}



void Raspisanie::save(string filename)                                                      //сохранение файла
{
    ofstream output(filename);
    for (int i = 0; i < raspisanie.size(); i++){
        output << raspisanie[i].name << " " << raspisanie[i].time << " " << raspisanie[i].endstation << endl;
        for (int j = 0; j < raspisanie[i].stations.size(); j++)
            output << "    " << raspisanie[i].stations[j] << endl;
    }
}



void Raspisanie::newpoezd(string nomer,string time,string station)                          // новый поезд
{
    poezd supp;
    supp.name = nomer;
    supp.time = time;
    supp.endstation = station;
    supp.tttime = inttime(supp.time);
    raspisanie.push_back(supp);
}

void Raspisanie::deletepoezd(string supp)                                                   //удалить поезд со всеми станциями
{
    int flag = 0;
    for (int i = 0; i < raspisanie.size()&&flag==0;i++)
        if (raspisanie[i].name == supp){
            flag = 1;
            raspisanie.erase(raspisanie.begin() + i, raspisanie.begin() + i+1);
        }
    
}

void Raspisanie::addstations(string supp,string supp1)                                      //добавить станцию к поезду
{
    int flag = 0;
    for (int i = 0; i < raspisanie.size() && flag == 0; i++)
        if (raspisanie[i].name == supp){
            flag = 1;
            raspisanie[i].stations.push_back(supp1);
        }
}

void Raspisanie::delstations(string supp, string supp1)                                     //удаление станции у поезда
{
    int flag = 0,flag1=0;
    for (int i = 0; i < raspisanie.size() && flag == 0; i++)
        if (raspisanie[i].name == supp){
            flag = 1;
            for (int j = 0; j < raspisanie[i].stations.size() && flag1 == 0; j++)
                if (raspisanie[i].stations[j] == supp1){
                    flag1 = 1;
                    raspisanie[i].stations.erase(raspisanie[i].stations.begin() + i, raspisanie[i].stations.begin() + i + 1);
                }
        }
}

void Raspisanie::poisk(string  punktnaznach, string blizhvremia)
{
    int vvremya, besttime, bestpoezd=0, trans, flag = 0;
    
    vvremya = inttime(blizhvremia);
    besttime = vvremya;
    for (int i = 0; i < raspisanie.size(); i++)
    {
        if (raspisanie[i].endstation == punktnaznach){
            if (raspisanie[i].tttime >= vvremya)
                trans = raspisanie[i].tttime - vvremya;
            else
                trans = vvremya - raspisanie[i].tttime + 1440;
            
            if (trans <= besttime){
                besttime = trans;
                bestpoezd = i;
                flag = 1;
            }
        }
        for(int j=0;j<raspisanie[i].stations.size();j++)
            if (raspisanie[i].stations[j] == punktnaznach){
                if (raspisanie[i].tttime >= vvremya)
                    trans = raspisanie[i].tttime - vvremya;
                else
                    trans = vvremya - raspisanie[i].tttime + 1440;
                
                if (trans <= besttime){
                    besttime = trans;
                    bestpoezd = i;
                    flag = 1;
                }
            }
        
    }
    
    if (flag == 1){
        cout << raspisanie[bestpoezd].name << " " << raspisanie[bestpoezd].time << " " << raspisanie[bestpoezd].endstation << endl;
        for (int j = 0; j < raspisanie[bestpoezd].stations.size(); j++)
            cout << "    " << raspisanie[bestpoezd].stations[j] << endl;
    }
    else
        cout << "no way ! " << endl;
}

struct support
{
    int trans;
    int bestpoezd;
};

void Raspisanie::poryadok(string  cel, string vremya){     //список поездов до этой станции
    
    support goodpoezd;
    int vvremya, flag=0;
    
    
    vvremya = inttime(vremya);
    
    vector<support>goodpoezda;
    
    for (int i = 0; i < raspisanie.size(); i++)
    {
        if (raspisanie[i].endstation == cel)
        {
            if (raspisanie[i].tttime >= vvremya)
                goodpoezd.trans = raspisanie[i].tttime - vvremya;
            else
                goodpoezd.trans = vvremya - raspisanie[i].tttime + 1440;
            goodpoezd.bestpoezd = i;
            goodpoezda.push_back(goodpoezd);
            flag = 1;
        }
        
        for(int j=0;j<raspisanie[i].stations.size();j++)
            if (raspisanie[i].stations[j] == cel){
                if (raspisanie[i].tttime >= vvremya)
                    goodpoezd.trans = raspisanie[i].tttime - vvremya;
                else
                    goodpoezd.trans = vvremya - raspisanie[i].tttime + 1440;
                goodpoezd.bestpoezd = i;
                goodpoezda.push_back(goodpoezd);
                flag = 1;
            }
    }
    
    if (goodpoezda.size()>1)                                                            //пузырьковая сортировка
        for (int i = 0; i < goodpoezda.size(); i++)
            for (int j = 0; j <goodpoezda.size() - i ; j++)
                if (goodpoezda[j].trans > goodpoezda[j + 1].trans)
                    swap(goodpoezda[j], goodpoezda[j + 1]);
    
    if (flag == 1){
        for (int i = 0; i < goodpoezda.size(); i++){
            cout << raspisanie[goodpoezda[i].bestpoezd].name << " " << raspisanie[goodpoezda[i]. bestpoezd].time << " " << raspisanie[goodpoezda[i].bestpoezd].endstation << endl;
            for (int j = 0; j < raspisanie[goodpoezda[i].bestpoezd].stations.size(); j++)
                cout << "    " << raspisanie[goodpoezda[i].bestpoezd].stations[j] << endl;
        }
    }
    else
        cout << "no way man ! " << endl;
}

int Raspisanie::menu(){                         //вывод
    string supp,supp1,supp2;
    char symb;
    system("cls");
    cout << "Press: 1 to add new poezd, 2 to delete poezd, 3 to load raspisanie," << endl;
    cout << "4 to save raspisanie, 5 to add stations to poezd, 6 to del stations from poezd," << endl;
    cout << "7 to found best poezd, 8 to get list of poezd, e to exit." << endl;
    cin >> symb;
    cout << endl;
    switch (symb){
        case '1':cout << "vvedite nomer poezda: ";
            cin >> supp;
            cout << endl << "vremya otpravleniya: ";
            cin >> supp1;
            cout << endl << "konechnaya station: ";
            cin >> supp2;
            cout << endl;
            newpoezd(supp,supp1,supp2);
            break;
        case '2':cout << "vvedite poezd number: ";
            cin >> supp;
            cout << endl;
            deletepoezd(supp);
            break;
        case '3': cout << "enter filename: ";
            cin >> supp;
            cout << endl;
            load(supp);
            break;
        case '4': cout << "enter filename: ";
            cin >> supp;
            cout << endl;
            save(supp);
            break;
        case '5': cout << "vvedite poezd number: ";
            cin >> supp;
            cout << endl << "vvedite station: ";
            cin >> supp1;
            cout << endl;
            addstations(supp,supp1);
            break;
        case '6': cout << "vvedite poezd number: ";
            cin >> supp;
            cout << endl << "vvedite station: ";
            cin >> supp1;
            cout << endl;
            delstations(supp,supp1);
            break;
        case '7': cout << endl << "vvedite station naznacheniya: ";
            cin >> supp;
            cout << endl << "vvedite vremya: ";
            cin >> supp1;
            cout << endl;
            poisk(supp,supp1);
            break;
        case '8':cout << endl << "vvedite station naznacheniya: ";
            cin >> supp;
            cout << endl << "vvedite vremya: ";
            cin >> supp1;
            cout << endl;
            poryadok(supp,supp1);
            break;
        case 'e':return 0;
    }
    system("pause");
    menu();
    return 0;
    
}

Raspisanie::~Raspisanie()                                           //деструктор
{
}
