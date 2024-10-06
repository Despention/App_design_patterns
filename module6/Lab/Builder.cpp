#include <iostream>
#include <string>

using namespace std;

class Computer {
public:
    string CPU;
    string RAM;
    string Storage;
    string GPU;
    string OS;

    string ToString() const {
        return "Компьютер: CPU - " + CPU + ", RAM - " + RAM + ", Storage - " + Storage + ", GPU - " + GPU + ", OS - " + OS;
    }
};

class IComputerBuilder {
public:
    virtual void SetCPU() = 0;
    virtual void SetRAM() = 0;
    virtual void SetStorage() = 0;
    virtual void SetGPU() = 0;
    virtual void SetOS() = 0;
    virtual Computer GetComputer() = 0;
};

class OfficeComputerBuilder : public IComputerBuilder {
private:
    Computer computer;
public:
    void SetCPU() override { computer.CPU = "Intel i3"; }
    void SetRAM() override { computer.RAM = "8GB"; }
    void SetStorage() override { computer.Storage = "1TB HDD"; }
    void SetGPU() override { computer.GPU = "Integrated"; }
    void SetOS() override { computer.OS = "Windows 10"; }
    Computer GetComputer() override { return computer; }
};

class GamingComputerBuilder : public IComputerBuilder {
private:
    Computer computer;
public:
    void SetCPU() override { computer.CPU = "Intel i9"; }
    void SetRAM() override { computer.RAM = "32GB"; }
    void SetStorage() override { computer.Storage = "1TB SSD"; }
    void SetGPU() override { computer.GPU = "NVIDIA RTX 3080"; }
    void SetOS() override { computer.OS = "Windows 11"; }
    Computer GetComputer() override { return computer; }
};

class ComputerDirector {
private:
    IComputerBuilder* builder;
public:
    ComputerDirector(IComputerBuilder* b) : builder(b) {}
    void ConstructComputer() {
        builder->SetCPU();
        builder->SetRAM();
        builder->SetStorage();
        builder->SetGPU();
        builder->SetOS();
    }
    Computer GetComputer() {
        return builder->GetComputer();
    }
};

int main() {
    OfficeComputerBuilder officeBuilder;
    ComputerDirector director(&officeBuilder);
    director.ConstructComputer();
    Computer officeComputer = director.GetComputer();
    cout << officeComputer.ToString() << endl;

    GamingComputerBuilder gamingBuilder;
    director = ComputerDirector(&gamingBuilder);
    director.ConstructComputer();
    Computer gamingComputer = director.GetComputer();
    cout << gamingComputer.ToString() << endl;

    return 0;
}
