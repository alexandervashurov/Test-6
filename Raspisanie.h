//  Raspisanie.h
//  Raspisanie
//  Created by Alex Vashurov on 04.12.14.
//  Copyright (c) 2014 Alex Vashurov. All rights reserved.


#pragma once                    //чтобы запускать класс один раз
#include<fstream>               //библиотеки
#include<vector>
#include<string>
#include<iostream>
using namespace std;

struct poezd{                   //структура
    string name;
    string time;
    int tttime;
    string endstation;
    vector <string> stations;
};

class Raspisanie
{
public:
    Raspisanie();
    bool load(string filename);                                     //загрузить из файла
    void save(string filename);                                     //сохранить в файле
    
    void newpoezd(string nomer, string time, string station);       //добавить новый поезд
    
    void deletepoezd(string nomer);                                 //удалить поезд
    
    void addstations(string nomer,string station);                  //добавить станции к поезду
    
    void delstations(string supp, string supp1);                    //удалить станции поезда
    
    void poryadok(string  cel, string vremya);                      //сортировка 
    
    void poisk(string  cel, string vremya);                         //поиск ближаешего времени
    
    int menu();
    
    ~Raspisanie();
    
    
private:
    
    vector<poezd> raspisanie;
};

