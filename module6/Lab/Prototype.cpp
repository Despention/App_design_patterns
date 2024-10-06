#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

class IPrototype {
public:
    virtual unique_ptr<IPrototype> Clone() const = 0;
};

class Section : public IPrototype {
private:
    string title;
    string content;
public:
    Section(string t, string c) : title(t), content(c) {}
    unique_ptr<IPrototype> Clone() const override {
        return make_unique<Section>(*this);
    }
    void Show() const {
        cout << "Section: " << title << ", Content: " << content << endl;
    }
};

class Document : public IPrototype {
private:
    string title;
    vector<unique_ptr<Section>> sections;
public:
    Document(string t) : title(t) {}
    void AddSection(unique_ptr<Section> section) {
        sections.push_back(move(section));
    }
    unique_ptr<IPrototype> Clone() const override {
        unique_ptr<Document> clone = make_unique<Document>(title);
        for (const auto& section : sections) {
            clone->AddSection(unique_ptr<Section>(dynamic_cast<Section*>(section->Clone().release())));
        }
        return clone;
    }
    void Show() const {
        cout << "Document: " << title << endl;
        for (const auto& section : sections) {
            section->Show();
        }
    }
};

int main() {
    Document original("Original Document");
    original.AddSection(make_unique<Section>("Introduction", "This is the intro section"));
    original.AddSection(make_unique<Section>("Conclusion", "This is the conclusion section"));

    unique_ptr<Document> clone = unique_ptr<Document>(dynamic_cast<Document*>(original.Clone().release()));

    original.Show();
    clone->Show();

    return 0;
}
