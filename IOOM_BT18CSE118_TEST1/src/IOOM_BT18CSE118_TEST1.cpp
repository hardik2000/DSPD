//============================================================================
// Name        : IOOM_BT18CSE118_TEST1.cpp
// Author      : Hardik
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Employee
{
	public:
		Employee( const string &, const string &, const string & );
		void setFirstName( const string & ); // set first name
		string getFirstName() const; // return first name
		void setLastName( const string & ); // set last name
		string getLastName() const; // return last name
		void setSocialSecurityNumber( const string & ); // set SSN
		string getSocialSecurityNumber() const; // return SSN
		virtual double earnings() const = 0; // pure virtual
		virtual void print() const; // virtual
	private:
		string firstName;
		string lastName;
		string socialSecurityNumber;
}; // end class Employee
// constructor
Employee::Employee( const string &first, const string &last,const string &ssn )
: firstName( first ), lastName( last ), socialSecurityNumber( ssn )
{
}
void Employee::setFirstName( const string &first )
{
	firstName = first;
}
string Employee::getFirstName() const
{
   return firstName;
}
void Employee::setLastName( const string &last )
{
	lastName = last;
}
string Employee::getLastName() const
{
	return lastName;
} // end function getLastName
void Employee::setSocialSecurityNumber( const string &ssn )
{
	socialSecurityNumber = ssn; // should validate
}
string Employee::getSocialSecurityNumber() const
{
return socialSecurityNumber;
}void Employee::print() const
{
	cout << getFirstName() << ' ' << getLastName()
		<< "\nsocial security number: " << getSocialSecurityNumber();
}

class SalariedEmployee : public Employee
{
    private:
     double weeklySalary;

  public:
    SalariedEmployee( const string &, const string &, const string &, double = 0.0 );

    void setWeeklySalary( double );
    double getWeeklySalary() const;

    virtual double earnings() const;
    virtual void print() const;


};

SalariedEmployee::SalariedEmployee(const string &first,const string &last, const string &ssn, double salary ) : Employee( first, last, ssn )
{
        setWeeklySalary( salary );
}

void SalariedEmployee::setWeeklySalary( double salary )
{
	weeklySalary = ( salary < 0.0 ) ? 0.0 : salary;
}

double SalariedEmployee::getWeeklySalary() const
{
	return weeklySalary;
}


double SalariedEmployee::earnings() const
{
	return getWeeklySalary();
}

void SalariedEmployee::print() const
{
	cout << "salaried employee: ";Employee::print();cout << "\nweekly salary: " << getWeeklySalary();
}


class HourlyEmployee : public Employee
{
private:
  double wage;
  double hours;

public:
  HourlyEmployee(const string &, const string &,const string &, double = 0.0, double = 0.0);
  void setWage( double );
  double getWage() const;
  void setHours( double );
  double getHours() const;
  virtual double earnings() const;
  virtual void print() const;

};


HourlyEmployee::HourlyEmployee( const string &first, const string &last,const string &ssn, double hourlyWage, double hoursWorked )
:Employee( first, last, ssn )
{
  setWage( hourlyWage );
  setHours( hoursWorked );
}

void HourlyEmployee::setWage( double hourlyWage )
{
  wage = ( hourlyWage < 0.0 ? 0.0 : hourlyWage );
}

double HourlyEmployee::getWage() const
{
  return wage;
}

void HourlyEmployee::setHours( double hoursWorked )
{
  hours = ( ( ( hoursWorked >= 0.0 ) && ( hoursWorked <= 168.0 ) ) ?
  hoursWorked : 0.0 );
}

double HourlyEmployee::getHours() const
{
  return hours;
}

double HourlyEmployee::earnings() const
{
  if ( getHours() <= 40 )
  return getWage() * getHours();
  else
  return 40 * getWage() + ( ( getHours() - 40 ) * getWage() * 1.5 );
}

void HourlyEmployee::print() const
{
  cout << "Hourly Employee: ";
  Employee::print();
  cout << "\nHourly Wage: " << getWage() <<
  " Hours Worked: " << getHours();
}
class CommissionEmployee :public Employee
{
	private:
		double grossSales;
		double commissionRate;
	public:
		CommissionEmployee();
		CommissionEmployee( const string &first,const string &last, const string &ssn, double sales, double rate ):
		Employee(first,last,ssn)
		{

			setGrossSales( sales );
			setCommissionRate( rate );
		}
		void setCommissionRate( double );
		double getCommissionRate() const;
		void setGrossSales( double );
		double getGrossSales() const;
		virtual double earnings() const;
		virtual void print() const;
		//~CommissionEmployee();
};



void CommissionEmployee::setCommissionRate( double rate )
{
	commissionRate = ( ( rate > 0.0 && rate < 1.0 ) ? rate : 0.0 );
}
double CommissionEmployee::getCommissionRate() const
{
	return commissionRate;
}
void CommissionEmployee::setGrossSales( double sales )
{
	grossSales = ( ( sales < 0.0 ) ? 0.0 : sales );
}

double CommissionEmployee::getGrossSales() const
{
	return grossSales;
}
double CommissionEmployee::earnings() const
{
	return getCommissionRate() * getGrossSales();
}
void CommissionEmployee::print() const
{
	cout << "commission employee: ";Employee::print(); // code reuse
	cout << "\ngross sales: " << getGrossSales()
		<< "; commission rate: " << getCommissionRate();
} // end function print


class BasePlusCommissionEmployee : public CommissionEmployee
{
  public:
     BasePlusCommissionEmployee( const string &, const string &,
        const string &, double = 0.0, double = 0.0, double = 0.0 );

     void setBaseSalary( double );
     double getBaseSalary() const;

     virtual double earnings() const;
     virtual void print() const;

  private:
     double baseSalary;
};


  BasePlusCommissionEmployee::BasePlusCommissionEmployee(const string &first, const string &last, const string &ssn,double sales, double rate, double salary ): CommissionEmployee( first, last, ssn, sales, rate )
  {
     setBaseSalary( salary );
  }


  void BasePlusCommissionEmployee::setBaseSalary( double salary )
  {
     baseSalary = ( ( salary < 0.0 ) ? 0.0 : salary );
  }


  double BasePlusCommissionEmployee::getBaseSalary() const
  {
      return baseSalary;
  }


  double BasePlusCommissionEmployee::earnings() const
  {
      return getBaseSalary() + CommissionEmployee::earnings();
  }

  void BasePlusCommissionEmployee::print() const
  {
     cout << "base-salaried ";
     CommissionEmployee::print();
     cout << "; base salary: " << getBaseSalary();
  }


int main() {
    BasePlusCommissionEmployee b("hardik","hardik","BT18CSE118",0.10,1200,12000);
    b.print();
    cout<<b.earnings()<<endl;
    return 0;
	return 0;
}
