#include "curves_lib.h"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>
#include <numbers>
using namespace curves;
using namespace std;

int main()
{
    const size_t num_curves = 15;
    const double t_value = M_PI / 4.0;
    //1.Populate a container of objects of these types created in random manner with random parameters.
    vector<shared_ptr<Curve>> curves;
    for (size_t i = 0; i < num_curves; ++i) {
        curves.push_back(createRandomCurve());
    }
    //2.Print coordinates of points and derivatives of all curves in the container at t=PI/4.
    cout << "Points and derivatives at t = pi/4:" << endl;
    cout << fixed << setprecision(3);
    for (size_t i = 0; i < curves.size(); ++i)
    {
        curves[i]->PrintPointAndDerivative(t_value);
    }
    //3.Populate a second container that would contain only circles from the first container.
    vector<shared_ptr<Curve>> circles;
    for (const auto& curve : curves) {
        if (curve->IsCircle()) {
            circles.push_back(curve);
        }
    }
    //4.Sort the second container in the ascending order of radii.
    sort(circles.begin(), circles.end(), 
    [](const std::shared_ptr<Curve>& a, const std::shared_ptr<Curve>& b) 
    {
            return a->GetRadius() < b->GetRadius();
    });
    cout << "\nCircles sorted by radius:" << endl;
    for (size_t i = 0; i < circles.size(); ++i) {
        std::cout << "Circle " << i + 1 << ": radius = " << circles[i]->GetRadius() << std::endl;
    }
    //6.Compute the total sum of radii of all curves in the second container
    double sum_radius = calculateTotalRadiusParallel(circles);
    cout << "\nTotal radius sum of all circles: " << sum_radius << endl;
    return 0;
}