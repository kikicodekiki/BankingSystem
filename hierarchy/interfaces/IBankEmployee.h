#pragma once
#include "MyString.h"
class IBankEmployee {
public :
    virtual void show_tasks () const = 0;

    virtual void view (const MyString& taskId) const  = 0;
    virtual void approve (const MyString& taskId)  = 0;
    virtual void disapprove (const MyString& taskId, const MyString& message) = 0;
    virtual void validate (const MyString& taskId) = 0;

    virtual ~IBankEmployee() = default;

};
