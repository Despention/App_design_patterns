#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Document {
public:
    virtual void Open() const = 0;
    virtual ~Document() = default;
};

class Report : public Document {
public:
    void Open() const override {
        cout << "Открытие отчета...\n";
    }
};

class Resume : public Document {
public:
    void Open() const override {
        cout << "Открытие резюме...\n";
    }
};

class Letter : public Document {
public:
    void Open() const override {
        cout << "Открытие письма...\n";
    }
};

class Invoice : public Document {
public:
    void Open() const override {
        cout << "Открытие счета-фактуры...\n";
    }
};

class DocumentCreator {
public:
    virtual unique_ptr<Document> CreateDocument() const = 0;
    virtual ~DocumentCreator() = default;
};

class ReportCreator : public DocumentCreator {
public:
    unique_ptr<Document> CreateDocument() const override {
        return make_unique<Report>();
    }
};

class ResumeCreator : public DocumentCreator {
public:
    unique_ptr<Document> CreateDocument() const override {
        return make_unique<Resume>();
    }
};

class LetterCreator : public DocumentCreator {
public:
    unique_ptr<Document> CreateDocument() const override {
        return make_unique<Letter>();
    }
};

class InvoiceCreator : public DocumentCreator {
public:
    unique_ptr<Document> CreateDocument() const override {
        return make_unique<Invoice>();
    }
};

void CreateDocumentFromFactory(const DocumentCreator& creator) {
    auto document = creator.CreateDocument();
    document->Open();
}

int main() {
    setlocale(LC_ALL, "Rus");
    
    int choice;
    cout << "Выберите тип документа:\n1. Отчет\n2. Резюме\n3. Письмо\n4. Счет-фактура\n";
    cin >> choice;

    switch (choice) {
        case 1: {
            ReportCreator reportFactory;
            CreateDocumentFromFactory(reportFactory);
            break;
        }
        case 2: {
            ResumeCreator resumeFactory;
            CreateDocumentFromFactory(resumeFactory);
            break;
        }
        case 3: {
            LetterCreator letterFactory;
            CreateDocumentFromFactory(letterFactory);
            break;
        }
        case 4: {
            InvoiceCreator invoiceFactory;
            CreateDocumentFromFactory(invoiceFactory);
            break;
        }
        default:
            cout << "Неверный выбор.\n";
            break;
    }

    return 0;
}
