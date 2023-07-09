// Yzer De Gula
// Customer.h Class for a Customer

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <cstdlib>

// Customer Implementation
class Customer
{
    public:
        // Default Constructor
        Customer() : name_(""), service_time_(0), priority_level_(0)
        {
            setPriorityLevel();
        } // End Default Constructor


        // Parameterized Constructor (1 Parameter)
        Customer(const std::string &name)
        : name_(name), service_time_(0), priority_level_(0)
        {
            setPriorityLevel();
        } // End Parameterized Constructor


        // Parameterized Constructor (2 Parameters)
        Customer(const std::string &name, int service_time)
        : name_(name), service_time_(service_time), priority_level_(0)
        {
            setPriorityLevel();
        } // End Parameterized Constructor


        // Copy Constructor
        Customer(const Customer &rhs) 
        : name_(rhs.name_), service_time_(rhs.service_time_), priority_level_(rhs.priority_level_)
        {} // End Copy Constructor


        // Copy Assignment
        Customer& operator=(const Customer &rhs)
        {
            name_ = rhs.name_;
            service_time_ = rhs.service_time_;
            priority_level_ = rhs.priority_level_;

            return *this;
        } // End Copy Assignment


        // Move Constructor
        Customer(Customer &&rhs)
        {
            name_ = rhs.name_;
            service_time_ = rhs.service_time_;
            priority_level_ = rhs.priority_level_;

            rhs.name_ = "";
            rhs.service_time_ = 0;
            rhs.priority_level_ = 0;
        } // End Move Constructor


        // Move Assignment
        Customer& operator=(Customer &&rhs)
        {
            std::swap(name_, rhs.name_);
            std::swap(service_time_, rhs.service_time_);
            std::swap(priority_level_,rhs.priority_level_);

            rhs.name_ = "";
            rhs.service_time_ = 0;
            rhs.priority_level_ = 0;

            return *this;
        } // End Move Assignment

        
        // Destructor
        ~Customer()
        {
            name_ = "";
            service_time_ = 0;
            priority_level_ = 0;
        } // End Destructor

    /**************************** START ACCESSORS ****************************/
        // getName
        std::string getName() const
        {
            return name_;
        } // End getName


        // getServiceTime
        int getServiceTime() const
        {
            return service_time_;
        } // End getServiceTime


        // getPriorityLevel
        int getPriorityLevel() const
        {
            return priority_level_;
        } // End getPriorityLevel

    /***************************  END  ACCESSORS  ****************************/
    /*************************************************************************/
    /**************************** START MUTATORS *****************************/
        // setName
        void setName(const std::string &name)
        {
            name_ = name;
        } // End setName


        // setServiceTime
        void setServiceTime(int service_time)
        {
            service_time_ = service_time;
        } // End setServiceTime


        // setPriorityLevel
        void setPriorityLevel(int priority_level)
        {
            priority_level_ = priority_level;
        } // End setPriorityLevel


        // setPriorityLevel
        void setPriorityLevel()
        {
            priority_level_ = rand() % 101;
        } // End setPriorityLevel


        // setServiceTime
        void setServiceTime()
        {
            service_time_ = rand() % 61;
        } // End setServiceTime

    /****************************** END MUTATORS *****************************/
    /*************************************************************************/
    /******************************** UTILITY ********************************/
        // display
        void display() const
        {
            std::cout << "Name:           " << getName() << std::endl;
            std::cout << "Service Time:   " << getServiceTime() << std::endl;
            std::cout << "Priority Level: " << getPriorityLevel() << std::endl;
            std::cout << std::endl;
        } // End display

        // Overloaded << operator
        friend std::ostream &operator<<(std::ostream &out, const Customer &customer)
        {
            out << std::endl;
            out << "    Name:           " << customer.getName() << std::endl;
            out << "    Service Time:   " << customer.getServiceTime() << std::endl;
            out << "    Priority Level: " << customer.getPriorityLevel() << std::endl;
            //out << std::endl;

            return out;
        } // End Overloaded << operator

    private:
        std::string name_;
        int service_time_;
        int priority_level_;
};

#endif // CUSTOMER_H