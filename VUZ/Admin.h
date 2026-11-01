#pragma once
#include "Base.h"

class Admin : public Base
{
private:
    string position;    // должность
    string phone;       // телефон
    string area;        // область ответственности

public:
    Admin();
    Admin(const string& fio, const string& position, const string& phone,
          const string& area);
    Admin(const Admin& other);
    ~Admin();

    string getPosition() const;
    string getPhone() const;
    string getArea() const;

    void setPosition(const string& position);
    void setPhone(const string& phone);
    void setArea(const string& area);

    string getType() const override;
    Base* clone() const override;
    void input() override;
    void edit() override;
    void print(ostream& out) const override;
    void save(ostream& out) const override;
    void load(istream& in) override;

    Admin& operator=(const Admin& other);
};
