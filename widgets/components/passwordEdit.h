#ifndef PASSWORD_EDIT_H
#define PASSWORD_EDIT_H

#include <Wt/WPasswordEdit.h>

class PasswordEdit : public Wt::WPasswordEdit {
public:
    PasswordEdit(const std::string& placeholder) : Wt::WPasswordEdit(placeholder) {}



private: 

Wt::WPasswordEdit* passwordEdit_;
};

#endif