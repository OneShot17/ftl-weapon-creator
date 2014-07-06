//
//  main.cpp
//  FTL Weapon Creator Tool
//
//  Created by Stephen Brimhall on 7/5/14.
//  Copyright (c) 2014 Belman Industries. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void writeTag(string,string,ofstream &);
void writeOpenTag(string,ofstream &);
void writeCloseTag(string,ofstream &);

int main(int argc, const char * argv[]) {
    string path = "";
    string pwd = "";
    string weaponName = "";
    int weaponTypeNum = 0;
    string weaponType = "";
    string shortName = "";
    cout << "Path of folder to create:\n";
    getline(cin,path);
    string command = "mkdir \"" + path + "\"";
    system(command.c_str());
    command = "mkdir \"" + path + "/data\"";
    system(command.c_str());
    command = "mkdir \"" + path + "/img\"";
    system(command.c_str());
    command = "mkdir \"" + path + "/audio\"";
    system(command.c_str());
    cout << "Weapon name: ";
    getline(cin,weaponName);
    char blueprintName[weaponName.length()];
    for(int i = 0; weaponName.c_str()[i] != '\0'; i++) {
        if(weaponName.c_str()[i] == ' ') {
            blueprintName[i] = '_';
            continue;
        }
        blueprintName[i] = weaponName.c_str()[i];
    }
    cout << "Short name: ";
    getline(cin,shortName);
    cout << "Types:\nBeam (1)\nMissile (2)\nLaser (3)\nBomb (4)\nPick one: ";
    cin >> weaponTypeNum;
    switch (weaponTypeNum) {
        case 1:
            weaponType = "BEAM";
            break;
        case 2:
            weaponType = "MISSILE";
            break;
        case 3:
            weaponType = "LASER";
            break;
        case 4:
            weaponType = "BOMB";
            break;
    }
    pwd = path + "/data";
    command = "cd \"" + pwd + "\"";
    path = pwd + "blueprints.xml.append";
    system(command.c_str());
    static ofstream out(path,ios::app);
    string tag = "weaponBlueprint name=\"";
    tag += blueprintName;
    tag += "\"";
    writeOpenTag(tag,out);
    tag = "type";
    writeTag(tag, weaponType, out);
    tag = "title";
    writeTag(tag, weaponName, out);
    tag = "short";
    writeTag(tag,shortName, out);
    cout << "Descripton: ";
    string desc;
    getline(cin, desc);
    tag = "desc";
    writeTag(tag,desc,out);
    cout << "Tooltip: ";
    string tooltip;
    getline(cin, tooltip);
    tag = "tooltip";
    writeTag(tag,tooltip,out);
    cout << "Damage: ";
    string damage;
    tag = "damage";
    getline(cin,damage);
    writeTag(tag,damage,out);
    cout << "Shield piercing: ";
    string sp;
    getline(cin,sp);
    tag = "sp";
    writeTag(tag,sp,out);
    cout << "Fire chance: ";
    string fireChance;
    tag = "fireChance";
    getline(cin,fireChance);
    writeTag(tag,fireChance,out);
    cout << "Charge time: ";
    string cooldown;
    getline(cin,cooldown);
    tag = "cooldown";
    writeTag(tag,cooldown,out);
    tag = "weaponBlueprint";
    writeCloseTag(tag,out);
    out << endl << endl;
    return 0;
}

void writeTag(string tag, string value, ofstream &out) {
    out << "<" << tag.c_str() << ">" << value.c_str() << "</" << tag.c_str() << ">\n";
}

void writeOpenTag(string tag, ofstream &out) {
    out << "<" << tag.c_str() << ">\n";
}

void writeCloseTag(string tag, ofstream &out) {
    out << "</" << tag.c_str() << ">";
}
