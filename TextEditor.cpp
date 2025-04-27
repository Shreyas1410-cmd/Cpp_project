
#include <iostream> 
#include <string> 
#include <fstream> 
#include <vector> 
 
using namespace std; 
 
class TextEditor { 
private: 
    vector<string> lines; 
    string filename; 
    bool isModified; 
 
public: 
    TextEditor() : filename(""), isModified(false) {} 
     
    void createNew(); 
    void openFile(); 
    void displayContent(); 
    void editContent(); 
    void saveFile(); 
    void saveFileAs(); 
    void searchText(); 
    void displayMenu(); 
    void run(); 
}; 
 
void TextEditor::createNew() { 
    if (isModified) { 
        char choice; 
        cout << "Current file has unsaved changes. Save? (y/n): "; 
        cin >> choice; 
        cin.ignore(); 
         
        if (choice == 'y' || choice == 'Y') { 
            saveFile(); 
        } 
    } 
     
    lines.clear(); 
    filename = ""; 
    isModified = false; 
    cout << "New file created. Use edit option to add content.\n"; 
} 

void TextEditor::openFile() { 
    string fname; 
    cout << "Enter filename to open: "; 
    getline(cin, fname); 
     
    ifstream file(fname); 
    if (!file) { 
        cout << "Error: Cannot open file " << fname << endl; 
        return; 
    } 
     
    lines.clear(); 
    string line; 
    while (getline(file, line)) { 
        lines.push_back(line); 
    } 
     
    file.close(); 
    filename = fname; 
    isModified = false; 
    cout << "File opened successfully: " << filename << endl; 
} 

void TextEditor::displayContent() { 
    if (lines.empty()) { 
        cout << "No content to display. File is empty.\n"; 
        return; 
    } 
     
    cout << "\n===== File Content =====\n"; 
    for (size_t i = 0; i < lines.size(); ++i) { 
        cout << i+1 << ":\t" << lines[i] << endl; 
    } 
    cout << "=======================\n"; 
} 

void TextEditor::editContent() { 
    displayContent(); 
     
    cout << "\nEditing Options:\n"; 
    cout << "1. Add new line at the end\n"; 
    cout << "2. Insert line at specific position\n"; 
    cout << "3. Edit existing line\n"; 
    cout << "4. Delete a line\n"; 
    cout << "5. Go back to main menu\n"; 
     
    int choice; 
    cout << "Enter your choice: "; 
    cin >> choice; 
    cin.ignore(); 
     
    string newLine; 
    int lineNum; 
     
    switch(choice) { 
        case 1: 
            cout << "Enter new line: "; 
            getline(cin, newLine); 
            lines.push_back(newLine); 
            isModified = true; 
            break; 
        case 2: 
            cout << "Enter line number to insert at: "; 
            cin >> lineNum; 
            cin.ignore(); 
            if (lineNum < 1 || lineNum > lines.size() + 1) { 
                cout << "Invalid line number.\n"; 
                return; 
            } 
            cout << "Enter new line: "; 
            getline(cin, newLine); 
            lines.insert(lines.begin() + lineNum - 1, newLine); 
            isModified = true; 
            break; 
        case 3: 
            cout << "Enter line number to edit: "; 
            cin >> lineNum; 
            cin.ignore(); 
            if (lineNum < 1 || lineNum > lines.size()) { 
                cout << "Invalid line number.\n"; 
                return; 
            } 
            cout << "Current line: " << lines[lineNum - 1] << endl; 
            cout << "Enter new content: "; 
            getline(cin, newLine); 
            lines[lineNum - 1] = newLine; 
            isModified = true; 
            break; 
        case 4: 
            cout << "Enter line number to delete: "; 
            cin >> lineNum; 
            cin.ignore(); 
            if (lineNum < 1 || lineNum > lines.size()) { 
                cout << "Invalid line number.\n"; 
                return; 
            } 
            lines.erase(lines.begin() + lineNum - 1); 
            isModified = true; 
            break; 
        case 5: 
            return; 
        default: 
            cout << "Invalid choice.\n"; 
    } 
    cout << "Content updated.\n"; 
} 

void TextEditor::saveFile() { 
    if (filename.empty()) { 
        saveFileAs(); 
        return; 
    } 
     
    ofstream file(filename); 
    if (!file) { 
        cout << "Error: Cannot save to " << filename << endl; 
        return; 
    } 
    for (const auto& line : lines) { 
        file << line << endl; 
    } 
    file.close(); 
    isModified = false; 
    cout << "File saved successfully: " << filename << endl; 
} 

void TextEditor::saveFileAs() { 
    string fname; 
    cout << "Enter filename to save as: "; 
    getline(cin, fname); 
    filename = fname; 
    saveFile(); 
} 

void TextEditor::searchText() { 
    if (lines.empty()) { 
        cout << "No content to search. File is empty.\n"; 
        return; 
    } 
    string searchTerm; 
    cout << "Enter text to search: "; 
    getline(cin, searchTerm); 
     
    bool found = false; 
    cout << "\nSearch results:\n"; 
     
    for (size_t i = 0; i < lines.size(); ++i) { 
        size_t pos = lines[i].find(searchTerm); 
        if (pos != string::npos) { 
            cout << "Line " << i+1 << ": " << lines[i] << endl; 
            found = true; 
        } 
    } 
    if (!found) { 
        cout << "No matches found for '" << searchTerm << "'.\n"; 
    } 
} 

void TextEditor::displayMenu() { 
    cout << "\n===== SIMPLE TEXT EDITOR =====\n"; 
    cout << "1. Create new file\n"; 
    cout << "2. Open file\n"; 
    cout << "3. Display content\n"; 
    cout << "4. Edit content\n"; 
    cout << "5. Save\n"; 
    cout << "6. Save as\n"; 
    cout << "7. Search text\n"; 
    cout << "8. Exit\n"; 
} 

void TextEditor::run() { 
    int choice = 0; 
    do { 
        displayMenu(); 
        cout << "Enter your choice: "; 
        cin >> choice; 
        cin.ignore(); 
        switch(choice) { 
            case 1: createNew(); break; 
            case 2: openFile(); break; 
            case 3: displayContent(); break; 
            case 4: editContent(); break; 
            case 5: saveFile(); break; 
            case 6: saveFileAs(); break; 
            case 7: searchText(); break; 
            case 8: cout << "Exiting editor...\n"; break; 
            default: cout << "Invalid choice. Try again.\n"; 
        } 
    } while(choice != 8); 
} 

int main() { 
    TextEditor editor; 
    editor.run(); 
    return 0; 
}
