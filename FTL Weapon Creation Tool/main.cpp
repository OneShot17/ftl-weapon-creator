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
    // Variable initialization
    string path = "";
    string pwd = "";
    string weaponName = "";
    int weaponTypeNum = 0;
    string weaponType = "";
    string shortName = "";
    // Get path of folder that will contain mod contents
    cout << "Path of folder to create:\n";
    getline(cin,path);
    
    // Make the mod directory structure
    string command = "mkdir \"" + path + "\"";
    system(command.c_str());
    command = "mkdir \"" + path + "/data\"";
    system(command.c_str());
    command = "mkdir \"" + path + "/img\"";
    system(command.c_str());
    command = "mkdir \"" + path + "/audio\"";
    system(command.c_str());
    
    // Get the weapon name
    cout << "Weapon name: ";
    getline(cin,weaponName);
    // Set weapon-blueprint name based on weapon name (so it's easy to find in ship editors xD)
    char blueprintName[weaponName.length()];
    for(int i = 0; weaponName.c_str()[i] != '\0'; i++) {
        if(weaponName.c_str()[i] == ' ') {
            blueprintName[i] = '_';
            continue;
        }
        blueprintName[i] = weaponName.c_str()[i];
    }
    
    // Set short name of weapon
    cout << "Short name: ";
    getline(cin,shortName);
    // Get weapon type (NUMBER REQD!)
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
    
    // CD to data directory and open blueprints.xml.append in append mode, creating it if it doesn't exist
    pwd = path + "/data";
    command = "cd \"" + pwd + "\"";
    path = pwd + "/blueprints.xml.append";
    system(command.c_str());
    ofstream out(path,ios::app);
    
    /////////////////////////////
    // BEGIN BLUEPRINT WRITING //
    /////////////////////////////
    
    // Create blueprint open tag
    string tag = "weaponBlueprint name=\"";
    tag += blueprintName;
    tag += "\"";
    writeOpenTag(tag,out);
    // Create weapon type tag
    tag = "type";
    writeTag(tag, weaponType, out);
    // Create weapon title tag
    tag = "title";
    writeTag(tag, weaponName, out);
    // Create short name tag
    tag = "short";
    writeTag(tag,shortName, out);
    // Ask for description and write tag to file
    cout << "Descripton: ";
    string desc;
    getline(cin, desc);
    tag = "desc";
    writeTag(tag,desc,out);
    // Ask for tooltip and write tag to file
    cout << "Tooltip: ";
    string tooltip;
    getline(cin, tooltip);
    tag = "tooltip";
    writeTag(tag,tooltip,out);
    // Ask for damage value and write tag to file
    cout << "Damage: ";
    string damage;
    tag = "damage";
    getline(cin,damage);
    writeTag(tag,damage,out);
    // Ask for shield piercing value and write tag to file
    cout << "Shield piercing: ";
    string sp;
    getline(cin,sp);
    tag = "sp";
    writeTag(tag,sp,out);
    // Ask for fire chance and write tag to file
    cout << "Fire chance: ";
    string fireChance;
    tag = "fireChance";
    getline(cin,fireChance);
    writeTag(tag,fireChance,out);
    // Ask for cooldown and write tag to file
    cout << "Charge time: ";
    string cooldown;
    getline(cin,cooldown);
    tag = "cooldown";
    writeTag(tag,cooldown,out);
    // Ask for power requirement and write tag to file
    cout << "Power requirement: ";
    string power;
    tag = "power";
    getline(cin,power);
    writeTag(tag,power,out);
    
    // Code that still needs writing
    
    // Close weapon blueprint file
    tag = "weaponBlueprint";
    writeCloseTag(tag,out);
    out << endl << endl;
    out.close();
    
    //////////////////////////////////
    // BEGIN ANIMATION FILE WRITING //
    //////////////////////////////////
    
    
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
