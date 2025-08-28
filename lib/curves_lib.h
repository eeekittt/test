#include "vector"
#include <memory>

using namespace std;
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
namespace curves
{
    enum
    {
        CIRCLE = 0, ELIPSE = 1, HELIXES = 2
    };

    double pi = M_PI;
    
    class Curve{
        public:
            Curve(int ID_);
            virtual vector<double> GetPoint(double t) const = 0;
            virtual vector<double> GetDerivative(double t) const = 0;
            virtual double GetRadius() const = 0;
            void PrintPointAndDerivative(double t);
            bool IsCircle(){
                return (ID == CIRCLE);
            }
            int ID;//type curves
    };
    shared_ptr<Curve> createRandomCurve();
    double calculateTotalRadiusParallel(const vector<shared_ptr<Curve>>& curves);
    //---------------------------------------------------------------------------------//
    class Circle : public Curve {
        public:
            Circle();
            Circle(double radius_);
            //--------------------------//
            vector<double> GetPoint(double t) const override;
            vector<double> GetDerivative(double t) const override;
            double GetRadius() const override;
        private:
            double radius;
    };

    class Ellipse  : public Curve {
        public:
            Ellipse();
            Ellipse(double radius_x_, double radius_y_);
            //--------------------------//
            vector<double> GetPoint(double t) const override;
            vector<double> GetDerivative(double t) const override;
            double GetRadius() const override;
        private:
            double radius_x;
            double radius_y;
    };

    class Helixes : public Curve {
        public:
            Helixes();
            Helixes(double radius_, double step_);
            //--------------------------//
            vector<double> GetPoint(double t) const override;
            vector<double> GetDerivative(double t) const override;
            double GetRadius() const override;
        private:
            double radius;
            double step;
    };
};