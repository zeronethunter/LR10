#include <iostream>
#include <filesystem>
#include <string>

using namespace std;
namespace fs = std::filesystem;

void print_instruction() {
    cout << "Commands:" << endl;
    cout << "1.  'current_path'" << endl;
    cout << "2.  'what_in'" << endl;
    cout << "3.  'create_dir'" << endl;
    cout << "4.  'file_size'" << endl;
    cout << "5.  'copy'" << endl;
    cout << "6.  'delete_file'" << endl;
    cout << "7.  'delete_dir'" << endl;
    cout << "8.  'rotate up or down'" << endl;
    cout << "9.  'rename_file'" << endl;
    cout << "10. 'move'" << endl;
    cout << "0.  'exit'" << endl;
    cout << "Enter only numbers" << endl;
}


int main() {
    string command, name_of_dir, name_of_file, name_where_to_copy, name;
    int num, count = 0;
    fs::path my_dir;
    while (true) {
        ++count;
        print_instruction();
        cin >> command;
        switch (stoi(command)) {
            default:
                cout << "Enter existing command\n";
                break;
            case 1:
                cout << " Current path is " << fs::current_path() << endl;
                break;
            case 2:
                num = 1;
                for (const auto &i : fs::directory_iterator(fs::current_path())) {
                    my_dir = i.path();
                    cout << num << ". " << my_dir.filename() << endl;
                    ++num;
                }
                break;
            case 3:
                cout << " Enter name of dir : ";
                cin.ignore(1);
                getline(cin, name_of_dir);
                my_dir = fs::current_path();
                if (!fs::exists(my_dir/name_of_dir)) {
                     fs::create_directory(name_of_dir);
                } else {
                    cout << "Directory is already exist\n";
                }
                cout << " Done!" << endl;
                break;
            case 4:
                cout << " Enter name of file : ";
                cin.ignore(1);
                getline(cin, name_of_file);
                my_dir = fs::current_path();
                if (fs::exists(my_dir/name_of_file)) {
                    cout << fs::file_size(my_dir / name_of_file) << " bytes" << endl;
                } else {
                    cout << "File doesn't exist!\n";
                }
                cout << " Done!\n";
                break;
            case 5:
                my_dir = fs::current_path();
                cout << " Enter what to copy : ";
                cin.ignore();
                getline(cin, name_of_file);
                cout << "Enter where to copy : ";
                getline(cin, name_where_to_copy);
                if (fs::exists(my_dir/name_of_file)) {
                    fs::copy(my_dir/name_of_file, my_dir/name_where_to_copy);
                    cout << "Done!\n";
                } else {
                    cout << "File doesn't exist!\n";
                }
                break;
            case 6:
                my_dir = fs::current_path();
                cout << " Enter file that you what to delete : ";
                cin.ignore();
                getline(cin, name_of_file);
                if (fs::exists(my_dir/name_of_file)) {
                    fs::remove(my_dir/name_of_file);
                    cout << "Done!\n";
                } else {
                    cout << "File doesn't exist!\n";
                }
                break;
            case 7:
                my_dir = fs::current_path();
                cout << " Enter directory that you what to delete : ";
                cin.ignore();
                getline(cin, name_of_file);
                if (fs::exists(my_dir/name_of_file)) {
                    fs::remove_all(my_dir/name_of_file);
                    cout << "Done!\n";
                } else {
                    cout << "Directory doesn't exist!\n";
                }
                break;
            case 8:
                cout << " Enter '1' if you want go down\n Enter '2' if you want to go up : ";
                cin.ignore();
                getline(cin, command);
                if (command == "1") {
                    fs::current_path(fs::current_path().remove_filename());
                } else if (command == "2") {
                    cout << "Enter name of directory : ";
                    getline(cin, name_of_dir);
                    if (!fs::exists(fs::current_path()/name_of_dir)) {
                        fs::create_directory(fs::current_path()/name_of_dir);
                    }
                    fs::current_path(fs::current_path()/name_of_dir);
                }
                cout << "Now you are here : " << fs::current_path() << endl;
                cout << " Done!\n";
                break;
            case 9:
                cout << " Enter file or directory that you want to rename : ";
                cin.ignore();
                getline(cin, name_of_file);
                my_dir = fs::current_path();
                cout << "Enter new name : ";
                getline(cin, name);
                if (fs::exists(my_dir/name_of_file)) {
                    fs::rename(my_dir/name_of_file, my_dir/name);
                    cout << "Done!\n";
                } else {
                    cout << "File or directory doesn't exist!\n";
                }
                break;
            case 10:
                cout << " Enter file or directory that you want to move : ";
                cin.ignore();
                getline(cin, name_of_file);
                my_dir = fs::current_path();
                cout << "Enter where you want to move : ";
                getline(cin, name);
                if (fs::exists(my_dir/name_of_file)) {
                    fs::rename(my_dir/name_of_file, my_dir/name/name_of_file);
                    cout << "Done!\n";
                } else {
                    cout << "File or directory doesn't exist!\n";
                }
                break;
            case 0:
                cout << "Bye bye!";
                return 0;
        }
    }
}