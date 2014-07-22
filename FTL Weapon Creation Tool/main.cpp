//
//  main.cpp
//  PhaserMaker Weapon Creator for FTL
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
    // Intro
    cout << "Welcome to the FTL Weapon Creation Tool. Please note that\n";
    cout << "all sounds must have the .ogg extension and all images \n";
    cout << "must have the .png extension. If any of your resources\n";
    cout << "are not in these formats, please convert them now." << endl;
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
    command = "mkdir \"" + path + "/audio/waves\"";
    system(command.c_str());
    command = "mkdir \"" + path + "/audio/waves/weapons\"";
    system(command.c_str());
    command = "mkdir \"" + path + "/img/weapons\"";
    system(command.c_str());
    
    // Get the weapon name
    cout << "Weapon name: ";
    getline(cin,weaponName);
    // Set weapon-blueprint name based on weapon name (so it's easy to find in ship editors xD)
    char blueprintName[weaponName.length()];
    int i;
    for(i = 0; weaponName.c_str()[i] != '\0'; i++) {
        if(weaponName.c_str()[i] == ' ') {
            blueprintName[i] = '_';
            continue;
        }
        blueprintName[i] = weaponName.c_str()[i];
    }
    blueprintName[i] = '\0';
    
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
    
    // Get garbage newline character that is stuck in cin stream
    
    cin.get();
    
    // CD to data directory and open blueprints.xml.append in append mode, creating it if it doesn't exist
    pwd = path + "/data";
    command = "cd \"" + pwd + "\"";
    string newpath = pwd + "/blueprints.xml.append";
    system(command.c_str());
    ofstream out(newpath,ios::app);
    
    // open animations.xml.append in append mode, creating it if it doesn't exist
    newpath = pwd + "/animations.xml.append";
    ofstream anims(newpath,ios::app);
    
    // open sounds.xml.append in append mode, creating it if it doesn't exist
    newpath = pwd + "/sounds.xml.append";
    ofstream sounds(newpath,ios::app);
    
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
    out << "    ";
    writeTag(tag, weaponType, out);
    // Create weapon title tag
    tag = "title";
    out << "    ";
    writeTag(tag, weaponName, out);
    // Create short name tag
    tag = "short";
    out << "    ";
    writeTag(tag,shortName, out);
    // Ask for description and write tag to file
    cout << "Descripton: ";
    out << "    ";
    string desc;
    getline(cin, desc);
    tag = "desc";
    writeTag(tag,desc,out);
    // Ask for tooltip and write tag to file
    cout << "Tooltip: ";
    out << "    ";
    string tooltip;
    getline(cin, tooltip);
    tag = "tooltip";
    writeTag(tag,tooltip,out);
    // Ask for damage value and write tag to file
    cout << "Damage: ";
    out << "    ";
    string damage;
    tag = "damage";
    getline(cin,damage);
    writeTag(tag,damage,out);
    // Ask for shield piercing value and write tag to file
    cout << "Shield piercing: ";
    out << "    ";
    string sp;
    getline(cin,sp);
    tag = "sp";
    writeTag(tag,sp,out);
    // Ask for fire chance and write tag to file
    cout << "Fire chance (1-10): ";
    out << "    ";
    string fireChance;
    tag = "fireChance";
    getline(cin,fireChance);
    writeTag(tag,fireChance,out);
    // Ask for cooldown and write tag to file
    cout << "Charge time: ";
    out << "    ";
    string cooldown;
    getline(cin,cooldown);
    tag = "cooldown";
    writeTag(tag,cooldown,out);
    // Ask for power requirement and write tag to file
    cout << "Power requirement: ";
    out << "    ";
    string power;
    tag = "power";
    getline(cin,power);
    writeTag(tag,power,out);
    // Ask for cost of weapon and write tag to file
    cout << "Cost in stores: ";
    out << "    ";
    string cost;
    tag = "cost";
    getline(cin,cost);
    writeTag(tag,cost,out);
    // Ask for speed and write tag to file
    cout << "Speed of weapon travel: ";
    out << "    ";
    string speed;
    tag = "speed";
    getline(cin,speed);
    writeTag(tag,speed,out);
    // Ask for rarity and write tag to file
    cout << "Rarity to find in stores/events (1-5): ";
    out << "    ";
    string rarity;
    tag = "rarity";
    getline(cin,rarity);
    writeTag(tag,rarity,out);
    // If weapon is a beam, ask for beam length and write tag to file
    if(strcmp(weaponType.c_str(),"BEAM") == 0) {
        cout << "Beam length: ";
        out << "    ";
        string length;
        tag = "length";
        getline(cin,length);
        writeTag(tag,length,out);
    }
    
    // Get name for projectile image/animation and write tag to file
    cout << "Name for projectile image: ";
    out << "    ";
    string image;
    tag = "image";
    getline(cin,image);
    while (image.find_first_of(' ') != image.npos) {
        image[image.find_first_of(' ')] = '-';
    }
    writeTag(tag,image,out);
    // Then get data for projectile animation frames and write to animations
    cout << "Image height: ";
    int h;
    cin >> h;
    cin.get();
    cout << "Image width: ";
    int w;
    cin >> w;
    cin.get();
    cout << "Frame height: ";
    int fw;
    cin >> fw;
    cin.get();
    cout << "Frame width: ";
    int fh;
    cin >> fh;
    cin.get();
    tag = "animSheet name=\"" + image + "\" w=\"" + to_string(w) + "\" h=\"" + to_string(h);
    tag += "\" fw=\"" + to_string(fw) + "\" fh=\"" + to_string(fh) + "\"";
    string val = "weapons/" + image;
    writeOpenTag(tag,anims);
    anims << "\b" << val;
    // Get path for projectile image/animation and cp it to mod directories
    cout << "Path to projectile image/animation sheet:\n";
    string projectilePath;
    tag = "image";
    getline(cin,projectilePath);
    command = "cp \"" + projectilePath + "\" \"" + path + "/img/weapons/" + image + "\"";
    system(command.c_str());
    // Open launch sounds tag
    writeOpenTag("launchSounds",out);
    // Get # of launch sounds and create array
    cout << "How many launch sounds? (please limit yourself to 2 or three)\n ";
    int launchSoundsNum;
    cin >> launchSoundsNum;
    cin.get();
    string *launchSounds;
    launchSounds = new string[launchSoundsNum];
    // Get names for launch sounds and write tags, also copy files
    tag = "sound";
    for(int i = 0; i < launchSoundsNum; i++) {
        cout << "Name of sound " << (i+1) << ": ";
        getline(cin,launchSounds[i]);
        out << "        ";
        writeTag(tag,launchSounds[i],out);
        cout << "Path to sound file: ";
        string path2File;
        getline(cin,path2File);
        command = "cp \"" + path2File + "\" \"" + path + "/img/weapons/" + launchSounds[i] + "\"";
        system(command.c_str());
    }
    // Close launch sounds tag
    writeCloseTag("launchSounds",out);
    // Open explosion sounds tag
    writeOpenTag("hitShipSounds",out);
    // Get # of explosion sounds and create array
    cout << "How many explosions? (please limit yourself to 2 or three)\n";
    int explosionSoundsNum;
    cin >> explosionSoundsNum;
    cin.get();
    string *explosionSounds;
    explosionSounds = new string[explosionSoundsNum];
    // Get names for launch sounds and write tags
    
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
