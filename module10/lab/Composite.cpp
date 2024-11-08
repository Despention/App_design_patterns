#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
using namespace std;

class FileSystemComponent {
protected:
    string name;

public:
    FileSystemComponent(const string& name) : name(name) {}
    virtual void Display(int depth) const = 0;

    virtual void Add(FileSystemComponent* component) {
        throw runtime_error("Operation not supported.");
    }

    virtual void Remove(FileSystemComponent* component) {
        throw runtime_error("Operation not supported.");
    }

    virtual ~FileSystemComponent() = default;
};

class File : public FileSystemComponent {
public:
    File(const string& name) : FileSystemComponent(name) {}

    void Display(int depth) const override {
        cout << string(depth, '-') << " File: " << name << endl;
    }
};

class Directory : public FileSystemComponent {
    vector<FileSystemComponent*> children;

public:
    Directory(const string& name) : FileSystemComponent(name) {}

    void Add(FileSystemComponent* component) override {
        children.push_back(component);
    }

    void Remove(FileSystemComponent* component) override {
        children.erase(remove(children.begin(), children.end(), component), children.end());
    }

    void Display(int depth) const override {
        cout << string(depth, '-') << " Directory: " << name << endl;
        for (const auto& child : children) {
            child->Display(depth + 2); 
        }
    }

    ~Directory() {
        for (auto child : children) {
            delete child;
        }
    }
};

int main() {
    
    Directory* root = new Directory("Root");
    File* file1 = new File("File1.txt");
    File* file2 = new File("File2.txt");

    Directory* subDir = new Directory("SubDirectory");
    File* subFile1 = new File("SubFile1.txt");

    root->Add(file1);
    root->Add(file2);
    subDir->Add(subFile1);
    root->Add(subDir);

    root->Display(1);

    delete root;

    return 0;
}
