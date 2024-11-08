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
    virtual int GetSize() const = 0;

    virtual void Add(FileSystemComponent* component) {
        throw runtime_error("Operation not supported.");
    }

    virtual void Remove(FileSystemComponent* component) {
        throw runtime_error("Operation not supported.");
    }

    virtual ~FileSystemComponent() = default;
};

class File : public FileSystemComponent {
    int size;

public:
    File(const string& name, int size) : FileSystemComponent(name), size(size) {}

    void Display(int depth) const override {
        cout << string(depth, '-') << " File: " << name << " (" << size << " KB)" << endl;
    }

    int GetSize() const override {
        return size;
    }
};

class Directory : public FileSystemComponent {
    vector<FileSystemComponent*> children;

public:
    Directory(const string& name) : FileSystemComponent(name) {}

    void Add(FileSystemComponent* component) override {
        if (find(children.begin(), children.end(), component) == children.end()) {
            children.push_back(component);
        }
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

    int GetSize() const override {
        int totalSize = 0;
        for (const auto& child : children) {
            totalSize += child->GetSize();
        }
        return totalSize;
    }

    ~Directory() {
        for (auto child : children) {
            delete child;
        }
    }
};

int main() {
    Directory* root = new Directory("Root");
    File* file1 = new File("File1.txt", 100);
    File* file2 = new File("File2.txt", 200);

    Directory* subDir = new Directory("SubDirectory");
    File* subFile1 = new File("SubFile1.txt", 50);

    root->Add(file1);
    root->Add(file2);
    subDir->Add(subFile1);
    root->Add(subDir);

    cout << "File system structure:" << endl;
    root->Display(1);

    cout << "Total size: " << root->GetSize() << " KB" << endl;

    delete root;
    return 0;
}
