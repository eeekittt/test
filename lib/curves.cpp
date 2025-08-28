#include "curves_lib.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>


using namespace std;

static random_device rd;
static mt19937 gen(rd());
static uniform_real_distribution<> param(1.0, 50.0);
static uniform_int_distribution<> type(0, 2);

namespace curves {

 Curve::Curve(int ID_) :ID(ID_) {};
 void Curve::PrintPointAndDerivative(double t)
 {
    auto point = GetPoint(t);
    auto derivative = GetDerivative(t);
    cout << fixed << setprecision(3);
    switch(ID)
    {
        case CIRCLE:
        {
            cout << "Circle." << endl;
            break;
        }
        case ELIPSE:
        {
            cout << " Ellipse." << endl;
            break;
        }
        case HELIXES:
        {
            cout << "Helixes." << endl;
            break;
        }
        default:
        {
            break;
        }
    }
    cout << "  Point at t=" << t << ":      (" 
                  << setw(8) << point[0] << ", " 
                  << setw(8) << point[1] << ", " 
                  << setw(8) << point[2] << ")" << endl;
    cout << "  Derivative at t=" << t << ": (" 
                  << setw(8) << derivative[0] << ", " 
                  << setw(8) << derivative[1] << ", " 
                  << setw(8) << derivative[2] << ")" << endl;
    cout << "  Radius: " << setw(8) << GetRadius() << endl;
    cout << "---------------------------------------" << endl;
 };
 shared_ptr<Curve> createRandomCurve()
 {
     uint8_t curve_type = type(gen);
     switch (curve_type)
     {
     case CIRCLE:
     {
         return make_shared<Circle>();
     }
     case ELIPSE:
     {
         return make_shared<Ellipse>();
     }
     case HELIXES:
     {
         return make_shared<Helixes>();
     }
     default:
     {
         return make_shared<Circle>();
     }
     };
 };

//------------------------------------Circle-----------------------------//
    Circle::Circle(double radius_) : Curve(CIRCLE), radius(radius_) {
        if (radius <= 0) {
            throw invalid_argument("Radius must be positive");
        }
    }

    Circle::Circle() : Curve(CIRCLE), radius(param(gen)){ }

    vector<double> Circle::GetPoint(double t) const {
        return {radius * cos(t),radius * sin(t), 0.0};
    }

    vector<double> Circle::GetDerivative(double t) const {
        return {-radius * sin(t), radius * cos(t), 0.0};
    }

    double Circle::GetRadius() const {
        return radius;
    }
//--------------------------------EndCircle-----------------------------//

//------------------------------------Ellipse-----------------------------//
    Ellipse::Ellipse(double radius_x_, double radius_y_) : Curve(ELIPSE), radius_x(radius_x_), radius_y(radius_y_) {
        if (radius_x <= 0 || radius_y <= 0) {
            throw invalid_argument("Radius must be positive");
        }
    }

    Ellipse::Ellipse() : Curve(ELIPSE), radius_x(param(gen)), radius_y(param(gen)){ }

    vector<double> Ellipse::GetPoint(double t) const {
        return {radius_x * cos(t),radius_y * sin(t), 0.0};   
    }

    vector<double> Ellipse::GetDerivative(double t) const {
        return  {-radius_x * sin(t),radius_y * cos(t), 0.0};
    }

    double Ellipse::GetRadius() const {
        return ((radius_x + radius_y) / 2);
    }

//--------------------------------EndEllipse-----------------------------//

//------------------------------------Helixes-----------------------------//
    Helixes::Helixes(double radius_, double step_) : Curve(HELIXES), radius(radius_), step(step_) {
        if (radius <= 0 || step <= 0) {
            throw invalid_argument("Parametr must be positive");
        }
    }

    Helixes::Helixes() : Curve(HELIXES), radius(param(gen)), step(param(gen)){ }

    vector<double> Helixes::GetPoint(double t) const {
        return {radius * cos(t),radius * sin(t), (step * t)/(2 * pi)}; 
    }

    vector<double> Helixes::GetDerivative(double t) const {
        return {-radius * sin(t), radius * cos(t), step/(2 * pi)};
    }

    double Helixes::GetRadius() const {
        return radius;
    }
//--------------------------------EndHelixes-----------------------------//

     double calculateTotalRadiusParallel(const vector<shared_ptr<Curve>>& curves) {
        double total_radius = 0.0;

        #pragma omp parallel for reduction(+:total_radius)
        for (size_t i = 0; i < curves.size(); ++i) {
            total_radius += curves[i]->GetRadius();
        }

        return total_radius;
    }
};
